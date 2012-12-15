# Copyright (C) 2012  Internet Systems Consortium.
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

'''Tests for the loadzone module'''

import unittest
from loadzone import *
from isc.dns import *
from isc.datasrc import *
import isc.log
import os
import shutil

# Some common test parameters
TESTDATA_PATH = os.environ['TESTDATA_PATH'] + os.sep
READ_ZONE_DB_FILE = TESTDATA_PATH + "rwtest.sqlite3" # original, to be copied
LOCAL_TESTDATA_PATH = os.environ['LOCAL_TESTDATA_PATH'] + os.sep
READ_ZONE_DB_FILE = TESTDATA_PATH + "rwtest.sqlite3" # original, to be copied
NEW_ZONE_TXT_FILE = LOCAL_TESTDATA_PATH + "example.org.zone"
ALT_NEW_ZONE_TXT_FILE = TESTDATA_PATH + "example.com.zone"
TESTDATA_WRITE_PATH = os.environ['TESTDATA_WRITE_PATH'] + os.sep
WRITE_ZONE_DB_FILE = TESTDATA_WRITE_PATH + "rwtest.sqlite3.copied"
TEST_ZONE_NAME = Name('example.org')
DATASRC_CONFIG = '{"database_file": "' + WRITE_ZONE_DB_FILE + '"}'

# before/after SOAs: different in mname and serial
ORIG_SOA_TXT = 'example.org. 3600 IN SOA ns1.example.org. ' +\
    'admin.example.org. 1234 3600 1800 2419200 7200\n'
NEW_SOA_TXT = 'example.org. 3600 IN SOA ns.example.org. ' +\
    'admin.example.org. 1235 3600 1800 2419200 7200\n'
# This is the brandnew SOA for a newly created zone
ALT_NEW_SOA_TXT = 'example.com. 3600 IN SOA ns.example.com. ' +\
    'admin.example.com. 1234 3600 1800 2419200 7200\n'

class TestLoadZoneRunner(unittest.TestCase):
    def setUp(self):
        shutil.copyfile(READ_ZONE_DB_FILE, WRITE_ZONE_DB_FILE)

        # default command line arguments
        self.__args = ['-c', DATASRC_CONFIG, 'example.org', NEW_ZONE_TXT_FILE]
        self.__runner = LoadZoneRunner(self.__args)

    def tearDown(self):
        # Delete the used DB file; if some of the tests unexpectedly fail
        # unexpectedly in the middle of updating the DB, a lock could stay
        # there and would affect the other tests that would otherwise succeed.
        os.unlink(WRITE_ZONE_DB_FILE)

    def test_init(self):
        '''
        Checks initial class attributes
        '''
        self.assertIsNone(self.__runner._zone_class)
        self.assertIsNone(self.__runner._zone_name)
        self.assertIsNone(self.__runner._zone_file)
        self.assertIsNone(self.__runner._datasrc_config)
        self.assertIsNone(self.__runner._datasrc_type)
        self.assertIsNone(self.__runner._load_iteration_limit)
        self.assertEqual('INFO', self.__runner._log_severity)
        self.assertEqual(0, self.__runner._log_debuglevel)

    def test_parse_args(self):
        self.__runner._parse_args()
        self.assertEqual(TEST_ZONE_NAME, self.__runner._zone_name)
        self.assertEqual(NEW_ZONE_TXT_FILE, self.__runner._zone_file)
        self.assertEqual(DATASRC_CONFIG, self.__runner._datasrc_config)
        self.assertEqual('sqlite3', self.__runner._datasrc_type) # default
        self.assertEqual(10000, self.__runner._load_iteration_limit) # default
        self.assertEqual(RRClass.IN(), self.__runner._zone_class) # default
        self.assertEqual('INFO', self.__runner._log_severity) # default
        self.assertEqual(0, self.__runner._log_debuglevel)

    def test_set_loglevel(self):
        runner = LoadZoneRunner(['-d', '1'] + self.__args)
        runner._parse_args()
        self.assertEqual('DEBUG', runner._log_severity)
        self.assertEqual(1, runner._log_debuglevel)

    def test_parse_bad_args(self):
        # -c cannot be omitted (right now)
        self.assertRaises(BadArgument,
                          LoadZoneRunner(['example', 'example.zone']).
                          _parse_args)

        copt = ['-c', '0']      # template for the mandatory -c option

        # There must be exactly 2 non-option arguments: zone name and zone file
        self.assertRaises(BadArgument, LoadZoneRunner(copt)._parse_args)
        self.assertRaises(BadArgument, LoadZoneRunner(copt + ['example']).
                          _parse_args)
        self.assertRaises(BadArgument, LoadZoneRunner(self.__args + ['0']).
                          _parse_args)

        # Bad zone name
        self.assertRaises(BadArgument,
                          LoadZoneRunner(copt + ['bad..name', 'example.zone']).
                          _parse_args)

        # Bad class name
        self.assertRaises(BadArgument,
                          LoadZoneRunner(copt + ['-C', 'badclass']).
                          _parse_args)
        # Unsupported class
        self.assertRaises(BadArgument,
                          LoadZoneRunner(copt + ['-C', 'CH']).
                          _parse_args)

        # bad debug level
        args = copt + ['example.org', 'example.zone'] # otherwise valid args
        self.assertRaises(BadArgument,
                          LoadZoneRunner(['-d', '-10'] + args)._parse_args)

        # bad report interval
        self.assertRaises(BadArgument,
                          LoadZoneRunner(['-i', '-5'] + args)._parse_args)

    def __common_load_setup(self):
        self.__runner._zone_class = RRClass.IN()
        self.__runner._zone_name = TEST_ZONE_NAME
        self.__runner._zone_file = NEW_ZONE_TXT_FILE
        self.__runner._datasrc_type = 'sqlite3'
        self.__runner._datasrc_config = DATASRC_CONFIG
        self.__runner._load_iteration_limit = 1
        self.__reports = []
        self.__runner._report_progress = lambda x: self.__reports.append(x)

    def __check_zone_soa(self, soa_txt, zone_name=TEST_ZONE_NAME):
        """Check that the given SOA RR exists and matches the expected string

        If soa_txt is None, the zone is expected to be non-existent.
        Otherwise, if soa_txt is False, the zone should exist but SOA is
        expected to be missing.

        """

        client = DataSourceClient('sqlite3', DATASRC_CONFIG)
        result, finder = client.find_zone(zone_name)
        if soa_txt is None:
            self.assertEqual(client.NOTFOUND, result)
            return
        self.assertEqual(client.SUCCESS, result)
        result, rrset, _ = finder.find(zone_name, RRType.SOA())
        if soa_txt:
            self.assertEqual(finder.SUCCESS, result)
            self.assertEqual(soa_txt, rrset.to_text())
        else:
            self.assertEqual(finder.NXRRSET, result)

    def test_load_update(self):
        '''successful case to loading new contents to an existing zone.'''
        self.__common_load_setup()
        self.__check_zone_soa(ORIG_SOA_TXT)
        self.__runner._do_load()
        # In this test setup every loaded RR will be reported, and there will
        # be 3 RRs
        self.assertEqual([1, 2, 3], self.__reports)
        self.__check_zone_soa(NEW_SOA_TXT)

    def test_load_update_skipped_report(self):
        '''successful loading, with reports for every 2 RRs'''
        self.__common_load_setup()
        self.__runner._load_iteration_limit = 2
        self.__runner._do_load()
        self.assertEqual([2], self.__reports)

    def test_load_update_no_report(self):
        '''successful loading, without progress reports'''
        self.__common_load_setup()
        self.__runner._load_iteration_limit = 0
        self.__runner._do_load()
        self.assertEqual([], self.__reports) # no report
        self.__check_zone_soa(NEW_SOA_TXT)   # but load is completed

    def test_create_and_load(self):
        '''successful case to loading contents to a new zone (created).'''
        self.__common_load_setup()
        self.__runner._zone_name = Name('example.com')
        self.__runner._zone_file = ALT_NEW_ZONE_TXT_FILE
        self.__check_zone_soa(None, zone_name=Name('example.com'))
        self.__runner._do_load()
        self.__check_zone_soa(ALT_NEW_SOA_TXT, zone_name=Name('example.com'))

    def test_load_fail_badconfig(self):
        '''Load attempt fails due to broken datasrc config.'''
        self.__common_load_setup()
        self.__runner._datasrc_config = "invalid config"
        self.__check_zone_soa(ORIG_SOA_TXT)
        self.assertRaises(LoadFailure, self.__runner._do_load)
        self.__check_zone_soa(ORIG_SOA_TXT) # no change to the zone

    def test_load_fail_badzone(self):
        '''Load attempt fails due to broken zone file.'''
        self.__common_load_setup()
        self.__runner._zone_file = \
            LOCAL_TESTDATA_PATH + '/broken-example.org.zone'
        self.__check_zone_soa(ORIG_SOA_TXT)
        self.assertRaises(LoadFailure, self.__runner._do_load)
        self.__check_zone_soa(ORIG_SOA_TXT)

    def test_load_fail_noloader(self):
        '''Load attempt fails because loading isn't supported'''
        self.__common_load_setup()
        self.__runner._datasrc_type = 'memory'
        self.__runner._datasrc_config = '{"type": "memory"}'
        self.__check_zone_soa(ORIG_SOA_TXT)
        self.assertRaises(LoadFailure, self.__runner._do_load)
        self.__check_zone_soa(ORIG_SOA_TXT)

    def test_load_fail_create_cancel(self):
        '''Load attempt fails and new creation of zone is canceled'''
        self.__common_load_setup()
        self.__runner._zone_name = Name('example.com')
        self.__runner._zone_file = 'no-such-file'
        self.__check_zone_soa(None, zone_name=Name('example.com'))
        self.assertRaises(LoadFailure, self.__runner._do_load)
        # _do_load() should have once created the zone but then canceled it.
        self.__check_zone_soa(None, zone_name=Name('example.com'))

    def __common_post_load_setup(self, zone_file):
        '''Common setup procedure for post load tests.'''
        # replace the LoadZoneRunner's original _post_load_warning() for
        # inspection
        self.__warnings = []
        self.__runner._post_load_warning = \
            lambda msg: self.__warnings.append(msg)

        # perform load and invoke checks
        self.__common_load_setup()
        self.__runner._zone_file = zone_file
        self.__check_zone_soa(ORIG_SOA_TXT)
        self.__runner._do_load()
        self.__runner._post_load_checks()

    def test_load_fail_create_cancel(self):
        '''Load succeeds but warns about missing SOA, should cause warn'''
        self.__common_load_setup()
        self.__common_post_load_setup(LOCAL_TESTDATA_PATH +
                                      '/example-nosoa.org.zone')
        self.__check_zone_soa(False)
        self.assertEqual(1, len(self.__warnings))
        self.assertEqual('zone has no SOA', self.__warnings[0])

    def test_load_fail_create_cancel(self):
        '''Load succeeds but warns about missing NS, should cause warn'''
        self.__common_load_setup()
        self.__common_post_load_setup(LOCAL_TESTDATA_PATH +
                                      '/example-nons.org.zone')
        self.__check_zone_soa(NEW_SOA_TXT)
        self.assertEqual(1, len(self.__warnings))
        self.assertEqual('zone has no NS', self.__warnings[0])

    def test_run_success(self):
        '''Check for the top-level method.

        Detailed behavior is tested in other tests.  We only check the
        return value of run(), and the zone is successfully loaded.

        '''
        self.__check_zone_soa(ORIG_SOA_TXT)
        self.assertEqual(0, self.__runner.run())
        self.__check_zone_soa(NEW_SOA_TXT)

    def test_run_fail(self):
        '''Check for the top-level method, failure case.

        Similar to the success test, but loading will fail, and return
        value should be 1.

        '''
        runner = LoadZoneRunner(['-c', DATASRC_CONFIG, 'example.org',
                                 LOCAL_TESTDATA_PATH +
                                 '/broken-example.org.zone'])
        self.__check_zone_soa(ORIG_SOA_TXT)
        self.assertEqual(1, runner.run())
        self.__check_zone_soa(ORIG_SOA_TXT)

if __name__== "__main__":
    isc.log.resetUnitTestRootLogger()
    # Disable the internal logging setup so the test output won't be too
    # verbose by default.
    LoadZoneRunner._config_log = lambda x: None
    unittest.main()
