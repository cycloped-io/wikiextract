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

  desc 'Convert links to token, source and target ROD ids'
  task :convert do
    puts "Convert links to token, source and target ID"
    data,db = get_params
    Cyclopedio::Wiki::Database.instance.open_database(db)
    split_jobs(Cyclopedio::Wiki::Article.count) do |job_index,first_index,last_index|
      quiet = (job_index == 0 ? "" : "-q")
      puts `./utils/convert_links.rb -i #{data}/links.tsv -x #{first_index} -l #{last_index} -o #{data}/tokens_links_#{first_index}_#{last_index}.csv -c #{data}/tokens_counts_#{first_index}_#{last_index}.csv -w #{data}/tokens_text_#{first_index}_#{last_index}.csv -t #{data}/tokens.tsv -d #{db} #{quiet}`
    end
    `cat #{data}/tokens_links_* | sort -n > #{data}/tokens_links.sorted.csv`
    `cat #{data}/tokens_counts_* | sort -n > #{data}/tokens_counts.sorted.csv`
    `cat #{data}/tokens_text_* | sort -n > #{data}/tokens_text.sorted.csv`
    #`rm #{data}/tokens_links_* #{data}/tokens_counts_* #{data}/tokens_text_*`
    `./utils/merge_links.rb -i #{data}/tokens_links.sorted.csv -o #{data}/tokens_links.merged.csv`
    `./utils/merge_links.rb -i #{data}/tokens_counts.sorted.csv -o #{data}/tokens_counts.merged.csv`
    #`rm #{data}/tokens_links.sorted.csv #{data}/tokens_counts.sorted.csv #{data}/tokens_text.sorted.csv`
    Cyclopedio::Wiki::Database.instance.close_database()
  end
end

namespace :links do
  desc "Count all links occurrences"
  task :count do
    puts "Count all link occurrences"
    data,db = get_params
    #`rm #{data}/link_counts_*.csv`
    split_jobs(`tail -1 #{data}/tokens.tsv | cut -f 1`.to_i) do |job_index,offset,length|
      puts `./utils/count_links.rb -t #{data}/tokens.tsv -l #{data}/occurrences.txt -o #{data}/counts_#{offset}.csv -f #{offset} -e #{offset + length} -g log/count.log -q`
    end
    `cat #{data}/link_counts_*.csv > #{data}/link_counts.all.csv`
    `./utils/sort_links.rb -i #{data}/link_counts.all.csv -o #{data}/link_counts.sorted.csv`
    `./utils/merge_links.rb -i #{data}/link_counts.sorted.csv -o #{data}/link_counts.merged.csv`
    `rm #{data}/link_counts_* #{data}/link_counts.all.csv #{data}/link_counts.sorted.csv`
  end

  desc "Find link candidates"
  task :candidates do
    puts "Find link candidates"
    data,db = get_params
    `rm #{data}/link_candidates_*.csv`
    split_jobs(Cyclopedio::Wiki::Article.count) do |job_index,first_index,last_index|
      quiet = (job_index == 0 ? "" : "-q")
      puts `./utils/find_candidates.rb -d #{db} -t #{data}/tokens_text.sorted.csv -o #{data}/link_candidates_#{first_index}_#{last_index}.csv -x #{first_index} -l #{last_index} #{quiet} -p 0.01 -s 0.01`
    end
    `cat #{data}/link_candidates_*.csv > #{data}/link_candidates.cat.csv`
    #`rm #{data}/link_candidates_* `
  end
end
