PYTESTS = error_test.sh

EXTRA_DIST = error.known
EXTRA_DIST += formerr1.db 
EXTRA_DIST += formerr2.db
EXTRA_DIST += formerr3.db
EXTRA_DIST += formerr4.db
EXTRA_DIST += formerr5.db
EXTRA_DIST += include.txt
EXTRA_DIST += keyerror1.db
EXTRA_DIST += keyerror2.db
EXTRA_DIST += keyerror3.db
#EXTRA_DIST += nofilenane.db
EXTRA_DIST += originerr1.db
EXTRA_DIST += originerr2.db

# later will have configure option to choose this, like: coverage run --branch
PYCOVERAGE = $(PYTHON)
# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	for pytest in $(PYTESTS) ; do \
	echo Running test: $$pytest ; \
	env PYTHONPATH=$(abs_top_srcdir)/src/lib/python:$(abs_top_builddir)/src/bin/loadzone \
	$(SHELL) $(abs_builddir)/$$pytest || exit ; \
	done
