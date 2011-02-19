#
# A malformed NSEC3 RDATA: bit map length being 0
#

[custom]
sections: nsec3
[nsec3]
rdlen: 33
maplen: 0
# dummy data:
bitmap: '01'
