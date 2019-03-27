AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = command_interpreter_unittests.cc
run_unittests_SOURCES += data_unittests.cc
run_unittests_SOURCES += data_file_unittests.cc
run_unittests_SOURCES += element_value_unittests.cc
run_unittests_SOURCES += json_feed_unittests.cc
run_unittests_SOURCES += simple_parser_unittest.cc
run_unittests_SOURCES += stamped_element_unittest.cc
run_unittests_SOURCES += stamped_value_unittest.cc
run_unittests_SOURCES += user_context_unittests.cc
run_unittests_SOURCES += run_unittests.cc
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)

run_unittests_LDADD =  $(top_builddir)/src/lib/cc/libkea-cc.la
run_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
run_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
run_unittests_LDADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS) $(GTEST_LDADD)

endif

noinst_PROGRAMS = $(TESTS)
