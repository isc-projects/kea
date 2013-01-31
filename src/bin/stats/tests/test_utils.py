# Copyright (C) 2011-2012  Internet Systems Consortium.
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

CONST_BASETIME = (2011, 6, 22, 8, 14, 8, 2, 173, 0)

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

    def shutdown(self, blocking=False):
        """Shut down the server by calling its own shutdown() method.
           Then wait for its thread to finish. If blocking is True,
           the thread.join() blocks until the thread finishes. If not,
           it uses a zero timeout. The latter is necessary in a number
           of existing tests. We should redo this part (we should not
           even need threads in most, if not all, of these threads, see
           ticket #1668)"""
        self.server.shutdown()
        if blocking:
            self.server._thread.join()
        else:
            self.server._thread.join(0) # timeout is 0

class MockMsgq:
    def __init__(self):
        self._started = threading.Event()
        self.msgq = msgq.MsgQ(verbose=False)
        result = self.msgq.setup()
        if result:
            sys.exit("Error on Msgq startup: %s" % result)

    def run(self):
        self._started.set()
        try:
            self.msgq.run()
        finally:
            # Make sure all the sockets, etc, are removed once it stops.
            self.msgq.shutdown()

    def shutdown(self):
        # Ask it to terminate nicely
        self.msgq.stop()

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

class MockInit:
    spec_str = """\
{
  "module_spec": {
    "module_name": "Init",
    "module_description": "Mock Master process",
    "config_data": [
      {
        "item_name": "components",
        "item_type": "named_set",
        "item_optional": false,
        "item_default": {
          "b10-stats": { "address": "Stats", "kind": "dispensable" },
          "b10-cmdctl": { "special": "cmdctl", "kind": "needed" }
        },
        "named_set_item_spec": {
          "item_name": "component",
          "item_type": "map",
          "item_optional": false,
          "item_default": { },
          "map_item_spec": [
            {
              "item_name": "special",
              "item_optional": true,
              "item_type": "string"
            },
            {
              "item_name": "process",
              "item_optional": true,
              "item_type": "string"
            },
            {
              "item_name": "kind",
              "item_optional": false,
              "item_type": "string",
              "item_default": "dispensable"
            },
            {
              "item_name": "address",
              "item_optional": true,
              "item_type": "string"
            },
            {
              "item_name": "params",
              "item_optional": true,
              "item_type": "list",
              "list_item_spec": {
                "item_name": "param",
                "item_optional": false,
                "item_type": "string",
                "item_default": ""
              }
            },
            {
              "item_name": "priority",
              "item_optional": true,
              "item_type": "integer"
            }
          ]
        }
      }
    ],
    "commands": [
      {
        "command_name": "shutdown",
        "command_description": "Shut down BIND 10",
        "command_args": []
      },
      {
        "command_name": "ping",
        "command_description": "Ping the b10-init process",
        "command_args": []
      },
      {
        "command_name": "show_processes",
        "command_description": "List the running BIND 10 processes",
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
    _BASETIME = CONST_BASETIME

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
        self.pid_list = [[ 9999, "b10-auth", "Auth" ],
                         [ 9998, "b10-auth-2", "Auth" ]]
        self.statistics_data = {
            'boot_time': time.strftime('%Y-%m-%dT%H:%M:%SZ', self._BASETIME)
            }

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
        sdata = self.statistics_data
        if command == 'getstats':
            return isc.config.create_answer(0, sdata)
        elif command == 'show_processes':
            # Return dummy pids
            return isc.config.create_answer(
                0, self.pid_list)
        return isc.config.create_answer(1, "Unknown Command")

class MockAuth:
    spec_str = """\
{
  "module_spec": {
    "module_name": "Auth",
    "module_description": "Mock Authoritative service",
    "config_data": [],
    "commands": [],
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
      },
      {
        "item_name": "queries.perzone",
        "item_type": "list",
        "item_optional": false,
        "item_default": [
          {
            "zonename" : "test1.example",
            "queries.udp" : 1,
            "queries.tcp" : 2
          },
          {
            "zonename" : "test2.example",
            "queries.udp" : 3,
            "queries.tcp" : 4
          }
        ],
        "item_title": "Queries per zone",
        "item_description": "Queries per zone",
        "list_item_spec": {
          "item_name": "zones",
          "item_type": "map",
          "item_optional": false,
          "item_default": {},
          "map_item_spec": [
            {
              "item_name": "zonename",
              "item_type": "string",
              "item_optional": false,
              "item_default": "",
              "item_title": "Zonename",
              "item_description": "Zonename"
            },
            {
              "item_name": "queries.udp",
              "item_type": "integer",
              "item_optional": false,
              "item_default": 0,
              "item_title": "Queries UDP per zone",
              "item_description": "A number of UDP query counts per zone"
            },
            {
              "item_name": "queries.tcp",
              "item_type": "integer",
              "item_optional": false,
              "item_default": 0,
              "item_title": "Queries TCP per zone",
              "item_description": "A number of TCP query counts per zone"
            }
          ]
        }
      },
      {
        "item_name": "nds_queries.perzone",
        "item_type": "named_set",
        "item_optional": false,
        "item_default": {
          "test10.example" : {
            "queries.udp" : 1,
            "queries.tcp" : 2
          },
          "test20.example" : {
            "queries.udp" : 3,
            "queries.tcp" : 4
          }
        },
        "item_title": "Queries per zone",
        "item_description": "Queries per zone",
        "named_set_item_spec": {
          "item_name": "zonename",
          "item_type": "map",
          "item_optional": false,
          "item_default": {},
          "item_title": "Zonename",
          "item_description": "Zonename",
          "map_item_spec": [
            {
              "item_name": "queries.udp",
              "item_type": "integer",
              "item_optional": false,
              "item_default": 0,
              "item_title": "Queries UDP per zone",
              "item_description": "A number of UDP query counts per zone"
            },
            {
              "item_name": "queries.tcp",
              "item_type": "integer",
              "item_optional": false,
              "item_default": 0,
              "item_title": "Queries TCP per zone",
              "item_description": "A number of TCP query counts per zone"
            }
          ]
        }
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
        self.queries_per_zone = [{
                'zonename': 'test1.example',
                'queries.tcp': 5,
                'queries.udp': 4
                }]
        self.nds_queries_per_zone = {
            'test10.example': {
                'queries.tcp': 5,
                'queries.udp': 4
                }
            }

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
        sdata = { 'queries.tcp': self.queries_tcp,
                  'queries.udp': self.queries_udp,
                  'queries.perzone' : self.queries_per_zone,
                  'nds_queries.perzone' : {
                    'test10.example': {
                    'queries.tcp': \
                      isc.cc.data.find(
                        self.nds_queries_per_zone,
                        'test10.example/queries.tcp')
                    }
                  },
                  'nds_queries.perzone/test10.example/queries.udp' :
                      isc.cc.data.find(self.nds_queries_per_zone,
                                       'test10.example/queries.udp')
                }
        if command == 'getstats':
            return isc.config.create_answer(0, sdata)
        return isc.config.create_answer(1, "Unknown Command")

class MyStats(stats.Stats):

    stats._BASETIME = CONST_BASETIME
    stats.get_timestamp = lambda: time.mktime(CONST_BASETIME)
    stats.get_datetime = lambda x=None: time.strftime("%Y-%m-%dT%H:%M:%SZ", CONST_BASETIME)

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
        # MockInit
        self.b10_init = ThreadingServerManager(MockInit)
        self.b10_init.run()
        # MockAuth
        self.auth = ThreadingServerManager(MockAuth)
        self.auth.run()
        self.auth2 = ThreadingServerManager(MockAuth)
        self.auth2.run()


    def shutdown(self):
        # MockMsgq. We need to wait (blocking) for it, otherwise it'll wipe out
        # a socket for another test during its shutdown.
        self.msgq.shutdown(True)

        # We also wait for the others, but these are just so we don't create
        # too many threads in parallel.

        # MockAuth
        self.auth2.shutdown(True)
        self.auth.shutdown(True)
        # MockInit
        self.b10_init.shutdown(True)
        # MockCfgmgr
        self.cfgmgr.shutdown(True)
        # remove the unused socket file
        socket_file = self.msgq.server.msgq.socket_file
        try:
            if os.path.exists(socket_file):
                os.remove(socket_file)
        except OSError:
            pass
