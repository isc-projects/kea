SUBDIRS = . asio
if HAVE_GTEST_SOURCE
SUBDIRS += gtest
endif

# As we are copying ASIO headers to the installation directory, copy across
# the licence file as well.
asio_datadir = $(pkgincludedir)/asio
asio_data_DATA = LICENSE_1_0.txt

EXTRA_DIST = LICENSE_1_0.txt
