SUBDIRS = . tests

pkgpython_PYTHON = kea_conn.py kea_connector2.py kea_connector3.py

sbin_SCRIPTS = kea-shell

CLEANFILES = *.pyc

man_MANS = kea-shell.8
DISTCLEANFILES = $(sbin_SCRIPTS) $(man_MANS)
EXTRA_DIST = $(man_MANS) kea-shell.xml

if GENERATE_DOCS
kea-shell.8: kea-shell.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ \
        http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl \
	$(srcdir)/kea-shell.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild Kea > $@

endif

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
