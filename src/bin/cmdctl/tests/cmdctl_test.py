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
import tempfile
import sys
from cmdctl import *

SPEC_FILE_PATH = '..' + os.sep
if 'CMDCTL_SPEC_PATH' in os.environ:
    SPEC_FILE_PATH = os.environ['CMDCTL_SPEC_PATH'] + os.sep

SRC_FILE_PATH = '..' + os.sep
if 'CMDCTL_SRC_PATH' in os.environ:
    SRC_FILE_PATH = os.environ['CMDCTL_SRC_PATH'] + os.sep

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
    

class FakeSecureHTTPServer(SecureHTTPServer):
    def __init__(self):
        self.user_sessions = {}
        self.cmdctl = FakeCommandControlForTestRequestHandler()
        self._verbose = True 
        self._user_infos = {}
        self.idle_timeout = 1200
        self._lock = threading.Lock()

class FakeCommandControlForTestRequestHandler(CommandControl):
    def __init__(self):
        self._config_data = {}
        self.modules_spec = {}
        self._lock = threading.Lock()

    def send_command(self, mod, cmd, param):
        return 0, {}


class TestSecureHTTPRequestHandler(unittest.TestCase):
    def setUp(self):
        self.old_stdout = sys.stdout
        sys.stdout = open(os.devnull, 'w')
        self.handler = MySecureHTTPRequestHandler()
        self.handler.server = FakeSecureHTTPServer()
        self.handler.server.user_sessions = {}
        self.handler.server._user_infos = {}
        self.handler.headers = {}
        self.handler.rfile = open("check.tmp", 'w+b')

    def tearDown(self):
        sys.stdout = self.old_stdout
        self.handler.rfile.close()
        os.remove('check.tmp')

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
        self.assertFalse(ret)
        self.assertEqual(msg, ['invalid username or password'])

    def test_check_user_name_and_pwd_1(self):
        user_info = {'username':'root', 'password':'abc123'}
        len = self.handler.rfile.write(json.dumps(user_info).encode())
        self.handler.headers['Content-Length'] = len
        self.handler.rfile.seek(0, 0)

        self.handler.server._user_infos['root'] = ['aa', 'aaa']
        ret, msg = self.handler._check_user_name_and_pwd()
        self.assertFalse(ret)
        self.assertEqual(msg, ['password doesn\'t match'])

    def test_check_user_name_and_pwd_2(self):
        user_info = {'username':'root', 'password':'abc123'}
        len = self.handler.rfile.write(json.dumps(user_info).encode())
        self.handler.headers['Content-Length'] = len - 1
        self.handler.rfile.seek(0, 0)

        ret, msg = self.handler._check_user_name_and_pwd()
        self.assertFalse(ret)
        self.assertEqual(msg, ['invalid username or password'])

    def test_check_user_name_and_pwd_3(self):
        user_info = {'usernae':'root', 'password':'abc123'}
        len = self.handler.rfile.write(json.dumps(user_info).encode())
        self.handler.headers['Content-Length'] = len
        self.handler.rfile.seek(0, 0)

        ret, msg = self.handler._check_user_name_and_pwd()
        self.assertFalse(ret)
        self.assertEqual(msg, ['need user name'])

    def test_check_user_name_and_pwd_4(self):
        user_info = {'username':'root', 'pssword':'abc123'}
        len = self.handler.rfile.write(json.dumps(user_info).encode())
        self.handler.headers['Content-Length'] = len
        self.handler.rfile.seek(0, 0)

        self.handler.server._user_infos['root'] = ['aa', 'aaa']
        ret, msg = self.handler._check_user_name_and_pwd()
        self.assertFalse(ret)
        self.assertEqual(msg, ['need password'])

    def test_check_user_name_and_pwd_5(self):
        user_info = {'username':'root', 'password':'abc123'}
        len = self.handler.rfile.write(json.dumps(user_info).encode())
        self.handler.headers['Content-Length'] = len
        self.handler.rfile.seek(0, 0)

        ret, msg = self.handler._check_user_name_and_pwd()
        self.assertFalse(ret)
        self.assertEqual(msg, ['user doesn\'t exist'])

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

    def _gen_module_spec(self):
        spec = { 'commands': [ 
                  { 'command_name' :'command', 
                    'command_args': [ {
                            'item_name' : 'param1',
                            'item_type' : 'integer',
                            'item_optional' : False,
                            'item_default' : 0
                           } ],
                    'command_description' : 'cmd description'
                  }
                ] 
               }
        
        return spec

    def test_handle_post_request_2(self):
        params = {'param1':123}
        len = self.handler.rfile.write(json.dumps(params).encode())
        self.handler.headers['Content-Length'] = len

        self.handler.rfile.seek(0, 0)
        self.handler.path = '/module/command'
        self.handler.server.cmdctl.modules_spec = {}
        self.handler.server.cmdctl.modules_spec['module'] = self._gen_module_spec()
        rcode, reply = self.handler._handle_post_request()
        self.assertEqual(http.client.OK, rcode)

    def test_handle_post_request_3(self):
        params = {'param1':'abc'}
        len = self.handler.rfile.write(json.dumps(params).encode())
        self.handler.headers['Content-Length'] = len

        self.handler.rfile.seek(0, 0)
        self.handler.path = '/module/command'
        self.handler.server.cmdctl.modules_spec = {}
        self.handler.server.cmdctl.modules_spec['module'] = self._gen_module_spec()
        rcode, reply = self.handler._handle_post_request()
        self.assertEqual(http.client.BAD_REQUEST, rcode)

class MyCommandControl(CommandControl):
    def _get_modules_specification(self):
        return {}

    def _get_config_data_from_config_manager(self):
        return {}

    def _setup_session(self):
        spec_file = SPEC_FILE_PATH + 'cmdctl.spec'
        module_spec = isc.config.module_spec_from_file(spec_file)
        config = isc.config.config_data.ConfigData(module_spec)
        self._module_name = 'Cmdctl'
        self._cmdctl_config_data = config.get_full_config()

    def _handle_msg_from_msgq(self): 
        pass

class TestCommandControl(unittest.TestCase):

    def setUp(self):
        self.old_stdout = sys.stdout
        sys.stdout = open(os.devnull, 'w')
        self.cmdctl = MyCommandControl(None, True)
   
    def tearDown(self):
        sys.stdout = self.old_stdout

    def _check_config(self, cmdctl):
        key, cert, account = cmdctl.get_cmdctl_config_data()
        self.assertIsNotNone(key)
        self.assertIsNotNone(cert)
        self.assertIsNotNone(account)

    def test_get_cmdctl_config_data(self):
        old_env = os.environ
        if 'B10_FROM_SOURCE' in os.environ:
            del os.environ['B10_FROM_SOURCE']
        self.cmdctl.get_cmdctl_config_data() 
        self._check_config(self.cmdctl)
        os.environ = old_env

        old_env = os.environ
        os.environ['B10_FROM_SOURCE'] = '../'
        self._check_config(self.cmdctl)
        os.environ = old_env
    
    def test_parse_command_result(self):
        self.assertEqual({}, self.cmdctl._parse_command_result(1, {'error' : 1}))
        self.assertEqual({'a': 1}, self.cmdctl._parse_command_result(0, {'a' : 1}))

    def _check_answer(self, answer, rcode_, msg_):
        rcode, msg = ccsession.parse_answer(answer)
        self.assertEqual(rcode, rcode_)
        self.assertEqual(msg, msg_)

    def test_command_handler(self):
        answer = self.cmdctl.command_handler('unknown-command', None)
        self._check_answer(answer, 1, 'unknown command: unknown-command')

        answer = self.cmdctl.command_handler('print_settings', None)
        rcode, msg = ccsession.parse_answer(answer)
        self.assertEqual(rcode, 0)
        self.assertTrue(msg != None)

    def test_check_config_handler(self):
        answer = self.cmdctl.config_handler({'non-exist': 123})
        self._check_answer(answer, 1, 'unknown config item: non-exist')

        old_env = os.environ
        os.environ['B10_FROM_SOURCE'] = '../'
        self._check_config(self.cmdctl)
        os.environ = old_env

        answer = self.cmdctl.config_handler({'key_file': '/user/non-exist_folder'})
        self._check_answer(answer, 1, "the file doesn't exist: /user/non-exist_folder")

        answer = self.cmdctl.config_handler({'cert_file': '/user/non-exist_folder'})
        self._check_answer(answer, 1, "the file doesn't exist: /user/non-exist_folder")

        answer = self.cmdctl.config_handler({'accounts_file': '/user/non-exist_folder'})
        self._check_answer(answer, 1, 
                "Invalid accounts file: [Errno 2] No such file or directory: '/user/non-exist_folder'")

        # Test with invalid accounts file
        file_name = 'tmp.account.file'
        temp_file = open(file_name, 'w')
        writer = csv.writer(temp_file)
        writer.writerow(['a', 'b'])
        temp_file.close()
        answer = self.cmdctl.config_handler({'accounts_file': file_name})
        self._check_answer(answer, 1, "Invalid accounts file: list index out of range")
        os.remove(file_name)
    
    def test_send_command(self):
        rcode, value = self.cmdctl.send_command('Cmdctl', 'print_settings', None)
        self.assertEqual(rcode, 0)

class MySecureHTTPServer(SecureHTTPServer):
    def server_bind(self):
        pass

class TestSecureHTTPServer(unittest.TestCase):
    def setUp(self):
        self.old_stdout = sys.stdout
        self.old_stderr = sys.stderr
        sys.stdout = open(os.devnull, 'w')
        sys.stderr = sys.stdout
        self.server = MySecureHTTPServer(('localhost', 8080), 
                                         MySecureHTTPRequestHandler,
                                         MyCommandControl, verbose=True)

    def tearDown(self):
        sys.stdout = self.old_stdout
        sys.stderr = self.old_stderr

    def test_addr_in_use(self):
        server_one = None
        try:
            server_one = SecureHTTPServer(('localhost', 53531),
                                        MySecureHTTPRequestHandler,
                                        MyCommandControl)
        except CmdctlException:
            pass
        else:
            self.assertRaises(CmdctlException, SecureHTTPServer,
                              ('localhost', 53531),
                              MySecureHTTPRequestHandler, MyCommandControl)
        if server_one:
            server_one.server_close()

    def test_create_user_info(self):
        self.server._create_user_info('/local/not-exist')
        self.assertEqual(0, len(self.server._user_infos))

        self.server._create_user_info(SRC_FILE_PATH + 'cmdctl-accounts.csv')
        self.assertEqual(1, len(self.server._user_infos))
        self.assertTrue('root' in self.server._user_infos)

    def test_check_key_and_cert(self):
        self.assertRaises(CmdctlException, self.server._check_key_and_cert,
                         '/local/not-exist', 'cmdctl-keyfile.pem')

        self.server._check_key_and_cert(SRC_FILE_PATH + 'cmdctl-keyfile.pem',
                                        SRC_FILE_PATH + 'cmdctl-certfile.pem')

    def test_wrap_sock_in_ssl_context(self):
        sock = socket.socket()
        self.assertRaises(socket.error, 
                          self.server._wrap_socket_in_ssl_context,
                          sock, 
                          '../cmdctl-keyfile',
                          '../cmdctl-certfile')

        sock1 = socket.socket()
        self.server._wrap_socket_in_ssl_context(sock1, 
                          SRC_FILE_PATH + 'cmdctl-keyfile.pem',
                          SRC_FILE_PATH + 'cmdctl-certfile.pem')

class TestFuncNotInClass(unittest.TestCase):
    def test_check_port(self):
        self.assertRaises(OptionValueError, check_port, None, 'port', -1, None)        
        self.assertRaises(OptionValueError, check_port, None, 'port', 65536, None)        
        self.assertRaises(OptionValueError, check_addr, None, 'ipstr', 'a.b.d', None)        
        self.assertRaises(OptionValueError, check_addr, None, 'ipstr', '1::0:a.b', None)        


if __name__== "__main__":
    unittest.main()


