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

import sys
import re

def die(message):
    sys.stderr.write(message + "\n")
    sys.exit(1)

if len(sys.argv) != 3:
    die("Usage: python3 ./const2hdr.py input.cpp output.h")

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
