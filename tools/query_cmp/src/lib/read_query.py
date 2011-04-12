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

import re
import sys

def read_query(file, querylist):
	fh = open(file)
	while True:
		query = {}
		query['header'] = {}

		line = fh.readline()
		if not line: break
		line = line.rstrip('\n')

		if re.search('^#', line): continue
		if re.search('^\s*$', line): continue

		fields = line.split(' ')
		query['header']['id'] = fields.pop(0)
		query['header']['qr'] = fields.pop(0)
		query['header']['opcode'] = int(fields.pop(0))
		query['header']['aa'] = fields.pop(0)
		query['header']['tc'] = fields.pop(0)
		query['header']['rd'] = fields.pop(0)
		query['header']['ra'] = fields.pop(0)
		query['header']['z'] = fields.pop(0)
		query['header']['ad'] = fields.pop(0)
		query['header']['cd'] = fields.pop(0)
		query['header']['rcode'] = fields.pop(0)
		query['header']['qdcount'] = fields.pop(0)
		query['header']['ancount'] = fields.pop(0)
		query['header']['nscount'] = fields.pop(0)
		query['header']['arcount'] = fields.pop(0)

		if query['header']['opcode'] == 0:
			get_qtuple(query, 'question', fields)

		querylist.append(query)

	fh.close()

def get_qtuple(query, sectname, list):
	if sectname == 'question':
		count = int(query['header']['qdcount'])
	item = {}
	i = 0
	while i < count:
		query[sectname] = []
		item['qname'] = list.pop(0)
		item['qtype'] = list.pop(0)
		item['qclass'] = list.pop(0)
		query[sectname].append(item)
		i += 1

def print_query(querylist):
	keylist = ['id', 'qr', 'opcode', 'aa', 'tc', 'rd', 'ra', 'z',
		'ad', 'cd', 'rcode', 'qdcount', 'ancount', 'nscount',
		'arcount']
	for q in querylist:
		for key in keylist:
			print(q['header'][key], ' ')
		print_question(q)

def print_question(query):
	i = 0

	while i < len(query['question']):
		print(query['question'][i]['qname'], \
			query['question'][i]['qtype'], \
			query['question'][i]['qclass'], \
			sep=' ')
		i += 1

if __name__ == '__main__':
	qlist = []
	read_query(sys.argv[1], qlist)
	print_query(qlist)

