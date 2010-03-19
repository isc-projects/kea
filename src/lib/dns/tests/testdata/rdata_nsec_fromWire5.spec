#
# A malformed NSEC RDATA: incomplete bit map field
#

[custom]
sections: nsec
[nsec]
# only containing the block field of the bitmap
rdlen: 19
#dummy data
maplen: 31
#dummy data
bitmap: '00'
