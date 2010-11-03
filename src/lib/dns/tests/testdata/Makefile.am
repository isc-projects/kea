CLEANFILES = *.wire

BUILT_SOURCES = edns_toWire1.wire edns_toWire2.wire edns_toWire3.wire
BUILT_SOURCES += edns_toWire4.wire
BUILT_SOURCES += message_fromWire10.wire message_fromWire11.wire
BUILT_SOURCES += name_toWire5.wire name_toWire6.wire
BUILT_SOURCES += rdatafields1.wire rdatafields2.wire rdatafields3.wire
BUILT_SOURCES += rdatafields4.wire rdatafields5.wire rdatafields6.wire
BUILT_SOURCES += rdata_nsec_fromWire4.wire rdata_nsec_fromWire5.wire
BUILT_SOURCES += rdata_nsec_fromWire6.wire rdata_nsec_fromWire7.wire
BUILT_SOURCES += rdata_nsec_fromWire8.wire rdata_nsec_fromWire9.wire
BUILT_SOURCES += rdata_nsec_fromWire10.wire
BUILT_SOURCES += rdata_rrsig_fromWire2.wire
BUILT_SOURCES += rdata_soa_toWireUncompressed.wire
BUILT_SOURCES +=  rdata_txt_fromWire2.wire rdata_txt_fromWire3.wire
BUILT_SOURCES += rdata_txt_fromWire4.wire rdata_txt_fromWire5.wire

# NOTE: keep this in sync with real file listing
# so is included in tarball
EXTRA_DIST = gen-wiredata.py.in
EXTRA_DIST += edns_toWire1.spec edns_toWire2.spec
EXTRA_DIST += edns_toWire3.spec edns_toWire4.spec
EXTRA_DIST += message_fromWire1 message_fromWire2
EXTRA_DIST += message_fromWire3 message_fromWire4
EXTRA_DIST += message_fromWire5 message_fromWire6
EXTRA_DIST += message_fromWire7 message_fromWire8
EXTRA_DIST += message_fromWire9 message_fromWire10.spec
EXTRA_DIST += message_fromWire11.spec
EXTRA_DIST += message_toWire1
EXTRA_DIST += name_fromWire1 name_fromWire2 name_fromWire3_1 name_fromWire3_2
EXTRA_DIST += name_fromWire4 name_fromWire6 name_fromWire7 name_fromWire8
EXTRA_DIST += name_fromWire9 name_fromWire10 name_fromWire11 name_fromWire12
EXTRA_DIST += name_fromWire13 name_fromWire14
EXTRA_DIST += name_toWire1 name_toWire2 name_toWire3 name_toWire4
EXTRA_DIST += name_toWire5.spec name_toWire6.spec
EXTRA_DIST += question_fromWire question_toWire1 question_toWire2
EXTRA_DIST += rdatafields1.spec rdatafields2.spec rdatafields3.spec
EXTRA_DIST += rdatafields4.spec rdatafields5.spec rdatafields6.spec
EXTRA_DIST += rdata_cname_fromWire rdata_dname_fromWire rdata_dnskey_fromWire
EXTRA_DIST += rdata_ds_fromWire rdata_in_a_fromWire rdata_in_aaaa_fromWire
EXTRA_DIST += rdata_mx_fromWire rdata_mx_toWire1 rdata_ns_fromWire
EXTRA_DIST += rdata_nsec3_fromWire1 rdata_nsec3_fromWire2 rdata_nsec3_fromWire3
EXTRA_DIST += rdata_nsec3param_fromWire1 rdata_nsec_fromWire1
EXTRA_DIST += rdata_nsec_fromWire2 rdata_nsec_fromWire3
EXTRA_DIST += rdata_nsec_fromWire4.spec rdata_nsec_fromWire5.spec
EXTRA_DIST += rdata_nsec_fromWire6.spec rdata_nsec_fromWire7.spec
EXTRA_DIST += rdata_nsec_fromWire8.spec rdata_nsec_fromWire9.spec
EXTRA_DIST += rdata_nsec_fromWire10.spec
EXTRA_DIST += rdata_opt_fromWire rdata_rrsig_fromWire1
EXTRA_DIST += rdata_rrsig_fromWire2.spec
EXTRA_DIST += rdata_soa_fromWire rdata_soa_toWireUncompressed.spec
EXTRA_DIST += rdata_txt_fromWire1 rdata_txt_fromWire2.spec
EXTRA_DIST += rdata_txt_fromWire3.spec rdata_txt_fromWire4.spec
EXTRA_DIST += rdata_txt_fromWire5.spec rdata_unknown_fromWire
EXTRA_DIST += rrcode16_fromWire1 rrcode16_fromWire2
EXTRA_DIST += rrcode32_fromWire1 rrcode32_fromWire2
EXTRA_DIST += rrset_toWire1 rrset_toWire2

.spec.wire:
	./gen-wiredata.py -o $@ $<
