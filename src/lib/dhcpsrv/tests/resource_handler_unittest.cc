// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <dhcpsrv/resource_handler.h>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;

namespace {

// Verifies behavior with empty block.
TEST(ResourceHandleTest, empty) {
    try {
        // Get a resource handler.
        ResourceHandler resource_handler;
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

// Verifies behavior with empty block (v4).
TEST(ResourceHandleTest, empty4) {
    try {
        // Get a resource handler.
        ResourceHandler4 resource_handler;
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

// Verifies behavior with one handler.
TEST(ResourceHandleTest, one) {
    IOAddress addr("2001:db8::1");

    try {
        // Get a resource handler.
        ResourceHandler resource_handler;

        // Try to lock it.
        bool busy = false;
        EXPECT_NO_THROW(busy = !resource_handler.tryLock(Lease::TYPE_NA, addr));

        // Should return false (free).
        EXPECT_FALSE(busy);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

// Verifies behavior with one IPv4 handler.
TEST(ResourceHandleTest, one4) {
    IOAddress addr("192.0.2.1");

    try {
        // Get a resource handler.
        ResourceHandler4 resource_handler;

        // Try to lock it.
        bool busy = false;
        EXPECT_NO_THROW(busy = !resource_handler.tryLock4(addr));

        // Should return false (free).
        EXPECT_FALSE(busy);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

// Verifies behavior with two handlers.
TEST(ResourceHandleTest, two) {
    IOAddress addr("2001:db8::");

    try {
        // Get a resource handler.
        ResourceHandler resource_handler;

        // Try to lock it.
        bool busy = false;
        EXPECT_NO_THROW(busy = !resource_handler.tryLock(Lease::TYPE_PD, addr));

        // Should return false (free).
        EXPECT_FALSE(busy);

        // Get a second resource handler.
        ResourceHandler resource_handler2;

        // Try to lock it.
        EXPECT_NO_THROW(busy = !resource_handler2.tryLock(Lease::TYPE_PD, addr));

        // Should return true (busy);
        EXPECT_TRUE(busy);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

// Verifies behavior with two IPv4 handlers.
TEST(ResourceHandleTest, two4) {
    IOAddress addr("192.0.2.1");

    try {
        // Get a resource handler.
        ResourceHandler4 resource_handler;

        // Try to lock it.
        bool busy = false;
        EXPECT_NO_THROW(busy = !resource_handler.tryLock4(addr));

        // Should return false (free).
        EXPECT_FALSE(busy);

        // Get a second resource handler.
        ResourceHandler4 resource_handler2;

        // Try to lock it.
        EXPECT_NO_THROW(busy = !resource_handler2.tryLock4(addr));

        // Should return true (busy);
        EXPECT_TRUE(busy);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

// Verifies behavior with two handlers in different blocks (sequence).
TEST(ResourceHandleTest, sequence) {
    IOAddress addr("2001:db8::1");

    try {
        // Get a resource handler.
        ResourceHandler resource_handler;

        // Try to lock it.
        bool busy = false;
        EXPECT_NO_THROW(busy = !resource_handler.tryLock(Lease::TYPE_NA, addr));

        // Should return false (free).
        EXPECT_FALSE(busy);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }

    try {
        // Get a second resource handler.
        ResourceHandler resource_handler2;

        // Try to lock it.
        bool busy = false;
        EXPECT_NO_THROW(busy = !resource_handler2.tryLock(Lease::TYPE_NA, addr));

        // Should return false (free)
        EXPECT_FALSE(busy);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

// Verifies behavior with two IPv4 handlers in different blocks (sequence).
TEST(ResourceHandleTest, sequence4) {
    IOAddress addr("192.0.2.1");

    try {
        // Get a resource handler.
        ResourceHandler4 resource_handler;

        // Try to lock it.
        bool busy = false;
        EXPECT_NO_THROW(busy = !resource_handler.tryLock4(addr));

        // Should return false (free).
        EXPECT_FALSE(busy);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }

    try {
        // Get a second resource handler.
        ResourceHandler4 resource_handler2;

        // Try to lock it.
        bool busy = false;
        EXPECT_NO_THROW(busy = !resource_handler2.tryLock4(addr));

        // Should return false (free)
        EXPECT_FALSE(busy);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

// Verifies behavior with two handlers for different addresses.
TEST(ResourceHandleTest, differentAddress) {
    IOAddress addr("2001:db8::1");
    IOAddress addr2("2001:db8::2");

    try {
        // Get a resource handler.
        ResourceHandler resource_handler;

        // Try to lock it.
        bool busy = false;
        EXPECT_NO_THROW(busy = !resource_handler.tryLock(Lease::TYPE_NA, addr));

        // Should return false (free).
        EXPECT_FALSE(busy);

        // Get a second resource handler.
        ResourceHandler resource_handler2;

        // Try to lock it.
        EXPECT_NO_THROW(busy = !resource_handler2.tryLock(Lease::TYPE_NA, addr2));

        // Should return false (free).
        EXPECT_FALSE(busy);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

// Verifies behavior with two IPv4 handlers for different addresses.
TEST(ResourceHandleTest, differentAddress4) {
    IOAddress addr("192.0.2.1");
    IOAddress addr2("192.0.2.2");

    try {
        // Get a resource handler.
        ResourceHandler4 resource_handler;

        // Try to lock it.
        bool busy = false;
        EXPECT_NO_THROW(busy = !resource_handler.tryLock4(addr));

        // Should return false (free).
        EXPECT_FALSE(busy);

        // Get a second resource handler.
        ResourceHandler4 resource_handler2;

        // Try to lock it.
        EXPECT_NO_THROW(busy = !resource_handler2.tryLock4(addr2));

        // Should return false (free).
        EXPECT_FALSE(busy);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

// Verifies behavior with two handlers for different types.
TEST(ResourceHandleTest, differentTypes) {
    IOAddress addr("2001:db8::");

    try {
        // Get a resource handler.
        ResourceHandler resource_handler;

        // Try to lock it.
        bool busy = false;
        EXPECT_NO_THROW(busy = !resource_handler.tryLock(Lease::TYPE_NA, addr));

        // Should return false (free).
        EXPECT_FALSE(busy);

        // Get a second resource handler.
        ResourceHandler resource_handler2;

        // Try to lock it.
        EXPECT_NO_THROW(busy = !resource_handler2.tryLock(Lease::TYPE_PD, addr));

        // Should return false (free).
        EXPECT_FALSE(busy);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

// Verifies behavior of the isLocked predicate.
TEST(ResourceHandleTest, isLocked) {
    IOAddress addr("2001:db8::1");
    IOAddress addr2("2001:db8::2");
    IOAddress addr3("2001:db8::3");

    try {
        // Get a resource handler.
        ResourceHandler resource_handler;

        // Try to lock it.
        bool busy = false;
        EXPECT_NO_THROW(busy = !resource_handler.tryLock(Lease::TYPE_NA, addr));

        // Should return false (free).
        EXPECT_FALSE(busy);

        // Get a second resource handler.
        ResourceHandler resource_handler2;

        // Try to lock it.
        EXPECT_NO_THROW(busy = !resource_handler2.tryLock(Lease::TYPE_NA, addr2));

        // Should return false (free).
        EXPECT_FALSE(busy);

        // Check ownership.
        EXPECT_TRUE(resource_handler.isLocked(Lease::TYPE_NA, addr));
        EXPECT_FALSE(resource_handler.isLocked(Lease::TYPE_NA, addr2));
        EXPECT_FALSE(resource_handler.isLocked(Lease::TYPE_NA, addr3));
        EXPECT_FALSE(resource_handler.isLocked(Lease::TYPE_PD, addr));
        EXPECT_FALSE(resource_handler2.isLocked(Lease::TYPE_NA, addr));
        EXPECT_TRUE(resource_handler2.isLocked(Lease::TYPE_NA, addr2));
        EXPECT_FALSE(resource_handler2.isLocked(Lease::TYPE_NA, addr3));
        EXPECT_FALSE(resource_handler2.isLocked(Lease::TYPE_PD, addr2));
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

// Verifies behavior with two IPv4 handlers.
TEST(ResourceHandleTest, isLocked4) {
    IOAddress addr("192.0.2.1");
    IOAddress addr2("192.0.2.2");
    IOAddress addr3("192.0.2.3");

    try {
        // Get a resource handler.
        ResourceHandler4 resource_handler;

        // Try to lock it.
        bool busy = false;
        EXPECT_NO_THROW(busy = !resource_handler.tryLock4(addr));

        // Should return false (free).
        EXPECT_FALSE(busy);

        // Get a second resource handler.
        ResourceHandler4 resource_handler2;

        // Try to lock it.
        EXPECT_NO_THROW(busy = !resource_handler2.tryLock4(addr2));

        // Should return false (free).
        EXPECT_FALSE(busy);

        // Check ownership.
        EXPECT_TRUE(resource_handler.isLocked4(addr));
        EXPECT_FALSE(resource_handler.isLocked4(addr2));
        EXPECT_FALSE(resource_handler.isLocked4(addr3));
        EXPECT_FALSE(resource_handler2.isLocked4(addr));
        EXPECT_TRUE(resource_handler2.isLocked4(addr2));
        EXPECT_FALSE(resource_handler2.isLocked4(addr3));

        // ResourceHandler4 derives from ResourceHandler.
        EXPECT_FALSE(resource_handler.isLocked(Lease::TYPE_NA, addr));
        EXPECT_FALSE(resource_handler2.isLocked(Lease::TYPE_NA, addr2));
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

// Verifies that double tryLock call for the same resource returns busy.
TEST(ResourceHandleTest, doubleTryLock) {
    IOAddress addr("2001:db8::");

    try {
        // Get a resource handler.
        ResourceHandler resource_handler;

        // Try to lock it.
        bool busy = false;
        EXPECT_NO_THROW(busy = !resource_handler.tryLock(Lease::TYPE_PD, addr));

        // Should return false (free).
        EXPECT_FALSE(busy);

        // Try to lock it again.
        EXPECT_NO_THROW(busy = !resource_handler.tryLock(Lease::TYPE_PD, addr));

        // Should return true (busy);
        EXPECT_TRUE(busy);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

// Verifies that double tryLock call for the same resource returns busy (v4).
TEST(ResourceHandleTest, doubleTryLock4) {
    IOAddress addr("192.0.2.1");

    try {
        // Get a resource handler.
        ResourceHandler4 resource_handler;

        // Try to lock it.
        bool busy = false;
        EXPECT_NO_THROW(busy = !resource_handler.tryLock4(addr));

        // Should return false (free).
        EXPECT_FALSE(busy);

        // Try to lock it again.
        EXPECT_NO_THROW(busy = !resource_handler.tryLock4(addr));

        // Should return true (busy);
        EXPECT_TRUE(busy);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

// Verifies behavior of the unLock method.
TEST(ResourceHandleTest, unLock) {
    IOAddress addr("2001:db8::1");

    try {
        // Get a resource handler.
        ResourceHandler resource_handler;

        // Try to lock it.
        bool busy = false;
        EXPECT_NO_THROW(busy = !resource_handler.tryLock(Lease::TYPE_NA, addr));

        // Should return false (free).
        EXPECT_FALSE(busy);

        // The resource is owned by us.
        EXPECT_TRUE(resource_handler.isLocked(Lease::TYPE_NA, addr));

        // Try to unlock it.
        EXPECT_NO_THROW(resource_handler.unLock(Lease::TYPE_NA, addr));

        // The resource is no longer owned by us.
        EXPECT_FALSE(resource_handler.isLocked(Lease::TYPE_NA, addr));

        // Get a second resource handler.
        ResourceHandler resource_handler2;

        // Try to lock it by the second handler.
        EXPECT_NO_THROW(busy = !resource_handler2.tryLock(Lease::TYPE_NA, addr));

        // Should return false (free).
        EXPECT_FALSE(busy);

        // The resource is owned by the second handler.
        EXPECT_FALSE(resource_handler.isLocked(Lease::TYPE_NA, addr));
        EXPECT_TRUE(resource_handler2.isLocked(Lease::TYPE_NA, addr));

        // Only the owner is allowed to release a resource.
        EXPECT_THROW(resource_handler.unLock(Lease::TYPE_NA, addr), NotFound);
        EXPECT_NO_THROW(resource_handler2.unLock(Lease::TYPE_NA, addr));
        // Once.
        EXPECT_THROW(resource_handler2.unLock(Lease::TYPE_NA, addr), NotFound);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

// Verifies behavior of the unLock method.
TEST(ResourceHandleTest, unLock4) {
    IOAddress addr("192.0.2.1");

    try {
        // Get a resource handler.
        ResourceHandler4 resource_handler;

        // Try to lock it.
        bool busy = false;
        EXPECT_NO_THROW(busy = !resource_handler.tryLock4(addr));

        // Should return false (free).
        EXPECT_FALSE(busy);

        // The resource is owned by us.
        EXPECT_TRUE(resource_handler.isLocked4(addr));

        // Try to unlock it.
        EXPECT_NO_THROW(resource_handler.unLock4(addr));

        // The resource is no longer owned by us.
        EXPECT_FALSE(resource_handler.isLocked4(addr));

        // Get a second resource handler
        ResourceHandler4 resource_handler2;

        // Try to lock it by the second handler.
        EXPECT_NO_THROW(busy = !resource_handler2.tryLock4(addr));

        // Should return false (free).
        EXPECT_FALSE(busy);

        // The resource is owned by the second handler.
        EXPECT_FALSE(resource_handler.isLocked4(addr));
        EXPECT_TRUE(resource_handler2.isLocked4(addr));

        // Only the owner is allowed to release a resource.
        EXPECT_THROW(resource_handler.unLock4(addr), NotFound);
        EXPECT_NO_THROW(resource_handler2.unLock4(addr));
        // Once.
        EXPECT_THROW(resource_handler2.unLock4(addr), NotFound);
    } catch (const std::exception& ex) {
        ADD_FAILURE() << "unexpected exception: " << ex.what();
    }
}

} // end of anonymous namespace
