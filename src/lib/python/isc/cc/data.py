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
import re

class DataNotFoundError(Exception):
    """Raised if an identifier does not exist according to a spec file,
       or if an item is addressed that is not in the current (or default)
       config (such as a nonexistent list or map element)"""
    pass

class DataAlreadyPresentError(Exception):
    """Raised if there is an attemt to add an element to a list or a
       map that is already present in that list or map (i.e. if 'add'
       is used when it should be 'set')"""
    pass

class DataTypeError(Exception):
    """Raised if there is an attempt to set an element that is of a
       different type than the type specified in the specification."""
    pass

def remove_identical(a, b):
    """Removes the values from dict a that are the same as in dict b.
       Raises a DataTypeError is a or b is not a dict"""
    to_remove = []
    if type(a) != dict or type(b) != dict:
        raise DataTypeError("Not a dict in remove_identical()")
    duplicate_keys = [key for key in a.keys() if key in b and a[key] == b[key]]
    for id in duplicate_keys:
        del(a[id])

def merge(orig, new):
    """Merges the contents of new into orig, think recursive update()
       orig and new must both be dicts. If an element value is None in
       new it will be removed in orig."""
    if type(orig) != dict or type(new) != dict:
        raise DataTypeError("Not a dict in merge()")
    orig.update(new)
    remove_null_items(orig)

def remove_null_items(d):
    """Recursively removes all (key,value) pairs from d where the
       value is None"""
    null_keys = []
    for key in d.keys():
        if type(d[key]) == dict:
            remove_null_items(d[key])
        elif d[key] is None:
            null_keys.append(key)
    for k in null_keys:
        del d[k]

def _concat_identifier(id_parts):
    """Concatenates the given identifier parts into a string,
       delimited with the '/' character.
    """
    return '/'.join(id_parts)

def split_identifier(identifier):
    """Splits the given identifier into a list of identifier parts,
       as delimited by the '/' character.
       Raises a DataTypeError if identifier is not a string."""
    if type(identifier) != str:
        raise DataTypeError("identifier is not a string")
    id_parts = identifier.split('/')
    id_parts[:] = (value for value in id_parts if value != "")
    return id_parts

def identifier_has_list_index(identifier):
    """Returns True if the given identifier string has at least one
       list index (with [I], where I is a number"""
    return (type(identifier) == str and
            re.search("\[\d+\]", identifier) is not None)


def split_identifier_list_indices(identifier):
    """Finds list indexes in the given identifier, which are of the
       format [integer].
       Identifier must be a string.
       This will only give the list index for the last 'part' of the
       given identifier (as delimited by the '/' sign).
       Raises a DataTypeError if the identifier is not a string,
       or if the format is bad.
       Returns a tuple, where the first element is the string part of
       the identifier, and the second element is a list of (nested) list
       indices.
       Examples:
       'a/b/c' will return ('a/b/c', None)
       'a/b/c[1]' will return ('a/b/c', [1])
       'a/b/c[1][2][3]' will return ('a/b/c', [1, 2, 3])
       'a[0]/b[1]/c[2]' will return ('a[0]/b[1]/c', [2])
    """
    if type(identifier) != str:
        raise DataTypeError("identifier in "
                            "split_identifier_list_indices() "
                            "not a string: " + str(identifier))

    # We only work on the final 'part' of the identifier
    id_parts = split_identifier(identifier)
    id_str = id_parts[-1]

    i = id_str.find('[')
    if i < 0:
        if id_str.find(']') >= 0:
            raise DataTypeError("Bad format in identifier (] but no [): " + str(identifier))
        return identifier, None

    # keep the non-index part of that to replace later
    id = id_str[:i]
    indices = []
    while i >= 0:
        e = id_str.find(']')
        if e < i + 1:
            raise DataTypeError("Bad format in identifier (] before [): " + str(identifier))
        try:
            indices.append(int(id_str[i+1:e]))
        except ValueError:
            raise DataTypeError("List index in " + identifier + " not an integer")
        id_str = id_str[e + 1:]
        i = id_str.find('[')
        if i > 0:
            raise DataTypeError("Bad format in identifier ([ within []): " + str(identifier))
    if id.find(']') >= 0 or len(id_str) > 0:
        raise DataTypeError("Bad format in identifier (extra ]): " + str(identifier))

    # we replace the final part of the original identifier with
    # the stripped string
    id_parts[-1] = id
    id = _concat_identifier(id_parts)
    return id, indices

def _find_child_el(element, id):
    """Finds the child of element with the given id. If the id contains
       [i], where i is a number, and the child element is a list, the
       i-th element of that list is returned instead of the list itself.
       Raises a DataTypeError if the element is of wrong type, if id
       is not a string, or if the id string contains a bad value.
       Raises a DataNotFoundError if the element at id could not be
       found.
    """
    id, list_indices = split_identifier_list_indices(id)
    if type(element) == dict and id in element.keys():
        result = element[id]
    else:
        raise DataNotFoundError(id + " in " + str(element))
    if type(result) == list and list_indices is not None:
        for list_index in list_indices:
            if list_index >= len(result):
                raise DataNotFoundError("Element " + str(list_index) + " in " + str(result))
            result = result[list_index]
    return result

def find(element, identifier):
    """Returns the subelement in the given data element, raises
       DataNotFoundError if not found.
       Returns the given element if the identifier is an empty string.
       Raises a DataTypeError if identifier is not a string, or if
       identifier is not empty, and element is not a dict.
    """
    if type(identifier) != str:
        raise DataTypeError("identifier in find() is not a str")
    if identifier == "":
        return element
    if type(element) != dict:
        raise DataTypeError("element in find() is not a dict")
    id_parts = split_identifier(identifier)
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
    if type(identifier) != str:
        raise DataTypeError("identifier in set() is not a str")
    id_parts = split_identifier(identifier)
    cur_el = element
    for id in id_parts[:-1]:
        try:
            cur_el = _find_child_el(cur_el, id)
        except DataNotFoundError:
            if value is None:
                # ok we are unsetting a value that wasn't set in
                # the first place. Simply stop.
                return
            cur_el[id] = {}
            cur_el = cur_el[id]

    id, list_indices = split_identifier_list_indices(id_parts[-1])
    if list_indices is None:
        # value can be an empty list or dict, so check for None explicitly
        if value is not None:
            cur_el[id] = value
        else:
            del cur_el[id]
    else:
        cur_el = cur_el[id]
        # in case of nested lists, we need to get to the next to last
        for list_index in list_indices[:-1]:
            if type(cur_el) != list:
                raise DataTypeError("Element at " + identifier + " is not a list")
            if len(cur_el) <= list_index:
                raise DataNotFoundError("List index at " + identifier + " out of range")
            cur_el = cur_el[list_index]
        # value can be an empty list or dict, so check for None explicitly
        list_index = list_indices[-1]
        if type(cur_el) != list:
            raise DataTypeError("Element at " + identifier + " is not a list")
        if len(cur_el) <= list_index:
            raise DataNotFoundError("List index at " + identifier + " out of range")
        if value is not None:
            cur_el[list_index] = value
        else:
            del cur_el[list_index]
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

