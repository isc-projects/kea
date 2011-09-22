SUBDIRS = . tests

bin_SCRIPTS = bindctl
man_MANS = bindctl.1

EXTRA_DIST = $(man_MANS) bindctl.xml

noinst_SCRIPTS = run_bindctl.sh

python_PYTHON = __init__.py bindcmd.py cmdparse.py exception.py moduleinfo.py \
		mycollections.py
pythondir = $(pyexecdir)/bindctl

bindctldir = $(pkgdatadir)

CLEANFILES = bindctl bindctl_main.pyc

if ENABLE_MAN

bindctl.1: bindctl.xml
	xsltproc --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/bindctl.xml

endif

bindctl: bindctl_main.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@SYSCONFDIR@@|@sysconfdir@|" \
	       -e "s|@@LIBEXECDIR@@|$(pkglibexecdir)|" bindctl_main.py >$@
	chmod a+x $@

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
