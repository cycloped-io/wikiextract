#!/usr/bin/env ruby

require 'bundler/setup'
require_relative '../ext/wikitext'
require_relative '../lib/wikiextractor'
require 'slop'
require 'csv'
require 'progress'
require 'cyclopedio/wiki'
require 'string_case_pl'
require 'fiber'

options = Slop.new do
  banner "#{$PROGRAM_NAME} -i links.csv -d pathi/to/db [-x offset] [-l limit]\n" +
    "Convert links TSV to ids of tokens"

  on :i=, :links, "Dump of Wikipedia links", required: true
  on :t=, :tokens, "Dump of Wikipedia tokens", required: true
  on :x=, :offset, "Offset of articles to convert", as: Integer, default: 0
  on :l=, :limit, "Number of articles to convert", as: Integer, default: -1
  on :o=, :output, "Output file with converted links", required: true
  on :c=, :counts, "Output file with token counts", required: true
  on :w=, :text, "Output file with Wikipedia text converted to tokens", required: true
  on :d=, :database, "Path to ROD database", required: true
  on :q, :quiet, "Don't print progress"
end

begin
  options.parse
rescue => ex
  puts ex
  puts options
  exit
end

class SimpleLink < Struct.new(:article_id,:line_start,:line_stop,:token_start,:token_stop,:target,:value)
  def include?(token)
    self.article_id == token.article_id && 
      (self.line_start == token.line_start && self.token_start <= token.token_start || self.line_start < token.line_start) &&
      (self.line_stop == token.line_stop && self.token_stop >= token.token_stop || self.line_stop > token.line_stop)
  end

  def <(token)
    self.article_id < token.article_id ||
      (self.article_id == token.article_id && 
       (self.line_stop < token.line_start ||
	self.line_stop == token.line_start && self.token_stop < token.token_start))
  end


  def >(token)
    self.article_id > token.article_id ||
      (self.article_id == token.article_id &&
	 (self.line_start > token.line_stop ||
	  self.line_start == token.line_stop && self.token_start > token.token_stop))
  end
end

class SimpleToken < Struct.new(:article_id,:line_start,:line_stop,:token_start,:token_stop,:type,:value,:wiki_token)
end

include Cyclopedio::Wiki

Database.instance.open_database(options[:database])
if options[:limit] < 0
  limit = Article.count + 1
else
  limit = options[:limit]
end
counter = Hash.new(0)
tokens_fiber = Fiber.new do
  File.open(options[:tokens],"r:utf-8") do |input|
    CSV.open(options[:text],"w") do |output|
      tokens = nil
      input.each do |line|
	begin
	  tuple = line.chomp.split("\t")
	  token = SimpleToken.new(*tuple[0..4].map(&:to_i),tuple[-2],tuple[-1],nil)
	  next if token.article_id < options[:offset]
	  break if token.article_id >= limit
	  tokens = [token.article_id] if tokens.nil?

	  if tokens.first != token.article_id
	    output << tokens unless tokens.size <= 1
	    tokens.clear
	    tokens.push(token.article_id)
	  end
	  if token.type != "space" && token.type != "crlft"
	    wiki_token = Token.find_by_value(token.value)
	    if wiki_token
	      tokens << wiki_token.rod_id 
	      token.wiki_token = wiki_token
	      Fiber.yield(token)
	    end
	  end
	rescue => ex
	  STDERR.puts "In fiber: #{line}"
	  STDERR.puts ex
	  STDERR.puts ex.backtrace
	end
      end
      output << tokens unless tokens.size <= 1
    end
  end
  nil
end

CSV.open(options[:output],"w") do |output|
  File.open(options[:links],"r:utf-8") do |input|
    last_id = options[:offset] - 1
    token = tokens_fiber.resume
    ids = []
    Progress.start(limit-options[:offset]) unless options[:quiet]
    input.each do |link_line|
      begin
	tuple = link_line.chomp.split("\t")
	link = SimpleLink.new(*tuple[0..4].map(&:to_i),tuple[-2],tuple[-1])

	next if link.article_id < options[:offset]
	break if link.article_id >= limit
	if link.article_id != last_id
	  Progress.step unless options[:quiet]
	end
	last_id = link.article_id

	target_name = link.target[0].upcase + link.target[1..-1]
	target = Article.find_with_redirect(target_name)
	next if target.nil?

	while(link > token) do
	  token = tokens_fiber.resume
	  break if token.nil?
	end
	break if token.nil?
	#p ["l:#{target_name}",link.article_id,link.line_start,link.line_stop]
	ids.clear
	while(link.include?(token))
	  #p ["t:#{token.value}",token.article_id,token.line_start,token.line_stop]
	  counter[token.wiki_token.rod_id] += 1
	  ids << token.wiki_token.rod_id
	  token = tokens_fiber.resume
	  break if token.nil?
	end
	break if token.nil?
	output << [ids.join("_"),"#{link.article_id}_#{target.rod_id}"] unless ids.empty?
      rescue Interrupt
	break
      rescue => ex
	STDERR.puts "In main: #{link_line}"
	STDERR.puts ex
	STDERR.puts ex.backtrace
      end
    end
    Progress.stop unless options[:quiet]
  end
end
while(tokens_fiber.alive?) do
  tokens_fiber.resume
end
CSV.open(options[:counts],"w") do |counts|
  counter.each do |key,value|
    counts << [key,value]
  end
end
Database.instance.close_database
