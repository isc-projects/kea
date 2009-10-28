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
using isc::dns::Rdata::RDATAPTR;
using isc::dns::Rdata::IN::A;
using isc::dns::Rdata::IN::AAAA;
using isc::dns::Rdata::Generic::NS;
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

TEST_F(RRClassTest, from_to_text)
{
    EXPECT_EQ("IN", rrclass_in.to_text());
    EXPECT_EQ("CH", rrclass_ch.to_text());
}

// The fixture for testing class RRType.
class RRTypeTest : public ::testing::Test {
protected:
    RRTypeTest() :
        rrtype_a("A"), rrtype_aaaa("AAAA"), rrtype_ns("NS") {}
    RRType rrtype_a;
    RRType rrtype_aaaa;
    RRType rrtype_ns;
};

TEST_F(RRTypeTest, from_to_text)
{
    EXPECT_EQ("A", rrtype_a.to_text());
    EXPECT_EQ("AAAA", rrtype_aaaa.to_text());
    EXPECT_EQ("NS", rrtype_ns.to_text());
}

// The fixture for testing class TTL.
class TTLTest : public ::testing::Test {
protected:
    TTLTest() : ttl3600(3600), ttl0(0) {}
    TTL ttl3600;
    TTL ttl0;
};

TEST_F(TTLTest, to_text)
{
    EXPECT_EQ("3600", ttl3600.to_text());
    EXPECT_EQ("0", ttl0.to_text());
}

TEST_F(TTLTest, get_value)
{
    EXPECT_EQ(3600, ttl3600.get_value());
    EXPECT_EQ(0, ttl0.get_value());
}

// The fixture for testing class IN/A Rdata
class Rdata_IN_A_Test : public ::testing::Test {
protected:
    Rdata_IN_A_Test() : rdata("192.0.2.1") {}
    A rdata;
};

TEST_F(Rdata_IN_A_Test, from_to_text)
{
    EXPECT_EQ("192.0.2.1", rdata.to_text());
    EXPECT_THROW(A("2001:db8::1234"), isc::ISCInvalidAddressString);
}

// The fixture for testing class IN/AAAA Rdata
class Rdata_IN_AAAA_Test : public ::testing::Test {
protected:
    Rdata_IN_AAAA_Test() : rdata("2001:db8::abcd") {}
    AAAA rdata;
};

TEST_F(Rdata_IN_AAAA_Test, from_to_text)
{
    EXPECT_EQ("2001:db8::abcd", rdata.to_text());
    EXPECT_THROW(AAAA("192.0.2.255"), isc::ISCInvalidAddressString);
}

// The fixture for testing class Generic/NS Rdata
class Rdata_Generic_NS_Test : public ::testing::Test {
protected:
    Rdata_Generic_NS_Test() : rdata("ns.example.com") {}
    NS rdata;
};

TEST_F(Rdata_Generic_NS_Test, from_to_text)
{
    EXPECT_EQ("ns.example.com.", rdata.to_text());
}

// The fixture for testing class RRset
class RRsetTest : public ::testing::Test {
protected:
    RRsetTest() :
        rrset_a(Name("www.example.com"), RRClass::IN, RRType::A, TTL(3600)),
        rrset_aaaa(Name("ns.example.net"), RRClass::IN, RRType::AAAA, TTL(60))
    {
        rrset_a.add_rdata(RDATAPTR(new A("192.0.2.1")));
        rrset_a.add_rdata(RDATAPTR(new A("192.0.2.255")));
        rrset_aaaa.add_rdata(RDATAPTR(new AAAA("2001:db8::1234")));
    }
          
    RRset rrset_a;
    RRset rrset_aaaa;
};

TEST_F(RRsetTest, to_text)
{
    EXPECT_EQ("www.example.com. 3600 IN A 192.0.2.1\n"
              "www.example.com. 3600 IN A 192.0.2.255",
              rrset_a.to_text());
    EXPECT_EQ("ns.example.net. 60 IN AAAA 2001:db8::1234",
              rrset_aaaa.to_text());
}

TEST_F(RRsetTest, count_rdata)
{
    EXPECT_EQ(2, rrset_a.count_rdata());
    EXPECT_EQ(1, rrset_aaaa.count_rdata());
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

TEST_F(QuestionTest, to_text)
{
    EXPECT_EQ("www.example.com. IN A", question_a.to_text());
    EXPECT_EQ("ns.example.net. IN AAAA", question_aaaa.to_text());
}

TEST_F(QuestionTest, count_rdata)
{
    EXPECT_EQ(0, question_a.count_rdata());
    EXPECT_EQ(0, question_aaaa.count_rdata());
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

TEST_F(RRTest, to_text)
{
    EXPECT_EQ("www.example.com. 3600 IN A 192.0.2.1", rr_a.to_text());
    EXPECT_EQ("ns.example.net. 60 IN AAAA 2001:db8::1234", rr_aaaa.to_text());
    EXPECT_EQ("example.net. 1800 IN NS ns.example.net.", rr_ns.to_text());
}
}
