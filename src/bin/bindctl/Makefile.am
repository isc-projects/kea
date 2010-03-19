bin_SCRIPTS = bindctl
man_MANS = bindctl.1

EXTRA_DIST = $(man_MANS) bindctl.xml

python_PYTHON = __init__.py bindcmd.py cmdparse.py exception.py moduleinfo.py mycollections.py
pythondir = $(pyexecdir)/bindctl

bindctldir = $(DESTDIR)$(pkgdatadir)
bindctl_DATA = bindctl.pem
EXTRA_DIST += bindctl.pem

CLEANFILES = bindctl

if ENABLE_MAN

bindctl.1: bindctl.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/bindctl.xml

endif

bindctl: bindctl-source.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@SYSCONFDIR@@|@sysconfdir@|" \
	       -e "s|@@LIBEXECDIR@@|$(pkglibexecdir)|" bindctl-source.py >$@
	chmod a+x $@

if ENABLE_CONFIGURATION_INSTALL

# TODO: permissions handled later
install-data-local:
	$(mkinstalldirs) $(DESTDIR)/@sysconfdir@/@PACKAGE@   
	if test ! -f $(DESTDIR)$(sysconfdir)/@PACKAGE@/bindctl.pem; then	\
	  $(INSTALL_DATA) $(srcdir)/bindctl.pem $(DESTDIR)$(sysconfdir)/@PACKAGE@/ ;	\
	fi

endif
