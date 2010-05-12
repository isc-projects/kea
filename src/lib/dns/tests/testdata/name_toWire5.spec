#
# A sequence of names that would be compressed case-sensitive manner.
# First name: "a.example.com"
# Second name: "b.eXample.com".  Due to case-sensitive comparison only "com"
# can be compressed.
# Third name: "c.eXample.com".  "eXample.com" part matches that of the second
# name and can be compressed.
#

[custom]
sections: name/1:name/2:name/3
[name/1]
name: a.example.com
[name/2]
name: b.eXample
pointer: 10
[name/3]
name: c
pointer: 17
