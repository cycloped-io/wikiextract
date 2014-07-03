#!/usr/bin/env ruby

require 'bundler/setup'
require 'slop'
require 'colors'
require 'csv'
require 'progress'

options = Slop.new do
  banner "#{$PROGRAM_NAME} -s segments.csv -l links.csv [-a article_id|-r 0:10]\n" +
    "Display dumped Wikipedia article"

  on :s=, :segments, "Dump of Wikipedia segments", required: true
  on :l=, :links, "Dump of Wikipedia links", required: true
  on :a=, :"article-id", "Id of article to display", as: Integer
  on :r=, :range, "Range of article ids"
  on :o=, :output, "Output file with text and marked links"
end

begin
  options.parse
rescue => ex
  puts ex
  puts options
  exit
end

if options[:"article-id"]
  lower = upper = options[:"article-id"]
else
  _,lower,upper = options[:range].match(/(\d+)-(\d+)/).to_a.map(&:to_i)
end

class Link < Struct.new(:article_id,:line_start,:line_end,:start,:end,:link,:text)
  def includes?(token)
    self.article_id == token.article_id && self.line_start <= token.line_start &&
      self.line_end >= token.line_end && self.start <= token.start &&
      self.end >= token.end
  end

  def follows?(token)
    self.article_id == token.article_id &&
      self.line_end == token.line_end &&
      self.end == token.end
  end


  def before?(token)
    self.article_id < token.article_id ||
      (self.article_id == token.article_id &&
       (self.line_end < token.line_start ||
        (self.line_end == token.line_start && self.end < token.start)))
  end
end

class Token < Struct.new(:article_id,:type,:line_start,:line_end,:start,:end,:token)
end

tokens = []
segments_file = File.open(options[:segments])
links_file = File.open(options[:links])
output = File.open(options[:output],"w") if options[:output]
Progress.start(upper-lower)
lower.upto(upper) do |current_id|
  tokens = []
  links = []
  # read segmens
  last_position = segments_file.pos
  segments_file.each do |line|
    article_id,type,line_start,line_end,token_start,token_end,*token = line.chomp.split(",")
    article_id = article_id.to_i
    next if article_id < current_id
    Progress.set(article_id-lower)
    break if article_id > current_id
    last_position = segments_file.pos
    token = token.join(",")
    tokens << Token.new(article_id,type,line_start.to_i,line_end.to_i,token_start.to_i,token_end.to_i,token)
  end
  segments_file.pos = last_position

  # read links
  last_position = links_file.pos
  links_file.each do |line|
    article_id,line_start,line_end,token_start,token_end,link,text = line.chomp.split("\t")
    article_id = article_id.to_i
    next if article_id < current_id
    Progress.set(article_id-lower)
    break if article_id > current_id
    last_position = links_file.pos
    # This is correct - but we have invalid data, so we assume that
    # links are always in the same line.
    #links << Link.new(article_id,line_start.to_i,line_end.to_i,token_start.to_i,token_end.to_i,link,text)
    links << Link.new(article_id,line_end.to_i,line_end.to_i,token_start.to_i,token_end.to_i,link,text)
  end
  links_file.pos = last_position

  # print article
  result = ""
  in_link = false
  tokens.each do |token|
    begin
      link = links.first
      if link && link.includes?(token)
        result << token.token.hl(:yellow) unless output
        if output
          unless in_link
            result << "<link>"
            in_link = true
          end
          result << token.token.to_s
        end
      else
        result << token.token.to_s
      end
      if link && link.follows?(token)
        result << ":" << link.link.hl(:green) unless output
        if output
          result << "</link target=\"" << link.link << "\">"
          in_link = false
        end
        links.shift
        link = links.first
      end
      while(link) do
        if link.before?(token)
          result << ":" << link.hl(:red) unless output
          links.shift
          link = links.first
          in_link = false
        else
          link = nil
        end
      end
    rescue => ex
      puts token
      puts link
      puts ex
      puts ex.backtrace
      raise
    end
  end
  puts result.gsub(/(\\n)+/,"\n") unless output
  output.puts result.gsub(/(\\n)+/,"\n") if output
end
Progress.stop
segments_file.close
links_file.close
output.close if output
