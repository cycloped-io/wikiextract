#!/usr/bin/env ruby

require 'bundler/setup'
require 'slop'
require 'colors'
require 'csv'

options = Slop.new do
  banner "#{$PROGRAM_NAME} -t tokens.csv -l links.csv -a article_id\n" +
    "Display dumped Wikipedia article"

  on :s=, :segments, "Dump of Wikipedia segments", required: true
  on :l=, :links, "Dump of Wikipedia links", required: true
  on :a=, :"article-id", "Id of article to display", as: Integer, required: true
end

begin
  options.parse
rescue => ex
  puts ex
  puts options
  exit
end

tokens = []
File.open(options[:segments]) do |input|
  input.each do |line|
    article_id,type,line_start,line_end,token_start,token_end,*token = line.chomp.split(",")
    token = token.join(",")
    article_id = article_id.to_i
    next if article_id < options[:"article-id"]
    break if article_id > options[:"article-id"]
    tokens << [line_start.to_i,line_end.to_i,token_start.to_i,token_end.to_i,token]
  end
end

links = []
File.open(options[:links]) do |input|
  input.each do |line|
    article_id,line_start,line_end,token_start,token_end,link,text = line.chomp.split("\t")
    article_id = article_id.to_i
    next if article_id < options[:"article-id"]
    break if article_id > options[:"article-id"]
    links << [line_start.to_i,line_end.to_i,token_start.to_i,token_end.to_i,link,text]
  end
end

result = ""
tokens.each do |tuple|
  begin
    line_start,line_end,token_start,token_end,token = tuple
    link_line_start,link_line_end,link_token_start,link_token_end,link,link_text = links.first
    if link_line_start == line_start && token_start >= link_token_start && token_end <= link_token_end
      result << token.hl(:yellow)
    else
      result << token
    end
    if link && (link_line_end < line_start || link_line_start == line_start && (link_token_end == token_end || link_token_end < token_start))
      result << ":" << link.hl(:green)
      links.shift
    end
  rescue => ex
    p tuple
    p links.first
    puts ex
    puts ex.backtrace
    raise
  end
end
puts result.gsub(/(\\n)+/,"\n")
