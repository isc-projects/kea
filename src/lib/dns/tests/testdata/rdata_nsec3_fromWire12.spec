#
# An invalid NSEC3 RDATA: Hash length is too large
#

[custom]
sections: nsec3
[nsec3]
# only contains the first byte of hash
rdlen: 12
