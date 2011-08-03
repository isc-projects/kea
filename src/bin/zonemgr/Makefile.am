SUBDIRS = . tests

pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-zonemgr

b10_zonemgrdir = $(pkgdatadir)
b10_zonemgr_DATA = zonemgr.spec
pyexec_DATA = zonemgr_messages.py

CLEANFILES  = b10-zonemgr zonemgr.pyc zonemgr.spec
CLEANFILES += zonemgr_messages.py zonemgr_messages.pyc

man_MANS = b10-zonemgr.8
EXTRA_DIST = $(man_MANS) b10-zonemgr.xml

if ENABLE_MAN

b10-zonemgr.8: b10-zonemgr.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-zonemgr.xml

endif

# Build logging source file from message files
zonemgr_messages.py: zonemgr_messages.mes
	$(top_builddir)/src/lib/log/compiler/message -p $(top_srcdir)/src/bin/zonemgr/zonemgr_messages.mes

zonemgr.spec: zonemgr.spec.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" zonemgr.spec.pre >$@

b10-zonemgr: zonemgr.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" zonemgr.py >$@
	chmod a+x $@

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
