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
# Helper functions for data elements as used in cc-channel and
# configuration. There is no python equivalent for the cpp Element
# class, since data elements are represented by native python types
# (int, real, bool, string, list and dict respectively)
#

import ast

class DataNotFoundError(Exception): pass
class DataTypeError(Exception): pass

def merge(orig, new):
    """Merges the contents of new into orig, think recursive update()
       orig and new must both be dicts. If an element value is None in
       new it will be removed in orig."""
    if type(orig) != dict or type(new) != dict:
        raise DataTypeError("Not a dict in merge()")
    for kn in new.keys():
        if kn in orig:
            if new[kn]:
                if type(new[kn]) == dict:
                    merge(orig[kn], new[kn])
                else:
                    orig[kn] = new[kn]
            else:
                del orig[kn]
        else:
            orig[kn] = new[kn]

def find(element, identifier):
    """Returns the subelement in the given data element, raises DataNotFoundError if not found"""
    if type(identifier) != str or (type(element) != dict and identifier != ""):
        raise DataTypeError("identifier in merge() is not a string")
    if type(identifier) != str or (type(element) != dict and identifier != ""):
        raise DataTypeError("element in merge() is not a dict")
    id_parts = identifier.split("/")
    id_parts[:] = (value for value in id_parts if value != "")
    cur_el = element
    for id in id_parts:
        if type(cur_el) == dict and id in cur_el.keys():
            cur_el = cur_el[id]
        else:
            raise DataNotFoundError(identifier + " in " + str(element))
    return cur_el

def set(element, identifier, value):
    """Sets the value at the element specified by identifier to value.
       If the value is None, it is removed from the dict. If element
       is not a dict, or if the identifier points to something that is
       not, a DataTypeError is raised. The element is updated inline,
       so if the original needs to be kept, you must make a copy before
       calling set(). The updated base element is returned (so that
       el.set().set().set() is possible)"""
    if type(element) != dict:
        raise DataTypeError("element in set() is not a dict")
    if type(identifier) != str:
        raise DataTypeError("identifier in set() is not a string")
    id_parts = identifier.split("/")
    id_parts[:] = (value for value in id_parts if value != "")
    cur_el = element
    for id in id_parts[:-1]:
        if id in cur_el.keys():
            cur_el = cur_el[id]
        else:
            if value:
                cur_el[id] = {}
                cur_el = cur_el[id]
            else:
                # set to none, and parent el not found, return
                return element
    if value:
        cur_el[id_parts[-1]] = value
    else:
        del cur_el[id_parts[-1]]
    return element

def unset(element, identifier):
    """Removes the element at the given identifier if it exists. Raises
       a DataTypeError if element is not a dict or if identifier is not
       a string. Returns the base element."""
    # perhaps we can simply do with set none, and remove this whole
    # function
    return set(element, identifier, None)

def find_no_exc(element, identifier):
    """Returns the subelement in the given data element, returns None
       if not found, or if an error occurred (i.e. this function should
       never raise an exception)"""
    if type(identifier) != str:
        return None
    id_parts = identifier.split("/")
    id_parts[:] = (value for value in id_parts if value != "")
    cur_el = element
    for id in id_parts:
        if (type(cur_el) == dict and id in cur_el.keys()) or id=="":
            cur_el = cur_el[id]
        else:
            return None
    return cur_el

#
# hmm, these are more relevant for datadefition
# should we (re)move them?
#
def find_spec(element, identifier):
    """find the data definition for the given identifier
       returns either a map with 'item_name' etc, or a list of those"""
    id_parts = identifier.split("/")
    id_parts[:] = (value for value in id_parts if value != "")
    cur_el = element
    for id in id_parts:
        if type(cur_el) == dict and id in cur_el.keys():
            cur_el = cur_el[id]
        elif type(cur_el) == dict and 'item_name' in cur_el.keys() and cur_el['item_name'] == id:
            pass
        elif type(cur_el) == list:
            found = False
            for cur_el_item in cur_el:
                if cur_el_item['item_name'] == id and 'item_default' in cur_el_item.keys():
                    cur_el = cur_el_item
                    found = True
            if not found:
                raise DataNotFoundError(id + " in " + str(cur_el))
        else:
            raise DataNotFoundError(id + " in " + str(cur_el))
    return cur_el

def check_type(specification, value):
    """Returns true if the value is of the correct type given the
       specification"""
    if type(specification) == list:
        data_type = "list"
    else:
        data_type = specification['item_type']

    if data_type == "integer" and type(value) != int:
        raise DataTypeError(str(value) + " should be an integer")
    elif data_type == "real" and type(value) != double:
        raise DataTypeError(str(value) + " should be a real")
    elif data_type == "boolean" and type(value) != boolean:
        raise DataTypeError(str(value) + " should be a boolean")
    elif data_type == "string" and type(value) != str:
        raise DataTypeError(str(value) + " should be a string")
    elif data_type == "list":
        if type(value) != list:
            raise DataTypeError(str(value) + " should be a list, not a " + str(value.__class__.__name__))
        else:
            # todo: check subtypes etc
            for element in value:
                check_type(specification['list_item_spec'], element)
    elif data_type == "map" and type(value) != dict:
        # todo: check subtypes etc
        raise DataTypeError(str(value) + " should be a map")

def spec_name_list(spec, prefix="", recurse=False):
    """Returns a full list of all possible item identifiers in the
       specification (part)"""
    result = []
    if prefix != "" and not prefix.endswith("/"):
        prefix += "/"
    if type(spec) == dict:
        for name in spec:
            result.append(prefix + name + "/")
            if recurse:
                result.extend(spec_name_list(spec[name],name, recurse))
    elif type(spec) == list:
        for list_el in spec:
            if 'item_name' in list_el:
                if list_el['item_type'] == dict:
                    if recurse:
                        result.extend(spec_name_list(list_el['map_item_spec'], prefix + list_el['item_name'], recurse))
                else:
                    name = list_el['item_name']
                    if list_el['item_type'] in ["list", "map"]:
                        name += "/"
                    result.append(name)

    return result

def parse_value_str(value_str):
    """Parses the given string to a native python object. If the
       string cannot be parsed, it is returned. If it is not a string,
       None is returned"""
    if type(value_str) != str:
        return None
    try:
        return ast.literal_eval(value_str)
    except ValueError as ve:
        # simply return the string itself
        return value_str
    except SyntaxError as ve:
        # simply return the string itself
        return value_str

class ConfigData:
    def __init__(self, specification):
        self.specification = specification
        self.data = {}

    def get_item_list(self, identifier = None):
        if identifier:
            spec = find_spec(self.specification, identifier)
            return spec_name_list(spec, identifier + "/")
        return spec_name_list(self.specification)

    def get_value(self, identifier):
        """Returns a tuple where the first item is the value at the
           given identifier, and the second item is a bool which is
           true if the value is an unset default"""
        value = find_no_exc(self.data, identifier)
        if value:
            return value, False
        spec = find_spec(self.specification, identifier)
        if spec and 'item_default' in spec:
            return spec['item_default'], True
        return None, False

class UIConfigData():
    def __init__(self, conn, name = ''):
        self.module_name = name
        data_spec = self.get_data_specification(conn)
        self.config = ConfigData(data_spec)
        self.get_config_data(conn)
        self.config_changes = {}
    
    def get_config_data(self, conn):
        self.config.data = conn.send_GET('/config_data') 

    def send_changes(self, conn):
        conn.send_POST('/ConfigManager/set_config', self.config_changes)
        # Get latest config data
        self.get_config_data(conn)
        self.config_changes = {}
    
    def get_data_specification(self, conn):
        return conn.send_GET('/config_spec') 

    def set(self, identifier, value):
        # check against definition
        spec = find_spec(identifier)
        check_type(spec, value)
        set(self.config_changes, identifier, value)

    def get_value(self, identifier):
        """Returns a three-tuple, where the first item is the value
           (or None), the second is a boolean specifying whether
           the value is the default value, and the third is a boolean
           specifying whether the value is an uncommitted change"""
        value = find_no_exc(self.config_changes, identifier)
        if value:
            return value, False, True
        value, default = self.config.get_value(identifier)
        if value:
            return value, default, False
        return None, False, False

    def get_value_map_single(self, identifier, entry):
        """Returns a single entry for a value_map, where the value is
           not a part of a bigger map"""
        result_part = {}
        result_part['name'] = entry['item_name']
        result_part['type'] = entry['item_type']
        value, default, modified = self.get_value(identifier)
        # should we check type and only set int, double, bool and string here?
        result_part['value'] = value
        result_part['default'] = default
        result_part['modified'] = modified
        return result_part

    def get_value_map(self, identifier, entry):
        """Returns a single entry for a value_map, where the value is
           a part of a bigger map"""
        result_part = {}
        result_part['name'] = entry['item_name']
        result_part['type'] = entry['item_type']
        value, default, modified = self.get_value(identifier + "/" + entry['item_name'])
        # should we check type and only set int, double, bool and string here?
        result_part['value'] = value
        result_part['default'] = default
        result_part['modified'] = modified
        return result_part

    def get_value_maps(self, identifier = None):
        """Returns a list of maps, containing the following values:
           name: name of the entry (string)
           type: string containing the type of the value (or 'module')
           value: value of the entry if it is a string, int, double or bool
           modified: true if the value is a local change
           default: true if the value has been changed
           Throws DataNotFoundError if the identifier is bad
        """
        spec = find_spec(self.config.specification, identifier)
        result = []
        if type(spec) == dict:
            # either the top-level list of modules or a spec map
            if 'item_name' in spec:
                result_part = self.get_value_map_single(identifier, spec)
                if result_part['type'] == "list":
                    values = self.get_value(identifier)[0]
                    if values:
                        for value in values:
                            result_part2 = {}
                            li_spec = spec['list_item_spec']
                            result_part2['name'] = li_spec['item_name']
                            result_part2['value'] = value
                            result_part2['type'] = li_spec['item_type']
                            result_part2['default'] = False
                            result_part2['modified'] = False
                            result.append(result_part2)
                else:
                    result.append(result_part)
                
            else:
                for name in spec:
                    result_part = {}
                    result_part['name'] = name
                    result_part['type'] = "module"
                    result_part['value'] = None
                    result_part['default'] = False
                    result_part['modified'] = False
                    result.append(result_part)
        elif type(spec) == list:
            for entry in spec:
                if type(entry) == dict and 'item_name' in entry:
                    result.append(self.get_value_map(identifier, entry))
        return result

    def add(self, identifier, value_str):
        data_spec = find_spec(self.config.specification, identifier)
        if (type(data_spec) != dict or "list_item_spec" not in data_spec):
            raise DataTypeError(identifier + " is not a list")
        value = parse_value_str(value_str)
        check_type(data_spec, [value])
        cur_list = find_no_exc(self.config_changes, identifier)
        if not cur_list:
            cur_list = find_no_exc(self.config.data, identifier)
        if not cur_list:
            cur_list = []
        if value not in cur_list:
            cur_list.append(value)
        set(self.config_changes, identifier, cur_list)

    def remove(self, identifier, value_str):
        data_spec = find_spec(self.config.specification, identifier)
        if (type(data_spec) != dict or "list_item_spec" not in data_spec):
            raise DataTypeError(identifier + " is not a list")
        value = parse_value_str(value_str)
        check_type(data_spec, [value])
        cur_list = find_no_exc(self.config_changes, identifier)
        if not cur_list:
            cur_list = find_no_exc(self.config.data, identifier)
        if not cur_list:
            cur_list = []
        if value in cur_list:
            cur_list.remove(value)
        set(self.config_changes, identifier, cur_list)

    def set(self, identifier, value_str):
        data_spec = find_spec(self.config.specification, identifier)
        value = parse_value_str(value_str)
        check_type(data_spec, value)
        set(self.config_changes, identifier, value)

    def unset(self, identifier):
        # todo: check whether the value is optional?
        unset(self.config_changes, identifier)

    def revert(self):
        self.config_changes = {}

    def commit(self, conn):
        self.send_changes(conn)
