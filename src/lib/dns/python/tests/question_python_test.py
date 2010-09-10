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
# Tests for the rrtype part of the pydnspp module
#

import unittest
import os
from pydnspp import *

if "TESTDATA_PATH" in os.environ:
    testdata_path = os.environ["TESTDATA_PATH"]
else:
    testdata_path = "../tests/testdata"

def read_wire_data(filename):
    data = bytes()
    file = open(testdata_path + os.sep + filename, "r")
    for line in file:
        line = line.strip()
        if line == "" or line.startswith("#"):
            pass
        else:
            cur_data = bytes.fromhex(line)
            data += cur_data

    return data

def question_from_wire(file, position = 0):
    data = read_wire_data(file)
    return Question(data, position)


class QuestionTest(unittest.TestCase):
    def setUp(self):
        self.example_name1 = Name("foo.example.com")
        self.example_name2 = Name("bar.example.com")
        self.test_question1 = Question(self.example_name1, RRClass("IN"), RRType("NS"))
        self.test_question2 = Question(self.example_name2, RRClass("CH"), RRType("A"))

    def test_init(self):
        self.assertRaises(TypeError, Question, "wrong")

    # tests below based on cpp unit tests
    # also tests get_name, get_class and get_type
    def test_from_wire(self):
        
        q = question_from_wire("question_fromWire")

        self.assertEqual(self.example_name1, q.get_name())
        self.assertEqual(RRClass("IN"), q.get_class())
        self.assertEqual(RRType("NS"), q.get_type())
    
        # owner name of the second Question is compressed.  It's uncommon
        # (to have multiple questions), but isn't prohibited by the protocol.
        q = question_from_wire("question_fromWire", 21)
        self.assertEqual(self.example_name2, q.get_name())
        self.assertEqual(RRClass("CH"), q.get_class())
        self.assertEqual(RRType("A"), q.get_type())
    
        # Pathological cases: Corresponding exceptions will be thrown from
        # the underlying parser.
        self.assertRaises(DNSMessageFORMERR,
                          question_from_wire,
                          "question_fromWire", 31)
        self.assertRaises(IncompleteRRClass,
                          question_from_wire,
                          "question_fromWire", 36)
    
    def test_to_text(self):
    
        self.assertEqual("foo.example.com. IN NS\n", self.test_question1.to_text())
        self.assertEqual("foo.example.com. IN NS\n", str(self.test_question1))
        self.assertEqual("bar.example.com. CH A\n", self.test_question2.to_text())
    
    
    def test_to_wire_buffer(self):
        obuffer = bytes()
        obuffer = self.test_question1.to_wire(obuffer)
        obuffer = self.test_question2.to_wire(obuffer)
        wiredata = read_wire_data("question_toWire1")
        self.assertEqual(obuffer, wiredata)
    
    
    def test_to_wire_renderer(self):
        renderer = MessageRenderer()
        self.test_question1.to_wire(renderer)
        self.test_question2.to_wire(renderer)
        wiredata = read_wire_data("question_toWire2")
        self.assertEqual(renderer.get_data(), wiredata)
        self.assertRaises(TypeError, self.test_question1.to_wire, 1)
    

if __name__ == '__main__':
    unittest.main()
