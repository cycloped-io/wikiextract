#!/usr/bin/env ruby

require 'bundler/setup'
require 'csv'
require 'progress'
require 'slop'
require_relative 'local_progress'

options = Slop.new do
  banner "#{$PROGRAM_NAME} -t tokens.tsv -i index.tsv\n" +
    "Create index for tokens.tsv to be used by the counter to speed up file reading."

  on :t=, :tokens, "File with text tokens", required: true
  on :i=, :index, "Output file with tokens index", required: true
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

BATCH_SIZE = 1000

progress = LocalProgress.new("Creating the index", `wc -l #{options[:tokens]}`.to_i / BATCH_SIZE, quiet: options[:quiet], log: options[:log])
File.open(options[:index], "w") do |output|
  File.open(options[:tokens]) do |input|
    last_wiki_id = nil
    last_pos = 0
    input.each do |token|
      progress.step(1) if input.lineno % BATCH_SIZE == 0
      wiki_id, token_offset, space_before, token = token.split("\t")
      wiki_id = wiki_id.to_i
      if last_wiki_id != wiki_id
        output.write("#{wiki_id}\t#{last_pos}\n")
      end
      last_wiki_id = wiki_id
      last_pos = input.pos
    end
  end
end
progress.stop()
