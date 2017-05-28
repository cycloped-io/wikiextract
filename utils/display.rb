#!/usr/bin/env ruby

require 'bundler/setup'
require 'slop'
require 'colors'
require 'csv'
require 'progress'

options = Slop.new do
  banner "#{$PROGRAM_NAME} -t tokens.csv -l links.csv [-a article_id|-r 0:10]\n" +
    "Display dumped Wikipedia article"

  on :t=, :tokens, "Dump of Wikipedia tokens", required: true
  on :l=, :links, "Dump of Wikipedia links", required: true
  on :a=, :"article-id", "Id of article to display", as: Integer
  on :r=, :range, "Range of article ids", as: Range, default: (0...1)
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
  lower = options[:range].first
  upper = options[:range].last
end

class SimpleLink < Struct.new(:article_id,:start,:end,:link,:text)
  def includes?(token)
    self.article_id == token.article_id && self.start <= token.start && self.end >= token.end
  end

  def last?(token)
    self.article_id == token.article_id && self.end == token.end
  end


  def before?(token)
    result = self.article_id < token.article_id ||
      (self.article_id == token.article_id && self.end < token.start)
    p [self.link, token.token, self.end, token.start] if result
    result
  end
end

class SimpleToken < Struct.new(:article_id,:space,:start,:end,:token)
  def initialize(*args)
    super
    self.token = " " + self.token if self.space
  end
end

class OutputService
  def initialize(output)
    @output = output
    @in_link = false
    @result = ""
  end

  def push_token(token)
    @result << token.token.to_s
  end

  def push_link_source(token)
    if @output
      unless @in_link
        @result << "<link>"
        @in_link = true
      end
      @result << token.token.to_s
    else
      @result << token.token.hl(:yellow)
    end
  end

  def push_link_target(link)
    if @output
      @result << "</link target=\"" << link.link << "\">"
      @in_link = false
    else
      @result << ":" << link.link.hl(:green)
    end
  end

  def push_link_error(link)
    unless @output
      @result << ":" << link.link.hl(:red)
    end
    @in_link = false
  end

  def print
    if @output
      @output.puts @result
    else
      puts @result
    end
  end
end

tokens = []
tokens_file = File.open(options[:tokens])
links_file = File.open(options[:links])
output = File.open(options[:output],"w") if options[:output]
Progress.start(upper-lower)
lower.upto(upper) do |current_id|
  tokens = []
  links = []
  # read segmens
  last_position = tokens_file.pos
  tokens_file.each do |line|
    article_id,token_start,space,*token = line.chomp.split("\t")
    article_id = article_id.to_i
    next if article_id < current_id
    Progress.set(article_id-lower)
    break if article_id > current_id
    last_position = tokens_file.pos
    token = token.join("\t")
    space = (space == "1")
    tokens << SimpleToken.new(article_id,space,token_start.to_i,token_start.to_i,token)
  end
  tokens_file.pos = last_position

  # read links
  last_position = links_file.pos
  links_file.each do |line|
    article_id,token_start,token_end,link,text = line.chomp.split("\t")
    article_id = article_id.to_i
    next if article_id < current_id
    Progress.set(article_id-lower)
    break if article_id > current_id
    last_position = links_file.pos
    links << SimpleLink.new(article_id,token_start.to_i,token_end.to_i,link,text)
  end
  links_file.pos = last_position

  # print article
  output_service = OutputService.new(output)
  tokens.each do |token|
    begin
      link = links.first
      if link && link.includes?(token)
        output_service.push_link_source(token)
        if link.last?(token)
          output_service.push_link_target(link)
          links.shift
          link = links.first
        end
      else
        output_service.push_token(token)
      end
      while(link) do
        if link.before?(token)
          output_service.push_link_error(link)
          links.shift
          link = links.first
        else
          break
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
  output_service.print
end
Progress.stop
tokens_file.close
links_file.close
output.close if output
