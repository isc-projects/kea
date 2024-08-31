AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CXXFLAGS=$(KEA_CXXFLAGS)

noinst_SCRIPTS = dhcp_test_lib.sh xml_reporting_test_lib.sh

if HAVE_GTEST
noinst_LTLIBRARIES = libkea-testutils.la

libkea_testutils_la_SOURCES  = io_utils.cc io_utils.h
libkea_testutils_la_SOURCES += sandbox.h
libkea_testutils_la_SOURCES += log_utils.cc log_utils.h
libkea_testutils_la_SOURCES += test_to_element.cc test_to_element.h
libkea_testutils_la_SOURCES += threaded_test.cc threaded_test.h
libkea_testutils_la_SOURCES += unix_control_client.cc unix_control_client.h
libkea_testutils_la_SOURCES += user_context_utils.cc user_context_utils.h
libkea_testutils_la_SOURCES += gtest_utils.h
libkea_testutils_la_SOURCES += multi_threading_utils.h
libkea_testutils_la_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
libkea_testutils_la_LIBADD  = $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
libkea_testutils_la_LIBADD += $(top_builddir)/src/lib/dns/libkea-dns++.la
endif

# Include common libraries being used by shell-based tests.
SHLIBS = dhcp_test_lib.sh.in xml_reporting_test_lib.sh.in

EXTRA_DIST = $(SHLIBS)

CLEANFILES = dhcp_test_lib.sh xml_reporting_test_lib.sh
