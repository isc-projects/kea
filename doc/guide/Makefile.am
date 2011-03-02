EXTRA_DIST = bind10-guide.css
EXTRA_DIST += bind10-guide.html
EXTRA_DIST += bind10-guide.xml

# This is not a "man" manual, but reuse this for now for docbook.
if ENABLE_MAN

bind10-guide.html: bind10-guide.xml
	xsltproc --novalid --xinclude --nonet \
		--path $(top_builddir)/doc \
		-o $@ \
		--stringparam html.stylesheet $(srcdir)/bind10-guide.css \
		http://docbook.sourceforge.net/release/xsl/current/html/docbook.xsl \
		$(srcdir)/bind10-guide.xml

endif
