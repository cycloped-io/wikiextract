#!/usr/bin/env ruby
# encoding: utf-8

require 'bundler/setup'
require_relative 'local_progress'
require 'cyclopedio/linker'
require 'slop'

# Create a Finite State Automaton matching the names of links in the text.


opts = Slop.parse do
  on :l=, :links, 'The path to input file with unique link names', required: true
  on :f=, :fsa, 'The path to output Ruby object with the FSA', required: true
  on :g=, :log, "Log file to report progress"
  on :s, :silent, 'Do not show any progress information', default: false, type: :boolean
  on :t, :test, 'Do not create the FSA, but load it and test if it works', default: false, type: :boolean
  on :h, :help, 'Print help' do
    puts o
    exit
  end
end


if opts[:test]
  matcher = nil
  File.open(opts[:fsa], "rb") do |input|
    start_time = Process.clock_gettime(Process::CLOCK_MONOTONIC)
    matcher = Marshal.load(input.read())
    puts "%.3f" % (Process.clock_gettime(Process::CLOCK_MONOTONIC) - start_time)
    start_time = Process.clock_gettime(Process::CLOCK_MONOTONIC)
    matcher.read_names()
    puts "%.3f" % (Process.clock_gettime(Process::CLOCK_MONOTONIC) - start_time)
  end
  p matcher.match(%{Warszawa jest stolicą Polski})
else
  progress = LocalProgress.new("Reading links", `wc -l #{opts[:links]}`.to_i / 100, quiet: opts[:silent], log: opts[:log])
  class FileIterator 
    def initialize(path, progress)
      @file = File.open(path)
      @progress = progress
    end

    def each
      @file.each.with_index do |line, index|
        @progress.step(1) if index % 100 == 0
        yield line.chomp.strip
      end
    end

    def close
      @file.close
    end
  end

  begin
    iterator = FileIterator.new(opts[:links], progress)
    matcher = Cyclopedio::Linker::Matcher.new(iterator)
    matcher.read_names()
    progress.stop
    matcher.report unless opts[:silent]

    File.open(opts[:fsa], "wb") do |output|
      matcher.prepare_for_serialization()
      output.print(Marshal.dump(matcher))
    end
  rescue Exception => ex
    puts ex
    puts ex.backtrace
    iterator.close unless iterator.nil?
  end
end