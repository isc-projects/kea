CLEANFILES = *.gcno *.gcda

TESTS = sysrepo_setup_tests

sysrepo_setup_tests_SOURCES = sysrepo_setup_tests.cc
sysrepo_setup_tests_CPPFLAGS = -I$(top_builddir)/src/lib
sysrepo_setup_tests_CPPFLAGS += -I$(top_srcdir)/src/lib
sysrepo_setup_tests_CPPFLAGS += $(SYSREPO_CPPFLAGS)
sysrepo_setup_tests_CPPFLAGS += $(SYSREPO_INCLUDEDIR)
sysrepo_setup_tests_CPPFLAGS += -DSYSREPO_REPO=\"@SR_REPO_PATH@\"
sysrepo_setup_tests_LDFLAGS = $(AM_LDFLAGS)
sysrepo_setup_tests_LDADD = $(SYSREPO_LIBS)

noinst_PROGRAMS = $(TESTS)
