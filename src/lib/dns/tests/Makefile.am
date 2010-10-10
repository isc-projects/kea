SUBDIRS = testdata .

AM_CPPFLAGS = -I$(top_builddir)/src/lib -I$(top_srcdir)/src/lib
AM_CPPFLAGS += $(BOOST_INCLUDES)
AM_CPPFLAGS += -I$(top_srcdir)/src/lib/dns -I$(top_builddir)/src/lib/dns
AM_CPPFLAGS += -DTEST_DATA_SRCDIR=\"$(srcdir)/testdata\"
AM_CPPFLAGS += -DTEST_DATA_BUILDDIR=\"$(top_builddir)/src/lib/dns/tests/testdata\"
AM_CXXFLAGS = $(B10_CXXFLAGS)

if USE_STATIC_LINK
AM_LDFLAGS = -static
endif

CLEANFILES = *.gcno *.gcda

TESTS =
if HAVE_GTEST
TESTS += run_unittests
run_unittests_SOURCES = unittest_util.h unittest_util.cc
run_unittests_SOURCES += buffer_unittest.cc name_unittest.cc
run_unittests_SOURCES += edns_unittest.cc
run_unittests_SOURCES += messagerenderer_unittest.cc
run_unittests_SOURCES += rrclass_unittest.cc rrtype_unittest.cc
run_unittests_SOURCES += rrttl_unittest.cc
run_unittests_SOURCES += dnssectime_unittest.cc
run_unittests_SOURCES += opcode_unittest.cc
run_unittests_SOURCES += rcode_unittest.cc
run_unittests_SOURCES += rdata_unittest.h rdata_unittest.cc
run_unittests_SOURCES += rdata_in_a_unittest.cc rdata_in_aaaa_unittest.cc
run_unittests_SOURCES += rdata_ns_unittest.cc rdata_soa_unittest.cc
run_unittests_SOURCES += rdata_txt_unittest.cc rdata_mx_unittest.cc
run_unittests_SOURCES += rdata_ptr_unittest.cc rdata_cname_unittest.cc
run_unittests_SOURCES += rdata_dname_unittest.cc
run_unittests_SOURCES += rdata_opt_unittest.cc
run_unittests_SOURCES += rdata_dnskey_unittest.cc
run_unittests_SOURCES += rdata_ds_unittest.cc
run_unittests_SOURCES += rdata_nsec_unittest.cc
run_unittests_SOURCES += rdata_nsec3_unittest.cc
run_unittests_SOURCES += rdata_nsec3param_unittest.cc
run_unittests_SOURCES += rdata_rrsig_unittest.cc
run_unittests_SOURCES += rrset_unittest.cc rrsetlist_unittest.cc
run_unittests_SOURCES += question_unittest.cc
run_unittests_SOURCES += rrparamregistry_unittest.cc
run_unittests_SOURCES += message_unittest.cc
run_unittests_SOURCES += base32hex_unittest.cc
run_unittests_SOURCES += base64_unittest.cc
run_unittests_SOURCES += hex_unittest.cc
run_unittests_SOURCES += sha1_unittest.cc
run_unittests_SOURCES += tsig_unittest.cc
run_unittests_SOURCES += run_unittests.cc
run_unittests_CPPFLAGS = $(AM_CPPFLAGS) $(GTEST_INCLUDES)
run_unittests_LDFLAGS = $(AM_LDFLAGS) $(GTEST_LDFLAGS)
run_unittests_LDADD = $(GTEST_LDADD)
run_unittests_LDADD += $(top_builddir)/src/lib/dns/libdns++.la
run_unittests_LDADD += $(top_builddir)/src/lib/exceptions/libexceptions.la
endif

noinst_PROGRAMS = $(TESTS)
