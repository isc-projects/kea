# Copyright (C) 2009  Internet Systems Consortium.
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
# This class holds the data definition and validates data agains that
# definition. It is the python equivalent of data_def.h
#
import ast

# file objects are passed around as _io.TextIOWrapper objects
# import that so we can check those types
import _io

class DataDefinitionError(Exception):
    pass

class DataDefinition:
    def __init__(self, spec_file, check = True):
        if type(spec_file) == _io.TextIOWrapper:
            self._data_spec = __read_data_spec_file(spec_file)
        elif type(spec_file) == str:
            file = open(spec_file)
            self._data_spec = self.__readDataSpecFile(file)
            file.close()
        else:
            raise DataDefinitionError("Not a str or file-like object")

    def validate(self, data):
        """Check whether the given piece of data conforms to this
           data definition"""
        # "TODO"
        return True

    def __readDataSpecFile(self, file, check = True):
        """Reads the data spec from the given file object.
           If check is True, check whether it is of the correct form.
           If it is not, an DataDefinitionError exception is raised"""
        if type(file) != _io.TextIOWrapper:
            raise DataDefinitionError("Not a file-like object:" + str(type(file)))
        str = file.read()
        # TODO catch error here and reraise as a less ugly exception
        data_spec = ast.literal_eval(str)
        if check:
            # TODO
            _check(data_spec)
            pass
        return data_spec

    def getDefinition(self):
        return self._data_spec

def _check(data_spec):
    if "data_specification" not in data_spec:
        raise DataDefinitionError("no data_specification element in specification")
    if "config_data" in data_spec:
        _check_config_spec(data_spec["config_data"])
    if "commands" in data_spec:
        _check_config_spec(data_spec["commands"])

def _checkConfigSpec(config_data):
    # TODO
    pass

def _checkCommandSpec(commands):
    # TODO
    pass
