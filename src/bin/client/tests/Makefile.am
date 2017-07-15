SHTESTS =
# The test of dynamic reconfiguration based on signals will work only
# if we are using file based configuration approach.
SHTESTS += clnt_process_tests.sh

noinst_SCRIPTS = clnt_process_tests.sh

EXTRA_DIST  = clnt_process_tests.sh.in

# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	for shtest in $(SHTESTS) ; do \
	echo Running test: $$shtest ; \
	export KEA_LOCKFILE_DIR=$(abs_top_builddir); \
	export KEA_PIDFILE_DIR=$(abs_top_builddir); \
	${SHELL} $(abs_builddir)/$$shtest || exit ; \
	done

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/bin # for generated spec_config.h header
AM_CPPFLAGS += -I$(top_srcdir)/src/bin
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/bin/client/tests\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"
AM_CPPFLAGS += -DCFG_EXAMPLES=\"$(abs_top_srcdir)/doc/examples/client\"

DISTCLEANFILES = clnt_process_tests.sh

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

TESTS_ENVIRONMENT = \
        $(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST

TESTS += clnt_unittests

clnt_unittests_SOURCES  = clnt_unittests.cc

clnt_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
clnt_unittests_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS)
clnt_unittests_LDFLAGS += $(GTEST_LDFLAGS)

clnt_unittests_LDADD = $(top_builddir)/src/bin/client/libclnt.la
clnt_unittests_LDADD += $(top_builddir)/src/lib/process/testutils/libprocesstest.la
clnt_unittests_LDADD += $(top_builddir)/src/lib/process/libkea-process.la
clnt_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
clnt_unittests_LDADD += $(top_builddir)/src/lib/asiodns/libkea-asiodns.la
clnt_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
clnt_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
clnt_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
clnt_unittests_LDADD += $(top_builddir)/src/lib/hooks/libkea-hooks.la
clnt_unittests_LDADD += $(top_builddir)/src/lib/util/threads/libkea-threads.la
clnt_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
clnt_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
clnt_unittests_LDADD += $(LOG4CPLUS_LIBS) $(CRYPTO_LIBS)
clnt_unittests_LDADD += $(BOOST_LIBS) $(GTEST_LDADD)

endif

noinst_PROGRAMS = $(TESTS)
