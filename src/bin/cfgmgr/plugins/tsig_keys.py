# Copyright (C) 2011  Internet Systems Consortium.
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

from isc.config.module_spec import module_spec_from_file
from isc.util.file import path_search
from pydnspp import TSIGKey, InvalidParameter
from bind10_config import PLUGIN_PATHS
spec = module_spec_from_file(path_search('tsig_keys.spec', PLUGIN_PATHS))

def check(config):
    # Check the data layout first
    errors=[]
    if not spec.validate_config(False, config, errors):
        return ' '.join(errors)
    # Get the list of keys, if any
    keys = config.get('keys', [])
    # Run trough them, check they can be constructed and there are no dupes
    keyNames = set()
    for key in keys:
        try:
            name = str(TSIGKey(key).get_key_name())
        except InvalidParameter as e:
            return "TSIG: " + str(e)
        if name in keyNames:
            return "Multiple TSIG keys with name '" + name + "'"
        keyNames.add(name)
    # No error found, so let's assume it's OK
    return None

def load():
    return (spec, check)
