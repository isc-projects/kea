# We're going to abuse install-data-local for a pre-install check.
# This is to be considered a short term hack and is expected to be removed
# in a near future version.
install-data-local:
	if test -e $(localstatedir)/$(PACKAGE)/zone.sqlite3; then \
		$(SHELL) $(top_builddir)/src/bin/dbutil/run_dbutil.sh --check \
		$(localstatedir)/$(PACKAGE)/zone.sqlite3 || \
		(echo "\nSQLite3 DB file schema version is old.  " \
		"Please run: " \
		"$(abs_top_builddir)/src/bin/dbutil/run_dbutil.sh --upgrade " \
		"$(localstatedir)/$(PACKAGE)/zone.sqlite3";  exit 1) \
	fi
