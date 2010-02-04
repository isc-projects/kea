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
# Tests for the datadefinition module
#

import unittest
import os
from isc.config import DataDefinition


class TestDataDefinition(unittest.TestCase):

    def setUp(self):
        self.assert_('CONFIG_TESTDATA_PATH' in os.environ)
        self.data_path = os.environ['CONFIG_TESTDATA_PATH']

    def spec_file(self, filename):
        return(self.data_path + os.sep + filename)

    def spec1(self, dd):
        data_def = dd.get_definition()
        self.assert_('data_specification' in data_def)
        data_spec = data_def['data_specification']
        self.assert_('module_name' in data_spec)
        self.assertEqual(data_spec['module_name'], "Spec1")
        
    def test_open_file_name(self):
        dd = DataDefinition(self.spec_file("spec1.spec"))
        self.spec1(dd)

    def test_open_file_obj(self):
        file1 = open(self.spec_file("spec1.spec"))
        dd = DataDefinition(file1)
        self.spec1(dd)

    def test_bad_specfiles(self):
        self.assertRaises(DataDefinition(self.spec_file("spec3.spec")))

if __name__ == '__main__':
    unittest.main()
