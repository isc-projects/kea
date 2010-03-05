bin_SCRIPTS = b10-loadzone

b10-loadzone: b10-loadzone.py
	$(SED) -e "s|@@PYTHONPATH@@|@pyexecdir@|" \
	       -e "s|@@LIBEXECDIR@@|$(pkglibexecdir)|" b10-loadzone.py >$@
	chmod a+x $@
