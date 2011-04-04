#
# A malformed NSEC3 RDATA: incomplete bit map field
#

[custom]
sections: nsec3
[nsec3]
# only containing the block field of the bitmap
rdlen: 32
#dummy data
maplen: 31
#dummy data
bitmap: '00'
