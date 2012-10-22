PYCOVERAGE_RUN=@PYCOVERAGE_RUN@
PYTESTS = xfrout_test.py
noinst_SCRIPTS = $(PYTESTS)

EXTRA_DIST = testdata/test.sqlite3
# These are actually not necessary, but added for reference
EXTRA_DIST += testdata/example.com testdata/creatediff.py

# If necessary (rare cases), explicitly specify paths to dynamic libraries
# required by loadable python modules.
LIBRARY_PATH_PLACEHOLDER =
if SET_ENV_LIBRARY_PATH
LIBRARY_PATH_PLACEHOLDER += $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/cryptolink/.libs:$(abs_top_builddir)/src/lib/dns/.libs:$(abs_top_builddir)/src/lib/dns/python/.libs:$(abs_top_builddir)/src/lib/cc/.libs:$(abs_top_builddir)/src/lib/config/.libs:$(abs_top_builddir)/src/lib/log/.libs:$(abs_top_builddir)/src/lib/util/.libs:$(abs_top_builddir)/src/lib/util/threads/.libs:$(abs_top_builddir)/src/lib/exceptions/.libs:$(abs_top_builddir)/src/lib/util/io/.libs:$(abs_top_builddir)/src/lib/datasrc/.libs:$(abs_top_builddir)/src/lib/acl/.libs:$$$(ENV_LIBRARY_PATH)
else
# Some systems need the ds path even if not all paths are necessary
LIBRARY_PATH_PLACEHOLDER += $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/datasrc/.libs
endif

# test using command-line arguments, so use check-local target instead of TESTS
# We set B10_FROM_BUILD below, so that the test can refer to the in-source
# spec file.
check-local:
if ENABLE_PYTHON_COVERAGE
	touch $(abs_top_srcdir)/.coverage 
	rm -f .coverage
	${LN_S} $(abs_top_srcdir)/.coverage .coverage
endif
	for pytest in $(PYTESTS) ; do \
	echo Running test: $$pytest ; \
	chmod +x $(abs_builddir)/$$pytest ; \
	B10_FROM_BUILD=$(abs_top_builddir) \
	$(LIBRARY_PATH_PLACEHOLDER) \
	PYTHONPATH=$(COMMON_PYTHON_PATH):$(abs_top_builddir)/src/bin/xfrout:$(abs_top_builddir)/src/lib/dns/python/.libs:$(abs_top_builddir)/src/lib/util/io/.libs \
	TESTDATASRCDIR=$(abs_srcdir)/testdata/ \
	$(PYCOVERAGE_RUN) $(abs_builddir)/$$pytest || exit ; \
	done
