SUBDIRS = . tests

sbin_SCRIPTS = bind10
CLEANFILES = bind10 bind10_src.pyc bind10_messages.py bind10_messages.pyc

pkglibexecdir = $(libexecdir)/@PACKAGE@
pyexec_DATA = bind10_messages.py

bind10dir = $(pkgdatadir)
bind10_DATA = bob.spec
EXTRA_DIST = bob.spec

man_MANS = bind10.8
EXTRA_DIST += $(man_MANS) bind10.xml bind10_messages.mes

if ENABLE_MAN

bind10.8: bind10.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/bind10.xml 

endif

bind10_messages.py: bind10_messages.mes
	$(top_builddir)/src/lib/log/compiler/message -p $(top_srcdir)/src/bin/bind10/bind10_messages.mes

# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
bind10: bind10_src.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LIBEXECDIR@@|$(pkglibexecdir)|" bind10_src.py >$@
	chmod a+x $@

pytest:
	$(SHELL) tests/bind10_test

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
