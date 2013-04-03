PYCOVERAGE_RUN = @PYCOVERAGE_RUN@
PYTESTS = edns_python_test.py
PYTESTS += message_python_test.py
PYTESTS += messagerenderer_python_test.py
PYTESTS += name_python_test.py
PYTESTS += nsec3hash_python_test.py
PYTESTS += question_python_test.py
PYTESTS += opcode_python_test.py
PYTESTS += rcode_python_test.py
PYTESTS += rdata_python_test.py
PYTESTS += rrclass_python_test.py
PYTESTS += rrset_python_test.py
PYTESTS += rrttl_python_test.py
PYTESTS += rrtype_python_test.py
PYTESTS += rrset_collection_python_test.py
PYTESTS += serial_python_test.py
PYTESTS += tsig_python_test.py
PYTESTS += tsig_rdata_python_test.py
PYTESTS += tsigerror_python_test.py
PYTESTS += tsigkey_python_test.py
PYTESTS += tsigrecord_python_test.py
PYTESTS += zone_checker_python_test.py

EXTRA_DIST = $(PYTESTS)
EXTRA_DIST += testutil.py

# If necessary (rare cases), explicitly specify paths to dynamic libraries
# required by loadable python modules.
LIBRARY_PATH_PLACEHOLDER =
if SET_ENV_LIBRARY_PATH
LIBRARY_PATH_PLACEHOLDER += $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/dns/.libs:$(abs_top_builddir)/src/lib/dns/python/.libs:$(abs_top_builddir)/src/lib/cryptolink/.libs:$(abs_top_builddir)/src/lib/util/.libs:$(abs_top_builddir)/src/lib/util/threads/.libs:$(abs_top_builddir)/src/lib/exceptions/.libs:$$$(ENV_LIBRARY_PATH)
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
	env PYTHONPATH=$(abs_top_builddir)/src/lib/util/pyunittests/.libs:$(abs_top_srcdir)/src/lib/dns/.libs:$(abs_top_srcdir)/src/lib/python:$(abs_top_builddir)/src/lib/python:$(abs_top_builddir)/src/lib/dns/python/.libs \
	TESTDATA_PATH=$(abs_top_srcdir)/src/lib/dns/tests/testdata:$(abs_top_builddir)/src/lib/dns/tests/testdata \
	$(LIBRARY_PATH_PLACEHOLDER) \
	$(PYCOVERAGE_RUN) $(abs_srcdir)/$$pytest || exit ; \
	done

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
