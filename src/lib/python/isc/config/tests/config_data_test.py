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

    def test_spec_name_list(self):
        name_list = spec_name_list(self.cd.get_module_spec().get_config_spec())
        self.assertEqual(['item1', 'item2', 'item3', 'item4', 'item5/', 'item6/'], name_list)
        name_list = spec_name_list(self.cd.get_module_spec().get_config_spec(), "", True)
        self.assertEqual(['item1', 'item2', 'item3', 'item4', 'item5/', 'item6/value1', 'item6/value2'], name_list)
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
        self.assertEqual(['myModule/', 'myModule/value1', 'myModule/value2', 'myModule/value3', 'myModule/value4', 'myModule/value5/', 'myModule/value6/v61', 'myModule/value6/v62', 'myModule/value7/', 'myModule/value8/', 'myModule/value9/v91', 'myModule/value9/v92/v92a', 'myModule/value9/v92/v92b'], name_list)

        self.assertRaises(ConfigDataError, spec_name_list, 1)
        self.assertRaises(ConfigDataError, spec_name_list, [ 'a' ])

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
        self.assertEqual(['item1', 'item2', 'item3', 'item4', 'item5/', 'item6/'], name_list)
        name_list = self.cd.get_item_list("", True)
        self.assertEqual(['item1', 'item2', 'item3', 'item4', 'item5/', 'item6/value1', 'item6/value2'], name_list)
        name_list = self.cd.get_item_list("item6", False)
        self.assertEqual(['item6/value1', 'item6/value2'], name_list)

    def test_get_full_config(self):
        full_config = self.cd.get_full_config()
        self.assertEqual({ "item1": 1, "item2": 1.1, "item3": True, "item4": "test", "item5/": ['a', 'b'], "item6/value1": 'default', 'item6/value2': None}, full_config)
        my_config = { "item1": 2, "item2": 2.2, "item3": False, "item4": "asdf", "item5": [ "c", "d" ] }
        self.cd.set_local_config(my_config)
        full_config = self.cd.get_full_config()
        self.assertEqual({ "item1": 2, "item2": 2.2, "item3": False, "item4": "asdf", "item5/": [ "c", "d" ], "item6/value1": 'default', 'item6/value2': None}, full_config)

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
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec2.spec")
        self.mcd.set_specification(module_spec)
        spec_part = self.mcd.find_spec_part("Spec2/item1")
        self.assertEqual({'item_name': 'item1', 'item_type': 'integer', 'item_optional': False, 'item_default': 1, }, spec_part)

    def test_get_current_config(self):
        cf = { 'module1': { 'item1': 2, 'item2': True } }
        self.mcd._set_current_config(cf);
        self.assertEqual(cf, self.mcd.get_current_config())

    def test_get_local_changes(self):
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec2.spec")
        self.mcd.set_specification(module_spec)
        local_changes = self.mcd.get_local_changes()
        self.assertEqual({}, local_changes)
        self.mcd.set_value("Spec2/item1", 2)
        local_changes = self.mcd.get_local_changes()
        self.assertEqual({"Spec2": { "item1": 2}}, local_changes)
        

    def test_clear_local_changes(self):
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec2.spec")
        self.mcd.set_specification(module_spec)
        self.mcd.set_value("Spec2/item1", 2)
        self.mcd.clear_local_changes()
        local_changes = self.mcd.get_local_changes()
        self.assertEqual({}, local_changes)
        pass

    def test_get_local_value(self):
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
        value = self.mcd.get_default_value("Spec2/item6/value1")
        self.assertEqual('default', value)
        value = self.mcd.get_default_value("Spec2/item6/value2")
        self.assertEqual(None, value)
        value = self.mcd.get_default_value("Spec2/no_such_item/asdf")
        self.assertEqual(None, value)

    def test_get_value(self):
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec2.spec")
        self.mcd.set_specification(module_spec)
        self.mcd.set_value("Spec2/item1", 2)
        value,status = self.mcd.get_value("Spec2/item1")
        self.assertEqual(2, value)
        self.assertEqual(MultiConfigData.LOCAL, status)
        value,status = self.mcd.get_value("Spec2/item2")
        self.assertEqual(1.1, value)
        self.assertEqual(MultiConfigData.DEFAULT, status)
        self.mcd._current_config = { "Spec2": { "item3": False } }
        value,status = self.mcd.get_value("Spec2/item3")
        self.assertEqual(False, value)
        self.assertEqual(MultiConfigData.CURRENT, status)
        value,status = self.mcd.get_value("Spec2/no_such_item")
        self.assertEqual(None, value)
        self.assertEqual(MultiConfigData.NONE, status)

    def test_get_value_maps(self):
        maps = self.mcd.get_value_maps()
        self.assertEqual([], maps)
        
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec1.spec")
        self.mcd.set_specification(module_spec)
        maps = self.mcd.get_value_maps()
        self.assertEqual([{'default': False, 'type': 'module', 'name': 'Spec1', 'value': None, 'modified': False}], maps)
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
        self.assertEqual([{'default': False, 'type': 'integer', 'name': 'item1', 'value': 2, 'modified': False},
                          {'default': False, 'type': 'real', 'name': 'item2', 'value': 1.1, 'modified': False},
                          {'default': False, 'type': 'boolean', 'name': 'item3', 'value': False, 'modified': True},
                          {'default': False, 'type': 'string', 'name': 'item4', 'value': 'test', 'modified': False},
                          {'default': False, 'type': 'list', 'name': 'item5', 'value': ['a', 'b'], 'modified': False},
                          {'default': False, 'type': 'map', 'name': 'item6', 'value': {}, 'modified': False}], maps)
        maps = self.mcd.get_value_maps("Spec2")
        self.assertEqual([{'default': False, 'type': 'integer', 'name': 'item1', 'value': 2, 'modified': False},
                          {'default': False, 'type': 'real', 'name': 'item2', 'value': 1.1, 'modified': False},
                          {'default': False, 'type': 'boolean', 'name': 'item3', 'value': False, 'modified': True},
                          {'default': False, 'type': 'string', 'name': 'item4', 'value': 'test', 'modified': False},
                          {'default': False, 'type': 'list', 'name': 'item5', 'value': ['a', 'b'], 'modified': False},
                          {'default': False, 'type': 'map', 'name': 'item6', 'value': {}, 'modified': False}], maps)
        maps = self.mcd.get_value_maps("/Spec2/item5")
        self.assertEqual([{'default': False, 'type': 'string', 'name': 'list_element', 'value': 'a', 'modified': False},
                          {'default': False, 'type': 'string', 'name': 'list_element', 'value': 'b', 'modified': False}], maps)
        maps = self.mcd.get_value_maps("/Spec2/item1")
        self.assertEqual([{'default': False, 'type': 'integer', 'name': 'item1', 'value': 2, 'modified': False}], maps)
        maps = self.mcd.get_value_maps("/Spec2/item2")
        self.assertEqual([{'default': False, 'type': 'real', 'name': 'item2', 'value': 1.1, 'modified': False}], maps)
        maps = self.mcd.get_value_maps("/Spec2/item3")
        self.assertEqual([{'default': False, 'type': 'boolean', 'name': 'item3', 'value': False, 'modified': True}], maps)
        maps = self.mcd.get_value_maps("/Spec2/item4")
        self.assertEqual([{'default': False, 'type': 'string', 'name': 'item4', 'value': 'test', 'modified': False}], maps)

        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec24.spec")
        self.mcd.set_specification(module_spec)
        maps = self.mcd.get_value_maps("/Spec24/item")
        self.assertEqual([], maps)
        self.mcd._set_current_config({ "Spec24": { "item": [] } })
        maps = self.mcd.get_value_maps("/Spec24/item")
        self.assertEqual([], maps)



    def test_set_value(self):
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec2.spec")
        self.mcd.set_specification(module_spec)
        self.mcd.set_value("Spec2/item1", 2)
        self.assertRaises(isc.cc.data.DataTypeError, self.mcd.set_value, "Spec2/item1", "asdf")
        self.mcd.set_value("Spec2/no_such_item", 4)

    def test_get_config_item_list(self):
        config_items = self.mcd.get_config_item_list()
        self.assertEqual([], config_items)
        module_spec = isc.config.module_spec_from_file(self.data_path + os.sep + "spec2.spec")
        self.mcd.set_specification(module_spec)
        config_items = self.mcd.get_config_item_list()
        self.assertEqual(['Spec2'], config_items)
        config_items = self.mcd.get_config_item_list(None, False)
        self.assertEqual(['Spec2'], config_items)
        config_items = self.mcd.get_config_item_list(None, True)
        self.assertEqual(['Spec2/item1', 'Spec2/item2', 'Spec2/item3', 'Spec2/item4', 'Spec2/item5/', 'Spec2/item6/value1', 'Spec2/item6/value2'], config_items)
        config_items = self.mcd.get_config_item_list("Spec2", True)
        self.assertEqual(['Spec2/item1', 'Spec2/item2', 'Spec2/item3', 'Spec2/item4', 'Spec2/item5/', 'Spec2/item6/value1', 'Spec2/item6/value2'], config_items)
        config_items = self.mcd.get_config_item_list("Spec2")
        self.assertEqual(['Spec2/item1', 'Spec2/item2', 'Spec2/item3', 'Spec2/item4', 'Spec2/item5/', 'Spec2/item6/'], config_items)
        config_items = self.mcd.get_config_item_list("Spec2", True)
        self.assertEqual(['Spec2/item1', 'Spec2/item2', 'Spec2/item3', 'Spec2/item4', 'Spec2/item5/', 'Spec2/item6/value1', 'Spec2/item6/value2'], config_items)

if __name__ == '__main__':
    unittest.main()

