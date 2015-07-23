SHTESTS =

noinst_SCRIPTS = 

EXTRA_DIST  = 

# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	for shtest in $(SHTESTS) ; do \
	echo Running test: $$shtest ; \
	export KEA_LOCKFILE_DIR=$(abs_top_builddir); \
	${SHELL} $(abs_builddir)/$$shtest || exit ; \
	done

AM_CPPFLAGS = -I$(top_srcdir)/src/lib -I$(top_builddir)/src/lib
AM_CPPFLAGS += -I$(top_builddir)/src/bin # for generated spec_config.h header
AM_CPPFLAGS += -I$(top_srcdir)/src/bin
AM_CPPFLAGS += -I$(top_builddir)/src/lib/cc
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/asiolink
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_DIR=\"$(abs_top_srcdir)/src/lib/testutils/testdata\"
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/bin/lfc/tests\"
AM_CPPFLAGS += -DINSTALL_PROG=\"$(abs_top_srcdir)/install-sh\"

CLEANFILES = $(builddir)/interfaces.txt $(builddir)/logger_lockfile

DISTCLEANFILES = 

AM_CXXFLAGS = $(KEA_CXXFLAGS)
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

TESTS += lfc_unittests

lfc_unittests_SOURCES = lfc_unittests.cc
lfc_unittests_SOURCES += lfc_controller_unittests.cc

lfc_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
lfc_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
lfc_unittests_LDADD = $(GTEST_LDADD)
lfc_unittests_LDADD += $(top_builddir)/src/bin/lfc/liblfc.la
lfc_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
lfc_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
lfc_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
lfc_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la
lfc_unittests_LDADD += $(top_builddir)/src/lib/dhcpsrv/libkea-dhcpsrv.la
lfc_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
lfc_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
lfc_unittests_LDADD += $(top_builddir)/src/lib/cfgrpt/libcfgrpt.la

endif

noinst_PROGRAMS = $(TESTS)
