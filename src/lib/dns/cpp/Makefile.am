AM_CPPFLAGS = $(BOOST_INCLUDES)

lib_LTLIBRARIES = libdns.la
libdns_la_SOURCES = buffer.h name.cc name.h messagerenderer.h messagerenderer.cc
libdns_la_SOURCES += rrparamregistry.h rrparamregistry.cc
libdns_la_SOURCES += rrclass.h rrclass.cc rrtype.h rrtype.cc
libdns_la_SOURCES += exceptions.h exceptions.cc

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = unittest_util.h unittest_util.cc
run_unittests_SOURCES += buffer_unittest.cc name_unittest.cc
run_unittests_SOURCES += messagerenderer_unittest.cc exceptions_unittest.cc
run_unittests_SOURCES += rrclass_unittest.cc rrtype_unittest.cc
run_unittests_SOURCES += run_unittests.cc
run_unittests_CPPFLAGS = $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(GTEST_LDFLAGS)
run_unittests_LDADD = .libs/libdns.a $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
