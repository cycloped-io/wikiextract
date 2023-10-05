FROM ruby:2.7.2-slim
RUN bundle config --global frozen 1
RUN mkdir /wikiextract
WORKDIR /wikiextract
COPY Gemfile /wikiextract
COPY Gemfile.lock /wikiextract
#COPY cyclopedio-wikiextract.gemspec /wikiextract
RUN bundle
COPY . /wikiextract
RUN bundle exec rake make