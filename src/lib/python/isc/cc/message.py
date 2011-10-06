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

#
# Functions for reading and parsing cc messages
# Currently these are only abstraction functions for JSON conversion.
#

import sys
import struct

import json

def to_wire(items):
    '''Encodes the given python structure in JSON, and converts the
       result to bytes. Raises a TypeError if the given structure is
       not serializable with JSON.'''
    return json.dumps(items).encode('utf8')

def from_wire(data):
    '''Decodes the given bytes and parses it with the builtin JSON
       parser. Raises a ValueError if the data is not valid JSON.
       Raises an AttributeError if the given object has no decode()
       method (which should return a string).
       '''
    return json.loads(data.decode('utf8'), strict=False)

if __name__ == "__main__":
    import doctest
    doctest.testmod()
