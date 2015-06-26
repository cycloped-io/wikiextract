#!/usr/bin/env ruby

require 'bundler/setup'
require 'slop'
require 'csv'
require 'progress'

options = Slop.new do
  banner "#{$PROGRAM_NAME} -i tokens_links.csv -o tokens_links.sorted.csv\n" +
    "Sort tokens in links (in memory!)"

  on :i=, :input, "File with tokens in links", required: true
  on :o=, :output, "Output file with sorted tokens in links", required: true
end

begin
  options.parse
rescue => ex
  puts ex
  puts options
  exit
end

mega_array = []
CSV.open(options[:input]) do |input|
  input.with_progress do |tokens,link|
    tokens = tokens.split("_").map(&:to_i)
    mega_array[tokens[0]] ||= []
    mega_array[tokens[0]] << [tokens,link]
  end
end

CSV.open(options[:output],"w") do |output|
  mega_array.with_progress do |array|
    next if array.nil?
    array.sort do |(tokens_l,link_l),(tokens_r,link_r)|
      if tokens_l.size > tokens_r.size
	value = tokens_l.zip(tokens_r).each do |token_l,token_r|
	  if (token_l || 0) < (token_r || 0)
	    break -1
	  elsif (token_l || 0) > (token_r || 0)
	    break 1
	  end
	end
      else
	value = tokens_r.zip(tokens_l).each do |token_r,token_l|
	  if (token_l || 0) < (token_r || 0)
	    break -1
	  elsif (token_l || 0) > (token_r || 0)
	    break 1
	  end
	end
      end
      if value.is_a?(Integer)
	value
      else
	0
      end
    end.each do |tokens,link|
      output << [tokens.join("_"),link]
    end
  end
end
