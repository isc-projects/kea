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
EXTRA_DIST += comment.db

noinst_SCRIPTS = correct_test.sh

# If necessary (rare cases), explicitly specify paths to dynamic libraries
# required by loadable python modules.
LIBRARY_PATH_PLACEHOLDER =
if SET_ENV_LIBRARY_PATH
LIBRARY_PATH_PLACEHOLDER += $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/cryptolink/.libs:$(abs_top_builddir)/src/lib/dns/.libs:$(abs_top_builddir)/src/lib/dns/python/.libs:$(abs_top_builddir)/src/lib/cc/.libs:$(abs_top_builddir)/src/lib/config/.libs:$(abs_top_builddir)/src/lib/log/.libs:$(abs_top_builddir)/src/lib/util/.libs:$(abs_top_builddir)/src/lib/exceptions/.libs:$(abs_top_builddir)/src/lib/util/io/.libs:$(abs_top_builddir)/src/lib/datasrc/.libs:$$$(ENV_LIBRARY_PATH)
endif

# TODO: maybe use TESTS?
# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	echo Running test: correct_test.sh 
	$(LIBRARY_PATH_PLACEHOLDER) $(SHELL) $(abs_builddir)/correct_test.sh
