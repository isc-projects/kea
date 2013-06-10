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

    def start(self):
        pass

class MockMemmgr(memmgr.Memmgr):
    def _setup_ccsession(self):
        orig_cls = isc.config.ModuleCCSession
        isc.config.ModuleCCSession = MyCCSession
        try:
            super()._setup_ccsession()
        except Exception:
            raise
        finally:
            isc.config.ModuleCCSession = orig_cls

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
        # Restore faked values
        os.access = self.__orig_os_access
        os.path.isdir = self.__orig_isdir

        # If at test created a mapped-files directory, delete it.
        if os.path.isdir(self.__test_mapped_file_dir):
            os.rmdir(self.__test_mapped_file_dir)

    def test_init(self):
        self.assertIsNone(self.__mgr._mapped_file_dir)

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
                         self.__mgr._mapped_file_dir.split('/')[-1])

        # Update the configuration.
        user_cfg = {'mapped_file_dir': '/some/path/dir'}
        self.assertEqual((0, None),
                         parse_answer(self.__mgr._config_handler(user_cfg)))
        self.assertEqual('/some/path/dir', self.__mgr._mapped_file_dir)

        # Bad update: diretory doesn't exist (we assume it really doesn't
        # exist in the tested environment).  Update won't be made.
        os.path.isdir = self.__orig_isdir # use real library
        user_cfg = {'mapped_file_dir': '/another/path/dir'}
        answer = parse_answer(self.__mgr._config_handler(user_cfg))
        self.assertEqual(1, answer[0])
        self.assertIsNotNone(re.search('not a directory', answer[1]))

        # Bad update: directory exists but is not readable.
        os.mkdir(self.__test_mapped_file_dir, 0o500) # drop writable bit
        os.access = self.__orig_os_access
        user_cfg = {'mapped_file_dir': self.__test_mapped_file_dir}
        answer = parse_answer(self.__mgr._config_handler(user_cfg))
        self.assertEqual(1, answer[0])
        self.assertIsNotNone(re.search('not writable', answer[1]))

if __name__== "__main__":
    isc.log.resetUnitTestRootLogger()
    unittest.main()
