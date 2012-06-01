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

'''Tests for the DDNS module'''

from isc.ddns.session import *
from isc.dns import *
from isc.acl.acl import ACCEPT
import isc.util.cio.socketsession
from isc.datasrc import DataSourceClient
import ddns
import errno
import os
import select
import shutil
import socket
import unittest

# Some common test parameters
TESTDATA_PATH = os.environ['TESTDATA_PATH'] + os.sep
READ_ZONE_DB_FILE = TESTDATA_PATH + "rwtest.sqlite3" # original, to be copied
TEST_ZONE_NAME = Name('example.org')
TEST_ZONE_NAME_STR = TEST_ZONE_NAME.to_text()
UPDATE_RRTYPE = RRType.SOA()
TEST_QID = 5353                 # arbitrary chosen
TEST_RRCLASS = RRClass.IN()
TEST_RRCLASS_STR = TEST_RRCLASS.to_text()
TEST_SERVER6 = ('2001:db8::53', 53, 0, 0)
TEST_CLIENT6 = ('2001:db8::1', 53000, 0, 0)
TEST_SERVER4 = ('192.0.2.53', 53)
TEST_CLIENT4 = ('192.0.2.1', 53534)
TEST_ZONE_RECORD = Question(TEST_ZONE_NAME, TEST_RRCLASS, UPDATE_RRTYPE)
TEST_ACL_CONTEXT = isc.acl.dns.RequestContext(
    socket.getaddrinfo("192.0.2.1", 1234, 0, socket.SOCK_DGRAM,
                       socket.IPPROTO_UDP, socket.AI_NUMERICHOST)[0][4])
# TSIG key for tests when needed.  The key name is TEST_ZONE_NAME.
TEST_TSIG_KEY = TSIGKey("example.org:SFuWd/q99SzF8Yzd1QbB9g==")
# TSIG keyring that contanins the test key
TEST_TSIG_KEYRING = TSIGKeyRing()
TEST_TSIG_KEYRING.add(TEST_TSIG_KEY)
# Another TSIG key not in the keyring, making verification fail
BAD_TSIG_KEY = TSIGKey("example.com:SFuWd/q99SzF8Yzd1QbB9g==")

class FakeSocket:
    """
    A fake socket. It only provides a file number, peer name and accept method.
    """
    def __init__(self, fileno):
        self.proto = socket.IPPROTO_UDP
        self.__fileno = fileno
        self._sent_data = None
        self._sent_addr = None
        # customizable by tests; if set to True, sendto() will throw after
        # recording the parameters.
        self._raise_on_send = False
    def fileno(self):
        return self.__fileno
    def getpeername(self):
        return "fake_unix_socket"
    def accept(self):
        return FakeSocket(self.__fileno + 1), '/dummy/path'
    def sendto(self, data, addr):
        self._sent_data = data
        self._sent_addr = addr
        if self._raise_on_send:
            raise socket.error('test socket failure')
    def clear(self):
        '''Clear internal instrumental data.'''
        self._sent_data = None
        self._sent_addr = None

class FakeSessionReceiver:
    """
    A fake socket session receiver, for our tests.
    """
    def __init__(self, socket):
        self._socket = socket
    def socket(self):
        """
        This method is not present in the real receiver, but we use it to
        inspect the socket passed to the constructor.
        """
        return self._socket

class FakeUpdateSession:
    '''A fake update session, emulating isc.ddns.session.UpdateSession.

    It provides the same interfaces as UpdateSession with skipping complicated
    internal protocol processing and returning given faked results.  This
    will help simplify test setups.

    '''
    def __init__(self, msg, client_addr, zone_config, faked_result):
        '''Faked constructor.

        It takes an additional faked_result parameter.  It will be used
        as the result value of handle().  If its value is UPDATE_ERROR,
        get_message() will create a response message whose Rcode is
        REFUSED.

        '''
        self.__msg = msg
        self.__faked_result = faked_result

    def handle(self):
        if self.__faked_result == UPDATE_SUCCESS:
            return self.__faked_result, TEST_ZONE_NAME, TEST_RRCLASS
        return self.__faked_result, None, None

    def get_message(self):
        self.__msg.make_response()
        self.__msg.clear_section(SECTION_ZONE)
        if self.__faked_result == UPDATE_SUCCESS:
            self.__msg.set_rcode(Rcode.NOERROR())
        else:
            self.__msg.set_rcode(Rcode.REFUSED())
        return self.__msg

class FakeKeyringModule:
    '''Fake the entire isc.server_common.tsig_keyring module.'''

    def init_keyring(self, cc):
        '''Set the instrumental attribute to True when called.

        It can be used for a test that confirms TSIG key initialization is
        surely performed.  This class doesn't use any CC session, so the
        cc parameter will be ignored.

        '''
        self.initialized = True

    def get_keyring(self):
        '''Simply return the predefined TSIG keyring unconditionally.'''
        return TEST_TSIG_KEYRING

class MyCCSession(isc.config.ConfigData):
    '''Fake session with minimal interface compliance.'''
    def __init__(self):
        module_spec = isc.config.module_spec_from_file(
            ddns.SPECFILE_LOCATION)
        isc.config.ConfigData.__init__(self, module_spec)
        self._started = False
        self._stopped = False
        # Used as the return value of get_remote_config_value.  Customizable.
        self.auth_db_file = READ_ZONE_DB_FILE

    def start(self):
        '''Called by DDNSServer initialization, but not used in tests'''
        self._started = True

    def send_stopping(self):
        '''Called by shutdown code'''
        self._stopped = True

    def get_socket(self):
        """
        Used to get the file number for select.
        """
        return FakeSocket(1)

    def add_remote_config(self, spec_file_name):
        pass

    def get_remote_config_value(self, module_name, item):
        if module_name == "Auth" and item == "database_file":
            return self.auth_db_file, False

class MyDDNSServer():
    '''Fake DDNS server used to test the main() function'''
    def __init__(self):
        self.reset()

    def run(self):
        '''
        Fake the run() method of the DDNS server. This will set
        self._run_called to True.
        If self._exception is not None, this is raised as an exception
        '''
        self.run_called = True
        if self._exception is not None:
            self.exception_raised = True
            raise self._exception

    def set_exception(self, exception):
        '''Set an exception to be raised when run() is called'''
        self._exception = exception

    def reset(self):
        '''(Re)set to initial values'''
        self.run_called = False
        self.exception_raised = False
        self._exception = None

class TestDDNSServer(unittest.TestCase):
    def setUp(self):
        cc_session = MyCCSession()
        self.assertFalse(cc_session._started)
        self.orig_tsig_keyring = isc.server_common.tsig_keyring
        isc.server_common.tsig_keyring = FakeKeyringModule()
        self.ddns_server = ddns.DDNSServer(cc_session)
        self.__cc_session = cc_session
        self.assertTrue(cc_session._started)
        self.__select_expected = None
        self.__select_answer = None
        self.__select_exception = None
        self.__hook_called = False
        self.ddns_server._listen_socket = FakeSocket(2)
        ddns.select.select = self.__select

    def tearDown(self):
        ddns.select.select = select.select
        ddns.isc.util.cio.socketsession.SocketSessionReceiver = \
            isc.util.cio.socketsession.SocketSessionReceiver
        isc.server_common.tsig_keyring = self.orig_tsig_keyring

    def test_listen(self):
        '''
        Test the old socket file is removed (if any) and a new socket
        is created when the ddns server is created.
        '''
        # Make sure the socket does not exist now
        ddns.clear_socket()
        # Hook the call for clearing the socket
        orig_clear = ddns.clear_socket
        ddns.clear_socket = self.__hook
        # Create the server
        ddnss = ddns.DDNSServer(MyCCSession())
        ddns.clear_socket = orig_clear
        # The socket is created
        self.assertTrue(os.path.exists(ddns.SOCKET_FILE))
        self.assertTrue(isinstance(ddnss._listen_socket, socket.socket))
        # And deletion of the socket was requested
        self.assertIsNone(self.__hook_called)
        # Now make sure the clear_socket really works
        ddns.clear_socket()
        self.assertFalse(os.path.exists(ddns.SOCKET_FILE))

    def test_initial_config(self):
        # right now, the only configuration is the zone configuration, whose
        # default should be an empty map.
        self.assertEqual({}, self.ddns_server._zone_config)

    def test_config_handler(self):
        # Update with a simple zone configuration: including an accept-all ACL
        new_config = { 'zones': [ { 'origin': TEST_ZONE_NAME_STR,
                                    'class': TEST_RRCLASS_STR,
                                    'update_acl': [{'action': 'ACCEPT'}] } ] }
        answer = self.ddns_server.config_handler(new_config)
        self.assertEqual((0, None), isc.config.parse_answer(answer))
        acl = self.ddns_server._zone_config[(TEST_ZONE_NAME, TEST_RRCLASS)]
        self.assertEqual(ACCEPT, acl.execute(TEST_ACL_CONTEXT))

        # Slightly more complicated one: containing multiple ACLs
        new_config = { 'zones': [ { 'origin': 'example.com',
                                    'class': 'CH',
                                    'update_acl': [{'action': 'REJECT',
                                                    'from': '2001:db8::1'}] },
                                  { 'origin': TEST_ZONE_NAME_STR,
                                    'class': TEST_RRCLASS_STR,
                                    'update_acl': [{'action': 'ACCEPT'}] },
                                  { 'origin': 'example.org',
                                    'class': 'CH',
                                    'update_acl': [{'action': 'DROP'}] } ] }
        answer = self.ddns_server.config_handler(new_config)
        self.assertEqual((0, None), isc.config.parse_answer(answer))
        self.assertEqual(3, len(self.ddns_server._zone_config))
        acl = self.ddns_server._zone_config[(TEST_ZONE_NAME, TEST_RRCLASS)]
        self.assertEqual(ACCEPT, acl.execute(TEST_ACL_CONTEXT))

        # empty zone config
        new_config = { 'zones': [] }
        answer = self.ddns_server.config_handler(new_config)
        self.assertEqual((0, None), isc.config.parse_answer(answer))
        self.assertEqual({}, self.ddns_server._zone_config)

        # bad zone config data: bad name.  The previous config shouls be kept.
        bad_config = { 'zones': [ { 'origin': 'bad..example',
                                    'class': TEST_RRCLASS_STR,
                                    'update_acl': [{'action': 'ACCEPT'}] } ] }
        answer = self.ddns_server.config_handler(bad_config)
        self.assertEqual(1, isc.config.parse_answer(answer)[0])
        self.assertEqual({}, self.ddns_server._zone_config)

        # bad zone config data: bad class.
        bad_config = { 'zones': [ { 'origin': TEST_ZONE_NAME_STR,
                                    'class': 'badclass',
                                    'update_acl': [{'action': 'ACCEPT'}] } ] }
        answer = self.ddns_server.config_handler(bad_config)
        self.assertEqual(1, isc.config.parse_answer(answer)[0])
        self.assertEqual({}, self.ddns_server._zone_config)

        # bad zone config data: bad ACL.
        bad_config = { 'zones': [ { 'origin': TEST_ZONE_NAME_STR,
                                    'class': TEST_RRCLASS_STR,
                                    'update_acl': [{'action': 'badaction'}]}]}
        answer = self.ddns_server.config_handler(bad_config)
        self.assertEqual(1, isc.config.parse_answer(answer)[0])
        self.assertEqual({}, self.ddns_server._zone_config)

        # the first zone cofig is valid, but not the second.  the first one
        # shouldn't be installed.
        bad_config = { 'zones': [ { 'origin': TEST_ZONE_NAME_STR,
                                    'class': TEST_RRCLASS_STR,
                                    'update_acl': [{'action': 'ACCEPT'}] },
                                  { 'origin': 'bad..example',
                                    'class': TEST_RRCLASS_STR,
                                    'update_acl': [{'action': 'ACCEPT'}] } ] }
        answer = self.ddns_server.config_handler(bad_config)
        self.assertEqual(1, isc.config.parse_answer(answer)[0])
        self.assertEqual({}, self.ddns_server._zone_config)

        # Half-broken case: 'origin, class' pair is duplicate.  For now we
        # we accept it (the latter one will win)
        dup_config = { 'zones': [ { 'origin': TEST_ZONE_NAME_STR,
                                    'class': TEST_RRCLASS_STR,
                                    'update_acl': [{'action': 'REJECT'}] },
                                  { 'origin': TEST_ZONE_NAME_STR,
                                    'class': TEST_RRCLASS_STR,
                                    'update_acl': [{'action': 'ACCEPT'}] } ] }
        answer = self.ddns_server.config_handler(dup_config)
        self.assertEqual((0, None), isc.config.parse_answer(answer))
        acl = self.ddns_server._zone_config[(TEST_ZONE_NAME, TEST_RRCLASS)]
        self.assertEqual(ACCEPT, acl.execute(TEST_ACL_CONTEXT))

    def test_shutdown_command(self):
        '''Test whether the shutdown command works'''
        self.assertFalse(self.ddns_server._shutdown)
        answer = self.ddns_server.command_handler('shutdown', None)
        self.assertEqual((0, None), isc.config.parse_answer(answer))
        self.assertTrue(self.ddns_server._shutdown)

    def test_command_handler(self):
        '''Test some commands.'''
        # this command should not exist
        answer = self.ddns_server.command_handler('bad_command', None)
        self.assertEqual((1, 'Unknown command: bad_command'),
                         isc.config.parse_answer(answer))

    def test_signal_handler(self):
        '''Test whether signal_handler calls shutdown()'''
        signal_handler = ddns.create_signal_handler(self.ddns_server)
        self.assertFalse(self.ddns_server._shutdown)
        signal_handler(None, None)
        self.assertTrue(self.ddns_server._shutdown)

    def __select(self, reads, writes, exceptions, timeout=None):
        """
        A fake select. It checks it was called with the correct parameters and
        returns a preset answer.

        If there's an exception stored in __select_exception, it is raised
        instead and the exception is cleared.
        """
        self.assertEqual(self.__select_expected, (reads, writes, exceptions,
                                                  timeout))
        if self.__select_exception is not None:
            (self.__select_exception, exception) = (None,
                                                    self.__select_exception)
            raise exception
        answer = self.__select_answer
        self.__select_answer = None
        self.ddns_server._shutdown = True
        return answer

    def __hook(self, param=None):
        """
        A hook that can be installed to any nullary or unary function and see
        if it was really called.
        """
        self.__hook_called = param

    def test_accept_called(self):
        """
        Test we call the accept function when a new connection comes.
        """
        self.ddns_server.accept = self.__hook
        self.__select_expected = ([1, 2], [], [], None)
        self.__select_answer = ([2], [], [])
        self.__hook_called = "Not called"
        self.ddns_server.run()
        self.assertTrue(self.ddns_server._shutdown)
        # The answer got used
        self.assertIsNone(self.__select_answer)
        # Reset, when called without parameter
        self.assertIsNone(self.__hook_called)

    def test_check_command_called(self):
        """
        Test the check_command is called when there's something on the
        socket.
        """
        self.__cc_session.check_command = self.__hook
        self.__select_expected = ([1, 2], [], [], None)
        self.__select_answer = ([1], [], [])
        self.ddns_server.run()
        self.assertTrue(self.ddns_server._shutdown)
        # The answer got used
        self.assertIsNone(self.__select_answer)
        # And the check_command was called with true parameter (eg.
        # non-blocking)
        self.assertTrue(self.__hook_called)

    def test_accept(self):
        """
        Test that we can accept a new connection.
        """
        # There's nothing before the accept
        ddns.isc.util.cio.socketsession.SocketSessionReceiver = \
            FakeSessionReceiver
        self.assertEqual({}, self.ddns_server._socksession_receivers)
        self.ddns_server.accept()
        # Now the new socket session receiver is stored in the dict
        # The 3 comes from _listen_socket.accept() - _listen_socket has
        # fileno 2 and accept returns socket with fileno increased by one.
        self.assertEqual([3],
                         list(self.ddns_server._socksession_receivers.keys()))
        (socket, receiver) = self.ddns_server._socksession_receivers[3]
        self.assertTrue(isinstance(socket, FakeSocket))
        self.assertEqual(3, socket.fileno())
        self.assertTrue(isinstance(receiver, FakeSessionReceiver))
        self.assertEqual(socket, receiver.socket())

    def test_accept_fail(self):
        """
        Test we don't crash if an accept fails and that we don't modify the
        internals.
        """
        # Make the accept fail
        def accept_failure():
            raise socket.error(errno.ECONNABORTED)
        orig = self.ddns_server._listen_socket.accept
        self.ddns_server._listen_socket.accept = accept_failure
        self.assertEqual({}, self.ddns_server._socksession_receivers)
        # Doesn't raise the exception
        self.ddns_server.accept()
        # And nothing is stored
        self.assertEqual({}, self.ddns_server._socksession_receivers)
        # Now make the socket receiver fail
        self.ddns_server._listen_socket.accept = orig
        def receiver_failure(sock):
            raise isc.util.cio.socketsession.SocketSessionError('Test error')
        ddns.isc.util.cio.socketsession.SocketSessionReceiver = \
            receiver_failure
        # Doesn't raise the exception
        self.ddns_server.accept()
        # And nothing is stored
        self.assertEqual({}, self.ddns_server._socksession_receivers)
        # Check we don't catch everything, so raise just an exception
        def unexpected_failure(sock):
            raise Exception('Test error')
        ddns.isc.util.cio.socketsession.SocketSessionReceiver = \
            unexpected_failure
        # This one gets through
        self.assertRaises(Exception, self.ddns_server.accept)
        # Nothing is stored as well
        self.assertEqual({}, self.ddns_server._socksession_receivers)

    def test_session_called(self):
        """
        Test the run calls handle_session when there's something on the
        socket.
        """
        socket = FakeSocket(3)
        self.ddns_server._socksession_receivers = \
            {3: (socket, FakeSessionReceiver(socket))}
        self.ddns_server.handle_session = self.__hook
        self.__select_expected = ([1, 2, 3], [], [], None)
        self.__select_answer = ([3], [], [])
        self.ddns_server.run()
        self.assertTrue(self.ddns_server._shutdown)
        self.assertTrue(self.__cc_session._stopped)
        self.assertIsNone(self.__select_answer)
        self.assertEqual(3, self.__hook_called)

    def test_handle_session_ok(self):
        """
        Test the handle_session pops the receiver and calls handle_request
        when everything is OK.
        """
        socket = FakeSocket(3)
        receiver = FakeSessionReceiver(socket)
        # It doesn't really matter what data we use here, it is only passed
        # through the code
        param = (FakeSocket(4), ('127.0.0.1', 1234), ('127.0.0.1', 1235),
                 'Some data')
        def pop():
            return param
        # Prepare data into the receiver
        receiver.pop = pop
        self.ddns_server._socksession_receivers = {3: (socket, receiver)}
        self.ddns_server.handle_request = self.__hook
        # Call it
        self.ddns_server.handle_session(3)
        # The popped data are passed into the handle_request
        self.assertEqual(param, self.__hook_called)
        # The receivers are kept the same
        self.assertEqual({3: (socket, receiver)},
                         self.ddns_server._socksession_receivers)

    def test_handle_session_fail(self):
        """
        Test the handle_session removes (and closes) the socket and receiver
        when the receiver complains.
        """
        socket = FakeSocket(3)
        receiver = FakeSessionReceiver(socket)
        def pop():
            raise isc.util.cio.socketsession.SocketSessionError('Test error')
        receiver.pop = pop
        socket.close = self.__hook
        self.__hook_called = False
        self.ddns_server._socksession_receivers = {3: (socket, receiver)}
        self.ddns_server.handle_session(3)
        # The "dead" receiver is removed
        self.assertEqual({}, self.ddns_server._socksession_receivers)
        # Close is called with no parameter, so the default None
        self.assertIsNone(self.__hook_called)

    def test_select_exception_ignored(self):
        """
        Test that the EINTR is ignored in select.
        """
        # Prepare the EINTR exception
        self.__select_exception = select.error(errno.EINTR)
        # We reuse the test here, as it should act the same. The exception
        # should just get ignored.
        self.test_check_command_called()

    def test_select_exception_fatal(self):
        """
        Test that other exceptions are fatal to the run.
        """
        # Prepare a different exception
        self.__select_exception = select.error(errno.EBADF)
        self.__select_expected = ([1, 2], [], [], None)
        self.assertRaises(select.error, self.ddns_server.run)

def create_msg(opcode=Opcode.UPDATE(), zones=[TEST_ZONE_RECORD], tsigctx=None):
    msg = Message(Message.RENDER)
    msg.set_qid(TEST_QID)
    msg.set_opcode(opcode)
    msg.set_rcode(Rcode.NOERROR())
    for z in zones:
        msg.add_question(z)

    renderer = MessageRenderer()
    if tsigctx is not None:
        msg.to_wire(renderer, tsigctx)
    else:
        msg.to_wire(renderer)

    # re-read the created data in the parse mode
    msg.clear(Message.PARSE)
    msg.from_wire(renderer.get_data())

    return renderer.get_data()


class TestDDNSession(unittest.TestCase):
    def setUp(self):
        cc_session = MyCCSession()
        self.assertFalse(cc_session._started)
        self.orig_tsig_keyring = isc.server_common.tsig_keyring
        isc.server_common.tsig_keyring = FakeKeyringModule()
        self.server = ddns.DDNSServer(cc_session)
        self.server._UpdateSessionClass = self.__fake_session_creator
        self.__faked_result = UPDATE_SUCCESS # will be returned by fake session
        self.__sock = FakeSocket(-1)

    def tearDown(self):
        self.assertTrue(isc.server_common.tsig_keyring.initialized)
        isc.server_common.tsig_keyring = self.orig_tsig_keyring

    def __fake_session_creator(self, req_message, client_addr, zone_config):
        return FakeUpdateSession(req_message, client_addr, zone_config,
                                 self.__faked_result)

    def check_update_response(self, resp_wire, expected_rcode=Rcode.NOERROR(),
                              tsig_ctx=None):
        '''Check if given wire data are valid form of update response.

        In this implementation, zone/prerequisite/update sections should be
        empty in responses.

        If tsig_ctx (isc.dns.TSIGContext) is not None, the response should
        be TSIG signed and the signature should be verifiable with the context
        that has signed the corresponding request.

        '''
        msg = Message(Message.PARSE)
        msg.from_wire(resp_wire)
        if tsig_ctx is not None:
            tsig_record = msg.get_tsig_record()
            self.assertNotEqual(None, tsig_record)
            self.assertEqual(TSIGError.NOERROR,
                             tsig_ctx.verify(tsig_record, resp_wire))
        self.assertEqual(Opcode.UPDATE(), msg.get_opcode())
        self.assertEqual(expected_rcode, msg.get_rcode())
        self.assertEqual(TEST_QID, msg.get_qid())
        for section in [SECTION_ZONE, SECTION_PREREQUISITE, SECTION_UPDATE]:
            self.assertEqual(0, msg.get_rr_count(section))

    def check_session(self, result=UPDATE_SUCCESS, ipv6=True, tsig_key=None):
        # reset test parameters
        self.__sock.clear()
        self.__faked_result = result

        server_addr = TEST_SERVER6 if ipv6 else TEST_SERVER4
        client_addr = TEST_CLIENT6 if ipv6 else TEST_CLIENT4
        tsig = TSIGContext(tsig_key) if tsig_key is not None else None
        rcode = Rcode.NOERROR() if result == UPDATE_SUCCESS else Rcode.REFUSED()
        has_response = (result != UPDATE_DROP)

        self.assertEqual(has_response,
                         self.server.handle_request((self.__sock,
                                                     server_addr, client_addr,
                                                     create_msg(tsigctx=tsig))))
        if has_response:
            self.assertEqual(client_addr, self.__sock._sent_addr)
            self.check_update_response(self.__sock._sent_data, rcode)
        else:
            self.assertEqual((None, None), (self.__sock._sent_addr,
                                            self.__sock._sent_data))

    def test_handle_request(self):
        '''Basic request handling without any unexpected errors.'''
        # Success, without TSIG
        self.check_session()
        # Update will be refused with a response.
        self.check_session(UPDATE_ERROR, ipv6=False)
        # Update will be refused and dropped
        self.check_session(UPDATE_DROP)
        # Success, with TSIG
        self.check_session(ipv6=False, tsig_key=TEST_TSIG_KEY)
        # Update will be refused with a response, with TSIG.
        self.check_session(UPDATE_ERROR, tsig_key=TEST_TSIG_KEY)
        # Update will be refused and dropped, with TSIG (doesn't matter though)
        self.check_session(UPDATE_DROP, ipv6=False, tsig_key=TEST_TSIG_KEY)

    def test_broken_request(self):
        # Message data too short
        s = self.__sock
        self.assertFalse(self.server.handle_request((self.__sock, None,
                                                     None, b'x' * 11)))
        self.assertEqual((None, None), (s._sent_data, s._sent_addr))

        # Opcode is not UPDATE
        self.assertFalse(self.server.handle_request(
                (self.__sock, None, None, create_msg(opcode=Opcode.QUERY()))))
        self.assertEqual((None, None), (s._sent_data, s._sent_addr))

        # TSIG verification error.  We use UPDATE_DROP to signal check_session
        # that no response should be given.
        self.check_session(result=UPDATE_DROP, ipv6=False,
                           tsig_key=BAD_TSIG_KEY)

    def test_socket_error(self):
        # Have the faked socket raise an exception on sendto()
        self.__sock._raise_on_send = True
        # handle_request indicates the failure
        self.assertFalse(self.server.handle_request((self.__sock, TEST_SERVER6,
                                                     TEST_SERVER4,
                                                     create_msg())))
        # this check ensures sendto() was really attempted.
        self.check_update_response(self.__sock._sent_data, Rcode.NOERROR())

    def test_tcp_request(self):
        # Right now TCP request is not supported.
        s = self.__sock
        s.proto = socket.IPPROTO_TCP
        self.assertFalse(self.server.handle_request((s, TEST_SERVER6,
                                                     TEST_SERVER4,
                                                     create_msg())))
        self.assertEqual((None, None), (s._sent_data, s._sent_addr))

    def test_session_with_config(self):
        '''Check a session with more relistic config setups

        We don't have to explore various cases in detail in this test.
        We're just checking if the expected configured objects are passed
        to the session object.

        '''

        # reset the session class to the real one
        self.server._UpdateSessionClass = isc.ddns.session.UpdateSession

        # install all-drop ACL
        new_config = { 'zones': [ { 'origin': TEST_ZONE_NAME_STR,
                                    'class': TEST_RRCLASS_STR,
                                    'update_acl': [{'action': 'DROP'}] } ] }
        answer = self.server.config_handler(new_config)
        self.assertEqual((0, None), isc.config.parse_answer(answer))

        # check the result
        self.check_session(UPDATE_DROP)

class TestMain(unittest.TestCase):
    def setUp(self):
        self._server = MyDDNSServer()
        self.__orig_clear = ddns.clear_socket
        ddns.clear_socket = self.__clear_socket
        self.__clear_called = False

    def tearDown(self):
        ddns.clear_socket = self.__orig_clear

    def test_main(self):
        self.assertFalse(self._server.run_called)
        ddns.main(self._server)
        self.assertTrue(self._server.run_called)
        self.assertTrue(self.__clear_called)

    def __clear_socket(self):
        self.__clear_called = True

    def check_exception(self, ex):
        '''Common test sequence to see if the given exception is caused.
        '''
        # Should technically not be necessary, but reset server to be sure
        self._server.reset()
        self.assertFalse(self._server.exception_raised)
        self._server.set_exception(ex)
        ddns.main(self._server)
        self.assertTrue(self._server.exception_raised)

    def test_exceptions(self):
        '''
        Test whether exceptions are caught in main()
        These exceptions should not bubble up.
        '''
        self._server.set_exception(KeyboardInterrupt())
        self.assertFalse(self._server.exception_raised)
        ddns.main(self._server)
        self.assertTrue(self._server.exception_raised)

        self.check_exception(isc.cc.SessionError("error"))
        self.check_exception(isc.config.ModuleCCSessionError("error"))
        self.check_exception(ddns.DDNSConfigError("error"))
        self.check_exception(isc.cc.SessionTimeout("error"))
        self.check_exception(Exception("error"))

        # Add one that is not a subclass of Exception, and hence not
        # caught. Misuse BaseException for that.
        self._server.reset()
        self.assertFalse(self._server.exception_raised)
        self._server.set_exception(BaseException("error"))
        self.assertRaises(BaseException, ddns.main, self._server)
        self.assertTrue(self._server.exception_raised)

class TestConfig(unittest.TestCase):
    '''Test some simple config related things that don't need server. '''
    def setUp(self):
        self.__ccsession = MyCCSession()

    def test_file_path(self):
        # Check some common paths
        self.assertEqual(os.environ["B10_FROM_BUILD"] + "/ddns_socket",
                         ddns.SOCKET_FILE)
        self.assertEqual(os.environ["B10_FROM_SOURCE"] +
                         "/src/bin/ddns/ddns.spec", ddns.SPECFILE_LOCATION)
        self.assertEqual(os.environ["B10_FROM_BUILD"] +
                         "/src/bin/auth/auth.spec",
                         ddns.AUTH_SPECFILE_LOCATION)

    def test_get_datasrc_client(self):
        # The test sqlite DB should contain the example.org zone.
        rrclass, datasrc_client = ddns.get_datasrc_client(self.__ccsession)
        self.assertEqual(RRClass.IN(), rrclass)
        self.assertEqual(DataSourceClient.SUCCESS,
                         datasrc_client.find_zone(Name('example.org'))[0])

    def test_get_datasrc_client_fail(self):
        # DB file is in a non existent directory, and creatng the client
        # will fail.  get_datasrc_client will return a dummy client, which
        # will subsequently make find_zone() fail.
        self.__ccsession.auth_db_file = './notexistentdir/somedb.sqlite3'
        rrclass, datasrc_client = ddns.get_datasrc_client(self.__ccsession)
        self.assertEqual(RRClass.IN(), rrclass)
        self.assertRaises(isc.datasrc.Error,
                          datasrc_client.find_zone, Name('example.org'))

if __name__== "__main__":
    isc.log.resetUnitTestRootLogger()
    unittest.main()
