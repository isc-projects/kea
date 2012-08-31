sbin_SCRIPTS = b10-cmdctl-usermgr

b10_cmdctl_usermgrdir = $(pkgdatadir)

CLEANFILES=	b10-cmdctl-usermgr

man_MANS = b10-cmdctl-usermgr.8
MAINTAINERCLEANFILES = $(man_MANS)
EXTRA_DIST = $(man_MANS) b10-cmdctl-usermgr.xml

if GENERATE_DOCS

b10-cmdctl-usermgr.8: b10-cmdctl-usermgr.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-cmdctl-usermgr.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild BIND 10 > $@

endif

# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-cmdctl-usermgr: b10-cmdctl-usermgr.py
	$(SED) "s|@@PYTHONPATH@@|@pyexecdir@|" b10-cmdctl-usermgr.py >$@
	chmod a+x $@
