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

def _waitForString(bob, s):
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

class TestBossCmd(unittest.TestCase):
    @classmethod
    def setUpClass(cls):
        print("setupclass?")
        # start bind10
        cls._bob = subprocess.Popen(args=(BIND10_EXE,),
                               stdout=subprocess.PIPE, stderr=subprocess.STDOUT)
        started_ok = _waitForString(cls._bob, '[bind10] BIND 10 started')
        if not started_ok:
            cls._bob.terminate()
            cls._bob.wait()
            cls.fail('Unable to start BIND 10')

    @classmethod
    def tearDownClass(cls):
        # shut down bind10
        cls._bob.terminate()
        cls._bob.wait()

    def testPing(self):
        """Simple aliveness check"""
        ping_worked = False

        # connect to the command channel
        self.cc = isc.cc.Session()
        self.cc.group_subscribe('Boss')

        # send a ping
        cmd = { "command": ['ping']}
        seq = self.cc.group_sendmsg(cmd, 'Boss')

        # wait for a pong
        env, msg = self.cc.recvmsg(False, seq)
        if 'result' in msg:
            result = msg['result']
            if (result[0] == 0) and (result[1] == 'pong'):
                ping_worked = True

        # check that we were able to ping
        self.assertEqual(ping_worked, True)

    def _check_processes(self, process_list):
        # the msgq and cfgmgr are required, everything else is optional
        msgq_pid = None
        cfgmgr_pid = None
        for process in process_list:
            if len(process) != 2:
                return False
            if type(process[0]) != int:
                return False
            if type(process[1]) != str:
                return False
            if process[1] == 'b10-msgq':
                msgq_pid = process[0]
            elif process[1] == 'b10-cfgmgr':
                cfgmgr_pid = process[0]
        if msgq_pid and cfgmgr_pid:
            return True
        return False

    def testShowServices(self):
        """Get a list of children"""
        command_worked = False

        # connect to the command channel
        self.cc = isc.cc.Session()
        self.cc.group_subscribe('Boss')
    
        # send a ping
        cmd = { "command": ['show_processes']}
        seq = self.cc.group_sendmsg(cmd, 'Boss')

        # wait for a pong
        env, msg = self.cc.recvmsg(False, seq)
        if 'result' in msg:
            result = msg['result']
            if (result[0] == 0) and self._check_processes(result[1]):
                command_worked = True

        # check that we were able to ping
        self.assertEqual(command_worked, True)


if __name__ == '__main__':
    # Python 3.2 and later support the setUpClass() and tearDownClass() 
    # class methods to unittest, which are what we want to avoid having
    # to start/stop BIND 10 every time we run the test. For versions of
    # unittest that do not support this, we invoke them explicitly
    if not hasattr(unittest.TestCase, 'setUpClass'):
        TestBossCmd.setUpClass()
    unittest.main()
    if not hasattr(unittest.TestCase, 'tearDownClass'):
        TestBossCmd.tearDownClass()

