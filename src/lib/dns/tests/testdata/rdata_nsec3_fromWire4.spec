#
# A malformed NSEC3 RDATA: bit map length is too large, causing overflow
#

[custom]
sections: nsec3
[nsec3]
maplen: 31
bitmap: '01'
