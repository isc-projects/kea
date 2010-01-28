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
	ln -s ${abs_top_srcdir}/src/lib/config/python/isc/config pyshared/isc/config
	ln -s ${abs_top_srcdir}/src/lib/cc/python/ISC/CC pyshared/isc/cc

include:
	mkdir include
	ln -s ${abs_top_srcdir}/src/lib/cc/cpp include/cc
	ln -s ${abs_top_srcdir}/src/lib/config/cpp include/config
	ln -s ${abs_top_srcdir}/src/lib/dns/cpp include/dns

stree_symlinks:	pyshared include
.PHONY: stree_symlinks

all: stree_symlinks
clean-local:
	rm pyshared/isc/config
	rm pyshared/isc/cc
	rmdir pyshared/isc
	rmdir pyshared
	rm include/cc
	rm include/config
	rm include/dns
	rmdir include
