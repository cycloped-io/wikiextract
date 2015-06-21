#!/usr/bin/env ruby

require 'bundler/setup'
require_relative '../ext/wikitext'
require_relative '../lib/wikiextractor'
require 'slop'
require 'colors'
require 'csv'
require 'progress'
require 'cyclopedio/wiki'
require 'string_case_pl'
require 'timeout'
require 'tempfile'

options = Slop.new do
  banner "#{$PROGRAM_NAME} -i links.csv -d pathi/to/db [-x offset] [-l limit]\n" +
    "Convert links TSV to ids of tokens"

  on :i=, :links, "Dump of Wikipedia links", required: true
  on :x=, :offset, "Offset of articles to convert", as: Integer, default: 0
  on :l=, :limit, "Number of articles to convert", as: Integer, default: -1
  on :o=, :output, "Output file with converted links", required: true
  on :c=, :counts, "Output file with token counts", required: true
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

include Cyclopedio::Wiki


value_reader,value_writer = IO.pipe
fifo_name = Tempfile.new("tokens")
`mkfifo #{fifo_name.path}`
if fork
  Database.instance.open_database(options[:database])
  if options[:limit] < 0
    limit = Article.count + 1
  else
    limit = options[:limit]
  end
  tokens_reader = File.open(fifo_name.path,"r:utf-8")
  value_reader.close
  counter = Hash.new(0)
  CSV.open(options[:output],"w") do |output|
    File.open(options[:links],"r:utf-8") do |input|
      index = 0
      last_article_id = nil
      ids = []
      Progress.start(limit) unless options[:quiet]
      input.each do |link_line|
	begin
	  tuple = link_line.split("\t")
	  link = tuple.pop
	  target_name = tuple.pop
	  source_wiki_id = tuple.shift.to_i
	  if source_wiki_id != last_article_id
	    index += 1 
	    Progress.step unless options[:quiet]
	  end
	  last_article_id = source_wiki_id

	  next if index < options[:offset]
	  break if index >= limit

	  value_writer.puts(link)
	  value_writer.flush
	  ids.clear
	  Timeout.timeout(3) do
	    while(line = tokens_reader.gets) do
	      elements = line.chomp.split("\t")
	      type,value = elements.pop(2)
	      next if type == "space"
	      break if type == "crlft"
	      token = Token.find_by_value(value)
	      next if token.nil?
	      counter[token.rod_id] += 1
	      ids << token.rod_id
	    end
	  end
	  source = Article.find_by_wiki_id(source_wiki_id)
	  next if source.nil?
	  target_name = target_name[0].upcase + target_name[1..-1]
	  target = Article.find_with_redirect(target_name)
	  next if target.nil?
	  output << [ids.join("_"),"#{source.rod_id}_#{target.rod_id}"]
	rescue Interrupt
	  break
	rescue => ex
	  puts link_line
	  puts ex
	  puts ex.backtrace
	end
      end
      value_writer.close
      Progress.stop unless options[:quiet]
    end
  end
  CSV.open(options[:counts],"w") do |counts|
    counter.each do |key,value|
      counts << [key,value]
    end
  end
  Process.wait
  Database.instance.close_database
  fifo_name.unlink
else
  value_writer.close
  parser = Wikitext::Parser.new(fifo_name.path,"/dev/null")
  while(value = value_reader.gets)
    parser.parse(value,1)
    parser.flush_files
  end
end
