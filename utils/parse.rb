#!/usr/bin/env ruby

require 'bundler/setup'
require_relative '../ext/wikitext'
require_relative '../lib/wikiextractor'
require 'csv'
require 'pp'
require 'progress'
require 'slop'

options = Slop.new do
  banner "#{$PROGRAM_NAME} -w dump.xml -d database -t tokens.tsv -l links.tsv [-a article_id|-r range]\n" +
    "#{$PROGRAM_NAME} -f file.txt -t tokens.tsv -l links.tsv\n" +
    "Convert Wikipedia XML dump to CSV containing text tokens and links.\n"

  on :w=, :wikipedia, "Wikipedia dump path"
  on :d=, :database, "Rod database with Wikipedia data"
  on :f=, :input, "Text file to parse"
  on :a=, :"article-id", "ROD id of article to parse", as: Integer
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

if options[:input].nil? && (options[:wikipedia].nil? || options[:database].nil?)
  puts "Either file or Wikipedia dump and database have to be specified"
  puts options
  exit
end

parser = Wikitext::Parser.new(options[:tokens],options[:links])
article_id = options[:"article-id"]

start = options[:range].first
stop = options[:range].last

if options[:wikipedia]
  require 'cyclopedio/wiki'
  Cyclopedio::Wiki::Page.path = options[:wikipedia]
  Cyclopedio::Wiki::Database.instance.open_database(options[:database])
  stop = Cyclopedio::Wiki::Article.count + stop if stop < 0
  stop = [stop,Cyclopedio::Wiki::Article.count].min

  Progress.start("Wiki tokens",stop-start)
  Cyclopedio::Wiki::Article.each do |article|
    next if !article_id && article.rod_id < start
    break if !article_id && article.rod_id > stop
    Progress.set(article.rod_id-start)
    if article_id
      next if article.rod_id < article_id
      break if article.rod_id > article_id
    end
    parser.parse(article.contents,article.rod_id)
  end
  parser.close
  Progress.stop
  Cyclopedio::Wiki::Database.instance.close_database
else
  parser.parse(File.read(options[:input]),0)
  parser.close
end
