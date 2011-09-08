CLEANFILES = *.copied
BUILT_SOURCES = rwtest.sqlite3.copied

# We use install-sh with the -m option to make sure it's writable
rwtest.sqlite3.copied: $(srcdir)/rwtest.sqlite3
	$(top_srcdir)/install-sh -m 644 $(srcdir)/rwtest.sqlite3 $@
