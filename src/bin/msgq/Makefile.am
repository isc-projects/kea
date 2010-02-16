pkglibexecdir = $(libexecdir)/@PACKAGE@
 
pkglibexec_SCRIPTS = msgq

CLEANFILES = msgq

# TODO: does this need $$(DESTDIR) also?
# this is done here since configure.ac AC_OUTPUT doesn't expand exec_prefix
msgq: msgq.py
	$(SED) "s|@@PYTHONPATH@@|@pyexecdir@|" msgq.py >$@
	chmod a+x $@
