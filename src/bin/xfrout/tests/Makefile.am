PYTESTS = xfrout_test.py
EXTRA_DIST = $(PYTESTS)

# If necessary (rare cases), explicitly specify paths to dynamic libraries
# required by loadable python modules.
LIBRARY_PATH_PLACEHOLDER =
if SET_ENV_LIBRARY_PATH
LIBRARY_PATH_PLACEHOLDER += $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/dns/.libs:$(abs_top_builddir)/src/lib/exceptions/.libs:$(abs_top_builddir)/src/lib/xfr/.libs:$$$(ENV_LIBRARY_PATH)
endif

# later will have configure option to choose this, like: coverage run --branch
PYCOVERAGE = $(PYTHON)
# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	for pytest in $(PYTESTS) ; do \
	echo Running test: $$pytest ; \
	env PYTHONPATH=$(abs_top_builddir)/src/bin/xfrout:$(abs_top_srcdir)/src/lib/python:$(abs_top_builddir)/src/lib/python:$(abs_top_builddir)/src/lib/dns/python/.libs:$(abs_top_builddir)/src/lib/xfr/.libs \
	$(LIBRARY_PATH_PLACEHOLDER) \
	$(PYCOVERAGE) $(abs_srcdir)/$$pytest || exit ; \
	done
