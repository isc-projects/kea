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
spec = module_spec_from_file(path_search('datasrc.spec', PLUGIN_PATHS))

def check(config):
    """
    Check the configuration.
    """
    # Check the data layout first
    errors=[]
    if not spec.validate_config(False, config, errors):
        return ' '.join(errors)
    # TODO: Once we have solved ticket #2051, create the list and
    # fill it with the configuration. We probably want to have some way
    # to not load the data sources, just the configuration. It could
    # be hacked together by subclassing ConfigurableClientList and
    # having empty getDataSource method. But it looks like a hack and it
    # won't really check the params configuration.
    #
    # For now, we let everything pass.
    return None

def load():
    return (spec, check)
