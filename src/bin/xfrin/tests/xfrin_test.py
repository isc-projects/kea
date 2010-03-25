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
import socket
from xfrin import *

# Rewrite the class for unittest.
class MyXfrin(Xfrin):
    def __init__(self):
        pass


class TestXfrin(unittest.TestCase):
    def test_parse_cmd_params(self):
        xfr = MyXfrin()
        args = {}
        args['zone_name'] = 'sd.cn.'
        args['port'] = '12345'
        args['master'] = '218.241.108.122'
        args['db_file'] = '/home/tt'

        name, master, port, db_file = xfr._parse_cmd_params(args)
        self.assertEqual(port, 12345)
        self.assertEqual(name, 'sd.cn.')
        self.assertEqual(master, '218.241.108.122')
        self.assertEqual(db_file, '/home/tt')

    def test_parse_cmd_params_1(self):
        xfr = MyXfrin()
        args = {}
        args['port'] = '12345'
        args['master'] = '218.241.108.122'
        args['db_file'] = '/home/tt'

        self.assertRaises(XfrinException, xfr._parse_cmd_params, args)
        self.assertRaises(XfrinException, xfr._parse_cmd_params, {'zone_name':'ds.cn.', 'master':'3.3.3'})
        self.assertRaises(XfrinException, xfr._parse_cmd_params, {'zone_name':'ds.cn.'})
        self.assertRaises(XfrinException, xfr._parse_cmd_params, {'master':'ds.cn.'})


if __name__== "__main__":
    unittest.main()
