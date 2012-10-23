PYCOVERAGE_RUN = @PYCOVERAGE_RUN@
PYTESTS_GEN = log_console.py
PYTESTS_NOGEN = log_test.py
noinst_SCRIPTS = $(PYTESTS_GEN)
EXTRA_DIST = console.out check_output.sh $(PYTESTS_NOGEN)

# If necessary (rare cases), explicitly specify paths to dynamic libraries
# required by loadable python modules.
LIBRARY_PATH_PLACEHOLDER =
if SET_ENV_LIBRARY_PATH
LIBRARY_PATH_PLACEHOLDER += $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/cryptolink/.libs:$(abs_top_builddir)/src/lib/dns/.libs:$(abs_top_builddir)/src/lib/dns/python/.libs:$(abs_top_builddir)/src/lib/cc/.libs:$(abs_top_builddir)/src/lib/config/.libs:$(abs_top_builddir)/src/lib/log/.libs:$(abs_top_builddir)/src/lib/util/.libs:$(abs_top_builddir)/src/lib/exceptions/.libs:$(abs_top_builddir)/src/lib/datasrc/.libs:$$$(ENV_LIBRARY_PATH)
endif

# test using command-line arguments, so use check-local target instead of TESTS
# We need to run the cycle twice, because once the files are in builddir, once in srcdir
check-local:
	chmod +x $(abs_builddir)/log_console.py
	$(LIBRARY_PATH_PLACEHOLDER) \
	PYTHONPATH=$(COMMON_PYTHON_PATH):$(abs_top_builddir)/src/lib/python/isc/log \
	B10_LOCKFILE_DIR_FROM_BUILD=$(abs_top_builddir) \
	$(abs_srcdir)/check_output.sh $(abs_builddir)/log_console.py $(abs_srcdir)/console.out
if ENABLE_PYTHON_COVERAGE
	touch $(abs_top_srcdir)/.coverage
	rm -f .coverage
	${LN_S} $(abs_top_srcdir)/.coverage .coverage
endif
	for pytest in $(PYTESTS_NOGEN) ; do \
	echo Running test: $$pytest ; \
	$(LIBRARY_PATH_PLACEHOLDER) \
	PYTHONPATH=$(COMMON_PYTHON_PATH):$(abs_top_builddir)/src/lib/python/isc/log:$(abs_top_builddir)/src/lib/log/python/.libs \
	B10_TEST_PLUGIN_DIR=$(abs_top_srcdir)/src/bin/cfgmgr/plugins \
	B10_LOCKFILE_DIR_FROM_BUILD=$(abs_top_builddir) \
	$(PYCOVERAGE_RUN) $(abs_srcdir)/$$pytest || exit ; \
	done ; \
	for pytest in $(PYTESTS_GEN) ; do \
	echo Running test: $$pytest ; \
	chmod +x $(abs_builddir)/$$pytest ; \
	$(LIBRARY_PATH_PLACEHOLDER) \
	PYTHONPATH=$(COMMON_PYTHON_PATH):$(abs_top_builddir)/src/lib/python/isc/log:$(abs_top_builddir)/src/lib/log/python/.libs \
	B10_TEST_PLUGIN_DIR=$(abs_top_srcdir)/src/bin/cfgmgr/plugins \
	B10_LOCKFILE_DIR_FROM_BUILD=$(abs_top_builddir) \
	$(PYCOVERAGE_RUN) $(abs_builddir)/$$pytest || exit ; \
	done
