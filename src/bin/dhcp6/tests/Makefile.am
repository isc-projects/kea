PYCOVERAGE_RUN = @PYCOVERAGE_RUN@
PYTESTS = dhcp6_test.py
EXTRA_DIST = $(PYTESTS)

# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	for pytest in $(PYTESTS) ; do \
	echo Running test: $$pytest ; \
	PYTHONPATH=$(COMMON_PYTHON_PATH):$(abs_top_srcdir)/src/bin:$(abs_top_builddir)/src/bin/bind10:$(abs_top_builddir)/src/lib/util/io/.libs \
		$(PYCOVERAGE_RUN) $(abs_srcdir)/$$pytest || exit ; \
	done


AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/bin # for generated spec_config.h header
AM_CPPFLAGS += -I$(top_srcdir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

CLEANFILES = $(builddir)/interfaces.txt

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

TESTS =
if HAVE_GTEST

TESTS += dhcp6_unittests

dhcp6_unittests_SOURCES = ../dhcp6_srv.h ../dhcp6_srv.cc
dhcp6_unittests_SOURCES += dhcp6_unittests.cc
dhcp6_unittests_SOURCES += dhcp6_srv_unittest.cc

dhcp6_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
dhcp6_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
dhcp6_unittests_LDADD = $(GTEST_LDADD)
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libasiolink.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libdhcp++.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/log/liblog.la
dhcp6_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
endif

noinst_PROGRAMS = $(TESTS)
