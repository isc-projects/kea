class CppDriver < Formula
  desc "DataStax C/C++ Driver for Apache Cassandra"
  homepage "https://github.com/datastax/cpp-driver"
  url "https://github.com/datastax/cpp-driver/archive/2.9.0.tar.gz"
  sha256 "1fcf3a4626fe70c345ef7e40624b3f8910113fafb00a38f71357da146ea1a2ab"

  depends_on "cmake" => :build
  depends_on "libuv"
  depends_on "openssl"

  def install
    mkdir "build" do
      system "cmake", "..", *std_cmake_args
      system "make", "install"
    end
  end
end
