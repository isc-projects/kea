# Copyright (C) 2013  Internet Systems Consortium.
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

'''
This script takes a C++ file with constants and converts it to a python
module. However, the syntax it parses is very limited (it doesn't understand
C++ at all, it just looks for lines containing the equal sign and strips
what it thinks might be type).

The purpose is to keep the same values of constants in C++ and python. This
saves the work of keeping the constants in sync manually and is less error
prone.
'''

import sys
import re

if len(sys.argv) != 3:
    sys.stderr.write("Usage: python3 ./pythonize_constants.py input.cc output.py\n")
    sys.exit(1)

[filename_in, filename_out] = sys.argv[1:3]

# Ignore preprocessor, namespaces and the ends of namespaces.
ignore = re.compile('^(#|namespace|})')
comment = re.compile('^//(.*)')
constant = re.compile('^[a-zA-Z].*?([a-zA-Z_0-9]+\\s*=.*);')

with open(filename_in) as file_in, open(filename_out, "w") as file_out:
    file_out.write("# This file is generated from " + filename_in + "\n" +
                   "# by the pythonize_constants.py script.\n" +
                   "# Do not edit, all changes will be lost.\n\n")
    for line in file_in:
        if ignore.match(line):
            continue
        # Mangle comments to be python-like
        line = comment.sub('#\\1', line)
        # Extract the constant.

        # TODO: We may want to do something with the true vs. True and
        # NULL vs. None and such. Left out for now, since none are in
        # the input file currently.
        line = constant.sub('\\1', line)

        file_out.write(line)
