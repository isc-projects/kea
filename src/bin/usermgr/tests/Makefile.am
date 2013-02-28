PYCOVERAGE_RUN=@PYCOVERAGE_RUN@
PYTESTS = b10-cmdctl-usermgr_test.py
EXTRA_DIST = $(PYTESTS)

CLEANFILES = *.csv

# test using command-line arguments, so use check-local target instead of TESTS
check-local:
if ENABLE_PYTHON_COVERAGE
	touch $(abs_top_srcdir)/.coverage
	rm -f .coverage
	${LN_S} $(abs_top_srcdir)/.coverage .coverage
endif
	for pytest in $(PYTESTS) ; do \
	echo Running test: $$pytest ; \
	$(LIBRARY_PATH_PLACEHOLDER) \
	PYTHONPATH=$(COMMON_PYTHON_PATH):$(abs_top_builddir)/src/bin/cmdctl \
	CMDCTL_BUILD_PATH=$(abs_top_builddir)/src/bin/cmdctl \
	CMDCTL_SRC_PATH=$(abs_top_srcdir)/src/bin/cmdctl \
	B10_LOCKFILE_DIR_FROM_BUILD=$(abs_top_builddir) \
	$(PYCOVERAGE_RUN) $(abs_srcdir)/$$pytest || exit ; \
	done
