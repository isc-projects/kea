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

# A test plugin. It does mostly nothing, just provides a function we can
# recognize from the test. However, it looks like a real plugin, with the
# (almost) correct interface, even when it's not used.

class MockSpec:
    """Mock spec, contains no data, it can only provide it's name.
       It'll not really be used for anything."""
    def get_module_name(self):
        return "mock_config_plugin"

def mock_check_config(config):
    """Mock function to check config. Does nothing, only returns
       an "error" string to indicate it's this one."""
    return "Mock config plugin"

def load():
    """When a plugin is loaded, this is called to provide the spec and
       checking function."""
    return (MockSpec(), mock_check_config)
