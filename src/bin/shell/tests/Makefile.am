PYTESTS =
SHTESTS =
EXTRA_DIST =

if KEA_SHELL

# Ok, shell is enabled. Let's run those tests.
PYTESTS += shell_unittest.py
SHTESTS += shell_process_tests.sh
noinst_SCRIPTS = $(PYTESTS) $(SHTESTS)

# test using command-line arguments, so use check-local target instead of TESTS
check-local: check-shell check-python

check-python:
	@for pytest in $(PYTESTS) ; do \
	echo Running python test: $$pytest ; \
	chmod +x $(abs_builddir)/$$pytest ; \
	PYTHONPATH=$(PYTHONPATH):$(abs_top_builddir)/src/bin/shell python $(abs_builddir)/$$pytest || exit ; \
	done

check-shell:
	@for shtest in $(SHTESTS) ; do \
	echo Running shell test: $$shtest ; \
	export KEA_LOCKFILE_DIR=$(abs_top_builddir); \
	export KEA_PIDFILE_DIR=$(abs_top_builddir); \
	${SHELL} $(abs_builddir)/$$shtest || exit ; \
	done

else

# Nope, shell is disabled. Let's keep the files in EXTRA_DIST, so they get
# included in make dist, but don't do anything special about them.
EXTRA_DIST += shell_unittest.py shell_process_tests.sh

endif


CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
