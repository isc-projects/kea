SUBDIRS = . tests

pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-xfrout

b10_xfroutdir = $(pkgdatadir)
b10_xfrout_DATA = xfrout.spec

nodist_pylogmessage_PYTHON = $(PYTHON_LOGMSGPKG_DIR)/work/xfrout_messages.py
pylogmessagedir = $(pyexecdir)/isc/log_messages/

CLEANFILES = b10-xfrout xfrout.pyc xfrout.spec
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/xfrout_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/xfrout_messages.pyc

man_MANS = b10-xfrout.8
MAINTAINERCLEANFILES += $(man_MANS)
EXTRA_DIST = $(man_MANS) b10-xfrout.xml xfrout_messages.mes

if GENERATE_DOCS

b10-xfrout.8: b10-xfrout.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-xfrout.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild BIND 10 > $@

endif

# Define rule to build logging source files from message file
$(PYTHON_LOGMSGPKG_DIR)/work/xfrout_messages.py : xfrout_messages.mes
	$(top_builddir)/src/lib/log/compiler/message \
	-d $(PYTHON_LOGMSGPKG_DIR)/work -p $(srcdir)/xfrout_messages.mes

xfrout.spec: xfrout.spec.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" xfrout.spec.pre >$@

# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-xfrout: xfrout.py $(PYTHON_LOGMSGPKG_DIR)/work/xfrout_messages.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" xfrout.py >$@
	chmod a+x $@

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
