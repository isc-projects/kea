PYTESTS = message_python_test.py
PYTESTS += question_python_test.py
PYTESTS += rrset_python_test.py
PYTESTS += rrtype_python_test.py

EXTRA_DIST = $(PYTESTS)

# later will have configure option to choose this, like: coverage run --branch
PYCOVERAGE = $(PYTHON)
# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	for pytest in $(PYTESTS) ; do \
	echo Running test: $$pytest ; \
	env PYTHONPATH=$(abs_top_srcdir)/src/lib/python:$(abs_top_srcdir)/src/lib/dns/python/.libs \
	TESTDATA_PATH=$(abs_top_srcdir)/src/lib/dns/tests/testdata \
	$(PYCOVERAGE) $(abs_srcdir)/$$pytest ; \
	done
