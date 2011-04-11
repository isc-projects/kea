SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/log -I$(top_builddir)/src/lib/log
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/util -I$(top_builddir)/src/lib/util
AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES  = root_logger_name_unittest.cc
run_unittests_SOURCES += logger_unittest.cc
run_unittests_SOURCES += message_dictionary_unittest.cc
run_unittests_SOURCES += message_reader_unittest.cc
run_unittests_SOURCES += message_initializer_unittest.cc
run_unittests_SOURCES += message_initializer_unittest_2.cc
run_unittests_SOURCES += run_unittests.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)

run_unittests_LDADD  = $(GTEST_LDADD)
run_unittests_LDADD += $(top_builddir)/src/lib/log/liblog.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/libutil.la
endif

TESTS += logger_support_test
logger_support_test_SOURCES = logger_support_test.cc
logger_support_test_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
logger_support_test_LDFLAGS = $(AM_LDFLAGS)
logger_support_test_LDADD  = $(top_builddir)/src/lib/log/liblog.la
logger_support_test_LDADD += $(top_builddir)/src/lib/util/libutil.la

noinst_PROGRAMS = $(TESTS)

# Additional test using the shell
PYTESTS = run_time_init_test.sh
check-local:
	$(SHELL) $(abs_builddir)/run_time_init_test.sh
