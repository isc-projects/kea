pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-cmdctl

b10_cmdctldir = $(DESTDIR)$(pkgdatadir)

# NOTE: this will overwrite on install
# So these generic copies are placed in share/bind10 instead of to etc
# Admin or packageer will need to put into place manually.

CMDCTL_CONFIGURATIONS = cmdctl-accounts.csv
CMDCTL_CONFIGURATIONS += cmdctl-keyfile.pem cmdctl-certfile.pem

b10_cmdctl_DATA = $(CMDCTL_CONFIGURATIONS)
b10_cmdctl_DATA += cmdctl.spec
 
EXTRA_DIST = $(CMDCTL_CONFIGURATIONS)
EXTRA_DIST += cmdctl.spec
EXTRA_DIST += tests/cmdctl_test.py

CLEANFILES=	b10-cmdctl

man_MANS = b10-cmdctl.8
EXTRA_DIST += $(man_MANS) b10-cmdctl.xml

if ENABLE_MAN

b10-cmdctl.8: b10-cmdctl.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-cmdctl.xml

endif

# TODO: does this need $$(DESTDIR) also?
# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-cmdctl: cmdctl.py
	$(SED) "s|@@PYTHONPATH@@|@pyexecdir@|" cmdctl.py >$@
	chmod a+x $@

if INSTALL_CONFIGURATIONS

# TODO: permissions handled later
install-data-local:
	$(mkinstalldirs) $(DESTDIR)/@sysconfdir@/@PACKAGE@   
	for f in $(CMDCTL_CONFIGURATIONS) ; do	\
	  if test ! -f $(DESTDIR)$(sysconfdir)/@PACKAGE@/$$f; then	\
	    $(INSTALL_DATA) $(srcdir)/$$f $(DESTDIR)$(sysconfdir)/@PACKAGE@/ ;	\
	  fi ;	\
	done

endif
