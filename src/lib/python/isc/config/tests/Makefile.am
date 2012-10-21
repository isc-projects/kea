PYCOVERAGE_RUN=@PYCOVERAGE_RUN@
PYTESTS = ccsession_test.py cfgmgr_test.py config_data_test.py
PYTESTS += module_spec_test.py
EXTRA_DIST = $(PYTESTS)
EXTRA_DIST += unittest_fakesession.py

# If necessary (rare cases), explicitly specify paths to dynamic libraries
# required by loadable python modules.
LIBRARY_PATH_PLACEHOLDER =
if SET_ENV_LIBRARY_PATH
LIBRARY_PATH_PLACEHOLDER += $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/cryptolink/.libs:$(abs_top_builddir)/src/lib/dns/.libs:$(abs_top_builddir)/src/lib/dns/python/.libs:$(abs_top_builddir)/src/lib/cc/.libs:$(abs_top_builddir)/src/lib/config/.libs:$(abs_top_builddir)/src/lib/log/.libs:$(abs_top_builddir)/src/lib/util/.libs:$(abs_top_builddir)/src/lib/util/threads/.libs:$(abs_top_builddir)/src/lib/exceptions/.libs:$(abs_top_builddir)/src/lib/datasrc/.libs:$$$(ENV_LIBRARY_PATH)
endif

# test using command-line arguments, so use check-local target instead of TESTS
check-local:
if ENABLE_PYTHON_COVERAGE
	touch $(abs_top_srcdir)/.coverage
	rm -f .coverage
	${LN_S} $(abs_top_srcdir)/.coverage .coverage
endif
	for pytest in $(PYTESTS) ; do \
	echo Running test: $$pytest ; \
	$(LIBRARY_PATH_PLACEHOLDER) \
	PYTHONPATH=$(COMMON_PYTHON_PATH):$(abs_top_builddir)/src/lib/python/isc/config \
	B10_LOCKFILE_DIR_FROM_BUILD=$(abs_top_builddir) \
	B10_TEST_PLUGIN_DIR=$(abs_top_srcdir)/src/bin/cfgmgr/plugins \
	CONFIG_TESTDATA_PATH=$(abs_top_srcdir)/src/lib/config/tests/testdata \
	CONFIG_WR_TESTDATA_PATH=$(abs_top_builddir)/src/lib/config/tests/testdata \
	$(PYCOVERAGE_RUN) $(abs_srcdir)/$$pytest || exit ; \
	done

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
