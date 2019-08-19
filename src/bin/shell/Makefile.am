SUBDIRS = . tests

pkgpython_PYTHON = kea_conn.py kea_connector2.py kea_connector3.py

sbin_SCRIPTS = kea-shell

CLEANFILES = *.pyc

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
