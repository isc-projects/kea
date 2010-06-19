SUBDIRS = src
USE_LCOV=@USE_LCOV@
LCOV=@LCOV@
GENHTML=@GENHTML@

DISTCLEANFILES = config.report

# When running distcheck target, do not install the configurations
DISTCHECK_CONFIGURE_FLAGS = --disable-install-configurations

clean-coverage:
	@if [ $(USE_LCOV) = yes ] ; then \
		$(LCOV) --directory . --zerocounters; \
		rm -rf coverage/; \
	else \
		echo "Code coverage not enabled at configuration time"; \
		exit 1; \
	fi

perform-coverage: check

report-coverage:
	$(LCOV) --capture --directory . --output-file all.info
	$(LCOV) --remove all.info \
			c++/4.4\*/\* \
			c++/4.4\*/backward/\* \
			c++/4.4\*/bits/\* \
			c++/4.4\*/ext/\* \
			c++/4.4\*/\*-\*/bits/\* \
			boost/\* \
			gtest/\* \
			usr/include/\* \
			tests/\* \
			unittests/\* \
			\*_unittests.cc \
			\*_unittest.cc \
			\*_unittests.h \
		--output report.info
	$(GENHTML) -o coverage report.info 

coverage: clean-coverage perform-coverage report-coverage
