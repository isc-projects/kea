# Copyright (C) 2013  Internet Systems Consortium.
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
import re

import isc.log
from isc.dns import RRClass
import isc.config
from isc.config import parse_answer
import memmgr
from isc.testutils.ccsession_mock import MockModuleCCSession

class MyCCSession(MockModuleCCSession, isc.config.ConfigData):
    def __init__(self, specfile, config_handler, command_handler):
        super().__init__()
        specfile = os.environ['B10_FROM_BUILD'] + '/src/bin/memmgr/memmgr.spec'
        module_spec = isc.config.module_spec_from_file(specfile)
        isc.config.ConfigData.__init__(self, module_spec)
        self.add_remote_params = [] # for inspection
        self.add_remote_exception = None # to raise exception from the method

    def start(self):
        pass

    def add_remote_config_by_name(self, mod_name, handler):
        if self.add_remote_exception is not None:
            raise self.add_remote_exception
        self.add_remote_params.append((mod_name, handler))

class MockMemmgr(memmgr.Memmgr):
    def _setup_ccsession(self):
        orig_cls = isc.config.ModuleCCSession
        isc.config.ModuleCCSession = MyCCSession
        try:
            super()._setup_ccsession()
        finally:
            isc.config.ModuleCCSession = orig_cls

# Defined for easier tests with DataSrcClientsMgr.reconfigure(), which
# only needs get_value() method
class MockConfigData:
    def __init__(self, data):
        self.__data = data

    def get_value(self, identifier):
        return self.__data[identifier], False

class TestMemmgr(unittest.TestCase):
    def setUp(self):
        # Some tests use this directory.  Make sure it doesn't pre-exist.
        self.__test_mapped_file_dir = \
            os.environ['B10_FROM_BUILD'] + \
            '/src/bin/memmgr/tests/test_mapped_files'
        if os.path.isdir(self.__test_mapped_file_dir):
            os.rmdir(self.__test_mapped_file_dir)

        self.__mgr = MockMemmgr()
        # Fake some 'os' module functions for easier tests
        self.__orig_os_access = os.access
        self.__orig_isdir = os.path.isdir

    def tearDown(self):
        # Not all unittests cause this method to be called, so we call
        # it explicitly as it may be necessary in some cases where the
        # builder thread has been created.
        self.__mgr._shutdown_module()

        # Assert that all commands sent to the builder thread were
        # handled.
        self.assertEqual(len(self.__mgr._builder_command_queue), 0)

        # Restore faked values
        os.access = self.__orig_os_access
        os.path.isdir = self.__orig_isdir

        # If at test created a mapped-files directory, delete it.
        if os.path.isdir(self.__test_mapped_file_dir):
            os.rmdir(self.__test_mapped_file_dir)

    def test_init(self):
        """Check some initial conditions"""
        self.assertIsNone(self.__mgr._config_params)
        self.assertEqual([], self.__mgr._datasrc_info_list)

        # Try to configure a data source clients with the manager.  This
        # should confirm the manager object is instantiated enabling in-memory
        # cache.
        cfg_data = MockConfigData(
            {"classes": {"IN": [{"type": "MasterFiles",
                                 "cache-enable": True, "params": {}}]}})
        self.__mgr._datasrc_clients_mgr.reconfigure({}, cfg_data)
        clist = \
            self.__mgr._datasrc_clients_mgr.get_client_list(RRClass.IN)
        self.assertEqual(1, len(clist.get_status()))

    def test_configure(self):
        self.__mgr._setup_ccsession()

        # Pretend specified directories exist and writable
        os.path.isdir = lambda x: True
        os.access = lambda x, y: True

        # At the initial configuration, if mapped_file_dir isn't specified,
        # the default value will be set.
        self.assertEqual((0, None),
                         parse_answer(self.__mgr._config_handler({})))
        self.assertEqual('mapped_files',
                         self.__mgr._config_params['mapped_file_dir'].
                         split('/')[-1])

        # Update the configuration.
        user_cfg = {'mapped_file_dir': '/some/path/dir'}
        self.assertEqual((0, None),
                         parse_answer(self.__mgr._config_handler(user_cfg)))
        self.assertEqual('/some/path/dir',
                         self.__mgr._config_params['mapped_file_dir'])

        # Bad update: diretory doesn't exist (we assume it really doesn't
        # exist in the tested environment).  Update won't be made.
        os.path.isdir = self.__orig_isdir # use real library
        user_cfg = {'mapped_file_dir': '/another/path/dir'}
        answer = parse_answer(self.__mgr._config_handler(user_cfg))
        self.assertEqual(1, answer[0])
        self.assertIsNotNone(re.search('not a directory', answer[1]))

    @unittest.skipIf(os.getuid() == 0,
                     'test cannot be run as root user')
    def test_configure_bad_permissions(self):
        self.__mgr._setup_ccsession()

        # Pretend specified directories exist and writable
        os.path.isdir = lambda x: True
        os.access = lambda x, y: True

        # Initial configuration.
        self.assertEqual((0, None),
                         parse_answer(self.__mgr._config_handler({})))

        os.path.isdir = self.__orig_isdir
        os.access = self.__orig_os_access

        # Bad update: directory exists but is not writable.
        os.mkdir(self.__test_mapped_file_dir, 0o500) # drop writable bit
        user_cfg = {'mapped_file_dir': self.__test_mapped_file_dir}
        answer = parse_answer(self.__mgr._config_handler(user_cfg))
        self.assertEqual(1, answer[0])
        self.assertIsNotNone(re.search('not writable', answer[1]))

    def test_setup_module(self):
        # _setup_module should add data_sources remote module with
        # expected parameters.
        self.__mgr._setup_ccsession()
        self.assertEqual([], self.__mgr.mod_ccsession.add_remote_params)
        self.__mgr._setup_module()
        self.assertEqual([('data_sources',
                           self.__mgr._datasrc_config_handler)],
                         self.__mgr.mod_ccsession.add_remote_params)

        # If data source isn't configured it's considered fatal (checking the
        # same scenario with two possible exception types)
        self.__mgr.mod_ccsession.add_remote_exception = \
            isc.config.ModuleCCSessionError('faked exception')
        self.assertRaises(isc.server_common.bind10_server.BIND10ServerFatal,
                          self.__mgr._setup_module)

        self.__mgr.mod_ccsession.add_remote_exception = \
            isc.config.ModuleSpecError('faked exception')
        self.assertRaises(isc.server_common.bind10_server.BIND10ServerFatal,
                          self.__mgr._setup_module)

    def test_datasrc_config_handler(self):
        self.__mgr._config_params = {'mapped_file_dir': '/some/path'}

        # A simple (boring) case with real class implementations.  This
        # confirms the methods are called as expected.
        cfg_data = MockConfigData(
            {"classes": {"IN": [{"type": "MasterFiles",
                                 "cache-enable": True, "params": {}}]}})
        self.__init_called = None
        def mock_init_segments(param):
            self.__init_called = param
        self.__mgr._init_segments = mock_init_segments
        self.__mgr._datasrc_config_handler({}, cfg_data)
        self.assertEqual(1, len(self.__mgr._datasrc_info_list))
        self.assertEqual(1, self.__mgr._datasrc_info_list[0].gen_id)
        self.assertEqual(self.__init_called, self.__mgr._datasrc_info_list[0])

        # Below we're using a mock DataSrcClientMgr for easier tests
        class MockDataSrcClientMgr:
            def __init__(self, status_list, raise_on_reconfig=False):
                self.__status_list = status_list
                self.__raise_on_reconfig = raise_on_reconfig

            def reconfigure(self, new_config, config_data):
                if self.__raise_on_reconfig:
                    raise isc.server_common.datasrc_clients_mgr.ConfigError(
                        'test error')
                # otherwise do nothing

            def get_clients_map(self):
                return 42, {RRClass.IN: self}

            def get_status(self): # mocking get_clients_map()[1].get_status()
                return self.__status_list

        # This confirms memmgr's config is passed and handled correctly.
        # From memmgr's point of view it should be enough we have an object
        # in segment_info_map.  Note also that the new DataSrcInfo is appended
        # to the list
        self.__mgr._datasrc_clients_mgr = \
            MockDataSrcClientMgr([('sqlite3', 'mapped', None)])
        self.__mgr._datasrc_config_handler(None, None) # params don't matter
        self.assertEqual(2, len(self.__mgr._datasrc_info_list))
        self.assertEqual(self.__init_called, self.__mgr._datasrc_info_list[1])
        self.assertIsNotNone(
            self.__mgr._datasrc_info_list[1].segment_info_map[
                (RRClass.IN, 'sqlite3')])

        # Emulate the case reconfigure() fails.  Exception isn't propagated,
        # but the list doesn't change.
        self.__mgr._datasrc_clients_mgr = MockDataSrcClientMgr(None, True)
        self.__mgr._datasrc_config_handler(None, None)
        self.assertEqual(2, len(self.__mgr._datasrc_info_list))

if __name__== "__main__":
    isc.log.resetUnitTestRootLogger()
    unittest.main()
