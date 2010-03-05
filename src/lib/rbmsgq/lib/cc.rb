# Copyright (C) 2009  Internet Systems Consortium.
#
# Permission to use, copy, modify, and distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND INTERNET SYSTEMS CONSORTIUM
# DISCLAIMS ALL WARRANTIES WITH REGARD TO THIS SOFTWARE INCLUDING ALL
# IMPLIED WARRANTIES OF MERCHANTABILITY AND FITNESS. IN NO EVENT SHALL
# INTERNET SYSTEMS CONSORTIUM BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING
# FROM LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT,
# NEGLIGENCE OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION
# WITH THE USE OR PERFORMANCE OF THIS SOFTWARE.

unless respond_to?('relative_feature') # nodoc
  def require_relative(relative_feature)
    c = caller.first
    fail "Can't parse #{c}" unless c.rindex(/:\d+(:in `.*')?$/)
    file = $`
    if /\A\((.*)\)/ =~ file # eval, etc.
      raise LoadError, "require_relative is called in #{$1}"
    end
    absolute = File.expand_path(relative_feature, File.dirname(file))
    require absolute
  end
end

class CC
  def self.set_utf8(str) #nodoc
    if str.respond_to?('force_encoding')
      str.force_encoding(Encoding::UTF_8)
    end
  end

  def self.set_binary(str) #nodoc
    if str.respond_to?('force_encoding')
      str.force_encoding(Encoding::BINARY)
    end
  end
end

require_relative 'cc/message'
require_relative 'cc/session'

if $0 == __FILE__
  cc = CC::Session.new

  puts "Our local name: #{cc.lname}"

  cc.group_subscribe("test")

  counter = 0

  while counter < 10000 do
    cc.group_sendmsg({ :counter => counter }, "test", "foo")
    routing, data = cc.group_recvmsg(false)
    counter += 1
  end
end
