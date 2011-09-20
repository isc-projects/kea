SUBDIRS = . tests

pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-xfrin

b10_xfrindir = $(pkgdatadir)
b10_xfrin_DATA = xfrin.spec

nodist_pylogmessage_PYTHON = $(PYTHON_LOGMSGPKG_DIR)/work/xfrin_messages.py
pylogmessagedir = $(pyexecdir)/isc/log_messages/

CLEANFILES = b10-xfrin xfrin.pyc xfrinlog.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/xfrin_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/xfrin_messages.pyc

man_MANS = b10-xfrin.8
EXTRA_DIST = $(man_MANS) b10-xfrin.xml
EXTRA_DIST += xfrin.spec xfrin_messages.mes

if ENABLE_MAN

b10-xfrin.8: b10-xfrin.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-xfrin.xml

endif

# Define rule to build logging source files from message file
$(PYTHON_LOGMSGPKG_DIR)/work/xfrin_messages.py : xfrin_messages.mes
	$(top_builddir)/src/lib/log/compiler/message \
	-d $(PYTHON_LOGMSGPKG_DIR)/work -p $(srcdir)/xfrin_messages.mes

# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-xfrin: xfrin.py $(PYTHON_LOGMSGPKG_DIR)/work/xfrin_messages.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" xfrin.py >$@
	chmod a+x $@

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
