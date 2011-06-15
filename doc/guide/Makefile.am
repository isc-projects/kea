EXTRA_DIST = bind10-guide.css
EXTRA_DIST += bind10-guide.html bind10-messages.html
EXTRA_DIST += bind10-guide.xml

# This is not a "man" manual, but reuse this for now for docbook.
if ENABLE_MAN

.PHONY: bind10-messages.html

bind10-guide.html: bind10-guide.xml
	xsltproc --novalid --xinclude --nonet \
		--path $(top_builddir)/doc \
		-o $@ \
		--stringparam html.stylesheet $(srcdir)/bind10-guide.css \
		http://docbook.sourceforge.net/release/xsl/current/html/docbook.xsl \
		$(srcdir)/bind10-guide.xml

# So many dependencies that it's easiest just to regenerate it every time
bind10-messages.html:
	$(PYTHON) $(top_srcdir)/tools/system_messages.py -o $@ $(top_srcdir)

endif
