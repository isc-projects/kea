SUBDIRS = .

if HAVE_SYSREPO

# Shell tests
SHTESTS = check-hashes.sh

# Run shell tests on "make check".
check_SCRIPTS = $(SHTESTS)
TESTS = $(SHTESTS)

# Don't install tests.
noinst_SCRIPTS = $(SHTESTS)

# Add to the tarball:
EXTRA_DIST = $(SHTESTS)

endif
