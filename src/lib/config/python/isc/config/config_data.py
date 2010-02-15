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
# Class to store configuration data and data definition
# Used by the config manager and python modules that communicate
# with the configuration manager
#


import isc.cc.data
import isc.config.datadefinition

class ConfigDataError(Exception): pass

#
# hmm, these are more relevant for datadefition
# should we (re)move them?
#
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

def find_spec(element, identifier):
    """find the data definition for the given identifier
       returns either a map with 'item_name' etc, or a list of those"""
    if identifier == "":
        return element
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
                raise isc.cc.data.DataNotFoundError(id + " in " + str(cur_el))
        else:
            raise isc.cc.data.DataNotFoundError(id + " in " + str(cur_el))
    return cur_el

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


class ConfigData:
    """This class stores the datadefinition and the current non-default
       config values. It provides functions to get the actual value or
       the default value if no non-default value has been set"""
   
    def __init__(self, specification):
        """Initialize a ConfigData instance. If specification is not
           of type DataDefinition, a ConfigDataError is raised."""
        if type(specification) != isc.config.DataDefinition:
            raise ConfigDataError("specification is of type " + str(type(specification)) + ", not DataDefinition")
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

    def get_specification(self):
        """Returns the datadefinition"""
        print(self.specification)
        return self.specification

    def set_local_config(self, data):
        """Set the non-default config values, as passed by cfgmgr"""
        self.data = data

    def get_local_config(self):
        """Returns the non-default config values in a dict"""
        return self.config();

    #def get_identifiers(self):
    # Returns a list containing all identifiers

    #def 


class MultiConfigData:
    """This class stores the datadefinitions, current non-default
       configuration values and 'local' (uncommitted) changes for
       multiple modules"""
    LOCAL   = 1
    CURRENT = 2
    DEFAULT = 3
    NONE    = 4
    
    def __init__(self):
        self._specifications = {}
        self._current_config = {}
        self._local_changes = {}

    def set_specification(self, spec):
        if type(spec) != isc.config.DataDefinition:
            raise Exception("not a datadef")
        self._specifications[spec.get_module_name()] = spec

    def get_specification(self, module):
        if module in self._specifications:
            return self._specifications[module]
        else:
            return None

    def find_spec_part(self, identifier):
        """returns the specification for the item at the given
           identifier, or None if not found"""
        if identifier[0] == '/':
            identifier = identifier[1:]
        module, sep, id = identifier.partition("/")
        try:
            return find_spec(self._specifications[module].get_config_data(), id)
        except isc.cc.data.DataNotFoundError as dnfe:
            return None

    def set_current_config(self, config):
        self._current_config = config

    def get_current_config(self):
        """The current config is a dict where the first level is
           the module name, and the value is the config values for
           that module"""
        return self._current_config
        
    def get_local_changes(self):
        return self._local_changes

    def clear_local_changes(self):
        self._local_changes = {}

    def get_local_value(self, identifier):
        return isc.cc.data.find_no_exc(self._local_changes, identifier)
        
    def get_current_value(self, identifier):
        """Returns the current non-default value, or None if not set"""
        return isc.cc.data.find_no_exc(self._current_config, identifier)
        
    def get_default_value(self, identifier):
        """returns the default value, or None if there is no default"""
        if identifier[0] == '/':
            identifier = identifier[1:]
        module, sep, id = identifier.partition("/")
        try:
            spec = find_spec(self._specifications[module].get_config_data(), id)
            if 'item_default' in spec:
                return spec['item_default']
            else:
                return None
        except isc.cc.data.DataNotFoundError as dnfe:
            return None

    def get_value(self, identifier):
        """Returns a tuple containing value,status. Status is either
           LOCAL, CURRENT, DEFAULT or NONE, corresponding to the
           source of the value (local change, current setting, default
           as specified by the specification, or not found at all)."""
        value = self.get_local_value(identifier)
        if value:
            return value, self.LOCAL
        value = self.get_current_value(identifier)
        if value:
            return value, self.CURRENT
        value = self.get_default_value(identifier)
        if value:
            return value, self.DEFAULT
        return None, self.NONE

    def get_value_maps(self, identifier = None):
        """Returns a list of dicts, containing the following values:
           name: name of the entry (string)
           type: string containing the type of the value (or 'module')
           value: value of the entry if it is a string, int, double or bool
           modified: true if the value is a local change
           default: true if the value has been changed
           Throws DataNotFoundError if the identifier is bad
           TODO: use the consts for those last ones
        """
        result = []
        if not identifier:
            # No identifier, so we need the list of current modules
            for module in self._specifications.keys():
                entry = {}
                entry['name'] = module
                entry['type'] = 'module'
                entry['value'] = None
                entry['modified'] = False
                entry['default'] = False
                result.append(entry)
        else:
            if identifier[0] == '/':
                identifier = identifier[1:]
            module, sep, id = identifier.partition('/')
            spec = self.get_specification(module)
            if spec:
                print("[XX] getpartspec")
                spec_part = find_spec(spec.get_config_data(), id)
                print(spec_part)
                if type(spec_part) == list:
                    for item in spec_part:
                        entry = {}
                        entry['name'] = item['item_name']
                        entry['type'] = item['item_type']
                        print("[XX] getvalue")
                        value, status = self.get_value("/" + identifier + "/" + item['item_name'])
                        entry['value'] = value
                        if status == self.LOCAL:
                            entry['modified'] = True
                        else:
                            entry['modified'] = False
                        if status == self.DEFAULT:
                            entry['default'] = False
                        else:
                            entry['default'] = False
                        result.append(entry)
                else:
                    item = spec_part
                    if item['item_type'] == 'list':
                        li_spec = item['list_item_spec']
                        print("[XX] item:")
                        print(item)
                        l, status =  self.get_value("/" + identifier)
                        if l:
                            for value in l:
                                result_part2 = {}
                                result_part2['name'] = li_spec['item_name']
                                result_part2['value'] = value
                                result_part2['type'] = li_spec['item_type']
                                result_part2['default'] = False
                                result_part2['modified'] = False
                                result.append(result_part2)
                    else:
                        entry = {}
                        entry['name'] = item['item_name']
                        entry['type'] = item['item_type']
                        #value, status = self.get_value("/" + identifier + "/" + item['item_name'])
                        value, status = self.get_value("/" + identifier)
                        entry['value'] = value
                        if status == self.LOCAL:
                            entry['modified'] = True
                        else:
                            entry['modified'] = False
                        if status == self.DEFAULT:
                            entry['default'] = False
                        else:
                            entry['default'] = False
                        result.append(entry)
            #print(spec)
        return result

    def set_value(self, identifier, value):
        """Set the local value at the given identifier to value"""
        # todo: validate
        isc.cc.data.set(self._local_changes, identifier, value)
 
    def get_config_item_list(self, identifier = None):
        """Returns a list of strings containing the item_names of
           the child items at the given identifier. If no identifier is
           specified, returns a list of module names. The first part of
           the identifier (up to the first /) is interpreted as the
           module name"""
        if identifier:
            spec = self.find_spec_part(identifier)
            return spec_name_list(spec, identifier + "/")
        else:
            return self._specifications.keys()

    
class UIConfigData():
    """This class is used in a configuration user interface. It contains
       specific functions for getting, displaying, and sending
       configuration settings."""
    def __init__(self, conn):
        self._conn = conn
        self._data = MultiConfigData()
        self.request_specifications()
        self.request_current_config()
        a,b = self._data.get_value("/Boss/some_string")
        print("[XX] a,b: " + str(a) + ", " + str(b))

    def request_specifications(self):
        # this step should be unnecessary but is the current way cmdctl returns stuff
        # so changes are needed there to make this clean (we need a command to simply get the
        # full specs for everything, including commands etc, not separate gets for that)
        specs = self._conn.send_GET('/config_spec')
        commands = self._conn.send_GET('/commands')
        #print(specs)
        #print(commands)
        for module in specs.keys():
            cur_spec = { 'module_name': module }
            if module in specs and specs[module]:
                cur_spec['config_data'] = specs[module]
            if module in commands and commands[module]:
                cur_spec['commands'] = commands[module]
            
            self._data.set_specification(isc.config.DataDefinition(cur_spec))

    def request_current_config(self):
        config = self._conn.send_GET('/config_data')
        if 'version' not in config or config['version'] != 1:
            raise Exception("Bad config version")
        self._data.set_current_config(config)

    def get_value(self, identifier):
        return self._data.get_value(identifier)

    def set_value(self, identifier, value):
        return self._data.set_value(identifier, value);
    
    def add_value(self, identifier, value_str):
        data_spec = self._data.find_spec_part(identifier)
        if (type(data_spec) != dict or "list_item_spec" not in data_spec):
            raise DataTypeError(identifier + " is not a list")
        value = isc.cc.data.parse_value_str(value_str)
        cur_list, status = self.get_value(identifier)
        if not cur_list:
            cur_list = []
        if value not in cur_list:
            cur_list.append(value)
        self.set_value(identifier, cur_list)

    def remove_value(self, identifier, value_str):
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

    def get_value_maps(self, identifier = None):
        return self._data.get_value_maps(identifier)

    def get_local_changes(self):
        return self._data.get_local_changes()

    def commit(self):
        self._conn.send_POST('/ConfigManager/set_config', self._data.get_local_changes())
        # todo: check result
        self.request_current_config()
        self._data.clear_local_changes()

    def get_config_item_list(self, identifier = None):
        return self._data.get_config_item_list(identifier)

# remove
class OUIConfigData():
    """This class is used in a configuration user interface. It contains
       specific functions for getting, displaying, and sending
       configuration settings."""
    def __init__(self, conn):
        # the specs dict contains module: configdata elements
        # these should all be replaced by the new stuff
        data_spec = self.get_data_specification(conn)
        self.config = data_spec
        self.get_config_data(conn)
        self.config_changes = {}
        #
        self.config_
        self.specs = self.get_data_specifications(conn)
        
    
    def get_config_data(self, conn):
        data = conn.send_GET('/config_data')

    def send_changes(self, conn):
        conn.send_POST('/ConfigManager/set_config', self.config_changes)
        # Get latest config data
        self.get_config_data(conn)
        self.config_changes = {}

    def get_data_specification(self, conn):
        return conn.send_GET('/config_spec')

    def get_data_specifications(self, conn):
        specs = {}
        allspecs = conn.send_GET('/config_spec')
        print("[XX] allspecs:")
        print(allspecs)
        

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
        value = isc.cc.data.find_no_exc(self.config_changes, identifier)
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
        print("[XX] config:")
        print(self.config)
        spec = find_spec(self.config, identifier)
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
