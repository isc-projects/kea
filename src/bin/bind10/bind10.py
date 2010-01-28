"""\
This file implements the Boss of Bind (BoB, or bob) program.

It's purpose is to start up the BIND 10 system, and then manage the
processes, by starting and stopping processes, plus restarting
processes that exit.

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

# TODO: start up statistics thingy

import subprocess
import signal
import os
import sys
import re
import errno
import time
import select
import pprint
from optparse import OptionParser, OptionValueError

import ISC.CC
import isc

# This is the version that gets displayed to the user.
__version__ = "v20091030 (Paving the DNS Parking Lot)"

# Nothing at all to do with the 1990-12-10 article here:
# http://www.subgenius.com/subg-digest/v2/0056.html

class ProcessInfo:
    """Information about a process"""

    dev_null = open("/dev/null", "w")

    def _spawn(self):
        if self.dev_null_stdout:
            spawn_stdout = self.dev_null
        else:
            spawn_stdout = None
        spawn_env = self.env
        spawn_env['PATH'] = os.environ['PATH']
        spawn_env['PYTHON_EXEC'] = os.environ['PYTHON_EXEC']
        self.process = subprocess.Popen(self.args,
                                        stdin=subprocess.PIPE,
                                        stdout=spawn_stdout,
                                        stderr=spawn_stdout,
                                        close_fds=True,
                                        env=spawn_env,)
        self.pid = self.process.pid

    def __init__(self, name, args, env={}, dev_null_stdout=False):
        self.name = name 
        self.args = args
        self.env = env
        self.dev_null_stdout = dev_null_stdout
        self._spawn()

    def respawn(self):
        self._spawn()

class BoB:
    """Boss of BIND class."""
    def __init__(self, c_channel_port=9912, verbose=False):
        """Initialize the Boss of BIND. This is a singleton (only one
        can run).
        
        The c_channel_port specifies the TCP/IP port that the msgq
        process listens on. If verbose is True, then the boss reports
        what it is doing.
        """
        self.verbose = verbose
        self.c_channel_port = c_channel_port
        self.cc_session = None
        self.processes = {}
        self.dead_processes = {}
        self.runnable = False

    def config_handler(self, new_config):
        if self.verbose:
            print("[XX] handling new config:")
            print(new_config)
        # TODO

    def command_handler(self, command):
        # a command is of the form [ "command", { "arg1": arg1, "arg2": arg2 } ]
        if self.verbose:
            print("[XX] Boss got command:")
            print(command)
        answer = None
        if type(command) != list or len(command) == 0:
            answer = { "result": [ 1, "bad command" ] }
        else:
            cmd = command[0]
            if cmd == "shutdown":
                print("[XX] got shutdown command")
                self.runnable = False
                answer = { "result": [ 0 ] }
            elif cmd == "print_message":
                if len(command) > 1 and type(command[1]) == dict and "message" in command[1]:
                    print(command[1]["message"])
                answer = { "result": [ 0 ] }
            else:
                answer = { "result": [ 1, "Unknown command" ] }
        return answer
    
    def startup(self):
        """Start the BoB instance.
 
        Returns None if successful, otherwise an string describing the
        problem.
        """
        # start the c-channel daemon
        if self.verbose:
            sys.stdout.write("Starting msgq using port %d\n" % 
                             self.c_channel_port)
        c_channel_env = { "ISC_MSGQ_PORT": str(self.c_channel_port), }
        try:
            c_channel = ProcessInfo("msgq", "msgq", c_channel_env, True)
        except Exception as e:
            return "Unable to start msgq; " + str(e)
        self.processes[c_channel.pid] = c_channel
        if self.verbose:
            sys.stdout.write("Started msgq (PID %d)\n" % c_channel.pid)

        # now connect to the c-channel
        cc_connect_start = time.time()
        while self.cc_session is None:
            # if we have been trying for "a while" give up
            if (time.time() - cc_connect_start) > 5:
                c_channel.process.kill()
                return "Unable to connect to c-channel after 5 seconds"
            # try to connect, and if we can't wait a short while
            try:
                self.cc_session = ISC.CC.Session(self.c_channel_port)
            except ISC.CC.session.SessionError:
                time.sleep(0.1)
        #self.cc_session.group_subscribe("Boss", "boss")

        # start the configuration manager
        if self.verbose:
            sys.stdout.write("Starting b10-cfgmgr\n")
        try:
            bind_cfgd = ProcessInfo("b10-cfgmgr", "b10-cfgmgr")
        except Exception as e:
            c_channel.process.kill()
            return "Unable to start b10-cfgmgr; " + str(e)
        self.processes[bind_cfgd.pid] = bind_cfgd
        if self.verbose:
            sys.stdout.write("Started b10-cfgmgr (PID %d)\n" % bind_cfgd.pid)

        # TODO: once this interface is done, replace self.cc_session
        # by this one
        # sleep until b10-cfgmgr is fully up and running, this is a good place
        # to have a (short) timeout on synchronized groupsend/receive
        time.sleep(1)
        if self.verbose:
            print("[XX] starting ccsession")
        self.ccs = isc.config.CCSession("bob.spec", self.config_handler, self.command_handler)
        if self.verbose:
            print("[XX] ccsession started")

        # start the parking lot
        # XXX: this must be read from the configuration manager in the future
        # XXX: we hardcode port 5300
        if self.verbose:
            sys.stdout.write("Starting parkinglot on port 5300\n")
        try:
            parkinglot = ProcessInfo("parkinglot", ["parkinglot", "-p", "5300"])
        except Exception as e:
            c_channel.process.kill()
            bind_cfgd.process.kill()
            return "Unable to start parkinglot; " + str(e)
        self.processes[parkinglot.pid] = parkinglot
        if self.verbose:
            sys.stdout.write("Started parkinglot (PID %d)\n" % parkinglot.pid)

        # start the b10-cmdctl
        # XXX: we hardcode port 8080
        if self.verbose:
            sys.stdout.write("Starting b10-cmdctl on port 8080\n")
        try:
            cmd_ctrld = ProcessInfo("b10-cmdctl", ['b10-cmdctl'])
        except Exception as e:
            c_channel.process.kill()
            bind_cfgd.process.kill()
            parkinglot.process.kill()
            return "Unable to start b10-cmdctl; " + str(e)
        self.processes[cmd_ctrld.pid] = cmd_ctrld
        if self.verbose:
            sys.stdout.write("Started b10-cmdctl (PID %d)\n" % cmd_ctrld.pid)

        self.runnable = True

        return None

    def stop_all_processes(self):
        """Stop all processes."""
        cmd = { "command": ['shutdown']}
        self.cc_session.group_sendmsg(cmd, 'Boss', 'Cmd-Ctrld')
        self.cc_session.group_sendmsg(cmd, "Boss", "ConfigManager")
        self.cc_session.group_sendmsg(cmd, "Boss", "ParkingLot")

    def stop_process(self, process):
        """Stop the given process, friendly-like."""
        # XXX nothing yet
        pass

    def shutdown(self):
        """Stop the BoB instance."""
        if self.verbose:
            sys.stdout.write("Stopping the server.\n")
        # first try using the BIND 10 request to stop
        try:
            self.stop_all_processes()
        except:
            pass
        # XXX: some delay probably useful... how much is uncertain
        time.sleep(0.1)  
        self.reap_children()
        # next try sending a SIGTERM
        processes_to_stop = list(self.processes.values())
        unstopped_processes = []
        for proc_info in processes_to_stop:
            if self.verbose:
                sys.stdout.write("Sending SIGTERM to %s (PID %d).\n" % 
                                 (proc_info.name, proc_info.pid))
            try:
                proc_info.process.terminate()
            except OSError as o:
                # ignore these (usually ESRCH because the child
                # finally exited)
                pass
        # XXX: some delay probably useful... how much is uncertain
        time.sleep(0.1)  
        self.reap_children()
        # finally, send a SIGKILL (unmaskable termination)
        processes_to_stop = unstopped_processes
        for proc_info in processes_to_stop:
            if self.verbose:
                sys.stdout.write("Sending SIGKILL to %s (PID %d).\n" % 
                                 (proc_info.name, proc_info.pid))
            try:
                proc_info.process.kill()
            except OSError as o:
                # ignore these (usually ESRCH because the child
                # finally exited)
                pass
        if self.verbose:
            sys.stdout.write("All processes ended, server done.\n")

    def reap_children(self):
        """Check to see if any of our child processes have exited, 
        and note this for later handling. 
        """
        while True:
            try:
                (pid, exit_status) = os.waitpid(-1, os.WNOHANG)
            except OSError as o:
                if o.errno == errno.ECHILD: break
                # XXX: should be impossible to get any other error here
                raise
            if pid == 0: break
            if pid in self.processes:
                proc_info = self.processes.pop(pid)
                self.dead_processes[proc_info.pid] = proc_info
                if self.verbose:
                    sys.stdout.write("Process %s (PID %d) died.\n" % 
                                     (proc_info.name, proc_info.pid))
                if proc_info.name == "msgq":
                    if self.verbose:
                        sys.stdout.write(
                                     "The msgq process died, shutting down.\n")
                    self.runnable = False
            else:
                sys.stdout.write("Unknown child pid %d exited.\n" % pid)

    # 'old' command style, uncommented for now
    # move the handling below move to command_handler please
    #def recv_and_process_cc_msg(self):
        #"""Receive and process the next message on the c-channel,
        #if any."""
        #self.ccs.checkCommand()
        #msg, envelope = self.cc_session.group_recvmsg(False)
        #print(msg)
        #if msg is None:
        #    return
        #if not ((type(msg) is dict) and (type(envelope) is dict)):
        #    if self.verbose:
        #        sys.stdout.write("Non-dictionary message\n")
        #    return
        #if not "command" in msg:
        #    if self.verbose:
        #        if "msg" in envelope:
        #            del envelope['msg']
        #        sys.stdout.write("Unknown message received\n")
        #        sys.stdout.write(pprint.pformat(envelope) + "\n")
        #        sys.stdout.write(pprint.pformat(msg) + "\n")
        #    return

        #cmd = msg['command']
        #if not (type(cmd) is list):
        #    if self.verbose:
        #        sys.stdout.write("Non-list command\n")
        #    return
        #
        # done checking and extracting... time to execute the command
        #if cmd[0] == "shutdown":
        #    if self.verbose:
        #        sys.stdout.write("shutdown command received\n")
        #    self.runnable = False
        #    # XXX: reply here?
        #elif cmd[0] == "getProcessList":
        #    if self.verbose:
        #        sys.stdout.write("getProcessList command received\n")
        #    live_processes = [ ]
        #    for proc_info in processes:
        #        live_processes.append({ "name": proc_info.name, 
        #                                "args": proc_info.args, 
        #                                "pid": proc_info.pid, })
        #    dead_processes = [ ]
        #    for proc_info in dead_processes:
        #        dead_processes.append({ "name": proc_info.name, 
        #                                "args": proc_info.args, })
        #    cc.group_reply(envelope, { "response": cmd,
        #                               "sent": msg["sent"],
        #                               "live_processes": live_processes,
        #                               "dead_processes": dead_processes, })
        #else:
        #    if self.verbose:
        #        sys.stdout.write("Unknown command %s\n" % str(cmd))

    def restart_processes(self):
        """Restart any dead processes."""
        # XXX: this needs a back-off algorithm
        # if we're shutting down, then don't restart
        if not self.runnable:
            return
        # otherwise look through each dead process and try to restart
        still_dead = {}
        for proc_info in self.dead_processes.values():
            if self.verbose:
                sys.stdout.write("Resurrecting dead %s process...\n" % 
                                 proc_info.name)
            try:
                proc_info.respawn()
                self.processes[proc_info.pid] = proc_info
                if self.verbose:
                    sys.stdout.write("Resurrected %s (PID %d)\n" %
                                     (proc_info.name, proc_info.pid))
            except:
                still_dead[proc_info.pid] = proc_info
        # remember any processes that refuse to be resurrected
        self.dead_processes = still_dead

def reaper(signal_number, stack_frame):
    """A child process has died (SIGCHLD received)."""
    # don't do anything... 
    # the Python signal handler has been set up to write
    # down a pipe, waking up our select() bit
    pass
                   
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
    global options
    global boss_of_bind
    if options.verbose:
        sys.stdout.write("Received %s.\n" % get_signame(signal_number))
    signal.signal(signal.SIGCHLD, signal.SIG_DFL)
    boss_of_bind.runnable = False

def check_port(option, opt_str, value, parser):
    """Function to insure that the port we are passed is actually 
    a valid port number. Used by OptionParser() on startup."""
    if not re.match('^(6553[0-5]|655[0-2]\d|65[0-4]\d\d|6[0-4]\d{3}|[1-5]\d{4}|[1-9]\d{0,3}|0)$', value):
        raise OptionValueError("%s requires a port number (0-65535)" % opt_str)
    parser.values.msgq_port = value
  
def main():
    global options
    global boss_of_bind
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

    # Create wakeup pipe for signal handlers
    wakeup_pipe = os.pipe()
    signal.set_wakeup_fd(wakeup_pipe[1])

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

    # In our main loop, we check for dead processes or messages 
    # on the c-channel.
    wakeup_fd = wakeup_pipe[0]
    ccs_fd = boss_of_bind.ccs.getSocket().fileno()
    while boss_of_bind.runnable:
        # XXX: get time for next restart for timeout

        # select() can raise EINTR when a signal arrives, 
        # even if they are resumable, so we have to catch
        # the exception
        try:
            (rlist, wlist, xlist) = select.select([wakeup_fd, ccs_fd], [], [])
        except select.error as err:
            if err.args[0] == errno.EINTR:
                (rlist, wlist, xlist) = ([], [], [])
            else:
                sys.stderr.write("Error with select(); %s\n" % err)
                break

        for fd in rlist + xlist:
            if fd == ccs_fd:
                boss_of_bind.ccs.checkCommand()
            elif fd == wakeup_fd:
                os.read(wakeup_fd, 32)

        # clean up any processes that exited
        boss_of_bind.reap_children()
        boss_of_bind.restart_processes()

    # shutdown
    signal.signal(signal.SIGCHLD, signal.SIG_DFL)
    boss_of_bind.shutdown()

if __name__ == "__main__":
    main()
