SUBDIRS = . tests

sbin_SCRIPTS = bind10
pkglibexec_SCRIPTS = b10-init
CLEANFILES = b10-init b10-init.pyc init.pyc
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/init_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/init_messages.pyc

pkglibexecdir = $(libexecdir)/@PACKAGE@

nodist_pylogmessage_PYTHON = $(PYTHON_LOGMSGPKG_DIR)/work/init_messages.py
pylogmessagedir = $(pyexecdir)/isc/log_messages/

noinst_SCRIPTS = run_bind10.sh

bind10dir = $(pkgdatadir)
bind10_DATA = init.spec
EXTRA_DIST = init.spec bind10.in

man_MANS = b10-init.8 bind10.8
DISTCLEANFILES = $(man_MANS) bind10
EXTRA_DIST += $(man_MANS) b10-init.xml bind10.xml init_messages.mes

if GENERATE_DOCS

bind10.8: bind10.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/bind10.xml

b10-init.8: b10-init.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-init.xml

#dist-local-check-mans-enabled:
#	@if grep "Man generation disabled" $(man_MANS) >/dev/null; then $(RM) $(man_MANS); fi

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild BIND 10 > $@

#dist-local-check-mans-enabled:
#	@echo "*** --enable-generate-docs must be used in order to make dist"
#	@false

endif

$(PYTHON_LOGMSGPKG_DIR)/work/init_messages.py : init_messages.mes
	$(top_builddir)/src/lib/log/compiler/message \
	-d $(PYTHON_LOGMSGPKG_DIR)/work -p $(srcdir)/init_messages.mes

# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-init: init.py $(PYTHON_LOGMSGPKG_DIR)/work/init_messages.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LIBDIR@@|$(libdir)|" \
	       -e "s|@@LIBEXECDIR@@|$(pkglibexecdir)|" init.py >$@
	chmod a+x $@

pytest:
	$(SHELL) tests/bind10_test

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
