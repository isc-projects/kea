SUBDIRS = . tests

pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-msgq

CLEANFILES = b10-msgq msgq.pyc
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/msgq_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/msgq_messages.pyc

man_MANS = b10-msgq.8
DISTCLEANFILES = $(man_MANS)
EXTRA_DIST = $(man_MANS) msgq.xml msgq_messages.mes

nodist_pylogmessage_PYTHON = $(PYTHON_LOGMSGPKG_DIR)/work/msgq_messages.py
pylogmessagedir = $(pyexecdir)/isc/log_messages/
BUILT_SOURCES = $(PYTHON_LOGMSGPKG_DIR)/work/msgq_messages.py

if GENERATE_DOCS

b10-msgq.8: msgq.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/msgq.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild BIND 10 > $@

endif

# Define rule to build logging source files from message file
$(PYTHON_LOGMSGPKG_DIR)/work/msgq_messages.py : msgq_messages.mes
	$(top_builddir)/src/lib/log/compiler/message \
	-d $(PYTHON_LOGMSGPKG_DIR)/work -p $(srcdir)/msgq_messages.mes

# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-msgq: msgq.py
	$(SED) "s|@@PYTHONPATH@@|@pyexecdir@|" msgq.py >$@
	chmod a+x $@

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
