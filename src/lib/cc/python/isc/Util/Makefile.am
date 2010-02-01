PY_MODULES=	__init__.py hexdump.py

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(pyexecdir)/isc/Util
	@(for _foo_ in $(PY_MODULES) ; \
		do $(INSTALL) -m 0644 $(top_srcdir)/src/lib/cc/python/isc/Util/$$_foo_ $(DESTDIR)$(pyexecdir)/isc/Util/ ; done)
