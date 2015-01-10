require "formula"

class Tcl < Formula
  homepage "http://www.tcl.tk/"
  url "http://downloads.sourceforge.net/project/tcl/Tcl/8.6.3/tcl8.6.3-src.tar.gz"
  sha1 "026b4b6330205bdc49af12332ee17c2b01f76d37"

  def install
    system "cd", "macosx"
    system "./configure", "--disable-debug",
                          "--disable-dependency-tracking",
                          "--disable-silent-rules",
                          "--prefix=#{prefix}"
    system "make", "install"
  end
end
