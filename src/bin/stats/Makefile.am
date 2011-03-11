SUBDIRS = tests

pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-stats b10-stats-httpd

b10_statsdir = $(pkgdatadir)
b10_stats_DATA = stats.spec stats-httpd.spec
b10_stats_DATA += stats-httpd-xml.tpl stats-httpd-xsd.tpl stats-httpd-xsl.tpl

CLEANFILES = b10-stats stats.pyc
CLEANFILES += b10-stats-httpd stats_httpd.pyc

man_MANS = b10-stats.8 b10-stats-httpd.8
EXTRA_DIST = $(man_MANS) b10-stats.xml b10-stats-httpd.xml
EXTRA_DIST += stats.spec stats-httpd.spec
EXTRA_DIST += stats-httpd-xml.tpl stats-httpd-xsd.tpl stats-httpd-xsl.tpl

if ENABLE_MAN

b10-stats.8: b10-stats.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-stats.xml

b10-stats-httpd.8: b10-stats-httpd.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-stats-httpd.xml

endif

# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-stats: stats.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|.*#@@REMOVED@@$$||"  stats.py >$@
	chmod a+x $@

b10-stats-httpd: stats_httpd.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" stats_httpd.py >$@
	chmod a+x $@
