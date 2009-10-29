"""\
This file implements the Boss of Bind (BoB, or bob) program.

It's purpose is to start up the BIND 10 system, and then manage the
processes, by starting, stopping, and restarting processes that exit.

To start the system, it first runs the c-channel program (msgq), then
connects to that. It then runs the configuration manager, and reads
its own configuration. Then it proceeds to starting other modules.

The Python subprocess module is used for starting processes, but
because this is not efficient for managing groups of processes,
SIGCHLD signals are caught and processed using the signal module.

Most of the logic is contained in the BoB class. However, since Python
requires that signal processing happen in the main thread, we do
signal handling outside of that class, in the code running for
__main__.
"""

import subprocess
import signal
import os
import sys
import re
import errno
import time
from optparse import OptionParser, OptionValueError

import ISC.CC

# This is the version that gets displayed to the user.
__version__ = "v20091028 (Paving the DNS Parking Lot)"

# Nothing at all to do with the 1990-12-10 article here:
# http://www.subgenius.com/subg-digest/v2/0056.html

class BoB:
    """Boss of BIND class."""
    def __init__(self, c_channel_port=9912, verbose=False):
        """Initialize the Boss of BIND. This is a singleton (only one
        can run).
        
        The c_channel_port specifies the TCP/IP port that the msgq
        process listens on. If verbose is True, then the boss reports
        what it is doing.
        """
        self.verbose = True
        self.c_channel_port = c_channel_port
        self.cc_process = None
        self.cc_session = None
        self.processes = {}
        self.dead_processes = {}
        self.component_processes = {}

    def startup(self):
        """Start the BoB instance.
 
        Returns None if successful, otherwise an string describing the
        problem.
        """
        dev_null = open("/dev/null", "w")
        # start the c-channel daemon
        if self.verbose:
            sys.stdout.write("Starting msgq using port %d\n" % self.c_channel_port)
        c_channel_env = { "ISC_MSGQ_PORT": str(self.c_channel_port), }
        try:
            c_channel = subprocess.Popen("msgq",
                                         stdin=subprocess.PIPE,
                                         stdout=dev_null,
                                         stderr=dev_null,
                                         close_fds=True,
                                         env=c_channel_env,)
        except:
            return "Unable to start msgq"
        self.processes[c_channel.pid] = c_channel
        if self.verbose:
            sys.stdout.write("Started msgq with PID %d\n" % c_channel.pid)

        # now connect to the c-channel
        cc_connect_start = time.time()
        while self.cc_session is None:
            # if we have been trying for "a while" give up
            if (time.time() - cc_connect_start) > 5:
                c_channel.kill()
                return "Unable to connect to c-channel after 5 seconds"
            # try to connect, and if we can't wait a short while
            try:
                self.cc_session = ISC.CC.Session(self.c_channel_port)
            except ISC.CC.session.SessionError:
                time.sleep(0.1)
        self.cc_session.group_subscribe("Boss")

        # start the configuration manager
        if self.verbose:
            sys.stdout.write("Starting bind-cfgd\n")
        try:
            bind_cfgd = subprocess.Popen("bind-cfgd",
                                         stdin=dev_null,
                                         stdout=dev_null,
                                         stderr=dev_null,
                                         close_fds=True,
                                         env={},)
        except:
            c_channel.kill()
            return "Unable to start bind-cfgd"
        self.processes[bind_cfgd.pid] = bind_cfgd
        if self.verbose:
            sys.stdout.write("Started bind-cfgd with PID %d\n" % bind_cfgd.pid)

        # start the parking lot
        # XXX: this must be read from the configuration manager in the future
        # XXX: we hardcode port 5300
        if self.verbose:
            sys.stdout.write("Starting parkinglot\n")
        try:
            parkinglot = subprocess.Popen(["parkinglot", "-p", "5300",],
                                          stdin=dev_null,
                                          stdout=dev_null,
                                          stderr=dev_null,
                                          close_fds=True,
                                          env={},)
        except:
            c_channel.kill()
            bind_cfgd.kill()
            return "Unable to start parkinglot"
        self.processes[parkinglot.pid] = parkinglot
        if self.verbose:
            sys.stdout.write("Started parkinglot with PID %d\n" % parkinglot.pid)

        # remember our super-important process
        self.cc_process = c_channel
        
        return None

    def stop_all_processes(self):
        """Stop all processes."""
        self.cc_session.group_sendmsg({ "shutdown": True }, "Boss")

    def stop_process(self, process):
        """Stop the given process, friendly-like."""
        # XXX nothing yet
        pass

    def shutdown(self):
        """Stop the BoB instance."""
        if self.verbose:
            sys.stdout.write("Stopping the server.\n")
        # first try using the BIND 10 request to stop
        if self.cc_session:
            try:
                self.stop_all_processes()
            except:
                pass
        time.sleep(0.1)  # XXX: some delay probably useful... how much is uncertain
        # next try sending a SIGTERM
        processes_to_stop = list(self.processes.values())
        unstopped_processes = []
        for process in processes_to_stop:
            if self.verbose:
                sys.stdout.write("Sending SIGTERM to process %d.\n" % process.pid)
            try:
                process.terminate()
            except OSError as o:
                # ignore these (usually ESRCH because the child
                # finally exited)
                pass
        time.sleep(0.1)  # XXX: some delay probably useful... how much is uncertain
        for process in processes_to_stop:
            (pid, exit_status) = os.waitpid(process.pid, os.WNOHANG)
            if pid == 0:
                unstopped_processes.append(process)
        # finally, send a SIGKILL (unmaskable termination)
        processes_to_stop = unstopped_processes
        for process in processes_to_stop:
            if self.verbose:
                sys.stdout.write("Sending SIGKILL to process %d.\n" % process.pid)
            try:
                process.kill()
            except OSError as o:
                # ignore these (usually ESRCH because the child
                # finally exited)
                pass
        if self.verbose:
            sys.stdout.write("All processes ended, server done.\n")

    def reap(self, pid, exit_status):
        """The process specified by pid has exited with the value
        exit_status, so perform any action necessary (cleanup,
        restart, and so on).
  
        Returns True if everything is okay, or False if a fatal error
        has been detected and the program should exit.
        """
        process = self.processes.pop(pid)
        self.dead_processes[process.pid] = process
        if self.verbose:
            sys.stdout.write("Process %d died.\n" % pid)
        if self.cc_process and (pid == self.cc_process.pid):
            if self.verbose:
                sys.stdout.write("The msgq process died, shutting down.\n")
            return False
        else:
            return True

if __name__ == "__main__":
    def reaper(signal_number, stack_frame):
        """A child process has died (SIGCHLD received)."""
        global boss_of_bind
        while True:
            try:
                (pid, exit_status) = os.waitpid(-1, os.WNOHANG)
            except OSError as o:
                if o.errno == errno.ECHILD: break
                raise
            if pid == 0: break
            if not boss_of_bind.reap(pid, exit_status):
                signal.signal(signal.SIGCHLD, signal.SIG_DFL)
                boss_of_bind.shutdown()
                sys.exit(0)
                   
                

    def get_signame(signal_number):
        """Return the symbolic name for a signal."""
        for sig in dir(signal):
            if sig.startswith("SIG") and sig[3].isalnum():
                if getattr(signal, sig) == signal_number:
                    return sig
        return "Unknown signal %d" % signal_number

    # XXX: perhaps register atexit() function and invoke that instead
    def fatal_signal(signal_number, stack_frame):
        """We need to exit (SIGINT or SIGTERM received)."""
        global boss_of_bind
        global options
        if options.verbose:
            sys.stdout.write("Received %s.\n" % get_signame(signal_number))
        signal.signal(signal.SIGCHLD, signal.SIG_DFL)
        if boss_of_bind:
            boss_of_bind.shutdown()
        sys.exit(0)

    def check_port(option, opt_str, value, parser):
        """Function to insure that the port we are passed is actually 
        a valid port number. Used by OptionParser() on startup."""
        if not re.match('^(6553[0-5]|655[0-2]\d|65[0-4]\d\d|6[0-4]\d{3}|[1-5]\d{4}|[1-9]\d{0,3}|0)$', value):
            raise OptionValueError("%s requires a port number (0-65535)" % opt_str)
        parser.values.msgq_port = value

    # Parse any command-line options.
    parser = OptionParser(version=__version__)
    parser.add_option("-v", "--verbose", dest="verbose", action="store_true",
                      help="display more about what is going on")
    parser.add_option("-m", "--msgq-port", dest="msgq_port", type="string",
                      action="callback", callback=check_port, default="9912",
                      help="port the msgq daemon will use")
    (options, args) = parser.parse_args()

    # Announce startup.
    if options.verbose:
        sys.stdout.write("BIND 10 %s\n" % __version__)

    # TODO: set process name, perhaps by:
    #       http://code.google.com/p/procname/
    #       http://github.com/lericson/procname/

    # Set signal handlers for catching child termination, as well
    # as our own demise.
    signal.signal(signal.SIGCHLD, reaper)
    signal.siginterrupt(signal.SIGCHLD, False)
    signal.signal(signal.SIGINT, fatal_signal)
    signal.signal(signal.SIGTERM, fatal_signal)

    # Go bob!
    boss_of_bind = BoB(int(options.msgq_port), options.verbose)
    startup_result = boss_of_bind.startup()
    if startup_result:
        sys.stderr.write("Error on startup: %s\n" % startup_result)
        sys.exit(1)

    while True:
        time.sleep(1)

