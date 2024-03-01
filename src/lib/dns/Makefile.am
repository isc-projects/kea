AUTOMAKE_OPTIONS = subdir-objects

SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda
CLEANFILES += s-rdatacode
# These two are created with rrtype/class.h, so not explicitly listed in
# BUILT_SOURCES.
CLEANFILES += python/rrtype_constants_inc.cc
CLEANFILES += python/rrclass_constants_inc.cc

DISTCLEANFILES = gen-rdatacode.py

EXTRA_DIST = rrclass-placeholder.h
EXTRA_DIST += rrparamregistry-placeholder.cc
EXTRA_DIST += rrtype-placeholder.h

# TODO: double-check that this is the only way
# NOTE: when an rdata file is added, please also add to this list:
EXTRA_DIST += rdata/any_255/tsig_250.cc
EXTRA_DIST += rdata/any_255/tsig_250.h
EXTRA_DIST += rdata/generic/detail/lexer_util.h
EXTRA_DIST += rdata/generic/opt_41.cc
EXTRA_DIST += rdata/generic/opt_41.h
EXTRA_DIST += rdata/generic/ptr_12.cc
EXTRA_DIST += rdata/generic/ptr_12.h
EXTRA_DIST += rdata/generic/rrsig_46.cc
EXTRA_DIST += rdata/generic/rrsig_46.h
EXTRA_DIST += rdata/generic/soa_6.cc
EXTRA_DIST += rdata/generic/soa_6.h
EXTRA_DIST += rdata/generic/tkey_249.cc
EXTRA_DIST += rdata/generic/tkey_249.h
EXTRA_DIST += rdata/in_1/a_1.cc
EXTRA_DIST += rdata/in_1/a_1.h
EXTRA_DIST += rdata/in_1/aaaa_28.cc
EXTRA_DIST += rdata/in_1/aaaa_28.h
EXTRA_DIST += rdata/in_1/dhcid_49.cc
EXTRA_DIST += rdata/in_1/dhcid_49.h
EXTRA_DIST += rdata/template.cc
EXTRA_DIST += rdata/template.h

noinst_SCRIPTS = gen-rdatacode.py

# auto-generate by gen-rdatacode.py:
BUILT_SOURCES = rrclass.h rrtype.h rrparamregistry.cc
BUILT_SOURCES += rdataclass.h rdataclass.cc

lib_LTLIBRARIES = libkea-dns++.la

libkea_dns___la_LDFLAGS = -no-undefined -version-info 54:0:0
libkea_dns___la_LDFLAGS += $(AM_LDFLAGS) $(CRYPTO_LDFLAGS)

libkea_dns___la_SOURCES =
libkea_dns___la_SOURCES += dns_fwd.h
libkea_dns___la_SOURCES += edns.h edns.cc
libkea_dns___la_SOURCES += exceptions.h exceptions.cc
libkea_dns___la_SOURCES += master_lexer_inputsource.h master_lexer_inputsource.cc
libkea_dns___la_SOURCES += labelsequence.h labelsequence.cc
libkea_dns___la_SOURCES += master_lexer.h master_lexer.cc
libkea_dns___la_SOURCES += master_lexer_state.h
libkea_dns___la_SOURCES += master_loader.h master_loader.cc
libkea_dns___la_SOURCES += message.h message.cc
libkea_dns___la_SOURCES += messagerenderer.h messagerenderer.cc
libkea_dns___la_SOURCES += name.h name.cc
libkea_dns___la_SOURCES += name_internal.h
libkea_dns___la_SOURCES += opcode.h opcode.cc
libkea_dns___la_SOURCES += rcode.h rcode.cc
libkea_dns___la_SOURCES += rdata.h rdata.cc
libkea_dns___la_SOURCES += rrclass.cc
libkea_dns___la_SOURCES += rrparamregistry.h
libkea_dns___la_SOURCES += rrset.h rrset.cc
libkea_dns___la_SOURCES += rrttl.h rrttl.cc
libkea_dns___la_SOURCES += rrtype.cc
libkea_dns___la_SOURCES += qid_gen.h qid_gen.cc
libkea_dns___la_SOURCES += question.h question.cc
libkea_dns___la_SOURCES += serial.h serial.cc
libkea_dns___la_SOURCES += tsig.h tsig.cc
libkea_dns___la_SOURCES += tsigerror.h tsigerror.cc
libkea_dns___la_SOURCES += tsigkey.h tsigkey.cc
libkea_dns___la_SOURCES += tsigrecord.h tsigrecord.cc
libkea_dns___la_SOURCES += master_loader_callbacks.h
libkea_dns___la_SOURCES += master_loader.h

libkea_dns___la_CPPFLAGS = $(AM_CPPFLAGS)
libkea_dns___la_LIBADD  = $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libkea_dns___la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libkea_dns___la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_dns___la_LIBADD += $(CRYPTO_LIBS)

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

libdns___includedir = $(pkgincludedir)/dns
libdns___include_HEADERS = \
	dns_fwd.h \
	edns.h \
	exceptions.h \
	labelsequence.h \
	master_lexer.h \
	master_lexer_inputsource.h \
	master_lexer_state.h \
	master_loader.h \
	master_loader_callbacks.h \
	message.h \
	messagerenderer.h \
	name.h \
	opcode.h \
	qid_gen.h \
	question.h \
	rcode.h \
	rdata.h \
	rdataclass.h \
	rrclass.h \
	rrparamregistry.h \
	rrset.h \
	rrttl.h \
	rrtype.h \
	serial.h \
	tsig.h \
	tsigerror.h \
	tsigkey.h \
	tsigrecord.h
# Purposely not installing these headers:
# name_internal.h: used only internally, and not actually DNS specific
# rdata/*/detail/*.h: these are internal use only
# rrclass-placeholder.h
# rrtype-placeholder.h
