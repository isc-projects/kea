SUBDIRS = . tests

pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-cmdctl

nodist_pylogmessage_PYTHON = $(PYTHON_LOGMSGPKG_DIR)/work/cmdctl_messages.py
pylogmessagedir = $(pyexecdir)/isc/log_messages/

b10_cmdctldir = $(pkgdatadir)

# NOTE: this will overwrite on install
# So these generic copies are placed in share/bind10 instead of to etc
# Admin or packageer will need to put into place manually.

CMDCTL_CONFIGURATIONS = cmdctl-accounts.csv
CMDCTL_CONFIGURATIONS += cmdctl-keyfile.pem cmdctl-certfile.pem

b10_cmdctl_DATA = $(CMDCTL_CONFIGURATIONS)
b10_cmdctl_DATA += cmdctl.spec

EXTRA_DIST = $(CMDCTL_CONFIGURATIONS)

CLEANFILES= b10-cmdctl cmdctl.pyc cmdctl.spec
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/cmdctl_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/cmdctl_messages.pyc

man_MANS = b10-cmdctl.8
MAINTAINERCLEANFILES = $(man_MANS)
EXTRA_DIST += $(man_MANS) b10-cmdctl.xml cmdctl_messages.mes

if GENERATE_DOCS

b10-cmdctl.8: b10-cmdctl.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-cmdctl.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild BIND 10 > $@

endif

cmdctl.spec: cmdctl.spec.pre
	$(SED) -e "s|@@SYSCONFDIR@@|$(sysconfdir)|" cmdctl.spec.pre >$@

$(PYTHON_LOGMSGPKG_DIR)/work/cmdctl_messages.py : cmdctl_messages.mes
	$(top_builddir)/src/lib/log/compiler/message \
	-d $(PYTHON_LOGMSGPKG_DIR)/work -p $(srcdir)/cmdctl_messages.mes

# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-cmdctl: cmdctl.py $(PYTHON_LOGMSGPKG_DIR)/work/cmdctl_messages.py
	$(SED) "s|@@PYTHONPATH@@|@pyexecdir@|" cmdctl.py >$@
	chmod a+x $@

if INSTALL_CONFIGURATIONS

# Below we intentionally use ${INSTALL} -m 640 instead of $(INSTALL_DATA)
# because these file will contain sensitive information.
install-data-local:
	$(mkinstalldirs) $(DESTDIR)/@sysconfdir@/@PACKAGE@   
	for f in $(CMDCTL_CONFIGURATIONS) ; do	\
	  if test ! -f $(DESTDIR)$(sysconfdir)/@PACKAGE@/$$f; then	\
	    ${INSTALL} -m 640 $(srcdir)/$$f $(DESTDIR)$(sysconfdir)/@PACKAGE@/ ;	\
	  fi ;	\
	done

endif

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
