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

def _split_identifier(identifier):
    if type(identifier) != str:
        raise DataTypeError("identifier is not a string")
    id_parts = identifier.split("/")
    id_parts[:] = (value for value in id_parts if value != "")
    return id_parts

def _find_child_el(element, id):
    """Finds the child of element with the given id. If the id contains
       [i], where i is a number, and the child element is a list, the
       i-th element of that list is returned instead of the list itself.
       Raises a DataTypeError if the element is of wrong type, if id
       is not a string, or if the id string contains a bad value.
       Raises a DataNotFoundError if the element at id could not be
       found.
    """
    i = id.find('[')
    e = id.find(']')
    list_index = None
    if i >= 0 and e > i + 1:
        try:
            list_index = int(id[i + 1:e])
        except ValueError as ve:
            # repack as datatypeerror
            raise DataTypeError(ve)
        id = id[:i]
    if type(element) == dict and id in element.keys():
        result = element[id]
    else:
        raise DataNotFoundError(id + " in " + str(element))
    if type(result) == list and list_index is not None:
        print("[XX] GETTING ELEMENT NUMBER " + str(list_index) + " (of " + str(len(result)) + ")")
        if list_index >= len(result):
            print("[XX] OUT OF RANGE")
            raise DataNotFoundError("Element " + str(list_index) + " in " + str(result))
        result = result[list_index]
    return result

def find(element, identifier):
    """Returns the subelement in the given data element, raises DataNotFoundError if not found"""
    if (type(element) != dict and identifier != ""):
        raise DataTypeError("element in find() is not a dict")
    id_parts = _split_identifier(identifier)
    cur_el = element
    for id in id_parts:
        cur_el = _find_child_el(cur_el, id)
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
    print("[XX] full identifier: " + identifier)
    id_parts = _split_identifier(identifier)
    cur_el = element
    print("[XX] Full element:")
    print(element)
    for id in id_parts[:-1]:
        try:
            print("[XX] find " + id)
            cur_el = _find_child_el(cur_el, id)
        except DataNotFoundError:
            print("[XX] DNF for " + id)
            if value is None:
                # ok we are unsetting a value that wasn't set in
                # the first place. Simply stop.
                return
            cur_el[id] = {}
            cur_el = cur_el[id]

    # value can be an empty list or dict, so check for None eplicitely
    print("[XX] Current value: " + str(cur_el))
    if value is not None:
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
    try:
        return find(element, identifier)
    except DataNotFoundError:
        return None
    except DataTypeError:
        return None

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

