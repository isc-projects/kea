sbin_SCRIPTS = bind10
CLEANFILES = bind10

pkglibexecdir = $(libexecdir)/@PACKAGE@

bind10dir = $(DESTDIR)$(pkgdatadir)
bind10_DATA = bob.spec
EXTRA_DIST = bob.spec

man_MANS = bind10.8
EXTRA_DIST += $(man_MANS) bind10.xml

if ENABLE_MAN

bind10.8: bind10.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/bind10.xml 

endif

# TODO: does this need $$(DESTDIR) also?
# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
bind10: bind10.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LIBEXECDIR@@|$(pkglibexecdir)|" bind10.py >$@
	chmod a+x $@

pytest:
	$(SHELL) tests/bind10_test
