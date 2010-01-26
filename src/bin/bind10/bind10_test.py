from bind10 import ProcessInfo, BoB

import unittest
import sys
import os
import signal

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
        self.assertEqual(pi.env, { 'PATH': os.environ['PATH'],
                                   'PYTHON_EXEC': os.environ['PYTHON_EXEC'] })
        self.assertEqual(pi.dev_null_stdout, False)
        self.assertEqual(os.read(self.pipes[0], 100), b"foo\n")
        self.assertNotEqual(pi.process, None)
        self.assertTrue(type(pi.pid) is int)

    def test_setting_env(self):
        pi = ProcessInfo('Test Process', [ '/bin/true' ], env={'FOO': 'BAR'})
        os.dup2(self.old_stdout, sys.stdout.fileno())
        self.assertEqual(pi.env, { 'PATH': os.environ['PATH'],
                                   'PYTHON_EXEC': os.environ['PYTHON_EXEC'],
                                   'FOO': 'BAR' })

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
        self.assertEqual(pi.env, { 'PATH': os.environ['PATH'],
                                   'PYTHON_EXEC': os.environ['PYTHON_EXEC'] })
        self.assertEqual(pi.dev_null_stdout, False)
        self.assertEqual(os.read(self.pipes[0], 100), b"foo\n")
        self.assertNotEqual(pi.process, None)
        self.assertTrue(type(pi.pid) is int)
        self.assertNotEqual(pi.pid, old_pid)

class TestBoB(unittest.TestCase):
    def test_init(self):
        bob = BoB()
        self.assertEqual(bob.verbose, False)
        self.assertEqual(bob.c_channel_port, 9912)
        self.assertEqual(bob.cc_session, None)
        self.assertEqual(bob.processes, {})
        self.assertEqual(bob.dead_processes, {})
        self.assertEqual(bob.runnable, False)

    def test_init_alternate_port(self):
        bob = BoB(2199)
        self.assertEqual(bob.verbose, False)
        self.assertEqual(bob.c_channel_port, 2199)
        self.assertEqual(bob.cc_session, None)
        self.assertEqual(bob.processes, {})
        self.assertEqual(bob.dead_processes, {})
        self.assertEqual(bob.runnable, False)

    # verbose testing...

if __name__ == '__main__':
    unittest.main()
