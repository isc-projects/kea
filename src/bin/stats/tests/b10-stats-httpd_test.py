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

"""
In each of these tests we start several virtual components. They are
not the real components, no external processes are started. They are
just simple mock objects running each in its own thread and pretending
to be bind10 modules. This helps testing the stats http server in a
close to real environment.
"""

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
import random

import isc
import stats_httpd
import stats
from test_utils import BaseModules, ThreadingServerManager, MyStats, MyStatsHttpd, SignalHandler, send_command, send_shutdown

DUMMY_DATA = {
    'Boss' : {
        "boot_time": "2011-03-04T11:59:06Z"
        },
    'Auth' : {
        "queries.tcp": 2,
        "queries.udp": 3,
        "queries.perzone": [{
                "zonename": "test.example",
                "queries.tcp": 2,
                "queries.udp": 3
                }]
        },
    'Stats' : {
        "report_time": "2011-03-04T11:59:19Z",
        "boot_time": "2011-03-04T11:59:06Z",
        "last_update_time": "2011-03-04T11:59:07Z",
        "lname": "4d70d40a_c@host",
        "timestamp": 1299239959.560846
        }
    }

def get_availaddr(address='127.0.0.1', port=8001):
    """returns a tuple of address and port which is available to
    listen on the platform. The first argument is a address for
    search. The second argument is a port for search. If a set of
    address and port is failed on the search for the availability, the
    port number is increased and it goes on the next trial until the
    available set of address and port is looked up. If the port number
    reaches over 65535, it may stop the search and raise a
    OverflowError exception."""
    while True:
        for addr in socket.getaddrinfo(
            address, port, 0,
            socket.SOCK_STREAM, socket.IPPROTO_TCP):
            sock = socket.socket(addr[0], socket.SOCK_STREAM)
            try:
                sock.bind((address, port))
                return (address, port)
            except socket.error:
                continue
            finally:
                if sock: sock.close()
        # This address and port number are already in use.
        # next port number is added
        port = port + 1

def is_ipv6_enabled(address='::1', port=8001):
    """checks IPv6 enabled on the platform. address for check is '::1'
    and port for check is random number between 8001 and
    65535. Retrying is 3 times even if it fails. The built-in socket
    module provides a 'has_ipv6' parameter, but it's not used here
    because there may be a situation where the value is True on an
    environment where the IPv6 config is disabled."""
    for p in random.sample(range(port, 65535), 3):
        try:
            sock = socket.socket(socket.AF_INET6, socket.SOCK_STREAM)
            sock.bind((address, p))
            return True
        except socket.error:
            continue
        finally:
            if sock: sock.close()
    return False

class TestHttpHandler(unittest.TestCase):
    """Tests for HttpHandler class"""
    def setUp(self):
        # set the signal handler for deadlock
        self.sig_handler = SignalHandler(self.fail)
        self.base = BaseModules()
        self.stats_server = ThreadingServerManager(MyStats)
        self.stats = self.stats_server.server
        self.stats_server.run()
        (self.address, self.port) = get_availaddr()
        self.stats_httpd_server = ThreadingServerManager(MyStatsHttpd, (self.address, self.port))
        self.stats_httpd = self.stats_httpd_server.server
        self.stats_httpd_server.run()
        self.client = http.client.HTTPConnection(self.address, self.port)
        self.client._http_vsn_str = 'HTTP/1.0\n'
        self.client.connect()

    def tearDown(self):
        self.client.close()
        self.stats_httpd_server.shutdown()
        self.stats_server.shutdown()
        self.base.shutdown()
        # reset the signal handler
        self.sig_handler.reset()

    def test_do_GET(self):
        self.assertTrue(type(self.stats_httpd.httpd) is list)
        self.assertEqual(len(self.stats_httpd.httpd), 1)
        self.assertEqual((self.address, self.port), self.stats_httpd.http_addrs[0])

        def check_XML_URL_PATH(mod=None, item=None):
            url_path = stats_httpd.XML_URL_PATH
            if mod is not None:
                url_path = url_path + '/' + mod
                if item is not None:
                    url_path = url_path + '/' + item
            self.client.putrequest('GET', url_path)
            self.client.endheaders()
            response = self.client.getresponse()
            self.assertEqual(response.getheader("Content-type"), "text/xml")
            self.assertTrue(int(response.getheader("Content-Length")) > 0)
            self.assertEqual(response.status, 200)
            root = xml.etree.ElementTree.parse(response).getroot()
            self.assertTrue(root.tag.find('statistics') > 0)
            for (k,v) in root.attrib.items():
                if k.find('schemaLocation') > 0:
                    self.assertEqual(v, stats_httpd.XSD_NAMESPACE + ' ' + stats_httpd.XSD_URL_PATH)
            if item is None and mod is None:
                for m in DUMMY_DATA:
                    for k in DUMMY_DATA[m].keys():
                        self.assertIsNotNone(root.find(m + '/' + k))
            elif item is None:
                for k in DUMMY_DATA[mod].keys():
                    self.assertIsNotNone(root.find(k))
            else:
                self.assertIsNotNone(root.find(item))
        # URL is '/bind10/statistics/xml'
        check_XML_URL_PATH(mod=None, item=None)
        for m in DUMMY_DATA:
            # URL is '/bind10/statistics/xml/Module'
            check_XML_URL_PATH(mod=m)
            for k in DUMMY_DATA[m].keys():
                # URL is '/bind10/statistics/xml/Module/Item'
                check_XML_URL_PATH(mod=m, item=k)

        def check_XSD_URL_PATH(mod=None, item=None):
            url_path = stats_httpd.XSD_URL_PATH
            if mod is not None:
                url_path = url_path + '/' + mod
                if item is not None:
                    url_path = url_path + '/' + item
            self.client.putrequest('GET', url_path)
            self.client.endheaders()
            response = self.client.getresponse()
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
                if mod is None:
                    self.assertIsNotNone(elm.attrib['name'])
                    self.assertTrue(elm.attrib['name'] in DUMMY_DATA)
                else:
                    self.assertIsNotNone(elm.attrib['name'])
                    self.assertTrue(elm.attrib['name'] in DUMMY_DATA[mod])

        # URL is '/bind10/statistics/xsd'
        check_XSD_URL_PATH(mod=None, item=None)
        for m in DUMMY_DATA:
            # URL is '/bind10/statistics/xsd/Module'
            check_XSD_URL_PATH(mod=m)
            for k in DUMMY_DATA[m].keys():
                # URL is '/bind10/statistics/xsd/Module/Item'
                check_XSD_URL_PATH(mod=m, item=k)

        def check_XSL_URL_PATH(mod=None, item=None):
            url_path = stats_httpd.XSL_URL_PATH
            if mod is not None:
                url_path = url_path + '/' + mod
                if item is not None:
                    url_path = url_path + '/' + item
            self.client.putrequest('GET', url_path)
            self.client.endheaders()
            response = self.client.getresponse()
            self.assertEqual(response.getheader("Content-type"), "text/xml")
            self.assertTrue(int(response.getheader("Content-Length")) > 0)
            self.assertEqual(response.status, 200)
            root = xml.etree.ElementTree.parse(response).getroot()
            url_trans = '{http://www.w3.org/1999/XSL/Transform}'
            url_xhtml = '{http://www.w3.org/1999/xhtml}'
            self.assertEqual(root.tag, url_trans + 'stylesheet')
            if item is None and mod is None:
                xslpath = url_trans + 'template/' + url_xhtml + 'table/' + url_trans + 'for-each'
                for fe in root.findall(xslpath):
                    self.assertTrue(fe.attrib['select'] in DUMMY_DATA)
                    for vo in fe.findall(url_xhtml + 'tr/' \
                                             + url_xhtml + 'td/' \
                                             + url_xhtml + 'table/' \
                                             + url_xhtml + 'tr/' \
                                             + url_xhtml + 'td/' \
                                             + url_trans + 'value-of/'):
                        self.assertTrue(vo.attrib['select'] in DUMMY_DATA[fe.attrib['select']])
            elif item is None:
                xslpath = url_trans + 'template/' \
                    + url_xhtml + 'table/' + url_xhtml + 'tr/' + url_xhtml + 'td/' \
                    + url_trans + 'value-of'
                for vo in root.findall(xslpath):
                    self.assertTrue(vo.attrib['select'] in DUMMY_DATA[mod])
            else:
                xslpath = url_trans + 'template/' \
                    + url_xhtml + 'table/' + url_xhtml + 'tr/' + url_xhtml + 'td/' \
                    + url_trans + 'value-of'
                for vo in root.findall(xslpath):
                    self.assertEqual(vo.attrib['select'], item)

        # URL is '/bind10/statistics/xsl'
        check_XSL_URL_PATH(mod=None, item=None)
        for m in DUMMY_DATA:
            # URL is '/bind10/statistics/xsl/Module'
            check_XSL_URL_PATH(mod=m)
            for k in DUMMY_DATA[m].keys():
                # URL is '/bind10/statistics/xsl/Module/Item'
                check_XSL_URL_PATH(mod=m, item=k)

        # 302 redirect
        self.client._http_vsn_str = 'HTTP/1.1'
        self.client.putrequest('GET', '/')
        self.client.putheader('Host', self.address)
        self.client.endheaders()
        response = self.client.getresponse()
        self.assertEqual(response.status, 302)
        self.assertEqual(response.getheader('Location'),
                         "http://%s:%d%s" % (self.address, self.port, stats_httpd.XML_URL_PATH))

        # 404 NotFound
        self.client._http_vsn_str = 'HTTP/1.0'
        self.client.putrequest('GET', '/path/to/foo/bar')
        self.client.endheaders()
        response = self.client.getresponse()
        self.assertEqual(response.status, 404)


    def test_do_GET_failed1(self):
        # checks status
        self.assertEqual(send_command("status", "Stats"),
                         (0, "Stats is up. (PID " + str(os.getpid()) + ")"))
        # failure case(Stats is down)
        self.assertTrue(self.stats.running)
        self.assertEqual(send_shutdown("Stats"), (0, None)) # Stats is down
        self.assertFalse(self.stats.running)
        self.stats_httpd.cc_session.set_timeout(milliseconds=100)

        # request XML
        self.client.putrequest('GET', stats_httpd.XML_URL_PATH)
        self.client.endheaders()
        response = self.client.getresponse()
        self.assertEqual(response.status, 500)

        # request XSD
        self.client.putrequest('GET', stats_httpd.XSD_URL_PATH)
        self.client.endheaders()
        response = self.client.getresponse()
        self.assertEqual(response.status, 500)

        # request XSL
        self.client.putrequest('GET', stats_httpd.XSL_URL_PATH)
        self.client.endheaders()
        response = self.client.getresponse()
        self.assertEqual(response.status, 500)

    def test_do_GET_failed2(self):
        # failure case(Stats replies an error)
        self.stats.mccs.set_command_handler(
            lambda cmd, args: \
                isc.config.ccsession.create_answer(1, "I have an error.")
            )

        # request XML
        self.client.putrequest('GET', stats_httpd.XML_URL_PATH)
        self.client.endheaders()
        response = self.client.getresponse()
        self.assertEqual(response.status, 500)

        # request XSD
        self.client.putrequest('GET', stats_httpd.XSD_URL_PATH)
        self.client.endheaders()
        response = self.client.getresponse()
        self.assertEqual(response.status, 500)

        # request XSL
        self.client.putrequest('GET', stats_httpd.XSL_URL_PATH)
        self.client.endheaders()
        response = self.client.getresponse()
        self.assertEqual(response.status, 500)

    def test_do_HEAD(self):
        self.client.putrequest('HEAD', stats_httpd.XML_URL_PATH)
        self.client.endheaders()
        response = self.client.getresponse()
        self.assertEqual(response.status, 200)

        self.client.putrequest('HEAD', '/path/to/foo/bar')
        self.client.endheaders()
        response = self.client.getresponse()
        self.assertEqual(response.status, 404)

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
        # set the signal handler for deadlock
        self.sig_handler = SignalHandler(self.fail)
        self.base = BaseModules()

    def tearDown(self):
        if hasattr(self, "stats_httpd"):
            self.stats_httpd.stop()
        self.base.shutdown()
        # reset the signal handler
        self.sig_handler.reset()

    def test_httpserver(self):
        self.stats_httpd = MyStatsHttpd(get_availaddr())
        self.assertEqual(type(self.stats_httpd.httpd), list)
        self.assertEqual(len(self.stats_httpd.httpd), 1)
        for httpd in self.stats_httpd.httpd:
            self.assertTrue(isinstance(httpd, stats_httpd.HttpServer))

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
        # set the signal handler for deadlock
        self.sig_handler = SignalHandler(self.fail)
        self.base = BaseModules()
        self.stats_server = ThreadingServerManager(MyStats)
        self.stats_server.run()
        # checking IPv6 enabled on this platform
        self.ipv6_enabled = is_ipv6_enabled()

    def tearDown(self):
        if hasattr(self, "stats_httpd"):
            self.stats_httpd.stop()
        self.stats_server.shutdown()
        self.base.shutdown()
        # reset the signal handler
        self.sig_handler.reset()

    def test_init(self):
        server_address = get_availaddr()
        self.stats_httpd = MyStatsHttpd(server_address)
        self.assertEqual(self.stats_httpd.running, False)
        self.assertEqual(self.stats_httpd.poll_intval, 0.5)
        self.assertNotEqual(len(self.stats_httpd.httpd), 0)
        self.assertEqual(type(self.stats_httpd.mccs), isc.config.ModuleCCSession)
        self.assertEqual(type(self.stats_httpd.cc_session), isc.cc.Session)
        self.assertEqual(len(self.stats_httpd.config), 2)
        self.assertTrue('listen_on' in self.stats_httpd.config)
        self.assertEqual(len(self.stats_httpd.config['listen_on']), 1)
        self.assertTrue('address' in self.stats_httpd.config['listen_on'][0])
        self.assertTrue('port' in self.stats_httpd.config['listen_on'][0])
        self.assertTrue(server_address in set(self.stats_httpd.http_addrs))

    def test_openclose_mccs(self):
        self.stats_httpd = MyStatsHttpd(get_availaddr())
        self.stats_httpd.close_mccs()
        self.assertEqual(self.stats_httpd.mccs, None)
        self.stats_httpd.open_mccs()
        self.assertIsNotNone(self.stats_httpd.mccs)
        self.stats_httpd.mccs = None
        self.assertEqual(self.stats_httpd.mccs, None)
        self.assertEqual(self.stats_httpd.close_mccs(), None)

    def test_mccs(self):
        self.stats_httpd = MyStatsHttpd(get_availaddr())
        self.assertIsNotNone(self.stats_httpd.mccs.get_socket())
        self.assertTrue(
            isinstance(self.stats_httpd.mccs.get_socket(), socket.socket))
        self.assertTrue(
            isinstance(self.stats_httpd.cc_session, isc.cc.session.Session))
        statistics_spec = self.stats_httpd.get_stats_spec()
        for mod in DUMMY_DATA:
            self.assertTrue(mod in statistics_spec)
            for cfg in statistics_spec[mod]:
                self.assertTrue('item_name' in cfg)
                self.assertTrue(cfg['item_name'] in DUMMY_DATA[mod])
            self.assertTrue(len(statistics_spec[mod]), len(DUMMY_DATA[mod]))
        self.stats_httpd.close_mccs()
        self.assertIsNone(self.stats_httpd.mccs)

    def test_httpd(self):
        # dual stack (addresses is ipv4 and ipv6)
        if self.ipv6_enabled:
            server_addresses = (get_availaddr('::1'), get_availaddr())
            self.stats_httpd = MyStatsHttpd(*server_addresses)
            for ht in self.stats_httpd.httpd:
                self.assertTrue(isinstance(ht, stats_httpd.HttpServer))
                self.assertTrue(ht.address_family in set([socket.AF_INET, socket.AF_INET6]))
                self.assertTrue(isinstance(ht.socket, socket.socket))

        # dual stack (address is ipv6)
        if self.ipv6_enabled:
            server_addresses = get_availaddr('::1')
            self.stats_httpd = MyStatsHttpd(server_addresses)
            for ht in self.stats_httpd.httpd:
                self.assertTrue(isinstance(ht, stats_httpd.HttpServer))
                self.assertEqual(ht.address_family, socket.AF_INET6)
                self.assertTrue(isinstance(ht.socket, socket.socket))

        # dual/single stack (address is ipv4)
        server_addresses = get_availaddr()
        self.stats_httpd = MyStatsHttpd(server_addresses)
        for ht in self.stats_httpd.httpd:
            self.assertTrue(isinstance(ht, stats_httpd.HttpServer))
            self.assertEqual(ht.address_family, socket.AF_INET)
            self.assertTrue(isinstance(ht.socket, socket.socket))

        # any address (IPv4)
        server_addresses = get_availaddr(address='0.0.0.0')
        self.stats_httpd = MyStatsHttpd(server_addresses)
        for ht in self.stats_httpd.httpd:
            self.assertTrue(isinstance(ht, stats_httpd.HttpServer))
            self.assertEqual(ht.address_family,socket.AF_INET)
            self.assertTrue(isinstance(ht.socket, socket.socket))

        # any address (IPv6)
        if self.ipv6_enabled:
            server_addresses = get_availaddr(address='::')
            self.stats_httpd = MyStatsHttpd(server_addresses)
            for ht in self.stats_httpd.httpd:
                self.assertTrue(isinstance(ht, stats_httpd.HttpServer))
                self.assertEqual(ht.address_family,socket.AF_INET6)
                self.assertTrue(isinstance(ht.socket, socket.socket))

        # existent hostname
        self.assertRaises(stats_httpd.HttpServerError, MyStatsHttpd,
                          get_availaddr(address='localhost'))

        # nonexistent hostname
        self.assertRaises(stats_httpd.HttpServerError, MyStatsHttpd, ('my.host.domain', 8000))

        # over flow of port number
        self.assertRaises(stats_httpd.HttpServerError, MyStatsHttpd, ('127.0.0.1', 80000))

        # negative
        self.assertRaises(stats_httpd.HttpServerError, MyStatsHttpd, ('127.0.0.1', -8000))

        # alphabet
        self.assertRaises(stats_httpd.HttpServerError, MyStatsHttpd, ('127.0.0.1', 'ABCDE'))

        # Address already in use
        server_addresses = get_availaddr()
        self.stats_httpd_server = ThreadingServerManager(MyStatsHttpd, server_addresses)
        self.stats_httpd_server.run()
        self.assertRaises(stats_httpd.HttpServerError, MyStatsHttpd, server_addresses)
        send_shutdown("StatsHttpd")

    def test_running(self):
        self.stats_httpd_server = ThreadingServerManager(MyStatsHttpd, get_availaddr())
        self.stats_httpd = self.stats_httpd_server.server
        self.assertFalse(self.stats_httpd.running)
        self.stats_httpd_server.run()
        self.assertEqual(send_command("status", "StatsHttpd"),
                         (0, "Stats Httpd is up. (PID " + str(os.getpid()) + ")"))
        self.assertTrue(self.stats_httpd.running)
        self.assertEqual(send_shutdown("StatsHttpd"), (0, None))
        self.assertFalse(self.stats_httpd.running)
        self.stats_httpd_server.shutdown()

        # failure case
        self.stats_httpd = MyStatsHttpd(get_availaddr())
        self.stats_httpd.cc_session.close()
        self.assertRaises(ValueError, self.stats_httpd.start)

    def test_failure_with_a_select_error (self):
        """checks select.error is raised if the exception except
        errno.EINTR is raised while it's selecting"""
        def raise_select_except(*args):
            raise select.error('dummy error')
        orig_select = stats_httpd.select.select
        stats_httpd.select.select = raise_select_except
        self.stats_httpd = MyStatsHttpd(get_availaddr())
        self.assertRaises(select.error, self.stats_httpd.start)
        stats_httpd.select.select = orig_select

    def test_nofailure_with_errno_EINTR(self):
        """checks no exception is raised if errno.EINTR is raised
        while it's selecting"""
        def raise_select_except(*args):
            raise select.error(errno.EINTR)
        orig_select = stats_httpd.select.select
        stats_httpd.select.select = raise_select_except
        self.stats_httpd_server = ThreadingServerManager(MyStatsHttpd, get_availaddr())
        self.stats_httpd_server.run()
        self.stats_httpd_server.shutdown()
        stats_httpd.select.select = orig_select

    def test_open_template(self):
        self.stats_httpd = MyStatsHttpd(get_availaddr())
        # successful conditions
        tmpl = self.stats_httpd.open_template(stats_httpd.XML_TEMPLATE_LOCATION)
        self.assertTrue(isinstance(tmpl, string.Template))
        opts = dict(
            xml_string="<dummy></dummy>",
            xsl_url_path="/path/to/")
        lines = tmpl.substitute(opts)
        for n in opts:
            self.assertTrue(lines.find(opts[n])>0)
        tmpl = self.stats_httpd.open_template(stats_httpd.XSD_TEMPLATE_LOCATION)
        self.assertTrue(isinstance(tmpl, string.Template))
        opts = dict(xsd_string="<dummy></dummy>")
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
        self.stats_httpd = MyStatsHttpd(get_availaddr())
        self.assertEqual(self.stats_httpd.command_handler("status", None),
                         isc.config.ccsession.create_answer(
                0, "Stats Httpd is up. (PID " + str(os.getpid()) + ")"))
        self.stats_httpd.running = True
        self.assertEqual(self.stats_httpd.command_handler("shutdown", None),
                         isc.config.ccsession.create_answer(0))
        self.assertFalse(self.stats_httpd.running)
        self.assertEqual(
            self.stats_httpd.command_handler("__UNKNOWN_COMMAND__", None),
            isc.config.ccsession.create_answer(
                1, "Unknown command: __UNKNOWN_COMMAND__"))

    def test_config(self):
        self.stats_httpd = MyStatsHttpd(get_availaddr())
        self.assertEqual(
            self.stats_httpd.config_handler(dict(_UNKNOWN_KEY_=None)),
            isc.config.ccsession.create_answer(
                1, "unknown item _UNKNOWN_KEY_"))

        addresses = get_availaddr()
        self.assertEqual(
            self.stats_httpd.config_handler(
                dict(listen_on=[dict(address=addresses[0],port=addresses[1])])),
            isc.config.ccsession.create_answer(0))
        self.assertTrue("listen_on" in self.stats_httpd.config)
        for addr in self.stats_httpd.config["listen_on"]:
            self.assertTrue("address" in addr)
            self.assertTrue("port" in addr)
            self.assertTrue(addr["address"] == addresses[0])
            self.assertTrue(addr["port"] == addresses[1])

        if self.ipv6_enabled:
            addresses = get_availaddr("::1")
            self.assertEqual(
                self.stats_httpd.config_handler(
                dict(listen_on=[dict(address=addresses[0],port=addresses[1])])),
                isc.config.ccsession.create_answer(0))
            self.assertTrue("listen_on" in self.stats_httpd.config)
            for addr in self.stats_httpd.config["listen_on"]:
                self.assertTrue("address" in addr)
                self.assertTrue("port" in addr)
                self.assertTrue(addr["address"] == addresses[0])
                self.assertTrue(addr["port"] == addresses[1])

        addresses = get_availaddr()
        self.assertEqual(
            self.stats_httpd.config_handler(
                dict(listen_on=[dict(address=addresses[0],port=addresses[1])])),
            isc.config.ccsession.create_answer(0))
        self.assertTrue("listen_on" in self.stats_httpd.config)
        for addr in self.stats_httpd.config["listen_on"]:
            self.assertTrue("address" in addr)
            self.assertTrue("port" in addr)
            self.assertTrue(addr["address"] == addresses[0])
            self.assertTrue(addr["port"] == addresses[1])
        (ret, arg) = isc.config.ccsession.parse_answer(
            self.stats_httpd.config_handler(
                dict(listen_on=[dict(address="1.2.3.4",port=543210)]))
            )
        self.assertEqual(ret, 1)

    def test_xml_handler(self):
        self.stats_httpd = MyStatsHttpd(get_availaddr())
        self.stats_httpd.get_stats_spec = lambda x,y: \
            { 'Dummy' : [ {
                'item_name' : 'foo',
                'item_type' : 'string' } ] }
        self.stats_httpd.get_stats_data = lambda x,y: \
            { 'Dummy' : { 'foo':'bar' } }
        xml_body1 = self.stats_httpd.open_template(
            stats_httpd.XML_TEMPLATE_LOCATION).substitute(
            xml_string='<bind10:statistics xmlns:bind10="http://bind10.isc.org/bind10" xmlns:xsi="http://www.w3.org/2001/XMLSchema-instance" xsi:schemaLocation="http://bind10.isc.org/bind10 /bind10/statistics/xsd"><Dummy><foo>bar</foo></Dummy></bind10:statistics>',
            xsl_url_path=stats_httpd.XSL_URL_PATH)
        xml_body2 = self.stats_httpd.xml_handler()
        self.assertEqual(type(xml_body1), str)
        self.assertEqual(type(xml_body2), str)
        self.assertEqual(xml_body1, xml_body2)
        self.stats_httpd.get_stats_spec = lambda x,y: \
            { 'Dummy' : [ {
                'item_name' : 'bar',
                'item_type' : 'string' } ] }
        self.stats_httpd.get_stats_data = lambda x,y: \
            { 'Dummy' : {'bar':'foo'} }
        xml_body2 = self.stats_httpd.xml_handler()
        self.assertNotEqual(xml_body1, xml_body2)

    def test_xsd_handler(self):
        self.stats_httpd = MyStatsHttpd(get_availaddr())
        self.stats_httpd.get_stats_spec = lambda x,y: \
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
        xsd_body1 = self.stats_httpd.open_template(
            stats_httpd.XSD_TEMPLATE_LOCATION).substitute(
            xsd_string='<schema targetNamespace="' + stats_httpd.XSD_NAMESPACE + '" xmlns="http://www.w3.org/2001/XMLSchema" xmlns:bind10="' + stats_httpd.XSD_NAMESPACE + '"><annotation><documentation>XML schema of the statistics data in BIND 10</documentation></annotation><element name="statistics"><annotation><documentation>A set of statistics data</documentation></annotation><complexType><all><element name="Dummy"><complexType><all><element maxOccurs="1" minOccurs="1" name="foo" type="string"><annotation><appinfo>Foo</appinfo><documentation>foo is bar</documentation></annotation></element></all></complexType></element></all></complexType></element></schema>')
        xsd_body2 = self.stats_httpd.xsd_handler()
        self.assertEqual(type(xsd_body1), str)
        self.assertEqual(type(xsd_body2), str)
        self.assertEqual(xsd_body1, xsd_body2)
        self.stats_httpd.get_stats_spec = lambda x,y: \
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
        xsd_body2 = self.stats_httpd.xsd_handler()
        self.assertNotEqual(xsd_body1, xsd_body2)

    def test_xsl_handler(self):
        self.stats_httpd = MyStatsHttpd(get_availaddr())
        self.stats_httpd.get_stats_spec = lambda x,y: \
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
        xsl_body1 = self.stats_httpd.open_template(
            stats_httpd.XSL_TEMPLATE_LOCATION).substitute(
            xsl_string='<xsl:template match="bind10:statistics"><table><tr><th>Module Names</th><th>Items</th></tr><xsl:for-each select="Dummy"><tr><td>Dummy</td><td><table><tr><th>Item Names</th><th>Values</th></tr><tr><td>foo</td><td><xsl:value-of select="foo" /></td></tr></table></td></tr></xsl:for-each></table></xsl:template>',
            xsd_namespace=stats_httpd.XSD_NAMESPACE)
        xsl_body2 = self.stats_httpd.xsl_handler()
        self.assertEqual(type(xsl_body1), str)
        self.assertEqual(type(xsl_body2), str)
        self.assertEqual(xsl_body1, xsl_body2)
        self.stats_httpd.get_stats_spec = lambda x,y: \
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
        xsl_body2 = self.stats_httpd.xsl_handler()
        self.assertNotEqual(xsl_body1, xsl_body2)

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
