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
  banner "#{$PROGRAM_NAME} -w dump.xml -d database [-a article_id]\n" +
    "Convert Wikipedia XML dump to CSV containing text segments and links.\n"
    "The results are always stored in "

  on :w=, :wikipedia, "Wikipedia dump path", required: true
  on :d=, :database, "Rod database with Wikipedia data", required: true
  on :a=, :"article-id", "Id of article to parse", as: Integer
  on :s=, :segments, "Output file with segments", required: true
  on :l=, :links, "Output file with links", required: true
end

begin
  options.parse
rescue => ex
  puts ex
  puts options
  exit
end

parser = Wikitext::Parser.new(options[:segments],options[:links])
article_id = options[:"article-id"]

start = 0
stop = 10000
Rlp::Wiki::Page.path = options[:wikipedia]
Rlp::Wiki::Database.instance.open_database(options[:database])

Progress.start("Wiki segments",stop-start)
Rlp::Wiki::Concept.each.with_index do |concept,index|
  next if index < start && !article_id
  break if index > stop && !article_id
  Progress.step
  if article_id
    break if concept.wiki_id > article_id
    next if concept.wiki_id < article_id
  end
  parser.parse(concept.contents,concept.wiki_id)
end
parser.close
Progress.stop
Rlp::Wiki::Database.instance.close_database
