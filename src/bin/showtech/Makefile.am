bin_SCRIPTS = b10-showtech

CLEANFILES = b10-showtech showtech.pyc

# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-showtech: showtech.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" showtech.py >$@
	chmod a+x $@

MAN1_FILES = \
	b10-showtech.xml

man_MANS = \
	$(MAN1_FILES:.xml=.1)
CLEANFILES += $(man_MANS)

if ENABLE_MAN

.xml.1:
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $<

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-man to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-man, and rebuild BIND 10 > $@

endif

EXTRA_DIST = $(man_MANS) $(MAN1_FILES)

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
