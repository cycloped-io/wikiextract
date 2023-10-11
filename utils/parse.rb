#!/usr/bin/env ruby

require 'bundler/setup'
require_relative '../ext/wikitext'
require_relative '../lib/wikiextractor'
require 'csv'
require 'pp'
require 'progress'
require 'slop'

# Changes in code below caused by a new Slop API version.
options = Slop.parse do |o|
  o.string '-w', '--wikipedia', 'Wikipedia dump path'
  o.string '-o', '--offsets', 'File with article offsets'
  o.string '-f', '--input', 'Text file to parse'
  o.integer '-a', '--article-id', 'Wiki id of article to parse (overrides range)'
  # Two integers below replaced range from previous version. This version doesn't support o.range
  o.integer '-rb', '--rangebegin', 'Range of article ids to be parsed (default all)', default: 0
  o.integer '-re', '--rangeend', 'Range of article ids to be parsed (default all)', default: -1
  o.string '-t', '--tokens', 'Output file with tokens', required: true
  o.string '-l', '--links', 'Output file with links', required: true
end

if options[:input].nil? && (options[:wikipedia].nil? || options[:offsets].nil?)
  puts "Either file or Wikipedia dump and database have to be specified"
  puts options
  exit
end

parser = Wikitext::Parser.new(options[:tokens],options[:links])

article_id = options[:"article-id"]
if article_id
  start = article_id
  stop = article_id
else
  # Replacement for older o.range
  start = options[:rangebegin]
  stop = options[:rangeend]
end

indices = []

begin
  Progress.start("Reading index", `wc -l #{options[:offsets]}`.to_i)
  CSV.open(options[:offsets]) do |input|
    input.each do |page_id, offset, length|
      Progress.step(1)
      page_id = page_id.to_i
      offset = offset.to_i
      length = length.to_i
      next if page_id < start
      break if page_id > stop && stop > -1
      indices << [page_id, offset, length]
    end
  end
ensure
  Progress.stop()
end

if options[:wikipedia]
  File.open(options[:wikipedia]) do |wikipedia|
    begin
      Progress.start("Parsing wikipedia", indices.size)
      indices.each do |page_id, offset, length|
        Progress.step
        wikipedia.seek(offset)
        #puts wikipedia.read(length)
        parser.parse(wikipedia.read(length), page_id)
      end
    ensure
      Progress.stop
      parser.close
    end
  end
else
  parser.parse(File.read(options[:input]),0)
  parser.close
end