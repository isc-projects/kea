bin_SCRIPTS = bindctl
man_MANS = bindctl.1

EXTRA_DIST = $(man_MANS)

CLEANFILES = bindctl

bindctl: bindctl.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LIBEXECDIR@@|$(pkglibexecdir)|" bindctl.py >$@
	chmod a+x $@
