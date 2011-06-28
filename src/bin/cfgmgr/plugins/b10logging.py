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

# This is the configuration plugin for logging options
# The name is 'b10logging' because logging.py is an existing module
#
# For a technical background, see
# http://bind10.isc.org/wiki/LoggingCppApiDesign
#

from isc.config.module_spec import module_spec_from_file
from isc.util.file import path_search
from bind10_config import PLUGIN_PATHS
spec = module_spec_from_file(path_search('logging.spec', PLUGIN_PATHS))

ALLOWED_SEVERITIES = [ 'default',
                       'debug',
                       'info',
                       'warn',
                       'error',
                       'fatal',
                       'none' ]
ALLOWED_DESTINATIONS = [ 'console',
                         'file',
                         'syslog' ]
ALLOWED_STREAMS = [ 'stdout',
                    'stderr' ]

def check(config):
    # Check the data layout first
    errors=[]
    if not spec.validate_config(False, config, errors):
        return ' '.join(errors)
    # The 'layout' is ok, now check for specific values
    if 'loggers' in config:
        for logger in config['loggers']:
            # name should always be present
            name = logger['name']
            # report an error if name starts with * but not *.,
            # or if * is not the first character.
            # TODO: we might want to also warn or error if the
            # logger name is not an existing module, but we can't
            # really tell that from here at this point
            star_pos = name.find('*')
            if star_pos > 0 or\
               name == '*.' or\
               (star_pos == 0 and len(name) > 1 and name[1] != '.'):
                errors.append("Bad logger name: '" + name + "': * can "
                              "only be used instead of the full "
                              "first-level name, e.g. '*' or "
                              "'*.subsystem'")

            if 'severity' in logger and\
               logger['severity'].lower() not in ALLOWED_SEVERITIES:
                errors.append("bad severity value for logger " + name +
                              ": " + logger['severity'])
            if 'output_options' in logger:
                for output_option in logger['output_options']:
                    if 'destination' in output_option:
                        destination = output_option['destination'].lower()
                        if destination not in ALLOWED_DESTINATIONS:
                            errors.append("bad destination for logger " +
                            name + ": " + output_option['destination'])
                        else:
                            # if left to default, output is stdout, and
                            # it will not show in the updated config,
                            # so 1. we only need to check it if present,
                            # and 2. if destination is changed, so should
                            # output. So first check checks 'in', and the
                            # others 'not in' for 'output'
                            if destination == "console" and\
                               'output' in output_option and\
                               output_option['output'] not in ALLOWED_STREAMS:
                                errors.append("bad output for logger " + name +
                                              ": " + output_option['output'] +
                                              ", must be stdout or stderr")
                            elif destination == "file" and\
                                 ('output' not in output_option or\
                                  output_option['output'] == ""):
                                    errors.append("destination set to file but "
                                                  "output not set to any "
                                                  "filename for logger "
                                                  + name)
                            elif destination == "syslog" and\
                                 'output' not in output_option or\
                                 output_option['output'] == "":
                                    errors.append("destination set to syslog but "
                                                  "output not set to any facility"
                                                  " for logger " + name)

    if errors:
        return ', '.join(errors)
    return None

def load():
    return (spec, check)

