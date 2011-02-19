#
# NSEC3 RDATA with empty type bitmap.  It's okay.
# The test data includes bytes for a bitmap field, but RDLEN indicates
# it's not part of the RDATA and so it will be ignored.
#

[custom]
sections: nsec3
[nsec3]
rdlen: 31
