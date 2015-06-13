// Copyright (C) 2012, 2015  Internet Systems Consortium, Inc. ("ISC")
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

#include <dns/zone_checker.h>

#include <exceptions/exceptions.h>

#include <dns/name.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>
#include <dns/rdataclass.h>
#include <dns/rrset_collection.h>

#include <gtest/gtest.h>

#include <boost/bind.hpp>
#include <boost/scoped_ptr.hpp>

#include <algorithm>
#include <string>
#include <sstream>
#include <vector>

using isc::Unexpected;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace {

const char* const soa_txt = "ns.example.com. root.example.com. 0 0 0 0 0";
const char* const ns_txt1 = "ns.example.com.";
const char* const ns_a_txt1 = "192.0.2.1";
const char* const ns_txt2 = "ns2.example.com.";
const char* const ns_a_txt2 = "192.0.2.2";

class ZoneCheckerTest : public ::testing::Test {
protected:
    ZoneCheckerTest() :
        zname_("example.com"), zclass_(RRClass::IN()),
        soa_(new RRset(zname_, zclass_, RRType::SOA(), RRTTL(60))),
        ns_(new RRset(zname_, zclass_, RRType::NS(), RRTTL(60))),
        callbacks_(boost::bind(&ZoneCheckerTest::callback, this, _1, true),
                   boost::bind(&ZoneCheckerTest::callback, this, _1, false))
    {
        std::stringstream ss;
        ss << "example.com. 60 IN SOA " << soa_txt << "\n";
        ss << "example.com. 60 IN NS " << ns_txt1 << "\n";
        ss << "ns.example.com. 60 IN A " << ns_a_txt1 << "\n";
        ss << "ns2.example.com. 60 IN A " << ns_a_txt2 << "\n";
        rrsets_.reset(new RRsetCollection(ss, zname_, zclass_));
    }

public:
    // This one is passed to boost::bind.  Some compilers seem to require
    // it be public.
    void callback(const std::string& reason, bool is_error) {
        if (is_error) {
            errors_.push_back(reason);
        } else {
            warns_.push_back(reason);
        }
    }

protected:
    // Check stored issue messages with expected ones.  Clear vectors so
    // the caller can check other cases.
    void checkIssues() {
        EXPECT_EQ(expected_errors_.size(), errors_.size());
        for (size_t i = 0;
             i < std::min(expected_errors_.size(), errors_.size());
             ++i) {
            // The actual message should begin with the expected message.
            EXPECT_EQ(0, errors_[0].find(expected_errors_[0]))
                << "actual message: " << errors_[0] << " expected: " <<
                expected_errors_[0];
        }
        EXPECT_EQ(expected_warns_.size(), warns_.size());
        for (size_t i = 0;
             i < std::min(expected_warns_.size(), warns_.size());
             ++i) {
            EXPECT_EQ(0, warns_[0].find(expected_warns_[0]))
                << "actual message: " << warns_[0] << " expected: " <<
                expected_warns_[0];
        }

        errors_.clear();
        expected_errors_.clear();
        warns_.clear();
        expected_warns_.clear();
    }

    const Name zname_;
    const RRClass zclass_;
    boost::scoped_ptr<RRsetCollection> rrsets_;
    RRsetPtr soa_;
    RRsetPtr ns_;
    std::vector<std::string> errors_;
    std::vector<std::string> warns_;
    std::vector<std::string> expected_errors_;
    std::vector<std::string> expected_warns_;
    ZoneCheckerCallbacks callbacks_;
};

TEST_F(ZoneCheckerTest, checkGood) {
    // Checking a valid case.  No errors or warnings should be reported.
    EXPECT_TRUE(checkZone(zname_, zclass_, *rrsets_, callbacks_));
    checkIssues();

    // Multiple NS RRs are okay.
    rrsets_->removeRRset(zname_, zclass_, RRType::NS());
    ns_->addRdata(generic::NS(ns_txt1));
    ns_->addRdata(generic::NS(ns_txt2));
    rrsets_->addRRset(ns_);
    EXPECT_TRUE(checkZone(zname_, zclass_, *rrsets_, callbacks_));
    checkIssues();
}

TEST_F(ZoneCheckerTest, checkSOA) {
    // If the zone has no SOA it triggers an error.
    rrsets_->removeRRset(zname_, zclass_, RRType::SOA());
    EXPECT_FALSE(checkZone(zname_, zclass_, *rrsets_, callbacks_));
    expected_errors_.push_back("zone example.com/IN: has 0 SOA records");
    checkIssues();

    // If null callback is specified, checkZone() only returns the final
    // result.
    ZoneCheckerCallbacks noerror_callbacks(
        NULL, boost::bind(&ZoneCheckerTest::callback, this, _1, false));
    EXPECT_FALSE(checkZone(zname_, zclass_, *rrsets_, noerror_callbacks));
    checkIssues();

    // If there are more than 1 SOA RR, it's also an error.
    errors_.clear();
    soa_->addRdata(generic::SOA(soa_txt));
    soa_->addRdata(generic::SOA("ns2.example.com. . 0 0 0 0 0"));
    rrsets_->addRRset(soa_);
    EXPECT_FALSE(checkZone(zname_, zclass_, *rrsets_, callbacks_));
    expected_errors_.push_back("zone example.com/IN: has 2 SOA records");
    checkIssues();

    // If the SOA RRset is "empty", it's treated as an implementation
    // (rather than operational) error and results in an exception.
    rrsets_->removeRRset(zname_, zclass_, RRType::SOA());
    soa_.reset(new RRset(zname_, zclass_, RRType::SOA(), RRTTL(60)));
    rrsets_->addRRset(soa_);
    EXPECT_THROW(checkZone(zname_, zclass_, *rrsets_, callbacks_), Unexpected);
    checkIssues();              // no error/warning should be reported

    // Likewise, if the SOA RRset contains non SOA Rdata, it should be a bug.
    rrsets_->removeRRset(zname_, zclass_, RRType::SOA());
    soa_.reset(new RRset(zname_, zclass_, RRType::SOA(), RRTTL(60)));
    soa_->addRdata(createRdata(RRType::NS(), zclass_, "ns.example.com."));
    rrsets_->addRRset(soa_);
    EXPECT_THROW(checkZone(zname_, zclass_, *rrsets_, callbacks_), Unexpected);
    checkIssues();              // no error/warning should be reported
}

TEST_F(ZoneCheckerTest, checkNS) {
    // If the zone has no NS at origin it triggers an error.
    rrsets_->removeRRset(zname_, zclass_, RRType::NS());
    EXPECT_FALSE(checkZone(zname_, zclass_, *rrsets_, callbacks_));
    expected_errors_.push_back("zone example.com/IN: has no NS records");
    checkIssues();

    // Check two buggy cases like the SOA tests
    ns_.reset(new RRset(zname_, zclass_, RRType::NS(), RRTTL(60)));
    rrsets_->addRRset(ns_);
    EXPECT_THROW(checkZone(zname_, zclass_, *rrsets_, callbacks_), Unexpected);
    checkIssues();              // no error/warning should be reported

    rrsets_->removeRRset(zname_, zclass_, RRType::NS());
    ns_.reset(new RRset(zname_, zclass_, RRType::NS(), RRTTL(60)));
    ns_->addRdata(createRdata(RRType::TXT(), zclass_, "ns.example.com"));
    rrsets_->addRRset(ns_);
    EXPECT_THROW(checkZone(zname_, zclass_, *rrsets_, callbacks_), Unexpected);
    checkIssues();              // no error/warning should be reported
}

TEST_F(ZoneCheckerTest, checkNSData) {
    const Name ns_name("ns.example.com");

    // If a ("in-bailiwick") NS name doesn't have an address record, it's
    // reported as a warning.
    rrsets_->removeRRset(ns_name, zclass_, RRType::A());
    EXPECT_TRUE(checkZone(zname_, zclass_, *rrsets_, callbacks_));
    expected_warns_.push_back("zone example.com/IN: NS has no address");
    checkIssues();

    // Same check, but disabling warning callback.  Same result, but without
    // the warning.
    ZoneCheckerCallbacks nowarn_callbacks(
        boost::bind(&ZoneCheckerTest::callback, this, _1, true), NULL);
    EXPECT_TRUE(checkZone(zname_, zclass_, *rrsets_, nowarn_callbacks));
    checkIssues();

    // A tricky case: if the name matches a wildcard, it should technically
    // be considered valid, but this checker doesn't check that far and still
    // warns.
    RRsetPtr wild(new RRset(Name("*.example.com"), zclass_, RRType::A(),
                            RRTTL(0)));
    wild->addRdata(in::A("192.0.2.255"));
    rrsets_->addRRset(wild);
    EXPECT_TRUE(checkZone(zname_, zclass_, *rrsets_, callbacks_));
    expected_warns_.push_back("zone example.com/IN: NS has no address");
    checkIssues();

    // If there's a CNAME at the name instead, it's an error.
    rrsets_->removeRRset(Name("*.example.com"), zclass_, RRType::A());
    RRsetPtr cname(new RRset(ns_name, zclass_, RRType::CNAME(), RRTTL(60)));
    cname->addRdata(generic::CNAME("cname.example.com."));
    rrsets_->addRRset(cname);
    EXPECT_FALSE(checkZone(zname_, zclass_, *rrsets_, callbacks_));
    expected_errors_.push_back("zone example.com/IN: NS 'ns.example.com' is "
                               "a CNAME (illegal per RFC2181)");
    checkIssues();

    // It doesn't have to be A.  An AAAA is enough.
    rrsets_->removeRRset(ns_name, zclass_, RRType::CNAME());
    RRsetPtr aaaa(new RRset(ns_name, zclass_, RRType::AAAA(), RRTTL(60)));
    aaaa->addRdata(in::AAAA("2001:db8::1"));
    rrsets_->addRRset(aaaa);
    EXPECT_TRUE(checkZone(zname_, zclass_, *rrsets_, callbacks_));
    checkIssues();

    // Coexisting CNAME makes it error (CNAME with other record is itself
    // invalid, but it's a different issue in this context)
    rrsets_->addRRset(cname);
    EXPECT_FALSE(checkZone(zname_, zclass_, *rrsets_, callbacks_));
    expected_errors_.push_back("zone example.com/IN: NS 'ns.example.com' is "
                               "a CNAME (illegal per RFC2181)");
    checkIssues();

    // It doesn't matter if the NS name is "out of bailiwick".
    rrsets_->removeRRset(ns_name, zclass_, RRType::CNAME());
    rrsets_->removeRRset(zname_, zclass_, RRType::NS());
    ns_.reset(new RRset(zname_, zclass_, RRType::NS(), RRTTL(60)));
    ns_->addRdata(generic::NS("ns.example.org."));
    rrsets_->addRRset(ns_);
    EXPECT_TRUE(checkZone(zname_, zclass_, *rrsets_, callbacks_));
    checkIssues();

    // Note that if the NS name is the origin name, it should be checked
    rrsets_->removeRRset(zname_, zclass_, RRType::NS());
    ns_.reset(new RRset(zname_, zclass_, RRType::NS(), RRTTL(60)));
    ns_->addRdata(generic::NS(zname_));
    rrsets_->addRRset(ns_);
    EXPECT_TRUE(checkZone(zname_, zclass_, *rrsets_, callbacks_));
    expected_warns_.push_back("zone example.com/IN: NS has no address");
    checkIssues();
}

TEST_F(ZoneCheckerTest, checkNSWithDelegation) {
    // Tests various cases where there's a zone cut due to delegation between
    // the zone origin and the NS name.  In each case the NS name doesn't have
    // an address record.
    const Name ns_name("ns.child.example.com");

    // Zone cut due to delegation in the middle; the check for the address
    // record should be skipped.
    rrsets_->removeRRset(zname_, zclass_, RRType::NS());
    ns_.reset(new RRset(zname_, zclass_, RRType::NS(), RRTTL(60)));
    ns_->addRdata(generic::NS(ns_name));
    rrsets_->addRRset(ns_);
    RRsetPtr child_ns(new RRset(Name("child.example.com"), zclass_,
                                RRType::NS(), RRTTL(60)));
    child_ns->addRdata(generic::NS("ns.example.org."));
    rrsets_->addRRset(child_ns);
    EXPECT_TRUE(checkZone(zname_, zclass_, *rrsets_, callbacks_));
    checkIssues();

    // Zone cut at the NS name.  Same result.
    rrsets_->removeRRset(child_ns->getName(), zclass_, RRType::NS());
    child_ns.reset(new RRset(ns_name, zclass_, RRType::NS(), RRTTL(60)));
    child_ns->addRdata(generic::NS("ns.example.org."));
    rrsets_->addRRset(child_ns);
    EXPECT_TRUE(checkZone(zname_, zclass_, *rrsets_, callbacks_));
    checkIssues();

    // Zone cut below the NS name.  The check applies.
    rrsets_->removeRRset(child_ns->getName(), zclass_, RRType::NS());
    child_ns.reset(new RRset(Name("another.ns.child.example.com"), zclass_,
                             RRType::NS(), RRTTL(60)));
    child_ns->addRdata(generic::NS("ns.example.org."));
    rrsets_->addRRset(child_ns);
    EXPECT_TRUE(checkZone(zname_, zclass_, *rrsets_, callbacks_));
    expected_warns_.push_back("zone example.com/IN: NS has no address");
    checkIssues();
}

TEST_F(ZoneCheckerTest, checkNSWithDNAME) {
    // Similar to the above case, but the zone cut is due to DNAME.  This is
    // an invalid configuration.
    const Name ns_name("ns.child.example.com");

    // Zone cut due to DNAME at the zone origin.  This is an invalid case.
    rrsets_->removeRRset(zname_, zclass_, RRType::NS());
    ns_.reset(new RRset(zname_, zclass_, RRType::NS(), RRTTL(60)));
    ns_->addRdata(generic::NS(ns_name));
    rrsets_->addRRset(ns_);
    RRsetPtr dname(new RRset(zname_, zclass_, RRType::DNAME(), RRTTL(60)));
    dname->addRdata(generic::DNAME("example.org."));
    rrsets_->addRRset(dname);
    EXPECT_FALSE(checkZone(zname_, zclass_, *rrsets_, callbacks_));
    expected_errors_.push_back("zone example.com/IN: NS 'ns.child.example.com'"
                               " is below a DNAME 'example.com'");
    checkIssues();

    // Zone cut due to DNAME in the middle.  Same result.
    rrsets_->removeRRset(zname_, zclass_, RRType::DNAME());
    dname.reset(new RRset(Name("child.example.com"), zclass_, RRType::DNAME(),
                          RRTTL(60)));
    dname->addRdata(generic::DNAME("example.org."));
    rrsets_->addRRset(dname);
    EXPECT_FALSE(checkZone(zname_, zclass_, *rrsets_, callbacks_));
    expected_errors_.push_back("zone example.com/IN: NS 'ns.child.example.com'"
                               " is below a DNAME 'child.example.com'");
    checkIssues();

    // A tricky case: there's also an NS at the name that has DNAME.  It's
    // prohibited per RFC6672 so we could say it's "undefined".  Nevertheless,
    // this implementation prefers the NS and skips further checks.
    ns_.reset(new RRset(Name("child.example.com"), zclass_, RRType::NS(),
                        RRTTL(60)));
    ns_->addRdata(generic::NS("ns.example.org."));
    rrsets_->addRRset(ns_);
    EXPECT_TRUE(checkZone(zname_, zclass_, *rrsets_, callbacks_));
    checkIssues();

    // Zone cut due to DNAME at the NS name.  In this case DNAME doesn't
    // affect the NS name, so it should result in "no address record" warning.
    rrsets_->removeRRset(dname->getName(), zclass_, RRType::DNAME());
    rrsets_->removeRRset(ns_->getName(), zclass_, RRType::NS());
    dname.reset(new RRset(ns_name, zclass_, RRType::DNAME(), RRTTL(60)));
    dname->addRdata(generic::DNAME("example.org."));
    rrsets_->addRRset(dname);
    EXPECT_TRUE(checkZone(zname_, zclass_, *rrsets_, callbacks_));
    expected_warns_.push_back("zone example.com/IN: NS has no address");
    checkIssues();
}

}
