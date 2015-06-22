#!/usr/bin/env ruby

require 'bundler/setup'
require 'slop'
require 'csv'
require 'progress'

options = Slop.new do
  banner "#{$PROGRAM_NAME} -i tokens_links.sorted.csv -o tokens_links.merged.csv\n" +
    "Merge tokens in links and counts"

  on :i=, :input, "File with sorted tokens in links", required: true
  on :o=, :output, "Output file with merged tokens in links", required: true
end

begin
  options.parse
rescue => ex
  puts ex
  puts options
  exit
end

last_tokens = nil
links = []
CSV.open(options[:input]) do |input|
  CSV.open(options[:output],"w") do |output|
    input.with_progress do |tokens,link|
      if last_tokens  != tokens
	output << links.unshift(last_tokens) if last_tokens
	links.clear
      end
      links << link
      last_tokens = tokens
    end
    output << links.unshift(last_tokens)
  end
end
