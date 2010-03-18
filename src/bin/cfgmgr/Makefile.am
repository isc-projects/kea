pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-cfgmgr

CLEANFILES = b10-cfgmgr

b10_cfgmgrdir = @localstatedir@/@PACKAGE@
#B10_cfgmgr_DATA = 

# TODO: does this need $$(DESTDIR) also?
# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-cfgmgr: b10-cfgmgr.py
	$(SED) "s|@@PYTHONPATH@@|@pyexecdir@|" b10-cfgmgr.py >$@
	chmod a+x $@

install-data-local:
	$(mkinstalldirs) $(DESTDIR)/@localstatedir@/@PACKAGE@
# TODO: permissions handled later

