CLEANFILES = *.copied

# The following files are generated from the corresponding .spec files using
# gen-wiredata.py. Python is not a prerequisite for Kea, so it cannot be
# assumed that they can be generated when Kea is built. For this reason, they
# are part of the Kea repository and are distributed in the tarball.
EXTRA_DIST  = badExampleQuery_fromWire.wire examplequery_fromWire.wire
EXTRA_DIST += iqueryresponse_fromWire.wire multiquestion_fromWire.wire
EXTRA_DIST += queryBadEDNS_fromWire.wire shortanswer_fromWire.wire
EXTRA_DIST += simplequery_fromWire.wire simpleresponse_fromWire.wire
EXTRA_DIST += iquery_fromWire.wire iquery_response_fromWire.wire
EXTRA_DIST += nsec3query_nodnssec_fromWire.wire nsec3query_fromWire.wire

# NOTE: keep this in sync with real file listing
# so is included in tarball
EXTRA_DIST += badExampleQuery_fromWire.spec
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
EXTRA_DIST += rwtest.sqlite3	# SQLite3 DB file as a template data source

EXTRA_DIST += test1.zone.in
EXTRA_DIST += test1-new.zone.in
EXTRA_DIST += test1-broken.zone.in
EXTRA_DIST += test2.zone.in
EXTRA_DIST += test2-new.zone.in

# We no longer require gen_wiredata.py script during builds.
#.spec.wire:
#	$(PYTHON) $(top_builddir)/src/lib/util/python/gen_wiredata.py -o $@ $<
