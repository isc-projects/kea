EXTRA_DIST =
sphinxbuilddir = $(builddir)/_build
abs_sphinxbuilddir = $(abs_builddir)/_build

if GENERATE_DOCS

sphinxopts =
sphinxopts += -v
sphinxopts += -E
sphinxopts += -a
sphinxopts += -W
sphinxopts += -c "${abs_srcdir}"

static_sources  =
static_sources += static/kea-imageonly-100bw.png
static_sources += static/kea-logo-100x70.png
static_sources += static/kea-logo-200.png
static_sources += static/kea.css

# ARM
rst_arm_sources =
rst_arm_sources += index.rst
rst_arm_sources += manpages.rst
rst_arm_sources += umls.rst
include arm/rst_arm_sources.mk

EXTRA_DIST += arm/rst_arm_sources.mk

main_sources = $(rst_arm_sources) conf.py $(static_sources)

# mans
rst_man_sources =
include man/rst_man_sources.mk

EXTRA_DIST += man/rst_man_sources.mk

rst_arm_sources += grammar/grammar.rst
rst_arm_sources += grammar/grammar-ca-parser.rst
rst_arm_sources += grammar/grammar-d2-parser.rst
rst_arm_sources += grammar/grammar-dhcp4-parser.rst
rst_arm_sources += grammar/grammar-dhcp6-parser.rst
rst_arm_sources += grammar/grammar-netconf-parser.rst

man8s =
include man/man8s.mk

EXTRA_DIST += man/man8s.mk

man_sources = $(rst_man_sources) conf.py

EXTRA_DIST += $(main_sources) $(man_sources) mes2doc.py api2doc.py $(man8s)

# list of messages files that are used to generate kea-messages.rst and then kea-messages.pdf
mes_files =
include $(srcdir)/mes_files.mk

EXTRA_DIST += mes_files.mk

# list of api files that are used to generate api.rst
api_files =
include $(top_srcdir)/src/share/api/api_files.mk

if HAVE_PDFLATEX
all: html mans pdf text
else
all: html mans text
endif

# build the list of message files
mes-files.txt: mes_files.mk
	@sed 's;mes_files .*)/;;' $< > $@

# this rule is only used for development purposes and is not used in official
# build process as kea-messages.rst is always generated via sphinx's conf.py
$(srcdir)/kea-messages.rst: $(mes_files) mes2doc.py
	$(PYTHON) $(srcdir)/mes2doc.py -o $@ $(mes_files)

# build the list of api files
api-files.txt: $(top_srcdir)/src/share/api/api_files.mk
	@sed 's;api_files .*)/;;' $< > $@

# some tools do not use this makefile but still need generate files.
EXTRA_DIST += mes-files.txt api-files.txt

# this rule is only used for development purposes and is not used in official
# build process as api.rst is always generated via sphinx's conf.py
$(srcdir)/api.rst: $(api_files) api-files.txt api2doc.py
	$(PYTHON) $(srcdir)/api2doc.py -o $@ $(api_files)

$(srcdir)/arm/platforms.rst:
	rm -f $(srcdir)/arm/platforms.rst
	cp $(srcdir)/../../platforms.rst $(srcdir)/arm/platforms.rst

# UML files

umls  =
umls += uml/appendRequestedOptions.uml
umls += uml/appendRequestedVendorOptions.uml
umls += uml/assign-lease4.uml
umls += uml/buildCfgOptionList.uml
umls += uml/currentHost4.uml
umls += uml/lease-states.uml
umls += uml/main-loop.uml
umls += uml/packet4.uml
umls += uml/radius.uml
umls += uml/recognizing-same-client.uml
umls += uml/request4-lease.uml
umls += uml/request4.uml
umls += uml/requestLease4.uml
umls += uml/select4.uml
umls += uml/tkey.uml
umls += uml/update.uml

pngs  =
pngs += uml/appendRequestedOptions.png
pngs += uml/appendRequestedVendorOptions.png
pngs += uml/assign-lease4.png
pngs += uml/buildCfgOptionList.png
pngs += uml/currentHost4.png
pngs += uml/lease-states.png
pngs += uml/main-loop.png
pngs += uml/packet4.png
pngs += uml/radius.png
pngs += uml/recognizing-same-client.png
pngs += uml/request4-lease.png
pngs += uml/request4.png
pngs += uml/requestLease4.png
pngs += uml/select4.png
pngs += uml/tkey.png
pngs += uml/update.png

svgs  =
svgs += uml/appendRequestedOptions.svg
svgs += uml/appendRequestedVendorOptions.svg
svgs += uml/assign-lease4.svg
svgs += uml/buildCfgOptionList.svg
svgs += uml/currentHost4.svg
svgs += uml/lease-states.svg
svgs += uml/main-loop.svg
svgs += uml/packet4.svg
svgs += uml/radius.svg
svgs += uml/recognizing-same-client.svg
svgs += uml/request4-lease.svg
svgs += uml/request4.svg
svgs += uml/requestLease4.svg
svgs += uml/select4.svg
svgs += uml/tkey.svg
svgs += uml/update.svg

txts  =
txts += uml/option-data-priority.atxt
txts += uml/priority-of-lease-lifetimes-and-dhcpv4-fields.atxt
txts += uml/tkey.atxt
txts += uml/update.atxt

if HAVE_PLANTUML
uml: uml-to-png uml-to-svg format-svgs uml-to-txt

uml-to-png: $(umls)
	@ @PLANTUML@ -tpng $^

uml-to-svg: $(umls)
	@ @PLANTUML@ -tsvg $^

# Formatting puts every tag on a separate line, which makes it easier for diffing.
format-svgs: $(svgs)
if HAVE_XMLLINT
	@ for svg in $(svgs); do xmllint --format $$svg > tmp; mv tmp $$svg; done
else
	@ printf 'WARNING: xmllint not found. SVGs not formatted.\n'
endif

# Only sequence diagrams support ASCII art.
uml-to-txt: uml/tkey.uml uml/update.uml
	@ @PLANTUML@ -ttxt $^
	@ for txt in $(txts); do sed 's/ *$$//g' $$txt > tmp; mv tmp $$txt; done
endif

EXTRA_DIST += $(umls)
EXTRA_DIST += $(pngs)
EXTRA_DIST += $(svgs)
EXTRA_DIST += $(txts)

PDFLATEX_AND_OPTS=$(PDFLATEX) -interaction nonstopmode

pdf: $(main_sources) api-files.txt mes-files.txt $(srcdir)/arm/platforms.rst
	$(SPHINXBUILD) -M latex $(srcdir) $(sphinxbuilddir) $(sphinxopts)
	cd $(abs_sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-arm.tex
	cd $(abs_sphinxbuilddir)/latex && makeindex -s python.ist kea-arm.idx
	cd $(abs_sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-arm.tex
	cd $(abs_sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-messages.tex
	cd $(abs_sphinxbuilddir)/latex && makeindex -s python.ist kea-messages.idx
	cd $(abs_sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-messages.tex

html: $(main_sources) api-files.txt mes-files.txt $(srcdir)/arm/platforms.rst
	$(SPHINXBUILD) -M html $(srcdir) $(sphinxbuilddir) $(sphinxopts)

# This target is not used anywhere, but people who prefer single page docs
# can do make -C doc/sphinx singlehtml and then enjoy their docs being
# generated in doc/sphinx/_build/singlehtml
singlehtml: $(main_sources) api-files.txt mes-files.txt $(srcdir)/arm/platforms.rst
	$(SPHINXBUILD) -M singlehtml $(srcdir) $(sphinxbuilddir) $(sphinxopts)

text: $(main_sources) api-files.txt mes-files.txt $(srcdir)/arm/platforms.rst
	$(SPHINXBUILD) -M text $(srcdir) $(sphinxbuilddir) $(sphinxopts)

$(man8s): mans

mans: $(man_sources) api-files.txt mes-files.txt
	$(SPHINXBUILD) -M man $(srcdir) $(sphinxbuilddir) $(sphinxopts)

# Updates sphinx dependencies to the latest versions available on the current
# host and freezes them in ./src/requirements.txt. Requires pip-compile:
#   pip install pip-tools
# Run this when dependencies are added, changed or removed.
update-python-dependencies: ./src/requirements.in
	rm ./src/requirements.txt
	pip-compile -r ./src/requirements.in

clean-local:
	rm -rf $(sphinxbuilddir)
	rm -f $(srcdir)/mes-files.txt $(srcdir)/api-files.txt
	rm -f $(srcdir)/kea-messages.rst $(srcdir)/api.rst
	rm -f $(srcdir)/arm/platforms.rst

.PHONY: all pdf html mans update-python-dependencies uml uml-to-png uml-to-svg format-svgs uml-to-txt

endif

# install and uninstall can occur with GENERATE_DOCS and without it
# so we want to install all when GENERATE_DOCS is and
# just mans when GENERATE_DOCS is not used, and when man files exists (e.g release tarball)
install-data-local:
	mkdir -p $(DESTDIR)$(docdir)
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
	${INSTALL_DATA} $(sphinxbuilddir)/man/*.8 ${DESTDIR}${mandir}/man8/
endif
endif

uninstall-local:
	rm -rf $(DESTDIR)$(docdir)

# There are sometimes conflicts when more then one sphinx-build is run at a time.
# This target blocks running anything in parallel in this Makefile,
# all is run serially.

.NOTPARALLEL:
