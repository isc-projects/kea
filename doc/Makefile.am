SUBDIRS = guide

EXTRA_DIST = version.ent.in

devel:
	mkdir -p html
	doxygen Doxyfile > html/doxygen.log 2> html/doxygen-error.log
	echo "`wc -l html/doxygen-error.log` warnings/errors detected."

# That's a bit of a hack, but we are making sure that devel target
# is always valid. The alternative is to make devel depend on all
# *.cc *.h files in the whole tree.
.PHONY: devel
