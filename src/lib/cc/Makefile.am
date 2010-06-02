AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns

AM_CXXFLAGS = $(B10_CXXFLAGS)
# ASIO header files used in session.cc will trigger "unused-parameter"
# error.  Unfortunately there doesn't seem to be an easy way to selectively
# avoid the error.  As a short term workaround we suppress this warning
# for the entire this module.  See also src/bin/auth/Makefile.am.
AM_CXXFLAGS += -Wno-unused-parameter

lib_LIBRARIES = libcc.a
libcc_a_SOURCES = data.cc data.h session.cc session.h

CLEANFILES = *.gcno *.gcda

session_config.h: session_config.h.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" session_config.h.pre >$@

BUILT_SOURCES = session_config.h 

TESTS =
if HAVE_GTEST
TESTS += run_unittests
# (TODO: these need to be completed and moved to tests/)
run_unittests_SOURCES = data_unittests.cc session_unittests.cc run_unittests.cc
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
# TODO: remove PTHREAD_LDFLAGS (and from configure too)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS) $(PTHREAD_LDFLAGS)

run_unittests_LDADD = libcc.a $(GTEST_LDADD)
run_unittests_LDADD +=  $(top_builddir)/src/lib/dns/.libs/libdns.a
run_unittests_LDADD +=  $(top_builddir)/src/lib/exceptions/.libs/libexceptions.a

endif

noinst_PROGRAMS = $(TESTS)
