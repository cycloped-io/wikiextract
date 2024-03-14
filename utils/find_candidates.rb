#!/usr/bin/env ruby

require 'bundler/setup'
require 'csv'
require 'progress'
require 'slop'
require 'cyclopedio/wiki'

options = Slop.new do
  banner "#{$PROGRAM_NAME} -t tokens_text.csv -d database -o candidates.csv\n" +
    "Find candidate links in tokenized text.\n"

  on :d=, :database, "Rod database with Wikipedia data", required: true
  on :t=, :tokens, "File with text tokens", required: true
  on :o=, :output, "Output file with candidate links", required: true
  on :l=, :limit, "Limit for processing articles", as: Integer
  on :x=, :offset, "Offset of articles", as: Integer, default: 0
  on :q, :quiet, "Don't print progress"
  on :p=, :"link-probability", "Minimum probability of link to be processed", as: Float, default: 0.001
  on :s=, :"sense-probability", "Minimum probability of sense to be printed", as: Float, default: 0.001
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

limit = options[:limit] || Article.count+1
CSV.open(options[:tokens]) do |input|
  Progress.start(limit-options[:offset]) unless options[:quiet]
  CSV.open(options[:output],"w") do |output|
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
          # at least one letter is required in the first token of the link
          next unless token.value =~ /\p{L}/
          trie = token.trie
          current_index = index + 1
          next if current_index >= tokens.size
          while(trie) do
            if trie.link_probability >= options[:"link-probability"]
              trie.mentions.each do |mention|
                next if mention.probability < options[:"sense-probability"]
                output << [article_id,index,trie.rod_id,mention.rod_id]
                #output << [article_id,index,trie.link_name,trie.link_probability.round(5),mention.article.name,mention.probability.round(5)]
              end
            end
            trie = trie.fast_search(tokens[current_index])
            current_index += 1
            break if current_index >= tokens.size
          end
        end
      rescue Interrupt
	break
      end
    end
  end
  Progress.stop
end
Database.instance.close_database
