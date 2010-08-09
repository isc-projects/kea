
# Copyright (C) 2010  Internet Systems Consortium.
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
# Tests for the functions in data.py
#

import unittest
import isc.cc

class MessageTest(unittest.TestCase):
    def setUp(self):
        self.msg1 = { "just": [ "an", "arbitrary", "structure" ] }
        self.msg1_str = "{\"just\": [\"an\", \"arbitrary\", \"structure\"]}";
        self.msg1_wire = self.msg1_str.encode()

        self.msg2 = { "aaa": [ 1, 1.1, True, False, None ] }
        self.msg2_str = "{\"aaa\": [1, 1.1, true, false, null]}";
        self.msg2_wire = self.msg2_str.encode()

    def test_encode_json(self):
        self.assertEqual(self.msg1_wire, isc.cc.message.to_wire(self.msg1))
        self.assertEqual(self.msg2_wire, isc.cc.message.to_wire(self.msg2))

        self.assertRaises(TypeError, isc.cc.message.to_wire, NotImplemented)
        
    def test_decode_json(self):
        self.assertEqual(self.msg1, isc.cc.message.from_wire(self.msg1_wire))
        self.assertEqual(self.msg2, isc.cc.message.from_wire(self.msg2_wire))

        self.assertRaises(AttributeError, isc.cc.message.from_wire, 1)
        self.assertRaises(ValueError, isc.cc.message.from_wire, b'\x001')
        self.assertRaises(ValueError, isc.cc.message.from_wire, b'')
        self.assertRaises(ValueError, isc.cc.message.from_wire, b'{"a": ')
        self.assertRaises(ValueError, isc.cc.message.from_wire, b'[ 1 ')
        self.assertRaises(ValueError, isc.cc.message.from_wire, b']')

if __name__ == '__main__':
    unittest.main()


