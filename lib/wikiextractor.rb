require 'set'
require 'colors'

module Wikitext
  class Parser
    START_NOWIKI_TOKENS = Set.new([:pre_start, :tag_start, :math_start])

    END_NOWIKI_TOKENS = Set.new([:pre_end, :tag_end, :math_end])

    START_BLIND_TOKENS = Set.new([:img_start, :table_start, :special_link_start])

    END_BLIND_TOKENS = Set.new([:img_end, :table_end])


    SKIP_TOKENS = Set.new([:strong,:strong_start,:strong_end,:separator,
                           :em,:em_start,:em_end,:tt,:tt_start,:tt_end,
                           :uri, :no_wiki_start, :strong_em, :pre,
                           :no_wiki_end,  :named_entity, :blockquote_start,
                           :blockquote_end
    ])

    CRLF_TOKENS = Set.new([:h1_start, :h1_end, :h2_start, :h2_end, :h3_start,
                           :h3_end, :h4_start, :h4_end, :h5_start, :h5_end,
                           :h6_start, :h6_end, :ul, :ol, :sl, :cl])

    PRINT_TOKENS = Set.new([:space,:alnum,:default,:special_uri_chars,
                            :printable,:quot,:path, :amp, :left_curly, :right_curly])

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
      @stack = []
      @states = [:default]
      @link_stack = []
      self.tokenize(input).each.with_index do |token,index|
        unless true || token.token_type == :space
          str = "#{token.token_type.to_s} #{token.string_value}" +
            " [#{@states.join(",")}] [#{@stack.join(",")}]"
          str = str.hl(:green) if token.token_type == :crlf
          puts str
        end
        type = token.token_type
        case @states.last
        when :nowiki
          case type
          when *END_NOWIKI_TOKENS.to_a
            opening_type = @stack.last
            if opening_type.to_s == type.to_s.sub(/_end$/,"_start")
              @stack.pop
              @states.pop
            end
          else
            # skip
          end
        when :blind
          case type
          when *START_NOWIKI_TOKENS.to_a
            @stack.push type
            @states.push :nowiki
          when *END_NOWIKI_TOKENS.to_a
            puts "Closing token without opening token #{token.token_type} #{@states.last}".hl(:red)
          when *START_BLIND_TOKENS.to_a
            push_type_action(token)
            @states.push :blind
          when *END_BLIND_TOKENS.to_a
            opening_type = @stack.last
            if opening_type.to_s == type.to_s.sub(/_end$/,"_start")
              @stack.pop
              @states.pop
            else
              puts "Non-matching tokens #{opening_type} #{type} #{@states.last}".hl(:red)
            end
          when :link_start, :ext_link_start
            push_type_action(token)
            @states.push :blind_link
          when :link_end
            if @stack.last == :special_link_start
              @stack.pop
              @states.pop
            else
              puts "Non-matching tokens #{@stack.last} #{type} #{@states.last}".hl(:red)
            end
          when :ext_link_end
            puts "Non-matching tokens #{opening_type} #{type} #{@states.last}".hl(:red)
          when :end_of_file
            end_of_file_action
          end
        when :blind_link
          case type
          when *START_NOWIKI_TOKENS.to_a
            @stack.push type
            @states.push :nowiki
          when *END_NOWIKI_TOKENS.to_a
            puts "Closing token without opening token #{token.token_type} #{@states.last}".hl(:red)
          when *START_BLIND_TOKENS.to_a
            push_type_action(token)
            @states.push :blind
          when *END_BLIND_TOKENS.to_a
            puts "Non-matching tokens #{@stack.last} #{type} #{@states.last}".hl(:red)
          when :link_start, :ext_link_start
            push_type_action(token)
            @states.push :blind_link
          when :link_end, :ext_link_end
            @stack.pop
            @states.pop
          when :end_of_file
            end_of_file_action
          end
        when :inner_link
          case type
          when *START_NOWIKI_TOKENS.to_a
            @stack.push type
            @states.push :nowiki
          when *END_NOWIKI_TOKENS.to_a
            puts "Closing token without opening token #{token.token_type} #{@states.last}".hl(:red)
          when *START_BLIND_TOKENS.to_a
            push_type_action(token)
            @states.push :blind
          when *END_BLIND_TOKENS.to_a
            puts "Non-matching tokens #{@stack.last} #{type} #{@states.last}".hl(:red)
          when :link_start, :ext_link_start
            push_type_action(token)
            @states.push :inner_link
          when :link_end, :ext_link_end
            @stack.pop
            @states.pop
          when :end_of_file
            end_of_file_action
          else
            if token.token_type == :crlf
              @@crlf_positions[@stack.last] += 1
              puts "Unclosed link detected".hl(:red)
              @link_stack.each{|v| print v.string_value }
              @stack.pop
              @states.pop
            else
              push_token_action(token)
            end
          end
        when :link
          case type
          when *START_NOWIKI_TOKENS.to_a
            @stack.push type
            @states.push :nowiki
          when *END_NOWIKI_TOKENS.to_a
            puts "Closing token without opening token #{token.token_type} #{@states.last}".hl(:red)
          when *START_BLIND_TOKENS.to_a
            push_type_action(token)
            @states.push :blind
          when *END_BLIND_TOKENS.to_a
            puts "Non-matching tokens #{@stack.last} #{type} #{@states.last}".hl(:red)
          when :link_start, :ext_link_start
            push_type_action(token)
            @states.push :inner_link
          when :link_end
            close_link_action(token)
            @states.pop
          when :ext_link_end
            close_ext_link_action(token)
            @states.pop
          when :end_of_file
            end_of_file_action
          else
            if token.token_type == :crlf
              @@crlf_positions[@stack.last] += 1
              puts "Unclosed link detected".hl(:red)
              @link_stack.each{|v| print v.string_value }
              @stack.pop
              @states.pop
            else
              push_token_action(token)
            end
          end
        when :default
          case type
          when *START_NOWIKI_TOKENS.to_a
            @stack.push type
            @states.push :nowiki
          when *END_NOWIKI_TOKENS.to_a
            if type == :tag_end
              print token.string_value
            else
              puts "Closing token without opening token #{token.token_type} #{@states.last}".hl(:red)
            end
          when *START_BLIND_TOKENS.to_a
            push_type_action(token)
            @states.push :blind
          when *END_BLIND_TOKENS.to_a
            puts "Closing token without opening token #{token.token_type} #{@states.last}".hl(:red)
          when :link_start
            push_type_action(token)
            @states.push :link
          when :link_end
            puts "Closing token without opening token #{token.token_type} #{@states.last}".hl(:red)
          when :ext_link_start
            push_type_action(token)
            @states.push :link
          when :ext_link_end
            puts "Closing token without opening token #{token.token_type} #{@states.last}".hl(:red)
          when :end_of_file
            end_of_file_action
          else
            if CRLF_TOKENS.include?(token.token_type)
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
            end
          end
        else
          puts "Invalid state #{@state}".hl(:red)
        end
      end
      flush
    end

    def push_token_action(token)
      @link_stack << token
    end

    def push_type_action(token)
      @stack << token.token_type
    end

    def end_of_file_action
      unless @stack.empty?
        puts "There are unmatched tokens on stack [#{@stack.join(", ")}]".hl(:red)
      end
      unless @states.last == :default
        puts "There are unmatched states [#{@states.join(", ")}]".hl(:red)
      end
    end

    def close_link_action(token)
      opening_type = @stack.pop
      unless @stack.any?{|t| t == :link_start }
        if opening_type.to_s != token.token_type.to_s.sub(/_end$/,"_start")
          puts "Non-matching tokens #{opening_type} #{token.token_type} #{@states.last}".hl(:red)
        else
          to_print = []
          @link_stack.each do |token|
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
          @link_stack = []
        end
      end
    end

    def close_ext_link_action(token)
      opening_type = @stack.pop
      if opening_type.to_s != token.token_type.to_s.sub(/_end$/,"_start")
        puts "Non-matching tokens #{opening_type} #{token.token_type} #{@states.last}".hl(:red)
      else
        to_print = []
        @link_stack.each do |token|
          to_print << token.string_value unless token.token_type == :uri
        end
        to_print.each{|v| print v.hl(:yellow) }
        @link_stack = []
      end
    end
  end
end
