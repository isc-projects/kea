CLEANFILES = b10-config.db

BUILT_SOURCES = b10-config.db

# cfgmgr_test (under lib/python) will override b10-config.db, so we make a
# writable copy in the builddir.
b10-config.db: b10-config.db.master
	cp $(srcdir)/b10-config.db.master $@
