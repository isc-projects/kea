sbin_SCRIPTS = b10-cmdctl-usermgr

b10_cmdctl_usermgrdir = $(DESTDIR)$(pkgdatadir)

CLEANFILES=	b10-cmdctl-usermgr

man_MANS = b10-cmdctl-usermgr.8
EXTRA_DIST = $(man_MANS) b10-cmdctl-usermgr.xml

if ENABLE_MAN

b10-cmdctl-usermgr.8: b10-cmdctl-usermgr.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-cmdctl-usermgr.xml

endif

# TODO: does this need $$(DESTDIR) also?
# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-cmdctl-usermgr: b10-cmdctl-usermgr.py
	$(SED) "s|@@PYTHONPATH@@|@pyexecdir@|" b10-cmdctl-usermgr.py >$@
	chmod a+x $@
