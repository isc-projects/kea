pkglibexecdir = $(libexecdir)/@PACKAGE@

pkglibexec_SCRIPTS = b10-xfrout

b10_xfroutdir = $(DESTDIR)$(pkgdatadir)
b10_xfrout_DATA = xfrout.spec

CLEANFILES=	b10-xfrout xfrout.spec

EXTRA_DIST = tests/xfrout_test.py

xfrout.spec: xfrout.spec.pre
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" xfrout.spec.pre >$@

# TODO: does this need $$(DESTDIR) also?
# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
b10-xfrout: xfrout.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" xfrout.py >$@
	chmod a+x $@
