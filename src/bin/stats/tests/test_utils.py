"""
Utilities and mock modules for unittests of statistics modules

"""
import os
import io
import time
import sys
import threading
import tempfile

import msgq
import isc.config.cfgmgr 
import stats
import stats_httpd

# TODO: consider appropriate timeout seconds
TIMEOUT_SEC = 0.01

def send_command(command_name, module_name, params=None, session=None, nonblock=False, timeout=TIMEOUT_SEC*2):
    if not session:
        cc_session = isc.cc.Session()
    else:
        cc_session = session
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
        if not session:
            cc_session.close()
        else:
            cc_session.set_timeout(orig_timeout)

def send_shutdown(module_name):
    return send_command("shutdown", module_name)

class ThreadingServerManager:
    def __init__(self, server_class):
        self.server_class = server_class
        self.server_class_name = server_class.__name__
        self.server = self.server_class()
        self.server._thread = threading.Thread(
            name=self.server_class_name, target=self.server.run)
        self.server._thread.daemon = True
        
    def run(self):
        self.server._thread.start()
        self.server._started.wait()

    def shutdown(self):
        self.server.shutdown()
        self.server._thread.join(TIMEOUT_SEC)

class MockMsgq:
    def __init__(self):
        self._started = threading.Event()
        self.msgq = msgq.MsgQ(None)
        result = self.msgq.setup()
        if result:
            sys.exit("Error on Msgq startup: %s" % result)

    def run(self):
        self._started.set()
        try:
            self.msgq.run()
        except Exception:
            pass
        finally:
            self.shutdown()

    def shutdown(self):
        self.msgq.shutdown()

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
        finally:
            self.shutdown()

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
        while self.running:
            self.mccs.check_command(False)

    def shutdown(self):
        self.running = False

    def config_handler(self, new_config):
        return isc.config.create_answer(0)

    def command_handler(self, command, *args, **kwargs):
        self.got_command_name = command
        if command == 'sendstats':
            params = { "owner": "Boss",
                       "data": {
                    'boot_time': time.strftime('%Y-%m-%dT%H:%M:%SZ', self._BASETIME)
                    } 
                       }
            return send_command("set", "Stats", params=params, session=self.cc_session)
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
        while self.running:
            self.mccs.check_command(False)

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
        stats.Stats.start(self)

    def shutdown(self):
        send_shutdown("Stats")

class MyStatsHttpd(stats_httpd.StatsHttpd):
    def __init__(self):
        self._started = threading.Event()
        stats_httpd.StatsHttpd.__init__(self)

    def run(self):
        self._started.set()
        stats_httpd.StatsHttpd.start(self)

    def shutdown(self):
        send_shutdown("StatsHttpd")

class BaseModules:
    def __init__(self):
        self.class_name = BaseModules.__name__

        # Change value of BIND10_MSGQ_SOCKET_FILE in environment variables
        os.environ['BIND10_MSGQ_SOCKET_FILE'] = tempfile.mktemp(prefix='unix_socket.')
        # MockMsgq
        self.msgq = ThreadingServerManager(MockMsgq)
        self.msgq.run()
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
