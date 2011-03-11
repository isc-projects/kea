SUBDIRS = isc http testdata
PYCOVERAGE_RUN = @PYCOVERAGE_RUN@
PYTESTS = b10-stats_test.py b10-stats-httpd_test.py
EXTRA_DIST = $(PYTESTS) fake_time.py socket.py select.py
CLEANFILES = fake_time.pyc socket.pyc select.pyc

# test using command-line arguments, so use check-local target instead of TESTS
check-local:
if ENABLE_PYTHON_COVERAGE
	touch $(abs_top_srcdir)/.coverage 
	rm -f .coverage
	${LN_S} $(abs_top_srcdir)/.coverage .coverage
endif
	for pytest in $(PYTESTS) ; do \
	echo Running test: $$pytest ; \
	env PYTHONPATH=$(abs_top_srcdir)/src/lib/python:$(abs_top_builddir)/src/lib/python:$(abs_top_builddir)/src/bin/stats:$(abs_top_builddir)/src/bin/stats/tests \
	B10_FROM_SOURCE=$(abs_top_srcdir)/src/bin/stats \
	$(PYCOVERAGE_RUN) $(abs_srcdir)/$$pytest || exit ; \
	done
