#
# Quick and dirty makefile
#

bind10-guide.html: bind10-guide.xml
	xsltproc --novalid --xinclude --nonet \
		-o bind10-guide.html \
		--stringparam html.stylesheet bind10-guide.css \
		http://docbook.sourceforge.net/release/xsl/current/html/docbook.xsl \
		bind10-guide.xml

clean:
	rm -f bind10-guide.html
