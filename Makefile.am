SUBDIRS = src
USE_LCOV=@USE_LCOV@
LCOV=@LCOV@
GENHTML=@GENHTML@

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
			c++/4.4/\* \
			boost/\* \
			gtest/\* \
			usr/include/\* \
		--output report.info
	$(GENHTML) -o coverage report.info 

coverage: clean-coverage perform-coverage report-coverage

