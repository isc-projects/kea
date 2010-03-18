#
# Quick and dirty makefile
#

userguide.html: userguide.xml
	xsltproc --novalid --xinclude --nonet \
		-o userguide.html \
		--stringparam html.stylesheet userguide.css \
		http://docbook.sourceforge.net/release/xsl/current/html/docbook.xsl \
		userguide.xml

clean:
	rm -f userguide.html
