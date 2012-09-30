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

#
# Tests for the ConfigData and MultiConfigData classes
#

import unittest
import os
from isc.config.config_data import *
from isc.config.module_spec import *

class TestConfigData(unittest.TestCase):
    def setUp(self):
        if 'CONFIG_TESTDATA_PATH' in os.environ:
            self.data_path = os.environ['CONFIG_TESTDATA_PATH']
        else:
            self.data_path = "../../../testdata"
        spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec2.spec")
        self.cd = ConfigData(spec)

    #def test_module_spec_from_file(self):
    #    spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec1.spec")
    #    cd = ConfigData(spec)
    #    self.assertEqual(cd.specification, spec)
    #    self.assertEqual(cd.data, {})
    #    self.assertRaises(ConfigDataError, ConfigData, 1)

    def test_check_type(self):
        config_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec22.spec").get_config_spec()
        spec_part = find_spec_part(config_spec, "value1")
        check_type(spec_part, 1)
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, 1.1)
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, True)
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, "a")
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, [ 1, 2 ])
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, { "a": 1 })

        spec_part = find_spec_part(config_spec, "value2")
        check_type(spec_part, 1.1)
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, 1)
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, True)
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, "a")
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, [ 1, 2 ])
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, { "a": 1 })

        spec_part = find_spec_part(config_spec, "value3")
        check_type(spec_part, True)
        check_type(spec_part, False)
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, 1)
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, 1.1)
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, "a")
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, [ 1, 2 ])
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, { "a": 1 })

        spec_part = find_spec_part(config_spec, "value4")
        check_type(spec_part, "asdf")
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, 1)
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, 1.1)
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, True)
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, [ 1, 2 ])
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, { "a": 1 })

        spec_part = find_spec_part(config_spec, "value5")
        check_type(spec_part, [1, 2])
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, 1)
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, 1.1)
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, True)
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, "a")
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, [ "a", "b" ])
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, { "a": 1 })

        spec_part = find_spec_part(config_spec, "value6")
        check_type(spec_part, { "value1": "aaa", "value2": 2 })
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, 1)
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, 1.1)
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, True)
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, "a")
        self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, [ 1, 2 ])
        #self.assertRaises(isc.cc.data.DataTypeError, check_type, spec_part, { "value1": 1 })

        self.assertRaises(isc.cc.data.DataTypeError, check_type, config_spec, 1)

    def test_convert_type(self):
        config_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec22.spec").get_config_spec()
        spec_part = find_spec_part(config_spec, "value1")
        self.assertEqual(1, convert_type(spec_part, '1'))
        self.assertEqual(2, convert_type(spec_part, 2.1))
        self.assertEqual(2, convert_type(spec_part, '2'))
        self.assertEqual(3, convert_type(spec_part, '3'))
        self.assertEqual(1, convert_type(spec_part, True))

        self.assertRaises(isc.cc.data.DataTypeError, convert_type, spec_part, "a")
        self.assertRaises(isc.cc.data.DataTypeError, convert_type, spec_part, [ 1, 2 ])
        self.assertRaises(isc.cc.data.DataTypeError, convert_type, spec_part, { "a": 1 })
        self.assertRaises(isc.cc.data.DataTypeError, convert_type, 1, "a")
        self.assertRaises(isc.cc.data.DataTypeError, convert_type, { 'somedict': 'somevalue' }, "a")

        spec_part = find_spec_part(config_spec, "value2")
        self.assertEqual(1.1, convert_type(spec_part, '1.1'))
        self.assertEqual(123.0, convert_type(spec_part, '123'))
        self.assertEqual(1.0, convert_type(spec_part, True))
        self.assertRaises(isc.cc.data.DataTypeError, convert_type, spec_part, "a")
        self.assertRaises(isc.cc.data.DataTypeError, convert_type, spec_part, [ 1, 2 ])
        self.assertRaises(isc.cc.data.DataTypeError, convert_type, spec_part, { "a": 1 })

        spec_part = find_spec_part(config_spec, "value3")
        self.assertEqual(True, convert_type(spec_part, 'True'))
        self.assertEqual(False, convert_type(spec_part, 'False'))
        self.assertEqual(True, convert_type(spec_part, 1))
        self.assertEqual(True, convert_type(spec_part, 1.1))
        self.assertEqual(True, convert_type(spec_part, 'a'))
        self.assertEqual(True, convert_type(spec_part, [1, 2]))
        self.assertEqual(True, convert_type(spec_part, {'a' : 1}))

        spec_part = find_spec_part(config_spec, "value4")
        self.assertEqual('asdf', convert_type(spec_part, "asdf"))
        self.assertEqual('1', convert_type(spec_part, 1))
        self.assertEqual('1.1', convert_type(spec_part, 1.1))
        self.assertEqual('True', convert_type(spec_part, True))

        spec_part = find_spec_part(config_spec, "value5")
        self.assertEqual([1, 2], convert_type(spec_part, '1, 2'))
        self.assertEqual([1, 2, 3], convert_type(spec_part, '1 2  3'))
        self.assertEqual([1, 2, 3,4], convert_type(spec_part, '1 2  3, 4'))
        self.assertEqual([1], convert_type(spec_part, [1,]))
        self.assertEqual([1,2], convert_type(spec_part, [1,2]))
        self.assertEqual([1,2], convert_type(spec_part, ['1', '2']))

        self.assertRaises(isc.cc.data.DataTypeError, convert_type, spec_part, 1.1)
        self.assertRaises(isc.cc.data.DataTypeError, convert_type, spec_part, True)
        self.assertRaises(isc.cc.data.DataTypeError, convert_type, spec_part, "a")
        self.assertRaises(isc.cc.data.DataTypeError, convert_type, spec_part, [ "a", "b" ])
        self.assertRaises(isc.cc.data.DataTypeError, convert_type, spec_part, [ "1", "b" ])
        self.assertRaises(isc.cc.data.DataTypeError, convert_type, spec_part, { "a": 1 })

        spec_part = find_spec_part(config_spec, "value6")
        self.assertEqual({}, convert_type(spec_part, '{}'))
        self.assertEqual({ 'v61': 'a' }, convert_type(spec_part, '{ \'v61\': \'a\' }'))

        self.assertRaises(isc.cc.data.DataTypeError, convert_type, spec_part, 1.1)
        self.assertRaises(isc.cc.data.DataTypeError, convert_type, spec_part, True)
        self.assertRaises(isc.cc.data.DataTypeError, convert_type, spec_part, "a")
        self.assertRaises(isc.cc.data.DataTypeError, convert_type, spec_part, "1")
        self.assertRaises(isc.cc.data.DataTypeError, convert_type, spec_part, [ "a", "b" ])
        self.assertRaises(isc.cc.data.DataTypeError, convert_type, spec_part, [ "1", "b" ])
        self.assertRaises(isc.cc.data.DataTypeError, convert_type, spec_part, { "a": 1 })
        self.assertRaises(isc.cc.data.DataTypeError, convert_type, spec_part, "\"{ \"a\": 1 }\"")

        spec_part = find_spec_part(config_spec, "value7")
        self.assertEqual(['1', '2'], convert_type(spec_part, '1, 2'))
        self.assertEqual(['1', '2', '3'], convert_type(spec_part, '1 2  3'))
        self.assertEqual(['1', '2', '3','4'], convert_type(spec_part, '1 2  3, 4'))
        self.assertEqual([1], convert_type(spec_part, [1,]))
        self.assertEqual([1,2], convert_type(spec_part, [1,2]))
        self.assertEqual(['1','2'], convert_type(spec_part, ['1', '2']))

        self.assertRaises(isc.cc.data.DataTypeError, convert_type, spec_part, 1.1)
        self.assertRaises(isc.cc.data.DataTypeError, convert_type, spec_part, True)
        self.assertEqual(['a'], convert_type(spec_part, "a"))
        self.assertEqual(['a', 'b'], convert_type(spec_part, ["a", "b" ]))
        self.assertEqual([1, 'b'], convert_type(spec_part, [1, "b" ]))

    def test_find_spec_part(self):
        config_spec = self.cd.get_module_spec().get_config_spec()
        spec_part = find_spec_part(config_spec, "item1")
        self.assertEqual({'item_name': 'item1', 'item_type': 'integer', 'item_optional': False, 'item_default': 1, }, spec_part)
        spec_part = find_spec_part(config_spec, "/item1")
        self.assertEqual({'item_name': 'item1', 'item_type': 'integer', 'item_optional': False, 'item_default': 1, }, spec_part)
        self.assertRaises(isc.cc.data.DataNotFoundError, find_spec_part, config_spec, "no_such_item")
        self.assertRaises(isc.cc.data.DataNotFoundError, find_spec_part, config_spec, "no_such_item/multilevel")
        self.assertRaises(isc.cc.data.DataNotFoundError, find_spec_part, config_spec, "item6/multilevel")
        self.assertRaises(isc.cc.data.DataNotFoundError, find_spec_part, 1, "item6/multilevel")
        spec_part = find_spec_part(config_spec, "item6/value1")
        self.assertEqual({'item_name': 'value1', 'item_type': 'string', 'item_optional': True, 'item_default': 'default'}, spec_part)

        # make sure the returned data is a copy
        spec_part['item_default'] = 'foo'
        self.assertNotEqual(spec_part, find_spec_part(config_spec, "item6/value1"))

    def test_find_spec_part_lists(self):
        # A few specific tests for list data
        module_spec = isc.config.module_spec_from_file(self.data_path +
                                                       os.sep +
                                                       "spec31.spec")
        config_spec = module_spec.get_config_spec()

        expected_spec_part = {'item_name': 'number',
                              'item_type': 'integer',
                              'item_default': 1,
                              'item_optional': False}

        # First a check for a correct fetch
        spec_part = find_spec_part(config_spec,
                                   "/first_list_items[0]/second_list_items[1]/"
                                   "map_element/list1[1]/list2[1]")
        self.assertEqual(expected_spec_part, spec_part)

        # Leaving out an index should fail by default
        self.assertRaises(isc.cc.data.DataNotFoundError,
                          find_spec_part, config_spec,
                          "/first_list_items[0]/second_list_items/"
                          "map_element/list1[1]/list2[1]")

        # But not for the last element
        spec_part = find_spec_part(config_spec,
                                   "/first_list_items[0]/second_list_items[1]/"
                                   "map_element/list1[1]/list2")
        self.assertEqual(expected_spec_part, spec_part)

        # And also not if strict_identifier is false (third argument)
        spec_part = find_spec_part(config_spec,
                                   "/first_list_items[0]/second_list_items/"
                                   "map_element/list1[1]/list2[1]", False)
        self.assertEqual(expected_spec_part, spec_part)


    def test_spec_name_list(self):
        name_list = spec_name_list(self.cd.get_module_spec().get_config_spec())
        self.assertEqual(['item1', 'item2', 'item3', 'item4', 'item5', 'item6'], name_list)
        name_list = spec_name_list(self.cd.get_module_spec().get_config_spec(), "", True)
        self.assertEqual(['item1', 'item2', 'item3', 'item4', 'item5', 'item6/value1', 'item6/value2'], name_list)
        spec_part = find_spec_part(self.cd.get_module_spec().get_config_spec(), "item6")
        name_list = spec_name_list(spec_part, "item6", True)
        self.assertEqual(['item6/value1', 'item6/value2'], name_list)
        spec_part = find_spec_part(self.cd.get_module_spec().get_config_spec(), "item6")
        name_list = spec_name_list(spec_part, "item6", True)
        self.assertEqual(['item6/value1', 'item6/value2'], name_list)

        config_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec22.spec").get_config_spec()
        spec_part = find_spec_part(config_spec, "value9")
        name_list = spec_name_list(spec_part, "value9", True)
        self.assertEqual(['value9/v91', 'value9/v92/v92a', 'value9/v92/v92b'], name_list)

        name_list = spec_name_list({ "myModule": config_spec }, "", False)
        self.assertEqual(['myModule/'], name_list)
        name_list = spec_name_list({ "myModule": config_spec }, "", True)
        self.assertEqual(['myModule/', 'myModule/value1', 'myModule/value2', 'myModule/value3', 'myModule/value4', 'myModule/value5', 'myModule/value6/v61', 'myModule/value6/v62', 'myModule/value7', 'myModule/value8', 'myModule/value9/v91', 'myModule/value9/v92/v92a', 'myModule/value9/v92/v92b'], name_list)

        self.assertRaises(ConfigDataError, spec_name_list, 1)
        self.assertRaises(ConfigDataError, spec_name_list, [ 'a' ])

        # Test one with type any as well
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec40.spec")
        spec_part = module_spec.get_config_spec()
        name_list = spec_name_list(module_spec.get_config_spec())
        self.assertEqual(['item1', 'item2', 'item3'], name_list)

        # item3 itself is 'empty'
        spec_part = find_spec_part(spec_part, 'item3')
        name_list = spec_name_list(spec_part)
        self.assertEqual([], name_list)


    def test_init(self):
        self.assertRaises(ConfigDataError, ConfigData, "asdf")

    def test_get_value(self):
        value, default = self.cd.get_value("item1")
        self.assertEqual(1, value)
        self.assertEqual(True, default)
        value, default = self.cd.get_value("item2")
        self.assertEqual(1.1, value)
        self.assertEqual(True, default)
        value, default = self.cd.get_value("item3")
        self.assertEqual(True, value)
        self.assertEqual(True, default)
        value, default = self.cd.get_value("item4")
        self.assertEqual("test", value)
        self.assertEqual(True, default)
        value, default = self.cd.get_value("item5")
        self.assertEqual(["a", "b"], value)
        self.assertEqual(True, default)
        value, default = self.cd.get_value("item6")
        self.assertEqual({}, value)
        self.assertEqual(True, default)
        self.assertRaises(isc.cc.data.DataNotFoundError, self.cd.get_value, "no_such_item")
        value, default = self.cd.get_value("item6/value2")
        self.assertEqual(None, value)
        self.assertEqual(False, default)
        self.assertRaises(isc.cc.data.DataNotFoundError, self.cd.get_value, "item6/no_such_item")

    def test_get_default_value(self):
        self.assertEqual(1, self.cd.get_default_value("item1"))
        self.assertEqual('default', self.cd.get_default_value("item6/value1"))
        self.assertEqual(None, self.cd.get_default_value("item6/value2"))

        # set some local values to something else, and see if we
        # still get the default
        self.cd.set_local_config({"item1": 2, "item6": { "value1": "asdf" } })

        self.assertEqual((2, False), self.cd.get_value("item1"))
        self.assertEqual(1, self.cd.get_default_value("item1"))
        self.assertEqual(('asdf', False), self.cd.get_value("item6/value1"))
        self.assertEqual('default', self.cd.get_default_value("item6/value1"))

        self.assertRaises(isc.cc.data.DataNotFoundError,
                          self.cd.get_default_value,
                          "does_not_exist/value1")
        self.assertRaises(isc.cc.data.DataNotFoundError,
                          self.cd.get_default_value,
                          "item6/doesnotexist")

    def test_set_local_config(self):
        self.cd.set_local_config({"item1": 2})
        value, default = self.cd.get_value("item1")
        self.assertEqual(2, value)
        self.assertEqual(False, default)

    def test_get_local_config(self):
        local_config = self.cd.get_local_config()
        self.assertEqual({}, local_config)
        my_config = { "item1": 2, "item2": 2.2, "item3": False, "item4": "asdf", "item5": [ "c", "d" ] }
        self.cd.set_local_config(my_config)
        self.assertEqual(my_config, self.cd.get_local_config())

    def test_get_item_list(self):
        name_list = self.cd.get_item_list()
        self.assertEqual(['item1', 'item2', 'item3', 'item4', 'item5', 'item6'], name_list)
        name_list = self.cd.get_item_list("", True)
        self.assertEqual(['item1', 'item2', 'item3', 'item4', 'item5', 'item6/value1', 'item6/value2'], name_list)
        name_list = self.cd.get_item_list("item6", False)
        self.assertEqual(['item6/value1', 'item6/value2'], name_list)

    def test_get_full_config(self):
        full_config = self.cd.get_full_config()
        self.assertEqual({ "item1": 1, "item2": 1.1, "item3": True, "item4": "test", "item5": ['a', 'b'], "item6/value1": 'default', 'item6/value2': None}, full_config)
        my_config = { "item1": 2, "item2": 2.2, "item3": False, "item4": "asdf", "item5": [ "c", "d" ] }
        self.cd.set_local_config(my_config)
        full_config = self.cd.get_full_config()
        self.assertEqual({ "item1": 2, "item2": 2.2, "item3": False, "item4": "asdf", "item5": [ "c", "d" ], "item6/value1": 'default', 'item6/value2': None}, full_config)

class TestMultiConfigData(unittest.TestCase):
    def setUp(self):
        if 'CONFIG_TESTDATA_PATH' in os.environ:
            self.data_path = os.environ['CONFIG_TESTDATA_PATH']
        else:
            self.data_path = "../../../testdata"
        self.mcd = MultiConfigData()

    def test_init(self):
        self.assertEqual({}, self.mcd._specifications)
        self.assertEqual({}, self.mcd._current_config)
        self.assertEqual({}, self.mcd._local_changes)

    def test_set_remove_specification(self):
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec1.spec")
        self.assertFalse(self.mcd.have_specification(module_spec.get_module_name()))
        self.mcd.set_specification(module_spec)
        self.assertTrue(self.mcd.have_specification(module_spec.get_module_name()))
        self.assert_(module_spec.get_module_name() in self.mcd._specifications)
        self.assertEquals(module_spec, self.mcd._specifications[module_spec.get_module_name()])
        self.assertRaises(ConfigDataError, self.mcd.set_specification, "asdf")
        self.mcd.remove_specification(module_spec.get_module_name())
        self.assertFalse(self.mcd.have_specification(module_spec.get_module_name()))

    def test_clear_specifications(self):
        self.assertEqual(0, len(self.mcd._specifications))
        module_spec = isc.config.module_spec_from_file(self.data_path +
                                                       os.sep +
                                                       "spec1.spec")
        self.mcd.set_specification(module_spec)
        self.assertEqual(1, len(self.mcd._specifications))
        self.mcd.clear_specifications()
        self.assertEqual(0, len(self.mcd._specifications))

    def test_get_module_spec(self):
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec1.spec")
        self.mcd.set_specification(module_spec)
        module_spec2 = self.mcd.get_module_spec(module_spec.get_module_name())
        self.assertEqual(module_spec, module_spec2)
        module_spec3 = self.mcd.get_module_spec("no_such_module")
        self.assertEqual(None, module_spec3)

    def test_find_spec_part(self):
        spec_part = self.mcd.find_spec_part("Spec2/item1")
        self.assertEqual(None, spec_part)
        spec_part = self.mcd.find_spec_part("/Spec2/item1")
        self.assertEqual(None, spec_part)
        module_spec = isc.config.module_spec_from_file(self.data_path +
                                                       os.sep + "spec2.spec")
        self.mcd.set_specification(module_spec)
        spec_part = self.mcd.find_spec_part("Spec2/item1")
        self.assertEqual({'item_name': 'item1', 'item_type': 'integer',
                          'item_optional': False, 'item_default': 1, },
                         spec_part)

        # For lists, either the spec of the list itself, or the
        # spec for the list contents should be returned (the
        # latter when an index is given in the identifier)
        spec_part = self.mcd.find_spec_part("Spec2/item5")
        self.assertEqual({'item_default': ['a', 'b'],
                          'item_name': 'item5',
                          'item_optional': False,
                          'item_type': 'list',
                          'list_item_spec': {'item_default': '',
                                             'item_name': 'list_element',
                                             'item_optional': False,
                                             'item_type': 'string'}},
                         spec_part)
        spec_part = self.mcd.find_spec_part("Spec2/item5[0]")
        self.assertEqual({'item_default': '',
                          'item_name': 'list_element',
                          'item_optional': False,
                          'item_type': 'string'},
                         spec_part)


    def test_find_spec_part_nested(self):
        # Check that find_spec_part works for nested lists
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec30.spec")
        self.mcd.set_specification(module_spec)
        spec_part = self.mcd.find_spec_part("/lists/first_list_items[0]/second_list_items[1]/final_element")
        self.assertEqual({'item_name': 'final_element', 'item_type': 'string', 'item_default': 'hello', 'item_optional': False}, spec_part)
        spec_part = self.mcd.find_spec_part("/BAD_NAME/first_list_items[0]/second_list_items[1]/final_element")
        self.assertEqual(None, spec_part)

    def test_find_spec_part_nested2(self):
        # Check that find_spec_part works for nested lists and maps
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec31.spec")
        self.mcd.set_specification(module_spec)
        spec_part = self.mcd.find_spec_part("/lists/first_list_items[0]/second_list_items[1]/map_element/list1[1]/list2[2]")
        self.assertEqual({"item_name": "number", "item_type": "integer", "item_optional": False, "item_default": 1}, spec_part)

        spec_part = self.mcd.find_spec_part("/DOESNOTEXIST")
        self.assertEqual(None, spec_part)
        spec_part = self.mcd.find_spec_part("/lists/DOESNOTEXIST")
        self.assertEqual(None, spec_part)
        spec_part = self.mcd.find_spec_part("/lists/first_list_items[0]/DOESNOTEXIST")
        self.assertEqual(None, spec_part)
        spec_part = self.mcd.find_spec_part("/lists/first_list_items[0]/second_list_items[1]/DOESNOTEXIST")
        self.assertEqual(None, spec_part)
        spec_part = self.mcd.find_spec_part("/lists/first_list_items[0]/second_list_items[1]/map_element/DOESNOTEXIST")
        self.assertEqual(None, spec_part)
        spec_part = self.mcd.find_spec_part("/lists/first_list_items[0]/second_list_items[1]/map_element/list1[1]/DOESNOTEXIST")
        self.assertEqual(None, spec_part)
        spec_part = self.mcd.find_spec_part("/lists/first_list_items[0]/second_list_items[1]/map_element/list1[1]/list2[1]/DOESNOTEXIST")
        self.assertEqual(None, spec_part)

    def test_get_current_config(self):
        cf = { 'module1': { 'item1': 2, 'item2': True } }
        self.mcd._set_current_config(cf)
        self.assertEqual(cf, self.mcd.get_current_config())

    def test_get_local_changes(self):
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec2.spec")
        self.mcd.set_specification(module_spec)
        local_changes = self.mcd.get_local_changes()
        self.assertEqual({}, local_changes)
        self.mcd.set_value("Spec2/item1", 2)
        local_changes = self.mcd.get_local_changes()
        self.assertEqual({"Spec2": { "item1": 2}}, local_changes)

    def test_set_local_changes(self):
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec2.spec")
        self.mcd.set_specification(module_spec)
        self.assertEqual({}, self.mcd.get_local_changes())
        new_local_changes = {"Spec2": { "item1": 2}}
        self.mcd.set_local_changes(new_local_changes)
        self.assertEqual(new_local_changes, self.mcd.get_local_changes())

    def test_clear_local_changes(self):
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec2.spec")
        self.mcd.set_specification(module_spec)
        self.mcd.set_value("Spec2/item1", 2)
        self.mcd.clear_local_changes()
        local_changes = self.mcd.get_local_changes()
        self.assertEqual({}, local_changes)
        pass

    def test_get_local_value(self):
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec2.spec")
        self.mcd.set_specification(module_spec)
        value = self.mcd.get_local_value("Spec2/item1")
        self.assertEqual(None, value)
        self.mcd.set_value("Spec2/item1", 2)
        value = self.mcd.get_local_value("Spec2/item1")
        self.assertEqual(2, value)

    def test_get_current_value(self):
        value = self.mcd.get_current_value("Spec2/item1")
        self.assertEqual(None, value)
        self.mcd._current_config = { "Spec2": { "item1": 3 } }
        value = self.mcd.get_current_value("Spec2/item1")
        self.assertEqual(3, value)
        pass

    def test_get_default_value(self):
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec2.spec")
        self.mcd.set_specification(module_spec)
        value = self.mcd.get_default_value("Spec2/item1")
        self.assertEqual(1, value)
        value = self.mcd.get_default_value("/Spec2/item1")
        self.assertEqual(1, value)
        value = self.mcd.get_default_value("Spec2/item5[0]")
        self.assertEqual('a', value)
        value = self.mcd.get_default_value("Spec2/item5[1]")
        self.assertEqual('b', value)
        value = self.mcd.get_default_value("Spec2/item5[5]")
        self.assertEqual(None, value)
        value = self.mcd.get_default_value("Spec2/item5[0][1]")
        self.assertEqual(None, value)
        value = self.mcd.get_default_value("Spec2/item6/value1")
        self.assertEqual('default', value)
        value = self.mcd.get_default_value("Spec2/item6/value2")
        self.assertEqual(None, value)
        value = self.mcd.get_default_value("Spec2/no_such_item/asdf")
        self.assertEqual(None, value)

        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec32.spec")
        self.mcd.set_specification(module_spec)
        value = self.mcd.get_default_value("Spec32/named_set_item")
        self.assertEqual({ 'a': 1, 'b': 2}, value)
        value = self.mcd.get_default_value("Spec32/named_set_item/a")
        self.assertEqual(1, value)
        value = self.mcd.get_default_value("Spec32/named_set_item/b")
        self.assertEqual(2, value)
        value = self.mcd.get_default_value("Spec32/named_set_item/no_such_item")
        self.assertEqual(None, value)
        # Check that top-level default value works when named set contains list
        # (issue #2114)
        value = self.mcd.get_default_value("Spec32/named_set_item3/values[2]")
        self.assertEqual(3, value)
        self.assertRaises(IndexError, self.mcd.get_default_value,
                          "Spec32/named_set_item3/values[5]")

    def test_get_value(self):
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec2.spec")
        self.mcd.set_specification(module_spec)
        self.mcd.set_value("Spec2/item1", 2)

        value, status = self.mcd.get_value("Spec2/item1")
        self.assertEqual(2, value)
        self.assertEqual(MultiConfigData.LOCAL, status)

        value, status = self.mcd.get_value("Spec2/item2")
        self.assertEqual(1.1, value)
        self.assertEqual(MultiConfigData.DEFAULT, status)

        self.mcd._current_config = { "Spec2": { "item3": False } }

        value, status = self.mcd.get_value("Spec2/item3")
        self.assertEqual(False, value)
        self.assertEqual(MultiConfigData.CURRENT, status)

        value, status = self.mcd.get_value("Spec2/no_such_item")
        self.assertEqual(None, value)
        self.assertEqual(MultiConfigData.NONE, status)

        value, status = self.mcd.get_value("Spec2/item5")
        self.assertEqual(['a', 'b'], value)
        self.assertEqual(MultiConfigData.DEFAULT, status)

        value, status = self.mcd.get_value("Spec2/item5[0]")
        self.assertEqual("a", value)
        self.assertEqual(MultiConfigData.DEFAULT, status)

        value, status = self.mcd.get_value("Spec2/item5[0]", False)
        self.assertEqual(None, value)
        self.assertEqual(MultiConfigData.NONE, status)

        value, status = self.mcd.get_value("Spec2/item5[1]")
        self.assertEqual("b", value)
        self.assertEqual(MultiConfigData.DEFAULT, status)


    def test_get_value_maps(self):
        maps = self.mcd.get_value_maps()
        self.assertEqual([], maps)

        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec1.spec")
        self.mcd.set_specification(module_spec)

        expected = [{'default': False,
                     'type': 'module',
                     'name': 'Spec1',
                     'value': None,
                     'modified': False}]

        maps = self.mcd.get_value_maps()
        self.assertEqual(expected, maps)

        maps = self.mcd.get_value_maps("/")
        self.assertEqual(expected, maps)

        maps = self.mcd.get_value_maps('Spec2')
        self.assertEqual([], maps)
        maps = self.mcd.get_value_maps('Spec1')
        self.assertEqual([], maps)
        self.mcd.remove_specification("Spec1")
        self.mcd.remove_specification("foo")

        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec2.spec")
        self.mcd.set_specification(module_spec)
        maps = self.mcd.get_value_maps()
        self.assertEqual([{'default': False, 'type': 'module', 'name': 'Spec2', 'value': None, 'modified': False}], maps)
        self.mcd._set_current_config({ "Spec2": { "item1": 2 } })
        self.mcd.set_value("Spec2/item3", False)
        maps = self.mcd.get_value_maps("/Spec2")
        self.assertEqual([{'default': False, 'type': 'integer', 'name': 'Spec2/item1', 'value': 2, 'modified': False},
                          {'default': True, 'type': 'real', 'name': 'Spec2/item2', 'value': 1.1, 'modified': False},
                          {'default': False, 'type': 'boolean', 'name': 'Spec2/item3', 'value': False, 'modified': True},
                          {'default': True, 'type': 'string', 'name': 'Spec2/item4', 'value': 'test', 'modified': False},
                          {'default': True, 'type': 'list', 'name': 'Spec2/item5', 'value': ['a', 'b'], 'modified': False},
                          {'default': True, 'type': 'string', 'name': 'Spec2/item6/value1', 'value': 'default', 'modified': False},
                          {'default': False, 'type': 'integer', 'name': 'Spec2/item6/value2', 'value': None, 'modified': False}], maps)
        maps = self.mcd.get_value_maps("Spec2")
        self.assertEqual([{'default': False, 'type': 'integer', 'name': 'Spec2/item1', 'value': 2, 'modified': False},
                          {'default': True, 'type': 'real', 'name': 'Spec2/item2', 'value': 1.1, 'modified': False},
                          {'default': False, 'type': 'boolean', 'name': 'Spec2/item3', 'value': False, 'modified': True},
                          {'default': True, 'type': 'string', 'name': 'Spec2/item4', 'value': 'test', 'modified': False},
                          {'default': True, 'type': 'list', 'name': 'Spec2/item5', 'value': ['a', 'b'], 'modified': False},
                          {'default': True, 'type': 'string', 'name': 'Spec2/item6/value1', 'value': 'default', 'modified': False},
                          {'default': False, 'type': 'integer', 'name': 'Spec2/item6/value2', 'value': None, 'modified': False}], maps)
        maps = self.mcd.get_value_maps("/Spec2/item5")
        self.assertEqual([{'default': True, 'type': 'string', 'name': 'Spec2/item5[0]', 'value': 'a', 'modified': False},
                          {'default': True, 'type': 'string', 'name': 'Spec2/item5[1]', 'value': 'b', 'modified': False}], maps)
        maps = self.mcd.get_value_maps("/Spec2/item5[0]")
        self.assertEqual([{'default': True, 'modified': False, 'name': 'Spec2/item5[0]', 'type': 'string', 'value': 'a'}], maps)
        maps = self.mcd.get_value_maps("/Spec2/item1")
        self.assertEqual([{'default': False, 'type': 'integer', 'name': 'Spec2/item1', 'value': 2, 'modified': False}], maps)
        maps = self.mcd.get_value_maps("/Spec2/item2")
        self.assertEqual([{'default': True, 'type': 'real', 'name': 'Spec2/item2', 'value': 1.1, 'modified': False}], maps)
        maps = self.mcd.get_value_maps("/Spec2/item3")
        self.assertEqual([{'default': False, 'type': 'boolean', 'name': 'Spec2/item3', 'value': False, 'modified': True}], maps)
        maps = self.mcd.get_value_maps("/Spec2/item4")
        self.assertEqual([{'default': True, 'type': 'string', 'name': 'Spec2/item4', 'value': 'test', 'modified': False}], maps)

        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec24.spec")
        self.mcd.set_specification(module_spec)
        # optional list item that is not set should return as empty list
        maps = self.mcd.get_value_maps("/Spec24/item", 4)
        self.assertEqual([{'default': False, 'type': 'list', 'name': 'Spec24/item', 'value': [], 'modified': False}], maps)

        self.mcd._set_current_config({ "Spec24": { "item": [] } })
        maps = self.mcd.get_value_maps("/Spec24/item")
        self.assertEqual([{'default': False, 'modified': False, 'name': 'Spec24/item', 'type': 'list', 'value': []}], maps)

        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec22.spec")
        self.mcd.set_specification(module_spec)
        expected = [{'default': True,
                     'modified': False,
                     'name': 'Spec22/value9/v91',
                     'type': 'string',
                     'value': 'def'},
                    {'default': True,
                     'modified': False,
                     'name': 'Spec22/value9/v92/v92a',
                     'type': 'string',
                     'value': 'Hello'
                    },
                    {'default': True,
                     'modified': False,
                     'name': 'Spec22/value9/v92/v92b',
                     'type': 'integer',
                     'value': 47806
                    }
                   ]
        maps = self.mcd.get_value_maps("/Spec22/value9")
        self.assertEqual(expected, maps)

        # A slash at the end should not produce different output
        maps = self.mcd.get_value_maps("/Spec22/value9/")
        self.assertEqual(expected, maps)

        # A slash at the end should not produce different output with
        # indices either
        expected2 = [{'default': True,
                      'type': 'integer',
                      'name': 'Spec22/value5[1]',
                      'value': 'b',
                      'modified': False}]
        maps = self.mcd.get_value_maps("/Spec22/value5[1]/")
        self.assertEqual(expected2, maps)

    def test_get_value_maps_named_set(self):
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec32.spec")
        self.mcd.set_specification(module_spec)
        maps = self.mcd.get_value_maps()
        self.assertEqual([{'default': False, 'type': 'module',
                           'name': 'Spec32', 'value': None,
                           'modified': False}], maps)
        maps = self.mcd.get_value_maps("/Spec32/named_set_item")
        self.assertEqual([{'default': True, 'type': 'integer',
                           'name': 'Spec32/named_set_item/a',
                           'value': 1, 'modified': False},
                          {'default': True, 'type': 'integer',
                           'name': 'Spec32/named_set_item/b',
                           'value': 2, 'modified': False}], maps)
        maps = self.mcd.get_value_maps("/Spec32/named_set_item/a")
        self.assertEqual([{'default': True, 'type': 'integer',
                           'name': 'Spec32/named_set_item/a',
                           'value': 1, 'modified': False}], maps)
        maps = self.mcd.get_value_maps("/Spec32/named_set_item/b")
        self.assertEqual([{'default': True, 'type': 'integer',
                           'name': 'Spec32/named_set_item/b',
                           'value': 2, 'modified': False}], maps)

    def test_set_value(self):
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec2.spec")
        self.mcd.set_specification(module_spec)
        self.mcd.set_value("Spec2/item1", 2)
        self.assertRaises(isc.cc.data.DataTypeError,
                          self.mcd.set_value, "Spec2/item1", "asdf")

        self.assertRaises(isc.cc.data.DataNotFoundError,
                          self.mcd.set_value, "Spec2/no_such_item", 4)

        self.mcd.set_value("Spec2/item5[0]", "c")
        value, status = self.mcd.get_value("Spec2/item5[0]")
        self.assertEqual(value, "c")
        self.assertEqual(MultiConfigData.LOCAL, status)

        self.assertRaises(isc.cc.data.DataTypeError, self.mcd.set_value, "Spec2/item5[a]", "asdf")


    def test_unset(self):
        """
        Test the unset command works.
        """
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec2.spec")
        self.mcd.set_specification(module_spec)
        self.mcd.set_specification(module_spec)
        value, status = self.mcd.get_value("Spec2/item1")
        # This is the default first
        self.assertEqual(1, value)
        self.assertEqual(MultiConfigData.DEFAULT, status)
        # Unseting a default item does nothing.
        self.mcd.unset("Spec2/item1")
        value, status = self.mcd.get_value("Spec2/item1")
        # This should be the default
        self.assertEqual(1, value)
        self.assertEqual(MultiConfigData.DEFAULT, status)
        # Set it to something else
        self.mcd.set_value("Spec2/item1", 42)
        value, status = self.mcd.get_value("Spec2/item1")
        self.assertEqual(42, value)
        self.assertEqual(MultiConfigData.LOCAL, status)
        # Try to unset it
        self.mcd.unset("Spec2/item1")
        value, status = self.mcd.get_value("Spec2/item1")
        # This should be the default
        self.assertEqual(1, value)
        self.assertEqual(MultiConfigData.DEFAULT, status)
        # Unset a nonexisting item. Should raise.
        self.assertRaises(isc.cc.data.DataNotFoundError, self.mcd.unset, "Spec2/doesnotexist")

    def test_get_config_item_list(self):
        # Test get_config_item_list(), which returns a list of the config
        # items in a specification.
        config_items = self.mcd.get_config_item_list()
        self.assertEqual([], config_items)
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec2.spec")
        self.mcd.set_specification(module_spec)
        config_items = self.mcd.get_config_item_list()
        self.assertEqual(['Spec2'], config_items)
        config_items = self.mcd.get_config_item_list(None, False)
        self.assertEqual(['Spec2'], config_items)
        config_items = self.mcd.get_config_item_list(None, True)
        self.assertEqual(['Spec2/item1', 'Spec2/item2', 'Spec2/item3',
                          'Spec2/item4', 'Spec2/item5', 'Spec2/item6/value1',
                          'Spec2/item6/value2'], config_items)
        config_items = self.mcd.get_config_item_list("Spec2", True)
        self.assertEqual(['Spec2/item1', 'Spec2/item2', 'Spec2/item3',
                          'Spec2/item4', 'Spec2/item5[0]', 'Spec2/item5[1]',
                          'Spec2/item6/value1', 'Spec2/item6/value2'],
                          config_items)
        config_items = self.mcd.get_config_item_list("Spec2")
        self.assertEqual(['Spec2/item1', 'Spec2/item2', 'Spec2/item3',
                          'Spec2/item4', 'Spec2/item5[0]', 'Spec2/item5[1]',
                          'Spec2/item6'], config_items)
        config_items = self.mcd.get_config_item_list("/Spec2")
        self.assertEqual(['Spec2/item1', 'Spec2/item2', 'Spec2/item3',
                          'Spec2/item4', 'Spec2/item5[0]', 'Spec2/item5[1]',
                          'Spec2/item6'], config_items)
        config_items = self.mcd.get_config_item_list("Spec2", True)
        self.assertEqual(['Spec2/item1', 'Spec2/item2', 'Spec2/item3',
                          'Spec2/item4', 'Spec2/item5[0]', 'Spec2/item5[1]',
                          'Spec2/item6/value1', 'Spec2/item6/value2'],
                          config_items)

        # When lists are empty, it should only show the name
        self.mcd.set_value('Spec2/item5', [])
        config_items = self.mcd.get_config_item_list("Spec2", True)
        self.assertEqual(['Spec2/item1', 'Spec2/item2', 'Spec2/item3',
                          'Spec2/item4', 'Spec2/item5', 'Spec2/item6/value1',
                          'Spec2/item6/value2'], config_items)

    def test_is_named_set(self):
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec32.spec")
        self.mcd.set_specification(module_spec)
        spec_part = self.mcd.find_spec_part("Spec32/named_set_item")
        self.assertTrue(spec_part_is_named_set(spec_part))

    def test_get_config_item_list_named_set(self):
        config_items = self.mcd.get_config_item_list()
        self.assertEqual([], config_items)
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec32.spec")
        self.mcd.set_specification(module_spec)
        config_items = self.mcd.get_config_item_list()
        self.assertEqual(['Spec32'], config_items)
        config_items = self.mcd.get_config_item_list(None, False)
        self.assertEqual(['Spec32'], config_items)
        config_items = self.mcd.get_config_item_list(None, True)
        self.assertEqual(['Spec32/named_set_item', 'Spec32/named_set_item2',
                          'Spec32/named_set_item3', 'Spec32/named_set_item4'],
                         config_items)
        self.mcd.set_value('Spec32/named_set_item', { "aaaa": 4, "aabb": 5,
                                                      "bbbb": 6})
        config_items = self.mcd.get_config_item_list("/Spec32/named_set_item",
                                                     True)
        self.assertEqual(['Spec32/named_set_item/aaaa',
                          'Spec32/named_set_item/aabb',
                          'Spec32/named_set_item/bbbb',
                         ], config_items)

        self.mcd.set_value('Spec32/named_set_item', {})
        config_items = self.mcd.get_config_item_list("/Spec32/named_set_item",
                                                     True)
        self.assertEqual(['Spec32/named_set_item'], config_items)

        self.mcd.set_value('Spec32/named_set_item4', { "a": { "aa": 4 } } )
        config_items = self.mcd.get_config_item_list("/Spec32/named_set_item4",
                                                     True)
        self.assertEqual(['Spec32/named_set_item4/a/'], config_items)
        config_items = self.mcd.get_config_item_list("/Spec32/named_set_item4/a",
                                                     True)
        self.assertEqual(['Spec32/named_set_item4/a/aa'], config_items)

    def test_set_named_set_nonlocal(self):
        # Test whether a default named set is copied to local if a subitem
        # is changed, and that other items in the set do not get lost
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + 'spec32.spec')
        self.mcd.set_specification(module_spec)
        value, status = self.mcd.get_value('Spec32/named_set_item')
        self.assertEqual({'a': 1, 'b': 2}, value)
        self.assertEqual(MultiConfigData.DEFAULT, status)

        self.mcd.set_value('Spec32/named_set_item/b', 3)
        value, status = self.mcd.get_value('Spec32/named_set_item')
        self.assertEqual({'a': 1, 'b': 3}, value)
        self.assertEqual(MultiConfigData.LOCAL, status)

if __name__ == '__main__':
    unittest.main()

