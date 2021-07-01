// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <pgsql_cb_impl.h>
#include <gtest/gtest.h>

using namespace isc::db;
using namespace isc::dhcp;

namespace {

// Test that the Postgres binding can be created from a triplet.
TEST(PgSqlConfigBackendImplTest, createBindingFromTriplet) {
    // Create a binding from an unspecified triplet.
    auto binding = PgSqlConfigBackendImpl::createBinding(Triplet<uint32_t>());
    // The binding pointer should be non-null but the type of the binding
    // should be null.
    ASSERT_TRUE(binding);
    EXPECT_TRUE(binding->amNull());

    // This time create a triplet encapsulating a number.
    binding = PgSqlConfigBackendImpl::createBinding(Triplet<uint32_t>(123));
    ASSERT_TRUE(binding);
    // The binding type should be non-null.
    ASSERT_FALSE(binding->amNull());
    ASSERT_EQ(PsqlBindArray::TEXT_FMT, binding->getType());
    // Check that the correct value was stored in the binding.
    EXPECT_EQ(123, binding->getInteger<uint32_t>(0));
}

}
