ACLOCAL_AMFLAGS = -I m4macros ${ACLOCAL_FLAGS}
# ^^^^^^^^ This has to be the first line and cannot come later in this
# Makefile.am due to some bork in some versions of autotools.

# We now build doc after src/, because docgen, a tool to generate API
# documentation requires libkea-exceptions and libkea-cc.
SUBDIRS = compatcheck tools . ext src doc m4macros @PREMIUM_DIR@ @CONTRIB_DIR@

USE_LCOV=@USE_LCOV@
LCOV=@LCOV@
GENHTML=@GENHTML@
DISTCHECK_GTEST_CONFIGURE_FLAG=@DISTCHECK_GTEST_CONFIGURE_FLAG@
DISTCHECK_CRYPTO_CONFIGURE_FLAG=@DISTCHECK_CRYPTO_CONFIGURE_FLAG@
DISTCHECK_BOOST_CONFIGURE_FLAG=@DISTCHECK_BOOST_CONFIGURE_FLAG@
DISTCHECK_LOG4CPLUS_CONFIGURE_FLAG=@DISTCHECK_LOG4CPLUS_CONFIGURE_FLAG@
DISTCHECK_PERFDHCP_CONFIGURE_FLAG=@DISTCHECK_PERFDHCP_CONFIGURE_FLAG@
DISTCHECK_KEA_SHELL_CONFIGURE_FLAG=@DISTCHECK_KEA_SHELL_CONFIGURE_FLAG@
DISTCHECK_PREMIUM_CONFIGURE_FLAG=@DISTCHECK_PREMIUM_CONFIGURE_FLAG@
DISTCHECK_CONTRIB_CONFIGURE_FLAG=@DISTCHECK_CONTRIB_CONFIGURE_FLAG@
DISTCHECK_SYSREPO_CONFIGURE_FLAG=@DISTCHECK_SYSREPO_CONFIGURE_FLAG@

OVERALL_COVERAGE_DIR=$(abs_top_builddir)/coverage-cpp-html

DISTCLEANFILES = config.report

# When running distcheck target, do not install the configurations
DISTCHECK_CONFIGURE_FLAGS = --disable-install-configurations

# Use same --with-gtest flag if set
DISTCHECK_CONFIGURE_FLAGS += $(DISTCHECK_GTEST_CONFIGURE_FLAG)

# Keep the crypto backend config
DISTCHECK_CONFIGURE_FLAGS += $(DISTCHECK_CRYPTO_CONFIGURE_FLAG)

# Keep the Boost configuration which becomes sensible
DISTCHECK_CONFIGURE_FLAGS += $(DISTCHECK_BOOST_CONFIGURE_FLAG)

# Keep the log4cplus path too
DISTCHECK_CONFIGURE_FLAGS += $(DISTCHECK_LOG4CPLUS_CONFIGURE_FLAG)

# Keep perfdhcp if enabled
DISTCHECK_CONFIGURE_FLAGS += $(DISTCHECK_PERFDHCP_CONFIGURE_FLAG)

# Keep kea-shell if enabled
DISTCHECK_CONFIGURE_FLAGS += $(DISTCHECK_KEA_SHELL_CONFIGURE_FLAG)

# Keep the premium config
DISTCHECK_CONFIGURE_FLAGS += $(DISTCHECK_PREMIUM_CONFIGURE_FLAG)

# Keep the contrib config
DISTCHECK_CONFIGURE_FLAGS += $(DISTCHECK_CONTRIB_CONFIGURE_FLAG)

# keerp the sysrepo config
DISTCHECK_CONFIGURE_FLAGS += $(DISTCHECK_SYSREPO_CONFIGURE_FLAG)

dist_doc_DATA = AUTHORS COPYING ChangeLog README

.PHONY: check-valgrind check-valgrind-suppress

check-valgrind:
if HAVE_VALGRIND
	@VALGRIND_COMMAND="$(VALGRIND) -q --gen-suppressions=all --track-origins=yes --num-callers=48 --leak-check=full --fullpath-after=" \
	make -C $(abs_top_builddir) check
else
	@echo "*** Valgrind is required for check-valgrind ***"; exit 1;
endif

check-valgrind-suppress:
if HAVE_VALGRIND
	@VALGRIND_COMMAND="$(VALGRIND) -q --gen-suppressions=all --track-origins=yes --error-exitcode=1 --suppressions=$(abs_top_srcdir)/src/valgrind-suppressions --suppressions=$(abs_top_srcdir)/src/valgrind-suppressions.revisit --num-callers=48 --leak-check=full --fullpath-after=" \
	make -C $(abs_top_builddir) check
else
	@echo "*** Valgrind is required for check-valgrind-suppress ***"; exit 1;
endif

clean-cpp-coverage:
	@if [ $(USE_LCOV) = yes ] ; then \
		$(LCOV) --directory . --zerocounters; \
		rm -rf $(OVERALL_COVERAGE_DIR); \
	else \
		echo "C++ code coverage not enabled at configuration time." ; \
		echo "Use: ./configure --with-lcov" ; \
	fi

perform-coverage:
	find src -mindepth 2 -maxdepth 2 -type d | xargs -I{} bash -c "cd {}; make check || true"

report-cpp-coverage:
if HAVE_BOTAN
BOTAN_PATH=botan/\*
else
BOTAN_PATH=
endif
if HAVE_OPENSSL
OPENSSL_PATH=openssl/\*
else
OPENSSL_PATH=
endif
	@if [ $(USE_LCOV) = yes ] ; then \
		$(LCOV) --capture --directory . \
			--ignore-errors gcov,source,graph \
			--output-file all.info; \
		$(LCOV) --remove all.info \
			c++/* \
			boost/\* \
if HAVE_BOTAN
			botan/\* \
endif
			ext/coroutine/\* \
			gtest/\* \
			include/\* \
			lib/\eval/\* \
			log4cplus/\* \
			unittests/\* \
			tests/\* \
			testutils/\* \
			valgrind/\* \
			$(BOTAN_PATH) \
			$(OPENSSL_PATH) \
			--ignore-errors gcov,source,graph \
			--output report.info; \
		sed --in-place --expression "s|$(abs_top_srcdir)|$(abs_top_builddir)|g" report.info; \
		"$(GENHTML)" --frames --show-details --title 'Kea code coverage report' --legend \
                --function-coverage --ignore-errors source --demangle-cpp \
                --output "$(OVERALL_COVERAGE_DIR)" report.info; \
		printf "Generated C++ code coverage report in HTML at %s.\n" "$(OVERALL_COVERAGE_DIR)"; \
	else \
		echo "C++ code coverage not enabled at configuration time." ; \
		echo "Use: ./configure --with-lcov" ; \
	fi

# for c++ test coverage
.NOTPARALLEL: coverage

coverage: clean-coverage perform-coverage report-coverage

clean-coverage: clean-cpp-coverage

report-coverage: report-cpp-coverage

# for static C++ check using cppcheck (when available)
cppcheck:
	cppcheck -I./src/lib -I./src/bin --enable=all \
		--suppressions-list=src/cppcheck-suppress.lst --inline-suppr \
		--quiet --error-exitcode=1 \
		--template '{file}:{line}: check_fail: {message} ({severity},{id})' \
		src

# These steps are necessary during installation
install-exec-hook:
	mkdir -p $(DESTDIR)${localstatedir}/log/
	mkdir -p $(DESTDIR)${localstatedir}/run/${PACKAGE_NAME}

EXTRA_DIST  = tools/path_replacer.sh
EXTRA_DIST += tools/mk_cfgrpt.sh

#### include external sources in the distributed tarball:
EXTRA_DIST += ext/coroutine/coroutine.hpp

CLEANFILES = $(abs_top_builddir)/logger_lockfile

# config.h may be included by headers supplied for building user-written
# hooks libraries, so we need to include it in the distribution.
pkginclude_HEADERS = config.h kea_version.h
