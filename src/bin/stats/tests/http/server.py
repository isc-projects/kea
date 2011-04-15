# Copyright (C) 2011  Internet Systems Consortium.
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

"""
A mock-up module of http.server

*** NOTE ***
It is only for testing stats_httpd module and not reusable for
external module.
"""

import fake_socket

class DummyHttpResponse:
    def __init__(self, path):
        self.path = path
        self.headers={}
        self.log = ""

    def _write_log(self, msg):
        self.log = self.log + msg

class HTTPServer:
    """
    A mock-up class of http.server.HTTPServer
    """
    address_family = fake_socket.AF_INET
    def __init__(self, server_class, handler_class):
        self.socket = fake_socket.socket(self.address_family)
        self.server_class = server_class
        self.socket.bind(self.server_class)
        self._handler = handler_class(None, None, self)

    def handle_request(self):
        pass

    def server_close(self):
        self.socket.close()

class BaseHTTPRequestHandler:
    """
    A mock-up class of http.server.BaseHTTPRequestHandler
    """

    def __init__(self, request, client_address, server):
        self.path = "/path/to"
        self.headers = {}
        self.server = server
        self.response = DummyHttpResponse(path=self.path)
        self.response.write = self._write
        self.wfile = self.response

    def send_response(self, code=0):
        if self.path != self.response.path:
            self.response = DummyHttpResponse(path=self.path)
        self.response.code = code

    def send_header(self, key, value):
        if self.path != self.response.path:
            self.response = DummyHttpResponse(path=self.path)
        self.response.headers[key] = value

    def end_headers(self):
        if self.path != self.response.path:
            self.response = DummyHttpResponse(path=self.path)
        self.response.wrote_headers = True

    def send_error(self, code, message=None):
        if self.path != self.response.path:
            self.response = DummyHttpResponse(path=self.path)
        self.response.code = code
        self.response.body = message

    def address_string(self):
        return 'dummyhost'

    def log_date_time_string(self):
        return '[DD/MM/YYYY HH:MI:SS]'

    def _write(self, obj):
        if self.path != self.response.path:
            self.response = DummyHttpResponse(path=self.path)
        self.response.body = obj.decode()

