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

import struct
from pydnspp import *

# Some position parameters used in the formatted output report.
POS_TOTAL = 80
POS_TITLE = 14
POS_LEFT = int((POS_TOTAL - POS_TITLE) / 2)

def get_header_field(msg):
	header = {}
	header['id'] = msg.get_qid()
	header['qr'] = msg.get_header_flag(Message.HEADERFLAG_QR)
	header['opcode'] = msg.get_opcode()
	header['aa'] = msg.get_header_flag(Message.HEADERFLAG_AA)
	header['tc'] = msg.get_header_flag(Message.HEADERFLAG_TC)
	header['rd'] = msg.get_header_flag(Message.HEADERFLAG_RD)
	header['ra'] = msg.get_header_flag(Message.HEADERFLAG_RA)
	header['ad'] = msg.get_header_flag(Message.HEADERFLAG_AD)
	header['cd'] = msg.get_header_flag(Message.HEADERFLAG_CD)
	#header['rcode'] = dns.rcode.from_flags(msg.flags, msg.ednsflags)
	header['rcode'] = msg.get_rcode()	

	header['qdcount'] = msg.get_rr_count(Message.SECTION_QUESTION)
	header['ancount'] = msg.get_rr_count(Message.SECTION_ANSWER)
	header['nscount'] = msg.get_rr_count(Message.SECTION_AUTHORITY)
	header['arcount'] = msg.get_rr_count(Message.SECTION_ADDITIONAL)

	return header

def header_cmp(buf, msg1, msg2, diff):
	""" Compare the header of msg1 and msg2. 

	@param buf: the formatted difference for output. 
	@type buf: dict
	@param diff: the key is each flag in the header, the value is 
		     True for different and False for same
	@type diff: dict
	"""
	
	header1 = get_header_field(msg1)
	header2 = get_header_field(msg2)

	list = ['id', 'qr', 'opcode', 'aa', 'tc', 'rd', \
		'ra', 'ad', 'cd', 'rcode', 'qdcount', 'ancount', \
		'nscount', 'arcount']

	for header in list:
		diff[header] = header1[header] != header2[header]
		
	buf['header'] = ''
	for key in list:
		if diff[key]:
			buf['header'] = buf['header'] + \
				'%-*s%-*s%-*s\n' % (POS_TITLE, key, \
				POS_LEFT, header1[key], POS_LEFT, \
				header2[key])

	for key in diff.keys():
		if diff[key]: return(False)

	return(True)


def output(sect, buf, rrset, isleft):
	""" Format and return the rrset according to which section 
		and which message it belongs to. 

	@param sect: section name
	@type sect: string
	@param buf: passed by parameter, to store the formatted string
	@param buf: dict
	@param rrset: the rrset to be formatted
	@type rrset: RRset 
	@param isleft: to be compared, the report has the content corresponding to 
			the 1st message printed on the left, while the one corresponding
			to the 2nd message on the right. This is a flag to which one it is.
	@type isleft: BOOL
	"""

	if not sect in buf:
		buf[sect] = ''
	if sect == 'question':
		buf[sect] = buf[sect] + '%-*s' % (POS_TITLE, 'name')
		if not isleft:
			buf[sect] = buf[sect] + ' ' * POS_LEFT
		buf[sect] = buf[sect] + rrset.get_name().to_text() + "\n"

		buf[sect] = buf[sect] + '%-*s' % (POS_TITLE, 'class')
		if not isleft:
			buf[sect] = buf[sect] + ' ' * POS_LEFT
		buf[sect] = buf[sect] + rrset.get_class().to_text() + "\n"

		buf[sect] = buf[sect] + '%-*s' % (POS_TITLE, 'type')
		if not isleft:
			buf[sect] = buf[sect] + ' ' * POS_LEFT
		buf[sect] = buf[sect] + rrset.get_type().to_text() + "\n"

	else:
		buf[sect] = buf[sect] + '%-*s' % (POS_TITLE, 'ttl')
		if not isleft:
			buf[sect] = buf[sect] + ' ' * int(POS_LEFT)
		buf[sect] = buf[sect] + rrset.get_ttl().to_text() + "\n"

		buf[sect] = buf[sect] + '%-*s' % (POS_TITLE, 'name')
		if not isleft:
			buf[sect] = buf[sect] + ' ' * int(POS_LEFT)
		buf[sect] = buf[sect] + rrset.get_name().to_text() + "\n"

		buf[sect] = buf[sect] + '%-*s' % (POS_TITLE, 'class')
		if not isleft:
			buf[sect] = buf[sect] + ' ' * int(POS_LEFT)
		buf[sect] = buf[sect] + rrset.get_class().to_text() + "\n"

		buf[sect] = buf[sect] + '%-*s' % (POS_TITLE, 'type')
		if not isleft:
			buf[sect] = buf[sect] + ' ' * int(POS_LEFT)
		buf[sect] = buf[sect] + rrset.get_type().to_text() + "\n"

		buf[sect] = buf[sect] + '%-*s' % (POS_TITLE, 'rdata')

		i = 0
		rdata = rrset.get_rdata()
		for item in rdata:
			if i > 0:
                                buf[sect] = buf[sect] + ' ' * POS_TITLE
			if not isleft:
				buf[sect] = buf[sect] + ' ' * POS_LEFT
			buf[sect] = buf[sect] + item.to_text() + "\n"
			i = i + 1

	buf[sect] = buf[sect] + "\n"

def array_cmp(sectname, buf, rlist1, rlist2):
	""" Compare each entry of the question section of rlist1 and rlist2.
	    Compare each RRset of the sectname section (can be answer, authority, 
	    additional) of rlist1 and rlist2.
	    
	@param buf: store the formatted output of difference
	@type: dict
	"""

	diff_flag = True
	while len(rlist1) > 0:
		rr1 = rlist1.pop()
		find2 = False
		for rr2 in rlist2:
			if sectname == 'question':
				res = question_cmp(rr1, rr2)
			else:
				res = rr_cmp(rr1, rr2)
			if res:
				find2 = True
				rlist2.remove(rr2)
				break
		if not find2:
			output(sectname, buf, rr1, True)
			diff_flag = False

	while len(rlist2) > 0:
		rr2 = rlist2.pop()
		output(sectname, buf, rr2, False)
		diff_flag = False
	return(diff_flag)

def question_cmp(rra, rrb):
	if rra.get_name() != rrb.get_name(): return(False)
	if rra.get_class() != rrb.get_class(): return(False)
	if rra.get_type() != rrb.get_type(): return(False)
	return(True)

def rr_cmp(rra, rrb):
	""" Compare two rrsets: rra and rrb """

	if rra.get_name() != rrb.get_name(): return(False)
	if rra.get_class() != rrb.get_class(): return(False)
	if rra.get_type() != rrb.get_type(): return(False)
	if rra.get_ttl() != rrb.get_ttl(): return(False)
	rdata_a = rra.get_rdata()
	rdata_b = rrb.get_rdata()
	rdata_al = len(rdata_a)
	rdata_bl = len(rdata_b)

	if rdata_al != rdata_bl: 
		return(False)

	cmp_flag = False
	# Iterate rdata in rrset a, find if there is same rdata in rrset b
	for ra in rdata_a:
		for rb in rdata_b:
			if ra.to_text() == rb.to_text():
				cmp_flag = True
				rdata_b.remove(rb)
				break
		if not cmp_flag:
			break
	return(cmp_flag)

def resp_casecmp(msg1, msg2, num):
	""" Compare two response message, and print the different part
	    in formatted report. 

	@param msg1: 1st response message
	@type msg1: Message
	@param msg2: 2nd response message
        @type msg2: Message
	@param num: the id of the query case in the 1st column of the input file.
		    Used by output report to locate the specified query case. 
	@type num: int
	"""

	diff = {}
	buf = {}

	query = msg1.get_question()[0]

	res_hdr = header_cmp(buf, msg1, msg2, diff)
	res_ques = array_cmp('question', buf, \
				msg1.get_question(), msg2.get_question())
	res_ans = array_cmp('answer', buf, \
				msg1.get_section(Message.SECTION_ANSWER), \
				msg2.get_section(Message.SECTION_ANSWER))
	res_auth = array_cmp('authority', buf, \
				msg1.get_section(Message.SECTION_AUTHORITY), \
				msg2.get_section(Message.SECTION_AUTHORITY))
	res_addi = array_cmp('additional', buf, \
				msg1.get_section(Message.SECTION_ADDITIONAL), \
				msg2.get_section(Message.SECTION_ADDITIONAL))
	
	# If there are any differnt comparisons in the sections above, print the details
	# contained in buf formattedly.
	if not res_hdr or not res_ques or not res_ans or not res_auth or not res_addi:
		print('=' * 30, '  BEGIN QUERY %s  ' % num, '=' * 30, sep='')
		print('%-*s%-*s%-*s' % (POS_TITLE, '', int(POS_LEFT), 'SERVER1', \
			POS_TOTAL - POS_TITLE, 'SERVER2'))
		print('-' * 80)
		print('Query:  ', query.to_text(), sep='')
		print('-' * 80)

		if not res_hdr:
			print(buf['header'])
			print('-' * 80)

		if not res_ques:
			print("QUESTION")
			print('-' * 80)
			print(buf['question'])

		if not res_ans:
			print("ANSWER")
			print('-' * 80)
			print(buf['answer'])

		if not res_auth:
			print("AUTHORITY")
			print('-' * 80)
			print(buf['authority'])

		if not res_addi:
			print("ADDITIONAL")
			print('-' * 80)
			print(buf['additional'])

		print('=' * 30, '   END QUERY %s   ' % num, '=' * 30, sep='') 
		print("\n\n")

		return False

	return True

