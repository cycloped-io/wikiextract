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
    "Produce file with (link, linked_count, unlinked_count, (wiki_id, count)) and (wiki_id, (link, count))"

  on :i=, :links, "Dump of Wikipedia links", required: true
  on :t=, :tokens, "Dump of Wikipedia tokens", required: true
  on :f=, :first, "First ID articles to convert", as: Integer, default: 0
  on :l=, :last, "Last ID of articles to convert", as: Integer, default: -1
  on :o=, :output, "Output file with converted links", required: true
  on :r=, :occurrences, "Output file with articles and their links", required: true
  on :c=, :counts, "File with unliked link counts", required: true
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

class SimpleLink < Struct.new(:article_id,:first_token,:last_token,:target,:value)
  def include?(token)
    self.first_token <= token.token_id &&  token.token_id <= self.last_token
  end

  def <(token)
    self.last_token < token.token_id
  end


  def >(token)
    self.first_token > token.token_id
  end

  def add_token(token)
    raise "Invalid token #{token} for link #{self}" if self < token || self > token
    @tokens ||= []
    @tokens << token
  end

  def to_s
    @tokens ||= []
    "#{self.article_id} -- [#{self.first_token}:#{self.last_token}] -- #{self.value} -- #{self.target} -- #{@tokens.join(" ")}"
  end
end

class SimpleToken < Struct.new(:article_id,:token_id,:space_before, :value)
  def to_s
    "#{self.token_id}:'#{self.value}'"
  end
end

include Cyclopedio::Wiki

unlinked_link_counts = {}
CSV.open(options[:counts]) do |counts|
  counts.each do |tuple|
    unlinked_link_counts[tuple[0]] = tuple[1]
  end
end

Database.instance.open_database(options[:database])
if options[:last] < 0
  limit = `tail -1 #{options[:tokens]} | cut -f 1`.to_i
else
  limit = options[:last]
end

counter = Hash.new(0)
tokens_fiber = Fiber.new do
  File.open(options[:tokens],"r:utf-8") do |input|
    tokens = nil
    input.each do |line|
      begin
        tuple = line.chomp.split("\t")
        token = SimpleToken.new(*tuple[0..1].map(&:to_i),tuple[-2],tuple[-1])
        next if token.article_id < options[:first]
        break if token.article_id >= limit
        Fiber.yield(token)
      rescue => ex
        STDERR.puts "In fiber: #{line}"
        STDERR.puts ex
        STDERR.puts ex.backtrace
      end
    end
  end
  nil
end

link_to_article = Hash.new{|h,k| h[k] = Hash.new(0) }
article_to_link = Hash.new{|h,k| h[k] = Hash.new(0) }

File.open(options[:links],"r:utf-8") do |input|
  last_id = options[:first] - 1
  token = tokens_fiber.resume
  ids = []
  Progress.start(limit-options[:first]) unless options[:quiet]
  input.each do |link_line|
    begin
      tuple = link_line.chomp.split("\t")
      link = SimpleLink.new(*tuple[0..2].map(&:to_i),tuple[-2],tuple[-1])

      next if link.article_id < options[:first]
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

      while(link.include?(token))
        link.add_token(token)
        token = tokens_fiber.resume
        break if token.nil?
      end
      break if token.nil?

      link_to_article[link.value][target.wiki_id] += 1
      article_to_link[target.wiki_id][link.value] += 1
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

while(tokens_fiber.alive?) do
  tokens_fiber.resume
end

CSV.open(options[:output],"w") do |counts|
  link_to_article.each do |link, articles|
    unlinked_count = unlinked_link_counts[link]
    next if unlinked_count.nil?
    counts << [link, articles.sum{|a,v| v }, unlinked_count, *articles.to_a.flatten]
  end
end
CSV.open(options[:occurrences],"w") do |output|
  article_to_link.each do |wiki_id, links|
    output << [wiki_id, *links.keys]
  end
end
Database.instance.close_database
