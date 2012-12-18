SUBDIRS = . correct

PYCOVERAGE_RUN=@PYCOVERAGE_RUN@
PYTESTS = loadzone_test.py

EXTRA_DIST = $(PYTESTS)
EXTRA_DIST += testdata/example.org.zone
EXTRA_DIST += testdata/broken-example.org.zone
EXTRA_DIST += testdata/example-nosoa.org.zone
EXTRA_DIST += testdata/example-nons.org.zone

# If necessary (rare cases), explicitly specify paths to dynamic libraries
# required by loadable python modules.
LIBRARY_PATH_PLACEHOLDER =
if SET_ENV_LIBRARY_PATH
LIBRARY_PATH_PLACEHOLDER += $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/cryptolink/.libs:$(abs_top_builddir)/src/lib/dns/.libs:$(abs_top_builddir)/src/lib/dns/python/.libs:$(abs_top_builddir)/src/lib/cc/.libs:$(abs_top_builddir)/src/lib/config/.libs:$(abs_top_builddir)/src/lib/log/.libs:$(abs_top_builddir)/src/lib/util/.libs:$(abs_top_builddir)/src/lib/exceptions/.libs:$(abs_top_builddir)/src/lib/util/io/.libs:$(abs_top_builddir)/src/lib/datasrc/.libs:$(abs_top_builddir)/src/lib/acl/.libs:$$$(ENV_LIBRARY_PATH)
endif

# test using command-line arguments, so use check-local target instead of TESTS
# We need to define B10_FROM_BUILD for datasrc loadable modules
check-local:
if ENABLE_PYTHON_COVERAGE
	touch $(abs_top_srcdir)/.coverage
	rm -f .coverage
	${LN_S} $(abs_top_srcdir)/.coverage .coverage
endif
	for pytest in $(PYTESTS) ; do \
	echo Running test: $$pytest ; \
	B10_FROM_SOURCE=$(abs_top_srcdir) \
	B10_FROM_BUILD=$(abs_top_builddir) \
	$(LIBRARY_PATH_PLACEHOLDER) \
	TESTDATA_PATH=$(abs_top_srcdir)/src/lib/testutils/testdata \
	LOCAL_TESTDATA_PATH=$(srcdir)/testdata \
	TESTDATA_WRITE_PATH=$(builddir) \
	PYTHONPATH=$(COMMON_PYTHON_PATH):$(abs_top_builddir)/src/bin/loadzone:$(abs_top_builddir)/src/lib/dns/python/.libs:$(abs_top_builddir)/src/lib/util/io/.libs \
	$(PYCOVERAGE_RUN) $(abs_srcdir)/$$pytest || exit ; \
	done
