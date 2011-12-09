SUBDIRS = . tests

pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-ddns

b10_ddnsdir = $(pkgdatadir)
b10_ddns_DATA = ddns.spec

nodist_pylogmessage_PYTHON = $(PYTHON_LOGMSGPKG_DIR)/work/ddns_messages.py
pylogmessagedir = $(pyexecdir)/isc/log_messages/

CLEANFILES = b10-ddns ddns.pyc ddns.spec
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/ddns_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/ddns_messages.pyc

EXTRA_DIST =  ddns_messages.mes
#man_MANS = b10-ddns.8
#EXTRA_DIST += $(man_MANS) b10-ddns.xml

if ENABLE_MAN

b10-ddns.8: b10-ddns.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-ddns.xml

endif

# Define rule to build logging source files from message file
$(PYTHON_LOGMSGPKG_DIR)/work/ddns_messages.py : ddns_messages.mes
	$(top_builddir)/src/lib/log/compiler/message \
	-d $(PYTHON_LOGMSGPKG_DIR)/work -p $(srcdir)/ddns_messages.mes

ddns.spec: ddns.spec.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" ddns.spec.pre >$@

# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-ddns: ddns.py $(PYTHON_LOGMSGPKG_DIR)/work/ddns_messages.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" ddns.py >$@
	chmod a+x $@

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
