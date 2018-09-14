// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <mysql_cb_dhcp4.h>
#include <mysql/testutils/mysql_schema.h>
#include <gtest/gtest.h>

using namespace isc::db;
using namespace isc::db::test;
using namespace isc::dhcp;

namespace {

class MySqlConfigBackendDHCPv4Test : public ::testing::Test {
public:

    MySqlConfigBackendDHCPv4Test() {
        destroyMySQLSchema();
        createMySQLSchema();

        try {
            DatabaseConnection::ParameterMap params =
                DatabaseConnection::parse(validMySQLConnectionString());
            cbptr_.reset(new MySqlConfigBackendDHCPv4(params));

        } catch (...) {
            std::cerr << "*** ERROR: unable to open database. The test\n"
                         "*** environment is broken and must be fixed before\n"
                         "*** the MySQL tests will run correctly.\n"
                         "*** The reason for the problem is described in the\n"
                         "*** accompanying exception output.\n";
            throw;
        }
    }

    virtual ~MySqlConfigBackendDHCPv4Test() {
        cbptr_.reset();
        destroyMySQLSchema();
    }

    MySqlConfigBackendDHCPv4Ptr cbptr_;
};

TEST_F(MySqlConfigBackendDHCPv4Test, getSubnet4) {
    cbptr_->getSubnet4(ServerSelector::UNASSIGNED(), SubnetID(1));
}


}
