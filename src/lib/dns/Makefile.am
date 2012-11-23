SUBDIRS = . tests python benchmarks

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/util -I$(top_builddir)/src/lib/util
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(B10_CXXFLAGS)

CLEANFILES = *.gcno *.gcda
CLEANFILES += rrclass.h rrtype.h rrparamregistry.cc rdataclass.h rdataclass.cc

EXTRA_DIST = rrclass-placeholder.h
EXTRA_DIST += rrparamregistry-placeholder.cc
EXTRA_DIST += rrtype-placeholder.h

# TODO: double-check that this is the only way
# NOTE: when an rdata file is added, please also add to this list:
EXTRA_DIST += rdata/any_255/tsig_250.cc
EXTRA_DIST += rdata/any_255/tsig_250.h
EXTRA_DIST += rdata/ch_3/a_1.cc
EXTRA_DIST += rdata/ch_3/a_1.h
EXTRA_DIST += rdata/generic/cname_5.cc
EXTRA_DIST += rdata/generic/cname_5.h
EXTRA_DIST += rdata/generic/detail/nsec_bitmap.cc
EXTRA_DIST += rdata/generic/detail/nsec_bitmap.h
EXTRA_DIST += rdata/generic/detail/nsec3param_common.cc
EXTRA_DIST += rdata/generic/detail/nsec3param_common.h
EXTRA_DIST += rdata/generic/detail/txt_like.h
EXTRA_DIST += rdata/generic/detail/ds_like.h
EXTRA_DIST += rdata/generic/dlv_32769.cc
EXTRA_DIST += rdata/generic/dlv_32769.h
EXTRA_DIST += rdata/generic/dname_39.cc
EXTRA_DIST += rdata/generic/dname_39.h
EXTRA_DIST += rdata/generic/dnskey_48.cc
EXTRA_DIST += rdata/generic/dnskey_48.h
EXTRA_DIST += rdata/generic/ds_43.cc
EXTRA_DIST += rdata/generic/ds_43.h
EXTRA_DIST += rdata/generic/hinfo_13.cc
EXTRA_DIST += rdata/generic/hinfo_13.h
EXTRA_DIST += rdata/generic/mx_15.cc
EXTRA_DIST += rdata/generic/mx_15.h
EXTRA_DIST += rdata/generic/naptr_35.cc
EXTRA_DIST += rdata/generic/naptr_35.h
EXTRA_DIST += rdata/generic/ns_2.cc
EXTRA_DIST += rdata/generic/ns_2.h
EXTRA_DIST += rdata/generic/nsec3_50.cc
EXTRA_DIST += rdata/generic/nsec3_50.h
EXTRA_DIST += rdata/generic/nsec3param_51.cc
EXTRA_DIST += rdata/generic/nsec3param_51.h
EXTRA_DIST += rdata/generic/nsec_47.cc
EXTRA_DIST += rdata/generic/nsec_47.h
EXTRA_DIST += rdata/generic/opt_41.cc
EXTRA_DIST += rdata/generic/opt_41.h
EXTRA_DIST += rdata/generic/ptr_12.cc
EXTRA_DIST += rdata/generic/ptr_12.h
EXTRA_DIST += rdata/generic/rp_17.cc
EXTRA_DIST += rdata/generic/rp_17.h
EXTRA_DIST += rdata/generic/rrsig_46.cc
EXTRA_DIST += rdata/generic/rrsig_46.h
EXTRA_DIST += rdata/generic/soa_6.cc
EXTRA_DIST += rdata/generic/soa_6.h
EXTRA_DIST += rdata/generic/spf_99.cc
EXTRA_DIST += rdata/generic/spf_99.h
EXTRA_DIST += rdata/generic/sshfp_44.cc
EXTRA_DIST += rdata/generic/sshfp_44.h
EXTRA_DIST += rdata/generic/txt_16.cc
EXTRA_DIST += rdata/generic/txt_16.h
EXTRA_DIST += rdata/generic/minfo_14.cc
EXTRA_DIST += rdata/generic/minfo_14.h
EXTRA_DIST += rdata/generic/afsdb_18.cc
EXTRA_DIST += rdata/generic/afsdb_18.h
EXTRA_DIST += rdata/hs_4/a_1.cc
EXTRA_DIST += rdata/hs_4/a_1.h
EXTRA_DIST += rdata/in_1/a_1.cc
EXTRA_DIST += rdata/in_1/a_1.h
EXTRA_DIST += rdata/in_1/aaaa_28.cc
EXTRA_DIST += rdata/in_1/aaaa_28.h
EXTRA_DIST += rdata/in_1/dhcid_49.cc
EXTRA_DIST += rdata/in_1/dhcid_49.h
EXTRA_DIST += rdata/in_1/srv_33.cc
EXTRA_DIST += rdata/in_1/srv_33.h
#EXTRA_DIST += rdata/template.cc
#EXTRA_DIST += rdata/template.h

# auto-generate by gen-rdatacode.py:
BUILT_SOURCES = rrclass.h rrtype.h rrparamregistry.cc
BUILT_SOURCES += rdataclass.h rdataclass.cc

lib_LTLIBRARIES = libb10-dns++.la

libb10_dns___la_LDFLAGS = -no-undefined -version-info 2:0:0

libb10_dns___la_SOURCES =
libb10_dns___la_SOURCES += edns.h edns.cc
libb10_dns___la_SOURCES += exceptions.h exceptions.cc
libb10_dns___la_SOURCES += master_lexer_inputsource.h master_lexer_inputsource.cc
libb10_dns___la_SOURCES += labelsequence.h labelsequence.cc
libb10_dns___la_SOURCES += masterload.h masterload.cc
libb10_dns___la_SOURCES += master_lexer.h master_lexer.cc
libb10_dns___la_SOURCES += master_lexer_state.h
libb10_dns___la_SOURCES += master_loader.h master_loader.cc
libb10_dns___la_SOURCES += message.h message.cc
libb10_dns___la_SOURCES += messagerenderer.h messagerenderer.cc
libb10_dns___la_SOURCES += name.h name.cc
libb10_dns___la_SOURCES += name_internal.h
libb10_dns___la_SOURCES += nsec3hash.h nsec3hash.cc
libb10_dns___la_SOURCES += opcode.h opcode.cc
libb10_dns___la_SOURCES += rcode.h rcode.cc
libb10_dns___la_SOURCES += rdata.h rdata.cc
libb10_dns___la_SOURCES += rdatafields.h rdatafields.cc
libb10_dns___la_SOURCES += rrclass.cc
libb10_dns___la_SOURCES += rrparamregistry.h
libb10_dns___la_SOURCES += rrset.h rrset.cc
libb10_dns___la_SOURCES += rrttl.h rrttl.cc
libb10_dns___la_SOURCES += rrtype.cc
libb10_dns___la_SOURCES += question.h question.cc
libb10_dns___la_SOURCES += serial.h serial.cc
libb10_dns___la_SOURCES += tsig.h tsig.cc
libb10_dns___la_SOURCES += tsigerror.h tsigerror.cc
libb10_dns___la_SOURCES += tsigkey.h tsigkey.cc
libb10_dns___la_SOURCES += tsigrecord.h tsigrecord.cc
libb10_dns___la_SOURCES += character_string.h character_string.cc
libb10_dns___la_SOURCES += master_loader_callbacks.h
libb10_dns___la_SOURCES += master_loader.h
libb10_dns___la_SOURCES += rdata/generic/detail/nsec_bitmap.h
libb10_dns___la_SOURCES += rdata/generic/detail/nsec_bitmap.cc
libb10_dns___la_SOURCES += rdata/generic/detail/nsec3param_common.cc
libb10_dns___la_SOURCES += rdata/generic/detail/nsec3param_common.h
libb10_dns___la_SOURCES += rdata/generic/detail/txt_like.h
libb10_dns___la_SOURCES += rdata/generic/detail/ds_like.h

libb10_dns___la_CPPFLAGS = $(AM_CPPFLAGS)
# Most applications of libdns++ will only implicitly rely on libcryptolink,
# so we add the dependency here so that the applications don't have to link
# libcryptolink explicitly.
libb10_dns___la_LIBADD = $(top_builddir)/src/lib/cryptolink/libb10-cryptolink.la
libb10_dns___la_LIBADD += $(top_builddir)/src/lib/util/libb10-util.la

nodist_libdns___include_HEADERS = rdataclass.h rrclass.h rrtype.h
nodist_libb10_dns___la_SOURCES = rdataclass.cc rrparamregistry.cc

rrclass.h: rrclass-placeholder.h
rrtype.h: rrtype-placeholder.h
rrparamregistry.cc: rrparamregistry-placeholder.cc
rrclass.h rrtype.h rrparamregistry.cc rdataclass.h rdataclass.cc: Makefile
	./gen-rdatacode.py

libdns___includedir = $(includedir)/$(PACKAGE_NAME)/dns
libdns___include_HEADERS = \
	edns.h \
	exceptions.h \
	labelsequence.h \
	message.h \
	master_lexer.h \
	masterload.h \
	messagerenderer.h \
	name.h \
	question.h \
	opcode.h \
	rcode.h \
	rdata.h \
	rrparamregistry.h \
	rrset.h \
	rrttl.h \
	tsigkey.h
# Purposely not installing these headers:
# name_internal.h: used only internally, and not actually DNS specific
# rdata/*/detail/*.h: these are internal use only
# rrclass-placeholder.h
# rrtype-placeholder.h
