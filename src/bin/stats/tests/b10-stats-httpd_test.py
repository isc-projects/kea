# Copyright (C) 2011  Internet Systems Consortium.
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

import unittest
import os
import http.server
import string
import select
import imp
import sys
import socket

import isc.cc

import stats_httpd

DUMMY_DATA = {
    "auth.queries.tcp": 10000,
    "auth.queries.udp": 12000,
    "bind10.boot_time": "2011-03-04T11:59:05Z",
    "report_time": "2011-03-04T11:59:19Z",
    "stats.boot_time": "2011-03-04T11:59:06Z",
    "stats.last_update_time": "2011-03-04T11:59:07Z",
    "stats.lname": "4d70d40a_c@host",
    "stats.start_time": "2011-03-04T11:59:06Z",
    "stats.timestamp": 1299239959.560846
    }

def push_answer(stats_httpd):
    stats_httpd.cc_session.group_sendmsg(
        { 'result': 
          [ 0, DUMMY_DATA ] }, "Stats")

def pull_query(stats_httpd):
    (msg, env) = stats_httpd.cc_session.group_recvmsg()
    if 'result' in msg:
        (ret, arg) = isc.config.ccsession.parse_answer(msg)
    else:
        (ret, arg) = isc.config.ccsession.parse_command(msg)
    return (ret, arg, env)

class TestHttpHandler(unittest.TestCase):
    """Tests for HttpHandler class"""

    def setUp(self):
        self.verbose = True
        self.stats_httpd = stats_httpd.StatsHttpd(self.verbose)
        self.assertTrue(type(self.stats_httpd.httpd) is list)
        self.httpd = self.stats_httpd.httpd
        for ht in self.httpd:
            self.assertTrue(ht.verbose)
        self.stats_httpd.cc_session.verbose = False

    def test_do_GET(self):
        for ht in self.httpd:
            self._test_do_GET(ht._handler)

    def _test_do_GET(self, handler):

        # URL is '/bind10/statistics/xml'
        handler.path = stats_httpd.XML_URL_PATH
        push_answer(self.stats_httpd)
        handler.do_GET()
        (ret, arg, env) = pull_query(self.stats_httpd)
        self.assertEqual(ret, "show")
        self.assertIsNone(arg)
        self.assertTrue('group' in env)
        self.assertEqual(env['group'], 'Stats')
        (ret, arg, env) = pull_query(self.stats_httpd)
        self.assertEqual(ret, 0)
        self.assertIsNone(arg)
        self.assertTrue('group' in env)
        self.assertEqual(env['group'], 'Stats')
        self.assertEqual(handler.response.code, 200)
        self.assertEqual(handler.response.headers["Content-type"], "text/xml")
        self.assertTrue(handler.response.headers["Content-Length"] > 0)
        self.assertTrue(handler.response.wrote_headers)
        self.assertRegexpMatches(handler.response.body, stats_httpd.XSD_NAMESPACE)
        self.assertRegexpMatches(handler.response.body, stats_httpd.XSD_URL_PATH)
        for (k, v) in DUMMY_DATA.items():
            self.assertRegexpMatches(handler.response.body, str(k))
            self.assertRegexpMatches(handler.response.body, str(v))

        # URL is '/bind10/statitics/xsd'
        handler.path = stats_httpd.XSD_URL_PATH
        handler.do_GET()
        self.assertEqual(handler.response.code, 200)
        self.assertEqual(handler.response.headers["Content-type"], "text/xml")
        self.assertTrue(handler.response.headers["Content-Length"] > 0)
        self.assertTrue(handler.response.wrote_headers)
        self.assertRegexpMatches(handler.response.body, stats_httpd.XSD_NAMESPACE)
        for (k, v) in DUMMY_DATA.items():
            self.assertRegexpMatches(handler.response.body, str(k))

        # URL is '/bind10/statitics/xsl'
        handler.path = stats_httpd.XSL_URL_PATH
        handler.do_GET()
        self.assertEqual(handler.response.code, 200)
        self.assertEqual(handler.response.headers["Content-type"], "text/xml")
        self.assertTrue(handler.response.headers["Content-Length"] > 0)
        self.assertTrue(handler.response.wrote_headers)
        self.assertRegexpMatches(handler.response.body, stats_httpd.XSD_NAMESPACE)
        for (k, v) in DUMMY_DATA.items():
            self.assertRegexpMatches(handler.response.body, str(k))

        # 302 redirect
        handler.path = '/'
        handler.headers = {'Host': 'my.host.domain'}
        handler.do_GET()
        self.assertEqual(handler.response.code, 302)
        self.assertEqual(handler.response.headers["Location"],
                         "http://my.host.domain%s" % stats_httpd.XML_URL_PATH)

        # 404 NotFound
        handler.path = '/path/to/foo/bar'
        handler.headers = {}
        handler.do_GET()
        self.assertEqual(handler.response.code, 404)

        # failure case(connection with Stats is down)
        handler.path = stats_httpd.XML_URL_PATH
        push_answer(self.stats_httpd)
        self.assertFalse(self.stats_httpd.cc_session._socket._closed)
        self.stats_httpd.cc_session._socket._closed = True
        handler.do_GET()
        self.stats_httpd.cc_session._socket._closed = False
        self.assertEqual(handler.response.code, 500)
        self.stats_httpd.cc_session._clear_ques()

        # failure case(Stats module returns err)
        handler.path = stats_httpd.XML_URL_PATH
        self.stats_httpd.cc_session.group_sendmsg(
            { 'result': [ 1, "I have an error." ] }, "Stats")
        self.assertFalse(self.stats_httpd.cc_session._socket._closed)
        self.stats_httpd.cc_session._socket._closed = False
        handler.do_GET()
        self.assertEqual(handler.response.code, 500)
        self.stats_httpd.cc_session._clear_ques()

    def test_do_HEAD(self):
        for ht in self.httpd:
            self._test_do_HEAD(ht._handler)

    def _test_do_HEAD(self, handler):
        handler.path = '/path/to/foo/bar'
        handler.do_HEAD()
        self.assertEqual(handler.response.code, 404)

    def test_log_message(self):
        for ht in self.httpd:
            self._test_log_message(ht._handler)

    def _test_log_message(self, handler):
        # switch write_log function
        handler.server.log_writer = handler.response._write_log
        log_message = 'ABCDEFG'
        handler.log_message("%s", log_message)
        self.assertEqual(handler.response.log, 
                         "[b10-stats-httpd] %s - - [%s] %s\n" %
                         (handler.address_string(),
                          handler.log_date_time_string(),
                          log_message))

class TestHttpServerError(unittest.TestCase):
    """Tests for HttpServerError exception"""

    def test_raises(self):
        try:
            raise stats_httpd.HttpServerError('Nothing')
        except stats_httpd.HttpServerError as err:
            self.assertEqual(str(err), 'Nothing')

class TestHttpServer(unittest.TestCase):
    """Tests for HttpServer class"""

    def setUp(self):
        self.verbose = True
        self.stats_httpd = stats_httpd.StatsHttpd(self.verbose)
        self.stats_httpd.cc_session.verbose = False
        for ht in self.stats_httpd.httpd:
            self.assertTrue(ht.server_address in self.stats_httpd.http_addrs)
            self.assertEqual(self.ht.verbose, self.verbose)
            self.assertEqual(self.ht.xml_handler, self.stats_httpd.xml_handler)
            self.assertEqual(self.ht.xsd_handler, self.stats_httpd.xsd_handler)
            self.assertEqual(self.ht.xsl_handler, self.stats_httpd.xsl_handler)
            self.assertEqual(self.ht.log_writer, self.stats_httpd.write_log)
            self.assertTrue(isinstance(self.ht._handler, stats_httpd.HttpHandler))
            self.assertTrue(isinstance(self.ht.socket, socket.socket))

class TestStatsHttpdError(unittest.TestCase):
    """Tests for StatsHttpdError exception"""

    def test_raises(self):
        try:
            raise stats_httpd.StatsHttpdError('Nothing')
        except stats_httpd.StatsHttpdError as err:
            self.assertEqual(str(err), 'Nothing')

class TestStatsHttpd(unittest.TestCase):
    """Tests for StatsHttpd class"""

    def setUp(self):
        self.verbose = True
        socket._CLOSED = False
        socket.has_ipv6 = True
        self.stats_httpd = stats_httpd.StatsHttpd(self.verbose)
        self.stats_httpd.cc_session.verbose = False

    def tearDown(self):
        self.stats_httpd.stop()

    def test_init(self):
        self.assertTrue(self.stats_httpd.verbose)
        self.assertFalse(self.stats_httpd.mccs.get_socket()._closed)
        self.assertEqual(self.stats_httpd.mccs.get_socket().fileno(),
                         id(self.stats_httpd.mccs.get_socket()))
        for ht in self.stats_httpd.httpd:
            self.assertFalse(ht.socket._closed)
            self.assertEqual(ht.socket.fileno(), id(ht.socket))
        socket._CLOSED = True
        self.assertRaises(isc.cc.session.SessionError,
                          stats_httpd.StatsHttpd)
        socket._CLOSED = False

    def test_mccs(self):
        self.stats_httpd.open_mccs()
        self.assertTrue(
            isinstance(self.stats_httpd.mccs.get_socket(), socket.socket))
        self.assertTrue(
            isinstance(self.stats_httpd.cc_session, isc.cc.session.Session))
        self.assertTrue(
            isinstance(self.stats_httpd.stats_module_spec, isc.config.ModuleSpec))
        for cfg in self.stats_httpd.stats_config_spec:
            self.assertTrue('item_name' in cfg)
            self.assertTrue(cfg['item_name'] in DUMMY_DATA)
        self.assertTrue(len(self.stats_httpd.stats_config_spec), len(DUMMY_DATA))

    def test_load_config(self):
        self.stats_httpd.load_config()
        self.assertTrue(('127.0.0.1', 8000) in set(self.stats_httpd.http_addrs))

    def test_httpd(self):
        # dual stack (addresses is ipv4 and ipv6)
        socket.has_ipv6 = True
        self.assertTrue(('127.0.0.1', 8000) in set(self.stats_httpd.http_addrs))
        self.stats_httpd.http_addrs = [ ('::1', 8000), ('127.0.0.1', 8000) ]
        self.assertTrue(
            stats_httpd.HttpServer.address_family in set([socket.AF_INET, socket.AF_INET6]))
        self.stats_httpd.open_httpd()
        for ht in self.stats_httpd.httpd:
            self.assertTrue(isinstance(ht.socket, socket.socket))
        self.stats_httpd.close_httpd()

        # dual stack (address is ipv6)
        socket.has_ipv6 = True
        self.stats_httpd.http_addrs = [ ('::1', 8000) ]
        self.stats_httpd.open_httpd()
        for ht in self.stats_httpd.httpd:
            self.assertTrue(isinstance(ht.socket, socket.socket))
        self.stats_httpd.close_httpd()

        # dual stack (address is ipv4)
        socket.has_ipv6 = True
        self.stats_httpd.http_addrs = [ ('127.0.0.1', 8000) ]
        self.stats_httpd.open_httpd()
        for ht in self.stats_httpd.httpd:
            self.assertTrue(isinstance(ht.socket, socket.socket))
        self.stats_httpd.close_httpd()

        # only-ipv4 single stack
        socket.has_ipv6 = False
        self.stats_httpd.http_addrs = [ ('127.0.0.1', 8000) ]
        self.stats_httpd.open_httpd()
        for ht in self.stats_httpd.httpd:
            self.assertTrue(isinstance(ht.socket, socket.socket))
        self.stats_httpd.close_httpd()

        # only-ipv4 single stack (force set ipv6 )
        socket.has_ipv6 = False
        self.stats_httpd.http_addrs = [ ('::1', 8000) ]
        self.assertRaises(stats_httpd.HttpServerError,
            self.stats_httpd.open_httpd)

        # hostname
        self.stats_httpd.http_addrs = [ ('localhost', 8000) ]
        self.stats_httpd.open_httpd()
        for ht in self.stats_httpd.httpd:
            self.assertTrue(isinstance(ht.socket, socket.socket))
        self.stats_httpd.close_httpd()

        self.stats_httpd.http_addrs = [ ('my.host.domain', 8000) ]
        self.stats_httpd.open_httpd()
        for ht in self.stats_httpd.httpd:
            self.assertTrue(isinstance(ht.socket, socket.socket))
        self.stats_httpd.close_httpd()

        # over flow of port number
        self.stats_httpd.http_addrs = [ ('', 80000) ]
        self.assertRaises(stats_httpd.HttpServerError, self.stats_httpd.open_httpd)
        # negative
        self.stats_httpd.http_addrs = [ ('', -8000) ]
        self.assertRaises(stats_httpd.HttpServerError, self.stats_httpd.open_httpd)
        # alphabet
        self.stats_httpd.http_addrs = [ ('', 'ABCDE') ]
        self.assertRaises(stats_httpd.HttpServerError, self.stats_httpd.open_httpd)

    def test_start(self):
        self.stats_httpd.cc_session.group_sendmsg(
            { 'command': [ "shutdown" ] }, "StatsHttpd")
        self.stats_httpd.start()
        self.stats_httpd = stats_httpd.StatsHttpd(self.verbose)
        self.stats_httpd.cc_session.verbose = False
        self.assertRaises(
            select.error, self.stats_httpd.start)

    def test_stop(self):
        # success case
        socket._CLOSED = False
        self.stats_httpd.stop()
        self.assertFalse(self.stats_httpd.running)
        self.assertIsNone(self.stats_httpd.mccs)
        for ht in self.stats_httpd.httpd:
            self.assertTrue(ht.socket._closed)
        self.assertTrue(self.stats_httpd.cc_session._socket._closed)
        # failure case
        self.stats_httpd.cc_session._socket._closed = False
        self.stats_httpd.open_mccs()
        self.stats_httpd.cc_session._socket._closed = True
        self.stats_httpd.stop() # No excetion raises
        self.stats_httpd.cc_session._socket._closed = False

    def test_open_template(self):
        self.assertRaises(
            IOError,
            self.stats_httpd.open_template, '/path/to/foo/bar')

    def test_commands(self):
        self.assertEqual(self.stats_httpd.command_handler("status", None),
                         isc.config.ccsession.create_answer(
                0, "Stats Httpd is up. (PID " + str(os.getpid()) + ")"))
        self.stats_httpd.running = True
        self.assertEqual(self.stats_httpd.command_handler("shutdown", None),
                         isc.config.ccsession.create_answer(
                0, "Stats Httpd is shutting down."))
        self.assertFalse(self.stats_httpd.running)
        self.assertEqual(
            self.stats_httpd.command_handler("__UNKNOWN_COMMAND__", None),
            isc.config.ccsession.create_answer(
                1, "Unknown command: __UNKNOWN_COMMAND__"))

    def test_config(self):
        d = dict(_UNKNOWN_KEY_=None)
        self.assertEqual(
            self.stats_httpd.config_handler(d),
            isc.config.ccsession.create_answer(
                    1, "Unknown known config: _UNKNOWN_KEY_"))
        self.assertEqual(
            self.stats_httpd.config_handler(
                        dict(listen_on=[dict(address="::2",port=8000)])),
            isc.config.ccsession.create_answer(0))
        self.assertEqual(
            self.stats_httpd.config_handler(
                        dict(listen_on=[dict(address="::1",port=80)])),
            isc.config.ccsession.create_answer(0))
        self.assertEqual(
            self.stats_httpd.config_handler(
                        dict(listen_on=[dict(address="1.2.3.4",port=54321)])),
            isc.config.ccsession.create_answer(0))
        (ret, arg) = isc.config.ccsession.parse_answer(
            self.stats_httpd.config_handler(
                dict(listen_on=[dict(address="1.2.3.4",port=543210)]))
            )
        self.assertEqual(ret, 1)

    def test_no_buildpath(self):
        """
        test for no "B10_FROM_SOURCE"
        """
        if "B10_FROM_SOURCE" in os.environ:
            tmppath = os.environ["B10_FROM_SOURCE"]
            os.environ.pop("B10_FROM_SOURCE")
            imp.reload(stats_httpd)
            os.environ["B10_FROM_SOURCE"] = tmppath
            imp.reload(stats_httpd)

if __name__ == "__main__":
    unittest.main()
