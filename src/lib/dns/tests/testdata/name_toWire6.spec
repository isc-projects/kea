#
# A sequence of names that would be compressed both case-sensitive and
# case-insensitive manner (unusual, but allowed).
# First and second name: see name_toWire5.spec.
# Third name: "c.b.EXAMPLE.com".  This is rendered with case-insensitive
# compression, so "b.EXAMPLE.com" part of the name matches that of the
# second name.
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
pointer: 15
