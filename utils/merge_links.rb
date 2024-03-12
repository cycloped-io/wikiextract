#!/usr/bin/env ruby

require 'bundler/setup'
require 'slop'
require 'csv'
require 'progress'

options = Slop.new do
  banner "#{$PROGRAM_NAME} -i counts.sorted.csv -o counts.merged.csv\n" +
    "Merge link counts"

  on :i=, :input, "File with sorted count", required: true
  on :o=, :output, "Output file with merged count", required: true
end

begin
  options.parse
rescue => ex
  puts ex
  puts options
  exit
end

counts = Hash.new(0)
Dir.glob(options[:input]).each do |file_name|
  CSV.open(file_name) do |input|
    input.with_progress(file_name) do |link, count|
      counts[link] += count.to_i
    end
  end
end

CSV.open(options[:output],"w") do |output|
  counts.sort_by{|k,v| k}.each do |link, count|
    output << [link, count]
  end
end