ACLOCAL_AMFLAGS = -I m4macros ${ACLOCAL_FLAGS}
# ^^^^^^^^ This has to be the first line and cannot come later in this
# Makefile.am due to some bork in some versions of autotools.

SUBDIRS = compatcheck doc . ext src m4macros
USE_LCOV=@USE_LCOV@
LCOV=@LCOV@
GENHTML=@GENHTML@
DISTCHECK_GTEST_CONFIGURE_FLAG=@DISTCHECK_GTEST_CONFIGURE_FLAG@
DISTCHECK_CRYPTO_CONFIGURE_FLAG=@DISTCHECK_CRYPTO_CONFIGURE_FLAG@
DISTCHECK_BOOST_CONFIGURE_FLAG=@DISTCHECK_BOOST_CONFIGURE_FLAG@

DISTCLEANFILES = config.report

# When running distcheck target, do not install the configurations
DISTCHECK_CONFIGURE_FLAGS = --disable-install-configurations

# Use same --with-gtest flag if set
DISTCHECK_CONFIGURE_FLAGS += $(DISTCHECK_GTEST_CONFIGURE_FLAG)

# Keep the crypto backend config
DISTCHECK_CONFIGURE_FLAGS += $(DISTCHECK_CRYPTO_CONFIGURE_FLAG)

# Keep the Boost configuration which becomes sensible
DISTCHECK_CONFIGURE_FLAGS += $(DISTCHECK_BOOST_CONFIGURE_FLAG)

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
		rm -rf $(abs_top_srcdir)/coverage-cpp-html/; \
	else \
		echo "C++ code coverage not enabled at configuration time." ; \
		echo "Use: ./configure --with-lcov" ; \
	fi

clean-python-coverage:
	@if [ $(USE_PYCOVERAGE) = yes ] ; then \
		rm -f $(abs_top_srcdir)/.coverage ; \
		rm -rf $(abs_top_srcdir)/py-coverage-html ; \
	else \
		echo "Python code coverage not enabled at configuration time." ; \
		echo "Use: ./configure --with-pycoverage" ; \
	fi

perform-coverage: check

report-cpp-coverage:
	@if [ $(USE_LCOV) = yes ] ; then \
		$(LCOV) --capture --directory . --output-file all.info ; \
		$(LCOV) --remove all.info \
			c++/4.4\*/\* \
			c++/4.4\*/backward/\* \
			c++/4.4\*/bits/\* \
			c++/4.4\*/ext/\* \
			c++/4.4\*/\*-\*/bits/\* \
			boost/\* \
if HAVE_BOTAN
			botan/\* \
endif
			ext/coroutine/\* \
			gtest/\* \
			include/\* \
			log4cplus/\* \
if HAVE_OPENSSL
			openssl/\* \
endif
			unittests/\* \
			\*_unittests.cc \
			\*_unittest.cc \
			\*_unittests.h \
			--output report.info ; \
		sed -e "s|$(abs_top_srcdir)|$(abs_top_builddir)|g" < report.info > report.info.2 ; \
		$(GENHTML) --legend -o $(abs_top_builddir)/coverage-cpp-html report.info.2 ; \
		echo "Generated C++ Code Coverage report in HTML at $(abs_top_builddir)/coverage-cpp-html" ; \
	else \
		echo "C++ code coverage not enabled at configuration time." ; \
		echo "Use: ./configure --with-lcov" ; \
	fi

report-python-coverage:
	@if [ $(USE_PYCOVERAGE) = yes ] ; then \
		$(PYCOVERAGE) html -d $(abs_top_builddir)/coverage-python-html --omit=src/bin/bind10/tests/,src/bin/bindctl/tests/,src/bin/cfgmgr/tests/,src/bin/cmdctl/tests/,src/bin/loadzone/tests/,src/bin/msgq/tests/,src/bin/stats/tests/,src/bin/tests/,src/bin/xfrin/tests/,src/bin/xfrout/tests/,src/bin/zonemgr/tests/,src/lib/dns/python/tests/,src/lib/dns/tests/,src/lib/python/isc/cc/tests/,src/lib/python/isc/config/tests/,src/lib/python/isc/datasrc/tests/,src/lib/python/isc/log/tests/,src/lib/python/isc/net/tests/,src/lib/python/isc/notify/tests/,src/lib/python/isc/util/tests/ ; \
		echo "Generated Python Code Coverage report in HTML at $(abs_top_builddir)/coverage-python-html" ; \
	else \
		echo "Python code coverage not enabled at configuration time." ; \
		echo "Use: ./configure --with-pycoverage" ; \
	fi

# for python and c++ test coverage
coverage: clean-coverage perform-coverage report-coverage

clean-coverage: clean-cpp-coverage clean-python-coverage

report-coverage: report-cpp-coverage report-python-coverage

# for static C++ check using cppcheck (when available)
cppcheck:
	cppcheck -I./src/lib -I./src/bin --enable=all --suppressions \
		src/cppcheck-suppress.lst --inline-suppr \
		--quiet --error-exitcode=1 \
		--template '{file}:{line}: check_fail: {message} ({severity},{id})' \
		src

# These steps are necessary during installation
install-exec-hook:
	mkdir -p $(DESTDIR)${localstatedir}/log/
	mkdir -p $(DESTDIR)${localstatedir}/run/${PACKAGE_NAME}

### include tool to generate documentation from log message specifications
### in the distributed tarball:
EXTRA_DIST = tools/system_messages.py
EXTRA_DIST += tools/path_replacer.sh
EXTRA_DIST += tools/mk_cfgrpt.sh

#### include external sources in the distributed tarball:
EXTRA_DIST += ext/coroutine/coroutine.h

pkgconfigdir = $(libdir)/pkgconfig
pkgconfig_DATA = dns++.pc

CLEANFILES = $(abs_top_builddir)/logger_lockfile

# config.h may be included by headers supplied for building user-written
# hooks libraries, so we need to include it in the distribution.
pkginclude_HEADERS = config.h
