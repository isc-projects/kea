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

# TODO: maybe use TESTS?
# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	echo Running test: correct_test.sh 
	$(SHELL) $(abs_builddir)/correct_test.sh
