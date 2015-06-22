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

class SimpleToken < Struct.new(:article_id,:line_start,:line_stop,:token_start,:token_stop,:type,:value)
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
	  simple_token = SimpleToken.new(*tuple[0..4].map(&:to_i),tuple[-2],tuple[-1])
	  next if simple_token.article_id < options[:offset]
	  break if simple_token.article_id >= limit
	  tokens.push(simple_token.article_id) if tokens.nil?

	  if tokens.first != simple_token.article_id
	    output << tokens unless tokens.size <= 1
	    tokens.clear
	    tokens.push(simple_token.article_id)
	  end
	  if simple_token.type != "space" && simple_token.type != "crlft"
	    token = Token.find_by_value(simple_token.value)
	    if token
	      tokens << token.rod_id 
	      Fiber.yield(simple_token,token)
	    end
	  end
	rescue => ex
	  STDERR.puts "In fiber: #{line}"
	  STDERR.puts ex
	  STDERR.puts ex.backtrace
	end
      end
    end
  end
  nil
end

CSV.open(options[:output],"w") do |output|
  File.open(options[:links],"r:utf-8") do |input|
    index = 0
    last_link_article_id = nil
    token_article_id = nil
    token_start_id = nil
    token_stop_id = nil
    type = nil
    simple_token = nil
    token = nil
    ids = []
    Progress.start(limit) unless options[:quiet]
    input.each do |link_line|
      begin
	tuple = link_line.chomp.split("\t")
	link = SimpleLink.new(*tuple[0..4].map(&:to_i),tuple[-2],tuple[-1])
	if link.article_id != last_link_article_id
	  index += 1 
	  Progress.step unless options[:quiet]
	end
	last_link_article_id = link.article_id

	next if index < options[:offset]
	break if index >= limit

	source = Article.find_by_rod_id(link.article_id)
	next if source.nil?
	target_name = link.target[0].upcase + link.target[1..-1]
	target = Article.find_with_redirect(target_name)
	next if target.nil?

	while(simple_token.nil? || link > simple_token) do
	  simple_token,token = tokens_fiber.resume
	  break if simple_token.nil?
	end
	#p ["l:#{target_name}",link.article_id,link.line_start,link.line_stop]
	ids.clear
	while(link.include?(simple_token))
	  #p ["t:#{simple_token.value}",simple_token.article_id,simple_token.line_start,simple_token.line_stop]
	  counter[token.rod_id] += 1
	  ids << token.rod_id
	  simple_token,token = tokens_fiber.resume
	end
	output << [ids.join("_"),"#{source.rod_id}_#{target.rod_id}"] unless ids.empty?
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
CSV.open(options[:counts],"w") do |counts|
  counter.each do |key,value|
    counts << [key,value]
  end
end
Database.instance.close_database
