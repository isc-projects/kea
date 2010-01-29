SUBDIRS = config

PY_MODULES=	__init__.py

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(pyexecdir)/isc
	@(for _foo_ in $(PY_MODULES) ; \
		do $(INSTALL) -m 0644 $(top_srcdir)/src/lib/config/python/isc/$$_foo_ $(DESTDIR)$(pyexecdir)/isc/ ; done)
