AM_CPPFLAGS = -I$(top_builddir)/include -I$(top_srcdir)/ext

CLEANFILES = *.gcno *.gcda
CLEANFILES += rrclass.h rrtype.h rrparamregistry.cc rdataclass.h rdataclass.cc

# auto-generate by gen-rdatacode.py:
BUILT_SOURCES = rrclass.h rrtype.h rrparamregistry.cc

lib_LTLIBRARIES = libdns.la
libdns_la_SOURCES = buffer.h name.cc name.h messagerenderer.h messagerenderer.cc
libdns_la_SOURCES += rrparamregistry.h rrparamregistry.cc
libdns_la_SOURCES += rrclass.h rrclass.cc rrtype.h rrtype.cc rrttl.h rrttl.cc
libdns_la_SOURCES += rdata.h rdata.cc
libdns_la_SOURCES += rdataclass.h rdataclass.cc
libdns_la_SOURCES += rrset.h rrset.cc
libdns_la_SOURCES += question.h question.cc
libdns_la_SOURCES += message.h message.cc
libdns_la_SOURCES += base64.h base64.cc

rrclass.h: rrclass-placeholder.h
rrtype.h: rrtype-placeholder.h
rrparamregistry.cc: rrparamregistry-placeholder.cc
rrclass.h rrtype.h rrparamregistry.cc rdataclass.h rdataclass.cc: Makefile
	./gen-rdatacode.py
tests: libdns.la
