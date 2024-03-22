AUTOMAKE_OPTIONS = subdir-objects

SUBDIRS = . tests

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

CLEANFILES = *.gcno *.gcda

BUILT_SOURCES = rrclass.h rrtype.h rrparamregistry.cc
BUILT_SOURCES += rdataclass.h rdataclass.cc

lib_LTLIBRARIES = libkea-dns++.la

libkea_dns___la_LDFLAGS = -no-undefined -version-info 55:0:0
libkea_dns___la_LDFLAGS += $(AM_LDFLAGS) $(CRYPTO_LDFLAGS)

libkea_dns___la_SOURCES =
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
libkea_dns___la_SOURCES += question.h question.cc
libkea_dns___la_SOURCES += serial.h serial.cc
libkea_dns___la_SOURCES += time_utils.h time_utils.cc
libkea_dns___la_SOURCES += tsig.h tsig.cc
libkea_dns___la_SOURCES += tsigerror.h tsigerror.cc
libkea_dns___la_SOURCES += tsigkey.h tsigkey.cc
libkea_dns___la_SOURCES += tsigrecord.h tsigrecord.cc
libkea_dns___la_SOURCES += master_loader_callbacks.h
libkea_dns___la_SOURCES += master_loader.h
libkea_dns___la_SOURCES += txt_like.h
libkea_dns___la_SOURCES += char_string.h char_string.cc


libkea_dns___la_CPPFLAGS = $(AM_CPPFLAGS)
libkea_dns___la_LIBADD  = $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
libkea_dns___la_LIBADD += $(top_builddir)/src/lib/util/libkea-util.la
libkea_dns___la_LIBADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
libkea_dns___la_LIBADD += $(CRYPTO_LIBS)

# The following files used to be generated, but they are now part of the git tree:
# rrclass.h rrtype.h rrparamregistry.cc rdataclass.h rdataclass.cc
libkea_dns___la_SOURCES += rdataclass.h rrclass.h rrtype.h
libkea_dns___la_SOURCES += rdataclass.cc rrparamregistry.cc

libdns___includedir = $(pkgincludedir)/dns
libdns___include_HEADERS = \
	char_string.h \
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
	time_utils.h \
	tsig.h \
	tsigerror.h \
	tsigkey.h \
	tsigrecord.h \
	txt_like.h
# Purposely not installing these headers:
# name_internal.h: used only internally, and not actually DNS specific
