# SUBDIRS = . tests

pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-recurse

b10_recursedir = $(DESTDIR)$(pkgdatadir)
b10_recurse_DATA = recurse.spec

CLEANFILES=	b10-recurse recurse.pyc recurse.py recurse.spec recurse.spec.pre

recurse.spec: recurse.spec.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" recurse.spec.pre >$@

# TODO: does this need $$(DESTDIR) also?
# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-recurse: recurse.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" recurse.py >$@
	chmod a+x $@
