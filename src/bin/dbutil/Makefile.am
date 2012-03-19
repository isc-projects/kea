SUBDIRS = . tests

bin_SCRIPTS = b10-dbutil

noinst_SCRIPTS = run_dbutil.sh

CLEANFILES = b10-dbutil b10-dbutil.pyc

b10-dbutil: dbutil.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@SYSCONFDIR@@|@sysconfdir@|" \
	       -e "s|@@LIBEXECDIR@@|$(pkglibexecdir)|" dbutil.py >$@
	chmod a+x $@

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
