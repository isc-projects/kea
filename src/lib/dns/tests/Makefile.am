SUBDIRS = testdata .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -DTEST_DATA_SRCDIR=\"$(abs_top_srcdir)/src/lib/dns/tests/testdata\"
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(abs_top_builddir)/src/lib/dns/tests/testdata\"
AM_CXXFLAGS = $(KEA_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS_ENVIRONMENT = \
	$(LIBTOOL) --mode=execute $(VALGRIND_COMMAND)

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = unittest_util.h unittest_util.cc
run_unittests_SOURCES += dns_exceptions_unittest.cc
run_unittests_SOURCES += edns_unittest.cc
run_unittests_SOURCES += master_lexer_inputsource_unittest.cc
run_unittests_SOURCES += labelsequence_unittest.cc
run_unittests_SOURCES += messagerenderer_unittest.cc
run_unittests_SOURCES += master_lexer_token_unittest.cc
run_unittests_SOURCES += master_lexer_unittest.cc
run_unittests_SOURCES += master_loader_unittest.cc
run_unittests_SOURCES += master_lexer_state_unittest.cc
run_unittests_SOURCES += name_unittest.cc
run_unittests_SOURCES += nsec3hash_unittest.cc
run_unittests_SOURCES += rrclass_unittest.cc rrtype_unittest.cc
run_unittests_SOURCES += rrttl_unittest.cc
run_unittests_SOURCES += rrcollator_unittest.cc
run_unittests_SOURCES += opcode_unittest.cc
run_unittests_SOURCES += rcode_unittest.cc
run_unittests_SOURCES += rdata_unittest.h rdata_unittest.cc
run_unittests_SOURCES += rdatafields_unittest.cc
run_unittests_SOURCES += rdata_pimpl_holder_unittest.cc
run_unittests_SOURCES += rdata_char_string_unittest.cc
run_unittests_SOURCES += rdata_char_string_data_unittest.cc
run_unittests_SOURCES += rdata_in_a_unittest.cc rdata_in_aaaa_unittest.cc
run_unittests_SOURCES += rdata_ns_unittest.cc rdata_soa_unittest.cc
run_unittests_SOURCES += rdata_txt_like_unittest.cc
run_unittests_SOURCES += rdata_mx_unittest.cc
run_unittests_SOURCES += rdata_sshfp_unittest.cc
run_unittests_SOURCES += rdata_ptr_unittest.cc rdata_cname_unittest.cc
run_unittests_SOURCES += rdata_dname_unittest.cc
run_unittests_SOURCES += rdata_afsdb_unittest.cc
run_unittests_SOURCES += rdata_opt_unittest.cc
run_unittests_SOURCES += rdata_dhcid_unittest.cc
run_unittests_SOURCES += rdata_dnskey_unittest.cc
run_unittests_SOURCES += rdata_ds_like_unittest.cc
run_unittests_SOURCES += rdata_nsec_unittest.cc
run_unittests_SOURCES += rdata_nsec3_unittest.cc
run_unittests_SOURCES += rdata_nsecbitmap_unittest.cc
run_unittests_SOURCES += rdata_nsec3param_unittest.cc
run_unittests_SOURCES += rdata_nsec3param_like_unittest.cc
run_unittests_SOURCES += rdata_rrsig_unittest.cc
run_unittests_SOURCES += rdata_rp_unittest.cc
run_unittests_SOURCES += rdata_srv_unittest.cc
run_unittests_SOURCES += rdata_tlsa_unittest.cc
run_unittests_SOURCES += rdata_minfo_unittest.cc
run_unittests_SOURCES += rdata_tsig_unittest.cc
run_unittests_SOURCES += rdata_naptr_unittest.cc
run_unittests_SOURCES += rdata_hinfo_unittest.cc
run_unittests_SOURCES += rdata_caa_unittest.cc
run_unittests_SOURCES += rrset_unittest.cc
run_unittests_SOURCES += question_unittest.cc
run_unittests_SOURCES += rrparamregistry_unittest.cc
run_unittests_SOURCES += masterload_unittest.cc
run_unittests_SOURCES += message_unittest.cc
run_unittests_SOURCES += serial_unittest.cc
run_unittests_SOURCES += tsig_unittest.cc
run_unittests_SOURCES += tsigerror_unittest.cc
run_unittests_SOURCES += tsigkey_unittest.cc
run_unittests_SOURCES += tsigrecord_unittest.cc
run_unittests_SOURCES += master_loader_callbacks_test.cc
run_unittests_SOURCES += rrset_collection_unittest.cc
run_unittests_SOURCES += zone_checker_unittest.cc
run_unittests_SOURCES += run_unittests.cc
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(CRYPTO_LDFLAGS) $(GTEST_LDFLAGS)
run_unittests_LDADD = $(top_builddir)/src/lib/dns/libkea-dns++.la
run_unittests_LDADD += $(top_builddir)/src/lib/cryptolink/libkea-cryptolink.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/unittests/libutil_unittests.la
run_unittests_LDADD += $(top_builddir)/src/lib/util/libkea-util.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libkea-exceptions.la
run_unittests_LDADD += $(CRYPTO_LIBS) $(GTEST_LDADD)
endif

noinst_PROGRAMS = $(TESTS)
