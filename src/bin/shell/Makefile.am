SUBDIRS = . tests

pkgpython_PYTHON = kea_conn.py kea_connector2.py kea_connector3.py

sbin_SCRIPTS = kea-shell

CLEANFILES = *.pyc

man_MANS = kea-shell.8
DISTCLEANFILES = $(sbin_SCRIPTS) $(man_MANS)

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
