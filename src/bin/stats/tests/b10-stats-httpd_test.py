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
import fake_select
import imp
import sys
import fake_socket

import isc.cc

import stats_httpd
stats_httpd.socket = fake_socket
stats_httpd.select = fake_select

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
        self.stats_httpd = stats_httpd.StatsHttpd()
        self.assertTrue(type(self.stats_httpd.httpd) is list)
        self.httpd = self.stats_httpd.httpd

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
        self.assertEqual(handler.response.code, 200)
        self.assertEqual(handler.response.headers["Content-type"], "text/xml")
        self.assertTrue(handler.response.headers["Content-Length"] > 0)
        self.assertTrue(handler.response.wrote_headers)
        self.assertTrue(handler.response.body.find(stats_httpd.XSD_NAMESPACE)>0)
        self.assertTrue(handler.response.body.find(stats_httpd.XSD_URL_PATH)>0)
        for (k, v) in DUMMY_DATA.items():
            self.assertTrue(handler.response.body.find(str(k))>0)
            self.assertTrue(handler.response.body.find(str(v))>0)

        # URL is '/bind10/statitics/xsd'
        handler.path = stats_httpd.XSD_URL_PATH
        handler.do_GET()
        self.assertEqual(handler.response.code, 200)
        self.assertEqual(handler.response.headers["Content-type"], "text/xml")
        self.assertTrue(handler.response.headers["Content-Length"] > 0)
        self.assertTrue(handler.response.wrote_headers)
        self.assertTrue(handler.response.body.find(stats_httpd.XSD_NAMESPACE)>0)
        for (k, v) in DUMMY_DATA.items():
            self.assertTrue(handler.response.body.find(str(k))>0)

        # URL is '/bind10/statitics/xsl'
        handler.path = stats_httpd.XSL_URL_PATH
        handler.do_GET()
        self.assertEqual(handler.response.code, 200)
        self.assertEqual(handler.response.headers["Content-type"], "text/xml")
        self.assertTrue(handler.response.headers["Content-Length"] > 0)
        self.assertTrue(handler.response.wrote_headers)
        self.assertTrue(handler.response.body.find(stats_httpd.XSD_NAMESPACE)>0)
        for (k, v) in DUMMY_DATA.items():
            self.assertTrue(handler.response.body.find(str(k))>0)

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
        self.stats_httpd.cc_session._clear_queues()

        # failure case(Stats module returns err)
        handler.path = stats_httpd.XML_URL_PATH
        self.stats_httpd.cc_session.group_sendmsg(
            { 'result': [ 1, "I have an error." ] }, "Stats")
        self.assertFalse(self.stats_httpd.cc_session._socket._closed)
        self.stats_httpd.cc_session._socket._closed = False
        handler.do_GET()
        self.assertEqual(handler.response.code, 500)
        self.stats_httpd.cc_session._clear_queues()

    def test_do_HEAD(self):
        for ht in self.httpd:
            self._test_do_HEAD(ht._handler)

    def _test_do_HEAD(self, handler):
        handler.path = '/path/to/foo/bar'
        handler.do_HEAD()
        self.assertEqual(handler.response.code, 404)

class TestHttpServerError(unittest.TestCase):
    """Tests for HttpServerError exception"""

    def test_raises(self):
        try:
            raise stats_httpd.HttpServerError('Nothing')
        except stats_httpd.HttpServerError as err:
            self.assertEqual(str(err), 'Nothing')

class TestHttpServer(unittest.TestCase):
    """Tests for HttpServer class"""

    def test_httpserver(self):
        self.stats_httpd = stats_httpd.StatsHttpd()
        for ht in self.stats_httpd.httpd:
            self.assertTrue(ht.server_address in self.stats_httpd.http_addrs)
            self.assertEqual(ht.xml_handler, self.stats_httpd.xml_handler)
            self.assertEqual(ht.xsd_handler, self.stats_httpd.xsd_handler)
            self.assertEqual(ht.xsl_handler, self.stats_httpd.xsl_handler)
            self.assertEqual(ht.log_writer, self.stats_httpd.write_log)
            self.assertTrue(isinstance(ht._handler, stats_httpd.HttpHandler))
            self.assertTrue(isinstance(ht.socket, fake_socket.socket))

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
        fake_socket._CLOSED = False
        fake_socket.has_ipv6 = True
        self.stats_httpd = stats_httpd.StatsHttpd()

    def tearDown(self):
        self.stats_httpd.stop()

    def test_init(self):
        self.assertFalse(self.stats_httpd.mccs.get_socket()._closed)
        self.assertEqual(self.stats_httpd.mccs.get_socket().fileno(),
                         id(self.stats_httpd.mccs.get_socket()))
        for ht in self.stats_httpd.httpd:
            self.assertFalse(ht.socket._closed)
            self.assertEqual(ht.socket.fileno(), id(ht.socket))
        fake_socket._CLOSED = True
        self.assertRaises(isc.cc.session.SessionError,
                          stats_httpd.StatsHttpd)
        fake_socket._CLOSED = False

    def test_mccs(self):
        self.stats_httpd.open_mccs()
        self.assertTrue(
            isinstance(self.stats_httpd.mccs.get_socket(), fake_socket.socket))
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
        fake_socket.has_ipv6 = True
        self.assertTrue(('127.0.0.1', 8000) in set(self.stats_httpd.http_addrs))
        self.stats_httpd.http_addrs = [ ('::1', 8000), ('127.0.0.1', 8000) ]
        self.assertTrue(
            stats_httpd.HttpServer.address_family in set([fake_socket.AF_INET, fake_socket.AF_INET6]))
        self.stats_httpd.open_httpd()
        for ht in self.stats_httpd.httpd:
            self.assertTrue(isinstance(ht.socket, fake_socket.socket))
        self.stats_httpd.close_httpd()

        # dual stack (address is ipv6)
        fake_socket.has_ipv6 = True
        self.stats_httpd.http_addrs = [ ('::1', 8000) ]
        self.stats_httpd.open_httpd()
        for ht in self.stats_httpd.httpd:
            self.assertTrue(isinstance(ht.socket, fake_socket.socket))
        self.stats_httpd.close_httpd()

        # dual stack (address is ipv4)
        fake_socket.has_ipv6 = True
        self.stats_httpd.http_addrs = [ ('127.0.0.1', 8000) ]
        self.stats_httpd.open_httpd()
        for ht in self.stats_httpd.httpd:
            self.assertTrue(isinstance(ht.socket, fake_socket.socket))
        self.stats_httpd.close_httpd()

        # only-ipv4 single stack
        fake_socket.has_ipv6 = False
        self.stats_httpd.http_addrs = [ ('127.0.0.1', 8000) ]
        self.stats_httpd.open_httpd()
        for ht in self.stats_httpd.httpd:
            self.assertTrue(isinstance(ht.socket, fake_socket.socket))
        self.stats_httpd.close_httpd()

        # only-ipv4 single stack (force set ipv6 )
        fake_socket.has_ipv6 = False
        self.stats_httpd.http_addrs = [ ('::1', 8000) ]
        self.assertRaises(stats_httpd.HttpServerError,
            self.stats_httpd.open_httpd)

        # hostname
        self.stats_httpd.http_addrs = [ ('localhost', 8000) ]
        self.stats_httpd.open_httpd()
        for ht in self.stats_httpd.httpd:
            self.assertTrue(isinstance(ht.socket, fake_socket.socket))
        self.stats_httpd.close_httpd()

        self.stats_httpd.http_addrs = [ ('my.host.domain', 8000) ]
        self.stats_httpd.open_httpd()
        for ht in self.stats_httpd.httpd:
            self.assertTrue(isinstance(ht.socket, fake_socket.socket))
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
        self.stats_httpd = stats_httpd.StatsHttpd()
        self.assertRaises(
            fake_select.error, self.stats_httpd.start)

    def test_stop(self):
        # success case
        fake_socket._CLOSED = False
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
        # successful conditions
        tmpl = self.stats_httpd.open_template(stats_httpd.XML_TEMPLATE_LOCATION)
        self.assertTrue(isinstance(tmpl, string.Template))
        opts = dict(
            xml_string="<dummy></dummy>",
            xsd_namespace="http://host/path/to/",
            xsd_url_path="/path/to/",
            xsl_url_path="/path/to/")
        lines = tmpl.substitute(opts)
        for n in opts:
            self.assertTrue(lines.find(opts[n])>0)
        tmpl = self.stats_httpd.open_template(stats_httpd.XSD_TEMPLATE_LOCATION)
        self.assertTrue(isinstance(tmpl, string.Template))
        opts = dict(
            xsd_string="<dummy></dummy>",
            xsd_namespace="http://host/path/to/")
        lines = tmpl.substitute(opts)
        for n in opts:
            self.assertTrue(lines.find(opts[n])>0)
        tmpl = self.stats_httpd.open_template(stats_httpd.XSL_TEMPLATE_LOCATION)
        self.assertTrue(isinstance(tmpl, string.Template))
        opts = dict(
            xsl_string="<dummy></dummy>",
            xsd_namespace="http://host/path/to/")
        lines = tmpl.substitute(opts)
        for n in opts:
            self.assertTrue(lines.find(opts[n])>0)
        # unsuccessful condition
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
        self.assertEqual(
            self.stats_httpd.config_handler(dict(_UNKNOWN_KEY_=None)),
            isc.config.ccsession.create_answer(
                    1, "Unknown known config: _UNKNOWN_KEY_"))
        self.assertEqual(
            self.stats_httpd.config_handler(
                        dict(listen_on=[dict(address="::2",port=8000)])),
            isc.config.ccsession.create_answer(0))
        self.assertTrue("listen_on" in self.stats_httpd.config)
        for addr in self.stats_httpd.config["listen_on"]:
            self.assertTrue("address" in addr)
            self.assertTrue("port" in addr)
            self.assertTrue(addr["address"] == "::2")
            self.assertTrue(addr["port"] == 8000)

        self.assertEqual(
            self.stats_httpd.config_handler(
                        dict(listen_on=[dict(address="::1",port=80)])),
            isc.config.ccsession.create_answer(0))
        self.assertTrue("listen_on" in self.stats_httpd.config)
        for addr in self.stats_httpd.config["listen_on"]:
            self.assertTrue("address" in addr)
            self.assertTrue("port" in addr)
            self.assertTrue(addr["address"] == "::1")
            self.assertTrue(addr["port"] == 80)

        self.assertEqual(
            self.stats_httpd.config_handler(
                        dict(listen_on=[dict(address="1.2.3.4",port=54321)])),
            isc.config.ccsession.create_answer(0))
        self.assertTrue("listen_on" in self.stats_httpd.config)
        for addr in self.stats_httpd.config["listen_on"]:
            self.assertTrue("address" in addr)
            self.assertTrue("port" in addr)
            self.assertTrue(addr["address"] == "1.2.3.4")
            self.assertTrue(addr["port"] == 54321)
        (ret, arg) = isc.config.ccsession.parse_answer(
            self.stats_httpd.config_handler(
                dict(listen_on=[dict(address="1.2.3.4",port=543210)]))
            )
        self.assertEqual(ret, 1)

    def test_xml_handler(self):
        orig_get_stats_data = stats_httpd.StatsHttpd.get_stats_data
        stats_httpd.StatsHttpd.get_stats_data = lambda x: {'foo':'bar'}
        xml_body1 = stats_httpd.StatsHttpd().open_template(
            stats_httpd.XML_TEMPLATE_LOCATION).substitute(
            xml_string='<foo>bar</foo>',
            xsd_namespace=stats_httpd.XSD_NAMESPACE,
            xsd_url_path=stats_httpd.XSD_URL_PATH,
            xsl_url_path=stats_httpd.XSL_URL_PATH)
        xml_body2 = stats_httpd.StatsHttpd().xml_handler()
        self.assertEqual(type(xml_body1), str)
        self.assertEqual(type(xml_body2), str)
        self.assertEqual(xml_body1, xml_body2)
        stats_httpd.StatsHttpd.get_stats_data = lambda x: {'bar':'foo'}
        xml_body2 = stats_httpd.StatsHttpd().xml_handler()
        self.assertNotEqual(xml_body1, xml_body2)
        stats_httpd.StatsHttpd.get_stats_data = orig_get_stats_data

    def test_xsd_handler(self):
        orig_get_stats_spec = stats_httpd.StatsHttpd.get_stats_spec
        stats_httpd.StatsHttpd.get_stats_spec = lambda x: \
            [{
                "item_name": "foo",
                "item_type": "string",
                "item_optional": False,
                "item_default": "bar",
                "item_description": "foo is bar",
                "item_title": "Foo"
               }]
        xsd_body1 = stats_httpd.StatsHttpd().open_template(
            stats_httpd.XSD_TEMPLATE_LOCATION).substitute(
            xsd_string='<all>' \
                + '<element maxOccurs="1" minOccurs="1" name="foo" type="string">' \
                + '<annotation><appinfo>Foo</appinfo>' \
                + '<documentation>foo is bar</documentation>' \
                + '</annotation></element></all>',
            xsd_namespace=stats_httpd.XSD_NAMESPACE)
        xsd_body2 = stats_httpd.StatsHttpd().xsd_handler()
        self.assertEqual(type(xsd_body1), str)
        self.assertEqual(type(xsd_body2), str)
        self.assertEqual(xsd_body1, xsd_body2)
        stats_httpd.StatsHttpd.get_stats_spec = lambda x: \
            [{
                "item_name": "bar",
                "item_type": "string",
                "item_optional": False,
                "item_default": "foo",
                "item_description": "bar is foo",
                "item_title": "bar"
               }]
        xsd_body2 = stats_httpd.StatsHttpd().xsd_handler()
        self.assertNotEqual(xsd_body1, xsd_body2)
        stats_httpd.StatsHttpd.get_stats_spec = orig_get_stats_spec

    def test_xsl_handler(self):
        orig_get_stats_spec = stats_httpd.StatsHttpd.get_stats_spec
        stats_httpd.StatsHttpd.get_stats_spec = lambda x: \
            [{
                "item_name": "foo",
                "item_type": "string",
                "item_optional": False,
                "item_default": "bar",
                "item_description": "foo is bar",
                "item_title": "Foo"
               }]
        xsl_body1 = stats_httpd.StatsHttpd().open_template(
            stats_httpd.XSL_TEMPLATE_LOCATION).substitute(
            xsl_string='<xsl:template match="*"><tr>' \
                + '<td class="title" title="foo is bar">Foo</td>' \
                + '<td><xsl:value-of select="foo" /></td>' \
                + '</tr></xsl:template>',
            xsd_namespace=stats_httpd.XSD_NAMESPACE)
        xsl_body2 = stats_httpd.StatsHttpd().xsl_handler()
        self.assertEqual(type(xsl_body1), str)
        self.assertEqual(type(xsl_body2), str)
        self.assertEqual(xsl_body1, xsl_body2)
        stats_httpd.StatsHttpd.get_stats_spec = lambda x: \
            [{
                "item_name": "bar",
                "item_type": "string",
                "item_optional": False,
                "item_default": "foo",
                "item_description": "bar is foo",
                "item_title": "bar"
               }]
        xsl_body2 = stats_httpd.StatsHttpd().xsl_handler()
        self.assertNotEqual(xsl_body1, xsl_body2)
        stats_httpd.StatsHttpd.get_stats_spec = orig_get_stats_spec

    def test_for_without_B10_FROM_SOURCE(self):
        # just lets it go through the code without B10_FROM_SOURCE env
        # variable
        if "B10_FROM_SOURCE" in os.environ:
            tmppath = os.environ["B10_FROM_SOURCE"]
            os.environ.pop("B10_FROM_SOURCE")
            imp.reload(stats_httpd)
            os.environ["B10_FROM_SOURCE"] = tmppath
            imp.reload(stats_httpd)
            stats_httpd.socket = fake_socket
            stats_httpd.select = fake_select

if __name__ == "__main__":
    unittest.main()
