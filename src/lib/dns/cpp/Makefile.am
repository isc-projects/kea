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
libdns_la_SOURCES += rrsetlist.h rrsetlist.cc
libdns_la_SOURCES += question.h question.cc
libdns_la_SOURCES += message.h message.cc
libdns_la_SOURCES += base64.h base64.cc

rrclass.h: rrclass-placeholder.h
rrtype.h: rrtype-placeholder.h
rrparamregistry.cc: rrparamregistry-placeholder.cc
rrclass.h rrtype.h rrparamregistry.cc rdataclass.h rdataclass.cc: Makefile
	./gen-rdatacode.py

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = unittest_util.h unittest_util.cc
run_unittests_SOURCES += buffer_unittest.cc name_unittest.cc
run_unittests_SOURCES += messagerenderer_unittest.cc
run_unittests_SOURCES += rrclass_unittest.cc rrtype_unittest.cc
run_unittests_SOURCES += rrttl_unittest.cc
run_unittests_SOURCES += rdata_unittest.cc
run_unittests_SOURCES += rrset_unittest.cc
run_unittests_SOURCES += rrsetlist_unittest.cc
run_unittests_SOURCES += question_unittest.cc
run_unittests_SOURCES += rrparamregistry_unittest.cc
run_unittests_SOURCES += message_unittest.cc
run_unittests_SOURCES += base64_unittest.cc
run_unittests_SOURCES += run_unittests.cc
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
run_unittests_LDADD = .libs/libdns.a $(GTEST_LDADD)
run_unittests_LDADD +=  $(top_builddir)/src/lib/exceptions/cpp/.libs/libexceptions.a
endif

noinst_PROGRAMS = $(TESTS)
