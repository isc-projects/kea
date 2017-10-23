PYTESTS = shell_unittest.py
SHTESTS = shell_process_tests.sh
noinst_SCRIPTS = $(PYTESTS) $(SHTESTS)

DISTCLEANFILES = shell_process_tests.sh shell_unittest.py

# test using command-line arguments, so use check-local target instead of TESTS
check-local: check-shell check-python

check-python:
	@for pytest in $(PYTESTS) ; do \
	echo Running python test: $$pytest ; \
	chmod +x $(abs_builddir)/$$pytest ; \
	PYTHONPATH=$(PYTHONPATH):$(abs_top_srcdir)/src/bin/shell python $(abs_builddir)/$$pytest || exit ; \
	done

check-shell:
	@for shtest in $(SHTESTS) ; do \
	echo Running shell test: $$shtest ; \
	export KEA_LOCKFILE_DIR=$(abs_top_builddir); \
	export KEA_PIDFILE_DIR=$(abs_top_builddir); \
	export PYTHONPATH=$(PYTHONPATH):$(abs_top_srcdir)/src/bin/shell; \
	${SHELL} $(abs_builddir)/$$shtest || exit ; \
	done

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
