#!/usr/bin/env ruby

require "mini_magick"
require "optimist"

def opts(argv=ARGV)
  options = Optimist::options(argv) do
    version "0.0"
    banner  "Convert images for use with Mau's LCD library."

    opt :threshold, "Threshold for b/w convert", default: 128
    opt :preview, "Generate preview, don't convert", default: false
    opt :size, "Output image size", default: '128x64>'
    opt :invert, "Invert output", default: false
    opt :name, "Image name", default: 'IMAGE'
  end

  options[:_filename] = argv.shift || "C:/Users/eiser.000/Desktop/Sabine_Starbird.png"
  options
end

def convert(options)
  filename  = options[:_filename]
  threshold = options[:threshold].to_f / 255
  size      = options[:size]
  invert    = options[:invert]

  puts "Converting:  #{filename}"
  puts "Threshold:   #{threshold}"
  puts "Output Size: #{size}"

  # Clean Filename
  filename = filename.gsub(/\\/, '/')

  img = MiniMagick::Image.open(filename)
  img.resize(size)

  final_data = []

  img.get_pixels.each do |row|
    final_data << []
    row.each do |col|
      r, g, b = [col[0].to_f / 255, col[1].to_f / 255, col[2].to_f / 255]
      luminance = (0.2126 * r) + (0.7152 * g) + (0.0722 * b)
      black = luminance > threshold
      final_data.last << (invert ? black : !black)
    end
  end

  final_data
end

def output(data, options)
  frameCount = 1
  varname = options[:name].upcase
  bytes   = data.length * data[0].length / 8
  bytes  += 5 * frameCount

  lines = []
  lines << "#ifndef _#{varname}_h"
  lines << "#define _#{varname}_h"
  lines << ""

  lines << "// Size: #{bytes} bytes"

  lines << "const PROGMEM uint8_t #{varname}[] = {"
  lines << "  %-4d, // frameCount" % frameCount
  lines << ""
  lines << "  // FRAME #{1}"
  lines << "  %-4d, // frame"  % 1
  lines << "  %-4d, // startX" % 0
  lines << "  %-4d, // startY" % 0
  lines << "  %-4d, // width"  % data[0].length
  lines << "  %-4d, // height" % data.length
  lines << ""
  lines << "  // DATA"

  data.each do |row|
    rowline = "  "
    bytes = []
    row.each_with_index do |col, i|
      bytes[i/8] ||= 0
      bytes[i/8] <<= 1
      bytes[i/8]  |= col ? 1 : 0
    end

    # Shift the last col over
    bytes[bytes.length-1] <<= row.length % 8

    bytes.each do |byte|
      rowline << "0x%02x," % byte
    end
    lines << rowline
  end

  # Remove trailing comma after all frames written.
  lines[lines.length-1].gsub!(/,$/,'')

  lines << "};"
  lines << ""
  lines << "#endif"

  lines.join("\n")
end

def preview(data)
  (0..data.length).step(2).each do |i|
    rowA = data[i]
    rowB = data[i+1] rescue []

    return unless rowA

    1.upto(rowA.length) do |j|
      a, b = [rowA[j-1], rowB[j-1]]

      if a & b
        print "█"
      elsif a
        print "▀"
      elsif b
        print "▄"
      else
        print " "
      end
    end

    puts
  end
end

#== Main Execution

options = opts(ARGV)
data = convert(options)

puts "---"

if options[:preview]
  preview(data)
else
  cstr = output(data, options)
  filepath = "../src/assets/#{options[:name]}.h"
  File.write(filepath, cstr)
  puts "Wrote #{cstr.length} bytes to #{filepath}"
end
