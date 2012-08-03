SUBDIRS = . tests

pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-ddns

b10_ddnsdir = $(pkgdatadir)
b10_ddns_DATA = ddns.spec

nodist_pylogmessage_PYTHON = $(PYTHON_LOGMSGPKG_DIR)/work/ddns_messages.py
pylogmessagedir = $(pyexecdir)/isc/log_messages/

CLEANFILES = b10-ddns ddns.pyc
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/ddns_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/ddns_messages.pyc

EXTRA_DIST =  ddns_messages.mes ddns.spec

man_MANS = b10-ddns.8
CLEANFILES += $(man_MANS)
EXTRA_DIST += $(man_MANS) b10-ddns.xml

if GENERATE_DOCS

b10-ddns.8: b10-ddns.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-ddns.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild BIND 10 > $@

endif

# Define rule to build logging source files from message file
$(PYTHON_LOGMSGPKG_DIR)/work/ddns_messages.py : ddns_messages.mes
	$(top_builddir)/src/lib/log/compiler/message \
	-d $(PYTHON_LOGMSGPKG_DIR)/work -p $(srcdir)/ddns_messages.mes

# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-ddns: ddns.py $(PYTHON_LOGMSGPKG_DIR)/work/ddns_messages.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" ddns.py >$@
	chmod a+x $@

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
