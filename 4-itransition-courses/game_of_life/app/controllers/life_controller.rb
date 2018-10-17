class LifeController < ApplicationController

  FILE_TO_PROCESS = 'tmp/to_process'
  FILE_PROCESSED = 'tmp/processed'
  HASHLIFE_PATH = './lib/hashlife/hashlife'
  PATTERNS_PATH = 'app/life_patterns/'
  COLUMNS = 80
  ROWS = 32
  TOTAL_CELLS = COLUMNS * ROWS

  def run
    start_session(request.session_options[:id])
  end

  def count
    session_id = request.session_options[:id]
    start_session(session_id)
    server_data = Life.get_session_data(session_id)
    server_state = server_data.state
    if params[:client_state] != 'NO'
      server_state = decode_abcd(params[:client_state])
    end
    server_generation = server_data.generation
    server_state = hash_life(params[:steps].to_i, server_state)
    server_generation = (server_generation.to_i + params[:steps].to_i).to_s
    server_data.update(state: server_state, generation: server_generation)
    render :json => {new_state: server_state, generation: server_generation}
  end

  def init_state
    session_id = request.session_options[:id]
    start_session(session_id)
    new_state = get_init_state(params[:type])
    Life.get_session_data(session_id).update(state: new_state, generation: 1)
    render :json => {new_state: new_state, generation: 1}
  end

  def clear_state
    session_id = request.session_options[:id]
    new_state = get_empty_field
    Life.get_session_data(session_id).update(state: new_state, generation: 1)
    render :json => {success: 1}
  end

  private

  def start_session(id)
    session_id = id
    puts "SESSION: #{session_id}"
    unless Life.exists?(session: session_id)
      Life.create session: session_id, state: get_empty_field, generation: 1
    end
    @server_data = Life.get_session_data(session_id)
  end

  def hash_life(steps, string_state)
    session_id = request.session_options[:id]
    string_to_process = ''
    TOTAL_CELLS.times { |i| string_to_process << string_state[i]; string_to_process << "\n" if (i+1) % COLUMNS == 0; }
    File.open("#{FILE_TO_PROCESS}#{session_id}.txt", 'w+') { |f| f.write("!to process by HashLife\n" + string_to_process) }

    `#{HASHLIFE_PATH} #{FILE_TO_PROCESS}#{session_id}.txt #{steps} > #{FILE_PROCESSED}#{session_id}.txt`

    lines = File.new("#{FILE_PROCESSED}#{session_id}.txt", 'r').read.split(/\n/)
    output_string = ''
    lines.each { |line| output_string << line }
    output_string
  end

  def get_init_state(pattern)
    new_state = ''
    case pattern
      when 'random'
        TOTAL_CELLS.times { new_state << %w(. . . O).sample }
      else
        lines = File.new("#{PATTERNS_PATH}#{pattern}.txt", 'r').read.split(/\n/)
        lines.each { |line| new_state << line }
    end
    new_state
  end

  def get_empty_field
    new_state = ''
    TOTAL_CELLS.times { new_state << '.' }
    new_state
  end

  def decode_abcd(str)
    ans = ''
    str.each_char do |c|
      case c
        when 'A'
          ans << '..'
        when 'B'
          ans << 'O.'
        when 'C'
          ans << '.O'
        when 'D'
          ans << 'OO'
      end
    end
    ans
  end

end
