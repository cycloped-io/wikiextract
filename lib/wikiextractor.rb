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
                            :printable,:quot,:path,:amp,:left_curly,:right_curly])

    @@crlf_positions = Hash.new(0)
    @@errors = Hash.new(0)

    def print(contents)
      @message ||= ""
      @message << contents
    end

    def puts(contents="")
      print(contents + "\n")
    end

    def flush
      @message ||= ""
      STDOUT.puts @message.gsub(/\n\n+/,"\n\n")
      @message = ""
    end

    def crlf_stats
      @@crlf_positions
    end

    def errors
      @@errors
    end

    def error(msg,id)
      puts msg
      @@errors[id] += 1
    end

    def parse(input,id)
      @state = :default
      @link_stack = []
      self.tokenize(input).each.with_index do |token,index|
        unless token.token_type == :space
          str = "#{token.token_type.to_s} #{token.string_value}" +
            " [#{@states}]".hl(:green)
          str = str.hl(:green) if token.token_type == :crlf
          puts str
        end
        next
        type = token.token_type
        case type
        when :separator
          @link_stack.each{|t| print t.string_value.hl(:green) }
          print "|"
          @link_stack.clear
        when :link_start
          @state = :link
        when :link_end
          @link_stack.each{|t| print t.string_value.hl(:purple) }
          @link_stack.clear
          @state = :default
        when :ext_link_start
          @state = :ext_link
        when :ext_link_end
          @link_stack.each{|t| print t.string_value.hl(:yellow) }
          @link_stack.clear
          @state = :default
        when :alnum, :printable, :default, :space
          if @state == :default
            print token.string_value
          else
            push_token_action(token)
          end
        when :end_of_file
          end_of_file_action(id)
        when :crlf
          if @state == :default
            print "\n"
          else
            push_token_action(token)
          end
        else
          print " " + token.token_type.to_s.hl(:blue) + " #{token.string_value}".hl(:green)
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

    def end_of_file_action(id)
    end

    def close_link_action(token,id,opening_type)
      unless @stack.any?{|t| t == :link_start }
        if opening_type.to_s != token.token_type.to_s.sub(/_end$/,"_start")
          error("Non-matching tokens #{opening_type} #{token.token_type} #{@states.last}",id)
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

    def close_ext_link_action(token,id,opening_type)
      if opening_type.to_s != token.token_type.to_s.sub(/_end$/,"_start")
        error("Non-matching tokens #{opening_type} #{token.token_type} #{@states.last}",id)
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
