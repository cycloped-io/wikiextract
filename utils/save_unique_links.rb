#!/usr/bin/env ruby

require 'bundler/setup'
require 'csv'
require 'progress'
require 'slop'
require 'set'
require_relative 'local_progress'
require_relative 'link_map'


options = Slop.new do
  banner "#{$PROGRAM_NAME} -l link.tsv -u unique.obj\n" +
    "Comput unique links and marshall them"

  on :l=, :links, "File with unique links", required: true
  on :u=, :unique, "File with marshalled structure with unique names", required: true
  on :t, :test, "Test if the de-marshalled file is ok"
end

begin
  options.parse
rescue => ex
  puts ex
  puts options
  exit
end


if options[:test] 
  map = nil
  File.open(options[:unique], "rb") do |input|
    map = Marshal.load(input.read())
  end
  puts "Names count: #{map.names.size}"
else
  map = LinkMap.new(options[:links])
  map.read_links()
  map.prepare_for_serialization()
  File.open(options[:unique], "wb") do |output|
    output.write(Marshal.dump(map))
  end
end