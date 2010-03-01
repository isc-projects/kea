#
# A simple DNS query message with an EDNS0 indicating a BADVERS error
#

[header]
rd: 1
arcount: 1
[question]
# use default
[edns]
do: 1
extrcode: 1
