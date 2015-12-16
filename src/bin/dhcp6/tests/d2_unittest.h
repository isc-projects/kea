// Copyright (C) 2014-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file d2_unittest.h Defines classes for testing Dhcpv6srv with D2ClientMgr

#ifndef D2_UNITTEST_H
#define D2_UNITTEST_H

#include <dhcp6/dhcp6_srv.h>
#include <cc/command_interpreter.h>

#include <gtest/gtest.h>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Test derivation of Dhcpv6Srv class used in D2 testing.
/// Use of this class allows the intervention at strategic points in testing
/// by permitting overridden methods and access to scope protected members.
class D2Dhcpv6Srv : public  Dhcpv6Srv {
public:
    /// @brief Counts the number of times the client error handler is called.
    int error_count_;

    /// @brief Constructor
    D2Dhcpv6Srv()
        : Dhcpv6Srv(0), error_count_(0) {
    }

    /// @brief virtual Destructor.
    virtual ~D2Dhcpv6Srv() {
    }

    /// @brief Override the error handler.
    virtual void d2ClientErrorHandler(const dhcp_ddns::NameChangeSender::
                                      Result result,
                                      dhcp_ddns::NameChangeRequestPtr& ncr);
};

/// @brief Test fixture which permits testing the interaction between the
/// D2ClientMgr and Dhcpv6Srv.
class Dhcp6SrvD2Test : public ::testing::Test {
public:
    /// @brief Mnemonic constants for calls to configuration methods.
    static const bool SHOULD_PASS = true;
    static const bool SHOULD_FAIL = false;

    /// @brief Constructor
    Dhcp6SrvD2Test();

    /// @brief virtual Destructor
    virtual ~Dhcp6SrvD2Test();

    /// @brief Resets the CfgMgr singleton to defaults.
    /// Primarily used in the test destructor as gtest doesn't exit between
    /// tests.
    /// @todo CfgMgr should provide a method to reset everything or maybe
    /// reconstruct the singleton.
    void reset();

    /// @brief Configures the server with D2 enabled or disabled
    ///
    /// Constructs a configuration string including dhcp-ddns with the
    /// parameters given and passes it into the server's configuration handler.
    ///
    /// @param enable_updates value to assign to the enable-updates parameter
    /// @param server_ip IP address for the D2 server
    /// @param port  port for the D2 server
    /// @param sender_ip NCR sender's IP address
    /// @param sender_port NCR sender port
    /// @param max_queue_size maximum number of NCRs allowed in sender's queue
    void configureD2(bool enable_updates, bool exp_result = SHOULD_PASS,
                     const std::string& server_ip = "::1",
                     const size_t port = 53001,
                     const std::string& sender_ip = "::",
                     const size_t sender_port = 0,
                     const size_t max_queue_size = 1024);

    /// @brief Configures the server with the given configuration
    ///
    /// Passes the given configuration string into the server's configuration
    /// handler.  It accepts a flag indicating whether or not the configuration
    /// is expected to succeed or fail.  This permits testing the server's
    /// response to both valid and invalid configurations.
    ///
    /// @param config JSON string containing the configuration
    /// @param exp_result indicates if configuration should pass or fail
    void configure(const std::string& config, bool exp_result = SHOULD_PASS);

    /// @brief Constructs a NameChangeRequest message from a fixed JSON string.
    ///
    /// @param dhcid_id_num Integer value to use as the DHCID.
    dhcp_ddns::NameChangeRequestPtr buildTestNcr(uint32_t
                                                 dhcid_id_num = 0xdeadbeef);

    /// @brief Stores the return code of the last configuration attempt.
    int rcode_;

    /// @brief Stores the message component of the last configuration attempt.
    isc::data::ConstElementPtr comment_;

    /// @brief Server object under test.
    D2Dhcpv6Srv srv_;
};

}; // end of isc::dhcp::test namespace
}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // D2_UNITTEST_H
