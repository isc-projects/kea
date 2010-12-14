SUBDIRS = tests

pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-stats
noinst_SCRIPTS = b10-stats_stub

b10_statsdir = $(DESTDIR)$(pkgdatadir)
b10_stats_DATA = stats.spec

CLEANFILES = stats.spec b10-stats stats.pyc stats.pyo b10-stats_stub stats_stub.pyc stats_stub.pyo

man_MANS = b10-stats.8
EXTRA_DIST = $(man_MANS) b10-stats.xml

if ENABLE_MAN

b10-stats.8: b10-stats.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-stats.xml

endif

stats.spec: stats.spec.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" stats.spec.pre >$@

# TODO: does this need $$(DESTDIR) also?
# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-stats: stats.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" \
	       -e "s|.*#@@REMOVED@@$$||"  stats.py >$@
	chmod a+x $@

b10-stats_stub: stats_stub.py stats.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" stats_stub.py >$@
	chmod a+x $@
