SUBDIRS = .

SHTESTS = keactrl_tests.sh

noinst_SCRIPTS = keactrl_tests.sh

CLEANFILES = *.log *.json
DISTCLEANFILES = keactrl_tests.sh

EXTRA_DIST = keactrl_tests.sh.in

# Execute all test scripts.
check-local:
	for shtest in $(SHTESTS) ; do \
	echo Running test: $$shtest ; \
	chmod +x $(abs_builddir)/$$shtest ; \
	export KEA_LOCKFILE_DIR=$(abs_top_builddir); \
	export KEACTRL_BUILD_DIR=$(abs_top_builddir); \
	export KEA_PIDFILE_DIR=$(abs_top_builddir); \
	export KEACTRL_CONF=$(abs_top_builddir)/src/bin/keactrl/tests/keactrl_test.conf; \
	${SHELL} $(abs_builddir)/$$shtest || exit ; \
	done
