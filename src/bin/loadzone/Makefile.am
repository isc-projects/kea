bin_SCRIPTS = b10-loadzone

CLEANFILES = b10-loadzone

man_MANS = b10-loadzone.8
EXTRA_DIST = $(man_MANS) b10-loadzone.xml

if ENABLE_MAN

b10-loadzone.8: b10-loadzone.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-loadzone.xml

endif

b10-loadzone: b10-loadzone.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" \
	       -e "s|@@LIBEXECDIR@@|$(pkglibexecdir)|" b10-loadzone.py >$@
	chmod a+x $@

install-data-local:
	$(mkinstalldirs) $(DESTDIR)/@localstatedir@/@PACKAGE@
# TODO: permissions handled later
