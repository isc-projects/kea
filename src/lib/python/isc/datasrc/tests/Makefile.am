PYCOVERAGE_RUN = @PYCOVERAGE_RUN@
PYTESTS =  datasrc_test.py sqlite3_ds_test.py
PYTESTS += clientlist_test.py zone_loader_test.py
EXTRA_DIST = $(PYTESTS)

EXTRA_DIST += testdata/brokendb.sqlite3
EXTRA_DIST += testdata/example.com.sqlite3
EXTRA_DIST += testdata/example.com.source.sqlite3
EXTRA_DIST += testdata/newschema.sqlite3
EXTRA_DIST += testdata/oldschema.sqlite3
EXTRA_DIST += testdata/new_minor_schema.sqlite3
EXTRA_DIST += testdata/example.com
EXTRA_DIST += testdata/example.com.ch
EXTRA_DIST += testdata/static.zone
CLEANFILES = $(abs_builddir)/rwtest.sqlite3.copied
CLEANFILES += $(abs_builddir)/zoneloadertest.sqlite3

# If necessary (rare cases), explicitly specify paths to dynamic libraries
# required by loadable python modules.
# We always add one, the location of the data source modules
# We may want to add an API method for this to the ds factory, but that is out
# of scope for this ticket
LIBRARY_PATH_PLACEHOLDER = $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/datasrc/.libs:
if SET_ENV_LIBRARY_PATH
LIBRARY_PATH_PLACEHOLDER += $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/cryptolink/.libs:$(abs_top_builddir)/src/lib/dns/.libs:$(abs_top_builddir)/src/lib/dns/python/.libs:$(abs_top_builddir)/src/lib/cc/.libs:$(abs_top_builddir)/src/lib/config/.libs:$(abs_top_builddir)/src/lib/log/.libs:$(abs_top_builddir)/src/lib/util/.libs:$(abs_top_builddir)/src/lib/util/threads/.libs:$(abs_top_builddir)/src/lib/exceptions/.libs:$(abs_top_builddir)/src/lib/datasrc/.libs:$$$(ENV_LIBRARY_PATH)
else
LIBRARY_PATH_PLACEHOLDER += $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/datasrc/.libs:$$$(ENV_LIBRARY_PATH)
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
	$(LIBRARY_PATH_PLACEHOLDER) \
	PYTHONPATH=:$(COMMON_PYTHON_PATH):$(abs_top_builddir)/src/lib/python/isc/log:$(abs_top_builddir)/src/lib/python/isc/datasrc/.libs:$(abs_top_builddir)/src/lib/dns/python/.libs \
	TESTDATA_PATH=$(abs_srcdir)/testdata \
	TESTDATA_WRITE_PATH=$(abs_builddir) \
	GLOBAL_TESTDATA_PATH=$(abs_top_srcdir)/src/lib/testutils/testdata \
	B10_FROM_BUILD=$(abs_top_builddir) \
	$(PYCOVERAGE_RUN) $(abs_srcdir)/$$pytest || exit ; \
	done
