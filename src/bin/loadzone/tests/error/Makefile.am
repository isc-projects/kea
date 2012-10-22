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

noinst_SCRIPTS = error_test.sh

# If necessary (rare cases), explicitly specify paths to dynamic libraries
# required by loadable python modules.
LIBRARY_PATH_PLACEHOLDER =
if SET_ENV_LIBRARY_PATH
LIBRARY_PATH_PLACEHOLDER += $(ENV_LIBRARY_PATH)=$(abs_top_builddir)/src/lib/cryptolink/.libs:$(abs_top_builddir)/src/lib/dns/.libs:$(abs_top_builddir)/src/lib/dns/python/.libs:$(abs_top_builddir)/src/lib/cc/.libs:$(abs_top_builddir)/src/lib/config/.libs:$(abs_top_builddir)/src/lib/log/.libs:$(abs_top_builddir)/src/lib/util/.libs:$(abs_top_builddir)/src/lib/util/threads/.libs:$(abs_top_builddir)/src/lib/exceptions/.libs:$(abs_top_builddir)/src/lib/util/io/.libs:$(abs_top_builddir)/src/lib/datasrc/.libs:$$$(ENV_LIBRARY_PATH)
endif

# TODO: use TESTS ?
# test using command-line arguments, so use check-local target instead of TESTS
check-local:
	echo Running test: error_test.sh
	$(LIBRARY_PATH_PLACEHOLDER) $(SHELL) $(abs_builddir)/error_test.sh
