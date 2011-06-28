SUBDIRS = . tests

pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-xfrout

b10_xfroutdir = $(pkgdatadir)
b10_xfrout_DATA = xfrout.spec
pyexec_DATA = xfrout_messages.py

CLEANFILES=	b10-xfrout xfrout.pyc xfrout.spec xfrout_messages.py xfrout_messages.pyc

man_MANS = b10-xfrout.8
EXTRA_DIST = $(man_MANS) b10-xfrout.xml xfrout_messages.mes

if ENABLE_MAN

b10-xfrout.8: b10-xfrout.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/b10-xfrout.xml

endif

# Define rule to build logging source files from message file
xfrout_messages.py: xfrout_messages.mes
	$(top_builddir)/src/lib/log/compiler/message -p $(top_srcdir)/src/bin/xfrout/xfrout_messages.mes

xfrout.spec: xfrout.spec.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" xfrout.spec.pre >$@

# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-xfrout: xfrout.py xfrout_messages.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" xfrout.py >$@
	chmod a+x $@

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
