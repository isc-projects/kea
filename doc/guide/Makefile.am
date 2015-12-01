# generated documentation
HTMLDOCS = kea-guide.html kea-messages.html
DOCS = kea-guide.txt

dist_doc_DATA = $(DOCS)
dist_html_DATA = $(HTMLDOCS) kea-guide.css kea-logo-100x70.png

DOCBOOK = kea-guide.xml intro.xml quickstart.xml install.xml admin.xml config.xml
DOCBOOK += keactrl.xml dhcp4-srv.xml dhcp6-srv.xml lease-expiration.xml logging.xml
DOCBOOK += ddns.xml hooks.xml libdhcp.xml lfc.xml stats.xml ctrl-channel.xml faq.xml
DOCBOOK += classify.xml

EXTRA_DIST = $(DOCBOOK)

DISTCLEANFILES = $(HTMLDOCS) $(DOCS) kea-messages.xml

kea-messages.xml:
	$(top_srcdir)/tools/system_messages -o $@ \
	`find $(top_srcdir) -name "*.mes" -print`

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
		--stringparam generate.toc "book toc" \
		--stringparam html.stylesheet kea-guide.css \
		http://docbook.sourceforge.net/release/xsl/current/html/docbook.xsl \
		kea-messages.xml

else

$(HTMLDOCS) $(DOCS):
	@echo Doc generation disabled.  Creating dummy $@.  Configure with --enable-generate-docs to enable it.
	@echo Doc generation disabled.  Remove this file, configure with --enable-generate-docs, and rebuild Kea > $@

endif 

if HAVE_DBLATEX

CLEANFILES = kea-guide.pdf kea-messages.pdf

DBLATEX_FLAGS = --xslt-opts=--path --xslt-opts=$(abs_top_builddir)/doc \
	-P doc.collab.show=0 -P latex.output.revhistory=0 \
	--param=term.breakline=1

pdf: kea-guide.pdf kea-messages.pdf

kea-guide.pdf: $(DOCBOOK)
	@DBLATEX@ $(DBLATEX_FLAGS) kea-guide.xml

kea-messages.pdf: kea-messages.xml
	@DBLATEX@ $(DBLATEX_FLAGS) kea-messages.xml

else

pdf kea-guide.pdf kea-messages.pdf:
	@echo Install dblatex tool and rerun ./configure to be able to generate documentation in PDF format.

endif
