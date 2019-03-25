#!/usr/bin/env python3
from scapy.layers.inet6 import IPv6, ICMPv6ND_RS, ICMPv6NDOptSrcLLAddr
from scapy.sendrecv import sr

#m1 = IPv6(dst='ff02::2', hlim=255)
m1 = IPv6(dst='::1', hlim=255)
m2 = ICMPv6ND_RS()
m3 = ICMPv6NDOptSrcLLAddr(lladdr='48:a4:72:cd:ed:da')
m = m1 / m2 / m3
print("SENDING:")
m.show()

ans, unans = sr(m)

print("RECEIVED:")
for s, r in ans:
    r.show()
