SUBDIRS = .

yangdir = ${datarootdir}/${PACKAGE_NAME}/yang/modules/utils

yang_list  =
yang_list += check-hashes.sh
yang_list += check-revisions.sh

EXTRA_DIST = ${yang_list}

if HAVE_NETCONF

yang_SCRIPTS = reinstall.sh

# Shell tests
SHTESTS  =
SHTESTS += check-hashes.sh
SHTESTS += check-revisions.sh

if HAVE_GTEST

# Run shell tests on "make check".
check_SCRIPTS = $(SHTESTS)
TESTS = $(SHTESTS)

endif

# Don't install shell tests.
noinst_SCRIPTS = $(SHTESTS)

endif
