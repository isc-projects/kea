EXTRA_DIST  =
EXTRA_DIST += Doxyfile Doxyfile-xml
EXTRA_DIST += bison.dox
EXTRA_DIST += config-backend.dox
EXTRA_DIST += congestion-handling.dox
EXTRA_DIST += contribute.dox
EXTRA_DIST += cross-compile.dox
EXTRA_DIST += doc.dox
EXTRA_DIST += fuzz.dox
EXTRA_DIST += mainpage.dox
EXTRA_DIST += terminology.dox
EXTRA_DIST += unit-tests.dox

EXTRA_DIST += images/assign-lease4.png
EXTRA_DIST += images/assign-lease4.svg
EXTRA_DIST += images/assign-lease4.uml
EXTRA_DIST += images/main-loop.png
EXTRA_DIST += images/main-loop.svg
EXTRA_DIST += images/main-loop.uml
EXTRA_DIST += images/packet4.png
EXTRA_DIST += images/packet4.svg
EXTRA_DIST += images/packet4.uml
EXTRA_DIST += images/request4-lease.png
EXTRA_DIST += images/request4-lease.svg
EXTRA_DIST += images/request4-lease.uml
EXTRA_DIST += images/request4.png
EXTRA_DIST += images/request4.svg
EXTRA_DIST += images/request4.uml
EXTRA_DIST += images/requestLease4.png
EXTRA_DIST += images/requestLease4.svg
EXTRA_DIST += images/requestLease4.uml
EXTRA_DIST += images/select4.png
EXTRA_DIST += images/select4.svg
EXTRA_DIST += images/select4.uml

all: # do nothing, used only by developers manually

devel:
	mkdir -p $(builddir)/html
	(cat $(srcdir)/Doxyfile; echo PROJECT_NUMBER=$(PACKAGE_VERSION)) | doxygen - > $(builddir)/html/doxygen.log 2> $(builddir)/html/doxygen-error.log
	echo `grep -i ": warning:" $(builddir)/html/doxygen-error.log | wc -l` warnings/errors detected.

clean-local:
	rm -rf html

if HAVE_PLANTUML
.uml.png:
	@PLANTUML@ $<

.uml.svg:
	@PLANTUML@ -svg $<
endif
