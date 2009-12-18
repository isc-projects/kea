# data, data_definition, config_data, module_config_data and ui_config_data classes
# we might want to split these up :)
import ast

class DataNotFoundError(Exception): pass
class DataTypeError(Exception): pass

def find(element, identifier):
    """Returns the subelement in the given data element, raises DataNotFoundError if not found"""
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
    id_parts = identifier.split("/")
    id_parts[:] = (value for value in id_parts if value != "")
    cur_el = element
    for id in id_parts[:-1]:
        if id in cur_el.keys():
            cur_el = cur_el[id]
        else:
            cur_el[id] = {}
            cur_el = cur_el[id]
    cur_el[id_parts[-1]] = value
    return element

def unset(element, identifier):
    id_parts = identifier.split("/")
    id_parts[:] = (value for value in id_parts if value != "")
    cur_el = element
    for id in id_parts[:-1]:
        if id in cur_el.keys():
            cur_el = cur_el[id]
        else:
            cur_el[id] = {}
            cur_el = cur_el[id]
    cur_el[id_parts[-1]] = None
    return element

def find_no_exc(element, identifier):
    """Returns the subelement in the given data element, returns None if not found"""
    id_parts = identifier.split("/")
    id_parts[:] = (value for value in id_parts if value != "")
    cur_el = element
    for id in id_parts:
        if type(cur_el) == dict and id in cur_el.keys():
            cur_el = cur_el[id]
        else:
            return None
    return cur_el

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
    try:
        return ast.literal_eval(value_str)
    except ValueError as ve:
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
    def __init__(self, name, cc):
        self.module_name = name
        data_spec = self.get_data_specification(cc)
        self.config = ConfigData(data_spec)
        self.get_config_data(cc)
        self.config_changes = {}
    
    def get_config_data(self, cc):
        cc.group_sendmsg({ "command": ["get_config", self.module_name] }, "ConfigManager")
        answer, env = cc.group_recvmsg(False)
        if 'result' in answer.keys() and type(answer['result']) == list:
            # TODO: with the new cc implementation, replace "1" by 1
            if answer['result'][0] == "1":
                # todo: exception
                print("Error: " + str(answer['result'][1]))
            else:
                self.config.data = answer['result'][1]
        else:
            # XX todo: raise exc
            print("Error: unexpected answer from config manager:")
            print(answer)

    def send_changes(self, cc):
        """Sends the changes configuration values to the config manager.
           If the command succeeds, the changes are re-requested and
           the changed list is reset"""
        if self.module_name and self.module_name != "":
            cc.group_sendmsg({ "command": [ "set_config", self.module_name, self.config_changes ]}, "ConfigManager")
        else:
            cc.group_sendmsg({ "command": [ "set_config", self.config_changes ]}, "ConfigManager")
        answer, env = cc.group_recvmsg(False)
        if 'result' in answer and type(answer['result']) == list:
            # TODO: with the new cc implementation, replace "0" by 0
            if answer['result'][0] == "0":
                # ok
                self.get_config_data(cc)
                self.config_changes = {}
            else:
                print("Error committing changes: " + answer['result'][1])
        else:
            print("Error: unexpected answer: " + str(answer))
    
    def get_data_specification(self, cc):
        cc.group_sendmsg({ "command": ["get_data_spec", self.module_name] }, "ConfigManager")
        answer, env = cc.group_recvmsg(False)
        if 'result' in answer.keys() and type(answer['result']) == list:
            # TODO: with the new cc implementation, replace "1" by 1
            if answer['result'][0] == "1":
                # todo: exception
                print("Error: " + str(answer['result'][1]))
                return None
            else:
                return answer['result'][1]
        else:
            # XX todo: raise exc
            print("Error: unexpected answer from config manager:")
            print(answer)
        return None

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

    def commit(self, cc):
        self.send_changes(cc)
