pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-cmdctl

b10_cmdctldir = $(DESTDIR)$(pkgdatadir)
b10_cmdctl_DATA = passwd.csv b10-cmdctl.pem

CLEANFILES=	cmdctl.py

# TODO: does this need $$(DESTDIR) also?
# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-cmdctl: cmdctl.py
	$(SED) "s|@@PYTHONPATH@@|@pyexecdir@|" cmdctl.py >$@
	chmod a+x $@
