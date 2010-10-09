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

import unittest
from isc.utils.serve_mixin import ServeMixIn
import socketserver
import threading
import socket
import time

class MyHandler(socketserver.BaseRequestHandler):
    def handle(self):
        data = self.request.recv(20)
        self.request.send(data)

class MyServer(ServeMixIn, 
               socketserver.ThreadingMixIn,
               socketserver.TCPServer):

    def __init__(self, server_addr, handler_class):
        ServeMixIn.__init__(self)
        socketserver.TCPServer.__init__(self, server_addr, handler_class)

def send_and_get_reply(ip, port, msg):
    sock = socket.socket(socket.AF_INET, socket.SOCK_STREAM)
    sock.connect((ip, port))
    sock.send(msg)
    response = sock.recv(20)
    sock.close()
    return response

class TestServeMixIn(unittest.TestCase):
    def test_serve_forever(self):
        # use port 0 to select an arbitrary unused port.
        server = MyServer(('127.0.0.1', 0), MyHandler)
        ip, port = server.server_address
        server_thread = threading.Thread(target=server.serve_forever)
        server_thread.setDaemon(True)
        server_thread.start()

        msg = b'senddata'
        self.assertEqual(msg, send_and_get_reply(ip, port, msg))
        self.assertTrue(server_thread.is_alive())

        # Now shutdown the server
        server.shutdown()
        # Sleep a while, make sure the thread has finished.
        time.sleep(0.1)
        self.assertFalse(server_thread.is_alive())

if __name__== "__main__":
    unittest.main()


