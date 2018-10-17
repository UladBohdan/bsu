require 'open-uri'

class PdfGeneratorController < ApplicationController
  def create
    @email = params[:email]
    response = open('http://res.cloudinary.com/dhgy4yket/image/list/' + @email + '.json').read
    @json = ActiveSupport::JSON.decode(response)
    @image_list = []
    pdf = CombinePDF.new
    url_prefix = 'http://res.cloudinary.com/dhgy4yket/image/upload/v'
    @json['resources'].each do |img|
      name_image = img['public_id'] + '.' + img['format']
      name_pdf = img['public_id'] + '.pdf'
      next_image = url_prefix + img['version'].to_s + '/' + name_image
      @image_list.push(next_image)
      open('tmp/img/' + name_image, 'wb') do |file|
        file << open(next_image).read
      end
      Magick::Image.read('tmp/img/' + name_image).first.write('tmp/pdf/'+name_pdf)
      pdf << CombinePDF.load('tmp/pdf/'+name_pdf)
    end
    pdf.save 'tmp/pdf/COMBINED.pdf'
    Pdfmailer.photo_email(@email).deliver
    render json: {
        status: 200,
        message: 'pdf sent',
        email: @email
    }.to_json
  end
end
