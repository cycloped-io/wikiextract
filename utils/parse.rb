#!/usr/bin/env ruby

require 'bundler/setup'
$:.unshift "."
require_relative '../ext/wikitext'
require_relative '../lib/wikiextractor'
require 'csv'
require 'pp'
require 'rlp/wiki'
require 'progress'
require 'slop'

options = Slop.new do
  banner "#{$PROGRAM_NAME} -w dump.xml -d database -s segments.csv -l links.csv [-a article_id|-r range]\n" +
    "#{$PROGRAM_NAME} -f file.txt -s segments.csv -l links.csv\n" +
    "Convert Wikipedia XML dump to CSV containing text segments and links.\n"
    "The results are always stored in "

  on :w=, :wikipedia, "Wikipedia dump path"
  on :d=, :database, "Rod database with Wikipedia data"
  on :f=, :input, "Text file to parse"
  on :a=, :"article-id", "Id of article to parse", as: Integer
  on :r=, :range, "Range of article ids to be parsed (default 0-10000)"
  on :s=, :segments, "Output file with segments (tokens)", required: true
  on :l=, :links, "Output file with links", required: true
end

begin
  options.parse
rescue => ex
  puts ex
  puts options
  exit
end

if options[:input].nil? && (options[:wikipedia].nil? || options[:database].nil?)
  puts "Either file or Wikipedia dump and database have to be specified"
  puts options
  exit
end

parser = Wikitext::Parser.new(options[:segments],options[:links])
article_id = options[:"article-id"]

if options[:range]
  _,start,stop = options[:range].match(/(\d+)-(\d+)/).to_a.map(&:to_i)
else
  start = 0
  stop = 10000
end

if options[:wikipedia]
  Rlp::Wiki::Page.path = options[:wikipedia]
  Rlp::Wiki::Database.instance.open_database(options[:database])

  Progress.start("Wiki segments",stop-start)
  Rlp::Wiki::Concept.each do |concept|
    next if !article_id && concept.wiki_id < start
    break if !article_id && concept.wiki_id > stop
    Progress.set(concept.wiki_id)
    if article_id
      next if concept.wiki_id < article_id
      break if concept.wiki_id > article_id
    end
    parser.parse(concept.contents,concept.wiki_id)
  end
  parser.close
  Progress.stop
  Rlp::Wiki::Database.instance.close_database
else
  parser.parse(File.read(options[:input]),0)
  parser.close
end
