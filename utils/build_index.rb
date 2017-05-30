#!/usr/bin/env ruby

require 'bundler/setup'
require 'slop'
require 'csv'
require 'progress'
require 'melisa'


options = Slop.new do
  banner "#{$PROGRAM_NAME} -i occurrences.csv -f marisa.index [-x offset] [-l limit]\n" +
    "Build Marisa index of link occurrences"

  on :i=, :occurrences, "Dump of Wikipedia occurrences (txt file)", required: true
  on :o=, :index, "Output file with Marisa index", required: true
  on :x=, :offset, "Offset of articles to convert", as: Integer, default: 0
  on :l=, :limit, "Number of articles to convert", as: Integer, default: -1
end

begin
  options.parse
rescue => ex
  puts ex
  puts options
  exit
end

index = Melisa::IntTrie.new

line_index = 1
File.open(options[:occurrences]) do |input|
  input.with_progress do |line|
    index.set(line.chomp.force_encoding("ascii-8bit"), line_index + 1)
    line_index += 1
  end
end
index.save(options[:index])
