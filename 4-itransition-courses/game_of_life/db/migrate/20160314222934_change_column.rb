class ChangeColumn < ActiveRecord::Migration
  def change
    change_column :lives, :generation, :string
  end
end
