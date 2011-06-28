PYCOVERAGE_RUN = @PYCOVERAGE_RUN@
#PYTESTS = args_test.py bind10_test.py
# NOTE: this has a generated test found in the builddir
PYTESTS = dhcp6_test.py
EXTRA_DIST = $(PYTESTS)

# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	for pytest in $(PYTESTS) ; do \
	echo Running test: $$pytest ; \
	env PYTHONPATH=$(abs_top_srcdir)/src/lib/python:$(abs_top_builddir)/src/lib/python:$(abs_top_builddir)/src/bin/bind10 \
	BIND10_MSGQ_SOCKET_FILE=$(abs_top_builddir)/msgq_socket \
		$(PYCOVERAGE_RUN) $(abs_srcdir)/$$pytest || exit ; \
	done
