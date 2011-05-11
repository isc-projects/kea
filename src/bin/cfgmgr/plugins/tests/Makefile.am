PYCOVERAGE_RUN = @PYCOVERAGE_RUN@
PYTESTS = tsig_keys_test.py

# test using command-line arguments, so use check-local target instead of TESTS
check-local:
if ENABLE_PYTHON_COVERAGE
	touch $(abs_top_srcdir)/.coverage
	rm -f .coverage
	${LN_S} $(abs_top_srcdir)/.coverage .coverage
endif
	for pytest in $(PYTESTS) ; do \
	echo Running test: $$pytest ; \
	env PLUGIN_DIR=$(abs_srcdir)/.. \
	env PYTHONPATH=$(abs_top_srcdir)/src/lib/python:$(abs_top_builddir)/src/lib/python:$(abs_top_builddir)/src/bin/cfgmgr \
	$(PYCOVERAGE_RUN) $(abs_builddir)/$$pytest || exit ; \
	done

