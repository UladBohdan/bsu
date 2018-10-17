class MailSenderController < ApplicationController
  def create
    Pdfmailer.photo_email('vlbohdan@gmail.com').deliver
  end
end