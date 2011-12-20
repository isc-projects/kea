PYCOVERAGE_RUN = @PYCOVERAGE_RUN@
PYTESTS = socketsession_test.py
EXTRA_DIST = $(PYTESTS)

# If necessary (rare cases), explicitly specify paths to dynamic libraries
# required by loadable python modules.
LIBRARY_PATH_PLACEHOLDER =
if SET_ENV_LIBRARY_PATH
PATHS1 = $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/log/.libs:$(abs_top_builddir)/src/lib/util/.libs:$(abs_top_builddir)/src/lib/util/io/.libs:$(abs_top_builddir)/src/lib/exceptions/.libs$$$(ENV_LIBRARY_PATH)
PATHS2 = $(abs_top_builddir)/src/lib/dns/.libs
LIBRARY_PATH_PLACEHOLDER += $(PATHS1):$(PATHS2)
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
	PYTHONPATH=$(COMMON_PYTHON_PATH):$(abs_top_builddir)/src/lib/isc/python/util/io/.libs \
	$(LIBRARY_PATH_PLACEHOLDER) \
	TESTDATAOBJDIR=$(abs_builddir) \
	$(PYCOVERAGE_RUN) $(abs_srcdir)/$$pytest || exit ; \
	done

CLEANFILES = *.unix

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
