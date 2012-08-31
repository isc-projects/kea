bin_SCRIPTS = isc-sysinfo

CLEANFILES = isc-sysinfo sysinfo.pyc

# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
isc-sysinfo: sysinfo.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" sysinfo.py >$@
	chmod a+x $@

MAN1_FILES = \
	isc-sysinfo.xml

man_MANS = \
	$(MAN1_FILES:.xml=.1)
CLEANFILES += $(man_MANS)

if GENERATE_DOCS

.xml.1:
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $<

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild BIND 10 > $@

endif

EXTRA_DIST = $(man_MANS) $(MAN1_FILES)

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
