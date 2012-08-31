SUBDIRS = . tests

pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-zonemgr

b10_zonemgrdir = $(pkgdatadir)
b10_zonemgr_DATA = zonemgr.spec

nodist_pylogmessage_PYTHON = $(PYTHON_LOGMSGPKG_DIR)/work/zonemgr_messages.py
pylogmessagedir = $(pyexecdir)/isc/log_messages/

CLEANFILES  = b10-zonemgr zonemgr.pyc zonemgr.spec
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/zonemgr_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/zonemgr_messages.pyc

man_MANS = b10-zonemgr.8
MAINTAINERCLEANFILES = $(man_MANS)
EXTRA_DIST = $(man_MANS) b10-zonemgr.xml zonemgr_messages.mes

if GENERATE_DOCS

b10-zonemgr.8: b10-zonemgr.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-zonemgr.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild BIND 10 > $@

endif

# Build logging source file from message files
$(PYTHON_LOGMSGPKG_DIR)/work/zonemgr_messages.py : zonemgr_messages.mes
	$(top_builddir)/src/lib/log/compiler/message \
	-d $(PYTHON_LOGMSGPKG_DIR)/work -p $(srcdir)/zonemgr_messages.mes

zonemgr.spec: zonemgr.spec.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" zonemgr.spec.pre >$@

b10-zonemgr: zonemgr.py $(PYTHON_LOGMSGPKG_DIR)/work/zonemgr_messages.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" zonemgr.py >$@
	chmod a+x $@

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
