#
# An invalid NSEC RDATA with an oversized bitmap field (33 bitmap bytes)
#

[custom]
sections: nsec
[nsec]
maplen: 33
bitmap: '010101010101010101010101010101010101010101010101010101010101010101'
