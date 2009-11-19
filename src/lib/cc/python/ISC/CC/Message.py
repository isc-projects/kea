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

# XXX
from ISC.Util import hexdump

import sys
import struct

class DecodeError(Exception): pass

PROTOCOL_VERSION = 0x536b616e

_ITEM_DATA = 0x01
_ITEM_HASH = 0x02
_ITEM_LIST = 0x03
_ITEM_NULL = 0x04
_ITEM_MASK = 0x0f

_ITEM_LENGTH_32   = 0x00
_ITEM_LENGTH_16   = 0x10
_ITEM_LENGTH_8    = 0x20
_ITEM_LENGTH_MASK = 0x30

def to_wire(items):
    """Encode a dict into wire format.
    >>> wire_format = Message.to_wire({"a": "b"})
    """
    return struct.pack(">I", PROTOCOL_VERSION) + _encode_hash(items)

def _encode_tag(tag):
    """Encode a single UTF-8 tag.
    ... wire_partial = Message._encode_tag('this')
    """
    return(struct.pack(">B", len(tag)) + bytearray(tag, 'utf-8'))

def _encode_length_and_type(data, datatype):
    """Helper method to handle the length encoding in one place."""
    if data == None:
        return(struct.pack(">B", _ITEM_NULL))
    length = len(data)
    if type(data) == str:
        #print("[XX] data is still string, converting to bytearray...");
        data = bytearray(data, 'utf-8')
    if length < 0x0000100:
        return(struct.pack(">B B", datatype | _ITEM_LENGTH_8, length) + data)
    elif length < 0x00010000:
        return(struct.pack(">B H", datatype | _ITEM_LENGTH_16, length) + data)
    else:
        return(struct.pack(">B I", datatype, length) + data)

def _pack_string(item):
    """Pack a string (data) and its type/length prefix."""
    return (_encode_length_and_type(item, _ITEM_DATA))

def _pack_array(item):
    """Pack a list (array) and its type/length prefix."""
    return (_encode_length_and_type(_encode_array(item), _ITEM_LIST))

def _pack_hash(item):
    """Pack a dict (hash) and its type/length prefix."""
    data = _encode_hash(item)
    return (_encode_length_and_type(data, _ITEM_HASH))

def _encode_string(item):
    """Encode a string.  More or less identity."""
    return (item)

def _pack_nil():
    """Encode a nil (NULL, None) item."""
    return _encode_length_and_type(None, None)

def _encode_item(item):
    """Encode each item depending on its type"""
    if item == None:
        return (_pack_nil())
    elif type(item) == dict:
        return (_pack_hash(item))
    elif type(item) == list:
        return (_pack_array(item))
    elif type(item) in (bytearray, bytes):
        return (_pack_string(item))
    else:
        return (_pack_string(str(item)))

def _encode_array(item):
    """Encode an array, where each value is encoded recursively"""
    ret = bytearray()
    for i in item:
        ret += _encode_item(i)
    return ret

def _encode_hash(item):
    """Encode a hash, where each value is encoded recursively"""

    ret = bytearray()
    for key, value in item.items():
        ret += _encode_tag(key)
        ret += _encode_item(value)
    return ret

#
# decode methods
#

def from_wire(data):
    if len(data) < 5:
        raise DecodeError("Data is too short to decode")
    wire_version, data = data[0:4], data[4:]
    if (type(wire_version) == str):
        wire_version = bytearray(wire_version, 'utf-8')
    #wire_version = struct.unpack(">I", wire_version)[0]
    wire_version = struct.unpack(">I", wire_version)[0]
    if wire_version != PROTOCOL_VERSION:
        raise DecodeError("Incorrect protocol version")
    return _decode_hash(data)

def _decode_tag(data):
    if len(data) < 1:
        raise DecodeError("Data underrun while decoding")
    if (type(data) == str):
        data = bytearray(data, 'utf-8')
    length = data[0]
    if len(data) - 1 < length:
        raise DecodeError("Data underrun while decoding")
    return [data[1:length + 1], data[length + 1:]]

def _decode_item(data):
    if len(data) < 1:
        raise DecodeError("Data underrun while decoding")
    type_and_length_format = data[0]
    item_type = type_and_length_format & _ITEM_MASK
    length_format = type_and_length_format & _ITEM_LENGTH_MASK

    if item_type == _ITEM_NULL:
        data = data[1:]
    else:
        if length_format == _ITEM_LENGTH_8:
            if len(data) - 1 < 1:
                raise DecodeError("Data underrun while decoding")
            length = data[1]
            data = data[2:]
        elif length_format == _ITEM_LENGTH_16:
            if len(data) - 1 < 2:
                raise DecodeError("Data underrun while decoding")
            length = struct.unpack(">H", data[1:3])[0]
            data = data[3:]
        elif length_format == _ITEM_LENGTH_32:
            if len(data) - 1 < 4:
                raise DecodeError("Data underrun while decoding")
            length = struct.unpack(">I", data[1:5])[0]
            data = data[5:]
        if len(data) < length:
            raise DecodeError("Data underrun while decoding")
        item = data[0:length]
        data = data[length:]

    if item_type == _ITEM_DATA:
        value = item
    elif item_type == _ITEM_HASH:
        value = _decode_hash(item)
    elif item_type == _ITEM_LIST:
        value = _decode_array(item)
    elif item_type == _ITEM_NULL:
        value = None
    else:
        raise DecodeError("Unknown item type in decode: %02x" % item_type)

    return (value, data)

def _decode_hash(data):
    ret = {}
    while len(data) > 0:
        tag, data = _decode_tag(data)
        value, data = _decode_item(data)
        if type(value) == bytearray:
            # hack! just try it in case it is really a string
            try:
                value = value.decode('utf-8')
            except UnicodeDecodeError as ude:
                # apparently not a final item, leave it a bytearray
                pass
        if type(tag) == bytearray:
            tag = tag.decode('utf-8')
        ret[tag] = value
    return ret

def _decode_array(data):
    ret = []
    while len(data) > 0:
        value, data = _decode_item(data)
        if (type(value) == bytearray):
            value = value.decode('utf-8')
        ret.append(value)
    return ret

if __name__ == "__main__":
    import doctest
    doctest.testmod()
