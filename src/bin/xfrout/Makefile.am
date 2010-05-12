SUBDIRS = tests

pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-xfrout

b10_xfroutdir = $(DESTDIR)$(pkgdatadir)
b10_xfrout_DATA = xfrout.spec

CLEANFILES=	b10-xfrout xfrout.pyc xfrout.spec

man_MANS = b10-xfrout.8
EXTRA_DIST = $(man_MANS) b10-xfrout.xml

if ENABLE_MAN

b10-xfrout.8: b10-xfrout.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-xfrout.xml

endif


xfrout.spec: xfrout.spec.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" xfrout.spec.pre >$@

# TODO: does this need $$(DESTDIR) also?
# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-xfrout: xfrout.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" xfrout.py >$@
	chmod a+x $@
