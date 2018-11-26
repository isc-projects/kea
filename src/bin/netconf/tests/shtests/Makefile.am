SHTESTS = netconf_tests.sh

noinst_SCRIPTS = netconf_tests.sh

EXTRA_DIST = netconf_tests.sh.in

# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	for shtest in $(SHTESTS) ; do \
	echo Running test: $$shtest ; \
	export KEA_LOCKFILE_DIR=$(abs_top_builddir); \
	export KEA_PIDFILE_DIR=$(abs_top_builddir); \
	${SHELL} $(abs_builddir)/$$shtest || exit ; \
	done

CLEANFILES = *.json *.log

DISTCLEANFILES = netconf_tests.sh
