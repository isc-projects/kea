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
import threading
import json
import signal
import socket

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
        """invokes unittest.TestCase.fail as a signal handler"""
        self.fail_handler("A deadlock might be detected")

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

INIT_SPEC_STR = """\
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

# Note: this is derived of the spec for the DNS authoritative server, but
# for the purpose of this test, it's completely irrelevant to DNS.
# Some statisittics specs do not make sense for practical sense but used
# just cover various types of statistics data (list, map/dict, etc).
AUTH_SPEC_STR = """\
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

class MyModuleCCSession(isc.config.ConfigData):
    """Mocked ModuleCCSession class.

    This class incorporates the module spec directly from the file,
    and works as if the ModuleCCSession class as much as possible
    without involving network I/O.

    """
    def __init__(self, spec_file, config_handler, command_handler):
        module_spec = isc.config.module_spec_from_file(spec_file)
        isc.config.ConfigData.__init__(self, module_spec)
        self._session = self
        self.stopped = False
        self.closed = False
        self.lname = 'mock_mod_ccs'
        self._msg = None
        self._env = None

    def start(self):
        pass

    def send_stopping(self):
        self.stopped = True     # just record it's called to inspect it later

    def close(self):
        self.closed = True

    def check_command_without_recvmsg(self, msg, env):
        self._msg = msg
        self._env = env

class MyStats(stats.Stats):
    """A faked Stats class for unit tests.

    This class inherits most of the real Stats class, but replaces the
    ModuleCCSession with a fake one so we can avoid network I/O in tests,
    and can also inspect or tweak messages via the session more easily.
    This class also maintains some faked module information and statistics
    data that can be retrieved from the implementation of the Stats class.

    """
    def __init__(self):
        # First, setup some internal attributes.  All of them are essentially
        # private (so prefixed with double '_'), but some are defined as if
        # "protected" (with a single '_') for the convenient of tests that
        # may want to inspect or tweak them.

        # initial seq num for faked group_sendmsg, arbitrary choice.
        self._seq = 4200
        # if set, use them as faked response to group_recvmsg (see below).
        # it's a list of tuples, each of which is of (answer, envelope).
        self._answers = []
        # the default answer from faked recvmsg if _answers is empty
        self.__default_answer = isc.config.ccsession.create_answer(
            0, {'Init':
                    json.loads(INIT_SPEC_STR)['module_spec']['statistics'],
                'Auth':
                    json.loads(AUTH_SPEC_STR)['module_spec']['statistics']
                })
        # setup faked auth statistics
        self.__init_auth_stat()
        # statistics data for faked Init module
        self._init_sdata = {
            'boot_time': time.strftime('%Y-%m-%dT%H:%M:%SZ', CONST_BASETIME)
            }

        # Incorporate other setups of the real Stats module.  We use the faked
        # ModuleCCSession to avoid blocking network operation.  Note also that
        # we replace _init_statistics_data() (see below), so we don't
        # initialize statistics data yet.
        stats.Stats.__init__(self, MyModuleCCSession)

        # replace some (faked) ModuleCCSession methods so we can inspect/fake
        # the data exchanged via the CC session, then call
        # _init_statistics_data.  This will get the Stats module info from
        # the file directly and some amount information about the Init and
        # Auth modules (hardcoded below).
        self.cc_session.group_sendmsg = self.__group_sendmsg
        self.cc_session.group_recvmsg = self.__group_recvmsg
        self.cc_session.rpc_call = self.__rpc_call
        stats.Stats._init_statistics_data(self)

    def __init_auth_stat(self):
        self._queries_tcp = 3
        self._queries_udp = 2
        self._queries_per_zone = [{
                'zonename': 'test1.example', 'queries.tcp': 5, 'queries.udp': 4
                }]
        self._nds_queries_per_zone = \
            { 'test10.example': { 'queries.tcp': 5, 'queries.udp': 4 } }
        self._auth_sdata = \
            { 'queries.tcp': self._queries_tcp,
              'queries.udp': self._queries_udp,
              'queries.perzone' : self._queries_per_zone,
              'nds_queries.perzone' : {
                'test10.example': {
                    'queries.tcp': isc.cc.data.find(
                        self._nds_queries_per_zone,
                        'test10.example/queries.tcp')
                    }
                },
              'nds_queries.perzone/test10.example/queries.udp' :
                  isc.cc.data.find(self._nds_queries_per_zone,
                                   'test10.example/queries.udp')
              }

    def _init_statistics_data(self):
        # Inherited from real Stats class, just for deferring the
        # initialization until we are ready.
        pass

    def __group_sendmsg(self, command, destination, want_answer=False):
        """Faked ModuleCCSession.group_sendmsg for tests.

        Skipping actual network communication, and just returning an internally
        generated sequence number.

        """
        self._seq += 1
        return self._seq

    def __group_recvmsg(self, nonblocking = True, seq = None):
        """Faked ModuleCCSession.group_recvmsg for tests.

        Skipping actual network communication, and returning an internally
        prepared answer. sequence number.  If faked anser is given in
        _answers, use it; otherwise use the default.  we don't actually check
        the sequence.

        """
        if len(self._answers) == 0:
            return self.__default_answer, {'from': 'no-matter'}
        return self._answers.pop(0)

    def __rpc_call(self, command, group):
        """Faked ModuleCCSession.rpc_call for tests.

        At the moment we don't have to cover failure cases, so this is a
        simple wrapper for the faked group_recvmsg().

        """
        answer, _ = self.__group_recvmsg(None, None)
        return isc.config.ccsession.parse_answer(answer)[1]

class MyStatsHttpd(stats_httpd.StatsHttpd):
    """A faked StatsHttpd class for unit tests.

    This class inherits most of the real StatsHttpd class, but replaces the
    ModuleCCSession with a fake one so we can avoid network I/O in tests,
    and can also inspect or tweak messages via the session more easily.

    """

    ORIG_SPECFILE_LOCATION = stats_httpd.SPECFILE_LOCATION
    def __init__(self, *server_address):
        self._started = threading.Event()
        self.__dummy_sock = None # see below

        # Prepare commonly used statistics schema and data requested in
        # stats-httpd tests.  For the purpose of these tests, the content of
        # statistics data is not so important (they don't test whther the
        # counter values are correct, etc), so hardcoding the common case
        # should suffice.  Note also that some of the statistics values and
        # specs don't make sense in practice (see also comments on
        # AUTH_SPEC_STR).
        with open(stats.SPECFILE_LOCATION) as f:
            stat_spec_str = f.read()
        self.__default_spec_answer = {
            'Init': json.loads(INIT_SPEC_STR)['module_spec']['statistics'],
            'Auth': json.loads(AUTH_SPEC_STR)['module_spec']['statistics'],
            'Stats': json.loads(stat_spec_str)['module_spec']['statistics']
            }
        self.__default_data_answer = {
            'Init': {'boot_time':
                         time.strftime('%Y-%m-%dT%H:%M:%SZ', CONST_BASETIME)},
            'Stats': {'last_update_time':
                          time.strftime('%Y-%m-%dT%H:%M:%SZ', CONST_BASETIME),
                      'report_time':
                          time.strftime('%Y-%m-%dT%H:%M:%SZ', CONST_BASETIME),
                      'lname': 'test-lname',
                      'boot_time':
                          time.strftime('%Y-%m-%dT%H:%M:%SZ', CONST_BASETIME),
                      'timestamp': time.mktime(CONST_BASETIME)},
            'Auth': {'queries.udp': 4, 'queries.tcp': 6,
                     'queries.perzone': [
                    {'queries.udp': 8, 'queries.tcp': 10,
                     'zonename': 'test1.example'},
                    {'queries.udp': 6, 'queries.tcp': 8,
                     'zonename': 'test2.example'}],
                     'nds_queries.perzone': {
                    'test10.example': {'queries.udp': 8, 'queries.tcp': 10},
                    'test20.example': {'queries.udp': 6, 'queries.tcp': 8}}}}

        # if set, use them as faked response to rpc_call (see below).
        # it's a list of answer data of rpc_call.
        self._rpc_answers = []

        if server_address:
            stats_httpd.SPECFILE_LOCATION = \
                self.__create_specfile(*server_address)
            try:
                stats_httpd.StatsHttpd.__init__(self)
            finally:
                if hasattr(stats_httpd.SPECFILE_LOCATION, "close"):
                    stats_httpd.SPECFILE_LOCATION.close()
                stats_httpd.SPECFILE_LOCATION = self.ORIG_SPECFILE_LOCATION
        else:
            stats_httpd.StatsHttpd.__init__(self)

        # replace some (faked) ModuleCCSession methods so we can inspect/fake.
        # in order to satisfy select.select() we need some real socket.  We
        # use an unusable AF_UNIX socket; we won't actually use it for
        # communication.
        self.cc_session.rpc_call = self.__rpc_call
        self.__dummy_sock = socket.socket(socket.AF_UNIX, socket.SOCK_STREAM)
        self.mccs.get_socket = lambda: self.__dummy_sock

    def open_mccs(self):
        self.mccs = MyModuleCCSession(stats_httpd.SPECFILE_LOCATION,
                                      self.config_handler,
                                      self.command_handler)
        self.cc_session = self.mccs._session
        self.mccs.start = self.load_config # force reload

        # check_command could be called from the main select() loop due to
        # Linux's bug of spurious wakeup.  We don't need the actual behavior
        # of check_command in our tests, so we can basically replace it with a
        # no-op mock function.
        def mock_check_command(nonblock):
            pass
        self.mccs.check_command = mock_check_command

    def close_mccs(self):
        super().close_mccs()
        if self.__dummy_sock is not None:
            self.__dummy_sock.close()
            self.__dummy_sock = None

    def __rpc_call(self, command, group, params={}):
        """Faked ModuleCCSession.rpc_call for tests.

        The stats httpd module only issues two commands: 'showschema' and
        'show'.  In most cases we can simply use the prepared default
        answer.  If customization is needed, the test case can add a
        faked answer by appending it to _rpc_answers.  If the added object
        is of Exception type this method raises it instead of return it,
        emulating the situation where rpc_call() results in an exception.

        """
        if len(self._rpc_answers) == 0:
            if command == 'showschema':
                return self.__default_spec_answer
            elif command == 'show':
                return self.__default_data_answer
            assert False, "unexpected command for faked rpc_call: " + command

        answer = self._rpc_answers.pop(0)
        if issubclass(type(answer), Exception):
            raise answer
        return answer

    def __create_specfile(self, *server_address):
        spec_io = open(self.ORIG_SPECFILE_LOCATION)
        try:
            spec = json.load(spec_io)
            spec_io.close()
            config = spec['module_spec']['config_data']
            for i in range(len(config)):
                if config[i]['item_name'] == 'listen_on':
                    config[i]['item_default'] = \
                        [ dict(address=a[0], port=a[1])
                          for a in server_address ]
                    break
            return io.StringIO(json.dumps(spec))
        finally:
            spec_io.close()

    def run(self):
        self._started.set()
        self.start()

    def shutdown(self):
        self.command_handler('shutdown', None)
