SUBDIRS = . tests

sbin_SCRIPTS = bind10
CLEANFILES = bind10 bind10_src.pyc
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/bind10_messages.py
CLEANFILES += $(PYTHON_LOGMSGPKG_DIR)/work/bind10_messages.pyc

pkglibexecdir = $(libexecdir)/@PACKAGE@

nodist_pylogmessage_PYTHON = $(PYTHON_LOGMSGPKG_DIR)/work/bind10_messages.py
pylogmessagedir = $(pyexecdir)/isc/log_messages/

noinst_SCRIPTS = run_bind10.sh

bind10dir = $(pkgdatadir)
bind10_DATA = bob.spec
EXTRA_DIST = bob.spec

man_MANS = bind10.8
EXTRA_DIST += $(man_MANS) bind10.xml bind10_messages.mes

if ENABLE_MAN

bind10.8: bind10.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/bind10.xml 

endif

$(PYTHON_LOGMSGPKG_DIR)/work/bind10_messages.py : bind10_messages.mes
	$(top_builddir)/src/lib/log/compiler/message \
	-d $(PYTHON_LOGMSGPKG_DIR)/work -p $(srcdir)/bind10_messages.mes

# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
bind10: bind10_src.py $(PYTHON_LOGMSGPKG_DIR)/work/bind10_messages.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LIBDIR@@|$(libdir)|" \
	       -e "s|@@LIBEXECDIR@@|$(pkglibexecdir)|" bind10_src.py >$@
	chmod a+x $@

pytest:
	$(SHELL) tests/bind10_test

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
