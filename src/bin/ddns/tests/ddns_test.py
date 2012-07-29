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
from isc.cc.session import SessionTimeout, SessionError, ProtocolError
from isc.datasrc import DataSourceClient
from isc.config import module_spec_from_file
from isc.config.config_data import ConfigData
from isc.config.ccsession import create_answer, ModuleCCSessionError
from isc.config.module_spec import ModuleSpecError
from isc.server_common.dns_tcp import DNSTCPContext
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

# Incorporate it so we can use the real default values of zonemgr config
# in the tests.
ZONEMGR_MODULE_SPEC = module_spec_from_file(
    os.environ["B10_FROM_BUILD"] + "/src/bin/zonemgr/zonemgr.spec")

class FakeSocket:
    """
    A fake socket. It only provides a file number, peer name and accept method.
    """
    def __init__(self, fileno, proto=socket.IPPROTO_UDP):
        self.proto = proto
        self.__fileno = fileno
        self._sent_data = None
        self._sent_addr = None
        self._close_called = 0  # number of calls to close()
        self.__send_cc = 0      # waterline of the send buffer (can be reset)
        # customizable by tests; if set to True, sendto() will throw after
        # recording the parameters.
        self._raise_on_send = False
        self._send_buflen = None # imaginary send buffer for partial send
    def fileno(self):
        return self.__fileno
    def getpeername(self):
        if self.proto == socket.IPPROTO_UDP or \
                self.proto == socket.IPPROTO_TCP:
            return TEST_CLIENT4
        return "fake_unix_socket"
    def accept(self):
        return FakeSocket(self.__fileno + 1), '/dummy/path'
    def sendto(self, data, addr):
        self._sent_data = data
        self._sent_addr = addr
        if self._raise_on_send:
            raise socket.error('test socket failure')
    def send(self, data):
        if self._raise_on_send:
            raise socket.error(errno.EPIPE, 'faked connection disruption')
        elif self._send_buflen is None:
            available_space = len(data)
        else:
            available_space = self._send_buflen - self.__send_cc
        if available_space == 0:
            # if there's no space, (assuming it's nonblocking mode) raise
            # EAGAIN.
            raise socket.error(errno.EAGAIN,
                               "Resource temporarily unavailable")
        # determine the sendable part of the data, record it, update "buffer".
        cc = min(available_space, len(data))
        if self._sent_data is None:
            self._sent_data = data[:cc]
        else:
            self._sent_data += data[:cc]
        self.__send_cc += cc
        return cc
    def setblocking(self, on):
        # We only need a faked NO-OP implementation.
        pass
    def close(self):
        self._close_called += 1
    def clear(self):
        '''Clear internal instrumental data.'''
        self._sent_data = None
        self._sent_addr = None
    def make_send_ready(self):
        # pretend that the accrued data has been cleared, making room in
        # the send buffer.
        self.__send_cc = 0

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

    # faked CC sequence used in group_send/recvmsg
    FAKE_SEQUENCE = 53

    def __init__(self):
        module_spec = isc.config.module_spec_from_file(
            ddns.SPECFILE_LOCATION)
        isc.config.ConfigData.__init__(self, module_spec)
        self._started = False
        self._stopped = False
        # Used as the return value of get_remote_config_value.  Customizable.
        self.auth_db_file = READ_ZONE_DB_FILE
        # Used as the return value of get_remote_config_value.  Customizable.
        self.auth_datasources = None
        # faked cc channel, providing group_send/recvmsg itself.  The following
        # attributes are for inspection/customization in tests.
        self._session = self
        self._sent_msg = []
        self._recvmsg_called = 0
        self._answer_code = 0   # code used in answer returned via recvmsg
        self._sendmsg_exception = None # will be raised from sendmsg if !None
        self._recvmsg_exception = None # will be raised from recvmsg if !None

        # Attributes to handle (faked) remote configurations
        self.__callbacks = {}   # record callbacks for updates to remote confs
        self._raise_mods = {}  # map of module to exceptions to be triggered
                               # on add_remote.  settable by tests.
        self._auth_config = {}  # faked auth cfg, settable by tests
        self._zonemgr_config = {} # faked zonemgr cfg, settable by tests

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

    def add_remote_config_by_name(self, module_name, update_callback=None):
        # If a list of exceptions is given for the module, raise the front one,
        # removing that exception from the list (so the list length controls
        # how many (and which) exceptions should be raised on add_remote).
        if module_name in self._raise_mods.keys() and \
                len(self._raise_mods[module_name]) != 0:
            ex = self._raise_mods[module_name][0]
            self._raise_mods[module_name] = self._raise_mods[module_name][1:]
            raise ex('Failure requesting remote config data')

        if update_callback is not None:
            self.__callbacks[module_name] = update_callback
        if module_name is 'Auth':
            if module_name in self.__callbacks:
                # ddns implementation doesn't use the 2nd element, so just
                # setting it to None
                self.__callbacks[module_name](self._auth_config, None)
        if module_name is 'Zonemgr':
            if module_name in self.__callbacks:
                self.__callbacks[module_name](self._zonemgr_config,
                                              ConfigData(ZONEMGR_MODULE_SPEC))

    def get_remote_config_value(self, module_name, item):
        if module_name == "Auth" and item == "database_file":
            return self.auth_db_file, False
        if module_name == "Auth" and item == "datasources":
            if self.auth_datasources is None:
                return [], True # default
            else:
                return self.auth_datasources, False
        if module_name == 'Zonemgr' and item == 'secondary_zones':
            if item in self._zonemgr_config:
                return self._zonemgr_config[item], False
            else:
                seczone_default = \
                    ConfigData(ZONEMGR_MODULE_SPEC).get_default_value(
                    'secondary_zones')
                return seczone_default, True

    def group_sendmsg(self, msg, group):
        # remember the passed parameter, and return dummy sequence
        self._sent_msg.append((msg, group))
        if self._sendmsg_exception is not None:
            raise self._sendmsg_exception
        return self.FAKE_SEQUENCE

    def group_recvmsg(self, nonblock, seq):
        self._recvmsg_called += 1
        if seq != self.FAKE_SEQUENCE:
            raise RuntimeError('unexpected CC sequence: ' + str(seq))
        if self._recvmsg_exception is not None:
            raise self._recvmsg_exception
        if self._answer_code is 0:
            return create_answer(0), None
        else:
            return create_answer(self._answer_code, "dummy error value"), None

    def clear_msg(self):
        '''Clear instrumental attributes related session messages.'''
        self._sent_msg = []
        self._recvmsg_called = 0
        self._answer_code = 0
        self._sendmsg_exception = None
        self._recvmsg_exception = None

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
        # Because we overwrite the _listen_socket, close any existing
        # socket object.
        if self.ddns_server._listen_socket is not None:
            self.ddns_server._listen_socket.close()
        self.ddns_server._listen_socket = FakeSocket(2)
        ddns.select.select = self.__select

        # common private attributes for TCP response tests
        self.__tcp_sock = FakeSocket(10, socket.IPPROTO_TCP)
        self.__tcp_ctx = DNSTCPContext(self.__tcp_sock)
        self.__tcp_data = b'A' * 12 # dummy, just the same size as DNS header
        # some tests will override this, which will be restored in tearDown:
        self.__orig_add_pause = ddns.add_pause

    def tearDown(self):
        ddns.select.select = select.select
        ddns.isc.util.cio.socketsession.SocketSessionReceiver = \
            isc.util.cio.socketsession.SocketSessionReceiver
        isc.server_common.tsig_keyring = self.orig_tsig_keyring
        ddns.add_pause = self.__orig_add_pause

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
        # Let ddns object complete any necessary cleanup (not part of the test,
        # but for suppressing any warnings from the Python interpreter)
        ddnss.shutdown_cleanup()

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

    def test_datasrc_config(self):
        # By default (in our faked config) it should be derived from the
        # test data source
        rrclass, datasrc_client = self.ddns_server._datasrc_info
        self.assertEqual(RRClass.IN(), rrclass)
        self.assertEqual(DataSourceClient.SUCCESS,
                         datasrc_client.find_zone(Name('example.org'))[0])

        # emulating an update.  calling add_remote_config_by_name is a
        # convenient faked way to invoke the callback.  We set the db file
        # to a bogus one; the current implementation will create an unusable
        # data source client.
        self.__cc_session.auth_db_file = './notexistentdir/somedb.sqlite3'
        self.__cc_session._auth_config = \
            {'database_file': './notexistentdir/somedb.sqlite3'}
        self.__cc_session.add_remote_config_by_name('Auth')
        rrclass, datasrc_client = self.ddns_server._datasrc_info
        self.assertEqual(RRClass.IN(), rrclass)
        self.assertRaises(isc.datasrc.Error,
                          datasrc_client.find_zone, Name('example.org'))

        # Check the current info isn't changed if the new config doesn't
        # update it.
        info_orig = self.ddns_server._datasrc_info
        self.ddns_server._datasrc_info = 42 # dummy value, should be kept.
        self.__cc_session._auth_config = {'other_config': 'value'}
        self.__cc_session.add_remote_config_by_name('Auth')
        self.assertEqual(42, self.ddns_server._datasrc_info)
        self.ddns_server._datasrc_info = info_orig

    def test_secondary_zones_config(self):
        # By default it should be an empty list
        self.assertEqual(set(), self.ddns_server._secondary_zones)

        # emulating an update.
        self.__cc_session._zonemgr_config = {'secondary_zones': [
                {'name': TEST_ZONE_NAME_STR, 'class': TEST_RRCLASS_STR}]}
        self.__cc_session.add_remote_config_by_name('Zonemgr')

        # The new set of secondary zones should be stored.
        self.assertEqual({(TEST_ZONE_NAME, TEST_RRCLASS)},
                         self.ddns_server._secondary_zones)

        # Similar to the above, but 'class' is unspecified.  The default value
        # should be used.
        self.__cc_session._zonemgr_config = {'secondary_zones': [
                {'name': TEST_ZONE_NAME_STR}]}
        self.__cc_session.add_remote_config_by_name('Zonemgr')
        self.assertEqual({(TEST_ZONE_NAME, TEST_RRCLASS)},
                         self.ddns_server._secondary_zones)

        # The given list has a duplicate.  The resulting set should unify them.
        self.__cc_session._zonemgr_config = {'secondary_zones': [
                {'name': TEST_ZONE_NAME_STR, 'class': TEST_RRCLASS_STR},
                {'name': TEST_ZONE_NAME_STR, 'class': TEST_RRCLASS_STR}]}
        self.__cc_session.add_remote_config_by_name('Zonemgr')
        self.assertEqual({(TEST_ZONE_NAME, TEST_RRCLASS)},
                         self.ddns_server._secondary_zones)

        # Check the 2ndary zones aren't changed if the new config doesn't
        # update it.
        seczones_orig = self.ddns_server._secondary_zones
        self.ddns_server._secondary_zones = 42 # dummy value, should be kept.
        self.__cc_session._zonemgr_config = {}
        self.__cc_session.add_remote_config_by_name('Zonemgr')
        self.assertEqual(42, self.ddns_server._secondary_zones)
        self.ddns_server._secondary_zones = seczones_orig

        # If the update config is broken, the existing set should be intact.
        self.__cc_session._zonemgr_config = {'secondary_zones': [
                {'name': 'good.example', 'class': TEST_RRCLASS_STR},
                {'name': 'badd..example', 'class': TEST_RRCLASS_STR}]}
        self.__cc_session.add_remote_config_by_name('Zonemgr')
        self.assertEqual({(TEST_ZONE_NAME, TEST_RRCLASS)},
                         self.ddns_server._secondary_zones)

    def __check_remote_config_fail(self, mod_name, num_ex, expected_ex):
        '''Subroutine for remote_config_fail test.'''

        # fake pause function for inspection and to avoid having timeouts
        added_pause = []
        ddns.add_pause = lambda sec: added_pause.append(sec)

        # In our current implementation, there will be up to 3 tries of
        # adding the module, each separated by a 1-sec pause.  If all attempts
        # fail the exception will be propagated.
        exceptions = [expected_ex for i in range(0, num_ex)]
        self.__cc_session._raise_mods = {mod_name: exceptions}
        if num_ex >= 3:
            self.assertRaises(expected_ex, ddns.DDNSServer, self.__cc_session)
        else:
            ddns.DDNSServer(self.__cc_session)
        self.assertEqual([1 for i in range(0, num_ex)], added_pause)

    def test_remote_config_fail(self):
        # If getting config of Auth or Zonemgr fails on construction of
        # DDNServer, it should result in an exception and a few times
        # of retries.  We test all possible cases, changing the number of
        # raised exceptions and the type of exceptions that can happen,
        # which should also cover the fatal error case.
        for i in range(0, 4):
            self.__check_remote_config_fail('Auth', i, ModuleCCSessionError)
            self.__check_remote_config_fail('Auth', i, ModuleSpecError)
            self.__check_remote_config_fail('Zonemgr', i, ModuleCCSessionError)
            self.__check_remote_config_fail('Zonemgr', i, ModuleSpecError)

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

    def __send_select_tcp(self, buflen, raise_after_select=False):
        '''Common subroutine for some TCP related tests below.'''
        fileno = self.__tcp_sock.fileno()
        self.ddns_server._tcp_ctxs = {fileno: (self.__tcp_ctx, TEST_CLIENT6)}

        # make an initial, incomplete send via the test context
        self.__tcp_sock._send_buflen = buflen
        self.assertEqual(DNSTCPContext.SENDING,
                         self.__tcp_ctx.send(self.__tcp_data))
        self.assertEqual(buflen, len(self.__tcp_sock._sent_data))
        # clear the socket "send buffer"
        self.__tcp_sock.make_send_ready()
        # if requested, set up exception
        self.__tcp_sock._raise_on_send = raise_after_select

        # Run select
        self.__select_expected = ([1, 2], [fileno], [], None)
        self.__select_answer = ([], [fileno], [])
        self.ddns_server.run()

    def test_select_send_continued(self):
        '''Test continuation of sending a TCP response.'''
        # Common setup, with the bufsize that would make it complete after a
        # single select call.
        self.__send_select_tcp(7)

        # Now the send should be completed.  socket should be closed,
        # and the context should be removed from the server.
        self.assertEqual(14, len(self.__tcp_sock._sent_data))
        self.assertEqual(1, self.__tcp_sock._close_called)
        self.assertEqual(0, len(self.ddns_server._tcp_ctxs))

    def test_select_send_continued_twice(self):
        '''Test continuation of sending a TCP response, still continuing.'''
        # This is similar to the send_continued test, but the continued
        # operation still won't complete the send.
        self.__send_select_tcp(5)

        # Only 10 bytes should have been transmitted, socket is still open,
        # and the context is still in the server (that would require select
        # watch it again).
        self.assertEqual(10, len(self.__tcp_sock._sent_data))
        self.assertEqual(0, self.__tcp_sock._close_called)
        fileno = self.__tcp_sock.fileno()
        self.assertEqual(self.__tcp_ctx,
                         self.ddns_server._tcp_ctxs[fileno][0])

    def test_select_send_continued_failed(self):
        '''Test continuation of sending a TCP response, which fails.'''
        # Let the socket raise an exception in the second call to send().
        self.__send_select_tcp(5, raise_after_select=True)

        # Only the data before select() have been transmitted, socket is
        # closed due to the failure, and the context is removed from the
        # server.
        self.assertEqual(5, len(self.__tcp_sock._sent_data))
        self.assertEqual(1, self.__tcp_sock._close_called)
        self.assertEqual(0, len(self.ddns_server._tcp_ctxs))

    def test_select_multi_tcp(self):
        '''Test continuation of sending a TCP response, multiple sockets.'''
        # Check if the implementation still works with multiple outstanding
        # TCP contexts.  We use three (arbitray choice), of which two will be
        # writable after select and complete the send.
        tcp_socks = []
        for i in range(0, 3):
            # Use faked FD of 100, 101, 102 (again, arbitrary choice)
            s = FakeSocket(100 + i, proto=socket.IPPROTO_TCP)
            ctx = DNSTCPContext(s)
            self.ddns_server._tcp_ctxs[s.fileno()] = (ctx, TEST_CLIENT6)
            s._send_buflen = 7  # make sure it requires two send's
            self.assertEqual(DNSTCPContext.SENDING, ctx.send(self.__tcp_data))
            s.make_send_ready()

            tcp_socks.append(s)

        self.__select_expected = ([1, 2], [100, 101, 102], [], None)
        self.__select_answer = ([], [100, 102], [])
        self.ddns_server.run()

        for i in [0, 2]:
            self.assertEqual(14, len(tcp_socks[i]._sent_data))
            self.assertEqual(1, tcp_socks[i]._close_called)
        self.assertEqual(1, len(self.ddns_server._tcp_ctxs))

    def test_select_bad_writefd(self):
        # There's no outstanding TCP context, but select somehow returns
        # writable FD.  It should result in an uncaught exception, killing
        # the server.  This is okay, because it shouldn't happen and should be
        # an internal bug.
        self.__select_expected = ([1, 2], [], [], None)
        self.__select_answer = ([], [10], [])
        self.assertRaises(KeyError, self.ddns_server.run)

def create_msg(opcode=Opcode.UPDATE(), zones=[TEST_ZONE_RECORD], prereq=[],
               tsigctx=None):
    msg = Message(Message.RENDER)
    msg.set_qid(TEST_QID)
    msg.set_opcode(opcode)
    msg.set_rcode(Rcode.NOERROR())
    for z in zones:
        msg.add_question(z)
    for p in prereq:
        msg.add_rrset(SECTION_PREREQUISITE, p)

    renderer = MessageRenderer()
    if tsigctx is not None:
        msg.to_wire(renderer, tsigctx)
    else:
        msg.to_wire(renderer)

    # re-read the created data in the parse mode
    msg.clear(Message.PARSE)
    msg.from_wire(renderer.get_data())

    return renderer.get_data()


class TestDDNSSession(unittest.TestCase):
    def setUp(self):
        self.__cc_session = MyCCSession()
        self.assertFalse(self.__cc_session._started)
        self.orig_tsig_keyring = isc.server_common.tsig_keyring
        isc.server_common.tsig_keyring = FakeKeyringModule()
        self.server = ddns.DDNSServer(self.__cc_session)
        # Check that start_ddns_forwarder has been called upon
        # initialization (before we do anything else that might
        # cause messages to be sent)
        self.check_session_start_forwarder_called()
        self.server._UpdateSessionClass = self.__fake_session_creator
        self.__faked_result = UPDATE_SUCCESS # will be returned by fake session
        self.__sock = FakeSocket(-1)

    def tearDown(self):
        self.assertTrue(isc.server_common.tsig_keyring.initialized)
        isc.server_common.tsig_keyring = self.orig_tsig_keyring

    def __fake_session_creator(self, req_message, client_addr, zone_config):
        # remember the passed message for possible inspection later.
        self.__req_message = req_message
        return FakeUpdateSession(req_message, client_addr, zone_config,
                                 self.__faked_result)

    def check_update_response(self, resp_wire, expected_rcode=Rcode.NOERROR(),
                              tsig_ctx=None, tcp=False):
        '''Check if given wire data are valid form of update response.

        In this implementation, zone/prerequisite/update sections should be
        empty in responses.

        If tsig_ctx (isc.dns.TSIGContext) is not None, the response should
        be TSIG signed and the signature should be verifiable with the context
        that has signed the corresponding request.

        if tcp is True, the wire data are expected to be prepended with
        a 2-byte length field.

        '''
        if tcp:
            data_len = resp_wire[0] * 256 + resp_wire[1]
            resp_wire = resp_wire[2:]
            self.assertEqual(len(resp_wire), data_len)

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
                                                     TEST_CLIENT6,
                                                     create_msg())))
        # this check ensures sendto() was really attempted.
        self.check_update_response(self.__sock._sent_data, Rcode.NOERROR())

    def test_tcp_request(self):
        # A simple case using TCP: all resopnse data are sent out at once.
        s = self.__sock
        s.proto = socket.IPPROTO_TCP
        self.assertTrue(self.server.handle_request((s, TEST_SERVER6,
                                                    TEST_CLIENT6,
                                                    create_msg())))
        self.check_update_response(s._sent_data, Rcode.NOERROR(), tcp=True)
        # In the current implementation, the socket should be closed
        # immedidately after a successful send.
        self.assertEqual(1, s._close_called)
        # TCP context shouldn't be held in the server.
        self.assertEqual(0, len(self.server._tcp_ctxs))

    def test_tcp_request_incomplete(self):
        # set the size of the socket "send buffer" to a small value, which
        # should cause partial send.
        s = self.__sock
        s.proto = socket.IPPROTO_TCP
        s._send_buflen = 7
        # before this request there should be no outstanding TCP context.
        self.assertEqual(0, len(self.server._tcp_ctxs))
        self.assertTrue(self.server.handle_request((s, TEST_SERVER6,
                                                    TEST_CLIENT6,
                                                    create_msg())))
        # Only the part of data that fit the send buffer should be transmitted.
        self.assertEqual(s._send_buflen, len(s._sent_data))
        # the socket is not yet closed.
        self.assertEqual(0, s._close_called)
        # and a new context is stored in the server.
        self.assertEqual(1, len(self.server._tcp_ctxs))

        # clear the "send buffer" of the fake socket, and continue the send
        # by hand.  The next attempt should complete the send, and the combined
        # data should be the expected response.
        s.make_send_ready()
        self.assertEqual(DNSTCPContext.SEND_DONE,
                         self.server._tcp_ctxs[s.fileno()][0].send_ready())
        self.check_update_response(s._sent_data, Rcode.NOERROR(), tcp=True)

    def test_tcp_request_error(self):
        # initial send() on the TCP socket will fail.  The request handling
        # will be considered failure.
        s = self.__sock
        s.proto = socket.IPPROTO_TCP
        s._raise_on_send = True
        self.assertFalse(self.server.handle_request((s, TEST_SERVER6,
                                                     TEST_CLIENT6,
                                                     create_msg())))
        # the socket should have been closed.
        self.assertEqual(1, s._close_called)

    def test_tcp_request_quota(self):
        '''Test'''
        # Originally the TCP context map should be empty.
        self.assertEqual(0, len(self.server._tcp_ctxs))

        class FakeReceiver:
            '''Faked SessionReceiver, just returning given param by pop()'''
            def __init__(self, param):
                self.__param = param
            def pop(self):
                return self.__param

        def check_tcp_ok(fd, expect_grant):
            '''Supplemental checker to see if TCP request is handled.'''
            s = FakeSocket(fd, proto=socket.IPPROTO_TCP)
            s._send_buflen = 7
            self.server._socksession_receivers[s.fileno()] = \
                (None, FakeReceiver((s, TEST_SERVER6, TEST_CLIENT6,
                                     create_msg())))
            self.assertEqual(expect_grant,
                             self.server.handle_session(s.fileno()))
            self.assertEqual(0 if expect_grant else 1, s._close_called)

        # By default up to 10 TCP clients can coexist (use hardcode
        # intentionally so we can test the default value itself)
        for i in range(0, 10):
            check_tcp_ok(i, True)
        self.assertEqual(10, len(self.server._tcp_ctxs))

        # Beyond that, it should be rejected (by reset)
        check_tcp_ok(11, False)

        # If we remove one context from the server, new client can go in again.
        self.server._tcp_ctxs.pop(5)
        check_tcp_ok(12, True)

    def test_request_message(self):
        '''Test if the request message stores RRs separately.'''
        # Specify 'drop' so the passed message won't be modified.
        self.__faked_result = UPDATE_DROP
        # Put the same RR twice in the prerequisite section.  We should see
        # them as separate RRs.
        dummy_record = RRset(TEST_ZONE_NAME, TEST_RRCLASS, RRType.NS(),
                             RRTTL(0))
        dummy_record.add_rdata(Rdata(RRType.NS(), TEST_RRCLASS, "ns.example"))
        self.server.handle_request((self.__sock, TEST_SERVER6, TEST_CLIENT6,
                                    create_msg(prereq=[dummy_record,
                                                       dummy_record])))
        num_rrsets = len(self.__req_message.get_section(SECTION_PREREQUISITE))
        self.assertEqual(2, num_rrsets)

    def check_session_msg(self, result, expect_recv=2):
        '''Check post update communication with other modules.'''
        # iff the update succeeds, b10-ddns should tell interested other
        # modules the information about the update zone.  Possible modules
        # are xfrout and auth: for xfrout, the message format should be:
        # {'command': ['notify', {'zone_name': <updated_zone_name>,
        #                         'zone_class', <updated_zone_class>}]}
        # for auth, it should be:
        # {'command': ['loadzone', {'origin': <updated_zone_name>,
        #                           'class', <updated_zone_class>}]}
        # and expect an answer by calling group_recvmsg().
        #
        # expect_recv indicates the expected number of calls to
        # group_recvmsg(), which is normally 2, but can be 0 if send fails;
        # if the message is to be sent
        if result == UPDATE_SUCCESS:
            expected_sentmsg = 2
            self.assertEqual(expected_sentmsg,
                             len(self.__cc_session._sent_msg))
            self.assertEqual(expect_recv, self.__cc_session._recvmsg_called)
            msg_cnt = 0
            sent_msg, sent_group = self.__cc_session._sent_msg[msg_cnt]
            sent_cmd = sent_msg['command']
            self.assertEqual('Auth', sent_group)
            self.assertEqual('loadzone', sent_cmd[0])
            self.assertEqual(2, len(sent_cmd[1]))
            self.assertEqual(TEST_ZONE_NAME.to_text(),
                             sent_cmd[1]['origin'])
            self.assertEqual(TEST_RRCLASS.to_text(),
                             sent_cmd[1]['class'])
            msg_cnt += 1
            sent_msg, sent_group = self.__cc_session._sent_msg[msg_cnt]
            sent_cmd = sent_msg['command']
            self.assertEqual('Xfrout', sent_group)
            self.assertEqual('notify', sent_cmd[0])
            self.assertEqual(2, len(sent_cmd[1]))
            self.assertEqual(TEST_ZONE_NAME.to_text(), sent_cmd[1]['zone_name'])
            self.assertEqual(TEST_RRCLASS.to_text(), sent_cmd[1]['zone_class'])
        else:
            # for other result cases neither send nor recvmsg should be called.
            self.assertEqual([], self.__cc_session._sent_msg)
            self.assertEqual(0, self.__cc_session._recvmsg_called)

    def check_session_start_forwarder_called(self):
        '''Check that the command 'start_ddns_forwarder' has been called
           This test removes said message from the sent message queue.
        '''
        sent_msg, sent_group = self.__cc_session._sent_msg.pop(0)
        sent_cmd = sent_msg['command']
        self.assertEqual('Auth', sent_group)
        self.assertEqual('start_ddns_forwarder', sent_cmd[0])
        self.assertEqual(1, len(sent_cmd))
        self.assertEqual(1, self.__cc_session._recvmsg_called)
        # reset it for other tests
        self.__cc_session._recvmsg_called = 0

    def check_session_stop_forwarder_called(self):
        '''Check that the command 'stop_ddns_forwarder' has been called
           This test removes said message from the sent message queue.
        '''
        # check the last message sent
        sent_msg, sent_group = self.__cc_session._sent_msg.pop()
        sent_cmd = sent_msg['command']
        self.assertEqual('Auth', sent_group)
        self.assertEqual('stop_ddns_forwarder', sent_cmd[0])
        self.assertEqual(1, len(sent_cmd))

    def test_session_msg(self):
        '''Test post update communication with other modules.'''

        # Normal cases, confirming communication takes place iff update
        # succeeds
        for r in [UPDATE_SUCCESS, UPDATE_ERROR, UPDATE_DROP]:
            self.__cc_session.clear_msg()
            self.check_session(result=r)
            self.check_session_msg(r)

        # Return an error from the remote module, which should be just ignored.
        self.__cc_session.clear_msg()
        self.__cc_session._answer_code = 1
        self.check_session()
        self.check_session_msg(UPDATE_SUCCESS)

        # raise some exceptions from the faked session.  Expected ones are
        # simply (logged and) ignored
        self.__cc_session.clear_msg()
        self.__cc_session._recvmsg_exception = SessionTimeout('dummy timeout')
        self.check_session()
        self.check_session_msg(UPDATE_SUCCESS)

        self.__cc_session.clear_msg()
        self.__cc_session._recvmsg_exception = SessionError('dummy error')
        self.check_session()
        self.check_session_msg(UPDATE_SUCCESS)

        self.__cc_session.clear_msg()
        self.__cc_session._recvmsg_exception = ProtocolError('dummy perror')
        self.check_session()
        self.check_session_msg(UPDATE_SUCCESS)

        # Similar to the previous cases, but sendmsg() raises, so there should
        # be no call to recvmsg().
        self.__cc_session.clear_msg()
        self.__cc_session._sendmsg_exception = SessionError('send error')
        self.check_session()
        self.check_session_msg(UPDATE_SUCCESS, expect_recv=0)

        # Unexpected exception will be propagated (and will terminate the
        # server)
        self.__cc_session.clear_msg()
        self.__cc_session._sendmsg_exception = RuntimeError('unexpected')
        self.assertRaises(RuntimeError, self.check_session)

    def test_session_shutdown_cleanup(self):
        '''Test that the stop forwarding message is sent'''
        self.server.shutdown_cleanup()
        self.check_session_stop_forwarder_called()

    def test_session_msg_for_auth(self):
        '''Test post update communication with other modules including Auth.'''

        # Let the CC session return in-memory config with sqlite3 backend.
        # (The default case was covered by other tests.)
        self.__cc_session.auth_datasources = \
            [{'type': 'memory', 'class': 'IN', 'zones': [
                    {'origin': TEST_ZONE_NAME_STR, 'filetype': 'sqlite3'}]}]
        self.check_session()
        self.check_session_msg(UPDATE_SUCCESS)

        # Let sendmsg() raise an exception.  The first exception shouldn't
        # stop sending the second message.  There's just no recv calls.
        self.__cc_session.clear_msg()
        self.__cc_session._sendmsg_exception = SessionError('send error')
        self.check_session()
        self.check_session_msg(UPDATE_SUCCESS, expect_recv=0)

        # Likewise, in the case recvmsg() raises (and there should be recv
        # calls in this case)
        self.__cc_session.clear_msg()
        self.__cc_session._recvmsg_exception = SessionError('recv error')
        self.check_session()
        self.check_session_msg(UPDATE_SUCCESS)

    def test_session_with_config(self):
        '''Check a session with more realistic config setups.

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

    def test_session_start_stop_forwarder_failures(self):
        '''Check that we don't crash if the server reports an error
           setting up or closing down the DDNS UPDATE message forwarder,
           or if there is an exception from the message queue.'''
        self.__cc_session._answer_code = 1
        self.server._DDNSServer__notify_start_forwarder()
        self.server._DDNSServer__notify_stop_forwarder()

        for exc in [ SessionError("sessionerror"),
                     SessionTimeout("sessiontimeout"),
                     ProtocolError("protocolerror") ]:
            self.__cc_session._recvmsg_exception = exc
            self.server._DDNSServer__notify_start_forwarder()
            self.server._DDNSServer__notify_stop_forwarder()
            self.__cc_session._recvmsg_exception = None

            self.__cc_session._sendmsg_exception = exc
            self.server._DDNSServer__notify_start_forwarder()
            self.server._DDNSServer__notify_stop_forwarder()
            self.__cc_session._recvmsg_exception = None

    def test_session_auth_started(self):
        '''Check that 'start_ddns_forwarder' is sent (again) when the
           notification 'auth_started' is received'''
        # auth_started message should trigger it again
        answer = self.server.command_handler('auth_started', None)
        self.check_session_start_forwarder_called()

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
        # Get rid of the socket file too
        self.__orig_clear()

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

if __name__== "__main__":
    isc.log.resetUnitTestRootLogger()
    unittest.main()
