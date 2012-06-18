# We're going to abuse install-data-local for a pre-install check.  This may
# not be the cleanest way to do this type of job, but that's the least ugly
# one we've found.
#
# Note also that if any test needs to examine some file that has possibly
# been installed before (e.g., older DB or configuration file), it should be
# referenced with the prefix of DESTDIR.  Otherwise
# 'make DESTDIR=/somewhere install' may not work.
install-data-local:
	if test -e $(DESTDIR)$(localstatedir)/$(PACKAGE)/zone.sqlite3; then \
		$(SHELL) $(top_builddir)/src/bin/dbutil/run_dbutil.sh --check \
		$(DESTDIR)$(localstatedir)/$(PACKAGE)/zone.sqlite3 || \
		(echo "\nSQLite3 DB file schema version is old.  " \
		"Please run: " \
		"$(abs_top_builddir)/src/bin/dbutil/run_dbutil.sh --upgrade " \
		"$(DESTDIR)$(localstatedir)/$(PACKAGE)/zone.sqlite3"; exit 1) \
	fi
