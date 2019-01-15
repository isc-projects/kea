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
        return (boost::posix_time::microsec_clock::universal_time());
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

        ASSERT_NO_THROW(audit_entry = boost::make_shared<AuditEntry>
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

        ASSERT_NO_THROW(audit_entry = boost::make_shared<AuditEntry>
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

}
