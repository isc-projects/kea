EXTRA_DIST =
sphinxbuilddir = $(builddir)/_build
abs_sphinxbuilddir = $(abs_builddir)/_build

if GENERATE_DOCS

sphinxopts =
sphinxopts += -v
sphinxopts += -E
sphinxopts += -a
sphinxopts += -W
sphinxopts += -j 2
sphinxopts += -c "${abs_srcdir}"

static_sources =
include static/static_sources.mk

EXTRA_DIST += static/static_sources.mk

# ARM
rst_arm_sources =
rst_arm_sources += index.rst
rst_arm_sources += manpages.rst
include arm/rst_arm_sources.mk

EXTRA_DIST += arm/rst_arm_sources.mk

main_sources = $(rst_arm_sources) conf.py $(static_sources)

# mans
rst_man_sources =
include man/rst_man_sources.mk

EXTRA_DIST += man/rst_man_sources.mk

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
include $(srcdir)/api/api_files.mk

EXTRA_DIST += api/api_files.mk
EXTRA_DIST += api/README
EXTRA_DIST += api/_template.json
EXTRA_DIST += api/generate-templates
EXTRA_DIST += api/cmds-list
EXTRA_DIST += $(api_files)

if HAVE_PDFLATEX
all: html mans pdf
else
all: html mans
endif

# build the list of message files
mes-files.txt: mes_files.mk
	@sed 's;mes_files .*)/;;' $< > $@

# this rule is only used for development purposes and is not used in official
# build process as kea-messages.rst is always generated via sphinx's conf.py
$(srcdir)/kea-messages.rst: $(mes_files) mes2doc.py
	$(PYTHON) $(srcdir)/mes2doc.py -o $@ $(mes_files)

# build the list of api files
api-files.txt: api/api_files.mk
	@sed 's;_files .*%/;/;' $< > $@

# this rule is only used for development purposes and is not used in official
# build process as api.rst is always generated via sphinx's conf.py
$(srcdir)/api.rst: $(api_files) api-files.txt api2doc.py
	$(PYTHON) $(srcdir)/api2doc.py -o $@ $(api_files)

$(srcdir)/arm/platforms.rst:
	rm -f $(srcdir)/arm/platforms.rst
	cp $(srcdir)/../../platforms.rst $(srcdir)/arm/platforms.rst

PDFLATEX_AND_OPTS=$(PDFLATEX) -interaction nonstopmode

pdf: $(main_sources) api-files.txt mes-files.txt $(srcdir)/arm/platforms.rst
	$(SPHINXBUILD) -M latex $(srcdir) $(sphinxbuilddir) $(sphinxopts)
	-cd $(abs_sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-arm.tex
	-cd $(abs_sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-arm.tex
	-cd $(abs_sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-arm.tex
	-cd $(abs_sphinxbuilddir)/latex && makeindex -s python.ist kea-arm.idx
	-cd $(abs_sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-arm.tex
	cd $(abs_sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-arm.tex
	-cd $(abs_sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-messages.tex
	-cd $(abs_sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-messages.tex
	-cd $(abs_sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-messages.tex
	-cd $(abs_sphinxbuilddir)/latex && makeindex -s python.ist kea-messages.idx
	-cd $(abs_sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-messages.tex
	cd $(abs_sphinxbuilddir)/latex && $(PDFLATEX_AND_OPTS) kea-messages.tex

html: $(main_sources) api-files.txt mes-files.txt $(srcdir)/arm/platforms.rst
	$(SPHINXBUILD) -M html $(srcdir) $(sphinxbuilddir) $(sphinxopts)

# This target is not used anywhere, but people who prefer single page docs
# can do make -C doc/sphinx singlehtml and then enjoy their docs being
# generated in doc/sphinx/_build/singlehtml
singlehtml: $(main_sources) api-files.txt mes-files.txt $(srcdir)/arm/platforms.rst
	$(SPHINXBUILD) -M singlehtml $(srcdir) $(sphinxbuilddir) $(sphinxopts)

$(man8s): mans

mans: $(man_sources) api-files.txt mes-files.txt
	$(SPHINXBUILD) -M man $(srcdir) $(sphinxbuilddir) $(sphinxopts)

clean-local:
	rm -rf $(sphinxbuilddir)
	rm -f $(srcdir)/mes-files.txt $(srcdir)/api-files.txt
	rm -f $(srcdir)/kea-messages.rst $(srcdir)/api.rst
	rm -f $(srcdir)/arm/platforms.rst

.PHONY: all pdf html mans

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
