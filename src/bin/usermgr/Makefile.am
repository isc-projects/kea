sbin_SCRIPTS = b10-cmdctl-usermgr

b10_cmdctl_usermgrdir = $(DESTDIR)$(pkgdatadir)

CLEANFILES=	b10-cmdctl-usermgr

# TODO: does this need $$(DESTDIR) also?
# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-cmdctl-usermgr: b10-cmdctl-usermgr.py
	$(SED) "s|@@PYTHONPATH@@|@pyexecdir@|" b10-cmdctl-usermgr.py >$@
	chmod a+x $@
