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

class CC
  class DecodeError < Exception ; end
end

class CC
class Message
  PROTOCOL_VERSION = 0x536b616e

  ITEM_BLOB = 0x01
  ITEM_HASH = 0x02
  ITEM_LIST = 0x03
  ITEM_NULL = 0x04
  ITEM_BOOL = 0x05
  ITEM_UTF8 = 0x08
  ITEM_MASK = 0x0f

  ITEM_LENGTH_32   = 0x00
  ITEM_LENGTH_16   = 0x10
  ITEM_LENGTH_8    = 0x20
  ITEM_LENGTH_MASK = 0x30

  def initialize(msg = nil)
    @data = [PROTOCOL_VERSION].pack("N")
    if msg.is_a?(Hash)
      @data += CC::Message::encode_hash(msg)
    elsif msg.is_a?(String)
      @data = msg
    else
      raise ArgumentError, "initializer is not a Hash or String"
    end
  end

  def to_wire
    CC::set_binary(@data)
    @data
  end

  #
  # Encode a message.  The item passed in should be a hash, and can contain
  # any number of items of any type afterwards.  All keys in the hash must
  # be of type String or Symbol, and the values may be of any type.  If
  # the value is a Hash or Array, it will be encoded as a message type
  # HASH or LIST.  If it is nil, it will be encoded as NULL, and if it is
  # any other type, its to_s method will be called on it and it will be
  # encoded as a UTF8 item.
  #
  def self.to_wire(msg)
    encoded = [PROTOCOL_VERSION].pack("N")
    encoded += encode_hash(msg)
    encoded.force_encoding('binary')
    encoded
  end

  #
  # Decode a wire format message.
  #
  def self.from_wire(msg)
    if msg.length < 4
      raise CC::DecodeError, "Data is too short to decode"
    end
    msg.force_encoding('binary')
    version, msg = msg.unpack("N a*")
    unless version == PROTOCOL_VERSION
      raise CC::DecodeError, "Incorrect protocol version"
    end
    decode_hash(msg)
  end

  private
  # encode a simple string with a length prefix
  def self.encode_tag(tag)
    tag = tag.to_s
    [tag.length, tag].pack("C/a*")
  end

  def self.encode_length_and_type(data, type)
    if data.nil?
      [ITEM_NULL].pack("C")
    else
      len = data.length
      if len < 0x00000100
        [type | ITEM_LENGTH_8, len, data].pack("C C/a*")
      elsif len < 0x00010000
        [type | ITEM_LENGTH_16, len, data].pack("C n/a*")
      else
        [type | ITEM_LENGTH_32, len, data].pack("C N/a*")
      end
    end
  end

  # pack a string, including its type and length.
  def self.pack_utf8(str)
    encode_length_and_type(str.to_s.encode('binary'), ITEM_UTF8)
  end

  def self.pack_bool(bool)
    encode_length_and_type(encode_bool(bool), ITEM_BOOL)
  end

  def self.pack_blob(str)
    encode_length_and_type(str.to_s, ITEM_BLOB)
  end

  def self.pack_array(arr)
    encode_length_and_type(encode_array(arr), ITEM_LIST)
  end

  def self.pack_hash(hash)
    encode_length_and_type(encode_hash(hash), ITEM_HASH)
  end

  def self.encode_data(data)
    str.to_s
  end

  def self.encode_utf8(str)
    str.to_s.encode('binary')
  end

  def self.pack_nil
    encode_length_and_type(nil, ITEM_NULL)
  end

  def self.encode_item(item)
    case item
    when nil
      ret = pack_nil
    when Hash
      ret = pack_hash(item)
    when Array
      ret = pack_array(item)
    when String
      if item.encoding == 'utf-8'
        ret = pack_utf8(item)
      else
        ret = pack_blob(item)
      end
    when FalseClass
      ret = pack_bool(item)
    when TrueClass
      ret = pack_bool(item)
    else
      ret = pack_blob(item.to_s)
    end

    ret
  end

  def self.encode_hash(msg)
    unless msg.is_a?Hash
      raise ArgumentError, "Should be a hash"
    end
    buffer = ""
    msg.each do |key, value|
      buffer += encode_tag(key)
      buffer += encode_item(value)
    end
    buffer
  end

  def self.encode_bool(msg)
    unless msg.class == FalseClass or msg.class == TrueClass
      raise ArgumentError, "Should be true or false"
    end
    if msg
      [0x01].pack("C")
    else
      [0x00].pack("C")
    end
  end
    

  def self.encode_array(msg)
    unless msg.is_a?Array
      raise ArgumentError, "Should be an array"
    end
    buffer = ""
    msg.each do |value|
      buffer += encode_item(value)
    end
    buffer
  end

  def self.decode_tag(str)
    if str.length < 1
      raise CC::DecodeError, "Data underrun while decoding"
    end
    length = str.unpack("C")[0]
    if str.length - 1 < length
      raise CC::DecodeError, "Data underrun while decoding"
    end
    tag, remainder = str.unpack("x a#{length} a*")
    [ tag.encode('utf-8'), remainder ]
  end

  def self.decode_item(msg)
    if msg.length < 1
      raise CC::DecodeError, "Data underrun while decoding"
    end
    type_and_length_format = msg.unpack("C")[0]
    type = type_and_length_format & ITEM_MASK
    length_format = type_and_length_format & ITEM_LENGTH_MASK

    if type == ITEM_NULL
      msg = msg.unpack("x a*")[0]
    else
      if length_format == ITEM_LENGTH_8
        if msg.length - 1 < 1
          raise CC::DecodeError, "Data underrun while decoding"
        end
        length, msg = msg.unpack("x C a*")
      elsif length_format == ITEM_LENGTH_16
        if msg.length - 1 < 2
          raise CC::DecodeError, "Data underrun while decoding"
        end
        length, msg = msg.unpack("x n a*")
      elsif length_format == ITEM_LENGTH_32
        if msg.length - 1 < 4
          raise CC::DecodeError, "Data underrun while decoding"
        end
        length, msg = msg.unpack("x N a*")
      end
      if msg.length < length
        raise CC::DecodeError, "Data underrun while decoding"
      end
      item, msg = msg.unpack("a#{length} a*")
    end

    # unpack item based on type
    case type
    when ITEM_BLOB
      value = item
    when ITEM_UTF8
      value = item.encode('utf-8')
    when ITEM_BOOL
      value = decode_bool(item)
    when ITEM_HASH
      value = decode_hash(item)
    when ITEM_LIST
      value = decode_array(item)
    when ITEM_NULL
      value = nil
    else
      raise CC::DecodeError, "Unknown item type in decode: #{type}"
    end

    [value, msg]
  end

  def self.decode_bool(msg)
    return msg == [0x01].pack("C")
  end
    
  def self.decode_hash(msg)
    ret = {}
    while msg.length > 0
      tag, msg = decode_tag(msg)
      value, msg = decode_item(msg)
      ret[tag] = value
    end

    ret
  end

  def self.decode_array(msg)
    ret = []
    while msg.length > 0
      value, msg = decode_item(msg)
      ret << value
    end

    ret
  end

end # class Message
end # class CC

if $0 == __FILE__
  target = {
    "from" => "sender@host",
    "to" => "recipient@host",
    "seq" => 1234,
    "data" => {
      "list" => [ 1, 2, nil, true, false, "this" ],
      "description" => "Fun for all",
    },
  }

  wire = CC::Message.to_wire(target)
  puts wire.inspect

  puts CC::Message.from_wire(wire).inspect
end
