SUBDIRS = isc http testdata
PYCOVERAGE_RUN = @PYCOVERAGE_RUN@
PYTESTS = b10-stats_test.py b10-stats-httpd_test.py
EXTRA_DIST = $(PYTESTS) fake_time.py fake_socket.py fake_select.py
CLEANFILES = fake_time.pyc fake_socket.pyc fake_select.pyc

# If necessary (rare cases), explicitly specify paths to dynamic libraries
# required by loadable python modules.
LIBRARY_PATH_PLACEHOLDER =
if SET_ENV_LIBRARY_PATH
LIBRARY_PATH_PLACEHOLDER += $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/cc/.libs:$(abs_top_builddir)/src/lib/config/.libs:$(abs_top_builddir)/src/lib/log/.libs:$(abs_top_builddir)/src/lib/util/.libs:$(abs_top_builddir)/src/lib/exceptions/.libs:$$$(ENV_LIBRARY_PATH)
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
	PYTHONPATH=$(COMMON_PYTHON_PATH):$(abs_top_builddir)/src/bin/stats:$(abs_top_builddir)/src/bin/stats/tests \
	B10_FROM_SOURCE=$(abs_top_srcdir) \
	$(PYCOVERAGE_RUN) $(abs_srcdir)/$$pytest || exit ; \
	done

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
