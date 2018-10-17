class Pdfmailer < ApplicationMailer
  default from: 'photodelivery@photocloud.by'

  def photo_email(email)
    attachments['photos.pdf'] = File.read('tmp/pdf/COMBINED.pdf')
    mail(to: email, subject: 'PDF with your photos is ready!')
  end
end
