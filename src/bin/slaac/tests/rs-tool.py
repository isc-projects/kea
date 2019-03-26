#!/usr/bin/env python3
import pprint
from scapy.layers.inet6 import IPv6, ICMPv6ND_RS, ICMPv6NDOptSrcLLAddr
from scapy.sendrecv import sr
from scapy.layers import inet6
import cbor2


class ICMPv6NDOptUniversalRaOption(inet6._ICMPv6NDGuessPayload, inet6.Packet):
    name = "ICMPv6 Neighbor Discovery Option - Universal RA option"
    fields_desc = [inet6.ByteField("type", 1),
                   inet6.FieldLenField("optlen", None, length_of="optdata", fmt="B",
                                       adjust=lambda pkt, x: x // 8 + 1),
                   inet6.StrLenField("optdata", "",
                                     length_from=lambda pkt: pkt.optlen * 8)]

    def mysummary(self):
        return self.sprintf("%name% %lladdr%")


inet6.icmp6ndoptscls[42] = ICMPv6NDOptUniversalRaOption


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
    p = r.payload
    while not isinstance(p, ICMPv6NDOptUniversalRaOption):
        p = p.payload
    print('bin: %s' % p.optdata)
    data = cbor2.loads(p.optdata)
    print('dict:')
    pprint.pprint(data)
