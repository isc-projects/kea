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


import unittest
from bindctl import cmdparse

class TestCmdParse(unittest.TestCase):

    def test_remove_unquoted_whitespace(self):
        self.assertEqual(cmdparse._remove_unquoted_whitespace("a"), "a")
        self.assertEqual(cmdparse._remove_unquoted_whitespace(" a"), "a")
        self.assertEqual(cmdparse._remove_unquoted_whitespace("a "), "a")
        self.assertEqual(cmdparse._remove_unquoted_whitespace(" a "), "a")
        self.assertNotEqual(cmdparse._remove_unquoted_whitespace("a"), "a ")
        self.assertNotEqual(cmdparse._remove_unquoted_whitespace(" a"), " a")
        self.assertNotEqual(cmdparse._remove_unquoted_whitespace("a "), "a ")
        self.assertNotEqual(cmdparse._remove_unquoted_whitespace(" a "), " a ")
        self.assertNotEqual(cmdparse._remove_unquoted_whitespace(" a "), "b")

        self.assertEqual(cmdparse._remove_unquoted_whitespace("\"abc\""), "\"abc\"")
        self.assertEqual(cmdparse._remove_unquoted_whitespace(" \"abc\""), "\"abc\"")
        self.assertEqual(cmdparse._remove_unquoted_whitespace("\"abc\" "), "\"abc\"")
        self.assertEqual(cmdparse._remove_unquoted_whitespace(" \"abc\" "), "\"abc\"")
        
        self.assertEqual(cmdparse._remove_unquoted_whitespace("\" abc\""), "\" abc\"")
        self.assertEqual(cmdparse._remove_unquoted_whitespace(" \"a bc\""), "\"a bc\"")
        self.assertEqual(cmdparse._remove_unquoted_whitespace("\"ab c\" "), "\"ab c\"")
        self.assertEqual(cmdparse._remove_unquoted_whitespace(" \"abc \" "), "\"abc \"")
        self.assertEqual(cmdparse._remove_unquoted_whitespace(" \" a b c \" "), "\" a b c \"")
        
        self.assertEqual(cmdparse._remove_unquoted_whitespace("a\" abc\"a"), "a\" abc\"a")
        self.assertEqual(cmdparse._remove_unquoted_whitespace("a \"a bc\"a"), "a\"a bc\"a")
        self.assertEqual(cmdparse._remove_unquoted_whitespace("a\"ab c\" a"), "a\"ab c\"a")
        self.assertEqual(cmdparse._remove_unquoted_whitespace("a \"abc \" a"), "a\"abc \"a")
        self.assertEqual(cmdparse._remove_unquoted_whitespace("a \" a b c \" a"), "a\" a b c \"a")

    # short-hand function to make the set of tests more readable
    def rws(self, a, b):
        self.assertEqual(cmdparse._remove_list_and_map_whitespace(a), b)

    def test_remove_list_whitespace(self):
        self.rws("a", "a")
        self.rws(" a ", " a ")
        self.rws(" [a] ", " [a] ")
        self.rws(" [ a] ", " [a] ")
        self.rws(" [ a ] ", " [a] ")
        self.rws(" [ a b c ] ", " [abc] ")
        self.rws(" [ a \"b c\" ] ", " [a\"b c\"] ")
        self.rws("a [ a \"b c\" ] a", "a [a\"b c\"] a")
        self.rws("a] [ a \"b c\" ] a", "a] [a\"b c\"] a")
        self.rws(" [ a [b c] ] ", " [a[bc]] ")
        self.rws(" [ a b][ c d ] ", " [ab][cd] ")
        self.rws(" [ a b] [ c d ] ", " [ab] [cd] ")
        
        self.rws("a", "a")
        self.rws(" a ", " a ")
        self.rws(" {a} ", " {a} ")
        self.rws(" { a} ", " {a} ")
        self.rws(" { a } ", " {a} ")
        self.rws(" { a b c } ", " {abc} ")
        self.rws(" { a \"b c\" } ", " {a\"b c\"} ")
        self.rws("a { a \"b c\" } a", "a {a\"b c\"} a")
        self.rws("a} { a \"b c\" } a", "a} {a\"b c\"} a")
        self.rws(" { a {b c} } ", " {a{bc}} ")
        self.rws(" { a b}{ c d } ", " {ab}{cd} ")
        self.rws(" { a b} { c d } ", " {ab} {cd} ")

        self.rws(" [ a b]{ c d } ", " [ab]{cd} ")
        self.rws(" [ a b{ c d }] ", " [ab{cd}] ")
        self.rws(" [ a b{ \"c d\" }] ", " [ab{\"c d\"}] ")
        

if __name__== "__main__":
    unittest.main()
    
