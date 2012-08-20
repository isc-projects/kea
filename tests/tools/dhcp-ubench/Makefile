CFLAGS=-g -O0 -Wall -pedantic -Wextra
LDFLAGS=-lrt

MEMFILE_CFLAGS=
MEMFILE_LDFLAGS=

MYSQL_CFLAGS=`mysql_config --cflags`
MYSQL_LDFLAGS=`mysql_config --libs`

SQLITE_CFLAGS=`pkg-config sqlite3 --cflags`
SQLITE_LDFLAGS=`pkg-config sqlite3 --libs`

all: mysql_ubench sqlite_ubench memfile_ubench

doc: dhcp-perf-guide.html dhcp-perf-guide.pdf

mysql_ubench.o: mysql_ubench.cc mysql_ubench.h benchmark.h
	$(CXX) $< -c $(CFLAGS) $(MYSQL_CFLAGS)

benchmark.o: benchmark.cc benchmark.h
	$(CXX) $< -c $(CFLAGS) $(MYSQL_CFLAGS)

mysql_ubench: mysql_ubench.o benchmark.o
	$(CXX) $< benchmark.o -o mysql_ubench $(CFLAGS) $(MYSQL_CFLAGS) $(LDFLAGS) $(MYSQL_LDFLAGS)

sqlite_ubench.o: sqlite_ubench.cc sqlite_ubench.h benchmark.h
	$(CXX) $< -c $(CFLAGS) $(SQLLITE_CFLAGS)

sqlite_ubench: sqlite_ubench.o benchmark.o
	$(CXX) $< benchmark.o -o sqlite_ubench $(CFLAGS) $(SQLITE_CFLAGS) $(LDFLAGS) $(SQLITE_LDFLAGS)

memfile_ubench.o: memfile_ubench.cc memfile_ubench.h benchmark.h
	$(CXX) $< -c $(CFLAGS) $(MEMFILE_CFLAGS)

memfile_ubench: memfile_ubench.o benchmark.o
	$(CXX) $< benchmark.o -o memfile_ubench $(LDFLAGS) $(MEMFILE_LDFLAGS)

clean:
	rm -f mysql_ubench sqlite_ubench memfile_ubench *.o

version.ent:
	ln -s ../../../doc/version.ent

dhcp-perf-guide.html: dhcp-perf-guide.xml version.ent
	xsltproc --novalid --xinclude --nonet \
		-o $@ \
		--path ../../../doc \
		--stringparam section.autolabel 1 \
		--stringparam section.label.includes.component.label 1 \
		--stringparam html.stylesheet bind10-guide.css \
		http://docbook.sourceforge.net/release/xsl/current/html/docbook.xsl \
		dhcp-perf-guide.xml

dhcp-perf-guide.pdf: dhcp-perf-guide.xml
	docbook2pdf $<
