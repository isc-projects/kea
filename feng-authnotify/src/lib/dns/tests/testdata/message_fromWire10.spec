#
# A simple DNS response message with an EDNS0 indicating a BADVERS error
#

[header]
qr: response
rd: 1
arcount: 1
[question]
# use default
[edns]
do: 1
extrcode: 1
