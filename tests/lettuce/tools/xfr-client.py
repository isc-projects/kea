#!/usr/bin/env python3

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

# A simple XFR client program with some customized behavior.
# This is intended to provide some less common or even invalid client behavior
# for some specific tests on outbound zone transfer.
# It currently only supports AXFR, but can be extended to support IXFR
# as we see the need for it.
#
# For command line usage, run this program with -h option.

from isc.dns import *
import sys
import socket
import struct
import time
from optparse import OptionParser

parser = OptionParser(usage='usage: %prog [options] zone_name')
parser.add_option('-d', '--delay', dest='delay', action='store', default=None,
                  help='delay (sec) before receiving responses, ' +
                  'emulating slow clients')
parser.add_option('-s', '--server', dest='server_addr', action='store',
                  default='::1',
                  help="master server's address [default: %default]")
parser.add_option('-p', '--port', dest='server_port', action='store',
                  default=53,
                  help="master server's TCP port [default: %default]")
(options, args) = parser.parse_args()

if len(args) == 0:
    parser.error('missing argument')

# Parse arguments and options, and creates client socket.
zone_name = Name(args[0])
gai = socket.getaddrinfo(options.server_addr, int(options.server_port), 0,
                         socket.SOCK_STREAM, socket.IPPROTO_TCP,
                         socket.AI_NUMERICHOST|socket.AI_NUMERICSERV)
server_family, server_socktype, server_proto, server_sockaddr = \
    (gai[0][0], gai[0][1], gai[0][2], gai[0][4])
s = socket.socket(server_family, server_socktype, server_proto)
s.connect(server_sockaddr)
s.settimeout(60)                # safety net in case of hangup situation

# Build XFR query.
axfr_qry = Message(Message.RENDER)
axfr_qry.set_rcode(Rcode.NOERROR)
axfr_qry.set_opcode(Opcode.QUERY)
axfr_qry.add_question(Question(zone_name, RRClass.IN, RRType.AXFR))

renderer = MessageRenderer()
axfr_qry.to_wire(renderer)
qry_data = renderer.get_data()

# Send the query
hlen_data = struct.pack('H', socket.htons(len(qry_data)))
s.send(hlen_data)
s.send(qry_data)

# If specified wait for the given period
if options.delay is not None:
    time.sleep(int(options.delay))

def get_request_response(s, size):
    """A helper function to receive data of specified length from a socket."""
    recv_size = 0
    data = b''
    while recv_size < size:
        need_recv_size = size - recv_size
        tmp_data = s.recv(need_recv_size)
        if len(tmp_data) == 0:
            return None
        recv_size += len(tmp_data)
        data += tmp_data
    return data

# Receive responses until the connection is terminated, and dump the
# number of received answer RRs to stdout.
num_rrs = 0
while True:
    hlen_data = get_request_response(s, 2)
    if hlen_data is None:
        break
    resp_data = get_request_response(
        s, socket.ntohs(struct.unpack('H', hlen_data)[0]))
    msg = Message(Message.PARSE)
    msg.from_wire(resp_data, Message.PRESERVE_ORDER)
    num_rrs += msg.get_rr_count(Message.SECTION_ANSWER)
print(str(num_rrs))
