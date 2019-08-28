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
    opt :frames, "Max number of frames to render", type: Integer
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

  img.frames.each_with_index do |frame, f|
    if options[:frames_given] and f % (img.frames.length / options[:frames]) != 0
      next
    end

    final_data << []

    frame.get_pixels.each do |row|
      final_data.last << []
      row.each do |col|
        r, g, b = [col[0].to_f / 255, col[1].to_f / 255, col[2].to_f / 255]
        luminance = (0.2126 * r) + (0.7152 * g) + (0.0722 * b)
        black = luminance > threshold
        final_data.last.last << (invert ? black : !black)
      end
    end
  end

  final_data
end

def compare_frames(a, b)
  startX = 0
  startY = 0
  width  = a[0].length
  height = a.length

  if b.nil?
    data = a
  else
    diff = a.collect.with_index do |row, i|
      row.collect.with_index { |v, j| v != b[i][j] }
    end

    data = b
  end

  [startX, startY, width, height, data]
end

def output(data, options)
  frameCount = data.length
  varname = options[:name].upcase
  bytes   = (data.first.length * data.first.first.length / 8) + 5
  bytes  *= frameCount

  lines = []
  lines << "#ifndef _#{varname}_h"
  lines << "#define _#{varname}_h"
  lines << ""

  lines << "// Size: #{bytes} bytes"
  lines << ""

  lines << "const PROGMEM uint8_t #{varname}[] = {"
  lines << "  %-4d, // frameCount" % frameCount
  lines << ""

  data.each_with_index do |frame, f|
    startX, startY, width, height, fdata = compare_frames(frame, data[f-1])

    lines << "" if f > 0
    lines << "  // FRAME #{f}"
    lines << "  %-4d, // frame"  % f
    lines << "  %-4d, // startX" % startX
    lines << "  %-4d, // startY" % startY
    lines << "  %-4d, // width"  % width
    lines << "  %-4d, // height" % height
    lines << ""
    lines << "  // DATA"

    fdata.each do |row|
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
  end

  # Remove trailing comma after all frames written.
  lines[lines.length-1].gsub!(/,$/,'')

  lines << "};"
  lines << ""
  lines << "#endif"

  lines.join("\n")
end

def preview(data)
  data.each do |frame|
    (0..frame.length).step(2).each do |i|
      rowA = frame[i]
      rowB = frame[i+1] rescue []

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
