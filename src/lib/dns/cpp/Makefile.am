AM_CPPFLAGS = -I$(top_srcdir)/ext

CLEANFILES = *.gcno *.gcda

lib_LTLIBRARIES = libdns.la
libdns_la_SOURCES = buffer.h name.cc name.h messagerenderer.h messagerenderer.cc
libdns_la_SOURCES += rrparamregistry.h rrparamregistry.cc
libdns_la_SOURCES += rrclass.h rrclass.cc rrtype.h rrtype.cc rrttl.h rrttl.cc
libdns_la_SOURCES += rdata.h rdata.cc rrset.h rrset.cc
libdns_la_SOURCES += question.h question.cc
libdns_la_SOURCES += message.h message.cc
libdns_la_SOURCES += exceptions.h exceptions.cc

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = unittest_util.h unittest_util.cc
run_unittests_SOURCES += buffer_unittest.cc name_unittest.cc
run_unittests_SOURCES += messagerenderer_unittest.cc exceptions_unittest.cc
run_unittests_SOURCES += rrclass_unittest.cc rrtype_unittest.cc
run_unittests_SOURCES += rrttl_unittest.cc
run_unittests_SOURCES += rdata_unittest.cc
run_unittests_SOURCES += rrset_unittest.cc
run_unittests_SOURCES += question_unittest.cc
run_unittests_SOURCES += rrparamregistry_unittest.cc
run_unittests_SOURCES += message_unittest.cc
run_unittests_SOURCES += run_unittests.cc
run_unittests_CPPFLAGS = $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(GTEST_LDFLAGS)
run_unittests_LDADD = .libs/libdns.a $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
