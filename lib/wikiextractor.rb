require 'set'
require 'colors'
require 'csv'

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

    def initialize(segments_file,links_file)
      @out = File.open(segments_file,"w")
      @links = File.open(links_file,"w")
    end

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

    def close
      @out.close
      @links.close
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
      @id = id.to_i
      @state = :default
      @link_stack = []
      self.tokenize(input,@out,@links,@id).each.with_index do |token,index|
        unless true || token.token_type == :space
          str = "#{token.token_type.to_s} #{token.string_value}"
          str = str.hl(:green) if token.token_type == :crlf
          puts str
        end
        type = token.token_type
        case type
        when :separator
          link_head(@link_stack)
          @link_stack.clear
          @state = :separator
        when :link_start
          @state = :link
        when :link_end
          unless @state == :separator
            link_head(@link_stack)
          end
          link_tail(@link_stack)
          @link_stack.clear
          @state = :post_link
        when :ext_link_start
          @state = :ext_link
        when :ext_link_end
          #@link_stack.each{|t| print_token(t,t.string_value,@out) }
          @link_stack.clear
          @state = :default
        when :alnum
          if @state == :default
            print_token(token,token.string_value,@out)
          elsif @state == :post_link
            finish_link(token)
            @state = :default
          else
            push_token_action(token)
          end
        when :space, :printable, :default, :num
          if @state == :default
            print_token(token,token.string_value,@out)
          elsif @state == :post_link
            finish_link()
            print_token(token,token.string_value,@out)
            @state = :default
          else
            push_token_action(token)
          end
        when :end_of_file
          finish_link if @state == :post_link
          end_of_file_action(id)
        when :crlf
          if @state == :default
            print_token(token,"\n",@out)
          elsif @state == :post_link
            finish_link()
            print_token(token,"\n",@out)
            @state = :default
          else
            push_token_action(token)
          end
        else
          print " " + token.token_type.to_s.hl(:blue) + " #{token.string_value}".hl(:green)
        end
      end
      #flush
    end

    def push_token_action(token)
      @link_stack << token
    end

    def finish_link(token=nil)
      return if @link_head.empty?
      concept_name = @link_head.map(&:string_value).join("")
      if token
        if @link_tail.last
          last_token = @link_tail.last
          last_token.instance_variable_set("@line_stop",token.line_stop)
          last_token.instance_variable_set("@column_stop",token.column_stop)
          last_token.instance_variable_set("@string_value", @link_tail.last.string_value +
                                           token.string_value)
        else
          @link_tail = [token]
        end
      end
      if @link_tail.empty?
        @link_tail = @link_head
      end
      link_name = @link_tail.map(&:string_value).join("")
      @links << [@id,@link_head.first.line_start,@link_tail.last.line_stop,
                 @link_head.first.column_start,@link_tail.last.column_stop,
                 concept_name,link_name]
      #print "[".hl(:green)
      @link_tail.each do |token|
        print_token(token,token.string_value,@out)
      end
      #print "]".hl(:green)
    end

    def link_head(tokens)
      @link_head = tokens.dup
    end

    def link_tail(tokens)
      @link_tail = tokens.dup
    end

    def print_token(token,str,out)
      out << [@id,token.token_type,token.line_start,token.line_stop,
               token.column_start,token.column_stop,str]
      #print str
    end

    def end_of_file_action(id)
    end

  end
end
