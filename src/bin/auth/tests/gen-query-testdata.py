#!/usr/bin/env python3

# Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
#
# Permission to use, copy, modify, and/or distribute this software for any
# purpose with or without fee is hereby granted, provided that the above
# copyright notice and this permission notice appear in all copies.
#
# THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
# REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
# AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
# INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
# LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
# OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
# PERFORMANCE OF THIS SOFTWARE.

"""\
This is a supplemental script to generate various forms of test data
from a unified source file.

Usage: python gen-query-testdata.py source_file output-zonefile output--cc-file

The usage doesn't matter much, though, because it's expected to be invoked
from Makefile, and that would be only use case of this script.
"""

import sys
import re

# Skip lines starting with '##' (comments) or empty lines
re_skip = re.compile('(^##)|(^\s*$)')

# Markup for variable definition
re_start_rr = re.compile('^#var=(.*)')

def parse_input(input_file):
    '''Build an internal list of RR data from the input source file.

    It generates a list of (variable_name, list of RR) tuples, where
    variable_name is the expected C++ variable name for the subsequent RRs
    if they are expected to be named.  It can be an empty string if the RRs
    are only expected to appear in the zone file.
    The second element of the tuple is a list of strings, each of which
    represents a single RR, e.g., "example.com 3600 IN A 192.0.2.1".

    '''
    result = []
    rrs = None
    with open(input_file) as f:
        for line in f:
            if re_skip.match(line):
                continue
            m = re_start_rr.match(line)
            if m:
                if rrs is not None:
                    result.append((rr_varname, rrs))
                rrs = []
                rr_varname = m.group(1)
            else:
                rrs.append(line.rstrip('\n'))

        # if needed, store the last RRs (they are not followed by 'var=' mark)
        if rrs is not None:
            result.append((rr_varname, rrs))

    return result

def generate_variables(out_file, rrsets_data):
    '''Generate a C++ source file containing a C-string variables for RRs.

    This produces a definition of C-string for each RRset that is expected
    to be named as follows:
    const char* const var_name =
        "example.com. 3600 IN A 192.0.2.1\n"
        "example.com. 3600 IN A 192.0.2.2\n";

    Escape character '\' in the string will be further escaped so it will
    compile.

    '''
    with open(out_file, 'w') as out:
        for (var_name, rrs) in rrsets_data:
            if len(var_name) > 0:
                out.write('const char* const ' + var_name + ' =\n')
                # Combine all RRs, escaping '\' as a C-string
                out.write('\n'.join(['    \"%s\\n\"' %
                                     (rr.replace('\\', '\\\\'))
                                     for rr in rrs]))
                out.write(';\n')

def generate_zonefile(out_file, rrsets_data):
    '''Generate a DNS zone file for the given set of RRs.'''
    with open(out_file, 'w') as out:
        for (_, rrs) in rrsets_data:
            out.write('\n'.join(rrs) + '\n')

if __name__ == "__main__":
    if len(sys.argv) < 4:
        sys.stderr.write('gen-query-testdata.py require 3 args\n')
        sys.exit(1)
    rrsets_data = parse_input(sys.argv[1])
    generate_zonefile(sys.argv[2], rrsets_data)
    generate_variables(sys.argv[3], rrsets_data)

