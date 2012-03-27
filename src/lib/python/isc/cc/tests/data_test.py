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
import os
from isc.cc import data

class TestData(unittest.TestCase):
    def test_remove_identical(self):
        a = {}
        b = {}
        c = {}
        data.remove_identical(a, b)
        self.assertEqual(a, c)

        a = { "a": 1 }
        b = { "a": 1 }
        c = {}
        data.remove_identical(a, b)
        self.assertEqual(a, c)
    
        a = { "a": 1, "b": [ 1, 2 ] }
        b = {}
        c = { "a": 1, "b": [ 1, 2 ] }
        data.remove_identical(a, b)
        self.assertEqual(a, c)
    
        a = { "a": 1, "b": [ 1, 2 ] }
        b = { "a": 1, "b": [ 1, 2 ] }
        c = {}
        data.remove_identical(a, b)
        self.assertEqual(a, c)
    
        a = { "a": 1, "b": [ 1, 2 ] }
        b = { "a": 1, "b": [ 1, 3 ] }
        c = { "b": [ 1, 2 ] }
        data.remove_identical(a, b)
        self.assertEqual(a, c)
    
        a = { "a": { "b": "c" } }
        b = {}
        c = { "a": { "b": "c" } }
        data.remove_identical(a, b)
        self.assertEqual(a, c)
    
        a = { "a": { "b": "c" } }
        b = { "a": { "b": "c" } }
        c = {}
        data.remove_identical(a, b)
        self.assertEqual(a, c)
    
        a = { "a": { "b": "c" } }
        b = { "a": { "b": "d" } }
        c = { "a": { "b": "c" } }
        data.remove_identical(a, b)
        self.assertEqual(a, c)

        self.assertRaises(data.DataTypeError, data.remove_identical,
                          a, 1)
        self.assertRaises(data.DataTypeError, data.remove_identical,
                          1, b)
        
    def test_merge(self):
        d1 = { 'a': 'a', 'b': 1, 'c': { 'd': 'd', 'e': 2 } }
        d2 = { 'a': None, 'c': { 'd': None, 'e': 3, 'f': [ 1 ] } }
        d12 = { 'b': 1, 'c': { 'e': 3, 'f': [ 1 ] } }
        m12 = d1
        data.merge(m12, d2)
        self.assertEqual(d12, m12)
        self.assertRaises(data.DataTypeError, data.merge, d1, "a")
        self.assertRaises(data.DataTypeError, data.merge, 1, d2)
        self.assertRaises(data.DataTypeError, data.merge, None, None)


    def test_split_identifier_list_indices(self):
        id, indices = data.split_identifier_list_indices('a')
        self.assertEqual(id, 'a')
        self.assertEqual(indices, None)
        id, indices = data.split_identifier_list_indices('a[0]')
        self.assertEqual(id, 'a')
        self.assertEqual(indices, [0])
        id, indices = data.split_identifier_list_indices('a[0][1]')
        self.assertEqual(id, 'a')
        self.assertEqual(indices, [0, 1])

        # examples from the docstring
        id, indices = data.split_identifier_list_indices('a/b/c')
        self.assertEqual(id, 'a/b/c')
        self.assertEqual(indices, None)
        
        id, indices = data.split_identifier_list_indices('a/b/c[1]')
        self.assertEqual(id, 'a/b/c')
        self.assertEqual(indices, [1])
       
        id, indices = data.split_identifier_list_indices('a/b/c[1][2][3]')
        self.assertEqual(id, 'a/b/c')
        self.assertEqual(indices, [1, 2, 3])
        
        id, indices = data.split_identifier_list_indices('a[0]/b[1]/c[2]')
        self.assertEqual(id, 'a[0]/b[1]/c')
        self.assertEqual(indices, [2])

        # bad formats
        self.assertRaises(data.DataTypeError, data.split_identifier_list_indices, 'a[')
        self.assertRaises(data.DataTypeError, data.split_identifier_list_indices, 'a]')
        self.assertRaises(data.DataTypeError, data.split_identifier_list_indices, 'a[[0]]')
        self.assertRaises(data.DataTypeError, data.split_identifier_list_indices, 'a[0]a')
        self.assertRaises(data.DataTypeError, data.split_identifier_list_indices, 'a[0]a[1]')

        self.assertRaises(data.DataTypeError, data.split_identifier_list_indices, 1)
        

    def test_find(self):
        d1 = { 'a': 'a', 'b': 1, 'c': { 'd': 'd', 'e': 2, 'more': { 'data': 'here' } } }
        self.assertEqual(data.find(d1, ''), d1)
        self.assertEqual(data.find(d1, 'a'), 'a')
        self.assertEqual(data.find(d1, 'c/e'), 2)
        self.assertEqual(data.find(d1, 'c/more/'), { 'data': 'here' })
        self.assertEqual(data.find(d1, 'c/more/data'), 'here')
        self.assertRaises(data.DataNotFoundError, data.find, d1, 'c/f')
        self.assertRaises(data.DataNotFoundError, data.find, d1, 'f')
        self.assertRaises(data.DataTypeError, data.find, d1, 1)
        self.assertRaises(data.DataTypeError, data.find, None, 1)
        self.assertRaises(data.DataTypeError, data.find, None, "foo")
        self.assertRaises(data.DataTypeError, data.find, "123", "123")
        self.assertEqual(data.find("123", ""), "123")

        d2 = { 'a': [ 1, 2, 3 ] }
        self.assertEqual(data.find(d2, 'a[0]'), 1)
        self.assertEqual(data.find(d2, 'a[1]'), 2)
        self.assertEqual(data.find(d2, 'a[2]'), 3)
        self.assertRaises(data.DataNotFoundError, data.find, d2, 'a[3]')
        self.assertRaises(data.DataTypeError, data.find, d2, 'a[a]')

        d3 = { 'a': [ { 'b': [ {}, { 'c': 'd' } ] } ] }
        self.assertEqual(data.find(d3, 'a[0]/b[1]/c'), 'd')
        self.assertRaises(data.DataNotFoundError, data.find, d3, 'a[1]/b[1]/c')
        
    def test_set(self):
        d1 = { 'a': 'a', 'b': 1, 'c': { 'd': 'd', 'e': 2 } }
        d12 = { 'b': 1, 'c': { 'e': 3, 'f': [ 1 ] } }
        d13 = { 'b': 1, 'c': { 'e': 3, 'f': [ 2 ] } }
        d14 = { 'b': 1, 'c': { 'e': 3, 'f': [ { 'g': [ 1, 2 ] } ] } }
        d15 = { 'b': 1, 'c': { 'e': 3, 'f': [ { 'g': [ 1, 3 ] } ] } }
        data.set(d1, 'a', None)
        data.set(d1, 'c/d', None)
        data.set(d1, 'c/e/', 3)
        data.set(d1, 'c/f', [ 1 ] )
        self.assertEqual(d1, d12)
        data.set(d1, 'c/f[0]', 2 )
        self.assertEqual(d1, d13)

        data.set(d1, 'c/f[0]', { 'g': [ 1, 2] } )
        self.assertEqual(d1, d14)
        data.set(d1, 'c/f[0]/g[1]', 3)
        self.assertEqual(d1, d15)
        
        self.assertRaises(data.DataTypeError, data.set, d1, 1, 2)
        self.assertRaises(data.DataTypeError, data.set, 1, "", 2)
        self.assertRaises(data.DataTypeError, data.set, d1, 'c[1]', 2)
        self.assertRaises(data.DataTypeError, data.set, d1, 'c[1][2]', 2)
        self.assertRaises(data.DataNotFoundError, data.set, d1, 'c/f[5]', 2)
        self.assertRaises(data.DataNotFoundError, data.set, d1, 'c/f[5][2]', 2)

        d3 = {}
        e3 = data.set(d3, "does/not/exist", 123)
        self.assertEqual(d3,
                         { 'does': { 'not': { 'exist': 123 } } })
        self.assertEqual(e3,
                         { 'does': { 'not': { 'exist': 123 } } })

    def test_unset(self):
        d1 = { 'a': 'a', 'b': 1, 'c': { 'd': 'd', 'e': [ 1, 2, 3 ] } }
        data.unset(d1, 'a')
        data.unset(d1, 'c/d')
        data.unset(d1, 'does/not/exist')
        self.assertEqual(d1, { 'b': 1, 'c': { 'e': [ 1, 2, 3 ] } })
        data.unset(d1, 'c/e[0]')
        self.assertEqual(d1, { 'b': 1, 'c': { 'e': [ 2, 3 ] } })
        data.unset(d1, 'c/e[1]')
        self.assertEqual(d1, { 'b': 1, 'c': { 'e': [ 2 ] } })
        # index 1 should now be out of range
        self.assertRaises(data.DataNotFoundError, data.unset, d1, 'c/e[1]')
        d2 = { 'a': [ { 'b': [ 1, 2 ] } ] }
        data.unset(d2, 'a[0]/b[1]')
        self.assertEqual(d2, { 'a': [ { 'b': [ 1 ] } ] })
        d3 = { 'a': [ [ 1, 2 ] ] }
        data.set(d3, "a[0][1]", 3)
        self.assertEqual(d3, { 'a': [ [ 1, 3 ] ] })
        data.unset(d3, 'a[0][1]')
        self.assertEqual(d3, { 'a': [ [ 1 ] ] })
        
    def test_find_no_exc(self):
        d1 = { 'a': 'a', 'b': 1, 'c': { 'd': 'd', 'e': 2, 'more': { 'data': 'here' } } }
        self.assertEqual(data.find_no_exc(d1, ''), d1)
        self.assertEqual(data.find_no_exc(d1, 'a'), 'a')
        self.assertEqual(data.find_no_exc(d1, 'c/e'), 2)
        self.assertEqual(data.find_no_exc(d1, 'c/more/'), { 'data': 'here' })
        self.assertEqual(data.find_no_exc(d1, 'c/more/data'), 'here')
        self.assertEqual(data.find_no_exc(d1, 'c/f'), None)
        self.assertEqual(data.find_no_exc(d1, 'f'), None)
        self.assertEqual(data.find_no_exc(d1, 1), None)
        self.assertEqual(data.find_no_exc(d1, 'more/data/here'), None)
        self.assertEqual(data.find_no_exc(None, 1), None)
        self.assertEqual(data.find_no_exc("123", ""), "123")
        self.assertEqual(data.find_no_exc("123", ""), "123")
        
    def test_parse_value_str(self):
        self.assertEqual(data.parse_value_str("1"), 1)
        self.assertEqual(data.parse_value_str("true"), True)
        self.assertEqual(data.parse_value_str("null"), None)
        self.assertEqual(data.parse_value_str("1.1"), 1.1)
        self.assertEqual(data.parse_value_str("[]"), [])
        self.assertEqual(data.parse_value_str("[ 1, null, \"asdf\" ]"), [ 1, None, "asdf" ])
        self.assertEqual(data.parse_value_str("{}"), {})
        self.assertEqual(data.parse_value_str("{ \"a\": \"b\", \"c\": 1 }"), { 'a': 'b', 'c': 1 })
        self.assertEqual(data.parse_value_str("[ a c"), "[ a c")

        self.assertEqual(data.parse_value_str(1), None)


if __name__ == '__main__':
    #if not 'CONFIG_TESTDATA_PATH' in os.environ:
    #    print("You need to set the environment variable CONFIG_TESTDATA_PATH to point to the directory containing the test data files")
    #    exit(1)
    unittest.main(verbosity=2)


