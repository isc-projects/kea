SUBDIRS = . tests

bin_SCRIPTS = b10-dbutil

CLEANFILES = b10-dbutil b10-dbutil.pyc

b10-dbutil: dbutil.py
	$(SED) -e "s|@@LOCALSTATEDIR@@|$(localstatedir)|" dbutil.py > $@
	chmod a+x $@

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
