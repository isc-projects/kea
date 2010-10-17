SUBDIRS = isc testdata
PYTESTS = b10-stats_test.py b10-stats_stub_test.py
EXTRA_DIST = $(PYTESTS) fake_time.py
CLEANFILES = fake_time.pyc

# later will have configure option to choose this, like: coverage run --branch
PYCOVERAGE = $(PYTHON)
# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	for pytest in $(PYTESTS) ; do \
	echo Running test: $$pytest ; \
	env PYTHONPATH=$(abs_top_srcdir)/src/lib/python:$(abs_top_builddir)/src/lib/python:$(abs_top_builddir)/src/bin/stats:$(abs_top_builddir)/src/bin/stats/tests \
	B10_FROM_BUILD=$(abs_top_builddir) \
	$(PYCOVERAGE) $(abs_srcdir)/$$pytest || exit ; \
	done
