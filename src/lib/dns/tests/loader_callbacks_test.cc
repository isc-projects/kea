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

#include <dns/loader_callbacks.h>
#include <dns/name.h>
#include <dns/rrttl.h>
#include <dns/rrclass.h>

#include <exceptions/exceptions.h>

#include <gtest/gtest.h>
#include <boost/bind.hpp>

namespace {

using std::string;
using namespace isc::dns;

class LoaderCallbacksTest : public ::testing::Test {
protected:
    LoaderCallbacksTest() :
        called_(false),
        rrset_(new RRset(Name("example.org"), RRClass::IN(), RRType::A(),
                         RRTTL(3600))),
        error_(boost::bind(&LoaderCallbacksTest::checkCallback, this, true, _1,
                           _2, _3)),
        warning_(boost::bind(&LoaderCallbacksTest::checkCallback, this, false,
                             _1, _2, _3)),
        add_(boost::bind(&LoaderCallbacksTest::checkAdd, this, _1)),
        callbacks_(error_, warning_, add_)
    {}

    void checkCallback(bool error, const string& source, size_t line,
                       const string& reason)
    {
        called_ = true;
        last_was_error_ = error;
        EXPECT_EQ("source", source);
        EXPECT_EQ(1, line);
        EXPECT_EQ("reason", reason);
    }
    void checkAdd(const RRsetPtr& rrset) {
        called_ = true;
        EXPECT_EQ(rrset_, rrset);
    }
    bool last_was_error_;
    bool called_;
    const RRsetPtr rrset_;
    const LoaderCallbacks::IssueCallback error_, warning_;
    const LoaderCallbacks::AddCallback add_;
    LoaderCallbacks callbacks_;
};

// Check the constructor rejects empty callbacks, but accepts non-empty ones
TEST_F(LoaderCallbacksTest, constructor) {
    EXPECT_THROW(LoaderCallbacks(LoaderCallbacks::IssueCallback(), warning_,
                                 add_), isc::InvalidParameter);
    EXPECT_THROW(LoaderCallbacks(error_, LoaderCallbacks::IssueCallback(),
                                 add_), isc::InvalidParameter);
    EXPECT_THROW(LoaderCallbacks(error_, warning_,
                                 LoaderCallbacks::AddCallback()),
                 isc::InvalidParameter);
    EXPECT_NO_THROW(LoaderCallbacks(error_, warning_, add_));
}

// Call the issue callbacks
TEST_F(LoaderCallbacksTest, issueCall) {
    callbacks_.error("source", 1, "reason");
    EXPECT_TRUE(last_was_error_);
    EXPECT_TRUE(called_);

    called_ = false;

    callbacks_.warning("source", 1, "reason");
    EXPECT_FALSE(last_was_error_);
    EXPECT_TRUE(called_);
}

// Call the add callback
TEST_F(LoaderCallbacksTest, addCall) {
    EXPECT_FALSE(called_);
    callbacks_.addRRset(rrset_);
    EXPECT_TRUE(called_);
}


}
