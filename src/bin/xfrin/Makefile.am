pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-xfrin

b10_xfrindir = $(DESTDIR)$(pkgdatadir)
b10_xfrin_DATA = xfrin.spec

CLEANFILES = b10-xfrin xfrin.pre xfrin.spec

man_MANS = b10-xfrin.8
EXTRA_DIST += $(man_MANS) b10-xfrin.xml

if ENABLE_MAN

b10-xfrin.8: b10-xfrin.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-xfrin.xml

endif

xfrin.spec: xfrin.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" xfrin.pre >$@

# TODO: does this need $$(DESTDIR) also?
# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-xfrin: xfrin.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" xfrin.py >$@
	chmod a+x $@
