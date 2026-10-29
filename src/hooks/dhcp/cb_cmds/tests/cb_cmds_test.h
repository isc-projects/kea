// Copyright (C) 2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CB_CMDS_TEST_H
#define CB_CMDS_TEST_H

#include <test_cb_cmds_impl.h>
#include <cc/stamped_element.h>
#include <dhcpsrv/config_backend_dhcp4_mgr.h>
#include <dhcpsrv/config_backend_dhcp6_mgr.h>
#include <dhcpsrv/testutils/test_config_backend_dhcp4.h>
#include <dhcpsrv/testutils/test_config_backend_dhcp6.h>
#include <gtest/gtest.h>
#include <set>
#include <string>

namespace isc {
namespace cb {
namespace test {

/// @brief Template to derive ConfigCmdsDhcp[46]Test for testing
/// cb_cmds hooks library.
///
/// @tparam TestConfigCmdsDhcpXImpl Either @c TestConfigCmdsDhcp4Impl or
/// @c TestConfigCmdsDhcp6Impl.
/// @tparam ConfigBackendMgr Either @c ConfigBackendDHCPv4Mgr or
/// @c ConfigBackendDHCPv6Mgr.
/// @tparam TestConfigBackendDHCPvX Either @c TestConfigBackendDHCPv4
/// or @c TestConfigBackendDHCPv6.
template <typename TestConfigCmdsDhcpXImpl, typename ConfigBackendMgr,
    typename TestConfigBackendDHCPvX>
class ConfigCmdsDhcpXTest : public ::testing::Test {
public:

    /// @brief Constructor.
    ConfigCmdsDhcpXTest() : impl_() {
        /// @todo Register the test backend under "mysql" type for now,
        /// because the BackendSelector requires that it has a known type.
        /// We should later modify the BackendSelector to allow custom types
        /// of backends. In that case we will change "mysql" to "dhcp4-test"
        /// here.
        ConfigBackendMgr::instance().registerBackendFactory("mysql",
            [](const db::DatabaseConnection::ParameterMap& parameter_map) {
            return (boost::shared_ptr<TestConfigBackendDHCPvX>(new TestConfigBackendDHCPvX(parameter_map)));
        });

        ConfigBackendMgr::instance().addBackend("type=mysql");
    }

    /// @brief Destructor.
    virtual ~ConfigCmdsDhcpXTest() {
        ConfigBackendMgr::instance().delAllBackends();
        ConfigBackendMgr::instance().unregisterBackendFactory("mysql");
    }

    /// @brief Returns metadata from server tag.
    ///
    /// @param server_tag server tag.
    data::ElementPtr createMetadata(const std::string& server_tag) {
        data::StampedElement element;
        element.setServerTag(server_tag);
        return (element.getMetadata());
    }

    /// @brief Returns metadata from server tags.
    ///
    /// @param server_tags server tags.
    data::ElementPtr createMetadata(const std::set<std::string>& server_tags) {
        data::StampedElement element;
        for (auto const& server_tag : server_tags) {
            element.setServerTag(server_tag);
        }
        return (element.getMetadata());
    }

    /// @brief Checks option info from response against an OptionDescriptr.
    ///
    /// @param info option information to verify.
    /// @param desc OptionDescriptor with the expected option information.
    void checkOptionInfo(data::ConstElementPtr info, const OptionDescriptor& desc) {
        ASSERT_TRUE(info);
        ASSERT_EQ(data::Element::map, info->getType());

        auto info_code = info->get("code");
        ASSERT_TRUE(info_code);
        ASSERT_EQ(data::Element::integer, info_code->getType());
        EXPECT_EQ(static_cast<int64_t>(desc.option_->getType()),
                  info_code->intValue());

        auto info_space = info->get("space");
        ASSERT_TRUE(info_space);
        ASSERT_EQ(data::Element::string, info_space->getType());
        EXPECT_EQ(desc.space_name_, info_space->stringValue());

        auto info_classes = info->get("client-classes");
        if (desc.client_classes_.empty()) {
            EXPECT_EQ(2U, info->size());
            ASSERT_FALSE(info_classes);
        } else {
            EXPECT_EQ(3U, info->size());
            ASSERT_TRUE(info_classes);
            ASSERT_EQ(data::Element::list, info_classes->getType());
            EXPECT_EQ(*desc.client_classes_.toElement(),
                      *info_classes);
        }
    }

    TestConfigCmdsDhcpXImpl impl_;
};

/// @brief Base class for testing cb_cmds hooks library.
using ConfigCmdsDhcp4Test = ConfigCmdsDhcpXTest<TestConfigCmdsDhcp4Impl,
    dhcp::ConfigBackendDHCPv4Mgr, dhcp::test::TestConfigBackendDHCPv4>;

/// @brief Base class for testing cb_cmds hooks library.
using ConfigCmdsDhcp6Test = ConfigCmdsDhcpXTest<TestConfigCmdsDhcp6Impl,
    dhcp::ConfigBackendDHCPv6Mgr, dhcp::test::TestConfigBackendDHCPv6>;

} // end of namespace isc::cb::test
} // end of namespace isc::cb
} // end of namespace isc

#endif // CB_CMDS_TEST_H
