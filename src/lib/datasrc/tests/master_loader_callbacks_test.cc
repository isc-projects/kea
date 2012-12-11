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

#include <datasrc/master_loader_callbacks.h>
#include <datasrc/zone.h>

#include <dns/rrset.h>
#include <dns/rrclass.h>
#include <dns/rrttl.h>
#include <dns/rdata.h>

#include <testutils/dnsmessage_test.h>

#include <exceptions/exceptions.h>

#include <gtest/gtest.h>

#include <boost/lexical_cast.hpp>

#include <list>
#include <string>

using namespace isc::datasrc;

namespace {

// An updater for the tests. Most of the virtual methods throw
// NotImplemented, as they are not used in the tests.
class MockUpdater : public ZoneUpdater {
public:
    // We do the adding in this test. We currently only check these are
    // the correct ones, according to a predefined set in a list.
    virtual void addRRset(const isc::dns::AbstractRRset& rrset) {
        ASSERT_FALSE(expected_rrsets_.empty());

        // As the rrsetCheck requires a shared pointer, we need to create
        // a copy.
        isc::dns::RRsetPtr copy(new isc::dns::BasicRRset(rrset.getName(),
                                                         rrset.getClass(),
                                                         rrset.getType(),
                                                         rrset.getTTL()));
        EXPECT_FALSE(rrset.getRRsig()) << "Unexpected RRSIG on rrset, not "
            "copying. Following check will likely fail as a result.";
        for (isc::dns::RdataIteratorPtr it(rrset.getRdataIterator());
             !it->isLast(); it->next()) {
            copy->addRdata(it->getCurrent());
        }

        isc::testutils::rrsetCheck(expected_rrsets_.front(), copy);
        // And remove this RRset, as it has been used.
        expected_rrsets_.pop_front();
    }
    // The unused but required methods
    virtual ZoneFinder& getFinder() {
        isc_throw(isc::NotImplemented, "Not to be called in this test");
    }
    virtual void deleteRRset(const isc::dns::AbstractRRset&) {
        isc_throw(isc::NotImplemented, "Not to be called in this test");
    }
    virtual void commit() {
        isc_throw(isc::NotImplemented, "Not to be called in this test");
    }
    // The RRsets that are expected to appear through addRRset.
    std::list<isc::dns::RRsetPtr> expected_rrsets_;
};

class MasterLoaderCallbackTest : public ::testing::Test {
protected:
    MasterLoaderCallbackTest() :
        ok_(true),
        callbacks_(createMasterLoaderCallbacks(isc::dns::Name("example.org"),
                                               isc::dns::RRClass::IN(), &ok_))
    {}
    // Generate a new RRset, put it to the updater and return it.
    void generateRRset(isc::dns::AddRRCallback callback) {
        const isc::dns::RRsetPtr
            result(new isc::dns::RRset(isc::dns::Name("example.org"),
                                       isc::dns::RRClass::IN(),
                                       isc::dns::RRType::A(),
                                       isc::dns::RRTTL(3600)));
        const isc::dns::rdata::RdataPtr
            data(isc::dns::rdata::createRdata(isc::dns::RRType::A(),
                                              isc::dns::RRClass::IN(),
                                              "192.0.2.1"));

        result->addRdata(data);
        updater_.expected_rrsets_.push_back(result);

        callback(result->getName(), result->getClass(), result->getType(),
                 result->getTTL(), data);
    }
    // An updater to be passed to the context
    MockUpdater updater_;
    // Is the loading OK?
    bool ok_;
    // The tested context
    isc::dns::MasterLoaderCallbacks callbacks_;
};

// Check it doesn't crash if we don't provide the OK
TEST_F(MasterLoaderCallbackTest, noOkProvided) {
    createMasterLoaderCallbacks(isc::dns::Name("example.org"),
                                isc::dns::RRClass::IN(), NULL).
        error("No source", 1, "No reason");
}

// Check the callbacks can be called, don't crash and the error one switches
// to non-OK mode. This, however, does not stop anybody from calling more
// callbacks.
TEST_F(MasterLoaderCallbackTest, callbacks) {
    EXPECT_NO_THROW(callbacks_.warning("No source", 1, "Just for fun"));
    // The warning does not hurt the OK mode.
    EXPECT_TRUE(ok_);
    // Now the error
    EXPECT_NO_THROW(callbacks_.error("No source", 2, "Some error"));
    // The OK is turned off once there's at least one error
    EXPECT_FALSE(ok_);

    // Not being OK does not hurt that much, we can still call the callbacks
    EXPECT_NO_THROW(callbacks_.warning("No source", 3, "Just for fun"));
    // The OK is not reset back to true
    EXPECT_FALSE(ok_);
    EXPECT_NO_THROW(callbacks_.error("No source", 4, "Some error"));
}

// Try adding some RRsets.
TEST_F(MasterLoaderCallbackTest, addRRset) {
    isc::dns::AddRRCallback
        callback(createMasterLoaderAddCallback(updater_));
    // Put some of them in.
    EXPECT_NO_THROW(generateRRset(callback));
    EXPECT_NO_THROW(generateRRset(callback));
    // They all get pushed there right away, so there are none in the queue
    EXPECT_TRUE(updater_.expected_rrsets_.empty());
}

}
