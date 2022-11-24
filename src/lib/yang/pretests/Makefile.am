CLEANFILES = *.gcno *.gcda

TESTS = sysrepo_setup_tests

sysrepo_setup_tests_SOURCES = sysrepo_setup_tests.cc
sysrepo_setup_tests_CPPFLAGS  =
sysrepo_setup_tests_CPPFLAGS += -I$(top_builddir)/src/lib
sysrepo_setup_tests_CPPFLAGS += -I$(top_srcdir)/src/lib
sysrepo_setup_tests_CPPFLAGS += -DKEATEST_MODULE
sysrepo_setup_tests_CPPFLAGS += $(LIBYANG_CPPFLAGS)
sysrepo_setup_tests_CPPFLAGS += $(LIBYANG_INCLUDEDIR)
sysrepo_setup_tests_CPPFLAGS += $(LIBYANGCPP_CPPFLAGS)
sysrepo_setup_tests_CPPFLAGS += $(LIBYANGCPP_INCLUDEDIR)
sysrepo_setup_tests_CPPFLAGS += $(SYSREPO_CPPFLAGS)
sysrepo_setup_tests_CPPFLAGS += $(SYSREPO_INCLUDEDIR)
sysrepo_setup_tests_CPPFLAGS += $(SYSREPOCPP_CPPFLAGS)
sysrepo_setup_tests_CPPFLAGS += $(SYSREPOCPP_INCLUDEDIR)
sysrepo_setup_tests_LDFLAGS = $(AM_LDFLAGS)
sysrepo_setup_tests_LDADD  =
sysrepo_setup_tests_LDADD += $(LIBYANG_LIBS)
sysrepo_setup_tests_LDADD += $(LIBYANGCPP_LIBS)
sysrepo_setup_tests_LDADD += $(SYSREPO_LIBS)
sysrepo_setup_tests_LDADD += $(SYSREPOCPP_LIBS)

noinst_PROGRAMS = $(TESTS)
