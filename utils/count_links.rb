#!/usr/bin/env ruby

require 'bundler/setup'
require 'csv'
require 'progress'
require 'slop'
require 'ahocorasick'
require 'set'
require_relative 'local_progress'


def measure_time(print: true)
  starting = Process.clock_gettime(Process::CLOCK_MONOTONIC)
  yield
  ending = Process.clock_gettime(Process::CLOCK_MONOTONIC)
  elapsed = ending - starting
  puts "%.3f" % elapsed unless print
end

options = Slop.new do
  banner "#{$PROGRAM_NAME} -t tokens.tsv -l link.tsv\n" +
    "Count link occurrences and discover link candidates in Wikipedia text."

  on :t=, :tokens, "File with text tokens", required: true
  on :l=, :links, "File with unique links", required: true
  on :o=, :counts, "Output file with link counts", required: true
  on :f=, :first, "First article ID to process", as: Integer, default: 0
  on :e=, :last, "Last article ID to process", as: Integer, default: 100
  on :g=, :log, "Log file to report progress"
  on :q, :quiet, "Don't print progress"
end

begin
  options.parse
rescue => ex
  puts ex
  puts options
  exit
end

puts "Counting links: first article ID #{options[:first]}, last article ID #{options[:last]}"

progress = LocalProgress.new("Processing unique links", `wc -l #{options[:links]}`.to_i, quiet: options[:quiet], log: options[:log])
names = []
unique_tokens = Set.new
names_map = Hash.new{|h,e| h[e] = Set.new }
measure_time do
  File.open(options[:links]) do |input|
    input.each do |line|
      progress.step(1)
      name = line.chomp
      tokens = name.split(/\b/).reject{|e| e =~ /\s/ }
      next if tokens.empty?
      names_map[tokens] << name
      next if names_map[tokens].size > 1
      tokens.each{|t| unique_tokens << t}
      names << tokens
    end
  end
end
progress.stop
unless options[:quiet]
  puts "Unique names #{names.size}"
  puts "Unique tokens #{unique_tokens.size}"
  puts "First 10 names #{names[..10].join(" -- ")}"
  puts "Name map: \n" + names_map.to_a[..10].map{|k,v| "#{k}:#{v}" }.join("\n")
end

token_map = Hash.new(0)
token_map_inverted = Hash.new("")
unique_tokens.to_a.each.with_index do |token, index|
  token_map[token] = index + 1
  token_map_inverted[index + 1] = token
end

converted_names = []
names.each do |name|
  converted_names << name.map{|e| token_map[e] }
end
reconstructed = converted_names[..10].map{|ids| ids.map{|id| token_map_inverted[id] }}.join(" -- ")
puts "First 10 names reconstructed: #{reconstructed}" unless options[:quiet]

converted_names_map = {}
names_map.each do |tokens, names|
  ids = tokens.map{|t| token_map[t]}
  converted_names_map[ids] = names
end
reconstructed = converted_names_map.to_a[..10].map{|ids,names| ids.map{|id| token_map_inverted[id] }.join(" ") + ":" + names.to_s}.join(" -- ")
puts "First 10 names map reconstructed: #{reconstructed}" unless options[:quiet]

trie = AhoC::Trie.new
measure_time do 
  converted_names.each do |name| 
    trie.add(name)
  end
  trie.build()
end


counts = Hash.new(0)
last_wiki_id = nil
text = []
article_count = 0

progress = LocalProgress.new("Counting links", options[:last] - options[:first], quiet: options[:quiet], log: options[:log])

File.open(options[:tokens]) do |input|
  input.each do |token|
    begin
      wiki_id, token_offset, space_before, token = token.split("\t")
      wiki_id = wiki_id.to_i
      next if wiki_id < options[:first]
      break if wiki_id > options[:last]

      token_offset = token_offset.to_i
      space_before = (space_before == "1")
      token = token.chomp

      last_wiki_id = wiki_id if(last_wiki_id.nil?)
      if(wiki_id != last_wiki_id)
        progress.step(wiki_id - last_wiki_id)
        trie.lookup(text).each do |match|
          #puts(match.map{|id| token_map_inverted[id] }.join(" -- "))
          converted_names_map[match].each{|name| counts[name] += 1}
        end
        text = []
        article_count += 1
      end
      token_id = token_map[token]
      text << token_id if token_id > 0
      last_wiki_id = wiki_id
    rescue Interrupt
      break
    end
  end 
end
progress.stop

CSV.open(options[:counts], "w") do |csv_output|
  counts.sort_by{|k,v| k}.each do |key, value|
    #puts "%-20s%i" % [key,value]
    csv_output << [key, value]
  end
end