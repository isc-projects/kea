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
        // In our tests, pointer equality is enough.
        EXPECT_EQ(expected_rrsets_.front().get(), &rrset);
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

class LoaderCallbackTest : public ::testing::Test {
protected:
    LoaderCallbackTest() :
        ok_(true),
        callbacks_(createCallbacks(updater_, isc::dns::Name("example.org"),
                                   isc::dns::RRClass::IN(), &ok_))
    {}
    // Generate a new RRset, put it to the updater and return it.
    isc::dns::RRsetPtr generateRRset() {
        const isc::dns::RRsetPtr
            result(new isc::dns::RRset(isc::dns::Name("example.org"),
                                       isc::dns::RRClass::IN(),
                                       isc::dns::RRType::A(),
                                       isc::dns::RRTTL(3600)));
        updater_.expected_rrsets_.push_back(result);
        return (result);
    }
    // An updater to be passed to the context
    MockUpdater updater_;
    // Is the loading OK?
    bool ok_;
    // The tested context
    isc::dns::LoaderCallbacks callbacks_;
};

// Check it doesn't crash if we don't provide the OK
TEST_F(LoaderCallbackTest, noOkProvided) {
    createCallbacks(updater_, isc::dns::Name("example.org"),
                    isc::dns::RRClass::IN(), NULL).error("No source", 1,
                                                         "No reason");
}

// Check the callbacks can be called, don't crash and the error one switches
// to non-OK mode. This, however, does not stop anybody from calling more
// callbacks.
TEST_F(LoaderCallbackTest, callbacks) {
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
TEST_F(LoaderCallbackTest, addRRset) {
    // Put some of them in.
    EXPECT_NO_THROW(callbacks_.addRRset(generateRRset()));
    EXPECT_NO_THROW(callbacks_.addRRset(generateRRset()));
    // They all get pushed there right away, so there are none in the queue
    EXPECT_TRUE(updater_.expected_rrsets_.empty());

    // Making the status not OK by an error does not stop the RRsets to get
    // through.
    callbacks_.error("No source", 1, "Just an error");
    EXPECT_FALSE(ok_);

    EXPECT_NO_THROW(callbacks_.addRRset(generateRRset()));
    EXPECT_NO_THROW(callbacks_.addRRset(generateRRset()));
    // They got through and the OK status didn't get reset
    EXPECT_TRUE(updater_.expected_rrsets_.empty());
    EXPECT_FALSE(ok_);
}

}
