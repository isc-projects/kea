SUBDIRS = . tests

bin_SCRIPTS = bindctl
man_MANS = bindctl.1

EXTRA_DIST = $(man_MANS) bindctl.xml

noinst_SCRIPTS = run_bindctl.sh

python_PYTHON = __init__.py bindcmd.py cmdparse.py exception.py moduleinfo.py \
		mycollections.py command_sets.py
pythondir = $(pyexecdir)/bindctl

bindctldir = $(pkgdatadir)

CLEANFILES = bindctl bindctl_main.pyc
MAINTAINERCLEANFILES = $(man_MANS)

if GENERATE_DOCS

bindctl.1: bindctl.xml
	@XSLTPROC@ --novalid --xinclude --nonet -o $@ http://docbook.sourceforge.net/release/xsl/current/manpages/docbook.xsl $(srcdir)/bindctl.xml

else

$(man_MANS):
	@echo Man generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Man generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild BIND 10 > $@

endif

bindctl: bindctl_main.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@SYSCONFDIR@@|@sysconfdir@|" \
	       -e "s|@@LIBEXECDIR@@|$(pkglibexecdir)|" bindctl_main.py >$@
	chmod a+x $@

CLEANDIRS = __pycache__

clean-local:
	rm -rf $(CLEANDIRS)
