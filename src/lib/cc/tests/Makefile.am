AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns

AM_CXXFLAGS = $(KEA_CXXFLAGS)
if USE_GXX			#XXX: see ../Makefile.am
AM_CXXFLAGS += -Wno-unused-parameter
endif

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += run_unittests
# (TODO: these need to be completed and moved to tests/)
run_unittests_SOURCES = data_unittests.cc run_unittests.cc
run_unittests_SOURCES += data_file_unittests.cc
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)

# We need to put our libs first, in case gtest (or any dependency, really)
# is installed in the same location as a different version of bind10
# Otherwise the linker may not use the source tree libs
run_unittests_LDADD =  $(top_builddir)/src/lib/cc/libkea-cc.la
run_unittests_LDADD +=  $(top_builddir)/src/lib/log/libkea-log.la
run_unittests_LDADD +=  $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
run_unittests_LDADD +=  $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
run_unittests_LDADD += $(GTEST_LDADD)

endif

noinst_PROGRAMS = $(TESTS)
