bin_SCRIPTS = bind10
CLEANFILES = bind10.py

# TODO: does this need $$(DESTDIR) also?
# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
bind10: bind10.py
	$(SED) "s|@@PYTHONPATH@@|@pyexecdir@|" bind10.py >$@
#        chmod a+x $@
