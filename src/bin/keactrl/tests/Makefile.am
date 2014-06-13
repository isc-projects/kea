SUBDIRS = .

SHTESTS = keactrl_tests.sh

noinst_SCRIPTS = keactrl_tests.sh

CLEANFILES = *.log *.json

EXTRA_DIST = keactrl_tests.sh.in

check-local:
	for shtest in $(SHTESTS) ; do \
	echo Running test: $$shtest ; \
	chmod +x $(abs_builddir)/$$shtest ; \
	export KEACTRL_BUILD_DIR=$(abs_top_builddir); \
	export KEACTRL_CONF=$(abs_top_builddir)/src/bin/keactrl/tests/keactrl_test.conf; \
	$(abs_builddir)/$$shtest || exit ; \
	done
