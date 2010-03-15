bin_SCRIPTS = bindctl
man_MANS = bindctl.1

EXTRA_DIST = $(man_MANS)

python_PYTHON = __init__.py bindcmd.py cmdparse.py exception.py moduleinfo.py mycollections.py
pythondir = $(pyexecdir)/bindctl

CLEANFILES = bindctl

bindctl: bindctl.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LIBEXECDIR@@|$(pkglibexecdir)|" bindctl.py >$@
	chmod a+x $@
