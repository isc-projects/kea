SUBDIRS = CC Util

PY_MODULES=	__init__.py

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(pyexecdir)/ISC
	@(for _foo_ in $(PY_MODULES) ; \
		do $(INSTALL) -m 0644 $$_foo_ $(DESTDIR)$(pyexecdir)/ISC/ ; done)
