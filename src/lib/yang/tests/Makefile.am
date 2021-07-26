AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += $(SYSREPO_CPPFLAGS)
AM_CPPFLAGS += $(SYSREPO_INCLUDEDIR)
AM_CPPFLAGS += -DCFG_EXAMPLES=\"$(abs_top_srcdir)/doc/examples\"
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
run_unittests_SOURCES  = json_configs.h yang_configs.h
run_unittests_SOURCES += adaptor_unittests.cc
run_unittests_SOURCES += adaptor_option_unittests.cc
run_unittests_SOURCES += adaptor_pool_unittests.cc
run_unittests_SOURCES += adaptor_host_unittests.cc
run_unittests_SOURCES += adaptor_subnet_unittests.cc
run_unittests_SOURCES += adaptor_config_unittests.cc
run_unittests_SOURCES += sysrepo_setup.h
run_unittests_SOURCES += translator_unittests.cc
run_unittests_SOURCES += translator_control_socket_unittests.cc
run_unittests_SOURCES += translator_database_unittests.cc
run_unittests_SOURCES += translator_logger_unittests.cc
run_unittests_SOURCES += translator_option_data_unittests.cc
run_unittests_SOURCES += translator_option_def_unittests.cc
run_unittests_SOURCES += translator_class_unittests.cc
run_unittests_SOURCES += translator_pool_unittests.cc
run_unittests_SOURCES += translator_pd_pool_unittests.cc
run_unittests_SOURCES += translator_host_unittests.cc
run_unittests_SOURCES += translator_subnet_unittests.cc
run_unittests_SOURCES += translator_shared_network_unittests.cc
run_unittests_SOURCES += translator_utils_unittests.cc
run_unittests_SOURCES += config_unittests.cc
run_unittests_SOURCES += run_unittests.cc
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)

run_unittests_LDADD =  $(top_builddir)/src/lib/yang/testutils/libyangtest.la
run_unittests_LDADD += $(top_builddir)/src/lib/yang/libkea-yang.la
run_unittests_LDADD += $(top_builddir)/src/lib/testutils/libkea-testutils.la
run_unittests_LDADD += $(top_builddir)/src/lib/cc/libkea-cc.la
run_unittests_LDADD += $(top_builddir)/src/lib/asiolink/libkea-asiolink.la
run_unittests_LDADD += $(top_builddir)/src/lib/log/libkea-log.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
run_unittests_LDADD += $(LOG4CPLUS_LIBS) $(BOOST_LIBS)
run_unittests_LDADD += $(SYSREPO_LIBS) $(GTEST_LDADD)

endif

noinst_PROGRAMS = $(TESTS)
