PYCOVERAGE_RUN = @PYCOVERAGE_RUN@

PYTESTS = d2srv_test.py
EXTRA_DIST = $(PYTESTS)

# Explicitly specify paths to dynamic libraries required by loadable python
# modules. That is required on Mac OS systems. Otherwise we will get exception
# about python not being able to load liblog library.
LIBRARY_PATH_PLACEHOLDER =
if SET_ENV_LIBRARY_PATH
LIBRARY_PATH_PLACEHOLDER += $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/cryptolink/.libs:$(abs_top_builddir)/src/lib/dns/.libs:$(abs_top_builddir)/src/lib/dns/python/.libs:$(abs_top_builddir)/src/lib/cc/.libs:$(abs_top_builddir)/src/lib/config/.libs:$(abs_top_builddir)/src/lib/log/.libs:$(abs_top_builddir)/src/lib/util/.libs:$(abs_top_builddir)/src/lib/util/threads/.libs:$(abs_top_builddir)/src/lib/exceptions/.libs:$(abs_top_builddir)/src/lib/util/io/.libs:$(abs_top_builddir)/src/lib/datasrc/.libs:$$$(ENV_LIBRARY_PATH)
endif

# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	for pytest in $(PYTESTS) ; do \
	echo Running test: $$pytest ; \
	PYTHONPATH=$(COMMON_PYTHON_PATH):$(abs_top_srcdir)/src/bin:$(abs_top_builddir)/src/bin/bind10:$(abs_top_builddir)/src/lib/util/io/.libs \
	B10_LOCKFILE_DIR_FROM_BUILD=$(abs_top_builddir) \
	$(LIBRARY_PATH_PLACEHOLDER) \
		$(PYCOVERAGE_RUN) $(abs_srcdir)/$$pytest || exit ; \
	done

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/bin # for generated spec_config.h header
AM_CPPFLAGS += -I$(top_srcdir)/src/bin
AM_CPPFLAGS += -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/asiolink
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_DIR=\"$(abs_top_srcdir)/src/lib/testutils/testdata\"
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/bin/d2srv/tests\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

CLEANFILES = $(builddir)/interfaces.txt $(builddir)/logger_lockfile

AM_CXXFLAGS = $(B10_CXXFLAGS)
if USE_CLANGPP
# Disable unused parameter warning caused by some Boost headers when compiling with clang
AM_CXXFLAGS += -Wno-unused-parameter
endif

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

TESTS_ENVIRONMENT = \
        $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST

TESTS += d2srv_unittests

d2srv_unittests_SOURCES = ../d2srv_log.h ../d2srv_log.cc
d2srv_unittests_SOURCES += d2srv_unittests.cc
nodist_d2srv_unittests_SOURCES = ../d2srv_messages.h ../d2srv_messages.cc

d2srv_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
d2srv_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
d2srv_unittests_LDADD = $(GTEST_LDADD)
d2srv_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libb10-asiolink.la
d2srv_unittests_LDADD += $(top_builddir)/src/lib/cc/libb10-cc.la
d2srv_unittests_LDADD += $(top_builddir)/src/lib/config/libb10-cfgclient.la
d2srv_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libb10-dhcp++.la
d2srv_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libb10-dhcpsrv.la
d2srv_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libb10-exceptions.la
d2srv_unittests_LDADD += $(top_builddir)/src/lib/log/libb10-log.la
d2srv_unittests_LDADD += $(top_builddir)/src/lib/util/libb10-util.la
endif

noinst_PROGRAMS = $(TESTS)
