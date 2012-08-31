SUBDIRS = . plugins tests

pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-cfgmgr

CLEANFILES = b10-cfgmgr b10-cfgmgr.pyc

b10_cfgmgrdir = @localstatedir@/@PACKAGE@
#B10_cfgmgr_DATA = 

man_MANS = b10-cfgmgr.8
CLEANFILES += $(man_MANS)
EXTRA_DIST = $(man_MANS) b10-cfgmgr.xml

if GENERATE_DOCS

b10-cfgmgr.8: b10-cfgmgr.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-cfgmgr.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild BIND 10 > $@

endif

# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-cfgmgr: b10-cfgmgr.py
	$(SED) "s|@@PYTHONPATH@@|@pyexecdir@|" b10-cfgmgr.py >$@
	chmod a+x $@

install-data-local:
	$(mkinstalldirs) $(DESTDIR)/@localstatedir@/@PACKAGE@

install-data-hook:
	-chmod 2770 $(DESTDIR)/@localstatedir@/@PACKAGE@

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
