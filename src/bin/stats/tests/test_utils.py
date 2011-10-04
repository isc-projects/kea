"""
Utilities and mock modules for unittests of statistics modules

"""
import os
import io
import time
import sys
import threading
import tempfile
import json
import signal

import msgq
import isc.config.cfgmgr
import stats
import stats_httpd

# Change value of BIND10_MSGQ_SOCKET_FILE in environment variables
if 'BIND10_MSGQ_SOCKET_FILE' not in os.environ:
    os.environ['BIND10_MSGQ_SOCKET_FILE'] = tempfile.mktemp(prefix='msgq_socket_')

class SignalHandler():
    """A signal handler class for deadlock in unittest"""
    def __init__(self, fail_handler, timeout=20):
        """sets a schedule in SIGARM for invoking the handler via
        unittest.TestCase after timeout seconds (default is 20)"""
        self.fail_handler = fail_handler
        self.orig_handler = signal.signal(signal.SIGALRM, self.sig_handler)
        signal.alarm(timeout)

    def reset(self):
        """resets the schedule in SIGALRM"""
        signal.alarm(0)
        signal.signal(signal.SIGALRM, self.orig_handler)

    def sig_handler(self, signal, frame):
        """envokes unittest.TestCase.fail as a signal handler"""
        self.fail_handler("A deadlock might be detected")

def send_command(command_name, module_name, params=None, session=None, nonblock=False, timeout=None):
    if session is not None:
        cc_session = session
    else:
        cc_session = isc.cc.Session()
    if timeout is not None:
        orig_timeout = cc_session.get_timeout()
        cc_session.set_timeout(timeout * 1000)
    command = isc.config.ccsession.create_command(command_name, params)
    seq = cc_session.group_sendmsg(command, module_name)
    try:
        (answer, env) = cc_session.group_recvmsg(nonblock, seq)
        if answer:
            return isc.config.ccsession.parse_answer(answer)
    except isc.cc.SessionTimeout:
        pass
    finally:
        if timeout is not None:
            cc_session.set_timeout(orig_timeout)
        if session is None:
            cc_session.close()

def send_shutdown(module_name, **kwargs):
    return send_command("shutdown", module_name, **kwargs)

class ThreadingServerManager:
    def __init__(self, server, *args, **kwargs):
        self.server = server(*args, **kwargs)
        self.server_name = server.__name__
        self.server._thread = threading.Thread(
            name=self.server_name, target=self.server.run)
        self.server._thread.daemon = True

    def run(self):
        self.server._thread.start()
        self.server._started.wait()
        self.server._started.clear()

    def shutdown(self):
        self.server.shutdown()
        self.server._thread.join(0) # timeout is 0

def do_nothing(*args, **kwargs): pass

class dummy_sys:
    """Dummy for sys"""
    class dummy_io:
        write = do_nothing
    stdout = stderr = dummy_io()

class MockMsgq:
    def __init__(self):
        self._started = threading.Event()
        # suppress output to stdout and stderr
        msgq.sys = dummy_sys()
        msgq.print = do_nothing
        self.msgq = msgq.MsgQ(verbose=False)
        result = self.msgq.setup()
        if result:
            sys.exit("Error on Msgq startup: %s" % result)

    def run(self):
        self._started.set()
        try:
            self.msgq.run()
        except Exception:
            pass

    def shutdown(self):
        # do nothing
        pass

class MockCfgmgr:
    def __init__(self):
        self._started = threading.Event()
        self.cfgmgr = isc.config.cfgmgr.ConfigManager(
            os.environ['CONFIG_TESTDATA_PATH'], "b10-config.db")
        self.cfgmgr.read_config()

    def run(self):
        self._started.set()
        try:
            self.cfgmgr.run()
        except Exception:
            pass

    def shutdown(self):
        self.cfgmgr.running = False

class MockBoss:
    spec_str = """\
{
  "module_spec": {
    "module_name": "Boss",
    "module_description": "Mock Master process",
    "config_data": [],
    "commands": [
      {
        "command_name": "sendstats",
        "command_description": "Send data to a statistics module at once",
        "command_args": []
      }
    ],
    "statistics": [
      {
        "item_name": "boot_time",
        "item_type": "string",
        "item_optional": false,
        "item_default": "1970-01-01T00:00:00Z",
        "item_title": "Boot time",
        "item_description": "A date time when bind10 process starts initially",
        "item_format": "date-time"
      }
    ]
  }
}
"""
    _BASETIME = (2011, 6, 22, 8, 14, 8, 2, 173, 0)

    def __init__(self):
        self._started = threading.Event()
        self.running = False
        self.spec_file = io.StringIO(self.spec_str)
        # create ModuleCCSession object
        self.mccs = isc.config.ModuleCCSession(
            self.spec_file,
            self.config_handler,
            self.command_handler)
        self.spec_file.close()
        self.cc_session = self.mccs._session
        self.got_command_name = ''

    def run(self):
        self.mccs.start()
        self.running = True
        self._started.set()
        try:
            while self.running:
                self.mccs.check_command(False)
        except Exception:
            pass

    def shutdown(self):
        self.running = False

    def config_handler(self, new_config):
        return isc.config.create_answer(0)

    def command_handler(self, command, *args, **kwargs):
        self._started.set()
        self.got_command_name = command
        params = { "owner": "Boss",
                   "data": {
                'boot_time': time.strftime('%Y-%m-%dT%H:%M:%SZ', self._BASETIME)
                }
                   }
        if command == 'sendstats':
            send_command("set", "Stats", params=params, session=self.cc_session)
            return isc.config.create_answer(0)
        elif command == 'getstats':
            return isc.config.create_answer(0, params)
        return isc.config.create_answer(1, "Unknown Command")

class MockAuth:
    spec_str = """\
{
  "module_spec": {
    "module_name": "Auth",
    "module_description": "Mock Authoritative service",
    "config_data": [],
    "commands": [
      {
        "command_name": "sendstats",
        "command_description": "Send data to a statistics module at once",
        "command_args": []
      }
    ],
    "statistics": [
      {
        "item_name": "queries.tcp",
        "item_type": "integer",
        "item_optional": false,
        "item_default": 0,
        "item_title": "Queries TCP",
        "item_description": "A number of total query counts which all auth servers receive over TCP since they started initially"
      },
      {
        "item_name": "queries.udp",
        "item_type": "integer",
        "item_optional": false,
        "item_default": 0,
        "item_title": "Queries UDP",
        "item_description": "A number of total query counts which all auth servers receive over UDP since they started initially"
      }
    ]
  }
}
"""
    def __init__(self):
        self._started = threading.Event()
        self.running = False
        self.spec_file = io.StringIO(self.spec_str)
        # create ModuleCCSession object
        self.mccs = isc.config.ModuleCCSession(
            self.spec_file,
            self.config_handler,
            self.command_handler)
        self.spec_file.close()
        self.cc_session = self.mccs._session
        self.got_command_name = ''
        self.queries_tcp = 3
        self.queries_udp = 2

    def run(self):
        self.mccs.start()
        self.running = True
        self._started.set()
        try:
            while self.running:
                self.mccs.check_command(False)
        except Exception:
            pass

    def shutdown(self):
        self.running = False

    def config_handler(self, new_config):
        return isc.config.create_answer(0)

    def command_handler(self, command, *args, **kwargs):
        self.got_command_name = command
        if command == 'sendstats':
            params = { "owner": "Auth",
                       "data": { 'queries.tcp': self.queries_tcp,
                                 'queries.udp': self.queries_udp } }
            return send_command("set", "Stats", params=params, session=self.cc_session)
        return isc.config.create_answer(1, "Unknown Command")

class MyStats(stats.Stats):
    def __init__(self):
        self._started = threading.Event()
        stats.Stats.__init__(self)

    def run(self):
        self._started.set()
        try:
            self.start()
        except Exception:
            pass

    def shutdown(self):
        self.command_shutdown()

class MyStatsHttpd(stats_httpd.StatsHttpd):
    ORIG_SPECFILE_LOCATION = stats_httpd.SPECFILE_LOCATION
    def __init__(self, *server_address):
        self._started = threading.Event()
        if server_address:
            stats_httpd.SPECFILE_LOCATION = self.create_specfile(*server_address)
            try:
                stats_httpd.StatsHttpd.__init__(self)
            finally:
                if hasattr(stats_httpd.SPECFILE_LOCATION, "close"):
                    stats_httpd.SPECFILE_LOCATION.close()
                stats_httpd.SPECFILE_LOCATION = self.ORIG_SPECFILE_LOCATION
        else:
            stats_httpd.StatsHttpd.__init__(self)

    def create_specfile(self, *server_address):
        spec_io = open(self.ORIG_SPECFILE_LOCATION)
        try:
            spec = json.load(spec_io)
            spec_io.close()
            config = spec['module_spec']['config_data']
            for i in range(len(config)):
                if config[i]['item_name'] == 'listen_on':
                    config[i]['item_default'] = \
                        [ dict(address=a[0], port=a[1]) for a in server_address ]
                    break
            return io.StringIO(json.dumps(spec))
        finally:
            spec_io.close()

    def run(self):
        self._started.set()
        try:
            self.start()
        except Exception:
            pass

    def shutdown(self):
        self.command_handler('shutdown', None)

class BaseModules:
    def __init__(self):
        # MockMsgq
        self.msgq = ThreadingServerManager(MockMsgq)
        self.msgq.run()
        # Check whether msgq is ready. A SessionTimeout is raised here if not.
        isc.cc.session.Session().close()
        # MockCfgmgr
        self.cfgmgr = ThreadingServerManager(MockCfgmgr)
        self.cfgmgr.run()
        # MockBoss
        self.boss = ThreadingServerManager(MockBoss)
        self.boss.run()
        # MockAuth
        self.auth = ThreadingServerManager(MockAuth)
        self.auth.run()

    def shutdown(self):
        # MockAuth
        self.auth.shutdown()
        # MockBoss
        self.boss.shutdown()
        # MockCfgmgr
        self.cfgmgr.shutdown()
        # MockMsgq
        self.msgq.shutdown()
        # remove the unused socket file
        socket_file = self.msgq.server.msgq.socket_file
        try:
            if os.path.exists(socket_file):
                os.remove(socket_file)
        except OSError:
            pass
