# Copyright (C) 2010  Internet Systems Consortium.
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

# $id$

#
# helper functions for tests taken from C++ unittests
#

import os

if "TESTDATA_PATH" in os.environ:
    testdata_path = os.environ["TESTDATA_PATH"]
else:
    testdata_path = "../tests/testdata"

def read_wire_data(filename):
    data = bytes()
    for path in testdata_path.split(":"):
        try:
            file = open(path + os.sep + filename, "r")
            for line in file:
                line = line.strip()
                if line == "" or line.startswith("#"):
                    pass
                else:
                    cur_data = bytes.fromhex(line)
                    data += cur_data

            return data
        except IOError:
            pass
    raise ValueError("Data file " + filename + "cannot be found")
