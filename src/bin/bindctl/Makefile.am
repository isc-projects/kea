bin_SCRIPTS = bindctl
man_MANS = bindctl.1

bindctl: bindctl.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LIBEXECDIR@@|$(pkglibexecdir)|" bindctl.py >$@
	chmod a+x $@
