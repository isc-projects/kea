PY_MODULES=	__init__.py ccsession.py datadefinition.py cfgmgr.py

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(pyexecdir)/isc/config
	@(for _foo_ in $(PY_MODULES) ; \
		do $(INSTALL) -m 0644 $(top_srcdir)/src/lib/config/python/isc/config/$$_foo_ $(DESTDIR)$(pyexecdir)/isc/config/; done)
