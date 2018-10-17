class Life < ActiveRecord::Base

  def self.get_session_data(id)
    Life.where(session: id).first
  end

end
