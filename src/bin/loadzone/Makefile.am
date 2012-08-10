SUBDIRS = . tests/correct tests/error
bin_SCRIPTS = b10-loadzone
noinst_SCRIPTS = run_loadzone.sh

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

EXTRA_DIST += tests/normal/README
EXTRA_DIST += tests/normal/dsset-subzone.example.com
EXTRA_DIST += tests/normal/example.com
EXTRA_DIST += tests/normal/example.com.signed
EXTRA_DIST += tests/normal/Kexample.com.+005+04456.key
EXTRA_DIST += tests/normal/Kexample.com.+005+04456.private
EXTRA_DIST += tests/normal/Kexample.com.+005+33495.key
EXTRA_DIST += tests/normal/Kexample.com.+005+33495.private
EXTRA_DIST += tests/normal/Ksql1.example.com.+005+12447.key
EXTRA_DIST += tests/normal/Ksql1.example.com.+005+12447.private
EXTRA_DIST += tests/normal/Ksql1.example.com.+005+33313.key
EXTRA_DIST += tests/normal/Ksql1.example.com.+005+33313.private
EXTRA_DIST += tests/normal/Ksql2.example.com.+005+38482.key
EXTRA_DIST += tests/normal/Ksql2.example.com.+005+38482.private
EXTRA_DIST += tests/normal/Ksql2.example.com.+005+63192.key
EXTRA_DIST += tests/normal/Ksql2.example.com.+005+63192.private
EXTRA_DIST += tests/normal/sql1.example.com
EXTRA_DIST += tests/normal/sql1.example.com.signed
EXTRA_DIST += tests/normal/sql2.example.com
EXTRA_DIST += tests/normal/sql2.example.com.signed

pytest:
	$(SHELL) tests/correct/correct_test.sh
	$(SHELL) tests/error/error_test.sh
