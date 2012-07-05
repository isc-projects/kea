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

if ENABLE_MAN

.xml.1:
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $<

endif

EXTRA_DIST = $(man_MANS) $(MAN1_FILES)

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
