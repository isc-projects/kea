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
import copy

class ConfigDataError(Exception): pass

BIND10_CONFIG_DATA_VERSION = 2

# Helper functions
def spec_part_is_list(spec_part):
    """Returns True if the given spec_part is a dict that contains a
       list specification, and False otherwise."""
    return (type(spec_part) == dict and 'list_item_spec' in spec_part)

def spec_part_is_map(spec_part):
    """Returns True if the given spec_part is a dict that contains a
       map specification, and False otherwise."""
    return (type(spec_part) == dict and 'map_item_spec' in spec_part)

def spec_part_is_named_set(spec_part):
    """Returns True if the given spec_part is a dict that contains a
       named_set specification, and False otherwise."""
    return (type(spec_part) == dict and 'named_set_item_spec' in spec_part)

def spec_part_is_any(spec_part):
    """Returns true if the given spec_part specifies an element of type
       any, and False otherwise.
    """
    return (type(spec_part) == dict and 'item_type' in spec_part and
            spec_part['item_type'] == "any")

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
            try:
                map = ast.literal_eval(value)
                if type(map) == dict:
                    # todo: check types of map contents too
                    return map
                else:
                    raise isc.cc.data.DataTypeError(
                               "Value in convert_type not a string "
                               "specifying a dict")
            except SyntaxError as se:
                raise isc.cc.data.DataTypeError("Error parsing map: " + str(se))
        else:
            return value
    except ValueError as err:
        raise isc.cc.data.DataTypeError(str(err))
    except TypeError as err:
        raise isc.cc.data.DataTypeError(str(err))

def _get_map_or_list(spec_part):
    """Returns the list or map specification if this is a list or a
       map specification part. If not, returns the given spec_part
       itself"""
    if spec_part_is_map(spec_part):
        return spec_part["map_item_spec"]
    elif spec_part_is_list(spec_part):
        return spec_part["list_item_spec"]
    else:
        return spec_part

def _find_spec_part_single(cur_spec, id_part):
    """Find the spec part for the given (partial) name. This partial
       name does not contain separators ('/'), and the specification
       part should be a direct child of the given specification part.
       id_part may contain list selectors, which will be ignored.
       Returns the child part.
       Raises DataNotFoundError if it was not found."""
    # strip list selector part
    # don't need it for the spec part, so just drop it
    id, list_indices = isc.cc.data.split_identifier_list_indices(id_part)

    # The specification we want a sub-part for should be either a
    # list or a map, which is internally represented by a dict with
    # an element 'map_item_spec', a dict with an element 'list_item_spec',
    # or a list (when it is the 'main' config_data element of a module).
    if spec_part_is_map(cur_spec):
        for cur_spec_item in cur_spec['map_item_spec']:
            if cur_spec_item['item_name'] == id:
                return cur_spec_item
        # not found
        raise isc.cc.data.DataNotFoundError(id + " not found")
    elif spec_part_is_list(cur_spec):
        if cur_spec['item_name'] == id:
            return cur_spec['list_item_spec']
        # not found
        raise isc.cc.data.DataNotFoundError(id + " not found")
    elif type(cur_spec) == dict and 'named_set_item_spec' in cur_spec.keys():
        return cur_spec['named_set_item_spec']
    elif type(cur_spec) == list:
        for cur_spec_item in cur_spec:
            if cur_spec_item['item_name'] == id:
                return cur_spec_item
        # not found
        raise isc.cc.data.DataNotFoundError(id + " not found")
    else:
        raise isc.cc.data.DataNotFoundError("Not a correct config specification")

def find_spec_part(element, identifier, strict_identifier = True):
    """find the data definition for the given identifier
       returns either a map with 'item_name' etc, or a list of those
       Parameters:
       element: The specification element to start the search in
       identifier: The element to find (relative to element above)
       strict_identifier: If True (the default), additional checking occurs.
                          Currently the only check is whether a list index is
                          specified (except for the last part of the
                          identifier)
       Raises a DataNotFoundError if the data is not found, or if
       strict_identifier is True and any non-final identifier parts
       (i.e. before the last /) identify a list element and do not contain
       an index.
       Returns the spec element identified by the given identifier.
    """
    if identifier == "":
        return element
    id_parts = identifier.split("/")
    id_parts[:] = (value for value in id_parts if value != "")
    cur_el = element

    # up to the last element, if the result is a map or a list,
    # we want its subspecification (i.e. list_item_spec or
    # map_item_spec). For the last element in the identifier we
    # always want the 'full' spec of the item
    for id_part in id_parts[:-1]:
        cur_el = _find_spec_part_single(cur_el, id_part)
        # As soon as we find 'any', return that
        if cur_el["item_type"] == "any":
            return cur_el
        if strict_identifier and spec_part_is_list(cur_el) and\
           not isc.cc.data.identifier_has_list_index(id_part):
            raise isc.cc.data.DataNotFoundError(id_part +
                                                " is a list and needs an index")
        cur_el = _get_map_or_list(cur_el)

    cur_el = _find_spec_part_single(cur_el, id_parts[-1])
    # Due to the raw datatypes we use, it is safer to return a deep copy here
    return copy.deepcopy(cur_el)

def spec_name_list(spec, prefix="", recurse=False):
    """Returns a full list of all possible item identifiers in the
       specification (part). Raises a ConfigDataError if spec is not
       a correct spec (as returned by ModuleSpec.get_config_spec()"""
    result = []
    if prefix != "" and not prefix.endswith("/"):
        prefix += "/"
    if type(spec) == dict:
        if spec_part_is_map(spec):
            for map_el in spec['map_item_spec']:
                name = map_el['item_name']
                if map_el['item_type'] == 'map':
                    name += "/"
                if recurse and spec_part_is_map(map_el):
                    result.extend(spec_name_list(map_el['map_item_spec'], prefix + map_el['item_name'], recurse))
                else:
                    result.append(prefix + name)
        elif 'named_set_item_spec' in spec:
            # we added a '/' above, but in this one case we don't want it
            result.append(prefix[:-1])
        # ignore any
        elif not spec_part_is_any(spec):
            for name in spec:
                result.append(prefix + name + "/")
                if recurse:
                    result.extend(spec_name_list(spec[name], name, recurse))
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
        raise ConfigDataError("Bad specification")
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

    def get_default_value(self, identifier):
        """Returns the default from the specification, or None if there
           is no default"""
        # We are searching for the default value, so we can set
        # strict_identifier to false (in fact, we need to; we may not know
        # some list indices, or they may not exist, we are looking for
        # a default value for a reason here).
        spec = find_spec_part(self.specification.get_config_spec(),
                              identifier, False)
        if spec and 'item_default' in spec:
            return spec['item_default']
        else:
            return None

    def get_module_spec(self):
        """Returns the ModuleSpec object associated with this ConfigData"""
        return self.specification

    def set_local_config(self, data):
        """Set the non-default config values, as passed by cfgmgr"""
        self.data = data

    def get_local_config(self):
        """Returns the non-default config values in a dict"""
        return self.data

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

    def clear_specifications(self):
        """Remove all known module specifications"""
        self._specifications = {}

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
           string.
           If an index is given for a List-type element, it returns
           the specification of the list elements, not of the list itself
           """
        if type(identifier) != str or identifier == "":
            return None
        if identifier[0] == '/':
            identifier = identifier[1:]
        module, sep, id = identifier.partition("/")
        if id != "":
            id, indices = isc.cc.data.split_identifier_list_indices(id)
        else:
            indices = None
        try:
            spec_part = find_spec_part(self._specifications[module].get_config_spec(), id)
            if indices is not None and spec_part_is_list(spec_part):
                return spec_part['list_item_spec']
            else:
                return spec_part
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

    def set_local_changes(self, new_local_changes):
        """Sets the entire set of local changes, used when reverting
           changes done automatically in case there was a problem (e.g.
           when executing commands from a script that fails halfway
           through).
        """
        self._local_changes = new_local_changes

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
        try:
            if identifier[0] == '/':
                identifier = identifier[1:]
            module, sep, id = identifier.partition("/")
            # if there is a 'higher-level' list index specified, we need
            # to check if that list specification has a default that
            # overrides the more specific default in the final spec item
            # (ie. list_default = [1, 2, 3], list_item_spec=int, default=0)
            # def default list[1] should return 2, not 0
            id_parts = isc.cc.data.split_identifier(id)
            id_prefix = ""
            while len(id_parts) > 0:
                id_part = id_parts.pop(0)
                item_id, list_indices = isc.cc.data.split_identifier_list_indices(id_part)
                id_list = module + "/" + id_prefix + "/" + item_id
                id_prefix += "/" + id_part
                part_spec = find_spec_part(self._specifications[module].get_config_spec(), id_prefix)
                if part_spec['item_type'] == 'named_set':
                    # For named sets, the identifier is partly defined
                    # by which values are actually present, and not
                    # purely by the specification.
                    # So if there is a part of the identifier left,
                    # we need to look up the value, then see if that
                    # contains the next part of the identifier we got
                    if len(id_parts) == 0:
                        if 'item_default' in part_spec:
                            return part_spec['item_default']
                        else:
                            return None
                    id_part = id_parts.pop(0)
                    item_id, list_indices =\
                        isc.cc.data.split_identifier_list_indices(id_part)

                    named_set_value, type = self.get_value(id_list)
                    if item_id in named_set_value.keys():
                        result = named_set_value[item_id]
                        # If the item is a list and we have indices in the
                        # identifier part, continue with the item pointed to
                        # by those indices
                        if list_indices is not None:
                            while len(list_indices) > 0:
                                result = result[list_indices.pop(0)]

                        if len(id_parts) > 0:
                            # we are looking for the *default* value.
                            # so if not present in here, we need to
                            # lookup the one from the spec
                            rest_of_id = "/".join(id_parts)
                            result = isc.cc.data.find_no_exc(result, rest_of_id)
                            if result is None:
                                spec_part = self.find_spec_part(identifier)
                                if 'item_default' in spec_part:
                                    return spec_part['item_default']
                            return result
                        else:
                            return result
                    else:
                        return None
                elif list_indices is not None:
                    # there's actually two kinds of default here for
                    # lists; they can have a default value (like an
                    # empty list), but their elements can  also have
                    # default values.
                    # So if the list item *itself* is a default,
                    # we need to get the value out of that. If not, we
                    # need to find the default for the specific element.
                    list_value, type = self.get_value(id_list)
                    list_spec = find_spec_part(self._specifications[module].get_config_spec(), id_prefix)
                    if type == self.DEFAULT:
                        if 'item_default' in list_spec:
                            list_value = list_spec['item_default']
                            for i in list_indices:
                                if i < len(list_value):
                                    list_value = list_value[i]
                                else:
                                    # out of range, return None
                                    return None

                            if len(id_parts) > 0:
                                rest_of_id = "/".join(id_parts)
                                return isc.cc.data.find(list_value, rest_of_id)
                            else:
                                return list_value
                    else:
                        # we do have a non-default list, see if our indices
                        # exist
                        for i in list_indices:
                            if i < len(list_value):
                                list_value = list_value[i]
                            else:
                                # out of range, return None
                                return None

            spec = find_spec_part(self._specifications[module].get_config_spec(), id)
            if 'item_default' in spec:
                # one special case, named_set
                if spec['item_type'] == 'named_set':
                    return spec['item_default']
                else:
                    return spec['item_default']
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
            if value is not None:
                return value, self.DEFAULT
            else:
                # get_default_value returns None for both
                # the cases where there is no default, and where
                # it is set to null, so we need to catch the latter
                spec_part = self.find_spec_part(identifier)
                if spec_part and 'item_default' in spec_part and\
                   spec_part['item_default'] is None:
                    return None, self.DEFAULT
        return None, self.NONE

    def _append_value_item(self, result, spec_part, identifier, all, first = False):
        # Look at the spec; it is a list of items, or a map containing 'item_name' etc
        if type(spec_part) == list:
            for spec_part_element in spec_part:
                spec_part_element_name = spec_part_element['item_name']
                self._append_value_item(result, spec_part_element, identifier + "/" + spec_part_element_name, all)
        elif type(spec_part) == dict:
            # depending on item type, and the value of argument 'all'
            # we need to either add an item, or recursively go on
            # In the case of a list that is empty, we do need to show that
            item_name = spec_part['item_name']
            item_type = spec_part['item_type']
            if item_type == "list" and (all or first):
                spec_part_list = spec_part['list_item_spec']
                list_value, status = self.get_value(identifier)
                # If not set, and no default, lists will show up as 'None',
                # but it's better to treat it as an empty list then
                if list_value is None:
                    list_value = []

                if type(list_value) != list:
                    # the identifier specified a single element
                    self._append_value_item(result, spec_part_list, identifier, all)
                else:
                    list_len = len(list_value)
                    if len(list_value) == 0 and (all or first):
                        entry = _create_value_map_entry(identifier,
                                                        item_type,
                                                        [], status)
                        result.append(entry)
                    else:
                        for i in range(len(list_value)):
                            self._append_value_item(result, spec_part_list, "%s[%d]" % (identifier, i), all)
            elif item_type == "map":
                value, status = self.get_value(identifier)
                # just show the specific contents of a map, we are
                # almost never interested in just its name
                spec_part_map = spec_part['map_item_spec']
                self._append_value_item(result, spec_part_map, identifier, all)
            elif item_type == "named_set":
                value, status = self.get_value(identifier)

                # show just the one entry, when either the map is empty,
                # or when this is element is not requested specifically
                if len(value.keys()) == 0:
                    entry = _create_value_map_entry(identifier,
                                                    item_type,
                                                    {}, status)
                    result.append(entry)
                elif not first and not all:
                    entry = _create_value_map_entry(identifier,
                                                    item_type,
                                                    None, status)
                    result.append(entry)
                else:
                    spec_part_named_set = spec_part['named_set_item_spec']
                    for entry in value:
                        self._append_value_item(result,
                                                spec_part_named_set,
                                                identifier + "/" + entry,
                                                all)
            else:
                value, status = self.get_value(identifier)
                if status == self.NONE and not spec_part['item_optional']:
                    raise isc.cc.data.DataNotFoundError(identifier + " not found")

                entry = _create_value_map_entry(identifier,
                                                item_type,
                                                value, status)
                result.append(entry)
        return


    def get_value_maps(self, identifier = None, all = False):
        """Returns a list of dicts, containing the following values:
           name: name of the entry (string)
           type: string containing the type of the value (or 'module')
           value: value of the entry if it is a string, int, double or bool
           modified: true if the value is a local change that has not
                     been committed
           default: true if the value has not been changed (i.e. the
                    value is the default from the specification)
           TODO: use the consts for those last ones
           Throws DataNotFoundError if the identifier is bad
        """
        result = []
        if not identifier or identifier == "/":
            # No identifier, so we need the list of current modules
            for module in self._specifications.keys():
                if all:
                    spec = self.get_module_spec(module)
                    if spec:
                        spec_part = spec.get_config_spec()
                        self._append_value_item(result, spec_part, module, all, True)
                else:
                    entry = _create_value_map_entry(module, 'module', None)
                    result.append(entry)
        else:
            # Strip off start and end slashes, if they are there
            if len(identifier) > 0 and identifier[0] == '/':
                identifier = identifier[1:]
            if len(identifier) > 0 and identifier[-1] == '/':
                identifier = identifier[:-1]
            module, sep, id = identifier.partition('/')
            spec = self.get_module_spec(module)
            if spec:
                spec_part = find_spec_part(spec.get_config_spec(), id)
                self._append_value_item(result, spec_part, identifier, all, True)
        return result

    def unset(self, identifier):
        """
        Reset the value to default.
        """
        spec_part = self.find_spec_part(identifier)
        if spec_part is not None:
            isc.cc.data.unset(self._local_changes, identifier)
        else:
            raise isc.cc.data.DataNotFoundError(identifier + "not found")

    def set_value(self, identifier, value):
        """Set the local value at the given identifier to value. If
           there is a specification for the given identifier, the type
           is checked."""
        spec_part = self.find_spec_part(identifier)
        if spec_part is not None:
            if value is not None:
                id, list_indices = isc.cc.data.split_identifier_list_indices(identifier)
                if list_indices is not None \
                   and spec_part['item_type'] == 'list':
                    spec_part = spec_part['list_item_spec']
                check_type(spec_part, value)
        else:
            raise isc.cc.data.DataNotFoundError(identifier + " not found")

        # Since we do not support list diffs (yet?), we need to
        # copy the currently set list of items to _local_changes
        # if we want to modify an element in there
        # (for any list indices specified in the full identifier)
        id_parts = isc.cc.data.split_identifier(identifier)
        cur_id_part = '/'
        for id_part in id_parts:
            id, list_indices = isc.cc.data.split_identifier_list_indices(id_part)
            cur_value, status = self.get_value(cur_id_part + id)
            # Check if the value was there in the first place
            # If we are at the final element, we do not care whether we found
            # it, since if we have reached this point and it did not exist,
            # it was apparently an optional value without a default.
            if status == MultiConfigData.NONE and cur_id_part != "/" and\
               cur_id_part + id != identifier:
                raise isc.cc.data.DataNotFoundError(id_part +
                                                    " not found in " +
                                                    cur_id_part)
            if list_indices is not None:
                # And check if we don't set something outside of any
                # list
                cur_list = cur_value
                for list_index in list_indices:
                    if type(cur_list) != list:
                        raise isc.cc.data.DataTypeError(id + " is not a list")
                    if list_index >= len(cur_list):
                        raise isc.cc.data.DataNotFoundError("No item " +
                                  str(list_index) + " in " + id_part)
                    else:
                        cur_list = cur_list[list_index]
                if status != MultiConfigData.LOCAL:
                    isc.cc.data.set(self._local_changes,
                                    cur_id_part + id,
                                    cur_value)
            cur_id_part = cur_id_part + id_part + "/"

            # We also need to copy to local if we are changing a named set,
            # so that the other items in the set do not disappear
            if spec_part_is_named_set(self.find_spec_part(cur_id_part)):
                ns_value, ns_status = self.get_value(cur_id_part)
                if ns_status != MultiConfigData.LOCAL:
                    isc.cc.data.set(self._local_changes,
                                    cur_id_part,
                                    ns_value)
        isc.cc.data.set(self._local_changes, identifier, value)

    def _get_list_items(self, item_name):
        """This method is used in get_config_item_list, to add list
           indices and named_set names to the completion list. If
           the given item_name is for a list or named_set, it'll
           return a list of those (appended to item_name), otherwise
           the list will only contain the item_name itself.

           If the item is a named set, and it's contents are maps
           or named_sets as well, a / is appended to the result
           strings.

           If the item is a list, this method is then called recursively
           for each list entry.

           This behaviour is slightly arbitrary, and currently reflects
           the most probable way the resulting data should look like;
           for lists, bindctl would always expect their contents to
           be added as well. For named_sets, however, we do not
           do recursion, since the resulting list may be too long.
           This will probably change in a revision of the way this
           data is handled; ideally, the result should always recurse,
           but only up to a limited depth, and the resulting list
           should probably be paginated clientside.

           Parameters:
           item_name (string): the (full) identifier for the list or
                               named_set to enumerate.

           Returns a list of strings with item names

           Examples:
           _get_list_items("Module/some_item")
               where item is not a list of a named_set, or where
               said list or named set is empty, returns
               ["Module/some_item"]
           _get_list_items("Module/named_set")
               where the named_set contains items with names 'a'
               and 'b', returns
               [ "Module/named_set/a", "Module/named_set/b" ]
           _get_list_items("Module/named_set_of_maps")
               where the named_set contains items with names 'a'
               and 'b', and those items are maps themselves
               (or other named_sets), returns
               [ "Module/named_set/a/", "Module/named_set/b/" ]
           _get_list_items("Module/list")
               where the list contains 2 elements, returns
               [ "Module/list[0]", "Module/list[1]" ]
           _get_list_items("Module/list")
               where the list contains 2 elements, returns
               [ "Module/list[0]", "Module/list[1]" ]
        """
        spec_part = self.find_spec_part(item_name)
        if spec_part_is_named_set(spec_part):
            values, status = self.get_value(item_name)
            if values is not None and len(values) > 0:
                subslash = ""
                if spec_part['named_set_item_spec']['item_type'] == 'map' or\
                   spec_part['named_set_item_spec']['item_type'] == 'named_set':
                    subslash = "/"
                # Don't recurse for named_sets (so as not to return too
                # much data), but do add a / so the client so that
                # the user can immediately tab-complete further if needed.
                return [ item_name + "/" + v + subslash for v in values.keys() ]
            else:
                return [ item_name ]
        elif spec_part_is_list(spec_part):
            values, status = self.get_value(item_name)
            if values is not None and len(values) > 0:
                result = []
                for i in range(len(values)):
                    name = item_name + '[%d]' % i
                    # Recurse for list entries, so that its sub-contents
                    # are also added to the result
                    result.extend(self._get_list_items(name))
                return result
            else:
                return [ item_name ]
        else:
            return [ item_name ]

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
            spec_list = spec_name_list(spec, identifier + "/", recurse)
            result_list = []
            for spec_name in spec_list:
                result_list.extend(self._get_list_items(spec_name))
            return result_list
        else:
            if recurse:
                id_list = []
                for module in self._specifications.keys():
                    id_list.extend(spec_name_list(self.find_spec_part(module), module, recurse))
                return id_list
            else:
                return list(self._specifications.keys())
