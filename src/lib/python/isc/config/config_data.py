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

"""
Classes to store configuration data and module specifications

Used by the config manager, (python) modules, and UI's (those last
two through the classes in ccsession)
"""

import isc.cc.data
import isc.config.module_spec
import ast

class ConfigDataError(Exception): pass

BIND10_CONFIG_DATA_VERSION = 2

def check_type(spec_part, value):
    """Does nothing if the value is of the correct type given the
       specification part relevant for the value. Raises an
       isc.cc.data.DataTypeError exception if not. spec_part can be
       retrieved with find_spec_part()"""
    if type(spec_part) == dict and 'item_type' in spec_part:
        data_type = spec_part['item_type']
    else:
        raise isc.cc.data.DataTypeError(str("Incorrect specification part for type checking"))

    if data_type == "integer" and type(value) != int:
        raise isc.cc.data.DataTypeError(str(value) + " is not an integer")
    elif data_type == "real" and type(value) != float:
        raise isc.cc.data.DataTypeError(str(value) + " is not a real")
    elif data_type == "boolean" and type(value) != bool:
        raise isc.cc.data.DataTypeError(str(value) + " is not a boolean")
    elif data_type == "string" and type(value) != str:
        raise isc.cc.data.DataTypeError(str(value) + " is not a string")
    elif data_type == "list":
        if type(value) != list:
            raise isc.cc.data.DataTypeError(str(value) + " is not a list")
        else:
            for element in value:
                check_type(spec_part['list_item_spec'], element)
    elif data_type == "map" and type(value) != dict:
        # todo: check types of map contents too
        raise isc.cc.data.DataTypeError(str(value) + " is not a map")

def convert_type(spec_part, value):
    """Convert the given value(type is string) according specification 
    part relevant for the value. Raises an isc.cc.data.DataTypeError 
    exception if conversion failed.
    """
    if type(spec_part) == dict and 'item_type' in spec_part:
        data_type = spec_part['item_type']
    else:
        raise isc.cc.data.DataTypeError(str("Incorrect specification part for type conversion"))
   
    try:
        if data_type == "integer":
            return int(value)
        elif data_type == "real":
            return float(value)
        elif data_type == "boolean":
            return str.lower(str(value)) != 'false'
        elif data_type == "string":
            return str(value)
        elif data_type == "list":
            ret = []
            if type(value) == list:
                for item in value:    
                    ret.append(convert_type(spec_part['list_item_spec'], item))
            elif type(value) == str:    
                value = value.split(',')
                for item in value:
                    sub_value = item.split()
                    for sub_item in sub_value:
                        ret.append(convert_type(spec_part['list_item_spec'],
                                                sub_item))

            if ret == []:
                raise isc.cc.data.DataTypeError(str(value) + " is not a list")

            return ret
        elif data_type == "map":
            map = ast.literal_eval(value)
            if type(map) == dict:
                # todo: check types of map contents too
                return map
            else:
                raise isc.cc.data.DataTypeError(
                           "Value in convert_type not a string "
                           "specifying a dict")
        else:
            return value
    except ValueError as err:
        raise isc.cc.data.DataTypeError(str(err))
    except TypeError as err:
        raise isc.cc.data.DataTypeError(str(err))

def find_spec_part(element, identifier):
    """find the data definition for the given identifier
       returns either a map with 'item_name' etc, or a list of those"""
    if identifier == "":
        return element
    id_parts = identifier.split("/")
    id_parts[:] = (value for value in id_parts if value != "")
    cur_el = element

    for id_part in id_parts:
        # strip list selector part
        # don't need it for the spec part, so just drop it
        id, list_indices = isc.cc.data.split_identifier_list_indices(id_part)
        if type(cur_el) == dict and 'map_item_spec' in cur_el.keys():
            found = False
            for cur_el_item in cur_el['map_item_spec']:
                if cur_el_item['item_name'] == id:
                    cur_el = cur_el_item
                    found = True
            if not found:
                raise isc.cc.data.DataNotFoundError(id + " in " + str(cur_el))
        elif type(cur_el) == list:
            found = False
            for cur_el_item in cur_el:
                if cur_el_item['item_name'] == id:
                    cur_el = cur_el_item
                    found = True
            if not found:
                raise isc.cc.data.DataNotFoundError(id + " in " + str(cur_el))
        else:
            raise isc.cc.data.DataNotFoundError("Not a correct config specification")
    return cur_el

def spec_name_list(spec, prefix="", recurse=False):
    """Returns a full list of all possible item identifiers in the
       specification (part). Raises a ConfigDataError if spec is not
       a correct spec (as returned by ModuleSpec.get_config_spec()"""
    result = []
    if prefix != "" and not prefix.endswith("/"):
        prefix += "/"
    if type(spec) == dict:
        if 'map_item_spec' in spec:
            for map_el in spec['map_item_spec']:
                name = map_el['item_name']
                if map_el['item_type'] == 'map':
                    name += "/"
                if recurse and 'map_item_spec' in map_el:
                    result.extend(spec_name_list(map_el['map_item_spec'], prefix + map_el['item_name'], recurse))
                else:
                    result.append(prefix + name)
        else:
            for name in spec:
                result.append(prefix + name + "/")
                if recurse:
                    result.extend(spec_name_list(spec[name],name, recurse))
    elif type(spec) == list:
        for list_el in spec:
            if 'item_name' in list_el:
                if list_el['item_type'] == "map" and recurse:
                    result.extend(spec_name_list(list_el['map_item_spec'], prefix + list_el['item_name'], recurse))
                else:
                    name = list_el['item_name']
                    result.append(prefix + name)
            else:
                raise ConfigDataError("Bad specification")
    else:
        raise ConfigDataError("Bad specication")
    return result

class ConfigData:
    """This class stores the module specs and the current non-default
       config values. It provides functions to get the actual value or
       the default value if no non-default value has been set"""
   
    def __init__(self, specification):
        """Initialize a ConfigData instance. If specification is not
           of type ModuleSpec, a ConfigDataError is raised."""
        if type(specification) != isc.config.ModuleSpec:
            raise ConfigDataError("specification is of type " + str(type(specification)) + ", not ModuleSpec")
        self.specification = specification
        self.data = {}

    def get_value(self, identifier):
        """Returns a tuple where the first item is the value at the
           given identifier, and the second item is a bool which is
           true if the value is an unset default. Raises an
           isc.cc.data.DataNotFoundError if the identifier is bad"""
        value = isc.cc.data.find_no_exc(self.data, identifier)
        if value != None:
            return value, False
        spec = find_spec_part(self.specification.get_config_spec(), identifier)
        if spec and 'item_default' in spec:
            return spec['item_default'], True
        return None, False

    def get_module_spec(self):
        """Returns the ModuleSpec object associated with this ConfigData"""
        return self.specification

    def set_local_config(self, data):
        """Set the non-default config values, as passed by cfgmgr"""
        self.data = data

    def get_local_config(self):
        """Returns the non-default config values in a dict"""
        return self.data;

    def get_item_list(self, identifier = None, recurse = False):
        """Returns a list of strings containing the full identifiers of
           all 'sub'options at the given identifier. If recurse is True,
           it will also add all identifiers of all children, if any"""
        if identifier:
            spec = find_spec_part(self.specification.get_config_spec(), identifier)
            return spec_name_list(spec, identifier + "/")
        return spec_name_list(self.specification.get_config_spec(), "", recurse)

    def get_full_config(self):
        """Returns a dict containing identifier: value elements, for
           all configuration options for this module. If there is
           a local setting, that will be used. Otherwise the value
           will be the default as specified by the module specification.
           If there is no default and no local setting, the value will
           be None"""
        items = self.get_item_list(None, True)
        result = {}
        for item in items:
            value, default = self.get_value(item)
            result[item] = value
        return result

# should we just make a class for these?
def _create_value_map_entry(name, type, value, status = None):
    entry = {}
    entry['name'] = name
    entry['type'] = type
    entry['value'] = value
    entry['modified'] = False
    entry['default'] = False
    if status == MultiConfigData.LOCAL:
        entry['modified'] = True
    if status == MultiConfigData.DEFAULT:
        entry['default'] = True
    return entry

class MultiConfigData:
    """This class stores the module specs, current non-default
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
        """Add or update a ModuleSpec. Raises a ConfigDataError is spec is not a ModuleSpec"""
        if type(spec) != isc.config.ModuleSpec:
            raise ConfigDataError("not a datadef: " + str(type(spec)))
        self._specifications[spec.get_module_name()] = spec

    def remove_specification(self, module_name):
        """Removes the specification with the given module name. Does nothing if it wasn't there."""
        if module_name in self._specifications:
            del self._specifications[module_name]

    def have_specification(self, module_name):
        """Returns True if we have a specification for the module with the given name.
           Returns False if we do not."""
        return module_name in self._specifications

    def get_module_spec(self, module):
        """Returns the ModuleSpec for the module with the given name.
           If there is no such module, it returns None"""
        if module in self._specifications:
            return self._specifications[module]
        else:
            return None

    def find_spec_part(self, identifier):
        """Returns the specification for the item at the given
           identifier, or None if not found. The first part of the
           identifier (up to the first /) is interpreted as the module
           name. Returns None if not found, or if identifier is not a
           string."""
        if type(identifier) != str or identifier == "":
            return None
        if identifier[0] == '/':
            identifier = identifier[1:]
        module, sep, id = identifier.partition("/")
        try:
            return find_spec_part(self._specifications[module].get_config_spec(), id)
        except isc.cc.data.DataNotFoundError as dnfe:
            return None
        except KeyError as ke:
            return None

    # this function should only be called by __request_config
    def _set_current_config(self, config):
        """Replace the full current config values."""
        self._current_config = config

    def get_current_config(self):
        """Returns the current configuration as it is known by the
           configuration manager. It is a dict where the first level is
           the module name, and the value is the config values for
           that module"""
        return self._current_config
        
    def get_local_changes(self):
        """Returns the local config changes, i.e. those that have not
           been committed yet and are not known by the configuration
           manager or the modules."""
        return self._local_changes

    def clear_local_changes(self):
        """Reverts all local changes"""
        self._local_changes = {}

    def get_local_value(self, identifier):
        """Returns a specific local (uncommitted) configuration value,
           as specified by the identifier. If the local changes do not
           contain a new setting for this identifier, or if the
           identifier cannot be found, None is returned. See
           get_value() for a general way to find a configuration value
           """
        return isc.cc.data.find_no_exc(self._local_changes, identifier)
        
    def get_current_value(self, identifier):
        """Returns the current non-default value as known by the
           configuration manager, or None if it is not set.
           See get_value() for a general way to find a configuration
           value
        """
        return isc.cc.data.find_no_exc(self._current_config, identifier)
        
    def get_default_value(self, identifier):
        """Returns the default value for the given identifier as
           specified by the module specification, or None if there is
           no default or the identifier could not be found.
           See get_value() for a general way to find a configuration
           value
        """
        if identifier[0] == '/':
            identifier = identifier[1:]
        module, sep, id = identifier.partition("/")
        try:
            spec = find_spec_part(self._specifications[module].get_config_spec(), id)
            if type(spec) == dict and 'item_default' in spec:
                id, list_indices = isc.cc.data.split_identifier_list_indices(id)
                if list_indices is not None and \
                   type(spec['item_default']) == list:
                    if len(list_indices) == 1:
                        default_list = spec['item_default']
                        index = list_indices[0]
                        if index < len(default_list):
                            return default_list[index]
                        else:
                            return None
                else:
                    return spec['item_default']
            elif type(spec) == list:
                result = {}
                for i in spec:
                    if type(i) == dict and 'item_default' in i:
                        result[i['item_name']] = i['item_default']
                    else:
                        result[i['item_name']] = None
                return result
            else:
                return None
        except isc.cc.data.DataNotFoundError as dnfe:
            return None

    def get_value(self, identifier, default = True):
        """Returns a tuple containing value,status.
           The value contains the configuration value for the given
           identifier. The status reports where this value came from;
           it is one of: LOCAL, CURRENT, DEFAULT or NONE, corresponding
           (local change, current setting, default as specified by the
           specification, or not found at all). Does not check and
           set DEFAULT if the argument 'default' is False (default
           defaults to True)"""
        value = self.get_local_value(identifier)
        if value != None:
            return value, self.LOCAL
        value = self.get_current_value(identifier)
        if value != None:
            return value, self.CURRENT
        if default:
            value = self.get_default_value(identifier)
            if value != None:
                return value, self.DEFAULT
        return None, self.NONE

    def get_value_maps(self, identifier = None):
        """Returns a list of dicts, containing the following values:
           name: name of the entry (string)
           type: string containing the type of the value (or 'module')
           value: value of the entry if it is a string, int, double or bool
           modified: true if the value is a local change
           default: true if the value has been changed
           TODO: use the consts for those last ones
           Throws DataNotFoundError if the identifier is bad
        """
        result = []
        if not identifier:
            # No identifier, so we need the list of current modules
            for module in self._specifications.keys():
                entry = _create_value_map_entry(module, 'module', None)
                result.append(entry)
        else:
            if identifier[0] == '/':
                identifier = identifier[1:]
            module, sep, id = identifier.partition('/')
            spec = self.get_module_spec(module)
            if spec:
                spec_part = find_spec_part(spec.get_config_spec(), id)
                if type(spec_part) == list:
                    # list of items to show
                    for item in spec_part:
                        value, status = self.get_value("/" + identifier\
                                              + "/" + item['item_name'])
                        entry = _create_value_map_entry(item['item_name'],
                                                        item['item_type'],
                                                        value, status)
                        result.append(entry)
                elif type(spec_part) == dict:
                    # Two 'special cases' for easier viewing;
                    # If the item is a map, show the first-level contents
                    #
                    # If the item is a list, show all elements (with index in the name).
                    #
                    item = spec_part
                    if item['item_type'] == 'list':
                        li_spec = item['list_item_spec']
                        value, status =  self.get_value("/" + identifier)
                        if type(value) == list:
                            for list_value in value:
                                result_part2 = _create_value_map_entry(
                                                   li_spec['item_name'],
                                                   li_spec['item_type'],
                                                   list_value)
                                result.append(result_part2)
                        elif value is not None:
                            entry = _create_value_map_entry(
                                        li_spec['item_name'],
                                        li_spec['item_type'],
                                        value, status)
                            result.append(entry)
                    else:
                        value, status = self.get_value("/" + identifier)
                        if value is not None:
                            entry = _create_value_map_entry(
                                        item['item_name'],
                                        item['item_type'],
                                        value, status)
                            result.append(entry)
        return result

    def set_value(self, identifier, value):
        """Set the local value at the given identifier to value. If
           there is a specification for the given identifier, the type
           is checked."""
        spec_part = self.find_spec_part(identifier)
        if spec_part is not None and value is not None:
            id, list_indices = isc.cc.data.split_identifier_list_indices(identifier)
            if list_indices is not None \
               and spec_part['item_type'] == 'list':
                spec_part = spec_part['list_item_spec']
            check_type(spec_part, value)

        # Since we do not support list diffs (yet?), we need to
        # copy the currently set list of items to _local_changes
        # if we want to modify an element in there
        # (for any list indices specified in the full identifier)
        id_parts = isc.cc.data.split_identifier(identifier)
        cur_id_part = '/'
        for id_part in id_parts:
            id, list_indices = isc.cc.data.split_identifier_list_indices(id_part)
            if list_indices is not None:
                cur_list, status = self.get_value(cur_id_part + id)
                if status != MultiConfigData.LOCAL:
                    isc.cc.data.set(self._local_changes,
                                    cur_id_part + id,
                                    cur_list)
            cur_id_part = cur_id_part + id_part + "/"
        isc.cc.data.set(self._local_changes, identifier, value)
 
    def get_config_item_list(self, identifier = None, recurse = False):
        """Returns a list of strings containing the item_names of
           the child items at the given identifier. If no identifier is
           specified, returns a list of module names. The first part of
           the identifier (up to the first /) is interpreted as the
           module name"""
        if identifier and identifier != "/":
            if identifier.startswith("/"):
                identifier = identifier[1:]
            spec = self.find_spec_part(identifier)
            return spec_name_list(spec, identifier + "/", recurse)
        else:
            if recurse:
                id_list = []
                for module in self._specifications.keys():
                    id_list.extend(spec_name_list(self.find_spec_part(module), module, recurse))
                return id_list
            else:
                return list(self._specifications.keys())
