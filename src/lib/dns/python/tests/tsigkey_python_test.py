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

# $Id$

import unittest
from pydnspp import *

class TSIGKeyTest(unittest.TestCase):
    key_name = Name('example.com')
    secret = b'anotherRandomData'

    def test_algorithm_names(self):
        self.assertEqual(Name('hmac-md5.sig-alg.reg.int'),
                         TSIGKey.HMACMD5_NAME)
        self.assertEqual(Name('hmac-sha1'), TSIGKey.HMACSHA1_NAME)
        self.assertEqual(Name('hmac-sha256'), TSIGKey.HMACSHA256_NAME)

    def test_init(self):
        key = TSIGKey(self.key_name, TSIGKey.HMACMD5_NAME, self.secret)
        self.assertEqual(self.key_name, key.get_key_name())
        self.assertEqual(Name('hmac-md5.sig-alg.reg.int'),
                         key.get_algorithm_name())
        self.assertEqual(self.secret, key.get_secret())

        self.assertRaises(InvalidParameter, TSIGKey, self.key_name,
                          Name('unknown-alg'), self.secret)

        self.assertEqual('hmac-sha1.',
                         TSIGKey(self.key_name, TSIGKey.HMACSHA1_NAME,
                                 self.secret).get_algorithm_name().to_text())

        self.assertRaises(TypeError, TSIGKey, self.key_name,
                          TSIGKey.HMACMD5_NAME,
                          'should be binary') # signature mismatch

class TSIGKeyRingTest(unittest.TestCase):
    key_name = Name('example.com')
    secret = b'someRandomData'

    def setUp(self):
        self.keyring = TSIGKeyRing()

    def test_init(self):
        self.assertEqual(0, self.keyring.size())
        self.assertRaises(TypeError, TSIGKeyRing, 1)
        self.assertRaises(TypeError, TSIGKeyRing, 'there should not be arg')

    def test_add(self):
        self.assertEqual(TSIGKeyRing.SUCCESS,
                         self.keyring.add(TSIGKey(self.key_name,
                                                  TSIGKey.HMACSHA256_NAME,
                                                  self.secret)))
        self.assertEqual(1, self.keyring.size())
        self.assertEqual(TSIGKeyRing.EXIST,
                         self.keyring.add(TSIGKey(self.key_name,
                                                  TSIGKey.HMACSHA256_NAME,
                                                  self.secret)))
        self.assertEqual(TSIGKeyRing.EXIST,
                         self.keyring.add(TSIGKey(self.key_name,
                                                  TSIGKey.HMACSHA1_NAME,
                                                  self.secret)))
        self.assertEqual(TSIGKeyRing.EXIST,
                         self.keyring.add(TSIGKey(Name('EXAMPLE.COM'),
                                                  TSIGKey.HMACSHA1_NAME,
                                                  self.secret)))
        self.assertEqual(1, self.keyring.size())

    def test_add_more(self):
        self.assertEqual(TSIGKeyRing.SUCCESS,
                         self.keyring.add(TSIGKey(self.key_name,
                                                  TSIGKey.HMACSHA256_NAME,
                                                  self.secret)))
        self.assertEqual(TSIGKeyRing.SUCCESS,
                         self.keyring.add(TSIGKey(Name('another.example'),
                                                  TSIGKey.HMACMD5_NAME,
                                                  self.secret)))
        self.assertEqual(TSIGKeyRing.SUCCESS,
                         self.keyring.add(TSIGKey(Name('more.example'),
                                                  TSIGKey.HMACSHA1_NAME,
                                                  self.secret)))
        self.assertEqual(3, self.keyring.size())

        self.assertRaises(TypeError, self.keyring.add, 1)
        self.assertRaises(TypeError, self.keyring.add, 'invalid arg')

    def test_remove(self):
        self.assertEqual(TSIGKeyRing.SUCCESS,
                         self.keyring.add(TSIGKey(self.key_name,
                                                  TSIGKey.HMACSHA256_NAME,
                                                  self.secret)))
        self.assertEqual(TSIGKeyRing.SUCCESS,
                         self.keyring.remove(self.key_name))
        self.assertEqual(TSIGKeyRing.NOTFOUND,
                         self.keyring.remove(self.key_name))

        self.assertRaises(TypeError, self.keyring.add, 1)
        self.assertRaises(TypeError, self.keyring.add, 'invalid arg')
        self.assertRaises(TypeError, self.keyring.add, self.key_name, 0)

    def test_remove_from_some(self):
        self.assertEqual(TSIGKeyRing.SUCCESS,
                         self.keyring.add(TSIGKey(self.key_name,
                                                  TSIGKey.HMACSHA256_NAME,
                                                  self.secret)))
        self.assertEqual(TSIGKeyRing.SUCCESS,
                         self.keyring.add(TSIGKey(Name('another.example'),
                                                  TSIGKey.HMACMD5_NAME,
                                                  self.secret)))
        self.assertEqual(TSIGKeyRing.SUCCESS,
                         self.keyring.add(TSIGKey(Name('more.example'),
                                                  TSIGKey.HMACSHA1_NAME,
                                                  self.secret)))

        self.assertEqual(TSIGKeyRing.SUCCESS,
                         self.keyring.remove(Name('another.example')))
        self.assertEqual(TSIGKeyRing.NOTFOUND,
                         self.keyring.remove(Name('noexist.example')))
        self.assertEqual(2, self.keyring.size())

    def test_find(self):
        self.assertEqual((TSIGKeyRing.NOTFOUND, None),
                         self.keyring.find(self.key_name))

        self.assertEqual(TSIGKeyRing.SUCCESS,
                         self.keyring.add(TSIGKey(self.key_name,
                                                  TSIGKey.HMACSHA256_NAME,
                                                  self.secret)))
        (code, key) = self.keyring.find(self.key_name)
        self.assertEqual(TSIGKeyRing.SUCCESS, code)
        self.assertEqual(self.key_name, key.get_key_name())
        self.assertEqual(TSIGKey.HMACSHA256_NAME, key.get_algorithm_name())
        self.assertEqual(self.secret, key.get_secret())

        self.assertRaises(TypeError, self.keyring.find, 1)
        self.assertRaises(TypeError, self.keyring.find, 'should be a name')
        self.assertRaises(TypeError, self.keyring.find, self.key_name, 0)

    def test_find_from_some(self):
        self.assertEqual(TSIGKeyRing.SUCCESS,
                         self.keyring.add(TSIGKey(self.key_name,
                                                  TSIGKey.HMACSHA256_NAME,
                                                  self.secret)))
        self.assertEqual(TSIGKeyRing.SUCCESS,
                         self.keyring.add(TSIGKey(Name('another.example'),
                                                  TSIGKey.HMACMD5_NAME,
                                                  self.secret)))
        self.assertEqual(TSIGKeyRing.SUCCESS,
                         self.keyring.add(TSIGKey(Name('more.example'),
                                                  TSIGKey.HMACSHA1_NAME,
                                                  self.secret)))

        (code, key) = self.keyring.find(Name('another.example'))
        self.assertEqual(TSIGKeyRing.SUCCESS, code)
        self.assertEqual(Name('another.example'), key.get_key_name())
        self.assertEqual(TSIGKey.HMACMD5_NAME, key.get_algorithm_name())

        self.assertEqual((TSIGKeyRing.NOTFOUND, None),
                         self.keyring.find(Name('noexist.example')))

if __name__ == '__main__':
    unittest.main()
