CLEANFILES = *.wire *.copied

BUILT_SOURCES = badExampleQuery_fromWire.wire examplequery_fromWire.wire
BUILT_SOURCES += iqueryresponse_fromWire.wire multiquestion_fromWire.wire
BUILT_SOURCES += queryBadEDNS_fromWire.wire shortanswer_fromWire.wire
BUILT_SOURCES += simplequery_fromWire.wire simpleresponse_fromWire.wire
BUILT_SOURCES += iquery_fromWire.wire iquery_response_fromWire.wire
BUILT_SOURCES += nsec3query_nodnssec_fromWire.wire nsec3query_fromWire.wire

# NOTE: keep this in sync with real file listing
# so is included in tarball
EXTRA_DIST = badExampleQuery_fromWire.spec
EXTRA_DIST += examplequery_fromWire.spec
EXTRA_DIST += iqueryresponse_fromWire.spec
EXTRA_DIST += multiquestion_fromWire.spec
EXTRA_DIST += queryBadEDNS_fromWire.spec
EXTRA_DIST += shortanswer_fromWire.spec
EXTRA_DIST += shortmessage_fromWire
EXTRA_DIST += shortquestion_fromWire
EXTRA_DIST += shortresponse_fromWire
EXTRA_DIST += simplequery_fromWire.spec
EXTRA_DIST += simpleresponse_fromWire.spec
EXTRA_DIST += nsec3query_nodnssec_fromWire.spec nsec3query_fromWire.spec
EXTRA_DIST += iquery_fromWire.spec iquery_response_fromWire.spec
EXTRA_DIST += example.com.zone example.net.zone example.org.zone example.zone
EXTRA_DIST += rfc5155-example.zone.signed

EXTRA_DIST += example.com
EXTRA_DIST += example.sqlite3

EXTRA_DIST += test1.zone.in
EXTRA_DIST += test1-new.zone.in
EXTRA_DIST += test1-broken.zone.in
EXTRA_DIST += test2.zone.in
EXTRA_DIST += test2-new.zone.in

.spec.wire:
	$(PYTHON) $(top_builddir)/src/lib/util/python/gen_wiredata.py -o $@ $<
