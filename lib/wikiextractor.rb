require 'set'
require 'colors'

module Wikitext
  class Parser
    START_BLIND_TOKENS = Set.new([:pre_start, :img_start, :less, :table_start, :math_start])

    END_BLIND_TOKENS = Set.new([:pre_end, :img_end, :less, :table_end, :math_end, :greater])


    SKIP_TOKENS = Set.new([:strong,:strong_start,:strong_end,:separator,
                           :em,:em_start,:em_end,:tt,:tt_start,:tt_end,
                           :uri, :no_wiki_start, :strong_em, :pre,
                           :no_wiki_end,  :named_entity,
    ])

    CRLF_TOKENS = Set.new([:h1_start, :h1_end, :h2_start, :h2_end, :h3_start,
                           :h3_end, :h4_start, :h4_end, :h5_start, :h5_end,
                           :h6_start, :h6_end, :ul, :ol,])

    PRINT_TOKENS = Set.new([:space,:alnum,:default,:special_uri_chars,
                            :printable,:quot,:path, :amp])

    @@crlf_positions = Hash.new(0)

    def print(contents)
      @message ||= ""
      @message << contents
    end

    def puts(contents="")
      print(contents + "\n")
    end

    def flush
      STDOUT.puts @message.gsub(/\n\n+/,"\n\n")
      @message = ""
    end

    def crlf_stats
      @@crlf_positions
    end

    def parse(input)
      stack = [:default]
      link_stack = []
      self.tokenize(input).each.with_index do |token,index|
        unless true || token.token_type == :space
          puts "#{token.token_type.to_s} #{token.string_value}"
        end
        type = token.token_type
        case type
        when *START_BLIND_TOKENS.to_a
          if !START_BLIND_TOKENS.include?(stack.last) || stack.last == type
            stack << type
          end
        when *END_BLIND_TOKENS.to_a
          opening_type = stack.last
          if opening_type == :less
            if type == :greater
              stack.pop
            end
          elsif opening_type.to_s == type.to_s.sub(/_end$/,"_start")
            stack.pop
          end
        when :link_start
          unless START_BLIND_TOKENS.include?(stack.last)
            stack << type
          end
        when :link_end
          unless START_BLIND_TOKENS.include?(stack.last)
            opening_type = stack.pop
            unless stack.any?{|t| t == :link_start }
              if opening_type.to_s != type.to_s.sub(/_end$/,"_start")
                puts "Non-matching tokens #{opening_type} #{type}".hl(:red)
              else
                to_print = []
                link_stack.each do |token|
                  if token.token_type == :separator
                    to_print = []
                  elsif token.string_value == ":"
                    to_print = []
                    break
                  else
                    to_print << token.string_value
                  end
                end
                to_print.each{|v| print v.hl(:purple) }
                link_stack = []
              end
            end
          end
        when :ext_link_start
          unless START_BLIND_TOKENS.include?(stack.last)
            stack << type
          end
        when :ext_link_end
          unless START_BLIND_TOKENS.include?(stack.last)
            opening_type = stack.pop
            if opening_type.to_s != type.to_s.sub(/_end$/,"_start")
              puts "Non-matching tokens #{opening_type} #{type}".hl(:red)
              stack.push opening_type
            else
              to_print = []
              link_stack.each do |token|
                to_print << token.string_value unless token.token_type == :uri
              end
              to_print.each{|v| print v.hl(:yellow) }
              link_stack = []
            end
          end
        when :end_of_file
          if stack.last != :default
            puts "There are unmatched opening tokens #{stack.join(", ")}".hl(:red)
          end
        else
          if START_BLIND_TOKENS.include?(stack.last)
            # skip
          elsif stack.last == :link_start || stack.last == :ext_link_start
            if token.token_type == :crlf
              @@crlf_positions[stack.last] += 1
              puts "Unclosed link detected".hl(:red)
              link_stack.each{|v| print v.string_value }
              stack.pop
            else
              link_stack << token
            end
          elsif CRLF_TOKENS.include?(token.token_type)
            print "\n"
          elsif SKIP_TOKENS.include?(token.token_type)
            #skip
          else
            if PRINT_TOKENS.include?(token.token_type)
              print token.string_value
            elsif token.token_type == :crlf
              print "\n"
            else
              print " " + token.token_type.to_s.hl(:blue) +
                " #{token.string_value}".hl(:green)
            end
            #print token.string_value
          end
        end
      end
      flush
    end
  end
end
