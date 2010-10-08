PYCOVERAGE = @PYCOVERAGE@
PYTESTS = correct_test.sh
EXTRA_DIST = get_zonedatas.py
EXTRA_DIST += include.db
EXTRA_DIST += inclsub.db
EXTRA_DIST += known.test.out
EXTRA_DIST += mix1.db
EXTRA_DIST += mix1sub1.db
EXTRA_DIST += mix1sub2.db
EXTRA_DIST += mix2.db
EXTRA_DIST += mix2sub1.txt
EXTRA_DIST += mix2sub2.txt
EXTRA_DIST += ttl1.db
EXTRA_DIST += ttl2.db
EXTRA_DIST += ttlext.db
EXTRA_DIST += example.db

# test using command-line arguments, so use check-local target instead of TESTS
check-local:
if ENABLE_PYTHON_COVERAGE
	touch $(abs_top_srcdir)/.coverage 
	rm -f .coverage
	${LN_S} $(abs_top_srcdir)/.coverage .coverage
endif
	for pytest in $(PYTESTS) ; do \
	echo Running test: $$pytest ; \
	env PYTHONPATH=$(abs_top_srcdir)/src/lib/python:$(abs_top_builddir)/src/lib/python:$(abs_top_builddir)/src/bin/loadzone \
	$(SHELL) $(abs_builddir)/$$pytest || exit ; \
	done
