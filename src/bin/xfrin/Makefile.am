pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-xfrin

b10_xfrindir = $(DESTDIR)$(pkgdatadir)
b10_xfrin_DATA = xfrin.spec

CLEANFILES=	b10-xfrin

# TODO: does this need $$(DESTDIR) also?
# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-xfrin: xfrin.py
	$(SED) "s|@@PYTHONPATH@@|@pyexecdir@|" xfrin.py >$@
	chmod a+x $@
