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
from cmdctl import *

# Rewrite the class for unittest.
class MySecureHTTPRequestHandler(SecureHTTPRequestHandler):
    def __init__(self):
        pass

    def send_response(self, rcode):
        self.rcode = rcode
    
    def end_headers(self):
        pass

    def do_GET(self):
        self.wfile = open('tmp.file', 'wb')
        super().do_GET()
        self.wfile.close()
        os.remove('tmp.file')

    def do_POST(self):
        self.wfile = open("tmp.file", 'wb')
        super().do_POST()
        self.wfile.close()
        os.remove('tmp.file')
    

class MySecureHTTPServer(SecureHTTPServer):
    def __init__(self):
        self.user_sessions = {}
        self.idle_timeout = 1200
        self.cmdctrl = MyCommandControl()
        self._verbose = False

class MyCommandControl(CommandControl):
    def __init__(self):
        self.config_data = {}
        self.module_spec = {}

    def send_command(self, mod, cmd, param):
        return 0, {}


class TestSecureHTTPRequestHandler(unittest.TestCase):
    def setUp(self):
        self.handler = MySecureHTTPRequestHandler()
        self.handler.server = MySecureHTTPServer()
        self.handler.server.user_sessions = {}
        self.handler.server.user_infos = {}
        self.handler.headers = {}

    def test_parse_request_path(self):
        self.handler.path = ''
        mod, cmd = self.handler._parse_request_path()
        self.assertTrue((mod == None) and (cmd == None))

        self.handler.path = '/abc'
        mod, cmd = self.handler._parse_request_path()
        self.assertTrue((mod == 'abc') and (cmd == None))
        
        self.handler.path = '/abc/edf'
        mod, cmd = self.handler._parse_request_path()
        self.assertTrue((mod == 'abc') and (cmd == 'edf'))

        self.handler.path = '/abc/edf/ghi'
        mod, cmd = self.handler._parse_request_path()
        self.assertTrue((mod == 'abc') and (cmd == 'edf'))

    def test_parse_request_path_1(self):
        self.handler.path = '/ab*c'
        mod, cmd = self.handler._parse_request_path()
        self.assertTrue((mod == 'ab') and cmd == None)

        self.handler.path = '/abc/ed*fdd/ddd'
        mod, cmd = self.handler._parse_request_path()
        self.assertTrue((mod == 'abc') and cmd == 'ed')

        self.handler.path = '/-*/edfdd/ddd'
        mod, cmd = self.handler._parse_request_path()
        self.assertTrue((mod == None) and (cmd == None))

        self.handler.path = '/-*/edfdd/ddd'
        mod, cmd = self.handler._parse_request_path()
        self.assertTrue((mod == None) and (cmd == None))

    def test_do_GET(self):
        self.handler.do_GET()
        self.assertEqual(self.handler.rcode, http.client.BAD_REQUEST)    
        
    def test_do_GET_1(self):
        self.handler.headers['cookie'] = 12345
        self.handler.do_GET()
        self.assertEqual(self.handler.rcode, http.client.UNAUTHORIZED)    

    def test_do_GET_2(self):
        self.handler.headers['cookie'] = 12345
        self.handler.server.user_sessions[12345] = time.time() + 1000000
        self.handler.path = '/how/are'
        self.handler.do_GET()
        self.assertEqual(self.handler.rcode, http.client.NO_CONTENT)    
    
    def test_do_GET_3(self):
        self.handler.headers['cookie'] = 12346
        self.handler.server.user_sessions[12346] = time.time() + 1000000
        path_vec = ['config_data', 'module_spec']
        for path in path_vec:
            self.handler.path = '/' + path
            self.handler.do_GET()
            self.assertEqual(self.handler.rcode, http.client.OK)    
    
    def test_user_logged_in(self):
        self.handler.server.user_sessions = {}
        self.handler.session_id = 12345
        self.assertTrue(self.handler._is_user_logged_in() == False)

        self.handler.server.user_sessions[12345] = time.time()
        self.assertTrue(self.handler._is_user_logged_in())

        self.handler.server.user_sessions[12345] = time.time() - 1500
        self.handler.idle_timeout = 1200
        self.assertTrue(self.handler._is_user_logged_in() == False)

    def test_check_user_name_and_pwd(self):
        self.handler.headers = {}
        ret, msg = self.handler._check_user_name_and_pwd()
        self.assertTrue(ret == False)
        self.assertEqual(msg, ['invalid username or password'])

    def test_check_user_name_and_pwd_1(self):
        self.handler.rfile = open("check.tmp", 'w+b')
        user_info = {'username':'root', 'password':'abc123'}
        len = self.handler.rfile.write(json.dumps(user_info).encode())
        self.handler.headers['Content-Length'] = len
        self.handler.rfile.seek(0, 0)

        self.handler.server.user_infos['root'] = ['aa', 'aaa']
        ret, msg = self.handler._check_user_name_and_pwd()
        self.assertTrue(ret == False)
        self.assertEqual(msg, ['password doesn\'t match'])
        self.handler.rfile.close()
        os.remove('check.tmp')

    def test_check_user_name_and_pwd_2(self):
        self.handler.rfile = open("check.tmp", 'w+b')
        user_info = {'username':'root', 'password':'abc123'}
        len = self.handler.rfile.write(json.dumps(user_info).encode())
        self.handler.headers['Content-Length'] = len - 1
        self.handler.rfile.seek(0, 0)

        ret, msg = self.handler._check_user_name_and_pwd()
        self.assertTrue(ret == False)
        self.assertEqual(msg, ['invalid username or password'])
        self.handler.rfile.close()
        os.remove('check.tmp')

    def test_check_user_name_and_pwd_3(self):
        self.handler.rfile = open("check.tmp", 'w+b')
        user_info = {'usernae':'root', 'password':'abc123'}
        len = self.handler.rfile.write(json.dumps(user_info).encode())
        self.handler.headers['Content-Length'] = len
        self.handler.rfile.seek(0, 0)

        ret, msg = self.handler._check_user_name_and_pwd()
        self.assertTrue(ret == False)
        self.assertEqual(msg, ['need user name'])
        self.handler.rfile.close()
        os.remove('check.tmp')

    def test_check_user_name_and_pwd_4(self):
        self.handler.rfile = open("check.tmp", 'w+b')
        user_info = {'username':'root', 'pssword':'abc123'}
        len = self.handler.rfile.write(json.dumps(user_info).encode())
        self.handler.headers['Content-Length'] = len
        self.handler.rfile.seek(0, 0)

        self.handler.server.user_infos['root'] = ['aa', 'aaa']
        ret, msg = self.handler._check_user_name_and_pwd()
        self.assertTrue(ret == False)
        self.assertEqual(msg, ['need password'])
        self.handler.rfile.close()
        os.remove('check.tmp')

    def test_check_user_name_and_pwd_5(self):
        self.handler.rfile = open("check.tmp", 'w+b')
        user_info = {'username':'root', 'password':'abc123'}
        len = self.handler.rfile.write(json.dumps(user_info).encode())
        self.handler.headers['Content-Length'] = len
        self.handler.rfile.seek(0, 0)

        ret, msg = self.handler._check_user_name_and_pwd()
        self.assertTrue(ret == False)
        self.assertEqual(msg, ['user doesn\'t exist'])
        self.handler.rfile.close()
        os.remove('check.tmp')

    def test_do_POST(self):
        self.handler.headers = {}
        self.handler.do_POST()
        self.assertEqual(self.handler.rcode, http.client.BAD_REQUEST)

    def test_do_POST_1(self):
        self.handler.headers = {}
        self.handler.headers['cookie'] = 12345
        self.handler.path = '/'
        self.handler.do_POST()
        self.assertEqual(self.handler.rcode, http.client.UNAUTHORIZED)

    def test_handle_post_request(self):
        self.handler.path = '/cfgmgr/revert'
        self.handler.headers = {}
        rcode, reply = self.handler._handle_post_request()
        self.assertEqual(http.client.BAD_REQUEST, rcode)

    def test_handle_post_request_1(self):
        self.handler.path = '/*d/revert'
        self.handler.headers = {}
        rcode, reply = self.handler._handle_post_request()
        self.assertEqual(http.client.BAD_REQUEST, rcode)

    def test_handle_post_request_2(self):
        self.handler.rfile = open("check.tmp", 'w+b')
        params = {123:'param data'}
        len = self.handler.rfile.write(json.dumps(params).encode())
        self.handler.headers['Content-Length'] = len
        self.handler.rfile.seek(0, 0)
        self.handler.rfile.close()
        os.remove('check.tmp')

        self.handler.path = '/module/command'
        self.handler.server.cmdctrl.module_spec = {}
        self.handler.server.cmdctrl.module_spec['module'] = { 'commands': [{'command_name':'command'}, {'command_name': ['data1']} ] }
        rcode, reply = self.handler._handle_post_request()
        self.assertEqual(http.client.OK, rcode)

if __name__== "__main__":
    unittest.main()
