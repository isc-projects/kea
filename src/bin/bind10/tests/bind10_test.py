from bind10 import ProcessInfo, BoB

# XXX: environment tests are currently disabled, due to the preprocessor
#      setup that we have now complicating the environment

import unittest
import sys
import os
import signal
import socket
from isc.net.addr import IPAddr

class TestProcessInfo(unittest.TestCase):
    def setUp(self):
        # redirect stdout to a pipe so we can check that our
        # process spawning is doing the right thing with stdout
        self.old_stdout = os.dup(sys.stdout.fileno())
        self.pipes = os.pipe()
        os.dup2(self.pipes[1], sys.stdout.fileno())
        os.close(self.pipes[1])
        # note that we use dup2() to restore the original stdout
        # to the main program ASAP in each test... this prevents
        # hangs reading from the child process (as the pipe is only
        # open in the child), and also insures nice pretty output

    def tearDown(self):
        # clean up our stdout munging
        os.dup2(self.old_stdout, sys.stdout.fileno())
        os.close(self.pipes[0])

    def test_init(self):
        pi = ProcessInfo('Test Process', [ '/bin/echo', 'foo' ])
        os.dup2(self.old_stdout, sys.stdout.fileno())
        self.assertEqual(pi.name, 'Test Process')
        self.assertEqual(pi.args, [ '/bin/echo', 'foo' ])
#        self.assertEqual(pi.env, { 'PATH': os.environ['PATH'],
#                                   'PYTHON_EXEC': os.environ['PYTHON_EXEC'] })
        self.assertEqual(pi.dev_null_stdout, False)
        self.assertEqual(os.read(self.pipes[0], 100), b"foo\n")
        self.assertNotEqual(pi.process, None)
        self.assertTrue(type(pi.pid) is int)

#    def test_setting_env(self):
#        pi = ProcessInfo('Test Process', [ '/bin/true' ], env={'FOO': 'BAR'})
#        os.dup2(self.old_stdout, sys.stdout.fileno())
#        self.assertEqual(pi.env, { 'PATH': os.environ['PATH'],
#                                   'PYTHON_EXEC': os.environ['PYTHON_EXEC'],
#                                   'FOO': 'BAR' })

    def test_setting_null_stdout(self):
        pi = ProcessInfo('Test Process', [ '/bin/echo', 'foo' ], 
                         dev_null_stdout=True)
        os.dup2(self.old_stdout, sys.stdout.fileno())
        self.assertEqual(pi.dev_null_stdout, True)
        self.assertEqual(os.read(self.pipes[0], 100), b"")

    def test_respawn(self):
        pi = ProcessInfo('Test Process', [ '/bin/echo', 'foo' ])
        # wait for old process to work...
        self.assertEqual(os.read(self.pipes[0], 100), b"foo\n")
        # respawn it
        old_pid = pi.pid
        pi.respawn()
        os.dup2(self.old_stdout, sys.stdout.fileno())
        # make sure the new one started properly
        self.assertEqual(pi.name, 'Test Process')
        self.assertEqual(pi.args, [ '/bin/echo', 'foo' ])
#        self.assertEqual(pi.env, { 'PATH': os.environ['PATH'],
#                                   'PYTHON_EXEC': os.environ['PYTHON_EXEC'] })
        self.assertEqual(pi.dev_null_stdout, False)
        self.assertEqual(os.read(self.pipes[0], 100), b"foo\n")
        self.assertNotEqual(pi.process, None)
        self.assertTrue(type(pi.pid) is int)
        self.assertNotEqual(pi.pid, old_pid)

class TestBoB(unittest.TestCase):
    def test_init(self):
        bob = BoB()
        self.assertEqual(bob.verbose, False)
        self.assertEqual(bob.msgq_socket_file, None)
        self.assertEqual(bob.auth_port, 5300)
        self.assertEqual(bob.address, None)
        self.assertEqual(bob.cc_session, None)
        self.assertEqual(bob.ccs, None)
        self.assertEqual(bob.processes, {})
        self.assertEqual(bob.dead_processes, {})
        self.assertEqual(bob.runnable, False)
        self.assertEqual(bob.uid, None)
        self.assertEqual(bob.username, None)
        self.assertEqual(bob.nocache, False)
        self.assertEqual(bob.cfg_start_auth, True)
        self.assertEqual(bob.cfg_start_recurse, False)

    def test_init_alternate_socket(self):
        bob = BoB("alt_socket_file")
        self.assertEqual(bob.verbose, False)
        self.assertEqual(bob.msgq_socket_file, "alt_socket_file")
        self.assertEqual(bob.auth_port, 5300)
        self.assertEqual(bob.address, None)
        self.assertEqual(bob.cc_session, None)
        self.assertEqual(bob.ccs, None)
        self.assertEqual(bob.processes, {})
        self.assertEqual(bob.dead_processes, {})
        self.assertEqual(bob.runnable, False)
        self.assertEqual(bob.uid, None)
        self.assertEqual(bob.username, None)
        self.assertEqual(bob.nocache, False)
        self.assertEqual(bob.cfg_start_auth, True)
        self.assertEqual(bob.cfg_start_recurse, False)

    def test_init_alternate_auth_port(self):
        bob = BoB(None, 9999)
        self.assertEqual(bob.verbose, False)
        self.assertEqual(bob.msgq_socket_file, None)
        self.assertEqual(bob.auth_port, 9999)
        self.assertEqual(bob.address, None)
        self.assertEqual(bob.cc_session, None)
        self.assertEqual(bob.ccs, None)
        self.assertEqual(bob.processes, {})
        self.assertEqual(bob.dead_processes, {})
        self.assertEqual(bob.runnable, False)
        self.assertEqual(bob.uid, None)
        self.assertEqual(bob.username, None)
        self.assertEqual(bob.nocache, False)
        self.assertEqual(bob.cfg_start_auth, True)
        self.assertEqual(bob.cfg_start_recurse, False)

    def test_init_alternate_address(self):
        bob = BoB(None, 1234, IPAddr('127.127.127.127'))
        self.assertEqual(bob.verbose, False)
        self.assertEqual(bob.msgq_socket_file, None)
        self.assertEqual(bob.auth_port, 1234)
        self.assertEqual(bob.address.addr, socket.inet_aton('127.127.127.127'))
        self.assertEqual(bob.cc_session, None)
        self.assertEqual(bob.ccs, None)
        self.assertEqual(bob.processes, {})
        self.assertEqual(bob.dead_processes, {})
        self.assertEqual(bob.runnable, False)
        self.assertEqual(bob.uid, None)
        self.assertEqual(bob.username, None)
        self.assertEqual(bob.nocache, False)
        self.assertEqual(bob.cfg_start_auth, True)
        self.assertEqual(bob.cfg_start_recurse, False)

# Class for testing the Bob.start_all_processes() method call.
#
# Although testing that external processes start is outside the scope
# of the unit test, by overriding the process start methods we can check
# that the right processes are started depending on the configuration
# options.
class StartAllProcessesBob(BoB):
    def __init__(self):
        BoB.__init__(self)

# Set flags as to which of the overridden methods has been run.
        self.msgq = False
        self.cfgmgr = False
        self.ccsession = False
        self.auth = False
        self.recurse = False
        self.xfrout = False
        self.xfrin = False
        self.zonemgr = False
        self.stats = False
        self.cmdctl = False

    def read_bind10_config(self):
        # Configuration options are set directly
        pass

    def start_msgq(self, c_channel_env):
        self.msgq = True

    def start_cfgmgr(self, c_channel_env):
        self.cfgmgr = True

    def start_ccsession(self, c_channel_env):
        self.ccsession = True

    def start_auth(self, c_channel_env):
        self.auth = True

    def start_recurse(self, c_channel_env):
        self.recurse = True

    def start_xfrout(self, c_channel_env):
        self.xfrout = True

    def start_xfrin(self, c_channel_env):
        self.xfrin = True

    def start_zonemgr(self, c_channel_env):
        self.zonemgr = True

    def start_stats(self, c_channel_env):
        self.stats = True

    def start_cmdctl(self, c_channel_env):
        self.cmdctl = True

# Check that the start_all_processes method starts the right combination
# of processes.
class TestStartAllProcessesBob(unittest.TestCase):
    def check_preconditions(self, bob):
        self.assertEqual(bob.msgq, False)
        self.assertEqual(bob.cfgmgr, False)
        self.assertEqual(bob.ccsession, False)
        self.assertEqual(bob.auth, False)
        self.assertEqual(bob.recurse, False)
        self.assertEqual(bob.xfrout, False)
        self.assertEqual(bob.xfrin, False)
        self.assertEqual(bob.zonemgr, False)
        self.assertEqual(bob.stats, False)
        self.assertEqual(bob.cmdctl, False)

    # Checks the processes started when starting neither auth nor recurse
    # is specified.
    def test_start_none(self):
        # Created Bob and ensure initialization correct
        bob = StartAllProcessesBob()
        self.check_preconditions(bob)

        # Start processes and check what was started
        c_channel_env = {}
        bob.cfg_start_auth = False
        bob.cfg_start_recurse = False

        bob.start_all_processes(c_channel_env)

        self.assertEqual(bob.msgq, True)
        self.assertEqual(bob.cfgmgr, True)
        self.assertEqual(bob.ccsession, True)
        self.assertEqual(bob.auth, False)
        self.assertEqual(bob.recurse, False)
        self.assertEqual(bob.xfrout, False)
        self.assertEqual(bob.xfrin, False)
        self.assertEqual(bob.zonemgr, False)
        self.assertEqual(bob.stats, True)
        self.assertEqual(bob.cmdctl, True)

    # Checks the processes started when starting only the auth process
    def test_start_auth(self):
        # Created Bob and ensure initialization correct
        bob = StartAllProcessesBob()
        self.check_preconditions(bob)

        # Start processes and check what was started
        c_channel_env = {}
        bob.cfg_start_auth = True
        bob.cfg_start_recurse = False

        bob.start_all_processes(c_channel_env)

        self.assertEqual(bob.msgq, True)
        self.assertEqual(bob.cfgmgr, True)
        self.assertEqual(bob.ccsession, True)
        self.assertEqual(bob.auth, True)
        self.assertEqual(bob.recurse, False)
        self.assertEqual(bob.xfrout, True)
        self.assertEqual(bob.xfrin, True)
        self.assertEqual(bob.zonemgr, True)
        self.assertEqual(bob.stats, True)
        self.assertEqual(bob.cmdctl, True)

    # Checks the processes started when starting only the recurse process
    def test_start_recurse(self):
        # Created Bob and ensure initialization correct
        bob = StartAllProcessesBob()
        self.check_preconditions(bob)

        # Start processes and check what was started
        c_channel_env = {}
        bob.cfg_start_auth = False
        bob.cfg_start_recurse = True

        bob.start_all_processes(c_channel_env)

        self.assertEqual(bob.msgq, True)
        self.assertEqual(bob.cfgmgr, True)
        self.assertEqual(bob.ccsession, True)
        self.assertEqual(bob.auth, False)
        self.assertEqual(bob.recurse, True)
        self.assertEqual(bob.xfrout, False)
        self.assertEqual(bob.xfrin, False)
        self.assertEqual(bob.zonemgr, False)
        self.assertEqual(bob.stats, True)
        self.assertEqual(bob.cmdctl, True)

    # Checks the processes started when starting both auth and recurse process
    def test_start_both(self):
        # Created Bob and ensure initialization correct
        bob = StartAllProcessesBob()
        self.check_preconditions(bob)

        # Start processes and check what was started
        c_channel_env = {}
        bob.cfg_start_auth = True
        bob.cfg_start_recurse = True

        bob.start_all_processes(c_channel_env)

        self.assertEqual(bob.msgq, True)
        self.assertEqual(bob.cfgmgr, True)
        self.assertEqual(bob.ccsession, True)
        self.assertEqual(bob.auth, True)
        self.assertEqual(bob.recurse, True)
        self.assertEqual(bob.xfrout, True)
        self.assertEqual(bob.xfrin, True)
        self.assertEqual(bob.zonemgr, True)
        self.assertEqual(bob.stats, True)
        self.assertEqual(bob.cmdctl, True)


if __name__ == '__main__':
    unittest.main()
