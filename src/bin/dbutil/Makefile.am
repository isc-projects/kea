SUBDIRS = . tests

bin_SCRIPTS = b10-dbutil
man_MANS = b10-dbutil.8

EXTRA_DIST = $(man_MANS) b10-dbutil.xml

noinst_SCRIPTS = run_dbutil.sh

CLEANFILES = b10-dbutil b10-dbutil.pyc

if ENABLE_MAN

b10-dbutil.8: b10-dbutil.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-dbutil.xml

endif

b10-dbutil: dbutil.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@SYSCONFDIR@@|@sysconfdir@|" \
	       -e "s|@@LIBEXECDIR@@|$(pkglibexecdir)|" dbutil.py >$@
	chmod a+x $@

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
