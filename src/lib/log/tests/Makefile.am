SUBDIRS = .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS =
if HAVE_GTEST

# Define the flags used in each set of tests
COMMON_CXXFLAGS = $(AM_CXXFLAGS)
if USE_CLANGPP
# Workaround unused variables tcout and tcerr in log4cplus's streams.h.
COMMON_CXXFLAGS += -Wno-unused-variable
endif
COMMON_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES) $(LOG4CPLUS_INCLUDES)
COMMON_LDFLAGS  = $(AM_LDFLAGS)  $(GTEST_LDFLAGS)

COMMON_LDADD  = $(GTEST_LDADD)
COMMON_LDADD += $(top_builddir)/src/lib/log/liblog.la
COMMON_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
COMMON_LDADD += $(top_builddir)/src/lib/util/libutil.la
COMMON_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
COMMON_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la

# Set of unit tests for the general logging classes
TESTS += run_unittests
run_unittests_SOURCES  = run_unittests.cc
run_unittests_SOURCES += log_formatter_unittest.cc
run_unittests_SOURCES += logger_level_impl_unittest.cc
run_unittests_SOURCES += logger_level_unittest.cc
run_unittests_SOURCES += logger_manager_unittest.cc
run_unittests_SOURCES += logger_name_unittest.cc
run_unittests_SOURCES += logger_support_unittest.cc
run_unittests_SOURCES += logger_unittest.cc
run_unittests_SOURCES += logger_specification_unittest.cc
run_unittests_SOURCES += message_dictionary_unittest.cc
run_unittests_SOURCES += message_reader_unittest.cc
run_unittests_SOURCES += output_option_unittest.cc

run_unittests_CPPFLAGS = $(COMMON_CPPFLAGS)
run_unittests_CXXFLAGS = $(COMMON_CXXFLAGS)
run_unittests_LDADD    = $(COMMON_LDADD)
run_unittests_LDFLAGS  = $(COMMON_LDFLAGS)

# logging initialization tests.  These are put in separate programs to
# ensure that the initialization status at the start of each test is known,
# and to prevent circumstances where the execution of one test affects the
# starting conditions of the next.
TESTS += initializer_unittests_1
initializer_unittests_1_SOURCES  = run_initializer_unittests.cc
initializer_unittests_1_SOURCES += message_initializer_1_unittest.cc
initializer_unittests_1_SOURCES += message_initializer_1a_unittest.cc

initializer_unittests_1_CPPFLAGS = $(COMMON_CPPFLAGS)
initializer_unittests_1_CXXFLAGS = $(COMMON_CXXFLAGS)
initializer_unittests_1_LDADD    = $(COMMON_LDADD)
initializer_unittests_1_LDFLAGS  = $(COMMON_LDFLAGS)

TESTS += initializer_unittests_2
initializer_unittests_2_SOURCES  = run_initializer_unittests.cc
initializer_unittests_2_SOURCES += message_initializer_2_unittest.cc

initializer_unittests_2_CPPFLAGS = $(COMMON_CPPFLAGS)
initializer_unittests_2_CXXFLAGS = $(COMMON_CXXFLAGS)
initializer_unittests_2_LDADD    = $(COMMON_LDADD)
initializer_unittests_2_LDFLAGS  = $(COMMON_LDFLAGS)

endif

noinst_PROGRAMS = logger_example
logger_example_SOURCES = logger_example.cc
logger_example_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
logger_example_LDFLAGS = $(AM_LDFLAGS)
logger_example_LDADD  = $(LOG4CPLUS_LIBS)
logger_example_LDADD += $(top_builddir)/src/lib/log/liblog.la
logger_example_LDADD += $(top_builddir)/src/lib/util/libutil.la
logger_example_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la

noinst_PROGRAMS += init_logger_test
init_logger_test_SOURCES = init_logger_test.cc
init_logger_test_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
init_logger_test_LDFLAGS = $(AM_LDFLAGS)
init_logger_test_LDADD  = $(LOG4CPLUS_LIBS)
init_logger_test_LDADD += $(top_builddir)/src/lib/log/liblog.la
init_logger_test_LDADD += $(top_builddir)/src/lib/util/libutil.la
init_logger_test_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la

noinst_PROGRAMS += $(TESTS)

# Additional test using the shell.  These are principally tests
# where the global logging environment is affected, and where the
# output needs to be compared with stored output (where "cut" and
# "diff" are useful utilities).

check-local:
	$(SHELL) $(abs_builddir)/console_test.sh
	$(SHELL) $(abs_builddir)/destination_test.sh
	$(SHELL) $(abs_builddir)/init_logger_test.sh
	$(SHELL) $(abs_builddir)/local_file_test.sh
	$(SHELL) $(abs_builddir)/severity_test.sh
