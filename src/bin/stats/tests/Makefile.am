SUBDIRS = testdata .

PYCOVERAGE_RUN = @PYCOVERAGE_RUN@
PYTESTS = b10-stats_test.py b10-stats-httpd_test.py
EXTRA_DIST = $(PYTESTS) test_utils.py
CLEANFILES = test_utils.pyc

# If necessary (rare cases), explicitly specify paths to dynamic libraries
# required by loadable python modules.
LIBRARY_PATH_PLACEHOLDER =
if SET_ENV_LIBRARY_PATH
LIBRARY_PATH_PLACEHOLDER += $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/cryptolink/.libs:$(abs_top_builddir)/src/lib/dns/.libs:$(abs_top_builddir)/src/lib/dns/python/.libs:$(abs_top_builddir)/src/lib/dns/python/.libs:$(abs_top_builddir)/src/lib/cc/.libs:$(abs_top_builddir)/src/lib/config/.libs:$(abs_top_builddir)/src/lib/log/.libs:$(abs_top_builddir)/src/lib/util/.libs:$(abs_top_builddir)/src/lib/exceptions/.libs:$(abs_top_builddir)/src/lib/datasrc/.libs:$$$(ENV_LIBRARY_PATH)
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
	PYTHONPATH=$(COMMON_PYTHON_PATH):$(abs_top_builddir)/src/bin/stats:$(abs_top_builddir)/src/bin/stats/tests:$(abs_top_builddir)/src/bin/msgq:$(abs_top_builddir)/src/lib/python/isc/config \
	B10_FROM_SOURCE=$(abs_top_srcdir) \
	BIND10_MSGQ_SOCKET_FILE=$(abs_top_builddir)/msgq_socket \
	CONFIG_TESTDATA_PATH=$(abs_top_srcdir)/src/bin/stats/tests/testdata \
	B10_LOCKFILE_DIR_FROM_BUILD=$(abs_top_builddir) \
	$(PYCOVERAGE_RUN) $(abs_srcdir)/$$pytest || exit ; \
	done

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
