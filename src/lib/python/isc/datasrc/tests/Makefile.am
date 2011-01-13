PYCOVERAGE_RUN = @PYCOVERAGE_RUN@
PYTESTS = master_test.py sqlite3_ds_test.py
EXTRA_DIST = $(PYTESTS)

EXTRA_DIST += testdata/brokendb.sqlite3
EXTRA_DIST += testdata/example.com.sqlite3

# test using command-line arguments, so use check-local target instead of TESTS
check-local:
if ENABLE_PYTHON_COVERAGE
	touch $(abs_top_srcdir)/.coverage
	rm -f .coverage
	${LN_S} $(abs_top_srcdir)/.coverage .coverage
endif
	for pytest in $(PYTESTS) ; do \
	echo Running test: $$pytest ; \
	env PYTHONPATH=$(abs_top_srcdir)/src/lib/python:$(abs_top_builddir)/src/lib/python:$(abs_top_builddir)/src/lib/python/isc/log \
	$(PYCOVERAGE_RUN) $(abs_srcdir)/$$pytest || exit ; \
	done
