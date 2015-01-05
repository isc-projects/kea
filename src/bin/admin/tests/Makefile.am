SUBDIRS = .

SHTESTS = memfile_tests.sh

if HAVE_MYSQL
SHTESTS += mysql_tests.sh
endif

noinst_SCRIPTS = $(SHTESTS)

CLEANFILES = *.log
DISTCLEANFILES = memfile_tests.sh mysql_tests.sh

# Execute all test scripts.
check-local:
	for shtest in $(SHTESTS) ; do \
	echo Running test: $$shtest ; \
	chmod +x $(abs_builddir)/$$shtest ; \
	${SHELL} $(abs_builddir)/$$shtest || exit ; \
	done
