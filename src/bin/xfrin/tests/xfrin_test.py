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

# An axfr response of the simple zone "example.com(without soa record at the end)."
axfr_response1 = b'\x84\x00\x00\x01\x00\x06\x00\x00\x00\x00\x07example\x03com\x00\x00\xfc\x00\x01\xc0\x0c\x00\x06\x00\x01\x00\x00\x0e\x10\x00$\x05dns01\xc0\x0c\x05admin\xc0\x0c\x00\x00\x04\xd2\x00\x00\x0e\x10\x00\x00\x07\x08\x00$\xea\x00\x00\x00\x1c \xc0\x0c\x00\x02\x00\x01\x00\x00\x0e\x10\x00\x02\xc0)\xc0)\x00\x01\x00\x01\x00\x00\x0e\x10\x00\x04\xc0\xa8\x02\x02\x04sql1\xc0\x0c\x00\x02\x00\x01\x00\x00\x0e\x10\x00\x02\xc0)\x04sql2\xc0\x0c\x00\x02\x00\x01\x00\x00\x0e\x10\x00\x02\xc0)\x03ns1\x07subzone\xc0\x0c\x00\x01\x00\x01\x00\x00\x0e\x10\x00\x04\xc0\xa8\x03\x01'

# The second axfr response with only the end soa record.
axfr_response2 = b'\x84\x00\x00\x00\x00\x01\x00\x00\x00\x00\x07example\x03com\x00\x00\x06\x00\x01\x00\x00\x0e\x10\x00$\x05dns01\xc0\x0c\x05admin\xc0\x0c\x00\x00\x04\xd2\x00\x00\x0e\x10\x00\x00\x07\x08\x00$\xea\x00\x00\x00\x1c '

DB_FILE = 'db_file'
# Rewrite the class for unittest.
class MyXfrin(Xfrin):
    def __init__(self):
        pass

class MyXfrinConnection(XfrinConnection):
    query_data = b''
    eply_data = b''

    def _handle_xfrin_response(self):
        for rr in super()._handle_xfrin_response():
            pass

    def _get_request_response(self, size):
        ret = self.reply_data[:size]
        self.reply_data = self.reply_data[size:]
        if (len(ret) < size):
            raise XfrinException('cannot get reply data')
        return ret

    def send(self, data):
        self.query_data += data
        return len(data)

    def create_response_data(self, data):
        reply_data = self.query_data[2:4] + data
        size = socket.htons(len(reply_data))
        reply_data = struct.pack('H', size) + reply_data
        return reply_data


class TestXfrinConnection(unittest.TestCase):
    def setUp(self):
        self.conn = MyXfrinConnection('example.com.', DB_FILE, threading.Event(), '1.1.1.1')

    def test_response_with_invalid_msg(self):
        self.conn.data_exchange = b'aaaxxxx'
        self.assertRaises(Exception, self.conn._handle_xfrin_response)

    def test_response_without_end_soa(self):
        self.conn._send_query(RRType.AXFR())
        self.conn.reply_data = self.conn.create_response_data(axfr_response1) 
        self.assertRaises(XfrinException, self.conn._handle_xfrin_response)

    def test_response(self):
        self.conn._send_query(RRType.AXFR())
        self.conn.reply_data = self.conn.create_response_data(axfr_response1) 
        self.conn.reply_data += self.conn.create_response_data(axfr_response2) 
        self.conn._handle_xfrin_response()

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
    try:
        unittest.main()
        os.remove(DB_FILE)
    except KeyboardInterrupt as e:
        print(e)

