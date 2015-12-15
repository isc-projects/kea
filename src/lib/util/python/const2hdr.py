# Copyright (C) 2013  Internet Systems Consortium.
#
# This Source Code Form is subject to the terms of the Mozilla Public
# License, v. 2.0. If a copy of the MPL was not distributed with this
# file, You can obtain one at http://mozilla.org/MPL/2.0/.

'''
The script takes a C++ file with constant definitions and creates a
header file for the constants. It, however, does not understand C++
syntax, it only does some heuristics to guess what looks like
a constant and strips the values.

The purpose is just to save some work with keeping both the source and
header. The source syntax must be limited already, because it's used to
generate the python module (by the
lib/python/isc/util/pythonize_constants.py script).
'''

import sys
import re

if len(sys.argv) != 3:
    sys.stderr.write("Usage: python3 ./const2hdr.py input.cc output.h\n")
    sys.exit(1)

[filename_in, filename_out] = sys.argv[1:3]

preproc = re.compile('^#')
constant = re.compile('^([a-zA-Z].*?[a-zA-Z_0-9]+)\\s*=.*;')

with open(filename_in) as file_in, open(filename_out, "w") as file_out:
    file_out.write("// This file is generated from " + filename_in + "\n" +
                   "// by the const2hdr.py script.\n" +
                   "// Do not edit, all changes will be lost.\n\n")
    for line in file_in:
        if preproc.match(line):
            # There's only one preprocessor line in the .cc file. We abuse
            # that to position the top part of the header.
            file_out.write("#ifndef BIND10_COMMON_DEFS_H\n" +
                           "#define BIND10_COMMON_DEFS_H\n" +
                           "\n" +
                           "// \\file " + filename_out + "\n" +
'''// \\brief Common shared constants\n
// This file contains common definitions of constasts used across the sources.
// It includes, but is not limited to the definitions of messages sent from
// one process to another. Since the names should be self-explanatory and
// the variables here are used mostly to synchronize the same values across
// multiple programs, separate documentation for each variable is not provided.
''')
            continue
        # Extract the constant. Remove the values and add "extern"
        line = constant.sub('extern \\1;', line)

        file_out.write(line)

    file_out.write("#endif\n")
