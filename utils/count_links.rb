#!/usr/bin/env ruby

require 'bundler/setup'
require 'csv'
require 'progress'
require 'slop'
require 'cyclopedio/wiki'

options = Slop.new do
  banner "#{$PROGRAM_NAME} -t tokens_text.csv -d database -o candidates.csv\n" +
    "Count link occurrences in Wikipedia text."

  on :d=, :database, "Rod database with Wikipedia data", required: true
  on :t=, :tokens, "File with text tokens", required: true
  on :o=, :counts, "Output file with link counts", required: true
  on :l=, :limit, "Limit for articles (last-1 article to process)", as: Integer
  on :x=, :offset, "Offset of articles (first article to process)", as: Integer, default: 0
  on :q, :quiet, "Don't print progress"
end

begin
  options.parse
rescue => ex
  puts ex
  puts options
  exit
end

include Cyclopedio::Wiki
Database.instance.open_database(options[:database])

counts = Hash.new(0)
limit = options[:limit] || Article.count+1
CSV.open(options[:tokens]) do |input|
  Progress.start(limit-options[:offset]) unless options[:quiet]
  last_id = nil
  input.each do |tokens|
    begin
      tokens.map!(&:to_i)
      article_id = tokens.shift
      next if article_id < options[:offset]
      break if article_id >= limit
      Progress.step if !options[:quiet] && last_id != article_id
      last_id = article_id
      tokens.each.with_index do |token_id,index|
	token = Token.find_by_rod_id(token_id)
	trie = token.trie
	current_index = index + 1
	next if current_index >= tokens.size
	while(trie) do
	  counts[trie.trace] += 1
	  trie = trie.fast_search(tokens[current_index])
	  current_index += 1
	  break if current_index >= tokens.size
	end
      end
    rescue Interrupt
      break
    end
  end
  Progress.stop
end
Database.instance.close_database
CSV.open(options[:counts],"w") do |output|
  Progress.start(counts.size) unless options[:quiet]
  counts.each do |tuple|
    Progress.step unless options[:quiet]
    output << tuple
  end
  Progress.stop unless options[:quiet]
end
