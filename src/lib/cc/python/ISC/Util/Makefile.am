PY_MODULES=	__init__.py hexdump.py

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(pyexecdir)/ISC/Util
	@(for _foo_ in $(PY_MODULES) ; \
		do $(INSTALL) -m 0644 $(top_srcdir)/src/lib/cc/python/ISC/Util/$$_foo_ $(DESTDIR)$(pyexecdir)/ISC/Util/ ; done)
