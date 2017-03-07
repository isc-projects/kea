PYTESTS = kea-shell_unittest.py

SHTESTS = shell_process_tests.sh

noinst_SCRIPTS = $(PYTESTS) shell_process_tests.sh
EXTRA_DIST = testdata/plugins/testplugin.py

# test using command-line arguments, so use check-local target instead of TESTS
check-local: check-local-shell check-local-python

check-local-python:
	@for pytest in $(PYTESTS) ; do \
	echo Running python test: $$pytest ; \
	chmod +x $(abs_builddir)/$$pytest ; \
	PYTHONPATH=$(PYTHONPATH):$(abs_top_builddir)/src/bin/shell python $(abs_builddir)/$$pytest || exit ; \
	done

check-local-shell:
	@for shtest in $(SHTESTS) ; do \
	echo Running shell test: $$shtest ; \
	export KEA_LOCKFILE_DIR=$(abs_top_builddir); \
	export KEA_PIDFILE_DIR=$(abs_top_builddir); \
	${SHELL} $(abs_builddir)/$$shtest || exit ; \
	done


CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
