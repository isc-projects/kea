#!/usr/bin/python3

# Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

import sys; sys.path.append('lib')
from optparse import OptionParser

from read_query import *
import handledns
import compare_rrset

def getopt():
	"""
	get options from user.
	"""
	usage = "usage: %prog -f <file> -s <svr1> [-p <port1>] -t <svr2> [-q <port2>] [-e] [-u] [--bufsize] [--edns]"
	parser = OptionParser(usage)
	parser.add_option("-f", "--file", dest="filename",
		help="specify the input data filename")
	parser.add_option("-s", "--svr1", dest="server1",
		help="specify the tested DNS server 1")
	parser.add_option("-p",
		help="specify the port of the tested DNS server 1, default is 53")
	parser.add_option("-t", "--svr2", dest="server2",
		help="specify the tested DNS server 2")
	parser.add_option("-q",
		help="specify the port of the tested DNS server 2, default is 53")
	parser.add_option("-e", "--dnssec", action="store_true",
		default=False, help="turn on dnssec")
	parser.add_option("", "--edns", action="store_true",
		default=False, help="turn on edns, if -e is set, --edns will lapse, it must be True")
	parser.add_option("-u", "--udp", action="store_true", default=False,
		help="if set, query by udp, otherwise by tcp, default is unset")
	parser.add_option("", "--bufsize", default=4096,
		help="if --edns is set, --bufsize specifies payload of edns0, default is 4096")


	(options, args) = parser.parse_args()
	
	if(options.filename == None or options.server1 == None or
		options.server2 == None):
		parser.print_help()
		sys.exit(1)

	return options

def main():
	opts = getopt()

	qlist = []
	read_query(opts.filename, qlist)

	for q in qlist:
		# initial query
		query = {}
		if opts.dnssec:
			query['edns'] = 1
			query['dnssec'] = 1
		elif opts.edns:
			query['edns'] = 1
			query['dnssec'] = 0
		else:
			query['edns'] = 0
			query['dnssec'] = 0

		if opts.udp:
			query['protocol'] = 'udp'
		else:
			query['protocol'] = 'tcp'

		query['payload'] = opts.bufsize
		query['qname'] = q['question'][0]['qname']
		query['qtype'] = q['question'][0]['qtype']
		query['qclass'] = q['question'][0]['qclass']
		query['header'] = q['header']
		id = q['header']['id']

		# send the query to the 1st and 2nd server, and store the
		# response in res1 and res2
		res1 = handledns.send_req(query, opts.server1, opts.p)
		res2 = handledns.send_req(query, opts.server2, opts.q)

		if res1 != None and res2 != None:
			# compare res1 and res2, print the different part.
			res3 = compare_rrset.resp_casecmp(res1, res2, id)
		else:
			sys.stderr.write('Empty response.\n')

if __name__ == "__main__":
	main()
