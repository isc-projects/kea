SUBDIRS = . tests python

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CXXFLAGS = $(B10_CXXFLAGS)

CLEANFILES = *.gcno *.gcda
CLEANFILES += rrclass.h rrtype.h rrparamregistry.cc rdataclass.h rdataclass.cc

EXTRA_DIST = rrclass-placeholder.h
EXTRA_DIST += rrparamregistry-placeholder.cc
EXTRA_DIST += rrtype-placeholder.h

# TODO: double-check that this is the only way
# NOTE: when an rdata file is added, please also add to this list:
EXTRA_DIST += rdata/in_1/aaaa_28.cc
EXTRA_DIST += rdata/in_1/aaaa_28.h
EXTRA_DIST += rdata/in_1/a_1.cc
EXTRA_DIST += rdata/in_1/a_1.h
EXTRA_DIST += rdata/ch_3/a_1.cc
EXTRA_DIST += rdata/ch_3/a_1.h
EXTRA_DIST += rdata/generic/mx_15.h
EXTRA_DIST += rdata/generic/rrsig_46.cc
EXTRA_DIST += rdata/generic/dname_39.cc
EXTRA_DIST += rdata/generic/rrsig_46.h
EXTRA_DIST += rdata/generic/dname_39.h
EXTRA_DIST += rdata/generic/ns_2.cc
EXTRA_DIST += rdata/generic/nsec_47.cc
EXTRA_DIST += rdata/generic/ns_2.h
EXTRA_DIST += rdata/generic/nsec_47.h
EXTRA_DIST += rdata/generic/opt_41.cc
EXTRA_DIST += rdata/generic/soa_6.cc
EXTRA_DIST += rdata/generic/cname_5.cc
EXTRA_DIST += rdata/generic/dnskey_48.cc
EXTRA_DIST += rdata/generic/opt_41.h
EXTRA_DIST += rdata/generic/soa_6.h
EXTRA_DIST += rdata/generic/cname_5.h
EXTRA_DIST += rdata/generic/dnskey_48.h
EXTRA_DIST += rdata/generic/ds_43.cc
EXTRA_DIST += rdata/generic/ds_43.h
EXTRA_DIST += rdata/generic/txt_16.cc
EXTRA_DIST += rdata/generic/txt_16.h
EXTRA_DIST += rdata/generic/mx_15.cc
EXTRA_DIST += rdata/generic/nsec3param_51.h
EXTRA_DIST += rdata/generic/nsec3param_51.cc
EXTRA_DIST += rdata/generic/nsec3_50.cc
EXTRA_DIST += rdata/generic/nsec3_50.h
EXTRA_DIST += rdata/generic/ptr_12.cc
EXTRA_DIST += rdata/generic/ptr_12.h
EXTRA_DIST += rdata/hs_4/a_1.cc
EXTRA_DIST += rdata/hs_4/a_1.h
#EXTRA_DIST += rdata/template.cc
#EXTRA_DIST += rdata/template.h

# auto-generate by gen-rdatacode.py:
BUILT_SOURCES = rrclass.h rrtype.h rrparamregistry.cc
#TODO: check this###BUILT_SOURCES = rdataclass.h rdataclass.cc

lib_LTLIBRARIES = libdns++.la

libdns___la_SOURCES = util/base32hex.h util/base64.h util/base_n.cc
libdns___la_SOURCES += util/base32hex_from_binary.h
libdns___la_SOURCES += util/binary_from_base32hex.h
libdns___la_SOURCES += util/base16_from_binary.h util/binary_from_base16.h
libdns___la_SOURCES += buffer.h
libdns___la_SOURCES += dnssectime.h dnssectime.cc
libdns___la_SOURCES += exceptions.h exceptions.cc
libdns___la_SOURCES += util/hex.h
libdns___la_SOURCES += message.h message.cc
libdns___la_SOURCES += messagerenderer.h messagerenderer.cc
libdns___la_SOURCES += name.h name.cc
libdns___la_SOURCES += rdata.h rdata.cc
libdns___la_SOURCES += rrclass.cc
libdns___la_SOURCES += rrparamregistry.h
libdns___la_SOURCES += rrset.h rrset.cc
libdns___la_SOURCES += rrsetlist.h rrsetlist.cc
libdns___la_SOURCES += rrttl.h rrttl.cc
libdns___la_SOURCES += rrtype.cc
libdns___la_SOURCES += question.h question.cc
libdns___la_SOURCES += util/sha1.h util/sha1.cc
libdns___la_SOURCES += tsig.h tsig.cc

nodist_libdns___la_SOURCES = rdataclass.cc rrclass.h rrtype.h
nodist_libdns___la_SOURCES += rrparamregistry.cc

rrclass.h: rrclass-placeholder.h
rrtype.h: rrtype-placeholder.h
rrparamregistry.cc: rrparamregistry-placeholder.cc
rrclass.h rrtype.h rrparamregistry.cc rdataclass.h rdataclass.cc: Makefile
	./gen-rdatacode.py

libdns++_includedir = $(includedir)/dns
libdns++_include_HEADERS = \
	buffer.h \
	dnssectime.h \
	exceptions.h \
	message.h \
	messagerenderer.h \
	name.h \
	question.h \
	rdata.h \
	rdataclass.h \
	rrclass.h \
	rrparamregistry.h \
	rrset.h \
	rrsetlist.h \
	rrttl.h \
	rrtype.h \
	tsig.h
# Purposely not installing these headers:
# util/*.h: used only internally, and not actually DNS specific
# rrclass-placeholder.h
# rrtype-placeholder.h
