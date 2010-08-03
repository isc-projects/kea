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

# $Id$

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

    def test_open_bad_file_obj(self):
        self.assertRaises(ModuleSpecError, isc.config.module_spec_from_file, 1)
        # contains single quotes which json parser does not accept
        
        self.assertRaises(ModuleSpecError, isc.config.module_spec_from_file, self.spec_file("spec28.spec"), False)
        my_spec_file = open(self.spec_file("spec28.spec"))
        self.assertRaises(ModuleSpecError, isc.config.module_spec_from_file, my_spec_file, False)

        self.assertRaises(ModuleSpecError, isc.config.module_spec_from_file, self.spec_file("does_not_exist"), False)

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
        self.assertRaises(ModuleSpecError, self.read_spec_file, "spec26.spec")

    def validate_data(self, specfile_name, datafile_name):
        dd = self.read_spec_file(specfile_name);
        data_file = open(self.spec_file(datafile_name))
        data_str = data_file.read()
        data = isc.cc.data.parse_value_str(data_str)
        return dd.validate_config(True, data)
        
    def test_data_validation(self):
        self.assertEqual(True, self.validate_data("spec22.spec", "data22_1.data"))
        self.assertEqual(False, self.validate_data("spec22.spec", "data22_2.data"))
        self.assertEqual(False, self.validate_data("spec22.spec", "data22_3.data"))
        self.assertEqual(False, self.validate_data("spec22.spec", "data22_4.data"))
        self.assertEqual(False, self.validate_data("spec22.spec", "data22_5.data"))
        self.assertEqual(True, self.validate_data("spec22.spec", "data22_6.data"))
        self.assertEqual(True, self.validate_data("spec22.spec", "data22_7.data"))
        self.assertEqual(False, self.validate_data("spec22.spec", "data22_8.data"))

    def validate_command_params(self, specfile_name, datafile_name, cmd_name):
        dd = self.read_spec_file(specfile_name);
        data_file = open(self.spec_file(datafile_name))
        data_str = data_file.read()
        params = isc.cc.data.parse_value_str(data_str)
        return dd.validate_command(cmd_name, params)

    def test_command_validation(self):
        self.assertEqual(True, self.validate_command_params("spec27.spec", "data22_1.data", 'cmd1'))
        self.assertEqual(False, self.validate_command_params("spec27.spec", "data22_2.data",'cmd1'))
        self.assertEqual(False, self.validate_command_params("spec27.spec", "data22_3.data", 'cmd1'))
        self.assertEqual(False, self.validate_command_params("spec27.spec", "data22_4.data", 'cmd1'))
        self.assertEqual(False, self.validate_command_params("spec27.spec", "data22_5.data", 'cmd1'))
        self.assertEqual(True, self.validate_command_params("spec27.spec", "data22_6.data", 'cmd1'))
        self.assertEqual(True, self.validate_command_params("spec27.spec", "data22_7.data", 'cmd1'))
        self.assertEqual(False, self.validate_command_params("spec27.spec", "data22_8.data", 'cmd1'))
        self.assertEqual(False, self.validate_command_params("spec27.spec", "data22_8.data", 'cmd2'))

    def test_init(self):
        self.assertRaises(ModuleSpecError, ModuleSpec, 1)
        module_spec = isc.config.module_spec_from_file(self.spec_file("spec1.spec"), False)
        self.spec1(module_spec)

        module_spec = isc.config.module_spec_from_file(self.spec_file("spec25.spec"), True)
        self.assertEqual("Spec25", module_spec.get_module_name())
        self.assertEqual("Just an empty module", module_spec.get_module_description())

    def test_str(self):
        module_spec = isc.config.module_spec_from_file(self.spec_file("spec1.spec"), False)
        self.assertEqual(module_spec.__str__(), "{'module_name': 'Spec1'}")

    def test_check_module_spec(self):
        self.assertRaises(ModuleSpecError, isc.config.module_spec._check, 1)
        
    def test_check_command_spec(self):
        self.assertRaises(ModuleSpecError, isc.config.module_spec._check_command_spec, 1 )
        
        self.assertRaises(ModuleSpecError, isc.config.module_spec._check_command_spec, [ 1 ] )

        self.assertRaises(ModuleSpecError, isc.config.module_spec._check_command_spec,
                          [ { 'command_name': 1,
                              'command_description': 'just for testing',
                              'command_args': [
                                { 'item_name': 'arg1',
                                  'item_type': 'string',
                                  'item_optional': True
                                }
                              ]
                            }
                          ]
                         )

        self.assertRaises(ModuleSpecError, isc.config.module_spec._check_command_spec,
                          [ { 'command_name': 'test_command',
                              'command_description': 1,
                              'command_args': [
                                { 'item_name': 'arg1',
                                  'item_type': 'string',
                                  'item_optional': True
                                }
                              ]
                            }
                          ]
                         )

        self.assertRaises(ModuleSpecError, isc.config.module_spec._check_command_spec,
                          [  { 'command_name': 'test_command',
                              'command_args': [ 1 ]
                            }
                          ]
                         )

    def test_check_item_spec(self):
        self.assertRaises(ModuleSpecError, isc.config.module_spec._check_item_spec, 1 )
        self.assertRaises(ModuleSpecError, isc.config.module_spec._check_item_spec,
                          { 'item_name': 1,
                            'item_type': "string",
                            'item_optional': False,
                            'item_default': "asdf"
                          }
                         )

        self.assertRaises(ModuleSpecError, isc.config.module_spec._check_item_spec,
                          { 'item_name': "an_item",
                            'item_type': "bad_type",
                            'item_optional': False,
                            'item_default': "asdf"
                          }
                         )

        self.assertRaises(ModuleSpecError, isc.config.module_spec._check_item_spec,
                          { 'item_name': "an_item",
                            'item_type': 1,
                            'item_optional': False,
                            'item_default': "asdf"
                          }
                         )

        self.assertRaises(ModuleSpecError, isc.config.module_spec._check_item_spec,
                          { 'item_name': "an_item",
                            'item_type': "string",
                            'item_optional': False,
                          }
                         )

        self.assertRaises(ModuleSpecError, isc.config.module_spec._check_item_spec,
                          { 'item_name': "an_item",
                            'item_type': "string",
                            'item_optional': 1,
                          }
                         )

        self.assertRaises(ModuleSpecError, isc.config.module_spec._check_item_spec,
                          { 'item_name': "an_item",
                            'item_type': "string",
                            'item_optional': False,
                            'item_default': 1
                          }
                         )

        
        self.assertRaises(ModuleSpecError, isc.config.module_spec._check_item_spec,
                          { 'item_name': "an_item",
                            'item_type': "list",
                            'item_optional': False,
                            'item_default': []
                          }
                         )

        self.assertRaises(ModuleSpecError, isc.config.module_spec._check_item_spec,
                          { 'item_name': "an_item",
                            'item_type': "list",
                            'item_optional': False,
                            'item_default': [],
                            'list_item_spec': 1
                          }
                         )

        self.assertRaises(ModuleSpecError, isc.config.module_spec._check_item_spec,
                          { 'item_name': "an_item",
                            'item_type': "map",
                            'item_optional': False,
                            'item_default': {}
                          }
                         )

        self.assertRaises(ModuleSpecError, isc.config.module_spec._check_item_spec,
                          { 'item_name': "an_item",
                            'item_type': "map",
                            'item_optional': False,
                            'item_default': {},
                            'map_item_spec': 1
                          }
                         )

        self.assertRaises(ModuleSpecError, isc.config.module_spec._check_item_spec,
                          { 'item_name': "an_item",
                            'item_type': "map",
                            'item_optional': False,
                            'item_default': {},
                            'map_item_spec': [ 1 ]
                          }
                         )

    def test_validate_type(self):
        errors = []
        self.assertEqual(True, isc.config.module_spec._validate_type({ 'item_type': 'integer' }, 1, errors))
        self.assertEqual(False, isc.config.module_spec._validate_type({ 'item_type': 'integer' }, "a", None))
        self.assertEqual(False, isc.config.module_spec._validate_type({ 'item_type': 'integer' }, "a", errors))
        self.assertEqual(['a should be an integer'], errors)

        errors = []
        self.assertEqual(True, isc.config.module_spec._validate_type({ 'item_type': 'real' }, 1.1, errors))
        self.assertEqual(False, isc.config.module_spec._validate_type({ 'item_type': 'real' }, "a", None))
        self.assertEqual(False, isc.config.module_spec._validate_type({ 'item_type': 'real' }, "a", errors))
        self.assertEqual(['a should be a real'], errors)

        errors = []
        self.assertEqual(True, isc.config.module_spec._validate_type({ 'item_type': 'boolean' }, True, errors))
        self.assertEqual(False, isc.config.module_spec._validate_type({ 'item_type': 'boolean' }, "a", None))
        self.assertEqual(False, isc.config.module_spec._validate_type({ 'item_type': 'boolean' }, "a", errors))
        self.assertEqual(['a should be a boolean'], errors)

        errors = []
        self.assertEqual(True, isc.config.module_spec._validate_type({ 'item_type': 'string' }, "a", errors))
        self.assertEqual(False, isc.config.module_spec._validate_type({ 'item_type': 'string' }, 1, None))
        self.assertEqual(False, isc.config.module_spec._validate_type({ 'item_type': 'string' }, 1, errors))
        self.assertEqual(['1 should be a string'], errors)

        errors = []
        self.assertEqual(True, isc.config.module_spec._validate_type({ 'item_type': 'list' }, [ 1, 1], errors))
        self.assertEqual(False, isc.config.module_spec._validate_type({ 'item_type': 'list' }, 1, None))
        self.assertEqual(False, isc.config.module_spec._validate_type({ 'item_type': 'list' }, 1, errors))
        self.assertEqual(['1 should be a list'], errors)

        errors = []
        self.assertEqual(True, isc.config.module_spec._validate_type({ 'item_type': 'map' }, {"a": 1}, errors))
        self.assertEqual(False, isc.config.module_spec._validate_type({ 'item_type': 'map' }, 1, None))
        self.assertEqual(False, isc.config.module_spec._validate_type({ 'item_type': 'map' }, 1, errors))
        self.assertEqual(['1 should be a map'], errors)

    def test_validate_spec(self):
        spec = { 'item_name': "an_item",
                 'item_type': "string",
                 'item_optional': False,
                 'item_default': "asdf"
               }
        errors = []
        self.assertEqual(False, isc.config.module_spec._validate_spec(spec, True, {}, None))
        self.assertEqual(False, isc.config.module_spec._validate_spec(spec, True, {}, errors))
        self.assertEqual(['non-optional item an_item missing'], errors)
        


if __name__ == '__main__':
    unittest.main()
