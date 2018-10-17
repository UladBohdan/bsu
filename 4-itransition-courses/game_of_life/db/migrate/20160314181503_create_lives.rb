class CreateLives < ActiveRecord::Migration
  def change
    create_table :lives do |t|
      t.string :session
      t.integer :generation
      t.string :state

      t.timestamps null: false
    end
  end
end
