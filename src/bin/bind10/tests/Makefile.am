PYCOVERAGE_RUN = @PYCOVERAGE_RUN@
#PYTESTS = args_test.py bind10_test.py
# NOTE: this has a generated test found in the builddir
PYTESTS = bind10_test.py
noinst_SCRIPTS = $(PYTESTS)

# If necessary (rare cases), explicitly specify paths to dynamic libraries
# required by loadable python modules.
LIBRARY_PATH_PLACEHOLDER =
if SET_ENV_LIBRARY_PATH
LIBRARY_PATH_PLACEHOLDER += $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/cc/.libs:$(abs_top_builddir)/src/lib/config/.libs:$(abs_top_builddir)/src/lib/log/.libs:$(abs_top_builddir)/src/lib/util/.libs:$(abs_top_builddir)/src/lib/exceptions/.libs:$(abs_top_builddir)/src/lib/util/io/.libs:$$$(ENV_LIBRARY_PATH)
endif

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
	env PYTHONPATH=$(abs_top_srcdir)/src/lib/python:$(abs_top_builddir)/src/lib/python:$(abs_top_srcdir)/src/bin:$(abs_top_builddir)/src/bin/bind10:$(abs_top_builddir)/src/lib/util/io/.libs \
	BIND10_MSGQ_SOCKET_FILE=$(abs_top_builddir)/msgq_socket \
		$(PYCOVERAGE_RUN) $(abs_builddir)/$$pytest || exit ; \
	done
