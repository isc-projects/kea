SUBDIRS = isc

python_PYTHON =	bind10_config.py

# Explicitly define DIST_COMMON so ${python_PYTHON} is not included
# as we don't want the generated file included in distributed tarfile.
DIST_COMMON = $(srcdir)/Makefile.am $(srcdir)/Makefile.in bind10_config.py.in

# When setting DIST_COMMON, then need to add the .in file too.
EXTRA_DIST =  bind10_config.py.in
