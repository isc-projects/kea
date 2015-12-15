// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dns/master_loader_callbacks.h>
#include <dns/rrset.h>
#include <dns/name.h>
#include <dns/rrttl.h>
#include <dns/rrclass.h>

#include <exceptions/exceptions.h>

#include <gtest/gtest.h>
#include <boost/bind.hpp>

namespace {

using std::string;
using namespace isc::dns;

class MasterLoaderCallbacksTest : public ::testing::Test {
protected:
    MasterLoaderCallbacksTest() :
        last_was_error_(false), // Not needed, but then cppcheck complains
        issue_called_(false),
        rrset_(new RRset(Name("example.org"), RRClass::IN(), RRType::A(),
                         RRTTL(3600))),
        error_(boost::bind(&MasterLoaderCallbacksTest::checkCallback, this,
                           true, _1, _2, _3)),
        warning_(boost::bind(&MasterLoaderCallbacksTest::checkCallback, this,
                             false, _1, _2, _3)),
        callbacks_(error_, warning_)
    {}

    void checkCallback(bool error, const string& source, size_t line,
                       const string& reason)
    {
        issue_called_ = true;
        last_was_error_ = error;
        EXPECT_EQ("source", source);
        EXPECT_EQ(1, line);
        EXPECT_EQ("reason", reason);
    }
    bool last_was_error_;
    bool issue_called_;
    const RRsetPtr rrset_;
    const MasterLoaderCallbacks::IssueCallback error_, warning_;
    MasterLoaderCallbacks callbacks_;
};

// Check the constructor rejects empty callbacks, but accepts non-empty ones
TEST_F(MasterLoaderCallbacksTest, constructor) {
    EXPECT_THROW(MasterLoaderCallbacks(MasterLoaderCallbacks::IssueCallback(),
                                       warning_), isc::InvalidParameter);
    EXPECT_THROW(MasterLoaderCallbacks(error_,
                                       MasterLoaderCallbacks::IssueCallback()),
                 isc::InvalidParameter);
    EXPECT_NO_THROW(MasterLoaderCallbacks(error_, warning_));
}

// Call the issue callbacks
TEST_F(MasterLoaderCallbacksTest, issueCall) {
    callbacks_.error("source", 1, "reason");
    EXPECT_TRUE(last_was_error_);
    EXPECT_TRUE(issue_called_);

    issue_called_ = false;

    callbacks_.warning("source", 1, "reason");
    EXPECT_FALSE(last_was_error_);
    EXPECT_TRUE(issue_called_);
}

}
