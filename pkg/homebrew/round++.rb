class Roundxx < Formula
  homepage "http://www.cybergarage.org/do/view/Main/Round"
  url "https://github.com/cybergarage/Round/archive/0.1.tar.gz"
  sha1 "5f1b2513e55b97c2fd06ece3a3ac1f7978af413a"

  depends_on "autoconf" => :build
  depends_on "automake" => :build
  depends_on "readline" 
  depends_on "boost"   
  depends_on "jansson"
  depends_on "spidermonkey"
  depends_on "v8"
  depends_on "mupnp++"

  def install
    system "./bootstrap"
    system "./configure_macosx", "--disable-debug",
                                 "--disable-dependency-tracking",
                                 "--disable-silent-rules",
                                 "--prefix=#{prefix}"
    system "make"
    system "make", "install"
  end
end
