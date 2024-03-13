# Copyright 2007-2011 Wincent Colaiuta. All rights reserved.
#
# Redistribution and use in source and binary forms, with or without
# modification, are permitted provided that the following conditions are met:
#
# 1. Redistributions of source code must retain the above copyright notice,
#    this list of conditions and the following disclaimer.
# 2. Redistributions in binary form must reproduce the above copyright notice,
#    this list of conditions and the following disclaimer in the documentation
#    and/or other materials provided with the distribution.
#
# THIS SOFTWARE IS PROVIDED BY THE COPYRIGHT HOLDERS AND CONTRIBUTORS "AS IS"
# AND ANY EXPRESS OR IMPLIED WARRANTIES, INCLUDING, BUT NOT LIMITED TO, THE
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS FOR A PARTICULAR PURPOSE
# ARE DISCLAIMED. IN NO EVENT SHALL THE COPYRIGHT HOLDERS OR CONTRIBUTORS BE
# LIABLE FOR ANY DIRECT, INDIRECT, INCIDENTAL, SPECIAL, EXEMPLARY, OR
# CONSEQUENTIAL DAMAGES (INCLUDING, BUT NOT LIMITED TO, PROCUREMENT OF
# SUBSTITUTE GOODS OR SERVICES; LOSS OF USE, DATA, OR PROFITS; OR BUSINESS
# INTERRUPTION) HOWEVER CAUSED AND ON ANY THEORY OF LIABILITY, WHETHER IN
# CONTRACT, STRICT LIABILITY, OR TORT (INCLUDING NEGLIGENCE OR OTHERWISE)
# ARISING IN ANY WAY OUT OF THE USE OF THIS SOFTWARE, EVEN IF ADVISED OF THE
# POSSIBILITY OF SUCH DAMAGE.

require 'rake'
require 'rake/clean'
require 'rubygems'
require 'cyclopedio/wiki'

$LOAD_PATH.unshift(File.expand_path(File.join(File.dirname(__FILE__), 'lib')))
#require 'wikitext/version'

CLEAN.include   Rake::FileList['**/*.so', '**/*.bundle', '**/*.o', '**/mkmf.log', '**/Makefile']
CLOBBER.include Rake::FileList['ext/wikitext_ragel.c']


def get_params
  data = ENV['WIKI_DATA']
  db = ENV['WIKI_DB']
  if data.nil?
    puts "WIKI_DATA has to be set"
    exit
  end
  if db.nil?
    puts "WIKI_DB has to be set"
    exit
  end
  [data,db]
end

def split_jobs(count)
  require 'bundler/setup'
  jobs = (ENV['WIKI_JOBS'] || 1).to_i
  partial_size = count / jobs
  threads = jobs.times.map do |job_index|
    first_index = job_index * partial_size
    Thread.new do
      puts " *** #{job_index} started *** "
      Thread.pass
      yield(job_index,first_index,partial_size)
      puts " *** #{job_index} finished *** "
    end
  end
  threads.each(&:run)
  threads.each(&:join)
end

task :default => :all

desc 'Build all and run all specs'
task :all => [:make] #, :spec]

extension_makefile  = 'ext/Makefile'
ragel               = 'ext/wikitext_ragel.c'
built_extension     = "ext/wikitext.#{RbConfig::CONFIG['DLEXT']}" # wikitext.bundle (Darwin), wikitext.so (Linux)
extension_files     = FileList[
  'ext/Makefile',
  'ext/parser.c',
  'ext/parser.h',
  'ext/ruby_compat.h',
  'ext/token.c',
  'ext/token.h',
  'ext/wikitext.h',
  'ext/wikitext_ragel.c',
  'ext/wikitext_ragel.h'
]

desc 'Build C extension'
task :make => [ragel, extension_makefile, built_extension]

file ragel => ['ext/wikitext_ragel.rl'] do
  Dir.chdir('ext') do
    # pass the -s switch here because otherwise Ragel is totally silent
    # I like to have visual confirmation that it's actually run
    sh 'ragel -G2 -s wikitext_ragel.rl'
  end
end

file extension_makefile => ['ext/extconf.rb', 'ext/depend', ragel] do
  Dir.chdir('ext') do
    ruby 'extconf.rb'
  end
end

file built_extension => extension_files do
  Dir.chdir('ext') do
    sh 'make && touch .built'
  end
end

desc 'Run specs'
task :spec => :make do
  sh 'rspec spec'
end

desc 'Build gem ("gem build")'
task :build => :make do
  system 'gem build wikitext.gemspec'
end

desc 'Push gem to Gemcutter ("gem push")'
task :push => :build do
  system "gem push wikitext-#{Wikitext::VERSION}.gem"
end

namespace :tokens do
  desc 'Extract tokens and links from wikipedia dump'
  task :extract do
    puts "Extracting links and tokens from dump."
    data,db = get_params
    puts `./utils/parse.rb -w #{data}/pages-articles.xml -o #{data}/offsets.csv -t #{data}/tokens.tsv -l #{data}/links.tsv`
  end

  desc 'Find uniq token names'
  task :uniq do
    puts "Finidng unique token names. The output is stored in 'occurrences' directory."
    data,db = get_params
    puts `./utils/unique_segments.sh #{data}/links.tsv #{data}/occurrences`
  end
end

namespace :links do
  desc "Count all links occurrences"
  task :count do
    puts "Count all link occurrences #{Time.now}"
    data,db = get_params
    split_jobs(`tail -1 #{data}/tokens.tsv | cut -f 1`.to_i) do |job_index,offset,length|
      puts `./utils/count_links.rb -t #{data}/tokens.tsv -l #{data}/occurrences.txt -o #{data}/counts_#{offset}.csv -f #{offset} -e #{offset + length} -g log/count.log -q`
    end
    puts `./utils/merge_links.rb -i '#{data}/counts_*.csv' -o #{data}/counts.merged.csv`
    #`rm #{data}/counts_* #{data}/counts.all.csv #{data}/counts.sorted.csv`
  end

  desc "Convert links to occurrences"
  task :convert do
    puts "Convert links to occurrences #{Time.now}"
    data,db = get_params
    split_jobs(`tail -1 #{data}/tokens.tsv | cut -f 1`.to_i) do |job_index,offset,length|
      puts `./utils/convert_links.rb -t #{data}/tokens.tsv -l #{data}/occurrences.txt -o #{data}/counts_#{offset}.csv -f #{offset} -e #{offset + length} -g log/count.log -q`
    end
    #puts `./utils/merge_links.rb -i '#{data}/counts_*.csv' -o #{data}/counts.merged.csv`
    #`rm #{data}/counts_* #{data}/counts.all.csv #{data}/counts.sorted.csv`
  end
end
