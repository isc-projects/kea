PYCOVERAGE_RUN = @PYCOVERAGE_RUN@
PYTESTS = b10-cfgmgr_test.py

noinst_SCRIPTS = $(PYTESTS)
EXTRA_DIST = testdata/plugins/testplugin.py

# If necessary (rare cases), explicitly specify paths to dynamic libraries
# required by loadable python modules.
LIBRARY_PATH_PLACEHOLDER =
if SET_ENV_LIBRARY_PATH
LIBRARY_PATH_PLACEHOLDER += $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/cryptolink/.libs:$(abs_top_builddir)/src/lib/dns/.libs:$(abs_top_builddir)/src/lib/dns/python/.libs:$(abs_top_builddir)/src/lib/cc/.libs:$(abs_top_builddir)/src/lib/config/.libs:$(abs_top_builddir)/src/lib/log/.libs:$(abs_top_builddir)/src/lib/util/.libs:$(abs_top_builddir)/src/lib/exceptions/.libs:$(abs_top_builddir)/src/lib/util/io/.libs:$(abs_top_builddir)/src/lib/datasrc/.libs:$$$(ENV_LIBRARY_PATH)
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
	chmod +x $(abs_builddir)/$$pytest ; \
	TESTDATA_PATH=$(abs_srcdir)/testdata \
	$(LIBRARY_PATH_PLACEHOLDER) \
	PYTHONPATH=$(COMMON_PYTHON_PATH):$(abs_top_builddir)/src/bin/cfgmgr:$(abs_top_builddir)/src/lib/python/isc/config \
	$(PYCOVERAGE_RUN) $(abs_builddir)/$$pytest || exit ; \
	done

CLEANDIRS = testdata/plugins/__pycache__

clean-local:
	rm -rf $(CLEANDIRS)
