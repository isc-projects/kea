pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-cmdctl

b10_cmdctldir = $(DESTDIR)$(pkgdatadir)
# TODO: this is dangerous -- will overwrite!
b10_cmdctl_DATA = cmdctl-accounts.csv cmdctl-keyfile.pem cmdctl-certfile.pem cmdctl.spec

CLEANFILES=	b10-cmdctl

# TODO: does this need $$(DESTDIR) also?
# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-cmdctl: cmdctl.py
	$(SED) "s|@@PYTHONPATH@@|@pyexecdir@|" cmdctl.py >$@
	chmod a+x $@

install-data-local:
	chmod go-rwx $(DESTDIR)$(pkgdatadir)/cmdctl-accounts.csv
	chmod go-rwx $(DESTDIR)$(pkgdatadir)/cmdctl-certfile.pem
	chmod go-rwx $(DESTDIR)$(pkgdatadir)/cmdctl-keyfile.pem
