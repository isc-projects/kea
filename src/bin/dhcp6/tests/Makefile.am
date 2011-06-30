PYCOVERAGE_RUN = @PYCOVERAGE_RUN@
#PYTESTS = args_test.py bind10_test.py
# NOTE: this has a generated test found in the builddir
PYTESTS = dhcp6_test.py
EXTRA_DIST = $(PYTESTS)

# If necessary (rare cases), explicitly specify paths to dynamic libraries
# required by loadable python modules.
LIBRARY_PATH_PLACEHOLDER =
if SET_ENV_LIBRARY_PATH
LIBRARY_PATH_PLACEHOLDER += $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/cc/.libs:$(abs_top_builddir)/src/lib/config/.libs:$(abs_top_builddir)/src/lib/log/.libs:$(abs_top_builddir)/src/lib/util/.libs:$(abs_top_builddir)/src/lib/exceptions/.libs:$$$(ENV_LIBRARY_PATH)
endif

# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	for pytest in $(PYTESTS) ; do \
	echo Running test: $$pytest ; \
	env PYTHONPATH=$(abs_top_srcdir)/src/lib/python:$(abs_top_builddir)/src/lib/python:$(abs_top_builddir)/src/bin/bind10 \
	$(LIBRARY_PATH_PLACEHOLDER) \
	BIND10_MSGQ_SOCKET_FILE=$(abs_top_builddir)/msgq_socket \
		$(PYCOVERAGE_RUN) $(abs_srcdir)/$$pytest || exit ; \
	done


AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/bin # for generated spec_config.h header
AM_CPPFLAGS += -I$(top_srcdir)/src/bin
AM_CPPFLAGS += -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_DIR=\"$(abs_top_srcdir)/src/lib/testutils/testdata\"
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/lib/testutils/testdata\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

TESTS =
if HAVE_GTEST

TESTS += run_unittests

run_unittests_SOURCES  = ../addr6.h ../addr6.cc
run_unittests_SOURCES += ../pkt6.h ../pkt6.cc
run_unittests_SOURCES += ../iface_mgr.h ../iface_mgr.cc
run_unittests_SOURCES += ../dhcp6_srv.h ../dhcp6_srv.cc
run_unittests_SOURCES += addr6_unittest.cc
run_unittests_SOURCES += run_unittests.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
run_unittests_LDADD = $(GTEST_LDADD)
run_unittests_LDADD += $(SQLITE_LIBS)
run_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libasiolink.la
run_unittests_LDADD += $(top_builddir)/src/lib/config/libcfgclient.la
run_unittests_LDADD += $(top_builddir)/src/lib/cc/libcc.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
run_unittests_LDADD += $(top_builddir)/src/lib/log/liblog.la
endif

noinst_PROGRAMS = $(TESTS)
