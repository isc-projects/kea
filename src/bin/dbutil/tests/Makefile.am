SUBDIRS = . testdata

# Tests of the update script.

check-local:
	B10_LOCKFILE_DIR_FROM_BUILD=$(abs_top_builddir) \
	$(SHELL) $(abs_builddir)/dbutil_test.sh
