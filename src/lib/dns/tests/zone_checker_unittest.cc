// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

    void callback(const std::string& reason, bool is_error) {
        if (is_error) {
            errors_.push_back(reason);
        } else {
            warns_.push_back(reason);
        }
    }

    // Check stored issue messages with expected ones.  Clear vectors so
    // the caller can check other cases.
    void checkIssues() {
        EXPECT_EQ(expected_errors_.size(), errors_.size());
        for (int i = 0; i < std::min(expected_errors_.size(), errors_.size());
             ++i) {
            // The actual message should begin with the expected message.
            EXPECT_EQ(0, errors_[0].find(expected_errors_[0]))
                << "actual message: " << errors_[0] << " expected: " <<
                expected_errors_[0];
        }
        EXPECT_EQ(expected_warns_.size(), warns_.size());
        for (int i = 0; i < std::min(expected_warns_.size(), warns_.size());
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
    soa_->addRdata(createRdata(RRType::NS(), zclass_, "ns.example.com"));
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

    // It doesn't have to be A.  An AAAA is enough.
    RRsetPtr aaaa(new RRset(ns_name, zclass_, RRType::AAAA(), RRTTL(60)));
    aaaa->addRdata(in::AAAA("2001:db8::1"));
    rrsets_->addRRset(aaaa);
    EXPECT_TRUE(checkZone(zname_, zclass_, *rrsets_, callbacks_));
    checkIssues();

    // Or it doesn't matter if the NS name is "out of bailiwick".
    rrsets_->removeRRset(zname_, zclass_, RRType::NS());
    ns_.reset(new RRset(zname_, zclass_, RRType::NS(), RRTTL(60)));
    ns_->addRdata(generic::NS("ns.example.org"));
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

}
