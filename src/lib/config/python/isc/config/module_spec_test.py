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
# Tests for the module_spec module
#

import unittest
import os
from isc.config import ModuleSpec, ModuleSpecError
import isc.cc.data

class TestModuleSpec(unittest.TestCase):

    def setUp(self):
        if 'CONFIG_TESTDATA_PATH' in os.environ:
            self.data_path = os.environ['CONFIG_TESTDATA_PATH']
        else:
            self.data_path = "../../../testdata"

    def spec_file(self, filename):
        return(self.data_path + os.sep + filename)

    def read_spec_file(self, filename):
        return isc.config.module_spec_from_file(self.spec_file(filename))

    def spec1(self, dd):
        module_spec = dd.get_full_spec()
        self.assert_('module_name' in module_spec)
        self.assertEqual(module_spec['module_name'], "Spec1")
        
    def test_open_file_name(self):
        dd = self.read_spec_file("spec1.spec")
        self.spec1(dd)

    def test_open_file_obj(self):
        file1 = open(self.spec_file("spec1.spec"))
        dd = isc.config.module_spec_from_file(file1)
        self.spec1(dd)

    def test_bad_specfiles(self):
        self.assertRaises(ModuleSpecError, self.read_spec_file, "spec3.spec")
        self.assertRaises(ModuleSpecError, self.read_spec_file, "spec4.spec")
        self.assertRaises(ModuleSpecError, self.read_spec_file, "spec5.spec")
        self.assertRaises(ModuleSpecError, self.read_spec_file, "spec6.spec")
        self.assertRaises(ModuleSpecError, self.read_spec_file, "spec7.spec")
        self.assertRaises(ModuleSpecError, self.read_spec_file, "spec8.spec")
        self.assertRaises(ModuleSpecError, self.read_spec_file, "spec9.spec")
        self.assertRaises(ModuleSpecError, self.read_spec_file, "spec10.spec")
        self.assertRaises(ModuleSpecError, self.read_spec_file, "spec11.spec")
        self.assertRaises(ModuleSpecError, self.read_spec_file, "spec12.spec")
        self.assertRaises(ModuleSpecError, self.read_spec_file, "spec13.spec")
        self.assertRaises(ModuleSpecError, self.read_spec_file, "spec14.spec")
        self.assertRaises(ModuleSpecError, self.read_spec_file, "spec15.spec")
        self.assertRaises(ModuleSpecError, self.read_spec_file, "spec16.spec")
        self.assertRaises(ModuleSpecError, self.read_spec_file, "spec17.spec")
        self.assertRaises(ModuleSpecError, self.read_spec_file, "spec18.spec")
        self.assertRaises(ModuleSpecError, self.read_spec_file, "spec19.spec")
        self.assertRaises(ModuleSpecError, self.read_spec_file, "spec20.spec")
        self.assertRaises(ModuleSpecError, self.read_spec_file, "spec21.spec")

    def validate_data(self, specfile_name, datafile_name):
        dd = self.read_spec_file(specfile_name);
        data_file = open(self.spec_file(datafile_name))
        data_str = data_file.read()
        data = isc.cc.data.parse_value_str(data_str)
        return dd.validate(True, data)
        
    def test_data_validation(self):
        self.assertEqual(True, self.validate_data("spec22.spec", "data22_1.data"))
        self.assertEqual(False, self.validate_data("spec22.spec", "data22_2.data"))
        self.assertEqual(False, self.validate_data("spec22.spec", "data22_3.data"))
        self.assertEqual(False, self.validate_data("spec22.spec", "data22_4.data"))
        self.assertEqual(False, self.validate_data("spec22.spec", "data22_5.data"))
        self.assertEqual(True, self.validate_data("spec22.spec", "data22_6.data"))
        self.assertEqual(True, self.validate_data("spec22.spec", "data22_7.data"))
        self.assertEqual(False, self.validate_data("spec22.spec", "data22_8.data"))

if __name__ == '__main__':
    unittest.main()
