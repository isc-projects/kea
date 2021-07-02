// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <pgsql_cb_impl.h>
#include <gtest/gtest.h>
#include <dhcpsrv/testutils/pgsql_generic_backend_unittest.h>
#include <vector>

using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::dhcp::test;

namespace {

typedef PsqlBindArrayPtr (tripletFunc) (const Triplet<uint32_t>& triplet);

class PgsqlConfigBackendTest: public PgSqlGenericBackendTest {
public:
    PgsqlConfigBackendTest(): PgSqlGenericBackendTest() {
        DatabaseConnection::ParameterMap params;
        params["name"] = "keatest";
        params["password"] = "keatest";
        params["user"] = "keatest";

        cbptr_.reset(new PgSqlConfigBackendImpl(params, 0));

    }

    /// @brief checks if specified triplet generating function stores the values properly.
    ///
    /// @param f function pointer to a function that converts triplet to PgSqlBindArray
    /// @param t triplet to be converted
    /// @param exp expected value or values
    void checkBinding(tripletFunc f, Triplet<uint32_t> t, std::vector<uint32_t> exp) {
        PsqlBindArrayPtr binding = f(t);

        // Special case: empty binding
        if (exp.empty()) {
            // Binding should have one field that is set to null value.
            ASSERT_TRUE(binding);
            EXPECT_TRUE(binding->amNull());
            return;
        }

        // Let's check if the size of the binding equals expectations
        ASSERT_EQ(binding->size(), exp.size());

        for (int i = 0; i < exp.size(); i++) {
            // The field should not be empty
            ASSERT_FALSE(binding->amNull(i));

            // The field should have a type set to text (Postgres stores integers as text)
            EXPECT_EQ(PsqlBindArray::TEXT_FMT, binding->getType(i));

            // Check that the correct value was stored in the binding.
            EXPECT_EQ(exp[i], binding->getInteger<uint32_t>(i));
        }
    }

    boost::shared_ptr<PgSqlConfigBackendImpl> cbptr_;
};

// Let's start with absolute basics. Is this the right type?
TEST_F(PgsqlConfigBackendTest, triplet) {
    EXPECT_EQ("pgsql", cbptr_->getType());
}

// Test that the Postgres binding can be created from a triplet.
// the createBinding function takes the default value of a triplet.
TEST_F(PgsqlConfigBackendTest, createBinding) {

    tripletFunc &f = PgSqlConfigBackendImpl::createBinding;
    std::vector<uint32_t> exp;

    // Case 1: empty triplet creates empty binding
    checkBinding(f, Triplet<uint32_t>(), exp);

    // Case 2: triplet with just one value should create a single entry with that value
    exp.push_back(222);
    checkBinding(f, Triplet<uint32_t>(222), exp);

    // Case 3: an actual triplet with 3 values should create a single entry with the
    // default (middle) value
    checkBinding(f, Triplet<uint32_t>(111, 222, 333), exp);
}

// Test that the Postgres binding can be created from a triplet.
// the createBinding function takes the default value of a triplet.
TEST_F(PgsqlConfigBackendTest, createMinBinding) {

    tripletFunc &f = PgSqlConfigBackendImpl::createMinBinding;
    std::vector<uint32_t> exp;

    // Case 1: empty triplet creates empty binding
    checkBinding(f, Triplet<uint32_t>(), exp);

    // Case 2: triplet with just one value should not generate min binding
    //         (the value is supposed to be used in default binding)
    checkBinding(f, Triplet<uint32_t>(111), exp);

    // Case 3: an actual triplet with 3 values should create a single entry with the
    // min (first) value
    exp.push_back(111);
    checkBinding(f, Triplet<uint32_t>(111, 222, 333), exp);
}

// Test that the Postgres binding can be created from a triplet.
// the createBinding function takes the default value of a triplet.
TEST_F(PgsqlConfigBackendTest, createMaxBinding) {

    tripletFunc &f = PgSqlConfigBackendImpl::createMaxBinding;
    std::vector<uint32_t> exp;

    // Case 1: empty triplet creates empty binding
    checkBinding(f, Triplet<uint32_t>(), exp);

    // Case 2: triplet with just one value should not generate max binding
    //         (the value is supposed to be used in default binding)
    checkBinding(f, Triplet<uint32_t>(333), exp);

    // Case 3: an actual triplet with 3 values should create a single entry with the
    // max (third) value
    exp.push_back(333);
    checkBinding(f, Triplet<uint32_t>(111, 222, 333), exp);
}


}
