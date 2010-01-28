PY_MODULES=	__init__.py data.py session.py message.py

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(pyexecdir)/ISC/CC
	@(for _foo_ in $(PY_MODULES) ; \
		do $(INSTALL) -m 0644 $(top_srcdir)/src/lib/cc/python/ISC/CC/$$_foo_ $(DESTDIR)$(pyexecdir)/ISC/CC/ ; done)
