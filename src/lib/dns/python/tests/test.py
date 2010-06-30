#!/usr/bin/python3.1

import libdns_python

#for i in range(0,3):
#b = bytearray()
#while True:
#    c = libdns_python.RRClass("IN")
#    #print(dir(b))
#    c.toWire(b)
#    #print("b:")
#    print(b)
#    #print("d:")
#    #print(d)

#m = libdns_python.MessageRenderer()
#c1 = libdns_python.RRClass("IN")
#c2 = libdns_python.RRClass("CH")
#c3 = libdns_python.RRClass("IN")
#b2 = bytearray()
#d.toWire(b2)
#print(b2)
n = libdns_python.Name("tjeb.nl")
t = libdns_python.RRType("A")
c = libdns_python.RRClass("IN")
ttl = libdns_python.RRTTL(1234)

#set = libdns_python.RRset(1,2,3,4)

set = libdns_python.RRset(n, c, t, ttl)
#print(set.toText())
rd = libdns_python.Rdata(t, c, "123.123.123.123")
set.add_rdata(rd)
print(set.to_text())
