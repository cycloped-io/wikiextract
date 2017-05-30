#!/usr/bin/env ruby

require 'bundler/setup'
require 'csv'
require 'progress'
require 'slop'
require 'melisa'

options = Slop.new do
  banner "#{$PROGRAM_NAME} -i occurrences.index -o link_counts.csv -d candidates.tsv -t tokens.tsv\n" +
    "Count link occurrences and discover link candidates in Wikipedia text."

  on :t=, :tokens, "File with text tokens", required: true
  on :i=, :index, "Input file with Marisa index", required: true
  on :o=, :counts, "Output file with link counts", required: true
  on :c=, :candidates, "Output file with link candidates", required: true
  on :l=, :limit, "Limit for articles (last-1 article to process)", as: Integer
  on :x=, :offset, "Offset of articles (first article to process)", as: Integer, default: 0
  on :q, :quiet, "Don't print progress"
end

begin
  options.parse
rescue => ex
  puts ex
  puts options
  exit
end

def convert_tuple(tuple)
  document_id, token_index, space, token = *tuple
  token = token.chomp
  document_id = document_id.to_i
  [document_id, token_index, space, token]
end

def count_and_match_tokens(index, stack, input, output, counts)
  string = stack[0][3] + stack[1..-1].map{|_, _, s, t| s == "1" ? " " + t : t}.join("")
  string.force_encoding("ascii-8bit")
  token_id = index[string]
  if token_id
    first_tuple = stack[0]
    last_tuple = stack.last
    output.puts "%s\t%s\t%s\t%s" % [first_tuple[0], first_tuple[1], last_tuple[1], string]
    counts[string] += 1 if token_id
  end
  index.search(string).size > 0
end

counts = Hash.new(0)
index = Melisa::IntTrie.new
index.load(options[:index])
File.open(options[:candidates], "w") do |output|
  CSV.open(options[:tokens], col_sep: "\t", quote_char: "\x00") do |input|
    input.each do |tuple|
      begin
        stack = [convert_tuple(tuple)]
        recoreded_pos = input.pos
        while(count_and_match_tokens(index, stack, input, output, counts)) do
          stack << convert_tuple(input.shift)
        end
        input.pos = recoreded_pos
      rescue Interrupt
        break
      end
    end
    Progress.stop
  end
end

CSV.open(options[:counts],"w") do |output|
  Progress.start(counts.size) unless options[:quiet]
  counts.each do |tuple|
    Progress.step unless options[:quiet]
    output << tuple
  end
  Progress.stop unless options[:quiet]
end
