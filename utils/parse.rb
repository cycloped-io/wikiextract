#!/usr/bin/env ruby

require 'bundler/setup'
require_relative '../ext/wikitext'
require_relative '../lib/wikiextractor'
require 'csv'
require 'pp'
require 'progress'
require 'slop'

options = Slop.new do
  banner "#{$PROGRAM_NAME} -w dump.xml -o offsets.csv -t tokens.tsv -l links.tsv [-a article_id|-r range]\n" +
    "#{$PROGRAM_NAME} -f file.txt -t tokens.tsv -l links.tsv\n" +
    "Convert Wikipedia XML dump to CSV containing text tokens and links.\n"

  on :w=, :wikipedia, "Wikipedia dump path"
  on :o=, :offsets, "File with article offsets"
  on :f=, :input, "Text file to parse"
  on :a=, :"article-id", "Wiki id of article to parse (overrides range)", as: Integer
  on :r=, :range, "Range of article ids to be parsed (default all)", as: Range, default: (0..-1)
  on :t=, :tokens, "Output file with tokens", required: true
  on :l=, :links, "Output file with links", required: true
end

begin
  options.parse
rescue => ex
  puts ex
  puts options
  exit
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
  start = options[:range].first
  stop = options[:range].last
end

if options[:wikipedia]
  Progress.start("Wiki tokens",stop-start)
  File.open(options[:wikipedia]) do |wikipedia|
    CSV.open(options[:offsets]) do |input|
      input.each do |page_id, offset, length|
        page_id = page_id.to_i
        offset = offset.to_i
        length = length.to_i
        next if page_id < start
        break if page_id > stop
        Progress.set(page_id-start)
        wikipedia.seek(offset)
        #puts wikipedia.read(length)
        parser.parse(wikipedia.read(length), page_id)
      end
    end
  end
  parser.close
  Progress.stop
else
  parser.parse(File.read(options[:input]),0)
  parser.close
end
