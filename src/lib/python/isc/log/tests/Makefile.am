PYCOVERAGE = @PYCOVERAGE@
PYTESTS = log_test.py
EXTRA_DIST = $(PYTESTS)

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
	$(PYCOVERAGE) $(abs_srcdir)/$$pytest || exit ; \
	done
