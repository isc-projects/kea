"""
This program checks the BIND 10 boss interaction.
"""
import unittest
import subprocess
import time
import select
import isc.cc

BIND10_EXE="../run_bind10.sh"
TIMEOUT=3

class TestBossBindctl(unittest.TestCase):
    def _waitForString(self, bob, s):
        """Read the input from the Process object until we find the 
        string we're looking for or we timeout."""
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

    def testBasicBindctl(self):
        """Run basic bindctl"""
        # start bind10
        bob = subprocess.Popen(args=(BIND10_EXE,),
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        started_ok = self._waitForString(bob, '[bind10] BIND 10 started')

        # connect to the command channel
        self.cc = isc.cc.Session()

        # shut down 
        bob.terminate()
        bob.wait()


if __name__ == '__main__':
    unittest.main()

