SUBDIRS = . testdata

# Tests of the update script.

noinst_SCRIPTS = dbutil_test.sh

check-local:
if HAVE_SQLITE3_PROGRAM
	B10_LOCKFILE_DIR_FROM_BUILD=$(abs_top_builddir) \
	$(SHELL) $(abs_builddir)/dbutil_test.sh
else
	@echo ""
	@echo " **** The sqlite3 program is required to run dbutil tests **** "
	@echo ""
endif
