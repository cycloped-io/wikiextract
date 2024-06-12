#!/usr/bin/env ruby

require 'bundler/setup'
require 'csv'
require 'progress'
require 'slop'
require 'ahocorasick'
require 'set'
require_relative 'local_progress'
require 'cyclopedio/linker'


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
  on :i=, :index, "File with index of tokesn", required: true
  on :f=, :first, "First article ID to process", as: Integer, default: 0
  on :s=, :fsa, "FSA object", require: true
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

puts "Reading tokens index" unless options[:quiet]
token_index = {}
File.open(options[:index]) do |input|
  input.each do |line|
    wiki_id, offset = line.split("\t").map(&:to_i)
    token_index[wiki_id] = offset
  end
end

matcher = nil
File.open(options[:fsa], "rb") do |input|
  start_time = Process.clock_gettime(Process::CLOCK_MONOTONIC)
  matcher = Marshal.load(input.read())
  puts "Reading maps %.3f" % (Process.clock_gettime(Process::CLOCK_MONOTONIC) - start_time) unless options[:quiet]
  start_time = Process.clock_gettime(Process::CLOCK_MONOTONIC)
  matcher.read_names()
  puts "Building FSA %.3f" % (Process.clock_gettime(Process::CLOCK_MONOTONIC) - start_time) unless options[:quiet]
end

matcher.report unless options[:quiet]


counts = Hash.new(0)
last_wiki_id = nil
text = []
article_count = 0

progress = LocalProgress.new("Counting links", options[:last] - options[:first], quiet: options[:quiet], log: options[:log])

offset = 0

token_index.each_entry do |key, value|
  break if key > options[:first]
  offset = value
end


File.open(options[:tokens]) do |input|
  input.pos = offset
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
        matcher.match(text) do |matched_tokens, end_offset, names|
          names.each{|name| counts[name] += 1}
        end
        text = []
        article_count += 1
      end
      text << token
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
