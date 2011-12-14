PYCOVERAGE_RUN = @PYCOVERAGE_RUN@

# If necessary (rare cases), explicitly specify paths to dynamic libraries
# required by loadable python modules.
LIBRARY_PATH_PLACEHOLDER =
if SET_ENV_LIBRARY_PATH
LIBRARY_PATH_PLACEHOLDER += $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/cryptolink/.libs:$(abs_top_builddir)/src/lib/dns/.libs:$(abs_top_builddir)/src/lib/dns/python/.libs:$(abs_top_builddir)/src/lib/cc/.libs:$(abs_top_builddir)/src/lib/config/.libs:$(abs_top_builddir)/src/lib/log/.libs:$(abs_top_builddir)/src/lib/util/.libs:$(abs_top_builddir)/src/lib/exceptions/.libs:$(abs_top_builddir)/src/lib/util/io/.libs:$(abs_top_builddir)/src/lib/datasrc/.libs:$$$(ENV_LIBRARY_PATH)
endif

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/bin # for generated spec_config.h header
AM_CPPFLAGS += -I$(top_srcdir)/src/bin
AM_CPPFLAGS += -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/asiolink
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_DIR=\"$(abs_top_srcdir)/src/lib/testutils/testdata\"
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/bin/dhcp6/tests\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

CLEANFILES = $(builddir)/interfaces.txt

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

TESTS =
if HAVE_GTEST

TESTS += dhcp4_unittests

dhcp4_unittests_SOURCES == ../dhcp4_srv.h ../dhcp4_srv.cc
dhcp4_unittests_SOURCES += dhcp4_unittests.cc
dhcp4_unittests_SOURCES += dhcp4_srv_unittest.cc

dhcp4_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
dhcp4_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
dhcp4_unittests_LDADD = $(GTEST_LDADD)
dhcp4_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libasiolink.la
dhcp4_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libdhcp++.la
dhcp4_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
dhcp4_unittests_LDADD += $(top_builddir)/src/lib/log/liblog.la
endif

noinst_PROGRAMS = $(TESTS)
