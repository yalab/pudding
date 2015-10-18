require 'open3'
require 'pathname'

class TexturePacker
  FORMATS = {"PVRTC4" => "pvr.ccz", "ETC1_ALPHA" => "etc1"}
  def initialize(dir, dest, format)
    @dir = Pathname.new(dir)
    @dest = Pathname.new(dest)
    @format = format
  end

  def pack
    ext = FORMATS[@format]
    name = File.basename(@dir)
    plist = @dest.join("#{name}.plist")
    png = @dest.join("#{name}.#{ext}")
    
    cmd = ["/usr/local/bin/TexturePacker", '--data', plist.to_s, '--sheet', png.to_s, '--opt', @format, '--replace', "^=#{name}/"]
    if @format == "PVRTC4"
      cmd << '--force-squared'
    end
    
    cmd << @dir.to_s
    Open3.popen3(*cmd, chdir: @dir.to_s) do |stdin, stdout, stderr|
      puts stdout.read
      puts stderr.read
    end
  end
end

desc "Pack textures"
task :texture_pack do
  target = File.expand_path("../", __FILE__) + "/Textures/*"
  dest = File.expand_path("../", __FILE__) + "/Resources/Image"
  Dir.glob(target) do |d|
    TexturePacker.new(d, dest, "PVRTC4").pack
  end
  
end
task :default => :texture_pack
