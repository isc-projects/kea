PYTESTS = message_python_test.py
PYTESTS += messagerenderer_python_test.py
PYTESTS += name_python_test.py
PYTESTS += question_python_test.py
PYTESTS += rdata_python_test.py
PYTESTS += rrclass_python_test.py
PYTESTS += rrset_python_test.py
PYTESTS += rrttl_python_test.py
PYTESTS += rrtype_python_test.py

EXTRA_DIST = $(PYTESTS)

# If necessary (rare cases), explicitly specify paths to dynamic libraries
# required by loadable python modules.
LIBRARY_PATH_PLACEHOLDER =
if SET_ENV_LIBRARY_PATH
LIBRARY_PATH_PLACEHOLDER += $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/dns/.libs:$(abs_top_builddir)/src/lib/exceptions/.libs:$$$(ENV_LIBRARY_PATH)
endif

# later will have configure option to choose this, like: coverage run --branch
PYCOVERAGE = $(PYTHON)
# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	for pytest in $(PYTESTS) ; do \
	echo Running test: $$pytest ; \
	env PYTHONPATH=$(abs_top_srcdir)/src/lib/python:$(abs_top_builddir)/src/lib/python:$(abs_top_builddir)/src/lib/dns/python/.libs \
	TESTDATA_PATH=$(abs_top_srcdir)/src/lib/dns/tests/testdata \
	$(LIBRARY_PATH_PLACEHOLDER) \
	$(PYCOVERAGE) $(abs_srcdir)/$$pytest || exit ; \
	done
