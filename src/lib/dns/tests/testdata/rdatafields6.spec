#
# Names and RDATA (RRSIG) with an incompressible name.  The name in RRSIG
# isn't compressed, but it's used as the compression target.
#

[custom]
sections: name/1:rrsig:name/2
[name/1]
name: com
[rrsig]
[name/2]
name: www
pointer: 25
