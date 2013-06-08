PYCOVERAGE_RUN = @PYCOVERAGE_RUN@
PYTESTS = tsig_keyring_test.py dns_tcp_test.py datasrc_clients_mgr_test.py
PYTESTS += bind10_server_test.py
EXTRA_DIST = $(PYTESTS)

# If necessary (rare cases), explicitly specify paths to dynamic libraries
# required by loadable python modules.
LIBRARY_PATH_PLACEHOLDER =
if SET_ENV_LIBRARY_PATH
LIBRARY_PATH_PLACEHOLDER += $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/cryptolink/.libs:$(abs_top_builddir)/src/lib/dns/.libs:$(abs_top_builddir)/src/lib/dns/python/.libs:$(abs_top_builddir)/src/lib/cc/.libs:$(abs_top_builddir)/src/lib/config/.libs:$(abs_top_builddir)/src/lib/log/.libs:$(abs_top_builddir)/src/lib/util/.libs:$(abs_top_builddir)/src/lib/util/threads/.libs:$(abs_top_builddir)/src/lib/exceptions/.libs:$(abs_top_builddir)/src/lib/datasrc/.libs:$$$(ENV_LIBRARY_PATH)
endif

# We use our own "default" datasrc.spec, tweaking some installation path,
# so we can run the tests with something very close to the actual spec and
# yet independent from installation environment.
BUILT_SOURCES = datasrc.spec
datasrc.spec: $(abs_top_builddir)/src/bin/cfgmgr/plugins/datasrc.spec.pre
	$(SED) -e "s|@@STATIC_ZONE_FILE@@|$(abs_top_builddir)/src/lib/datasrc/static.zone|;s|@@SQLITE3_DATABASE_FILE@@|$(abs_builddir)/zone.sqlite3|" $(abs_top_builddir)/src/bin/cfgmgr/plugins/datasrc.spec.pre >$@
CLEANFILES = datasrc.spec zone.sqlite3

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
	PYTHONPATH=$(COMMON_PYTHON_PATH):$(abs_top_builddir)/src/lib/dns/python/.libs \
	B10_LOCKFILE_DIR_FROM_BUILD=$(abs_top_builddir) \
	B10_FROM_SOURCE=$(abs_top_srcdir) \
	B10_FROM_BUILD=$(abs_top_builddir) \
	$(PYCOVERAGE_RUN) $(abs_srcdir)/$$pytest || exit ; \
	done
