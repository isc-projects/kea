# generated documentation
HTMLDOCS = kea-guide.html kea-messages.html
DOCS = kea-guide.txt

dist_doc_DATA = $(DOCS)
dist_html_DATA = $(HTMLDOCS) kea-guide.css

DOCBOOK = kea-guide.xml intro.xml quickstart.xml install.xml config.xml
DOCBOOK += keactrl.xml dhcp4-srv.xml dhcp6-srv.xml logging.xml

EXTRA_DIST = $(DOCBOOK)
DISTCLEANFILES = $(HTMLDOCS) $(DOCS) kea-messages.xml

# This is not a "man" manual, but reuse this for now for docbook.
if GENERATE_DOCS

kea-guide.html: $(DOCBOOK)
	@XSLTPROC@ --novalid --xinclude --nonet \
		--path $(top_builddir)/doc \
		-o $@ \
		--stringparam section.autolabel 1 \
		--stringparam section.label.includes.component.label 1 \
		--stringparam html.stylesheet kea-guide.css \
		http://docbook.sourceforge.net/release/xsl/current/html/docbook.xsl \
		$(srcdir)/kea-guide.xml

kea-guide.txt: kea-guide.html
	@ELINKS@ -dump -no-numbering -no-references kea-guide.html > $@

kea-messages.html: kea-messages.xml
	@XSLTPROC@ --novalid --xinclude --nonet \
		--path $(top_builddir)/doc \
		-o $@ \
		--stringparam html.stylesheet kea-guide.css \
		http://docbook.sourceforge.net/release/xsl/current/html/docbook.xsl \
		kea-messages.xml

kea-messages.xml:
	$(PYTHON) $(top_srcdir)/tools/system_messages.py -o $@ $(top_srcdir)

else

$(HTMLDOCS) $(DOCS):
	@echo Doc generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Doc generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild BIND 10 > $@

endif
