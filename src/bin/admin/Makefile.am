SUBDIRS = . scripts tests

# Install kea-admin in sbin.
sbin_SCRIPTS  = kea-admin

man_MANS = kea-admin.8
DISTCLEANFILES = $(man_MANS)
EXTRA_DIST = $(man_MANS) kea-admin.xml admin-utils.sh

if GENERATE_DOCS

kea-admin.8: kea-admin.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/kea-admin.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild Kea > $@

endif

adminscriptsdir = ${datarootdir}/${PACKAGE_NAME}/scripts
adminscripts_DATA = admin-utils.sh
