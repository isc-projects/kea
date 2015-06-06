AUTOMAKE_OPTIONS = subdir-objects

SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/util -I$(top_builddir)/src/lib/util
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda
CLEANFILES += s-rdatacode
# These two are created with rrtype/class.h, so not explicitly listed in
# BUILT_SOURCES.
CLEANFILES += python/rrtype_constants_inc.cc
CLEANFILES += python/rrclass_constants_inc.cc

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
EXTRA_DIST += rdata/generic/detail/char_string.cc
EXTRA_DIST += rdata/generic/detail/char_string.h
EXTRA_DIST += rdata/generic/detail/lexer_util.h
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
EXTRA_DIST += rdata/generic/tlsa_52.cc
EXTRA_DIST += rdata/generic/tlsa_52.h
EXTRA_DIST += rdata/generic/txt_16.cc
EXTRA_DIST += rdata/generic/txt_16.h
EXTRA_DIST += rdata/generic/minfo_14.cc
EXTRA_DIST += rdata/generic/minfo_14.h
EXTRA_DIST += rdata/generic/afsdb_18.cc
EXTRA_DIST += rdata/generic/afsdb_18.h
EXTRA_DIST += rdata/generic/caa_257.cc
EXTRA_DIST += rdata/generic/caa_257.h
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

noinst_SCRIPTS = gen-rdatacode.py

# auto-generate by gen-rdatacode.py:
BUILT_SOURCES = rrclass.h rrtype.h rrparamregistry.cc
BUILT_SOURCES += rdataclass.h rdataclass.cc

lib_LTLIBRARIES = libkea-dns++.la

libkea_dns___la_LDFLAGS = -no-undefined -version-info 2:0:0

libkea_dns___la_SOURCES =
libkea_dns___la_SOURCES += dns_fwd.h
libkea_dns___la_SOURCES += edns.h edns.cc
libkea_dns___la_SOURCES += exceptions.h exceptions.cc
libkea_dns___la_SOURCES += master_lexer_inputsource.h master_lexer_inputsource.cc
libkea_dns___la_SOURCES += labelsequence.h labelsequence.cc
libkea_dns___la_SOURCES += masterload.h masterload.cc
libkea_dns___la_SOURCES += master_lexer.h master_lexer.cc
libkea_dns___la_SOURCES += master_lexer_state.h
libkea_dns___la_SOURCES += master_loader.h master_loader.cc
libkea_dns___la_SOURCES += message.h message.cc
libkea_dns___la_SOURCES += messagerenderer.h messagerenderer.cc
libkea_dns___la_SOURCES += name.h name.cc
libkea_dns___la_SOURCES += name_internal.h
libkea_dns___la_SOURCES += nsec3hash.h nsec3hash.cc
libkea_dns___la_SOURCES += opcode.h opcode.cc
libkea_dns___la_SOURCES += rcode.h rcode.cc
libkea_dns___la_SOURCES += rdata.h rdata.cc
libkea_dns___la_SOURCES += rdatafields.h rdatafields.cc
libkea_dns___la_SOURCES += rrclass.cc
libkea_dns___la_SOURCES += rrparamregistry.h
libkea_dns___la_SOURCES += rrset.h rrset.cc
libkea_dns___la_SOURCES += rrttl.h rrttl.cc
libkea_dns___la_SOURCES += rrtype.cc
libkea_dns___la_SOURCES += rrcollator.h rrcollator.cc
libkea_dns___la_SOURCES += question.h question.cc
libkea_dns___la_SOURCES += serial.h serial.cc
libkea_dns___la_SOURCES += tsig.h tsig.cc
libkea_dns___la_SOURCES += tsigerror.h tsigerror.cc
libkea_dns___la_SOURCES += tsigkey.h tsigkey.cc
libkea_dns___la_SOURCES += tsigrecord.h tsigrecord.cc
libkea_dns___la_SOURCES += master_loader_callbacks.h master_loader_callbacks.cc
libkea_dns___la_SOURCES += master_loader.h
libkea_dns___la_SOURCES += rrset_collection_base.h
libkea_dns___la_SOURCES += rrset_collection.h rrset_collection.cc
libkea_dns___la_SOURCES += zone_checker.h zone_checker.cc
libkea_dns___la_SOURCES += rdata_pimpl_holder.h
libkea_dns___la_SOURCES += rdata/generic/detail/char_string.h
libkea_dns___la_SOURCES += rdata/generic/detail/char_string.cc
libkea_dns___la_SOURCES += rdata/generic/detail/nsec_bitmap.h
libkea_dns___la_SOURCES += rdata/generic/detail/nsec_bitmap.cc
libkea_dns___la_SOURCES += rdata/generic/detail/nsec3param_common.cc
libkea_dns___la_SOURCES += rdata/generic/detail/nsec3param_common.h
libkea_dns___la_SOURCES += rdata/generic/detail/txt_like.h
libkea_dns___la_SOURCES += rdata/generic/detail/ds_like.h

libkea_dns___la_CPPFLAGS = $(AM_CPPFLAGS)
# Most applications of libdns++ will only implicitly rely on libcryptolink,
# so we add the dependency here so that the applications don't have to link
# libcryptolink explicitly.
libkea_dns___la_LIBADD = $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libkea_dns___la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libkea_dns___la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_dns___la_LIBADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la

# The following files used to be generated, but they are now part of the git tree:
# rrclass.h rrtype.h rrparamregistry.cc rdataclass.h rdataclass.cc
libkea_dns___la_SOURCES += rdataclass.h rrclass.h rrtype.h
libkea_dns___la_SOURCES += rdataclass.cc rrparamregistry.cc

rrclass.h: rrclass-placeholder.h
rrtype.h: rrtype-placeholder.h
rrparamregistry.cc: rrparamregistry-placeholder.cc

s-rdatacode: Makefile $(EXTRA_DIST)
	$(PYTHON) ./gen-rdatacode.py
	touch $@

# In ticket #3413 we removed the whole BIND10/Bundy framework. We also want
# to not require Python3, hence instead of generating the code every time,
# we added the generated files to our repo. It is still possible to regenerate
# those files, but that step is no longer required for successful compilation.

#rrclass.h rrtype.h rrparamregistry.cc rdataclass.h rdataclass.cc: s-rdatacode

libdns___includedir = $(includedir)/$(PACKAGE_NAME)/dns
libdns___include_HEADERS = \
	edns.h \
	exceptions.h \
	dns_fwd.h \
	labelsequence.h \
	message.h \
	masterload.h \
	master_lexer.h \
	master_loader.h \
	master_loader_callbacks.h \
	messagerenderer.h \
	name.h \
	question.h \
	opcode.h \
	rcode.h \
	rdata.h \
	rrparamregistry.h \
	rrset.h \
	rrset_collection_base.h \
	rrset_collection.h \
	rrttl.h \
	tsigkey.h \
	zone_checker.h
# Purposely not installing these headers:
# name_internal.h: used only internally, and not actually DNS specific
# rdata/*/detail/*.h: these are internal use only
# rrclass-placeholder.h
# rrtype-placeholder.h
