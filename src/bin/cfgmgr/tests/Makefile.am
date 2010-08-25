PYTESTS = b10-cfgmgr_test.py

EXTRA_DIST = $(PYTESTS)

# later will have configure option to choose this, like: coverage run --branch
PYCOVERAGE = $(PYTHON)
# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	for pytest in $(PYTESTS) ; do \
	echo Running test: $$pytest ; \
	env PYTHONPATH=$(abs_top_srcdir)/src/lib/python:$(abs_top_builddir)/src/lib/python:$(abs_top_builddir)/src/bin/cfgmgr \
	$(PYCOVERAGE) $(abs_builddir)/$$pytest || exit ; \
	done
