// Copyright (C) 2014 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

/// @file d2_unittest.h Defines classes for testing Dhcpv4srv with D2ClientMgr

#ifndef D2_UNITTEST_H
#define D2_UNITTEST_H

#include <dhcp4/dhcp4_srv.h>
#include <cc/command_interpreter.h>

#include <gtest/gtest.h>

namespace isc {
namespace dhcp {
namespace test {

/// @brief Test derivation of Dhcpv4Srv class used in D2 testing.
/// Use of this class allows the intervention at strategic points in testing
/// by permitting overridden methods and access to scope protected members.
class D2Dhcpv4Srv : public  Dhcpv4Srv {
public:
    /// @brief Counts the number of times the client error handler is called.
    int error_count_;

    /// @brief Constructor
    D2Dhcpv4Srv()
        : Dhcpv4Srv(0, false, false), error_count_(0) {
    }

    /// @brief virtual Destructor.
    virtual ~D2Dhcpv4Srv() {
    }

    /// @brief Override the error handler.
    virtual void d2ClientErrorHandler(const dhcp_ddns::NameChangeSender::
                                      Result result,
                                      dhcp_ddns::NameChangeRequestPtr& ncr);
};

/// @brief Test fixture which permits testing the interaction between the
/// D2ClientMgr and Dhcpv4Srv.
class Dhcp4SrvD2Test : public ::testing::Test {
public:
    /// @brief Mnemonic constants for calls to configuration methods.
    static const bool SHOULD_PASS = true;
    static const bool SHOULD_FAIL = false;

    /// @brief Constructor
    Dhcp4SrvD2Test();

    /// @brief virtual Destructor
    virtual ~Dhcp4SrvD2Test();

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
    /// @param exp_result indicates if configuration should pass or fail
    /// @param server_ip IP address for the D2 server
    /// @param port  port for the D2 server
    /// @param sender_ip NCR sender's IP address
    /// @param sender_port NCR sender port
    /// @param max_queue_size maximum number of NCRs allowed in sender's queue
    void configureD2(bool enable_updates, bool exp_result = SHOULD_PASS,
                     const std::string& server_ip = "127.0.0.1",
                     const size_t port = 53001,
                     const std::string& sender_ip = "0.0.0.0",
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
    D2Dhcpv4Srv srv_;
};

}; // end of isc::dhcp::test namespace
}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // D2_UNITTEST_H
