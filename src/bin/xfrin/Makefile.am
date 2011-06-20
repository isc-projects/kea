SUBDIRS = . tests

pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-xfrin

b10_xfrindir = $(pkgdatadir)
b10_xfrin_DATA = xfrin.spec

CLEANFILES = b10-xfrin xfrin.pyc xfrinlog.py

man_MANS = b10-xfrin.8
EXTRA_DIST = $(man_MANS) b10-xfrin.xml
EXTRA_DIST += xfrin.spec

if ENABLE_MAN

b10-xfrin.8: b10-xfrin.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-xfrin.xml

endif

# Define rule to build logging source files from message file
xfrinlog.py: xfrinlog.mes
	$(top_builddir)/src/lib/log/compiler/message -p $(top_srcdir)/src/bin/xfrin/xfrinlog.mes

# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-xfrin: xfrin.py xfrinlog.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" xfrin.py >$@
	chmod a+x $@

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
