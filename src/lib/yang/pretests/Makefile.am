CLEANFILES = *.gcno *.gcda

TESTS = sysrepo_setup_tests
sysrepo_setup_tests_SOURCES = sysrepo_setup_tests.cc
sysrepo_setup_tests_CPPFLAGS = $(SYSREPO_CPPFLAGS) -DSYSREPO_REPO=\"@SYSREPO_REPO@\"
sysrepo_setup_tests_LDFLAGS = $(AM_LDFLAGS)
sysrepo_setup_tests_LDADD = $(SYSREPO_LIBS)

noinst_PROGRAMS = $(TESTS)
