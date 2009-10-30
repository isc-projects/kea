// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

// $Id$

#include <dns/buffer.h>
#include <dns/rrset.h>

#include <gtest/gtest.h>

namespace {

using isc::dns::Name;
using isc::dns::RRClass;
using isc::dns::RRType;
using isc::dns::TTL;
using isc::dns::Rdata::RdataPtr;
using isc::dns::Rdata::Rdata;
using isc::dns::Rdata::IN::A;
using isc::dns::Rdata::IN::AAAA;
using isc::dns::Rdata::Generic::NS;
using isc::dns::Rdata::Generic::SOA;
using isc::dns::Rdata::Generic::TXT;
using isc::dns::RRset;
using isc::dns::RR;
using isc::dns::Question;

// The fixture for testing class RRClass.
class RRClassTest : public ::testing::Test {
protected:
    RRClassTest() : rrclass_in("IN"), rrclass_ch("CH") {}
    RRClass rrclass_in;
    RRClass rrclass_ch;
};

TEST_F(RRClassTest, fromToText)
{
    EXPECT_EQ("IN", rrclass_in.toText());
    EXPECT_EQ("CH", rrclass_ch.toText());
}

// The fixture for testing class RRType.
class RRTypeTest : public ::testing::Test {
protected:
    RRTypeTest() :
        rrtype_a("A"), rrtype_aaaa("AAAA"), rrtype_ns("NS"), rrtype_txt("TXT")
    {}
    RRType rrtype_a;
    RRType rrtype_aaaa;
    RRType rrtype_ns;
    RRType rrtype_txt;
};

TEST_F(RRTypeTest, fromToText)
{
    EXPECT_EQ("A", rrtype_a.toText());
    EXPECT_EQ("AAAA", rrtype_aaaa.toText());
    EXPECT_EQ("NS", rrtype_ns.toText());
    EXPECT_EQ("TXT", rrtype_txt.toText());
}

// The fixture for testing class TTL.
class TTLTest : public ::testing::Test {
protected:
    TTLTest() : ttl3600(3600), ttl0(0) {}
    TTL ttl3600;
    TTL ttl0;
};

TEST_F(TTLTest, toText)
{
    EXPECT_EQ("3600", ttl3600.toText());
    EXPECT_EQ("0", ttl0.toText());
}

TEST_F(TTLTest, getValue)
{
    EXPECT_EQ(3600, ttl3600.getValue());
    EXPECT_EQ(0, ttl0.getValue());
}

// The fixture for testing generic Rdata class
class RdataTest : public ::testing::Test {
protected:
    RdataTest() {}
};

TEST_F(RdataTest, fromToText)
{
    EXPECT_EQ("192.0.2.1",
              Rdata::fromText(RRClass::IN, RRType::A, "192.0.2.1")->toText());
}

// The fixture for testing class IN/A Rdata
class Rdata_IN_A_Test : public ::testing::Test {
protected:
    Rdata_IN_A_Test() : rdata("192.0.2.1") {}
    A rdata;
};

TEST_F(Rdata_IN_A_Test, fromToText)
{
    EXPECT_EQ("192.0.2.1", rdata.toText());
    EXPECT_THROW(A("2001:db8::1234"), isc::ISCInvalidAddressString);
}

// The fixture for testing IN/AAAA Rdata class
class Rdata_IN_AAAA_Test : public ::testing::Test {
protected:
    Rdata_IN_AAAA_Test() : rdata("2001:db8::abcd") {}
    AAAA rdata;
};

TEST_F(Rdata_IN_AAAA_Test, fromToText)
{
    EXPECT_EQ("2001:db8::abcd", rdata.toText());
    EXPECT_THROW(AAAA("192.0.2.255"), isc::ISCInvalidAddressString);
}

// The fixture for testing class Generic/NS Rdata
class Rdata_Generic_NS_Test : public ::testing::Test {
protected:
    Rdata_Generic_NS_Test() : rdata("ns.example.com") {}
    NS rdata;
};

TEST_F(Rdata_Generic_NS_Test, fromToText)
{
    EXPECT_EQ("ns.example.com.", rdata.toText());
}

// The fixture for testing class Generic/SOA Rdata
class Rdata_Generic_SOA_Test : public ::testing::Test {
protected:
    Rdata_Generic_SOA_Test()
    {
        rdata = SOA("ns.example.com", "root.example.com", 2009102700, 7200,
                    3600, 24796800, TTL(1200));
    }
    SOA rdata;
};

TEST_F(Rdata_Generic_SOA_Test, fromToText)
{
    EXPECT_EQ("ns.example.com. root.example.com. 2009102700 7200 3600 24796800 1200", rdata.toText());
}

// The fixture for testing Generic/TXT Rdata class
class Rdata_Generic_TXT_Test : public ::testing::Test {
protected:
    Rdata_Generic_TXT_Test() : rdata("this is a test string") {}
    TXT rdata;
};

TEST_F(Rdata_Generic_TXT_Test, longCharString)
{
    EXPECT_THROW(TXT("0123456789abcdef0123456789abcdef0123456789abcdef"
                     "0123456789abcdef0123456789abcdef0123456789abcdef"
                     "0123456789abcdef0123456789abcdef0123456789abcdef"
                     "0123456789abcdef0123456789abcdef0123456789abcdef"
                     "0123456789abcdef0123456789abcdef0123456789abcdef"
                     "0123456789abcdef"),
                 isc::dns::DNSCharStringTooLong);
}

TEST_F(Rdata_Generic_TXT_Test, fromToText)
{
    EXPECT_EQ("\"this is a test string\"", rdata.toText());
}

// The fixture for testing class RRset
class RRsetTest : public ::testing::Test {
protected:
    RRsetTest() :
        rrset_a(Name("www.example.com"), RRClass::IN, RRType::A, TTL(3600)),
        rrset_aaaa(Name("ns.example.net"), RRClass::IN, RRType::AAAA, TTL(60))
    {
        rrset_a.addRdata(RdataPtr(new A("192.0.2.1")));
        rrset_a.addRdata(RdataPtr(new A("192.0.2.255")));
        rrset_aaaa.addRdata(RdataPtr(new AAAA("2001:db8::1234")));
    }
          
    RRset rrset_a;
    RRset rrset_aaaa;
};

TEST_F(RRsetTest, toText)
{
    EXPECT_EQ("www.example.com. 3600 IN A 192.0.2.1\n"
              "www.example.com. 3600 IN A 192.0.2.255",
              rrset_a.toText());
    EXPECT_EQ("ns.example.net. 60 IN AAAA 2001:db8::1234",
              rrset_aaaa.toText());
}

TEST_F(RRsetTest, count_rdata)
{
    EXPECT_EQ(2, rrset_a.countRdata());
    EXPECT_EQ(1, rrset_aaaa.countRdata());
}

// The fixture for testing class Question
class QuestionTest : public ::testing::Test {
protected:
    QuestionTest() :
        question_a(Name("www.example.com"), RRClass::IN, RRType::A),
        question_aaaa(Name("ns.example.net"), RRClass::IN, RRType::AAAA) {}
    Question question_a;
    Question question_aaaa;
};

TEST_F(QuestionTest, toText)
{
    EXPECT_EQ("www.example.com. IN A", question_a.toText());
    EXPECT_EQ("ns.example.net. IN AAAA", question_aaaa.toText());
}

TEST_F(QuestionTest, count_rdata)
{
    EXPECT_EQ(0, question_a.countRdata());
    EXPECT_EQ(0, question_aaaa.countRdata());
}

// The fixture for testing class RR
class RRTest : public ::testing::Test {
protected:
    RRTest() :
        rr_a(Name("www.example.com"), RRClass::IN, RRType::A, TTL(3600),
             A("192.0.2.1")),
        rr_aaaa(Name("ns.example.net"), RRClass::IN, RRType::AAAA, TTL(60),
                AAAA("2001:db8::1234")),
        rr_ns(Name("example.net"), RRClass::IN, RRType::NS, TTL(1800),
              NS("ns.example.net"))
    {}
    RR rr_a;
    RR rr_aaaa;
    RR rr_ns;
};

TEST_F(RRTest, toText)
{
    EXPECT_EQ("www.example.com. 3600 IN A 192.0.2.1", rr_a.toText());
    EXPECT_EQ("ns.example.net. 60 IN AAAA 2001:db8::1234", rr_aaaa.toText());
    EXPECT_EQ("example.net. 1800 IN NS ns.example.net.", rr_ns.toText());
}

TEST_F(RRTest, construtFromRdataPtr)
{
    EXPECT_EQ("www.example.com. 3600 IN A 192.0.2.1",
              RR(Name("www.example.com"), RRClass::IN, RRType::A, TTL(3600),
                 RdataPtr(new A("192.0.2.1"))).toText());
}
}
