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

EXTRA_DIST =  testdata/README
EXTRA_DIST += testdata/dsset-subzone.example.com.
EXTRA_DIST += testdata/example.com
EXTRA_DIST += testdata/example.com.signed
EXTRA_DIST += testdata/Kexample.com.+005+04456.key
EXTRA_DIST += testdata/Kexample.com.+005+04456.private
EXTRA_DIST += testdata/Kexample.com.+005+33495.key
EXTRA_DIST += testdata/Kexample.com.+005+33495.private
EXTRA_DIST += testdata/Ksql1.example.com.+005+12447.key
EXTRA_DIST += testdata/Ksql1.example.com.+005+12447.private
EXTRA_DIST += testdata/Ksql1.example.com.+005+33313.key
EXTRA_DIST += testdata/Ksql1.example.com.+005+33313.private
EXTRA_DIST += testdata/Ksql2.example.com.+005+38482.key
EXTRA_DIST += testdata/Ksql2.example.com.+005+38482.private
EXTRA_DIST += testdata/Ksql2.example.com.+005+63192.key
EXTRA_DIST += testdata/Ksql2.example.com.+005+63192.private
EXTRA_DIST += testdata/sql1.example.com
EXTRA_DIST += testdata/sql1.example.com.signed
EXTRA_DIST += testdata/sql2.example.com
EXTRA_DIST += testdata/sql2.example.com.signed
