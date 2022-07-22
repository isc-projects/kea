// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcpsrv/memfile_lease_limits.h>
#include <testutils/gtest_utils.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::data;

namespace {

/// @brief Test fixture for exercising ClassLeaseCounter.
class ClassLeaseCounterTest : public ::testing::Test {
public:
    /// @brief Constructor
    ClassLeaseCounterTest() {
        // Create two lists of classes and user contexts containing each.
        // Note the lists have one class in common, "three".
        classes1_.push_back("one");
        classes1_.push_back("three");
        classes1_.push_back("five");
        ctx1_ = makeContextWithClasses(classes1_);

        classes2_.push_back("two");
        classes2_.push_back("three");
        classes2_.push_back("four");
        ctx2_ = makeContextWithClasses(classes2_);
    }

    /// @brief Destructor
    virtual ~ClassLeaseCounterTest() = default;

    /// @brief Create a user-context with a given list of classes
    ///
    /// Creates an Element::map with the following content:
    ///
    /// {
    ///     "ISC": {
    ///         "client-classes": [ "class0", "class1", ... ]
    ///     }
    /// }
    ///
    /// @param classes  list of classes to include in the context
    /// @return ElementPtr containing the user-context
    ElementPtr makeContextWithClasses(const std::list<ClientClass>& classes) {
        ElementPtr ctx = Element::createMap();
        if (classes.size()) {
            ElementPtr clist = Element::createList();
            for (auto client_class : classes ) {
                clist->add(Element::create(client_class));
            }

            ElementPtr client_classes = Element::createMap();
            client_classes->set("client-classes", clist);
            ctx->set("ISC", client_classes);
        }

        return (ctx);
    }

    /// @brief Constructs a lease of a given Lease::Type
    ///
    /// @param ltype type of the lease desired (e.g Lease::TYPE_V4,
    /// TYPE_NA, or TYPE_PD
    ///
    /// @return LeasePtr pointing the newly created lease.
    LeasePtr leaseFactory(const Lease::Type& ltype) {
        LeasePtr lease;
        switch (ltype) {
        case Lease::TYPE_V4: {
            uint8_t hwaddr_data[] = { 0, 0x11, 0x11, 0x11, 0x11, 0x11 };
            HWAddrPtr hwaddr(new HWAddr(hwaddr_data, sizeof(hwaddr_data), HTYPE_ETHER));
            time_t now = time(NULL);
            lease.reset(new Lease4(IOAddress("192.0.2.100"), hwaddr, ClientIdPtr(), 500, now, 100));
            break;
            }
        case Lease::TYPE_NA: {
            DuidPtr duid(new DUID(DUID::fromText("01:02:03:04:05:06:07:08:09")));
            lease.reset(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"), duid, 1010,
                                    2400, 3600, 100));
            break;
            }
        case Lease::TYPE_PD: {
            DuidPtr duid(new DUID(DUID::fromText("11:22:33:44:55:66:77:88:99")));
            lease.reset(new Lease6(Lease::TYPE_PD, IOAddress("3001::"), duid, 1010,
                                   2400, 3600, 100));
            break;
            }
        default:
            ADD_FAILURE() << "TYPE_TA is not supported";
            break;
        }

        return (lease);
    }

    /// @brief Verifies that the ClassLeaseCounter has the expected entries
    ///
    /// @param classes list of classes to verify
    /// @param classes list of expected lease count for each class (assumed to be
    /// in the same order as classes)
    /// @param ltype type of lease counted
    void checkClassCounts(std::list<ClientClass> classes, std::list<size_t> expected_counts,
                          const Lease::Type& ltype = Lease::TYPE_V4) {
        ASSERT_EQ(classes.size(), expected_counts.size())
            << "test is broken, number of classes and counts do not match";

        EXPECT_EQ(classes.size(), clc_.size(ltype));
        auto expected_count = expected_counts.begin();
        for (auto client_class : classes) {
            size_t count;
            ASSERT_NO_THROW_LOG(count = clc_.getClassCount(client_class, ltype));
            EXPECT_EQ(count, *expected_count) << ", count is wrong for client_class: " << client_class;
            ++expected_count;
        }
    }

    /// @brief Exercises ClassLeaseCounter::addLease() and removeLease()
    ///
    /// Performs a series of adds and removes of a given lease in different
    /// lease states.
    ///
    /// @param lease Lease to add and remove
    void addAndRemoveLeaseTest(LeasePtr lease) {
        // Get the lease type for convenience.
        Lease::Type ltype = lease->getType();

        // Set the lease state to DEFAULT.
        lease->state_ = Lease::STATE_DEFAULT;

        // Add a lease with no classes.  Should create no counts.
        ASSERT_NO_THROW_LOG(clc_.addLease(lease));
        EXPECT_EQ(0, clc_.size(ltype));

        // Remove the lease with no classes.  Should create no counts.
        ASSERT_NO_THROW_LOG(clc_.removeLease(lease));
        EXPECT_EQ(0, clc_.size(ltype));

        // Add user-context with class list to lease.
        lease->setContext(ctx1_);
        ASSERT_NO_THROW_LOG(clc_.addLease(lease));
        checkClassCounts(classes1_, std::list<size_t>({ 1, 1, 1 }), ltype);

        // Add the same lease again. Counts should increment.
        ASSERT_NO_THROW_LOG(clc_.addLease(lease));
        checkClassCounts(classes1_, std::list<size_t>({ 2, 2, 2 }), ltype);

        // Set lease state to DECLINED and add it. Counts should not increment.
        lease->state_ = Lease::STATE_DECLINED;
        ASSERT_NO_THROW_LOG(clc_.addLease(lease));
        checkClassCounts(classes1_, std::list<size_t>({ 2, 2, 2 }), ltype);

        // Set lease state to EXPIRED_RECLAIMED and add it. Counts should not increment.
        lease->state_ = Lease::STATE_EXPIRED_RECLAIMED;
        ASSERT_NO_THROW_LOG(clc_.addLease(lease));
        checkClassCounts(classes1_, std::list<size_t>({ 2, 2, 2 }), ltype);

        // Set lease state back to DEFAULT and remove it. Counts should decrement.
        lease->state_ = Lease::STATE_DEFAULT;
        ASSERT_NO_THROW_LOG(clc_.removeLease(lease));
        checkClassCounts(classes1_, std::list<size_t>({ 1, 1, 1 }), ltype);

        // Set lease state to DECLINED and remove it. Counts should not decrement.
        lease->state_ = Lease::STATE_DECLINED;
        ASSERT_NO_THROW_LOG(clc_.removeLease(lease));
        checkClassCounts(classes1_, std::list<size_t>({ 1, 1, 1 }), ltype);

        // Set lease state to EXPIRED_RECLAIMED and remove it. Counts should not decrement.
        lease->state_ = Lease::STATE_EXPIRED_RECLAIMED;
        ASSERT_NO_THROW_LOG(clc_.removeLease(lease));
        checkClassCounts(classes1_, std::list<size_t>({ 1, 1, 1 }), ltype);

        // Set lease state back to DEFAULT and remove it. Counts should reach 0.
        lease->state_ = Lease::STATE_DEFAULT;
        ASSERT_NO_THROW_LOG(clc_.removeLease(lease));
        checkClassCounts(classes1_, std::list<size_t>({ 0, 0, 0 }), ltype);

        // Remove it again. Counts should not go negative.
        ASSERT_NO_THROW_LOG(clc_.removeLease(lease));
        checkClassCounts(classes1_, std::list<size_t>({ 0, 0, 0 }), ltype);
    }

    /// #brief Test updating type of lease for given old and new states and class lists
    ///
    /// The test creates an old and new version of the same lease and passes them into
    /// @c ClassLeaseCounter::updateLease().  It then verifies the class lease counts
    /// against expected count lists.
    ///
    /// @param old_state state of the old lease
    /// @param old_classes class list of the old lease
    /// @param expected_old_counts list of expected class lease counts (assumed to be
    /// in same order as old_classes)
    /// @param new_state state of the new lease
    /// @param new_classes class list of the new lease
    /// @param expected_new_counts list of expected class lease counts (assumed to be
    /// in same order as new_classes)
    /// @param ltype type of lease to update
    void updateLeaseTest(uint32_t old_state, const std::list<ClientClass> old_classes,
                         std::list<size_t> expected_old_counts,
                         uint32_t new_state, const std::list<ClientClass> new_classes,
                         std::list<size_t> expected_new_counts, const Lease::Type& ltype) {
        // Start the map with a count of one for all the old classes.
        clc_.clear();
        for (auto client_class : old_classes) {
            ASSERT_NO_THROW_LOG(clc_.setClassCount(client_class, 1, ltype));
        }

        // Create the old and new lease, that beyond classes and state, are the same.
        LeasePtr old_lease = leaseFactory(ltype);
        old_lease->state_ = old_state;
        old_lease->setContext(makeContextWithClasses(old_classes));

        LeasePtr new_lease = leaseFactory(ltype);
        new_lease->state_ = new_state;
        new_lease->setContext(makeContextWithClasses(new_classes));

        // Update the count.
        ASSERT_NO_THROW_LOG(clc_.updateLease(new_lease, old_lease));

        // Verify class counts for the old lease's classes are right.
        auto expected_count = expected_old_counts.begin();
        for (auto client_class : old_classes) {
            size_t count;
            ASSERT_NO_THROW_LOG(count = clc_.getClassCount(client_class, ltype));
            EXPECT_EQ(count, *expected_count)
                      << ", old count is wrong for client_class: " << client_class;
            ++expected_count;
        }

        // Verify class counts for the new lease's classes are right.
        expected_count = expected_new_counts.begin();
        for (auto client_class : new_classes) {
            size_t count;
            ASSERT_NO_THROW_LOG(count = clc_.getClassCount(client_class, ltype));
            EXPECT_EQ(count, *expected_count)
                      << ", new count is wrong for client_class: " << client_class;
            ++expected_count;
        }
    }

    /// @brief Verifies updateLease() over a permutation of class lists and lease states
    /// for a given lease type
    /// @param ltype type of lease to test
    void updateLeaseTests(const Lease::Type& ltype) {
        // Both state DEFAULT, no old class list.
        updateLeaseTest(Lease::STATE_DEFAULT, no_classes_, std::list<size_t>{},
                        Lease::STATE_DEFAULT, classes2_, std::list<size_t>{1,1,1}, ltype);

        // Both state DEFAULT, same class list.
        updateLeaseTest(Lease::STATE_DEFAULT, classes1_, std::list<size_t>{1,1,1},
                        Lease::STATE_DEFAULT, classes1_, std::list<size_t>{1,1,1}, ltype);

        // Both state DEFAULT, different class list.  Class "three" is in both lists.
        updateLeaseTest(Lease::STATE_DEFAULT, classes1_, std::list<size_t>{0,1,0},
                        Lease::STATE_DEFAULT, classes2_, std::list<size_t>{1,1,1}, ltype);

        // Old state is DEFAULT, new state is DECLINED.  Old classes should be decremented,
        // new classes should not be incremented.
        updateLeaseTest(Lease::STATE_DEFAULT, classes1_, std::list<size_t>{0,0,0},
                        Lease::STATE_DECLINED, classes2_, std::list<size_t>{0,0,0}, ltype);

        // Old state is DEFAULT, new state is EXPIRED_RECLAIMED.  Old classes should be decremented,
        // new classes should not be incremented.
        updateLeaseTest(Lease::STATE_DEFAULT, classes1_, std::list<size_t>{0,0,0},
                        Lease::STATE_EXPIRED_RECLAIMED, classes2_, std::list<size_t>{0,0,0}, ltype);

        // Old state is DECLINED, new state is DEFAULT.  Old classes should not decremented,
        // new classes should be incremented.  Class "three" is in both lists.
        updateLeaseTest(Lease::STATE_DECLINED, classes1_, std::list<size_t>{1,2,1},
                        Lease::STATE_DEFAULT, classes2_, std::list<size_t>{1,2,1}, ltype);

        // Old state is DECLINED, new state is DECLINED.  No count changes.
        updateLeaseTest(Lease::STATE_DECLINED, classes1_, std::list<size_t>{1,1,1},
                        Lease::STATE_DECLINED, classes2_, std::list<size_t>{0,1,0}, ltype);

        // Old state is DECLINED, new state is EXPIRED-RECLAIMED.  No count changes.
        updateLeaseTest(Lease::STATE_DECLINED, classes1_, std::list<size_t>{1,1,1},
                        Lease::STATE_EXPIRED_RECLAIMED, classes2_, std::list<size_t>{0,1,0}, ltype);

        // Old state is EXPIRED_RECLAIMED , new state is DEFAULT.  Old classes should not decremented,
        // new classes should be incremented.  Class "three" is in both lists.
        updateLeaseTest(Lease::STATE_EXPIRED_RECLAIMED, classes1_, std::list<size_t>{1,2,1},
                        Lease::STATE_DEFAULT, classes2_, std::list<size_t>{1,2,1}, ltype);

        // Old state is EXPIRED_RECLAIMED , new state is DECLINED.  No count changes.
        updateLeaseTest(Lease::STATE_EXPIRED_RECLAIMED, classes1_, std::list<size_t>{1,1,1},
                        Lease::STATE_DECLINED, classes2_, std::list<size_t>{0,1,0}, ltype);

        // Old state is EXPIRED_RECLAIMED , new state is EXPIRED_RECLAIMED.  No count changes.
        updateLeaseTest(Lease::STATE_EXPIRED_RECLAIMED, classes1_, std::list<size_t>{1,1,1},
                        Lease::STATE_EXPIRED_RECLAIMED, classes2_, std::list<size_t>{0,1,0}, ltype);

    }

    /// @brief Verifies ClassLeaseCounter::adjustClassCounts
    ///
    /// @param ltype type of lease to count.
    void adjustClassCountsTest(const Lease::Type ltype) {
        ConstElementPtr class_list1 =  ctx1_->find("ISC/client-classes");
        ASSERT_TRUE(class_list1);

        // Increment the classes by 2 and verify.
        ASSERT_NO_THROW_LOG(clc_.adjustClassCounts(class_list1, 2, ltype));
        checkClassCounts(classes1_, std::list<size_t>({ 2, 2, 2 }), ltype);

        // Decrement the classes by 1 and verify.
        ASSERT_NO_THROW_LOG(clc_.adjustClassCounts(class_list1, -1, ltype));
        checkClassCounts(classes1_, std::list<size_t>({ 1, 1, 1 }), ltype);

        // Decrement the classes by 2 and verify that roll-over is avoided..
        ASSERT_NO_THROW_LOG(clc_.adjustClassCounts(class_list1, -2, ltype));
        checkClassCounts(classes1_, std::list<size_t>({ 0, 0, 0 }), ltype);
    }

    /// @brief First test list of classes
    std::list<ClientClass> classes1_;

    /// @brief Second test list of classes
    std::list<ClientClass> classes2_;

    /// @brief Empty list of classes
    std::list<ClientClass> no_classes_;

    /// @brief User context containing classes1_;
    ElementPtr ctx1_;

    /// @brief User context containing classes2_;
    ElementPtr ctx2_;

    /// @brief ClassLeaseCounter instance to use in the test.
    ClassLeaseCounter clc_;
};

// Tests getting and adjusting basic class counts for
// a Lease::TYPE_V4.
TEST_F(ClassLeaseCounterTest, basicCountingTests4) {
    // Create test classes.
    ClientClass melon("melon");
    ClientClass water("water");

    // Fetching the count for a non-existent class
    // should return 0.
    ASSERT_EQ(0, clc_.size());
    size_t count;
    ASSERT_NO_THROW(count = clc_.getClassCount(melon));
    EXPECT_EQ(0, count);

    // Calling adjustClassCount() for non-existent class
    // should result in an entry with the adjustment value.
    ASSERT_EQ(0, clc_.size());
    ASSERT_NO_THROW(clc_.adjustClassCount(melon, 1));
    EXPECT_EQ(1, clc_.size());
    ASSERT_NO_THROW_LOG(count = clc_.getClassCount(melon));
    EXPECT_EQ(1, count);

    // Calling adjust() again to add 1 should work.
    ASSERT_NO_THROW(clc_.adjustClassCount(melon, 1));
    ASSERT_NO_THROW(count = clc_.getClassCount(melon));
    EXPECT_EQ(2, count);

    // Calling adjust() to subtract 1 should work.
    ASSERT_NO_THROW(clc_.adjustClassCount(melon, -1));
    ASSERT_NO_THROW(count = clc_.getClassCount(melon));
    EXPECT_EQ(1, count);

    // Calling adjust() to subtract 2 should not rollover.
    ASSERT_NO_THROW(clc_.adjustClassCount(melon, -2));
    ASSERT_NO_THROW(count = clc_.getClassCount(melon));
    EXPECT_EQ(0, count);

    // Set class value for a new class.
    ASSERT_NO_THROW(clc_.setClassCount(water, 40));
    EXPECT_EQ(2, clc_.size());
    ASSERT_NO_THROW(count = clc_.getClassCount(water));
    EXPECT_EQ(40, count);

    // Should be able to adjust the new class entry.
    ASSERT_NO_THROW(clc_.adjustClassCount(water, -1));
    ASSERT_NO_THROW(count = clc_.getClassCount(water));
    EXPECT_EQ(39, count);
}

// Tests getting and adjusting basic class counts for
// a Lease::TYPE_V4.
TEST_F(ClassLeaseCounterTest, adjustClassCountsTest4) {
    adjustClassCountsTest(Lease::TYPE_V4);
}

// Tests getting and adjusting basic class counts for
// a Lease::TYPE_NA and TYPE_PD.
TEST_F(ClassLeaseCounterTest, adjustClassCountsTest6) {
    adjustClassCountsTest(Lease::TYPE_NA);
    adjustClassCountsTest(Lease::TYPE_PD);
}

// Tests getting and adjusting basic class counts for
// a Lease::TYPE_NA and TYPE_PD.
TEST_F(ClassLeaseCounterTest, basicCountingTests6) {
    // Create test classes.
    ClientClass melon("melon");
    ClientClass water("water");

    // Fetching the count for a non-existent class
    // should return 0.
    ASSERT_EQ(0, clc_.size(Lease::TYPE_NA));
    size_t count;
    ASSERT_NO_THROW(count = clc_.getClassCount(melon, Lease::TYPE_NA));
    EXPECT_EQ(0, count);

    // Calling adjustClassCount() for non-existent class
    // should result in an entry with the adjustment value.
    ASSERT_NO_THROW(clc_.adjustClassCount(melon, 1, Lease::TYPE_NA));
    EXPECT_EQ(1, clc_.size(Lease::TYPE_NA));
    ASSERT_NO_THROW_LOG(count = clc_.getClassCount(melon, Lease::TYPE_NA));
    EXPECT_EQ(1, count);

    // Calling adjust() again to add 1 should work.
    ASSERT_NO_THROW(clc_.adjustClassCount(melon, 1, Lease::TYPE_NA));
    ASSERT_NO_THROW(count = clc_.getClassCount(melon, Lease::TYPE_NA));
    EXPECT_EQ(2, count);

    // Calling adjust() to subtract 1 should work.
    ASSERT_NO_THROW(clc_.adjustClassCount(melon, -1, Lease::TYPE_NA));
    ASSERT_NO_THROW(count = clc_.getClassCount(melon, Lease::TYPE_NA));
    EXPECT_EQ(1, count);

    // Calling adjust() to subtract 2 should not rollover.
    ASSERT_NO_THROW(clc_.adjustClassCount(melon, -2, Lease::TYPE_NA));
    ASSERT_NO_THROW(count = clc_.getClassCount(melon, Lease::TYPE_NA));
    EXPECT_EQ(0, count);

    // Set class value for a new class.
    ASSERT_NO_THROW(clc_.setClassCount(water, 40, Lease::TYPE_NA));
    EXPECT_EQ(2, clc_.size(Lease::TYPE_NA));
    ASSERT_NO_THROW(count = clc_.getClassCount(water, Lease::TYPE_NA));
    EXPECT_EQ(40, count);

    // Should be able to adjust the new class entry.
    ASSERT_NO_THROW(clc_.adjustClassCount(water, -1, Lease::TYPE_NA));
    ASSERT_NO_THROW(count = clc_.getClassCount(water, Lease::TYPE_NA));
    EXPECT_EQ(39, count);

    // Existing class should be able to count prefixes independently.
    ASSERT_NO_THROW(clc_.adjustClassCount(melon, 5, Lease::TYPE_PD));
    EXPECT_EQ(1, clc_.size(Lease::TYPE_PD));
    ASSERT_NO_THROW(count = clc_.getClassCount(melon, Lease::TYPE_PD));
    EXPECT_EQ(5, count);

    // Should be able to adjust the new class prefix entry.
    ASSERT_NO_THROW(clc_.adjustClassCount(melon, -2, Lease::TYPE_PD));
    ASSERT_NO_THROW(count = clc_.getClassCount(melon, Lease::TYPE_PD));
    EXPECT_EQ(3, count);

    // Calling adjust() to subtract 4 should not rollover.
    ASSERT_NO_THROW(clc_.adjustClassCount(melon, -4, Lease::TYPE_PD));
    ASSERT_NO_THROW(count = clc_.getClassCount(melon, Lease::TYPE_PD));
    EXPECT_EQ(0, count);
}

// Exercises ClassLeaseCounter::getLeaseClientClasses()
// No need for v4 and v6 versions of this test, getLeaseClientClasses()
// is not protocol specific.
TEST_F(ClassLeaseCounterTest, getLeaseClientClassesTest) {
    LeasePtr lease;

    // Describes an invalid context scenario, that
    // is expected to cause an exception throw.
    struct InvalidScenario {
        std::string ctx_json_;      // User context contents in JSON form.
        std::string exp_message_;   // Expected exception text.
    };

    // Invalid context scenarios.
    std::list<InvalidScenario> invalid_scenarios {
        {
          " \"bogus\" ",
          "getLeaseClientClasses - invalid context: \"bogus\","
          " find(string) called on a non-map Element in (<string>:1:2)"
        },
        {
            "{\"ISC\": \"bogus\" }",
            "getLeaseClientClasses - invalid context: {\n  \"ISC\": \"bogus\"\n},"
            " find(string) called on a non-map Element in (<string>:1:9)"
        },
        {
            "{\"ISC\": { \"client-classes\": \"bogus\" } }",
            "getLeaseClientClasses - invalid context:"
            " {\n  \"ISC\": {\n    \"client-classes\": \"bogus\"\n  }\n},"
            " client-classes is not a list"
        }
    };

    // Iterate over the invalid scenarios.
    for (auto scenario : invalid_scenarios) {
        // Construct the lease and context.
        lease = leaseFactory(Lease::TYPE_V4);
        ElementPtr ctx;
        ASSERT_NO_THROW(ctx = Element::fromJSON(scenario.ctx_json_))
                        << "test is broken" << scenario.ctx_json_;
        lease->setContext(ctx);

        // Calling getLeaseClientClasses() should throw.
        ASSERT_THROW_MSG(clc_.getLeaseClientClasses(lease), BadValue, scenario.exp_message_);
    }

    // Describes an valid context scenario, that is expected
    // to return normally.
    struct ValidScenario {
        std::string ctx_json_;      // User context contents in JSON form.
        std::string exp_classes_;   // Expected class list in JSON form.
    };

    // Valid scenarios.
    std::list<ValidScenario> valid_scenarios {
        {
            // No context
            "",
            ""
        },
        {
            // No client-classes element
            "{\"ISC\": {} }",
            ""
        },
        {
            // Empty client-classes list
            "{\"ISC\": { \"client-classes\": []} }",
             "[]"
        },
        {
            "{\"ISC\": { \"client-classes\": [ \"one\", \"two\", \"three\" ]} }",
            "[ \"one\", \"two\", \"three\" ]"
        }
    };

    // Iterate over the scenarios.
    for (auto scenario : valid_scenarios) {
        // Construct the lease and context.
        lease = leaseFactory(Lease::TYPE_V4);
        if (!scenario.ctx_json_.empty()) {
            ElementPtr ctx;
            ASSERT_NO_THROW(ctx = Element::fromJSON(scenario.ctx_json_))
                            << "test is broken" << scenario.ctx_json_;
            lease->setContext(ctx);
        }

        // Call getLeaseClientClasses().
        ConstElementPtr classes;
        ASSERT_NO_THROW_LOG(classes = clc_.getLeaseClientClasses(lease));

        // Verify we got the expected outcome for a class list.
        if (scenario.exp_classes_.empty()) {
            ASSERT_FALSE(classes);
        } else {
            ASSERT_TRUE(classes);
            ElementPtr exp_classes;
            ASSERT_NO_THROW(exp_classes = Element::fromJSON(scenario.exp_classes_))
                            << "test is broken" << scenario.exp_classes_;
            EXPECT_EQ(*classes, *exp_classes);
        }
    }
}

TEST_F(ClassLeaseCounterTest, addRemoveLeaseTest4) {
    addAndRemoveLeaseTest(leaseFactory(Lease::TYPE_V4));
}

TEST_F(ClassLeaseCounterTest, addRemoveLeaseTest6_NA) {
    addAndRemoveLeaseTest(leaseFactory(Lease::TYPE_NA));
}

TEST_F(ClassLeaseCounterTest, addRemoveLeaseTest6_PD) {
    addAndRemoveLeaseTest(leaseFactory(Lease::TYPE_PD));
}

TEST_F(ClassLeaseCounterTest, updateLeaseTests4) {
    updateLeaseTests(Lease::TYPE_V4);
}

TEST_F(ClassLeaseCounterTest, updateLeaseTests6_NA) {
    updateLeaseTests(Lease::TYPE_NA);
}

TEST_F(ClassLeaseCounterTest, updateLeaseTests6_PD) {
    updateLeaseTests(Lease::TYPE_PD);
}

}  // namespace
