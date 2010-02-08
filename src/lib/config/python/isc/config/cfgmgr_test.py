# Copyright (C) 2009  Internet Systems Consortium.
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

#
# Tests for the configuration manager module
#

import unittest
import os
from isc.config.cfgmgr import *

class TestConfigManagerData(unittest.TestCase):
    def setUp(self):
        self.data_path = os.environ['CONFIG_TESTDATA_PATH']
        self.config_manager_data = ConfigManagerData(self.data_path)
        self.assert_(self.config_manager_data)

    def test_init(self):
        self.assertEqual(self.config_manager_data.data['version'],
                         ConfigManagerData.CONFIG_VERSION)
        self.assertEqual(self.config_manager_data.data_path,
                         self.data_path)
        self.assertEqual(self.config_manager_data.db_filename,
                         self.data_path + os.sep + "b10-config.db")

    def test_set_data_definition(self):
        pass

    def test_read_from_file(self):
        ConfigManagerData.read_from_file(self.data_path)
        self.assertRaises(ConfigManagerDataEmpty,
                          ConfigManagerData.read_from_file,
                          "doesnotexist")
        self.assertRaises(ConfigManagerDataReadError,
                          ConfigManagerData.read_from_file,
                          self.data_path, "b10-config-bad1.db")
        self.assertRaises(ConfigManagerDataReadError,
                          ConfigManagerData.read_from_file,
                          self.data_path, "b10-config-bad2.db")
        self.assertRaises(ConfigManagerDataReadError,
                          ConfigManagerData.read_from_file,
                          self.data_path, "b10-config-bad3.db")

    def test_write_to_file(self):
        output_file_name = "b10-config-write-test";
        self.config_manager_data.write_to_file(output_file_name)
        new_config = ConfigManagerData(self.data_path, output_file_name)
        self.assertEqual(self.config_manager_data, new_config)


class TestConfigManager:

    def setUp(self):
        pass
    
    def test_init(self):
        pass

    def test_set_config(self):
        pass

    def test_remove_config(self):
        pass

    def test_write_config(self):
        pass

    def test_handle_msg(self):
        pass

    def test_run(self):
        pass


if __name__ == '__main__':
    if not 'CONFIG_TESTDATA_PATH' in os.environ:
        print("You need to set the environment variable CONFIG_TESTDATA_PATH to point to the directory containing the test data files")
        exit(1)
    unittest.main()

