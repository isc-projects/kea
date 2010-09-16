SUBDIRS = tests

pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-zonemgr

b10_zonemgrdir = $(DESTDIR)$(pkgdatadir)
b10_zonemgr_DATA = zonemgr.spec

CLEANFILES = b10-zonemgr zonemgr.pyc zonemgr.spec

man_MANS = b10-zonemgr.8
EXTRA_DIST = $(man_MANS) b10-zonemgr.xml

if ENABLE_MAN

b10-zonemgr.8: b10-zonemgr.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-zonemgr.xml

endif

zonemgr.spec: zonemgr.spec.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" zonemgr.spec.pre >$@

b10-zonemgr: zonemgr.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" zonemgr.py >$@
	chmod a+x $@
