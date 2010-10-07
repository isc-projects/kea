PYCOVERAGE=@PYCOVERAGE@
PYTESTS = cmdctl_test.py
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
	env PYTHONPATH=$(abs_top_srcdir)/src/lib/python:$(abs_top_builddir)/src/lib/python:$(abs_top_builddir)/src/bin/cmdctl \
	CMDCTL_SPEC_PATH=$(abs_top_builddir)/src/bin/cmdctl \
	CMDCTL_SRC_PATH=$(abs_top_srcdir)/src/bin/cmdctl \
	$(PYCOVERAGE) $(abs_srcdir)/$$pytest || exit ; \
	done
