class LinkMap
  attr_reader :token_map, :converted_names_map, :converted_names

  def initialize(links_path)
    @links_path = links_path
    @names = []
    @unique_tokens = Set.new
    @names_map = Hash.new{|h,e| h[e] = Set.new }
    @token_map = Hash.new(0)
    @converted_names = []
    @converted_names_map = {}
  end

  def read_links
    progress = LocalProgress.new("Processing unique links", `wc -l #{@links_path}`.to_i)
    File.open(@links_path) do |input|
      input.each do |line|
        progress.step(1)
        name = line.chomp
        tokens = name.split(/\b/).reject{|e| e =~ /\s/ }
        next if tokens.empty?
        @names_map[tokens] << name
        next if @names_map[tokens].size > 1
        tokens.each{|t| @unique_tokens << t}
        @names << tokens
      end
    end
    progress.stop

    @unique_tokens.to_a.each.with_index do |token, index|
      @token_map[token] = index + 1
    end

    @names.each do |name|
      @converted_names << name.map{|e| @token_map[e] }
    end

    @names_map.each do |tokens, names|
      ids = tokens.map{|t| @token_map[t]}
      @converted_names_map[ids] = names
    end
  end

  def prepare_for_serialization
    @links_path = nil
    @names_map = nil
    @unique_tokens = nil
  end
end 