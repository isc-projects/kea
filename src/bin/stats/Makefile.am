SUBDIRS = tests

pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-stats b10-stats-httpd

b10_statsdir = $(pkgdatadir)
b10_stats_DATA = stats.spec stats-httpd.spec
b10_stats_DATA += stats-httpd-xml.tpl stats-httpd-xsd.tpl stats-httpd-xsl.tpl

nodist_pylogmessage_PYTHON = $(PYTHON_LOGMSGPKG_DIR)/work/stats_messages.py
nodist_pylogmessage_PYTHON += $(PYTHON_LOGMSGPKG_DIR)/work/stats_httpd_messages.py
pylogmessagedir = $(pyexecdir)/isc/log_messages/

CLEANFILES = b10-stats stats.pyc
CLEANFILES += b10-stats-httpd stats_httpd.pyc
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/stats_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/stats_messages.pyc
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/stats_httpd_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/stats_httpd_messages.pyc

man_MANS = b10-stats.8 b10-stats-httpd.8
DISTCLEANFILES = $(man_MANS)
EXTRA_DIST = $(man_MANS) b10-stats.xml b10-stats-httpd.xml
EXTRA_DIST += stats.spec stats-httpd.spec
EXTRA_DIST += stats-httpd-xml.tpl stats-httpd-xsd.tpl stats-httpd-xsl.tpl
EXTRA_DIST += stats_messages.mes stats_httpd_messages.mes

if GENERATE_DOCS

b10-stats.8: b10-stats.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-stats.xml

b10-stats-httpd.8: b10-stats-httpd.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-stats-httpd.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild BIND 10 > $@

endif

$(PYTHON_LOGMSGPKG_DIR)/work/stats_messages.py : stats_messages.mes
	$(top_builddir)/src/lib/log/compiler/message \
	-d $(PYTHON_LOGMSGPKG_DIR)/work -p $(srcdir)/stats_messages.mes

$(PYTHON_LOGMSGPKG_DIR)/work/stats_httpd_messages.py : stats_httpd_messages.mes
	$(top_builddir)/src/lib/log/compiler/message \
	-d $(PYTHON_LOGMSGPKG_DIR)/work -p $(srcdir)/stats_httpd_messages.mes

# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-stats: stats.py $(PYTHON_LOGMSGPKG_DIR)/work/stats_messages.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|"  stats.py >$@
	chmod a+x $@

b10-stats-httpd: stats_httpd.py $(PYTHON_LOGMSGPKG_DIR)/work/stats_httpd_messages.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" stats_httpd.py >$@
	chmod a+x $@

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
