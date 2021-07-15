// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef SYSREPO_SETUP_H
#define SYSREPO_SETUP_H

#include <config.h>

#include <testutils/gtest_utils.h>
#include <yang/translator.h>
#include <yang/yang_models.h>

#include <gtest/gtest.h>

namespace isc {
namespace yang {
namespace test {

struct SysrepoSetup {
    static void cleanSharedMemory() {
        system("rm -rf /dev/shm/sr_*");
        system("rm -rf /dev/shm/srsub_*");
    }
};

/// @brief Test Fixture template for translator tests.
///
/// @tparam Name The name of the translator to test.
/// @tparam Type The type of the translator to test.
template<char const* Name, typename translator_t>
class GenericTranslatorTest : public ::testing::Test {
public:
    virtual ~GenericTranslatorTest() = default;

    void SetUp() override {
        SysrepoSetup::cleanSharedMemory();
        conn_.reset(new sysrepo::Connection());
        sess_.reset(new sysrepo::Session(conn_, SR_DS_CANDIDATE));
        t_obj_.reset(new translator_t(sess_, model_));
        cleanModelData();
    }

    void TearDown() override {
        cleanModelData();
        t_obj_.reset();
        sess_.reset();
        conn_.reset();
        SysrepoSetup::cleanSharedMemory();
    }

    void cleanModelData() {
        std::string toplevel_node("config");
        if (model_ == IETF_DHCPV6_SERVER) {
            toplevel_node = "server";
        }
        t_obj_->delItem("/" + model_ + ":" + toplevel_node);
    }

    /// @brief Sysrepo connection.
    sysrepo::S_Connection conn_;

    /// @brief Sysrepo session.
    sysrepo::S_Session sess_;

    /// @brief Shared pointer to the transaction object.
    boost::shared_ptr<translator_t> t_obj_;
    std::string model_;
};

} // namespace test
} // namespace yang
} // namespace isc

#endif // SYSREPO_SETUP_H
