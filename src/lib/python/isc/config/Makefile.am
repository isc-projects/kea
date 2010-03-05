PY_MODULES=	__init__.py ccsession.py cfgmgr.py config_data.py module_spec.py

install-data-local:
	$(mkinstalldirs) $(DESTDIR)$(pyexecdir)/isc/config
	@(for _foo_ in $(PY_MODULES) ; \
		do $(INSTALL) -m 0644 $(top_srcdir)/src/lib/python/isc/config/$$_foo_ $(DESTDIR)$(pyexecdir)/isc/config/; done)
