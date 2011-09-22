PYCOVERAGE_RUN = @PYCOVERAGE_RUN@
PYTESTS = master_test.py sqlite3_ds_test.py
EXTRA_DIST = $(PYTESTS)

EXTRA_DIST += testdata/brokendb.sqlite3
EXTRA_DIST += testdata/example.com.sqlite3
CLEANFILES = $(abs_builddir)/example.com.out.sqlite3

# If necessary (rare cases), explicitly specify paths to dynamic libraries
# required by loadable python modules.
LIBRARY_PATH_PLACEHOLDER =
if SET_ENV_LIBRARY_PATH
LIBRARY_PATH_PLACEHOLDER += $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/cc/.libs:$(abs_top_builddir)/src/lib/config/.libs:$(abs_top_builddir)/src/lib/log/.libs:$(abs_top_builddir)/src/lib/util/.libs:$(abs_top_builddir)/src/lib/exceptions/.libs:$$$(ENV_LIBRARY_PATH)
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
	PYTHONPATH=:$(COMMON_PYTHON_PATH):$(abs_top_builddir)/src/lib/python/isc/log \
	TESTDATA_PATH=$(abs_srcdir)/testdata \
	TESTDATA_WRITE_PATH=$(abs_builddir) \
	$(PYCOVERAGE_RUN) $(abs_srcdir)/$$pytest || exit ; \
	done
