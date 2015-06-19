SUBDIRS = testdata .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_DIR=\"$(abs_top_srcdir)/src/lib/testutils/testdata\"
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/lib/config/tests\"

AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = module_spec_unittests.cc
run_unittests_SOURCES += command_socket_factory_unittests.cc
run_unittests_SOURCES += config_data_unittests.cc run_unittests.cc
run_unittests_SOURCES += command_mgr_unittests.cc

run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
run_unittests_LDADD =  $(GTEST_LDADD)
run_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
run_unittests_LDADD += $(top_builddir)/src/lib/config/libkea-cfgclient.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
run_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
run_unittests_LDADD += $(top_builddir)/src/lib/dhcp/libkea-dhcp++.la

endif

noinst_PROGRAMS = $(TESTS)
