PY_MODULES=	__init__.py master.py sqlite3_ds.py

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(pyexecdir)/isc/auth
	@(for _foo_ in $(PY_MODULES) ; \
		do $(INSTALL) -m 0644 $(top_srcdir)/src/lib/python/isc/auth/$$_foo_ $(DESTDIR)$(pyexecdir)/isc/auth/; done)
