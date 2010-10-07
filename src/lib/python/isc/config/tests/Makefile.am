PYCOVERAGE=@PYCOVERAGE@
PYTESTS = ccsession_test.py cfgmgr_test.py config_data_test.py
PYTESTS += module_spec_test.py
EXTRA_DIST = $(PYTESTS)
EXTRA_DIST += unittest_fakesession.py

# test using command-line arguments, so use check-local target instead of TESTS
check-local:
if ENABLE_PYTHON_COVERAGE
	touch $(abs_top_srcdir)/.coverage
	rm -f .coverage
	${LN_S} $(abs_top_srcdir)/.coverage .coverage
endif
	for pytest in $(PYTESTS) ; do \
	echo Running test: $$pytest ; \
	env PYTHONPATH=$(abs_top_srcdir)/src/lib/python:$(abs_top_builddir)/src/lib/python \
	CONFIG_TESTDATA_PATH=$(abs_top_srcdir)/src/lib/config/tests/testdata \
	CONFIG_WR_TESTDATA_PATH=$(abs_top_builddir)/src/lib/config/tests/testdata \
	$(PYCOVERAGE) $(abs_srcdir)/$$pytest || exit ; \
	done
