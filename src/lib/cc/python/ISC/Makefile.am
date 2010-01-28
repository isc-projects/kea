SUBDIRS = CC Util

PY_MODULES=	__init__.py

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(pyexecdir)/ISC
	@(for _foo_ in $(PY_MODULES) ; \
		do $(INSTALL) -m 0644 $(top_srcdir)/src/lib/cc/python/ISC/$$_foo_ $(DESTDIR)$(pyexecdir)/ISC/ ; done)
