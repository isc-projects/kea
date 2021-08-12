SUBDIRS = .

yangdir = ${datarootdir}/${PACKAGE_NAME}/yang/modules/utils

yang_list  =
yang_list += check-hashes.sh
yang_list += check-revisions.sh

EXTRA_DIST = ${yang_list}

if HAVE_SYSREPO

yang_SCRIPTS = reinstall.sh

# Shell tests
SHTESTS  =
SHTESTS += check-hashes.sh
SHTESTS += check-revisions.sh

# Run shell tests on "make check".
check_SCRIPTS = $(SHTESTS)
TESTS = $(SHTESTS)

# Don't install tests.
noinst_SCRIPTS = $(SHTESTS)

endif
