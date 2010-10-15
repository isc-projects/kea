# Copyright (C) 2010  Internet Systems Consortium.
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

# $Id$
__version__ = "$Revision$"

#
# Tests for the stats stub module
#
import unittest
import time
import os
import imp
import stats_stub
from isc.cc.session import Session
from stats_stub import CCSessionStub, BossModuleStub, AuthModuleStub
from stats import get_datetime

class TestStats(unittest.TestCase):

    def setUp(self):
        self.session = Session()
        self.stub = CCSessionStub(session=self.session, verbose=True)
        self.boss = BossModuleStub(session=self.session, verbose=True)
        self.auth = AuthModuleStub(session=self.session, verbose=True)
        self.env = {'from': self.session.lname, 'group': 'Stats',
                    'instance': '*', 'to':'*',
                    'type':'send','seq':0}
        self.result_ok = {'result': [0]}

    def tearDown(self):
        self.session.close()

    def test_stub(self):
        """
        Test for send_command of CCSessionStub object
        """
        env = self.env
        result_ok = self.result_ok
        self.assertEqual(('status', None, env),
                         self.stub.send_command('status', None))
        self.assertEqual(result_ok, self.session.get_message("Stats", None))
        self.assertEqual(('shutdown', None, env),
                         self.stub.send_command('shutdown', None))
        self.assertEqual(result_ok, self.session.get_message("Stats", None))
        self.assertEqual(('show', None, env),
                         self.stub.send_command('show', None))
        self.assertEqual(result_ok, self.session.get_message("Stats", None))
        self.assertEqual(('set', {'atest': 100.0}, env),
                         self.stub.send_command('set', {'atest': 100.0}))
        self.assertEqual(result_ok, self.session.get_message("Stats", None))

    def test_boss_stub(self):
        """
        Test for send_command of BossModuleStub object
        """
        env = self.env
        result_ok = self.result_ok
        self.assertEqual(('set', {"stats_data":
                                      {"bind10.boot_time": get_datetime()}
                                  }, env), self.boss.send_boottime())
        self.assertEqual(result_ok, self.session.get_message("Stats", None))

    def test_auth_stub(self):
        """
        Test for send_command of AuthModuleStub object
        """
        env = self.env
        result_ok = self.result_ok
        self.assertEqual(
            ('set', {"stats_data": {"auth.queries.udp": 1}}, env),
            self.auth.send_udp_query_count())
        self.assertEqual(result_ok, self.session.get_message("Stats", None))
        self.assertEqual(
            ('set', {"stats_data": {"auth.queries.tcp": 1}}, env),
            self.auth.send_tcp_query_count())
        self.assertEqual(result_ok, self.session.get_message("Stats", None))
        self.assertEqual(
            ('set', {"stats_data": {"auth.queries.udp": 100}}, env),
            self.auth.send_udp_query_count(cmd='set', cnt=100))
        self.assertEqual(result_ok, self.session.get_message("Stats", None))
        self.assertEqual(
            ('set', {"stats_data": {"auth.queries.tcp": 99}}, env),
            self.auth.send_tcp_query_count(cmd='set', cnt=99))
        self.assertEqual(result_ok, self.session.get_message("Stats", None))

    def test_func_main(self):
        # explicitly make failed
        self.session.close()
        stats_stub.main(session=self.session)

    def test_osenv(self):
        """
        test for not having environ "B10_FROM_BUILD"
        """
        if "B10_FROM_BUILD" in os.environ:
            path = os.environ["B10_FROM_BUILD"]
            os.environ.pop("B10_FROM_BUILD")
            imp.reload(stats_stub)
            os.environ["B10_FROM_BUILD"] = path
            imp.reload(stats_stub)

if __name__ == "__main__":
    unittest.main()
