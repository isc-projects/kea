# Copyright (C) 2012  Internet Systems Consortium.
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
from bind10_config import PLUGIN_PATHS
import isc.dns
import isc.datasrc
import json
import os.path
import copy

spec = module_spec_from_file(path_search('datasrc.spec', PLUGIN_PATHS))

def check(config):
    """
    Check the configuration.
    """
    # Check the data layout first
    errors=[]
    if not spec.validate_config(False, config, errors):
        return ' '.join(errors)

    classes = config.get('classes')
    # Nothing passed here
    if classes is None:
        return None

    for rr_class_str in classes:
        try:
            rr_class = isc.dns.RRClass(rr_class_str)
        except isc.dns.InvalidRRClass as irc:
            return "The class '" + rr_class_str + "' is invalid"

        dlist = isc.datasrc.ConfigurableClientList(rr_class)
        # We get a copy here, as we are going to mangle the configuration.
        # But we don't want our changes to propagate outside, to the real
        # configuration.
        client_config = copy.deepcopy(classes.get(rr_class_str))

        for client in client_config:
            if client['type'] == 'MasterFiles':
                if not client.get('cache-enable', False):
                    return 'The cache must be enabled in MasterFiles type'
                params = client.get('params')
                if type(params) != dict:
                    return 'Params of MasterFiles must be a named set'
                for name in params:
                    try:
                        isc.dns.Name(name)
                    except Exception as e: # There are many related exceptions
                        return str(e)
                    if not os.path.exists(params[name]):
                        return "Master file " + params[name] + " does not exist"
                # We remove the list of zones locally. We already checked them,
                # and the client list would have skipped them anyway, as we
                # forbid cache. But it would produce a warning and we don't
                # want that here.
                client['params'] = {}

        try:
            dlist.configure(json.dumps(client_config), False)
        except isc.datasrc.Error as dse:
            return str(dse)
    return None

def load():
    return (spec, check)
