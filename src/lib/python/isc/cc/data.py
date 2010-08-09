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

import json

class DataNotFoundError(Exception): pass
class DataTypeError(Exception): pass

def remove_identical(a, b):
    """Removes the values from dict a that are the same as in dict b.
       Raises a DataTypeError is a or b is not a dict"""
    to_remove = []
    if type(a) != dict or type(b) != dict:
        raise DataTypeError("Not a dict in remove_identical()")
    for ka in a.keys():
        if ka in b and a[ka] == b[ka]:
            to_remove.append(ka)
    for id in to_remove:
        del(a[id])

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
            if value == None:
                # ok we are unsetting a value that wasn't set in
                # the first place. Simply stop.
                return
            cur_el[id] = {}
            cur_el = cur_el[id]
    # value can be an empty list or dict, so check for None eplicitely
    if value != None:
        cur_el[id_parts[-1]] = value
    elif id_parts[-1] in cur_el:
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

def parse_value_str(value_str):
    """Parses the given string to a native python object. If the
       string cannot be parsed, it is returned. If it is not a string,
       None is returned"""
    if type(value_str) != str:
        return None
    try:
        return json.loads(value_str)
    except ValueError as ve:
        # simply return the string itself
        return value_str
    except SyntaxError as ve:
        # simply return the string itself
        return value_str

