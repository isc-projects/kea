CLEANFILES = *.wire *.copied
CLEANFILES += example-base.sqlite3 example-nsec3.sqlite3
CLEANFILES += example-common-inc.zone

BUILT_SOURCES = badExampleQuery_fromWire.wire examplequery_fromWire.wire
BUILT_SOURCES += iqueryresponse_fromWire.wire multiquestion_fromWire.wire
BUILT_SOURCES += queryBadEDNS_fromWire.wire shortanswer_fromWire.wire
BUILT_SOURCES += simplequery_fromWire.wire simpleresponse_fromWire.wire

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
EXTRA_DIST += spec.spec

EXTRA_DIST += example.com
EXTRA_DIST += example.sqlite3

EXTRA_DIST += example-base-inc.zone example-nsec3-inc.zone
EXTRA_DIST += example-common-inc-template.zone

.spec.wire:
	$(PYTHON) $(top_builddir)/src/lib/util/python/gen_wiredata.py -o $@ $<
