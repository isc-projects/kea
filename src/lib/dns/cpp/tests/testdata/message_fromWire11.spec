#
# A simple DNS response message with an EDNS0 indicating the maximum error code
# (0xfff)
#

[header]
qr: response
rd: 1
rcode: 0xf
arcount: 1
[question]
# use default
[edns]
do: 1
extrcode: 0xff
