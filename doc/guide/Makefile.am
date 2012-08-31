# generated documentation
HTMLDOCS = bind10-guide.html bind10-messages.html
DOCS = bind10-guide.txt

dist_doc_DATA = $(DOCS)
dist_html_DATA = $(HTMLDOCS) bind10-guide.css

EXTRA_DIST = bind10-guide.xml
CLEANFILES = $(HTMLDOCS) $(DOCS) bind10-messages.xml

# This is not a "man" manual, but reuse this for now for docbook.
if GENERATE_DOCS

bind10-guide.html: bind10-guide.xml
	@XSLTPROC@ --novalid --xinclude --nonet \
		--path $(top_builddir)/doc \
		-o $@ \
		--stringparam section.autolabel 1 \
		--stringparam section.label.includes.component.label 1 \
		--stringparam html.stylesheet $(srcdir)/bind10-guide.css \
		http://docbook.sourceforge.net/release/xsl/current/html/docbook.xsl \
		$(srcdir)/bind10-guide.xml

HTML2TXT = elinks -dump -no-numbering -no-references

bind10-guide.txt: bind10-guide.html
	$(HTML2TXT) bind10-guide.html > $@

bind10-messages.html: bind10-messages.xml
	@XSLTPROC@ --novalid --xinclude --nonet \
		--path $(top_builddir)/doc \
		-o $@ \
		--stringparam html.stylesheet $(srcdir)/bind10-guide.css \
		http://docbook.sourceforge.net/release/xsl/current/html/docbook.xsl \
		bind10-messages.xml

bind10-messages.xml:
	$(PYTHON) $(top_srcdir)/tools/system_messages.py -o $@ $(top_srcdir)

else

$(HTMLDOCS) $(DOCS):
	@echo Doc generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Doc generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild BIND 10 > $@

endif
