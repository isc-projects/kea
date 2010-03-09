sbin_SCRIPTS = bind10
CLEANFILES = bind10

pkglibexecdir = $(libexecdir)/@PACKAGE@

bind10dir = $(DESTDIR)$(pkgdatadir)
bind10_DATA = bob.spec

# TODO: does this need $$(DESTDIR) also?
# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
bind10: bind10.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LIBEXECDIR@@|$(pkglibexecdir)|" bind10.py >$@
	chmod a+x $@

check: test

test: pytest

pytest:
	$(SHELL) tests/bind10_test
