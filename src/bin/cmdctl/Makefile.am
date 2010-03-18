pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-cmdctl

b10_cmdctldir = $(DESTDIR)$(pkgdatadir)

# NOTE: this will overwrite on install
# So these generic copies are placed in share/bind10 instead of to etc
# Admin or packageer will need to put into place manually.

b10_cmdctl_DATA = cmdctl-accounts.csv cmdctl-keyfile.pem cmdctl-certfile.pem
b10_cmdctl_DATA += cmdctl.spec
 
EXTRA_DIST = cmdctl-accounts.csv cmdctl-keyfile.pem cmdctl-certfile.pem
EXTRA_DIST += cmdctl.spec

CLEANFILES=	b10-cmdctl

# TODO: does this need $$(DESTDIR) also?
# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-cmdctl: cmdctl.py
	$(SED) "s|@@PYTHONPATH@@|@pyexecdir@|" cmdctl.py >$@
	chmod a+x $@

install-data-local:
	$(mkinstalldirs) $(DESTDIR)/@sysconfdir@/@PACKAGE@   
# TODO: permissions handled later

