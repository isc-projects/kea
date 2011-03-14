#
# An invalid NSEC3 RDATA with an oversized bitmap field (33 bitmap bytes)
#

[custom]
sections: nsec3
[nsec3]
maplen: 33
bitmap: '010101010101010101010101010101010101010101010101010101010101010101'
