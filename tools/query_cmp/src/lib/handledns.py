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

import errno
import sys
import select
import socket
import struct
import time

from pydnspp import *

RECV_BUFSIZE = 65536
	
def _wait_for(ir, iw, ix, expiration):
	done = False
	while not done:
		if expiration is None:
			timeout = None
		else:
			timeout = expiration - time.time()
			if timeout <= 0.0:
				raise socket.timeout
		try:
			if timeout is None:
				(r,w,x) = select.select(ir,iw,ix)
			else:
				(r,w,x) = select.select(ir,iw,ix,timeout)
		except select.error as e:
			if e.args[0] != errno.EINTR:
				raise e
		else:
			done = True
			if len(r) == 0 and len(w) == 0 and len(x) == 0:
				raise socket.timeout

def _wait_for_readable(s,expiration):
	_wait_for([s],[],[s],expiration)

def _compute_expiration(timeout):
	if timeout is None:
		return None
	else:
		return time.time() + timeout

def _send_udp(q, where, timeout=None, port=53, source=None, source_port=0):
	""" Return the response obtained after sending a query via UDP. 
	    Refered to dnspython source code. """

	qwire = MessageRenderer()
	q.to_wire(qwire)      
	if source is not None:
		source = (source, source_port)
	
	udpCliSock = socket.socket(socket.AF_INET, socket.SOCK_DGRAM, 0)

	expiration = _compute_expiration(timeout)
	if source is not None:
		udpCliSock.bind(source)

	dest = (where, port)
	udpCliSock.sendto(qwire.get_data(), dest)

	while True:
		_wait_for_readable(udpCliSock, expiration)
		rwire, r_addr = udpCliSock.recvfrom(RECV_BUFSIZE)
		if dest[0] == r_addr[0] and dest[1:] == r_addr[1:]:
			break
		else:
			sys.stderr.write('Got a respose from: %s instead of %s\n' % (r_addr, dest))

	udpCliSock.close()

	resp = Message(Message.PARSE)
	resp.from_wire(rwire)

	return resp 
	
def _connect(s, address):
	try:
		s.connect(address)
	except socket.error as msg:
		(exctype,value) = sys.exc_info()[:2]
		if value.errno != errno.EINPROGRESS and \
			value.errno != errno.EWOULDBLOCK and \
			value.errno != errno.EALREADY:
			raise value	

def _net_read(sock, count, expiration):
	""" Read the specified number of bytes from sock. Keep trying until we
	    either get the desired amount, or we hit EOF.
	    A Timeout exception will be raised if the operation is not completed
	    by the expiration time.
	"""

	msgdata = b''
	while count > 0:
		_wait_for_readable(sock, expiration)
		data = sock.recv(count)
		if not data:
			return None

		count -= len(data)
		msgdata += data
	
	return msgdata

def _net_write(sock, data, expiration):
	""" Write the specified data to the socket.
	    A Timeout exception will be raised if the operation is not completed
	    by the expiration time.
	"""
	current = 0
	l = len(data)
	while current < 1:
		_wait_for_writable(sock, expiration)
		current += sock.send(data[current:])

def _send_tcp(q, dest, timeout=None, dest_port=53, source=None, source_port=0):
	""" Return the response obtained after sending a query via TCP. 
	    Refered to dnspython source code """

	qwire = MessageRenderer()
	q.to_wire(qwire)

	if source is not None:
		source = (source, source_port)
	dest = (dest, dest_port)
	tcpCliSock = socket.socket(socket.AF_INET, socket.SOCK_STREAM, 0)
		
	expiration = _compute_expiration(timeout)
	tcpCliSock.setblocking(False)
	if source is not None:
		tcpCliSock.bind(source)
	_connect(tcpCliSock, dest)

	wire_s = qwire.get_data()
	l = len(wire_s)

	tcpmsg = struct.pack("!H", l) + wire_s
	_net_write(tcpCliSock, tcpmsg, expiration)
	ldata = _net_read(tcpCliSock, 2, expiration)
	(l,) = struct.unpack("!H", ldata)
	res_wire = _net_read(tcpCliSock, l, expiration)
	tcpCliSock.close()

	resp = Message(Message.PARSE)
	resp.from_wire(res_wire)

	return resp

def send_req(query, server, port=53, timeout=5):
	""" Return the response message obtained after 
	    sending the query.
	
	@param query: the query readed from input file
	@type query: dict
	@param server: the testee server ip address
	@type server: string
	@param port: the testee server listening port. The default is 53.
	@type port: int
	@param timeout: the number of seconds to wait before the query times out.
		The default is 5.
	@type timeout: float
	"""

	qname = query["qname"]
	qtype = query["qtype"]
	qclass = query["qclass"]
	edns = query["edns"]
	dnssec = query["dnssec"]
	qheader = query['header']
	protocol = query['protocol']

	msg = Message(Message.RENDER)
	msg.set_qid(int(qheader['id']))
	msg.set_opcode(Opcode.QUERY())
	msg.set_rcode(Rcode(int(qheader['rcode'])))

	if qheader['qr'] == 1: 
		msg.set_header_flag(Message.HEADERFLAG_QR)
	if qheader['aa'] == 1: 
		msg.set_header_flag(Message.HEADERFLAG_AA)
	if qheader['tc'] == 1: 
		msg.set_header_flag(Message.HEADERFLAG_TC)		
	if qheader['rd'] == 1: 
		msg.set_header_flag(Message.HEADERFLAG_RD)
	if qheader['ra'] == 1: 
		msg.set_header_flag(Message.HEADERFLAG_RA)
	if qheader['ad'] == 1: 
		msg.set_header_flag(Message.HEADERFLAG_AD)
	if qheader['cd'] == 1: 
		msg.set_header_flag(Message.HEADERFLAG_CD)

	try:
		msg.add_question(Question(Name(qname), \
                         	RRClass(qclass), RRType(qtype)))
	except InvalidRRType as e: 
		sys.stderr.write('Unrecognized RR queryeter string: %s\n' % qtype)
		return None

	if edns == 1 or dnssec == 1:
		edns_conf = EDNS()
		payload = query['payload']
		edns_conf.set_udp_size(payload)

		if dnssec == 1:
			edns_conf.set_dnssec_awareness(True)
		else:
			edns_conf.set_dnssec_awareness(False)

		msg.set_edns(edns_conf)

	port = int(port)
	if protocol == 'udp':
		resp = _send_udp(msg, server, timeout, port)
	else:
		resp = _send_tcp(msg, server, timeout, port)

	return resp


def main():
	query = {}
	query['qname'] = "A.example.com"
	query['qtype'] = "ANY"
	query['qclass'] = "IN"
	query["edns"] = 1
	query["dnssec"] = 1
	query["protocol"] = 'tcp'
	query["payload"] = 4096

	query['header'] = {}
	query['header']['id'] = 0
	query['header']['qr'] = 0
	query['header']['opcode'] = 0
	query['header']['aa'] = 0
	query['header']['tc'] = 0
	query['header']['rd'] = 1
	query['header']['ra'] = 0
	query['header']['z'] = 0
	query['header']['ad'] = 0
	query['header']['cd'] = 0
	query['header']['rcode'] = 0
	query['header']['qdcount'] = 0
	query['header']['ancount'] = 0
	query['header']['nscount'] = 0
	query['header']['arcount'] = 0

	resp = send_req(query, "218.241.108.124", "4040")

	if resp == None:
		print('timeout')
		exit(1)

	print('qid -----')
	print(resp.get_qid())

	rrset = resp.get_section(Message.SECTION_ANSWER)[0]
	print('name-----')
	print(rrset.get_name())
	print('type')
	print(rrset.get_type())
	print('class-----')
	print(rrset.get_class())
	print(rrset.get_ttl())
	rdata = rrset.get_rdata()
	print(rdata[0].to_text())
	
if __name__ == "__main__":
	main()
