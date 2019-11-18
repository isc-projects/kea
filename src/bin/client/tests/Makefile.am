# The test of dynamic reconfiguration based on signals will work only
# if we are using file based configuration approach.

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/bin # for generated spec_config.h header
AM_CPPFLAGS += -I$(top_srcdir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/bin/client/tests\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"
AM_CPPFLAGS += -DCFG_EXAMPLES=\"$(abs_top_srcdir)/doc/examples/client\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

TESTS_ENVIRONMENT = \
        $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST

TESTS += client_unittests

client_unittests_SOURCES  = client_unittests.cc
client_unittests_SOURCES  += state_machine_unittest.cc

# client_unittests_SOURCES  += ../client_interface.cc

client_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
client_unittests_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS)
client_unittests_LDFLAGS += $(GTEST_LDFLAGS)

#client_unittests_LDADD = $(top_builddir)/src/bin/client/libclient.la
client_unittests_LDADD = $(top_builddir)/src/lib/process/testutils/libprocesstest.la
client_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
client_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
client_unittests_LDADD += $(top_builddir)/src/lib/asiodns/libkea-asiodns.la
client_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
client_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
client_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
client_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
client_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
client_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
client_unittests_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS)
client_unittests_LDADD += $(BOOST_LIBS) $(GTEST_LDADD)

endif

noinst_PROGRAMS = $(TESTS)
