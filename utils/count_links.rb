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
  on :l=, :length, "Number of articles to process (default: 10)", as: Integer, default: 10
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

class Context < Struct.new(:index, :string, :output, :counts, :first_token_index, :last_token_index, :document_id)
end

def convert_tuple(tuple)
  document_id, token_index, space, token = *tuple
  token = token.chomp
  token.force_encoding("ascii-8bit")
  document_id = document_id.to_i
  [document_id, token_index, space, token]
end

def count_and_match_tokens(context)
  token_id = context.index[context.string]
  if token_id
    context.output.puts "%s\t%s\t%s\t%s" % [context.document_id, context.first_token_index, context.last_token_index, context.string]
    context.counts[context.string] += 1
  end
  context.index.search(context.string).size > 0
end

counts = Hash.new(0)
index = Melisa::IntTrie.new
index.load(options[:index])
File.open(options[:candidates], "w") do |output|
  CSV.open(options[:tokens], col_sep: "\t", quote_char: "\x00") do |input|
    context = Context.new(index, nil, output, counts, nil, nil, nil)
    Progress.start(options[:length])
    input.each do |tuple|
      begin
        context.document_id, context.first_token_index, space, token = *convert_tuple(tuple)
        next if context.document_id < options[:offset]
        break if context.document_id >= options[:offset] + options[:length]
        recoreded_pos = input.pos
        context.last_token_index = context.first_token_index
        context.string = token.dup
        while(count_and_match_tokens(context)) do
          last_document_id, context.last_token_index, space, last_token = convert_tuple(input.shift)
          break if context.document_id != last_document_id
          context.string << " " if space == "1"
          context.string << last_token
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
