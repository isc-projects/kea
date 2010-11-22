"""
This program tests the boss process to make sure that it runs while
dropping permissions. It must be run as a user that can set permission.
"""
import unittest
import os
import sys
import subprocess
import select
import time
import pwd

# Set to a valid user name on the system to run setuid() test
#SUID_USER=None
SUID_USER="shane"

BIND10_EXE="../run_bind10.sh"
TIMEOUT=3

class TestBossArgs(unittest.TestCase):
    def _waitForString(self, bob, s):
        found_string = False
        start_time = time.time()
        while time.time() < start_time + TIMEOUT:
            (r,w,x) = select.select((bob.stdout,), (), (), TIMEOUT) 
            if bob.stdout in r:
                s = bob.stdout.readline()
                if s == '':
                    break
                if s.startswith(s): 
                    found_string = True
                    break
        return found_string

    def testNoArgs(self):
        """Run bind10 without any arguments"""
        bob = subprocess.Popen(args=(BIND10_EXE,),
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        started_ok = self._waitForString(bob, '[bind10] BIND 10 started')
        time.sleep(0.1)
        bob.terminate()
        bob.wait()
        self.assertTrue(started_ok)

    def testBadOption(self):
        """Run bind10 with a bogus option"""
        bob = subprocess.Popen(args=(BIND10_EXE, "--badoption"),
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        failed = self._waitForString(bob, 'bind10: error: no such option: --badoption')
        time.sleep(0.1)
        bob.terminate()
        self.assertTrue(bob.wait() == 2)
        self.assertTrue(failed)

    def testArgument(self):
        """Run bind10 with an argument (this is not allowed)"""
        bob = subprocess.Popen(args=(BIND10_EXE, "argument"),
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        failed = self._waitForString(bob, 'Usage: bind10 [options]')
        time.sleep(0.1)
        bob.terminate()
        self.assertTrue(bob.wait() == 1)
        self.assertTrue(failed)

    def testBadUser(self):
        """Run bind10 with a bogus user"""
        bob = subprocess.Popen(args=(BIND10_EXE, "-u", "bogus_user"),
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        failed = self._waitForString(bob, "bind10: invalid user: 'bogus_user'")
        time.sleep(0.1)
        bob.terminate()
        self.assertTrue(bob.wait() == 1)
        self.assertTrue(failed)

    def testBadUid(self):
        """Run bind10 with a bogus user ID"""
        bob = subprocess.Popen(args=(BIND10_EXE, "-u", "999999999"),
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        failed = self._waitForString(bob, "bind10: invalid user: '999999999'")
        time.sleep(0.1)
        bob.terminate()
        self.assertTrue(bob.wait() == 1)
        self.assertTrue(failed)

    def testFailSetUser(self):
        """Try the -u option when we don't run as root"""
        global SUID_USER
        if SUID_USER is None:
            self.skipTest("test needs a valid user (set when run)")
        if os.getuid() == 0:
            self.skipTest("test must not be run as root (uid is 0)")
        # XXX: we depend on the "nobody" user
        bob = subprocess.Popen(args=(BIND10_EXE, "-u", "nobody"),
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        failed = self._waitForString(bob, "[bind10] Error on startup: Unable to start b10-msgq; Unable to change to user nobody")
        time.sleep(0.1)
        bob.terminate()
        self.assertTrue(bob.wait() == 1)
        self.assertTrue(failed)

    def testSetUser(self):
        """Try the -u option"""
        global SUID_USER
        if SUID_USER is None:
            self.skipTest("test needs a valid user (set when run)")
        if os.getuid() != 0:
            self.skipTest("test must run as root (uid is not 0)")
        if os.geteuid() != 0:
            self.skipTest("test must run as root (euid is not 0)")

        bob = subprocess.Popen(args=(BIND10_EXE, "-u", SUID_USER),
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        started_ok = self._waitForString(bob, '[bind10] BIND 10 started')
        self.assertTrue(started_ok)
        ps = subprocess.Popen(args=("ps", "axo", "user,pid"),
                              stdout=subprocess.PIPE)
        s = ps.stdout.readline()
        ps_user = None
        while True:
            s = ps.stdout.readline()
            if s == '': break
            (user, pid) = s.split()
            if int(pid) == bob.pid:
                ps_user = user.decode()
                break
        self.assertTrue(ps_user is not None)
        self.assertTrue(ps_user == SUID_USER)
        time.sleep(0.1)
        bob.terminate()
        x = bob.wait()
        self.assertTrue(bob.wait() == 0)

    def testPrettyName(self):
        """Try the --pretty-name option."""
        CMD_PRETTY_NAME = b'bob-name-test'
        bob = subprocess.Popen(args=(BIND10_EXE, '--pretty-name',
            CMD_PRETTY_NAME), stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        started_ok = self._waitForString(bob, '[bind10] BIND 10 started')
        self.assertTrue(started_ok)
        ps = subprocess.Popen(args=("ps", "axo", "pid,comm"),
                              stdout=subprocess.PIPE)
        s = ps.stdout.readline()
        command = None
        while True:
            s = ps.stdout.readline()
            if s == '': break
            (pid,comm) = s.split(None, 1)
            if int(pid) == bob.pid:
                command = comm
                break
        self.assertEqual(command, CMD_PRETTY_NAME + b'\n')
        time.sleep(0.1)
        bob.terminate()
        bob.wait()

if __name__ == '__main__':
    unittest.main()
