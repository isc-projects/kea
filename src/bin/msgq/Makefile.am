pkglibexecdir = $(libexecdir)/@PACKAGE@
 
pkglibexec_SCRIPTS = b10-msgq

CLEANFILES = b10-msgq

man_MANS = b10-msgq.8
EXTRA_DIST = $(man_MANS) msgq.xml msgq_test.py

if ENABLE_MAN

b10-msgq.8: msgq.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/msgq.xml

endif

# TODO: does this need $$(DESTDIR) also?
# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-msgq: msgq.py
	$(SED) "s|@@PYTHONPATH@@|@pyexecdir@|" msgq.py >$@
	chmod a+x $@
