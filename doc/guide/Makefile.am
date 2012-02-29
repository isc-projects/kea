# generated documentation
DOCS = bind10-messages.html bind10-guide.html bind10-guide.txt

docdir = $(pkgdatadir)/doc/$(PACKAGE)
doc_DATA = $(DOCS) bind10-guide.css

# TODO: okay to include the generated bind10-messages.xml in dist tarfile too?
EXTRA_DIST = bind10-guide.xml bind10-messages.xml $(doc_DATA)
CLEANFILES = $(DOCS) bind10-messages.xml

# This is not a "man" manual, but reuse this for now for docbook.
if ENABLE_MAN

bind10-guide.html: bind10-guide.xml
	xsltproc --novalid --xinclude --nonet \
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
	xsltproc --novalid --xinclude --nonet \
		--path $(top_builddir)/doc \
		-o $@ \
		--stringparam html.stylesheet $(srcdir)/bind10-guide.css \
		http://docbook.sourceforge.net/release/xsl/current/html/docbook.xsl \
		bind10-messages.xml

bind10-messages.xml:
	$(PYTHON) $(top_srcdir)/tools/system_messages.py -o $@ $(top_srcdir)

endif
