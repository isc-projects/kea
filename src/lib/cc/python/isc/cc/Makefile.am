PY_MODULES=	__init__.py data.py session.py message.py

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(pyexecdir)/isc/cc
	@(for _foo_ in $(PY_MODULES) ; \
		do $(INSTALL) -m 0644 $(top_srcdir)/src/lib/cc/python/isc/cc/$$_foo_ $(DESTDIR)$(pyexecdir)/isc/cc/ ; done)
