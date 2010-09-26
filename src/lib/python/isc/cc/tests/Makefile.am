PYTESTS = message_test.py data_test.py session_test.py
# NOTE: test_session.py is to be run manually, so not automated.
EXTRA_DIST = $(PYTESTS)
EXTRA_DIST += sendcmd.py
EXTRA_DIST += test_session.py

# later will have configure option to choose this, like: coverage run --branch
PYCOVERAGE = $(PYTHON)
# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	for pytest in $(PYTESTS) ; do \
	echo Running test: $$pytest ; \
	env PYTHONPATH=$(abs_top_srcdir)/src/lib/python:$(abs_top_builddir)/src/lib/python \
	BIND10_TEST_SOCKET_FILE=$(builddir)/test_socket.sock \
	$(PYCOVERAGE) $(abs_srcdir)/$$pytest || exit ; \
	done
