// Copyright (C) 2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.


#include <config.h>
#include <database/audit_entry.h>
#include <exceptions/exceptions.h>
#include <boost/date_time/posix_time/posix_time.hpp>
#include <boost/make_shared.hpp>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::db;

namespace {

/// @brief Test fixture class for testing @c AuditEntry.
class AuditEntryTest : public ::testing::Test {
public:

    /// @brief Constructor.
    AuditEntryTest()
        : fixed_time_(now()) {
    }

    /// @brief Returns current time.
    static boost::posix_time::ptime now() {
        return (boost::posix_time::microsec_clock::local_time());
    }

    /// @brief Returns always the same time value.
    ///
    /// The value is initialized when the test it started.
    boost::posix_time::ptime fixedTime() const {
        return (fixed_time_);
    }

    /// @brief Checks if the given time value is "close" to the
    /// current time.
    ///
    /// This is useful in tests when the @c AuditEntry class sets the
    /// modification time to a default value (in its constructor).
    /// Because the test doesn't know the exact value to which the
    /// modification time is set, it merely checks that this value
    /// is earlier than current time and within the range of 1s.
    ///
    /// @param t time value to be checked.
    bool almostEqualTime(const boost::posix_time::ptime& t) const {
        auto current = now();

        // The provided value must be a valid time.
        if (t.is_not_a_date_time()) {
            ADD_FAILURE() << "provided value is not a date time";
            return (false);
        }

        // It must be earlier than current time.
        if (t > current) {
            ADD_FAILURE() << "provided time value is later than current time";
            return (false);
        }

        // The difference must be lower than 1 second.
        boost::posix_time::time_duration dur = current - t;
        return (dur.total_milliseconds() < 1000);
    }

    /// @brief Fixed time value initialized in the constructor.
    ///
    /// This is used in tests that require the exact time values.
    boost::posix_time::ptime fixed_time_;
};

// Checks that the modification time value can be cast to a number.
TEST_F(AuditEntryTest, modificationType) {
    EXPECT_EQ(0, static_cast<int>(AuditEntry::ModificationType::CREATE));
    EXPECT_EQ(1, static_cast<int>(AuditEntry::ModificationType::UPDATE));
    EXPECT_EQ(2, static_cast<int>(AuditEntry::ModificationType::DELETE));
}

// Checks that the audit entry can be created.
TEST_F(AuditEntryTest, create) {

    AuditEntryPtr audit_entry;

    {
        SCOPED_TRACE("create with modification time");

        ASSERT_NO_THROW(audit_entry = AuditEntry::create
                        ("dhcp4_subnet", 10, AuditEntry::ModificationType::DELETE,
                         fixedTime(), "deleted subnet 10"));
        EXPECT_EQ("dhcp4_subnet", audit_entry->getObjectType());
        EXPECT_EQ(10, audit_entry->getObjectId());
        EXPECT_EQ(AuditEntry::ModificationType::DELETE, audit_entry->getModificationType());
        EXPECT_EQ(fixedTime(), audit_entry->getModificationTime());
        EXPECT_EQ("deleted subnet 10", audit_entry->getLogMessage());
    }

    {
        SCOPED_TRACE("create with default modification time");

        ASSERT_NO_THROW(audit_entry = AuditEntry::create
                        ("dhcp4_option", 123, AuditEntry::ModificationType::CREATE,
                         ""));
        EXPECT_EQ("dhcp4_option", audit_entry->getObjectType());
        EXPECT_EQ(123, audit_entry->getObjectId());
        EXPECT_EQ(AuditEntry::ModificationType::CREATE, audit_entry->getModificationType());
        EXPECT_TRUE(almostEqualTime(audit_entry->getModificationTime()));
        EXPECT_TRUE(audit_entry->getLogMessage().empty());
    }
}

// Checks that invalid values for the audit entry are rejected.
TEST_F(AuditEntryTest, createFailures) {
    {
        SCOPED_TRACE("empty object type");
        EXPECT_THROW(AuditEntry("", 10, AuditEntry::ModificationType::DELETE,
                                fixedTime(), "deleted subnet 10"),
                     BadValue);
    }

    {
        SCOPED_TRACE("not a date time");
        EXPECT_THROW(AuditEntry("dhcp4_subnet", 10,
                                AuditEntry::ModificationType::DELETE,
                                boost::posix_time::ptime(), "deleted subnet 10"),
                     BadValue);
    }
}

/// @brief Test fixture class for testing @c AuditEntryCollection.
class AuditEntryCollectionTest : public AuditEntryTest {
public:

    /// @brief Constructor.
    ///
    /// Creates a collection of audit entries used in the tests.
    AuditEntryCollectionTest()
        : AuditEntryTest(), audit_entries_() {
        createTestAuditEntries();
    }

    /// @brief Returns a time value being being a specified number of
    /// seconds later or earlier than the time returned by @c fixedTime.
    ///
    /// @param secs offset in seconds since the @c fixedTime output. If
    /// the parameter is negative, the returned time is earlier than the
    /// fixed time. Otherwise, it is later than fixed time.
    boost::posix_time::ptime diffTime(const long secs) {
        if (secs < 0) {
            return (fixedTime() - boost::posix_time::seconds(-secs));
        }
        return (fixedTime() + boost::posix_time::seconds(secs));
    }

    /// @brief Creates an @c AuditEntry instance and inserts it to
    /// the @c audit_entries_ collection.
    ///
    /// @tparam Args types of the arguments to be passed to the @c AuditEntry
    /// constructors.
    /// @param args arguments to be passed to the @c AuditEntry constructors.
    template<typename... Args>
    void create(Args&& ...args) {
        audit_entries_.insert(boost::make_shared<AuditEntry>(args...));
    }

    /// @brief Creates a collection of @c AuditEntry objects to be used by
    /// the tests.
    void createTestAuditEntries() {
        create("dhcp4_subnet", 10, AuditEntry::ModificationType::CREATE,
               diffTime(-5), "added subnet 10");
        create("dhcp4_shared_network", 1, AuditEntry::ModificationType::CREATE,
               diffTime(-5), "added shared network 1");
        create("dhcp4_shared_network", 120, AuditEntry::ModificationType::UPDATE,
               diffTime(-8), "updated shared network 120");
        create("dhcp4_subnet", 120, AuditEntry::ModificationType::DELETE,
               diffTime(8), "deleted subnet 120");
        create("dhcp4_subnet", 1000, AuditEntry::ModificationType::CREATE,
               diffTime(4), "created subnet 1000");
        create("dhcp4_option", 15, AuditEntry::ModificationType::UPDATE,
               diffTime(16), "updated option 15");
    }

    /// @brief Checks if the returned results range contains an @c AuditEntry
    /// with a given object type and identifier.
    ///
    /// @param object_type expected object type.
    /// @param object_id expected object id.
    /// @param begin beginning of the results range to be examined.
    /// @param end end of the results range to be examined.
    template<typename Iterator>
    bool includes(const std::string& object_type, const uint64_t object_id,
                  Iterator begin, Iterator end) {
        // Iterate over the results range and look for the entry.
        for (auto it = begin; it != end; ++it) {
            if (((*it)->getObjectType() == object_type) &&
                ((*it)->getObjectId() == object_id)) {
                // Entry found.
                return (true);
            }
        }

        // Entry not found.
        return (false);
    }

    /// @brief Audit entries used in the tests.
    AuditEntryCollection audit_entries_;

};

// Checks that entries can be found by object type.
TEST_F(AuditEntryCollectionTest, getByObjectType) {
    const auto& object_type_idx = audit_entries_.get<AuditEntryObjectTypeTag>();

    // Search for "dhcp4_subnet" objects.
    auto range = object_type_idx.equal_range("dhcp4_subnet");
    ASSERT_EQ(3, std::distance(range.first, range.second));
    EXPECT_TRUE(includes("dhcp4_subnet", 10, range.first, range.second));
    EXPECT_TRUE(includes("dhcp4_subnet", 120, range.first, range.second));
    EXPECT_TRUE(includes("dhcp4_subnet", 1000, range.first, range.second));

    // Search for "dhcp4_shared_network" objects.
    range = object_type_idx.equal_range("dhcp4_shared_network");
    ASSERT_EQ(2, std::distance(range.first, range.second));
    EXPECT_TRUE(includes("dhcp4_shared_network", 1, range.first, range.second));
    EXPECT_TRUE(includes("dhcp4_shared_network", 120, range.first, range.second));

    // Search for "dhcp4_option" objects.
    range = object_type_idx.equal_range("dhcp4_option");
    ASSERT_EQ(1, std::distance(range.first, range.second));
    EXPECT_TRUE(includes("dhcp4_option", 15, range.first, range.second));
}

// Checks that entries can be found by modification time.
TEST_F(AuditEntryCollectionTest, getByModificationTime) {
    const auto& mod_time_idx = audit_entries_.get<AuditEntryModificationTimeTag>();

    // Search for objects later than fixed time - 10s.
    auto lb = mod_time_idx.lower_bound(diffTime(-10));
    ASSERT_EQ(6, std::distance(lb, mod_time_idx.end()));
    EXPECT_TRUE(includes("dhcp4_subnet", 10, lb, mod_time_idx.end()));
    EXPECT_TRUE(includes("dhcp4_subnet", 120, lb, mod_time_idx.end()));
    EXPECT_TRUE(includes("dhcp4_subnet", 1000, lb, mod_time_idx.end()));
    EXPECT_TRUE(includes("dhcp4_shared_network", 1, lb, mod_time_idx.end()));
    EXPECT_TRUE(includes("dhcp4_shared_network", 120, lb, mod_time_idx.end()));
    EXPECT_TRUE(includes("dhcp4_option", 15, lb, mod_time_idx.end()));

    // Search for objects later than fixed time - 7s.
    lb = mod_time_idx.lower_bound(diffTime(-7));
    ASSERT_EQ(5, std::distance(lb, mod_time_idx.end()));
    EXPECT_TRUE(includes("dhcp4_subnet", 10, lb, mod_time_idx.end()));
    EXPECT_TRUE(includes("dhcp4_subnet", 120, lb, mod_time_idx.end()));
    EXPECT_TRUE(includes("dhcp4_subnet", 1000, lb, mod_time_idx.end()));
    EXPECT_TRUE(includes("dhcp4_shared_network", 1, lb, mod_time_idx.end()));
    EXPECT_TRUE(includes("dhcp4_option", 15, lb, mod_time_idx.end()));

    // Search for objects later than fixed time - 1s.
    lb = mod_time_idx.lower_bound(diffTime(-1));
    ASSERT_EQ(3, std::distance(lb, mod_time_idx.end()));
    EXPECT_TRUE(includes("dhcp4_subnet", 120, lb, mod_time_idx.end()));
    EXPECT_TRUE(includes("dhcp4_subnet", 1000, lb, mod_time_idx.end()));
    EXPECT_TRUE(includes("dhcp4_option", 15, lb, mod_time_idx.end()));

    // Search for objects later than fixed time + 6s.
    lb = mod_time_idx.lower_bound(diffTime(6));
    ASSERT_EQ(2, std::distance(lb, mod_time_idx.end()));
    EXPECT_TRUE(includes("dhcp4_subnet", 120, lb, mod_time_idx.end()));
    EXPECT_TRUE(includes("dhcp4_option", 15, lb, mod_time_idx.end()));

    // Search for objects later than fixed time + 10s.
    lb = mod_time_idx.lower_bound(diffTime(10));
    ASSERT_EQ(1, std::distance(lb, mod_time_idx.end()));
    EXPECT_TRUE(includes("dhcp4_option", 15, lb, mod_time_idx.end()));

    // Search for objects later than fixed time + 20s.
    lb = mod_time_idx.lower_bound(diffTime(20));
    // None found.
    ASSERT_EQ(0, std::distance(lb, mod_time_idx.end()));
}

}
