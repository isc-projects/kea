#
# A malformed NSEC RDATA: bit map length is too large, causing overflow
#

[custom]
sections: nsec
[nsec]
maplen: 31
bitmap: '01' 
