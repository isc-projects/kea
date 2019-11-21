EXTRA_DIST=
sphinxbuilddir=$(builddir)/_build

if GENERATE_DOCS

sphinxopts=
sphinxopts+=-v
sphinxopts+=-E
sphinxopts+=-a
sphinxopts+=-W
sphinxopts+=-j 2
sphinxopts+=-c "${abs_srcdir}"


static_sources=
static_sources+=static/kea-imageonly-100bw.png
static_sources+=static/kea-logo-200.png
static_sources+=static/kea.css

# ARM
rst_arm_sources=
rst_arm_sources+=arm/acknowledgments.rst
rst_arm_sources+=arm/admin.rst
rst_arm_sources+=arm/agent.rst
rst_arm_sources+=arm/classify.rst
rst_arm_sources+=arm/config-backend.rst
rst_arm_sources+=arm/config.rst
rst_arm_sources+=arm/congestion-handling.rst
rst_arm_sources+=arm/ctrl-channel.rst
rst_arm_sources+=arm/ddns.rst
rst_arm_sources+=arm/dhcp4-srv.rst
rst_arm_sources+=arm/dhcp6-srv.rst
rst_arm_sources+=arm/hammer.rst
rst_arm_sources+=arm/hooks-bootp.rst
rst_arm_sources+=arm/hooks-cb-cmds.rst
rst_arm_sources+=arm/hooks-class-cmds.rst
rst_arm_sources+=arm/hooks-ha.rst
rst_arm_sources+=arm/hooks-host-cache.rst
rst_arm_sources+=arm/hooks-lease-cmds.rst
rst_arm_sources+=arm/hooks-radius.rst
rst_arm_sources+=arm/hooks.rst
rst_arm_sources+=arm/hooks-stat-cmds.rst
rst_arm_sources+=arm/install.rst
rst_arm_sources+=index.rst
rst_arm_sources+=arm/intro.rst
rst_arm_sources+=arm/keactrl.rst
rst_arm_sources+=arm/lease-expiration.rst
rst_arm_sources+=arm/lfc.rst
rst_arm_sources+=arm/logging.rst
rst_arm_sources+=manpages.rst
rst_arm_sources+=arm/netconf.rst
rst_arm_sources+=arm/quickstart.rst
rst_arm_sources+=arm/shell.rst
rst_arm_sources+=arm/stats.rst

main_sources=$(rst_arm_sources) conf.py $(static_sources)

# mans
rst_man_sources=
rst_man_sources+=man/kea-admin.8.rst
rst_man_sources+=man/kea-ctrl-agent.8.rst
rst_man_sources+=man/kea-dhcp4.8.rst
rst_man_sources+=man/kea-dhcp6.8.rst
rst_man_sources+=man/kea-dhcp-ddns.8.rst
rst_man_sources+=man/kea-lfc.8.rst
rst_man_sources+=man/kea-netconf.8.rst
rst_man_sources+=man/kea-shell.8.rst
rst_man_sources+=man/keactrl.8.rst
rst_man_sources+=man/perfdhcp.8.rst
man_sources=$(rst_man_sources) conf.py
man8s=$(foreach rst,$(rst_man_sources), $(sphinxbuilddir)/$(basename $(rst)))

EXTRA_DIST+=$(main_sources) $(man_sources) mes2doc.py api2doc.py $(man8s)

# list of messages files that are used to generate kea-messages.rst and then kea-messages.pdf
mes_files1=$(shell cat mes-files.txt)
mes_files=$(foreach mf,$(mes_files1), $(top_srcdir)/$(mf))


# list of api files that are used to generate api.rst
api_files1=$(shell cat api-files.txt)
api_files=$(foreach af,$(api_files1), $(srcdir)/$(af))

EXTRA_DIST+=mes-files.txt
EXTRA_DIST+=api-files.txt
EXTRA_DIST+=$(api_files)
EXTRA_DIST+=api/README
EXTRA_DIST+=api/_template.json
EXTRA_DIST+=api/generate-templates
EXTRA_DIST+=api/cmds-list


if HAVE_PDFLATEX
all: html mans pdf
else
all: html mans
endif

# this rule is only used for development purposes and is not used in official
# build process as kea-messages.rst is always generated via sphinx's conf.py
$(srcdir)/kea-messages.rst: $(mes_files) mes2doc.py
	$(PYTHON) $(srcdir)/mes2doc.py -o $@ $(mes_files)

# this rule is only used for development purposes and is not used in official
# build process as api.rst is always generated via sphinx's conf.py
$(srcdir)/api.rst: $(api_files) api2doc.py
	$(PYTHON) $(srcdir)/api2doc.py -o $@ $(api_files)


PDFLATEX_AND_OPTS=$(PDFLATEX) -interaction nonstopmode

pdf: $(main_sources)
	$(SPHINXBUILD) -M latex $(srcdir) $(sphinxbuilddir) $(sphinxopts)
	-cd $(sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-arm.tex
	-cd $(sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-arm.tex
	-cd $(sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-arm.tex
	-cd $(sphinxbuilddir)/latex && makeindex -s python.ist kea-arm.idx
	-cd $(sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-arm.tex
	cd $(sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-arm.tex
	-cd $(sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-messages.tex
	-cd $(sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-messages.tex
	-cd $(sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-messages.tex
	-cd $(sphinxbuilddir)/latex && makeindex -s python.ist kea-messages.idx
	-cd $(sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-messages.tex
	cd $(sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-messages.tex

html: $(main_sources)
	$(SPHINXBUILD) -M html $(srcdir) $(sphinxbuilddir) $(sphinxopts)

# This target is not used anywhere, but people who prefer single page docs
# can do make -C doc/sphinx singlehtml and then enjoy their docs being
# generated in doc/sphinx/_build/singlehtml
singlehtml: $(main_sources)
	$(SPHINXBUILD) -M singlehtml $(srcdir) $(sphinxbuilddir) $(sphinxopts)

$(man8s): mans

mans: $(man_sources)
	$(SPHINXBUILD) -M man $(srcdir) $(sphinxbuilddir) $(sphinxopts)

clean-local:
	rm -rf $(sphinxbuilddir)
	rm -f $(srcdir)/kea-messages.rst $(srcdir)/api.rst

.PHONY: all pdf html mans

endif

# install and uninstall can occur with GENERATE_DOCS and without it
# so we want to install all when GENERATE_DOCS is and
# just mans when GENERATE_DOCS is not used, and when man files exists (e.g release tarball)
install-data-local:
	mkdir -p $(DESTDIR)$(docdir)
mans_found:=$(wildcard $(sphinxbuilddir)/man/*.8)
if GENERATE_DOCS
	cp -r $(sphinxbuilddir)/html $(DESTDIR)$(docdir)
if HAVE_PDFLATEX
	${INSTALL_DATA} $(sphinxbuilddir)/latex/kea-arm.pdf $(DESTDIR)$(docdir)
	${INSTALL_DATA} $(sphinxbuilddir)/latex/kea-messages.pdf $(DESTDIR)$(docdir)
endif
	${MKDIR_P} ${DESTDIR}${mandir}/man8
	${INSTALL_DATA} $(man8s) ${DESTDIR}${mandir}/man8/
else
if INSTALL_MANS
	${MKDIR_P} ${DESTDIR}${mandir}/man8
	${INSTALL_DATA} $(mans_found) ${DESTDIR}${mandir}/man8/
endif
endif

uninstall-local:
	rm -rf $(DESTDIR)$(docdir)

# There are sometimes conflicts when more then one sphinx-build is run at a time.
# This target blocks running anything in parallel in this Makefile,
# all is run serially.

.NOTPARALLEL:
