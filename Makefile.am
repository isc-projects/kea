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
			c++/4.4\*/\* \
			c++/4.4\*/backward/\* \
			c++/4.4\*/bits/\* \
			c++/4.4\*/ext/\* \
			c++/4.4\*/\*-\*/bits/\* \
			boost/\* \
			gtest/\* \
			usr/include/\* \
		--output report.info
	$(GENHTML) -o coverage report.info 

coverage: clean-coverage perform-coverage report-coverage

pyshared:
	mkdir pyshared
	mkdir pyshared/isc
	cat ${srcdir}/src/lib/config/python/isc/__init__.py ${srcdir}/src/lib/cc/python/isc/__init__.py > pyshared/isc/__init__.py
	ln -s ${abs_top_srcdir}/src/lib/config/python/isc/config pyshared/isc/config
	ln -s ${abs_top_srcdir}/src/lib/cc/python/isc/cc pyshared/isc/cc
	ln -s ${abs_top_srcdir}/src/lib/cc/python/isc/Util pyshared/isc/Util

include:
	mkdir include
	ln -s ${abs_top_srcdir}/src/lib/auth/cpp include/auth
	ln -s ${abs_top_srcdir}/src/lib/cc/cpp include/cc
	ln -s ${abs_top_srcdir}/src/lib/config/cpp include/config
	ln -s ${abs_top_srcdir}/src/lib/dns/cpp include/dns
	ln -s ${abs_top_srcdir}/src/lib/exceptions/cpp include/exceptions

stree_symlinks:	pyshared include
.PHONY: stree_symlinks

all: stree_symlinks
clean-local:
	@if [ -d pyshared/isc ] ; then \
		rm -f pyshared/isc/*; \
		rmdir pyshared/isc; \
	fi
	@if [ -d pyshared ]; then \
		rmdir pyshared; \
	fi
	@if [ -d include ]; then \
		rm -f include/*; \
		rmdir include; \
	fi
