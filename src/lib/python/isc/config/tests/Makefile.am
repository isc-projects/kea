PYTESTS = ccsession_test.py cfgmgr_test.py config_data_test.py
PYTESTS += module_spec_test.py
EXTRA_DIST = $(PYTESTS)
EXTRA_DIST += unittest_fakesession.py

# later will have configure option to choose this, like: coverage run --branch
PYCOVERAGE = $(PYTHON)
# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	for pytest in $(PYTESTS) ; do \
	echo Running test: $$pytest ; \
	env PYTHONPATH=$(abs_top_srcdir)/src/lib/python:$(abs_top_builddir)/src/lib/python \
	CONFIG_TESTDATA_PATH=$(abs_top_srcdir)/src/lib/config/testdata \
	CONFIG_WR_TESTDATA_PATH=$(abs_top_builddir)/src/lib/config/testdata \
	$(PYCOVERAGE) $(abs_srcdir)/$$pytest || exit ; \
	done
