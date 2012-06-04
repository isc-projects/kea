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

#include <datasrc/container.h>

#include <gtest/gtest.h>

using namespace isc::datasrc;
using namespace isc::data;
using namespace isc::dns;
using namespace boost;

namespace {

// The test version is the same as the normal version. We, however, add
// some methods to dig directly in the internals, for the tests.
class TestedContainer : public ConfigurableContainer {
public:
    TestedContainer(const ConstElementPtr& configuration,
                    bool allow_cache) :
        ConfigurableContainer(configuration, allow_cache)
    { }
};

class ContainerTest : public ::testing::Test {
public:
    ContainerTest() :
        // The empty list corresponds to a container with no elements inside
        container_(new TestedContainer(ConstElementPtr(new ListElement()),
                                       true))
    { }
    shared_ptr<TestedContainer> container_;
};

// Test the container we create with empty configuration is, in fact, empty
TEST_F(ContainerTest, emptyContainer) {
    EXPECT_TRUE(container_->dataSources().empty());
}

// Check the values returned by a search on an empty container. It should be
// a negative answer (nothing found) no matter if we want an exact or inexact
// match.
TEST_F(ContainerTest, emptySearch) {
    Container::SearchResult negativeResult;
    // No matter what we try, we don't get an answer.
    EXPECT_EQ(negativeResult, container_->search(Name("example.org"), false,
                                                 false));
    EXPECT_EQ(negativeResult, container_->search(Name("example.org"), false,
                                                 true));
    EXPECT_EQ(negativeResult, container_->search(Name("example.org"), true,
                                                 false));
    EXPECT_EQ(negativeResult, container_->search(Name("example.org"), true,
                                                 true));
}

}
