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
import imp
import socket
import errno
import select
import string
import time
import threading
import http.client
import xml.etree.ElementTree

import isc
import stats_httpd
import stats
from test_utils import BaseModules, ThreadingServerManager, MyStats, MyStatsHttpd, TIMEOUT_SEC

# set test name for logger
isc.log.init("b10-stats-httpd_test")

DUMMY_DATA = {
    'Boss' : {
        "boot_time": "2011-03-04T11:59:06Z"
        },
    'Auth' : {
        "queries.tcp": 2,
        "queries.udp": 3
        },
    'Stats' : {
        "report_time": "2011-03-04T11:59:19Z",
        "boot_time": "2011-03-04T11:59:06Z",
        "last_update_time": "2011-03-04T11:59:07Z",
        "lname": "4d70d40a_c@host",
        "timestamp": 1299239959.560846
        }
    }

class TestHttpHandler(unittest.TestCase):
    """Tests for HttpHandler class"""

    def setUp(self):
        self.base = BaseModules()
        self.stats_server = ThreadingServerManager(MyStats)
        self.stats = self.stats_server.server
        self.stats_server.run()

    def tearDown(self):
        self.stats_server.shutdown()
        self.base.shutdown()

    def test_do_GET(self):
        (address, port) = ('127.0.0.1', 65450)
        statshttpd_server = ThreadingServerManager(MyStatsHttpd)
        self.stats_httpd = statshttpd_server.server
        self.stats_httpd.load_config({'listen_on' : [{ 'address': address, 'port' : port }]})
        self.assertTrue(type(self.stats_httpd.httpd) is list)
        self.assertEqual(len(self.stats_httpd.httpd), 0)
        statshttpd_server.run()
        time.sleep(TIMEOUT_SEC*8)
        client = http.client.HTTPConnection(address, port)
        client._http_vsn_str = 'HTTP/1.0\n'
        client.connect()

        # URL is '/bind10/statistics/xml'
        client.putrequest('GET', stats_httpd.XML_URL_PATH)
        client.endheaders()
        response = client.getresponse()
        self.assertEqual(response.getheader("Content-type"), "text/xml")
        self.assertTrue(int(response.getheader("Content-Length")) > 0)
        self.assertEqual(response.status, 200)
        root = xml.etree.ElementTree.parse(response).getroot()
        self.assertTrue(root.tag.find('stats_data') > 0)
        for (k,v) in root.attrib.items():
            if k.find('schemaLocation') > 0:
                self.assertEqual(v, stats_httpd.XSD_NAMESPACE + ' ' + stats_httpd.XSD_URL_PATH)
        for mod in DUMMY_DATA:
            for (item, value) in DUMMY_DATA[mod].items():
                self.assertIsNotNone(root.find(mod + '/' + item))

        # URL is '/bind10/statitics/xsd'
        client.putrequest('GET', stats_httpd.XSD_URL_PATH)
        client.endheaders()
        response = client.getresponse()
        self.assertEqual(response.getheader("Content-type"), "text/xml")
        self.assertTrue(int(response.getheader("Content-Length")) > 0)
        self.assertEqual(response.status, 200)
        root = xml.etree.ElementTree.parse(response).getroot()
        url_xmlschema = '{http://www.w3.org/2001/XMLSchema}'
        tags = [ url_xmlschema + t for t in [ 'element', 'complexType', 'all', 'element' ] ]
        xsdpath = '/'.join(tags)
        self.assertTrue(root.tag.find('schema') > 0)
        self.assertTrue(hasattr(root, 'attrib'))
        self.assertTrue('targetNamespace' in root.attrib)
        self.assertEqual(root.attrib['targetNamespace'],
                         stats_httpd.XSD_NAMESPACE)
        for elm in root.findall(xsdpath):
            self.assertIsNotNone(elm.attrib['name'])
            self.assertTrue(elm.attrib['name'] in DUMMY_DATA)

        # URL is '/bind10/statitics/xsl'
        client.putrequest('GET', stats_httpd.XSL_URL_PATH)
        client.endheaders()
        response = client.getresponse()
        self.assertEqual(response.getheader("Content-type"), "text/xml")
        self.assertTrue(int(response.getheader("Content-Length")) > 0)
        self.assertEqual(response.status, 200)
        root = xml.etree.ElementTree.parse(response).getroot()
        url_trans = '{http://www.w3.org/1999/XSL/Transform}'
        url_xhtml = '{http://www.w3.org/1999/xhtml}'
        xslpath = url_trans + 'template/' + url_xhtml + 'tr'
        self.assertEqual(root.tag, url_trans + 'stylesheet')
        for tr in root.findall(xslpath):
            tds = tr.findall(url_xhtml + 'td')
            self.assertIsNotNone(tds)
            self.assertEqual(type(tds), list)
            self.assertTrue(len(tds) > 2)
            self.assertTrue(hasattr(tds[0], 'text'))
            self.assertTrue(tds[0].text in DUMMY_DATA)
            valueof = tds[2].find(url_trans + 'value-of')
            self.assertIsNotNone(valueof)
            self.assertTrue(hasattr(valueof, 'attrib'))
            self.assertIsNotNone(valueof.attrib)
            self.assertTrue('select' in valueof.attrib)
            self.assertTrue(valueof.attrib['select'] in \
                                [ tds[0].text+'/'+item for item in DUMMY_DATA[tds[0].text].keys() ])

        # 302 redirect
        client._http_vsn_str = 'HTTP/1.1'
        client.putrequest('GET', '/')
        client.putheader('Host', address)
        client.endheaders()
        response = client.getresponse()
        self.assertEqual(response.status, 302)
        self.assertEqual(response.getheader('Location'),
                         "http://%s:%d%s" % (address, port, stats_httpd.XML_URL_PATH))

        # # 404 NotFound
        client._http_vsn_str = 'HTTP/1.0'
        client.putrequest('GET', '/path/to/foo/bar')
        client.endheaders()
        response = client.getresponse()
        self.assertEqual(response.status, 404)

        client.close()
        statshttpd_server.shutdown()

    def test_do_GET_failed1(self):
        # failure case(connection with Stats is down)
        (address, port) = ('127.0.0.1', 65451)
        statshttpd_server = ThreadingServerManager(MyStatsHttpd)
        statshttpd = statshttpd_server.server
        statshttpd.load_config({'listen_on' : [{ 'address': address, 'port' : port }]})
        statshttpd_server.run()
        self.assertTrue(self.stats_server.server.running)
        self.stats_server.shutdown()
        time.sleep(TIMEOUT_SEC*2)
        self.assertFalse(self.stats_server.server.running)
        statshttpd.cc_session.set_timeout(milliseconds=TIMEOUT_SEC/1000)
        client = http.client.HTTPConnection(address, port)
        client.connect()

        # request XML
        client.putrequest('GET', stats_httpd.XML_URL_PATH)
        client.endheaders()
        response = client.getresponse()
        self.assertEqual(response.status, 500)

        # request XSD
        client.putrequest('GET', stats_httpd.XSD_URL_PATH)
        client.endheaders()
        response = client.getresponse()
        self.assertEqual(response.status, 500)

        # request XSL
        client.putrequest('GET', stats_httpd.XSL_URL_PATH)
        client.endheaders()
        response = client.getresponse()
        self.assertEqual(response.status, 500)

        client.close()
        statshttpd_server.shutdown()

    def test_do_GET_failed2(self):
        # failure case(connection with Stats is down)
        (address, port) = ('127.0.0.1', 65452)
        statshttpd_server = ThreadingServerManager(MyStatsHttpd)
        self.stats_httpd = statshttpd_server.server
        self.stats_httpd.load_config({'listen_on' : [{ 'address': address, 'port' : port }]})
        statshttpd_server.run()
        self.stats.mccs.set_command_handler(
            lambda cmd, args: \
                isc.config.ccsession.create_answer(1, "I have an error.")
            )
        time.sleep(TIMEOUT_SEC*5)
        client = http.client.HTTPConnection(address, port)
        client.connect()

        # request XML
        client.putrequest('GET', stats_httpd.XML_URL_PATH)
        client.endheaders()
        response = client.getresponse()
        self.assertEqual(response.status, 500)

        # request XSD
        client.putrequest('GET', stats_httpd.XSD_URL_PATH)
        client.endheaders()
        response = client.getresponse()
        self.assertEqual(response.status, 500)

        # request XSL
        client.putrequest('GET', stats_httpd.XSL_URL_PATH)
        client.endheaders()
        response = client.getresponse()
        self.assertEqual(response.status, 500)

        client.close()
        statshttpd_server.shutdown()

    def test_do_HEAD(self):
        (address, port) = ('127.0.0.1', 65453)
        statshttpd_server = ThreadingServerManager(MyStatsHttpd)
        self.stats_httpd = statshttpd_server.server
        self.stats_httpd.load_config({'listen_on' : [{ 'address': address, 'port' : port }]})
        statshttpd_server.run()
        time.sleep(TIMEOUT_SEC*5)
        client = http.client.HTTPConnection(address, port)
        client.connect()
        client.putrequest('HEAD', stats_httpd.XML_URL_PATH)
        client.endheaders()
        response = client.getresponse()
        self.assertEqual(response.status, 200)

        client.putrequest('HEAD', '/path/to/foo/bar')
        client.endheaders()
        response = client.getresponse()
        self.assertEqual(response.status, 404)
        client.close()
        statshttpd_server.shutdown()

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
        self.base = BaseModules()

    def tearDown(self):
        self.base.shutdown()

    def test_httpserver(self):
        statshttpd = stats_httpd.StatsHttpd()
        self.assertEqual(type(statshttpd.httpd), list)
        self.assertEqual(len(statshttpd.httpd), 0)

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
        self.base = BaseModules()
        self.stats_server = ThreadingServerManager(MyStats)
        self.stats = self.stats_server.server
        self.stats_server.run()
        self.stats_httpd = stats_httpd.StatsHttpd()

        # checking IPv6 enabled on this platform
        self.ipv6_enabled = True
        try:
            sock = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
            sock.bind(("::1",8000))
            sock.close()
        except socket.error:
            self.ipv6_enabled = False

    def tearDown(self):
        self.stats_httpd.stop()
        self.stats_server.shutdown()
        self.base.shutdown()

    def test_init(self):
        self.assertEqual(self.stats_httpd.running, False)
        self.assertEqual(self.stats_httpd.poll_intval, 0.5)
        self.assertEqual(self.stats_httpd.httpd, [])
        self.assertEqual(type(self.stats_httpd.mccs), isc.config.ModuleCCSession)
        self.assertEqual(type(self.stats_httpd.cc_session), isc.cc.Session)
        self.assertEqual(len(self.stats_httpd.config), 2)
        self.assertTrue('listen_on' in self.stats_httpd.config)
        self.assertEqual(len(self.stats_httpd.config['listen_on']), 1)
        self.assertTrue('address' in self.stats_httpd.config['listen_on'][0])
        self.assertTrue('port' in self.stats_httpd.config['listen_on'][0])
        self.assertTrue(('127.0.0.1', 8000) in set(self.stats_httpd.http_addrs))

    def test_openclose_mccs(self):
        statshttpd = stats_httpd.StatsHttpd()
        statshttpd.close_mccs()
        self.assertEqual(statshttpd.mccs, None)
        statshttpd.open_mccs()
        self.assertIsNotNone(statshttpd.mccs)
        statshttpd.mccs = None
        self.assertEqual(statshttpd.mccs, None)
        self.assertEqual(statshttpd.close_mccs(), None)

    def test_mccs(self):
        self.assertIsNotNone(self.stats_httpd.mccs.get_socket())
        self.assertTrue(
            isinstance(self.stats_httpd.mccs.get_socket(), socket.socket))
        self.assertTrue(
            isinstance(self.stats_httpd.cc_session, isc.cc.session.Session))
        self.statistics_spec = self.stats_httpd.get_stats_spec()
        for mod in DUMMY_DATA:
            self.assertTrue(mod in self.statistics_spec)
            for cfg in self.statistics_spec[mod]:
                self.assertTrue('item_name' in cfg)
                self.assertTrue(cfg['item_name'] in DUMMY_DATA[mod])
            self.assertTrue(len(self.statistics_spec[mod]), len(DUMMY_DATA[mod]))
        self.stats_httpd.close_mccs()
        self.assertIsNone(self.stats_httpd.mccs)

    def test_httpd(self):
        # dual stack (addresses is ipv4 and ipv6)
        if self.ipv6_enabled:
            self.assertTrue(('127.0.0.1', 8000) in set(self.stats_httpd.http_addrs))
            self.stats_httpd.http_addrs = [ ('::1', 8000), ('127.0.0.1', 8000) ]
            self.assertTrue(
                stats_httpd.HttpServer.address_family in set([socket.AF_INET, socket.AF_INET6]))
            self.stats_httpd.open_httpd()
            for ht in self.stats_httpd.httpd:
                self.assertTrue(isinstance(ht.socket, socket.socket))
            self.stats_httpd.close_httpd()

        # dual stack (address is ipv6)
        if self.ipv6_enabled:
            self.stats_httpd.http_addrs = [ ('::1', 8000) ]
            self.stats_httpd.open_httpd()
            for ht in self.stats_httpd.httpd:
                self.assertTrue(isinstance(ht.socket, socket.socket))
            self.stats_httpd.close_httpd()

        # dual stack (address is ipv4)
        if self.ipv6_enabled:
            self.stats_httpd.http_addrs = [ ('127.0.0.1', 8000) ]
            self.stats_httpd.open_httpd()
            for ht in self.stats_httpd.httpd:
                self.assertTrue(isinstance(ht.socket, socket.socket))
            self.stats_httpd.close_httpd()

        # only-ipv4 single stack
        if not self.ipv6_enabled:
            self.stats_httpd.http_addrs = [ ('127.0.0.1', 8000) ]
            self.stats_httpd.open_httpd()
            for ht in self.stats_httpd.httpd:
                self.assertTrue(isinstance(ht.socket, socket.socket))
            self.stats_httpd.close_httpd()

        # only-ipv4 single stack (force set ipv6 )
        if not self.ipv6_enabled:
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
        self.assertRaises(stats_httpd.HttpServerError, self.stats_httpd.open_httpd)
        self.assertEqual(type(self.stats_httpd.httpd), list)
        self.assertEqual(len(self.stats_httpd.httpd), 0)
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

        # Address already in use
        self.statshttpd_server = ThreadingServerManager(MyStatsHttpd)
        self.statshttpd_server.server.load_config({'listen_on' : [{ 'address': '127.0.0.1', 'port' : 65454 }]})
        self.statshttpd_server.run()
        time.sleep(TIMEOUT_SEC)
        self.stats_httpd.load_config({'listen_on' : [{ 'address': '127.0.0.1', 'port' : 65454 }]})
        self.assertRaises(stats_httpd.HttpServerError, self.stats_httpd.open_httpd)
        self.statshttpd_server.shutdown()

    def test_running(self):
        self.assertFalse(self.stats_httpd.running)
        self.statshttpd_server = ThreadingServerManager(MyStatsHttpd)
        self.stats_httpd = self.statshttpd_server.server
        self.stats_httpd.load_config({'listen_on' : [{ 'address': '127.0.0.1', 'port' : 65455 }]})
        self.statshttpd_server.run()
        time.sleep(TIMEOUT_SEC*2)
        self.assertTrue(self.stats_httpd.running)
        self.statshttpd_server.shutdown()
        self.assertFalse(self.stats_httpd.running)

        # failure case
        self.stats_httpd = stats_httpd.StatsHttpd()
        self.stats_httpd.cc_session.close()
        self.assertRaises(
            isc.cc.session.SessionError, self.stats_httpd.start)

    def test_select_failure(self):
        def raise_select_except(*args):
            raise select.error('dummy error')
        def raise_select_except_with_errno(*args):
            raise select.error(errno.EINTR)
        (address, port) = ('127.0.0.1', 65456)
        stats_httpd.select.select = raise_select_except
        statshttpd = stats_httpd.StatsHttpd()
        statshttpd.load_config({'listen_on' : [{ 'address': address, 'port' : port }]})
        self.assertRaises(select.error, statshttpd.start)
        statshttpd.stop()
        stats_httpd.select.select = raise_select_except_with_errno
        statshttpd_server = ThreadingServerManager(MyStatsHttpd)
        statshttpd = statshttpd_server.server
        statshttpd.load_config({'listen_on' : [{ 'address': address, 'port' : port }]})
        statshttpd_server.run()
        time.sleep(TIMEOUT_SEC*2)
        statshttpd_server.shutdown()

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
                dict(listen_on=[dict(address="127.0.0.2",port=8000)])),
            isc.config.ccsession.create_answer(0))
        self.assertTrue("listen_on" in self.stats_httpd.config)
        for addr in self.stats_httpd.config["listen_on"]:
            self.assertTrue("address" in addr)
            self.assertTrue("port" in addr)
            self.assertTrue(addr["address"] == "127.0.0.2")
            self.assertTrue(addr["port"] == 8000)

        if self.ipv6_enabled:
            self.assertEqual(
                self.stats_httpd.config_handler(
                    dict(listen_on=[dict(address="::1",port=8000)])),
                isc.config.ccsession.create_answer(0))
            self.assertTrue("listen_on" in self.stats_httpd.config)
            for addr in self.stats_httpd.config["listen_on"]:
                self.assertTrue("address" in addr)
                self.assertTrue("port" in addr)
                self.assertTrue(addr["address"] == "::1")
                self.assertTrue(addr["port"] == 8000)

        self.assertEqual(
            self.stats_httpd.config_handler(
                        dict(listen_on=[dict(address="127.0.0.1",port=54321)])),
            isc.config.ccsession.create_answer(0))
        self.assertTrue("listen_on" in self.stats_httpd.config)
        for addr in self.stats_httpd.config["listen_on"]:
            self.assertTrue("address" in addr)
            self.assertTrue("port" in addr)
            self.assertTrue(addr["address"] == "127.0.0.1")
            self.assertTrue(addr["port"] == 54321)
        (ret, arg) = isc.config.ccsession.parse_answer(
            self.stats_httpd.config_handler(
                dict(listen_on=[dict(address="1.2.3.4",port=543210)]))
            )
        self.assertEqual(ret, 1)

    def test_xml_handler(self):
        orig_get_stats_data = stats_httpd.StatsHttpd.get_stats_data
        stats_httpd.StatsHttpd.get_stats_data = lambda x: \
            { 'Dummy' : { 'foo':'bar' } }
        xml_body1 = stats_httpd.StatsHttpd().open_template(
            stats_httpd.XML_TEMPLATE_LOCATION).substitute(
            xml_string='<Dummy><foo>bar</foo></Dummy>',
            xsd_namespace=stats_httpd.XSD_NAMESPACE,
            xsd_url_path=stats_httpd.XSD_URL_PATH,
            xsl_url_path=stats_httpd.XSL_URL_PATH)
        xml_body2 = stats_httpd.StatsHttpd().xml_handler()
        self.assertEqual(type(xml_body1), str)
        self.assertEqual(type(xml_body2), str)
        self.assertEqual(xml_body1, xml_body2)
        stats_httpd.StatsHttpd.get_stats_data = lambda x: \
            { 'Dummy' : {'bar':'foo'} }
        xml_body2 = stats_httpd.StatsHttpd().xml_handler()
        self.assertNotEqual(xml_body1, xml_body2)
        stats_httpd.StatsHttpd.get_stats_data = orig_get_stats_data

    def test_xsd_handler(self):
        orig_get_stats_spec = stats_httpd.StatsHttpd.get_stats_spec
        stats_httpd.StatsHttpd.get_stats_spec = lambda x: \
            { "Dummy" :
                  [{
                        "item_name": "foo",
                        "item_type": "string",
                        "item_optional": False,
                        "item_default": "bar",
                        "item_description": "foo is bar",
                        "item_title": "Foo"
                        }]
              }
        xsd_body1 = stats_httpd.StatsHttpd().open_template(
            stats_httpd.XSD_TEMPLATE_LOCATION).substitute(
            xsd_string=\
                '<all><element name="Dummy"><complexType><all>' \
                + '<element maxOccurs="1" minOccurs="1" name="foo" type="string">' \
                + '<annotation><appinfo>Foo</appinfo>' \
                + '<documentation>foo is bar</documentation>' \
                + '</annotation></element></all>' \
                + '</complexType></element></all>',
            xsd_namespace=stats_httpd.XSD_NAMESPACE)
        xsd_body2 = stats_httpd.StatsHttpd().xsd_handler()
        self.assertEqual(type(xsd_body1), str)
        self.assertEqual(type(xsd_body2), str)
        self.assertEqual(xsd_body1, xsd_body2)
        stats_httpd.StatsHttpd.get_stats_spec = lambda x: \
            { "Dummy" :
                  [{
                        "item_name": "bar",
                        "item_type": "string",
                        "item_optional": False,
                        "item_default": "foo",
                        "item_description": "bar is foo",
                        "item_title": "bar"
                        }]
              }
        xsd_body2 = stats_httpd.StatsHttpd().xsd_handler()
        self.assertNotEqual(xsd_body1, xsd_body2)
        stats_httpd.StatsHttpd.get_stats_spec = orig_get_stats_spec

    def test_xsl_handler(self):
        orig_get_stats_spec = stats_httpd.StatsHttpd.get_stats_spec
        stats_httpd.StatsHttpd.get_stats_spec = lambda x: \
            { "Dummy" :
                  [{
                        "item_name": "foo",
                        "item_type": "string",
                        "item_optional": False,
                        "item_default": "bar",
                        "item_description": "foo is bar",
                        "item_title": "Foo"
                        }]
              }
        xsl_body1 = stats_httpd.StatsHttpd().open_template(
            stats_httpd.XSL_TEMPLATE_LOCATION).substitute(
            xsl_string='<xsl:template match="*"><tr>' \
                + '<td>Dummy</td>' \
                + '<td class="title" title="foo is bar">Foo</td>' \
                + '<td><xsl:value-of select="Dummy/foo" /></td>' \
                + '</tr></xsl:template>',
            xsd_namespace=stats_httpd.XSD_NAMESPACE)
        xsl_body2 = stats_httpd.StatsHttpd().xsl_handler()
        self.assertEqual(type(xsl_body1), str)
        self.assertEqual(type(xsl_body2), str)
        self.assertEqual(xsl_body1, xsl_body2)
        stats_httpd.StatsHttpd.get_stats_spec = lambda x: \
            { "Dummy" :
                  [{
                        "item_name": "bar",
                        "item_type": "string",
                        "item_optional": False,
                        "item_default": "foo",
                        "item_description": "bar is foo",
                        "item_title": "bar"
                        }]
              }
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

if __name__ == "__main__":
    unittest.main()
