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
import time
import stat
import sys
from cmdctl import *
import isc.log

assert 'CMDCTL_SRC_PATH' in os.environ,\
       "Please run this test with 'make check'"
SRC_FILE_PATH = os.environ['CMDCTL_SRC_PATH'] + os.sep

assert 'CMDCTL_BUILD_PATH' in os.environ,\
       "Please run this test with 'make check'"
BUILD_FILE_PATH = os.environ['CMDCTL_BUILD_PATH'] + os.sep

# Rewrite the class for unittest.
class MySecureHTTPRequestHandler(SecureHTTPRequestHandler):
    def __init__(self):
        self.session_id = None

    def send_response(self, rcode):
        self.rcode = rcode

    def end_headers(self):
        pass

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

# context to temporarily make a file unreadable
class UnreadableFile:
    def __init__(self, file_name):
        self.file_name = file_name
        self.orig_mode = os.stat(file_name).st_mode

    def __enter__(self):
        os.chmod(self.file_name, self.orig_mode & ~stat.S_IRUSR)

    def __exit__(self, type, value, traceback):
        os.chmod(self.file_name, self.orig_mode)

class TmpTextFile:
    """
    Context class for temporarily creating a text file with some
    lines of content.

    The file is automatically deleted if the context is left, so
    make sure to not use the path of an existing file!
    """
    def __init__(self, path, contents):
        self.__path = path
        self.__contents = contents

    def __enter__(self):
        with open(self.__path, 'w') as f:
            f.write("\n".join(self.__contents) + "\n")

    def __exit__(self, type, value, traceback):
        os.unlink(self.__path)


class TestSecureHTTPRequestHandler(unittest.TestCase):
    def setUp(self):
        self.old_stdout = sys.stdout
        sys.stdout = open(os.devnull, 'w')
        self.handler = MySecureHTTPRequestHandler()
        self.handler.server = FakeSecureHTTPServer()
        self.handler.server.user_sessions = {}
        self.handler.server._user_infos = {}
        self.handler.headers = {}
        self.handler.rfile = open('input.tmp', 'w+b')
        self.handler.wfile = open('output.tmp', 'w+b')

    def tearDown(self):
        sys.stdout.close()
        sys.stdout = self.old_stdout
        self.handler.wfile.close()
        os.remove('output.tmp')
        self.handler.rfile.close()
        os.remove('input.tmp')

    def test_is_session_valid(self):
        self.assertIsNone(self.handler.session_id)
        self.assertFalse(self.handler._is_session_valid())
        self.handler.session_id = 4234
        self.assertTrue(self.handler._is_session_valid())

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

    def test_is_user_logged_in(self):
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
        self.assertEqual(msg, ['username or password error'])

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
        self.assertEqual(msg, ['username or password error'])

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

    def test_handle_login(self):
        orig_is_user_logged_in = self.handler._is_user_logged_in
        orig_check_user_name_and_pwd = self.handler._check_user_name_and_pwd
        try:
            def create_is_user_logged_in(status):
                '''Create a replacement _is_user_logged_in() method.'''
                def my_is_user_logged_in():
                    return status
                return my_is_user_logged_in

            # Check case where _is_user_logged_in() returns True
            self.handler._is_user_logged_in = create_is_user_logged_in(True)
            self.handler.headers['cookie'] = 12345
            self.handler.path = '/login'
            self.handler.do_POST()
            self.assertEqual(self.handler.rcode, http.client.OK)
            self.handler.wfile.seek(0, 0)
            d = self.handler.wfile.read()
            self.assertEqual(json.loads(d.decode()),
                             ['user has already login'])

            # Clear the output
            self.handler.wfile.seek(0, 0)
            self.handler.wfile.truncate()

            # Check case where _is_user_logged_in() returns False
            self.handler._is_user_logged_in = create_is_user_logged_in(False)

            def create_check_user_name_and_pwd(status, error_info=None):
                '''Create a replacement _check_user_name_and_pwd() method.'''
                def my_check_user_name_and_pwd():
                    return status, error_info
                return my_check_user_name_and_pwd

            # (a) Check case where _check_user_name_and_pwd() returns
            # valid user status
            self.handler._check_user_name_and_pwd = \
                create_check_user_name_and_pwd(True)
            self.handler.do_POST()
            self.assertEqual(self.handler.rcode, http.client.OK)
            self.handler.wfile.seek(0, 0)
            d = self.handler.wfile.read()
            self.assertEqual(json.loads(d.decode()), ['login success'])

            # Clear the output
            self.handler.wfile.seek(0, 0)
            self.handler.wfile.truncate()

            # (b) Check case where _check_user_name_and_pwd() returns
            # invalid user status
            self.handler._check_user_name_and_pwd = \
                create_check_user_name_and_pwd(False, ['login failed'])
            self.handler.do_POST()
            self.assertEqual(self.handler.rcode, http.client.UNAUTHORIZED)
            self.handler.wfile.seek(0, 0)
            d = self.handler.wfile.read()
            self.assertEqual(json.loads(d.decode()), ['login failed'])

        finally:
            self.handler._is_user_logged_in = orig_is_user_logged_in
            self.handler._check_user_name_and_pwd = orig_check_user_name_and_pwd

class MockSession:
    """Act like isc.cc.Session, stealing group_sendmsg/recvmsg().

    The initial simple version only records given parameters in
    group_sendmsg() for later inspection and raise a timeout exception
    from recvmsg().  As we see the need for more test cases these methods
    should be extended.

    """
    def __init__(self, sent_messages):
        self.__sent_messages = sent_messages

    def group_sendmsg(self, msg, module_name, want_answer):
        self.__sent_messages.append((msg, module_name))

    def group_recvmsg(self, nonblock, seq):
        raise isc.cc.session.SessionTimeout('dummy timeout')

class MyCommandControl(CommandControl):
    def __init__(self, httpserver, verbose):
        super().__init__(httpserver, verbose)
        self.sent_messages = [] # for inspection; allow tests to see it
        self._cc = MockSession(self.sent_messages)

    def _get_modules_specification(self):
        return {}

    def _get_config_data_from_config_manager(self):
        return {}

    def _setup_session(self):
        spec_file = BUILD_FILE_PATH + 'cmdctl.spec'
        module_spec = isc.config.module_spec_from_file(spec_file)
        config = isc.config.config_data.ConfigData(module_spec)
        self._module_name = 'Cmdctl'
        self._cmdctl_config_data = config.get_full_config()

    def _handle_msg_from_msgq(self):
        pass

    def _start_msg_handle_thread(self): # just not bother to be threads
        pass

    def _get_current_thread(self):
        return None

class TestCommandControl(unittest.TestCase):

    def setUp(self):
        self.old_stdout = sys.stdout
        sys.stdout = open(os.devnull, 'w')
        self.cmdctl = MyCommandControl(None, True)

    def tearDown(self):
        sys.stdout.close()
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

    def test_command_handler_spec_update(self):
        # Should not be present
        self.assertFalse("foo" in self.cmdctl.modules_spec)

        answer = self.cmdctl.command_handler(
            ccsession.COMMAND_MODULE_SPECIFICATION_UPDATE, [ "foo", {} ])
        rcode, msg = ccsession.parse_answer(answer)
        self.assertEqual(rcode, 0)
        self.assertEqual(msg, None)

        # Should now be present
        self.assertTrue("foo" in self.cmdctl.modules_spec)

        # When sending specification 'None', it should be removed
        answer = self.cmdctl.command_handler(
            ccsession.COMMAND_MODULE_SPECIFICATION_UPDATE, [ "foo", None ])
        rcode, msg = ccsession.parse_answer(answer)
        self.assertEqual(rcode, 0)
        self.assertEqual(msg, None)

        # Should no longer be present
        self.assertFalse("foo" in self.cmdctl.modules_spec)

        # Don't store 'None' if it wasn't there in the first place!
        answer = self.cmdctl.command_handler(
            ccsession.COMMAND_MODULE_SPECIFICATION_UPDATE, [ "foo", None ])
        rcode, msg = ccsession.parse_answer(answer)
        self.assertEqual(rcode, 1)
        self.assertEqual(msg, "No such module: foo")

        # Should still not present
        self.assertFalse("foo" in self.cmdctl.modules_spec)


    def test_check_config_handler(self):
        answer = self.cmdctl.config_handler({'non-exist': 123})
        self._check_answer(answer, 1, 'unknown config item: non-exist')

        old_env = os.environ
        os.environ['B10_FROM_SOURCE'] = '../'
        self._check_config(self.cmdctl)
        os.environ = old_env

        answer = self.cmdctl.config_handler({'key_file': '/user/non-exist_folder'})
        self._check_answer(answer, 1, "'/user/non-exist_folder' does not exist")

        answer = self.cmdctl.config_handler({'cert_file': '/user/non-exist_folder'})
        self._check_answer(answer, 1, "'/user/non-exist_folder' does not exist")

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
        # Send a command to other module.  We check an expected message
        # is sent via the session (cmdct._cc).  Due to the behavior of
        # our mock session object the anser will be "fail", but it's not
        # the subject of this test, and so it's okay.
        # TODO: more detailed cases should be tested.
        rcode, value = self.cmdctl.send_command('Init', 'shutdown', None)
        self.assertEqual(1, len(self.cmdctl.sent_messages))
        self.assertEqual(({'command': ['shutdown']}, 'Init'),
                         self.cmdctl.sent_messages[-1])
        self.assertEqual(1, rcode)

        # Send a command to cmdctl itself.  Should be the same effect.
        rcode, value = self.cmdctl.send_command('Cmdctl', 'print_settings',
                                                None)
        self.assertEqual(2, len(self.cmdctl.sent_messages))
        self.assertEqual(({'command': ['print_settings']}, 'Cmdctl'),
                         self.cmdctl.sent_messages[-1])
        self.assertEqual(1, rcode)

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
        # both sys.stdout and sys.stderr are the same, so closing one is
        # sufficient
        sys.stdout.close()
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

    def test_get_user_info(self):
        self.assertIsNone(self.server.get_user_info('root'))
        self.server._create_user_info(SRC_FILE_PATH + 'cmdctl-accounts.csv')
        self.assertIn('6f0c73bd33101a5ec0294b3ca39fec90ef4717fe',
                      self.server.get_user_info('root'))

        # When the file is not changed calling _create_user_info() again
        # should have no effect. In order to test this, we overwrite the
        # user-infos that were just set and make sure it isn't touched by
        # the call (so make sure it isn't set to some empty value)
        fake_users_val = { 'notinfile': [] }
        self.server._user_infos = fake_users_val
        self.server._create_user_info(SRC_FILE_PATH + 'cmdctl-accounts.csv')
        self.assertEqual(fake_users_val, self.server._user_infos)

    def test_create_user_info_changing_file_time(self):
        self.assertEqual(0, len(self.server._user_infos))

        # Create a file
        accounts_file = BUILD_FILE_PATH + 'new_file.csv'
        with TmpTextFile(accounts_file, ['root,foo,bar']):
            self.server._create_user_info(accounts_file)
            self.assertEqual(1, len(self.server._user_infos))
            self.assertTrue('root' in self.server._user_infos)

            # Make sure re-reading is a noop if file was not modified
            fake_users_val = { 'notinfile': [] }
            self.server._user_infos = fake_users_val
            self.server._create_user_info(accounts_file)
            self.assertEqual(fake_users_val, self.server._user_infos)

        # create the file again, this time read should not be a noop
        with TmpTextFile(accounts_file, ['otherroot,foo,bar']):
            # Set mtime in future
            stat = os.stat(accounts_file)
            os.utime(accounts_file, (stat.st_atime, stat.st_mtime + 10))
            self.server._create_user_info(accounts_file)
            self.assertEqual(1, len(self.server._user_infos))
            self.assertTrue('otherroot' in self.server._user_infos)

    def test_create_user_info_changing_file_name(self):
        """
        Check that the accounts file is re-read if the file name is different
        """
        self.assertEqual(0, len(self.server._user_infos))

        # Create two files
        accounts_file1 = BUILD_FILE_PATH + 'new_file.csv'
        accounts_file2 = BUILD_FILE_PATH + 'new_file2.csv'
        with TmpTextFile(accounts_file2, ['otherroot,foo,bar']):
            with TmpTextFile(accounts_file1, ['root,foo,bar']):
                self.server._create_user_info(accounts_file1)
                self.assertEqual(1, len(self.server._user_infos))
                self.assertTrue('root' in self.server._user_infos)

                # Make sure re-reading is a noop if file was not modified
                fake_users_val = { 'notinfile': [] }
                self.server._user_infos = fake_users_val
                self.server._create_user_info(accounts_file1)
                self.assertEqual(fake_users_val, self.server._user_infos)

                # But a different file should be read
                self.server._create_user_info(accounts_file2)
                self.assertEqual(1, len(self.server._user_infos))
                self.assertTrue('otherroot' in self.server._user_infos)

    def test_create_user_info_nonexistent_file(self):
        # Even if there was data initially, if set to a nonexistent
        # file it should result in no users
        accounts_file = BUILD_FILE_PATH + 'new_file.csv'
        self.assertFalse(os.path.exists(accounts_file))
        fake_users_val = { 'notinfile': [] }
        self.server._user_infos = fake_users_val
        self.server._create_user_info(accounts_file)
        self.assertEqual({}, self.server._user_infos)

        # Should it now be created it should be read
        with TmpTextFile(accounts_file, ['root,foo,bar']):
            self.server._create_user_info(accounts_file)
            self.assertEqual(1, len(self.server._user_infos))
            self.assertTrue('root' in self.server._user_infos)

    def test_check_file(self):
        # Just some file that we know exists
        file_name = BUILD_FILE_PATH + 'cmdctl-keyfile.pem'
        check_file(file_name)
        with UnreadableFile(file_name):
            self.assertRaises(CmdctlException, check_file, file_name)
        self.assertRaises(CmdctlException, check_file, '/local/not-exist')
        self.assertRaises(CmdctlException, check_file, '/')


    def test_check_key_and_cert(self):
        keyfile = BUILD_FILE_PATH + 'cmdctl-keyfile.pem'
        certfile = BUILD_FILE_PATH + 'cmdctl-certfile.pem'

        # no exists
        self.assertRaises(CmdctlException, self.server._check_key_and_cert,
                          keyfile, '/local/not-exist')
        self.assertRaises(CmdctlException, self.server._check_key_and_cert,
                         '/local/not-exist', certfile)

        # not a file
        self.assertRaises(CmdctlException, self.server._check_key_and_cert,
                          keyfile, '/')
        self.assertRaises(CmdctlException, self.server._check_key_and_cert,
                         '/', certfile)

        # no read permission
        with UnreadableFile(certfile):
            self.assertRaises(CmdctlException,
                              self.server._check_key_and_cert,
                              keyfile, certfile)

        with UnreadableFile(keyfile):
            self.assertRaises(CmdctlException,
                              self.server._check_key_and_cert,
                              keyfile, certfile)

        # All OK (also happens to check the context code above works)
        self.server._check_key_and_cert(keyfile, certfile)

    def test_wrap_sock_in_ssl_context(self):
        sock = socket.socket()

        # Bad files should result in a socket.error raised by our own
        # code in the basic file checks
        self.assertRaises(socket.error,
                          self.server._wrap_socket_in_ssl_context,
                          sock,
                          'no_such_file', 'no_such_file')

        # Using a non-certificate file would cause an SSLError, which
        # is caught by our code which then raises a basic socket.error
        self.assertRaises(socket.error,
                          self.server._wrap_socket_in_ssl_context,
                          sock,
                          BUILD_FILE_PATH + 'cmdctl.py',
                          BUILD_FILE_PATH + 'cmdctl-certfile.pem')

        # Should succeed
        sock1 = socket.socket()
        ssl_sock = self.server._wrap_socket_in_ssl_context(sock1,
                                   BUILD_FILE_PATH + 'cmdctl-keyfile.pem',
                                   BUILD_FILE_PATH + 'cmdctl-certfile.pem')
        self.assertTrue(isinstance(ssl_sock, ssl.SSLSocket))

        # wrap_socket can also raise IOError, which should be caught and
        # handled like the other errors.
        # Force this by temporarily disabling our own file checks
        orig_check_func = self.server._check_key_and_cert
        try:
            self.server._check_key_and_cert = lambda x,y: None
            self.assertRaises(socket.error,
                              self.server._wrap_socket_in_ssl_context,
                              sock,
                              'no_such_file', 'no_such_file')
        finally:
            self.server._check_key_and_cert = orig_check_func

class TestFuncNotInClass(unittest.TestCase):
    def test_check_port(self):
        self.assertRaises(OptionValueError, check_port, None, 'port', -1, None)
        self.assertRaises(OptionValueError, check_port, None, 'port', 65536, None)
        self.assertRaises(OptionValueError, check_addr, None, 'ipstr', 'a.b.d', None)
        self.assertRaises(OptionValueError, check_addr, None, 'ipstr', '1::0:a.b', None)


if __name__== "__main__":
    isc.log.resetUnitTestRootLogger()
    unittest.main()


