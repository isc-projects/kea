SUBDIRS = tests

pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-zonemgr

b10_zonemgrdir = $(DESTDIR)$(pkgdatadir)
b10_zonemgr_DATA = zonemgr.spec

CLEANFILES = b10-zonemgr zonemgr.pyc zonemgr.spec

zonemgr.spec: zonemgr.spec.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" zonemgr.spec.pre >$@

b10-zonemgr: zonemgr.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" zonemgr.py >$@
	chmod a+x $@
