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

all: # do nothing, used only by developers manually

devel:
	mkdir -p $(builddir)/html
	(cat $(srcdir)/Doxyfile; echo PROJECT_NUMBER=$(PACKAGE_VERSION)) | doxygen - > $(builddir)/html/doxygen.log 2> $(builddir)/html/doxygen-error.log
	echo `grep -i ": warning:" $(builddir)/html/doxygen-error.log | wc -l` warnings/errors detected.

clean-local:
	rm -rf html
