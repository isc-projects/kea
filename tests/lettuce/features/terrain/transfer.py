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

# This script provides transfer (ixfr/axfr) test functionality
# It provides steps to perform the client side of a transfer,
# and inspect the results.
#
# Like querying.py, it uses dig to do the transfers, and
# places its output in a result structure
#
# This is done in a different file with different steps than
# querying, because the format of dig's output is
# very different than that of normal queries

from lettuce import *
import subprocess
import re

class TransferResult(object):
    """This object stores transfer results, which is essentially simply
       a list of RR strings. These are stored, as read from dig's output,
       in the list 'records'. So for an IXFR transfer it contains
       the exact result as returned by the server.
       If this list is empty, the transfer failed for some reason (dig
       does not really show error results well, unfortunately).
       We may add some smarter inspection functionality to this class
       later.
    """
    def __init__(self, args):
        """Perform the transfer by calling dig, and store the results.
           args is the array of arguments to pass to Popen(), this
           is passed as is since for IXFR and AXFR there can be very
           different options"""
        self.records = []
        
        dig_process = subprocess.Popen(args, 1, None, None, subprocess.PIPE,
                                       None)
        result = dig_process.wait()
        assert result == 0
        print("[XX]")
        print("[XX]")
        print("[XX]")
        print("[XX]")
        for l in dig_process.stdout:
            line = l.strip()
            if len(line) > 0 and line[0] != ';':
                self.records.append(line)
                print(line)
        print("[XX]")
        print("[XX]")
        print("[XX]")
        print("[XX]")

@step('An AXFR transfer of ([\w.]+)(?: from ([^:]+)(?::([0-9]+))?)?')
def perform_axfr(step, zone_name, address, port):
    """Perform an AXFR transfer, and store the result in world.transfer_result
    """
    if address is None:
        address = "127.0.0.1"
    if port is None:
        port = 47806
    args = [ 'dig', 'AXFR', '@' + str(address), '-p', str(port), zone_name ]
    world.transfer_result = TransferResult(args)

@step('An IXFR transfer of ([\w.]+) (\d+)(?: over (tcp|udp))?(?: from ([^:]+)(?::([0-9]+))?)?')
def perform_ixfr(step, zone_name, serial, protocol, address, port):
    """Perform an AXFR transfer, and store the result in world.transfer_result
    """
    if address is None:
        address = "127.0.0.1"
    if port is None:
        port = 47806
    args = [ 'dig', 'IXFR=' + str(serial), '@' + str(address), '-p', str(port), zone_name ]
    if protocol is not None:
        assert protocol == 'tcp' or protocol == 'udp', "Unknown protocol: " + protocol
        if protocol == 'tcp':
            args.append('+tcp')
        elif protocol == 'udp':
            args.append('+notcp')
    world.transfer_result = TransferResult(args)

@step('transfer result should have (\d+) rrs?')
def check_transfer_result_count(step, number_of_rrs):
    """Check the number of rrs in the transfer result object created by
       the AXFR transfer or IXFR transfer step."""
    assert int(number_of_rrs) == len(world.transfer_result.records),\
        "Got " + str(len(world.transfer_result.records)) +\
        " records, expected " + str(number_of_rrs)

@step('full result of the last transfer should be')
def check_full_transfer_result(step, ):
    records_string = "\n".join(world.transfer_result.records)
    records_string = re.sub("[ \t]+", " ", records_string)
    expect = re.sub("[ \t]+", " ", step.multiline)
    assert records_string.strip() == expect.strip(),\
        "Got:\n'" + records_string + "'\nExpected:\n'" + expect + "'"

