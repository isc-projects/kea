#!/usr/bin/python3

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

import isc, sys

cc = isc.cc.Session()
if len(sys.argv) < 3:
    sys.stderr.write('Usage: ' + sys.argv[0] + ' <channel> <command> [arg]\n')
    sys.exit(1)

channel = sys.argv[1]
command = sys.argv[2]
if len(sys.argv) >= 4:
    argument = sys.argv[3]
else:
    argument = ""

cmd = { "command": [ command, argument ] }

cc.group_subscribe(channel)
print("Sending:")
print(cmd)
cc.group_sendmsg(cmd, channel)
