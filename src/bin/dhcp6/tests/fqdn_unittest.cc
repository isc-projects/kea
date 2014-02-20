// Copyright (C) 2013-2014  Internet Systems Consortium, Inc. ("ISC")
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

#include <config.h>

#include <asiolink/io_address.h>
#include <dhcp_ddns/ncr_msg.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/option_custom.h>
#include <dhcp/option6_client_fqdn.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>
#include <dhcp/option_int_array.h>
#include <dhcpsrv/lease.h>

#include <dhcp6/tests/dhcp6_test_utils.h>
#include <boost/pointer_cast.hpp>
#include <gtest/gtest.h>

using namespace isc;
using namespace isc::test;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp_ddns;
using namespace isc::util;
using namespace isc::hooks;
using namespace std;

namespace {

/// @brief A test fixture class for testing DHCPv6 Client FQDN Option handling.
class FqdnDhcpv6SrvTest : public Dhcpv6SrvTest {
public:
    /// Pointer to Dhcpv6Srv that is used in tests
    boost::scoped_ptr<NakedDhcpv6Srv> srv_;

    // Reference to D2ClientMgr singleton
    D2ClientMgr& d2_mgr_;

    // Bit Constants for turning on and off DDNS configuration options.
    // (Defined here as these are only meaningful to this class.)
    static const uint16_t ALWAYS_INCLUDE_FQDN = 1;
    static const uint16_t OVERRIDE_NO_UPDATE = 2;
    static const uint16_t OVERRIDE_CLIENT_UPDATE = 4;
    static const uint16_t REPLACE_CLIENT_NAME = 8;

    /// @brief Constructor
    FqdnDhcpv6SrvTest()
        : Dhcpv6SrvTest(), srv_(new NakedDhcpv6Srv(0)),
          d2_mgr_(CfgMgr::instance().getD2ClientMgr()) {
        // generateClientId assigns DUID to duid_.
        generateClientId();
        lease_.reset(new Lease6(Lease::TYPE_NA, IOAddress("2001:db8:1::1"),
                                duid_, 1234, 501, 502, 503,
                                504, 1, 0));
        // Config DDNS to be enabled, all controls off
        enableD2();
    }

    /// @brief Destructor
    virtual ~FqdnDhcpv6SrvTest() {
        // Default constructor creates a config with DHCP-DDNS updates
        // disabled.
        D2ClientConfigPtr cfg(new D2ClientConfig());
        CfgMgr::instance().setD2ClientConfig(cfg);
    }

    /// @brief Sets the server's DDNS configuration to ddns updates disabled.
    void disableD2() {
        // Default constructor creates a config with DHCP-DDNS updates
        // disabled.
        D2ClientConfigPtr cfg(new D2ClientConfig());
        CfgMgr::instance().setD2ClientConfig(cfg);
    }

    /// @brief Enables DHCP-DDNS updates with the given options enabled.
    ///
    /// Replaces the current D2ClientConfiguration with a configuration
    /// which as updates enabled and the control options set based upon
    /// the bit mask of options.
    ///
    /// @param mask Bit mask of configuration options that should be enabled.
    void enableD2(const uint16_t mask = 0) {
        D2ClientConfigPtr cfg;

        ASSERT_NO_THROW(cfg.reset(new D2ClientConfig(true,
                                  isc::asiolink::IOAddress("127.0.0.1"), 53001,
                                  dhcp_ddns::NCR_UDP, dhcp_ddns::FMT_JSON,
                                  (mask & ALWAYS_INCLUDE_FQDN),
                                  (mask & OVERRIDE_NO_UPDATE),
                                  (mask & OVERRIDE_CLIENT_UPDATE),
                                  (mask & REPLACE_CLIENT_NAME),
                                  "myhost", "example.com")));
        ASSERT_NO_THROW(CfgMgr::instance().setD2ClientConfig(cfg));
        ASSERT_NO_THROW(srv_->startD2());
    }

    /// @brief Construct the DHCPv6 Client FQDN option using flags and
    /// domain-name.
    ///
    /// @param flags Flags to be set for the created option.
    /// @param fqdn_name A name which should be stored in the option.
    /// @param fqdn_type A type of the name carried by the option: partial
    /// or fully qualified.
    ///
    /// @return A pointer to the created option.
    Option6ClientFqdnPtr
    createClientFqdn(const uint8_t flags,
                     const std::string& fqdn_name,
                     const Option6ClientFqdn::DomainNameType fqdn_type) {
        return (Option6ClientFqdnPtr(new Option6ClientFqdn(flags,
                                                           fqdn_name,
                                                           fqdn_type)));
    }

    /// @brief Create a message with or without DHCPv6 Client FQDN Option.
    ///
    /// @param msg_type A type of the DHCPv6 message to be created.
    /// @param fqdn_flags Flags to be carried in the FQDN option.
    /// @param fqdn_domain_name A name to be carried in the FQDN option.
    /// @param fqdn_type A type of the name carried by the option: partial
    /// or fully qualified.
    /// @param include_oro A boolean value which indicates whether the ORO
    /// option should be added to the message (if true).
    /// @param srvid server id to be stored in the message.
    ///
    /// @return An object representing the created message.
    Pkt6Ptr generateMessage(uint8_t msg_type,
                            const uint8_t fqdn_flags,
                            const std::string& fqdn_domain_name,
                            const Option6ClientFqdn::DomainNameType
                            fqdn_type,
                            const bool include_oro,
                            OptionPtr srvid = OptionPtr()) {
        Pkt6Ptr pkt = Pkt6Ptr(new Pkt6(msg_type, 1234));
        pkt->setRemoteAddr(IOAddress("fe80::abcd"));
        Option6IAPtr ia = generateIA(D6O_IA_NA, 234, 1500, 3000);

        if (msg_type != DHCPV6_REPLY) {
            IOAddress hint("2001:db8:1:1::dead:beef");
            OptionPtr hint_opt(new Option6IAAddr(D6O_IAADDR, hint, 300, 500));
            ia->addOption(hint_opt);
            pkt->addOption(ia);
        }

        OptionPtr clientid = generateClientId();
        pkt->addOption(clientid);
        if (srvid && (msg_type != DHCPV6_SOLICIT)) {
            pkt->addOption(srvid);
        }

        pkt->addOption(createClientFqdn(fqdn_flags, fqdn_domain_name,
                                            fqdn_type));

        if (include_oro) {
            OptionUint16ArrayPtr oro(new OptionUint16Array(Option::V6,
                                                           D6O_ORO));
            oro->addValue(D6O_CLIENT_FQDN);
            pkt->addOption(oro);
        }

        return (pkt);
    }

    /// @brief Creates instance of the DHCPv6 message with client id and
    /// server id.
    ///
    /// @param msg_type A type of the message to be created.
    ///
    /// @return An object representing the created message.
    Pkt6Ptr generateMessageWithIds(const uint8_t msg_type) {
        Pkt6Ptr pkt = Pkt6Ptr(new Pkt6(msg_type, 1234));
        // Generate client-id.
        OptionPtr opt_clientid = generateClientId();
        pkt->addOption(opt_clientid);

        if (msg_type != DHCPV6_SOLICIT) {
            // Generate server-id.
            pkt->addOption(srv_->getServerID());
        }

        return (pkt);
    }

    /// @brief Returns an instance of the option carrying FQDN.
    ///
    /// @param pkt A message holding FQDN option to be returned.
    ///
    /// @return An object representing DHCPv6 Client FQDN option.
    Option6ClientFqdnPtr getClientFqdnOption(const Pkt6Ptr& pkt) {
        return (boost::dynamic_pointer_cast<Option6ClientFqdn>
                (pkt->getOption(D6O_CLIENT_FQDN)));
    }

    /// @brief Adds IA option to the message.
    ///
    /// Addded option holds an address.
    ///
    /// @param iaid IAID
    /// @param pkt A DHCPv6 message to which the IA option should be added.
    void addIA(const uint32_t iaid, const IOAddress& addr, Pkt6Ptr& pkt) {
        Option6IAPtr opt_ia = generateIA(D6O_IA_NA, iaid, 1500, 3000);
        Option6IAAddrPtr opt_iaaddr(new Option6IAAddr(D6O_IAADDR, addr,
                                                      300, 500));
        opt_ia->addOption(opt_iaaddr);
        pkt->addOption(opt_ia);
    }


    /// @brief Adds IA option to the message.
    ///
    /// Added option holds status code.
    ///
    /// @param iaid IAID
    /// @param status_code Status code
    /// @param pkt A DHCPv6 message to which the option should be added.
    void addIA(const uint32_t iaid, const uint16_t status_code, Pkt6Ptr& pkt) {
        Option6IAPtr opt_ia = generateIA(D6O_IA_NA, iaid, 1500, 3000);
        addStatusCode(status_code, "", opt_ia);
        pkt->addOption(opt_ia);
    }

    /// @brief Creates status code with the specified code and message.
    ///
    /// @param code A status code.
    /// @param msg A string representation of the message to be added to the
    /// Status Code option.
    ///
    /// @return An object representing the Status Code option.
    OptionCustomPtr createStatusCode(const uint16_t code,
                                     const std::string& msg) {
        OptionDefinition def("status-code", D6O_STATUS_CODE, "record");
        def.addRecordField("uint16");
        def.addRecordField("string");
        OptionCustomPtr opt_status(new OptionCustom(def, Option::V6));
        opt_status->writeInteger(code);
        if (!msg.empty()) {
            opt_status->writeString(msg, 1);
        }
        return (opt_status);
    }

    /// @brief Adds Status Code option to the IA.
    ///
    /// @param code A status code value.
    /// @param msg A string representation of the message to be added to the
    /// Status Code option.
    void addStatusCode(const uint16_t code, const std::string& msg,
                       Option6IAPtr& opt_ia) {
        opt_ia->addOption(createStatusCode(code, msg));
    }

    /// @brief Verifies if the DHCPv6 server processes DHCPv6 Client FQDN option
    /// as expected.
    ///
    /// This function simulates generation of the client's message holding FQDN.
    /// It then calls the server's @c Dhcpv6Srv::processClientFqdn option to
    /// generate server's response to the FQDN. This function returns the FQDN
    /// which should be appended to the server's response to the client.
    /// This function verifies that the FQDN option returned is correct.
    ///
    /// @param msg_type A type of the client's message.
    /// @param in_flags A value of flags field to be set for the FQDN carried
    /// in the client's message.
    /// @param in_domain_name A domain name to be carried in the client's FQDN
    /// option.
    /// @param in_domain_type A type of the domain name to be carried in the
    /// client's FQDM option (partial or fully qualified).
    /// @param exp_flags A value of flags expected in the FQDN sent by a server.
    /// @param exp_domain_name A domain name expected in the FQDN sent by a
    /// server.
    void testFqdn(const uint16_t msg_type,
                  const uint8_t in_flags,
                  const std::string& in_domain_name,
                  const Option6ClientFqdn::DomainNameType in_domain_type,
                  const uint8_t exp_flags,
                  const std::string& exp_domain_name) {

        Pkt6Ptr question = generateMessage(msg_type,
                                           in_flags,
                                           in_domain_name,
                                           in_domain_type,
                                           true);
        ASSERT_TRUE(getClientFqdnOption(question));

        Pkt6Ptr answer(new Pkt6(msg_type == DHCPV6_SOLICIT ? DHCPV6_ADVERTISE :
                                DHCPV6_REPLY, question->getTransid()));
        ASSERT_NO_THROW(srv_->processClientFqdn(question, answer));
        Option6ClientFqdnPtr answ_fqdn = boost::dynamic_pointer_cast<
            Option6ClientFqdn>(answer->getOption(D6O_CLIENT_FQDN));
        ASSERT_TRUE(answ_fqdn);

        const bool flag_n = (exp_flags & Option6ClientFqdn::FLAG_N) != 0;
        const bool flag_s = (exp_flags & Option6ClientFqdn::FLAG_S) != 0;
        const bool flag_o = (exp_flags & Option6ClientFqdn::FLAG_O) != 0;

        EXPECT_EQ(flag_n, answ_fqdn->getFlag(Option6ClientFqdn::FLAG_N));
        EXPECT_EQ(flag_s, answ_fqdn->getFlag(Option6ClientFqdn::FLAG_S));
        EXPECT_EQ(flag_o, answ_fqdn->getFlag(Option6ClientFqdn::FLAG_O));

        EXPECT_EQ(exp_domain_name, answ_fqdn->getDomainName());
        // If server is configured to generate full FQDN for a client, and/or
        // client sent empty FQDN the expected result of the processing by
        // processClientFqdn is an empty, partial FQDN. This is an indication
        // for the code which performs lease allocation that the FQDN has to
        // be generated from the lease address.
        if (exp_domain_name.empty()) {
            EXPECT_EQ(Option6ClientFqdn::PARTIAL,
                      answ_fqdn->getDomainNameType());

        } else {
            EXPECT_EQ(Option6ClientFqdn::FULL, answ_fqdn->getDomainNameType());

        }
    }

    /// @brief Tests that the client's message holding an FQDN is processed
    /// and that lease is acquired.
    ///
    /// @param msg_type A type of the client's message.
    /// @param hostname A domain name in the client's FQDN.
    /// @param include_oro A boolean value which indicates whether the ORO
    /// option should be included in the client's message (if true) or not
    /// (if false). In the former case, the function will expect that server
    /// responds with the FQDN option. In the latter case, the function expects
    /// that the server doesn't respond with the FQDN.
    void testProcessMessage(const uint8_t msg_type,
                            const std::string& hostname,
                            const std::string& exp_hostname,
                            const bool include_oro = true) {
        // Create a message of a specified type, add server id and
        // FQDN option.
        OptionPtr srvid = srv_->getServerID();
        // Set the appropriate FQDN type. It must be partial if hostname is
        // empty.
        Option6ClientFqdn::DomainNameType fqdn_type = (hostname.empty() ?
            Option6ClientFqdn::PARTIAL : Option6ClientFqdn::FULL);

        Pkt6Ptr req = generateMessage(msg_type, Option6ClientFqdn::FLAG_S,
                                      hostname, fqdn_type, include_oro, srvid);

        // For different client's message types we have to invoke different
        // functions to generate response.
        Pkt6Ptr reply;
        if (msg_type == DHCPV6_SOLICIT) {
            ASSERT_NO_THROW(reply = srv_->processSolicit(req));

        } else if (msg_type == DHCPV6_REQUEST) {
            ASSERT_NO_THROW(reply = srv_->processRequest(req));

        } else if (msg_type == DHCPV6_RENEW) {
            ASSERT_NO_THROW(reply = srv_->processRequest(req));

        } else if (msg_type == DHCPV6_RELEASE) {
            // For Release no lease will be acquired so we have to leave
            // function here.
            ASSERT_NO_THROW(reply = srv_->processRelease(req));
            return;
        } else {
            // We are not interested in testing other message types.
            return;
        }

        // For Solicit, we will get different message type obviously.
        if (msg_type == DHCPV6_SOLICIT) {
            checkResponse(reply, DHCPV6_ADVERTISE, 1234);

        } else {
            checkResponse(reply, DHCPV6_REPLY, 1234);
        }

        // Check verify that IA_NA is correct.
        Option6IAAddrPtr addr =
            checkIA_NA(reply, 234, subnet_->getT1(), subnet_->getT2());
        ASSERT_TRUE(addr);

        // Check that we have got the address we requested.
        checkIAAddr(addr, IOAddress("2001:db8:1:1::dead:beef"),
                    Lease::TYPE_NA);

        if (msg_type != DHCPV6_SOLICIT) {
            // Check that the lease exists.
            Lease6Ptr lease =
                checkLease(duid_, reply->getOption(D6O_IA_NA), addr);
            ASSERT_TRUE(lease);
            EXPECT_EQ(exp_hostname, lease->hostname_);
        }

        // The Client FQDN option should be always present in the server's
        // response, regardless if requested using ORO or not.
        Option6ClientFqdnPtr fqdn;
        ASSERT_TRUE(fqdn = boost::dynamic_pointer_cast<
                        Option6ClientFqdn>(reply->getOption(D6O_CLIENT_FQDN)));
        EXPECT_EQ(exp_hostname, fqdn->getDomainName());
    }

    /// @brief Verify that NameChangeRequest holds valid values.
    ///
    /// This function picks first NameChangeRequest from the internal server's
    /// queue and checks that it holds valid parameters. The NameChangeRequest
    /// is removed from the queue.
    ///
    /// @param type An expected type of the NameChangeRequest (Add or Remove).
    /// @param reverse An expected setting of the reverse update flag.
    /// @param forward An expected setting of the forward udpate flag.
    /// @param addr A string representation of the IPv6 address held in the
    /// NameChangeRequest.
    /// @param dhcid An expected DHCID value.
    /// @note This value is the value that is produced by
    /// dhcp_ddns::D2Dhcid::crateDigest() with the appropriate arguments. This
    /// method uses encryption tools to produce the value which cannot be
    /// easily duplicated by hand.  It is more or less necessary to generate
    /// these values programmatically and place them here. Should the
    /// underlying implementation of createDigest() change these test values
    /// will likely need to be updated as well.
    /// @param expires A timestamp when the lease associated with the
    /// NameChangeRequest expires.
    /// @param len A valid lifetime of the lease associated with the
    /// NameChangeRequest.
    void verifyNameChangeRequest(const isc::dhcp_ddns::NameChangeType type,
                                 const bool reverse, const bool forward,
                                 const std::string& addr,
                                 const std::string& dhcid,
                                 const uint16_t expires,
                                 const uint16_t len) {
        NameChangeRequestPtr ncr;
        ASSERT_NO_THROW(ncr = d2_mgr_.peekAt(0));
        ASSERT_TRUE(ncr);

        EXPECT_EQ(type, ncr->getChangeType());
        EXPECT_EQ(forward, ncr->isForwardChange());
        EXPECT_EQ(reverse, ncr->isReverseChange());
        EXPECT_EQ(addr, ncr->getIpAddress());
        EXPECT_EQ(dhcid, ncr->getDhcid().toStr());
        EXPECT_EQ(expires, ncr->getLeaseExpiresOn());
        EXPECT_EQ(len, ncr->getLeaseLength());
        EXPECT_EQ(isc::dhcp_ddns::ST_NEW, ncr->getStatus());

        // Process the message off the queue
        ASSERT_NO_THROW(d2_mgr_.runReadyIO());
    }

    // Holds a lease used by a test.
    Lease6Ptr lease_;

};

// A set of tests verifying server's behaviour when it receives the DHCPv6
// Client Fqdn Option.
// @todo: Extend these tests once appropriate configuration parameters are
// implemented (ticket #3034).

// Test server's response when client requests that server performs AAAA update.
TEST_F(FqdnDhcpv6SrvTest, serverAAAAUpdate) {
    testFqdn(DHCPV6_SOLICIT, Option6ClientFqdn::FLAG_S,
             "myhost.example.com",
             Option6ClientFqdn::FULL, Option6ClientFqdn::FLAG_S,
             "myhost.example.com.");
}

// Test server's response when client provides partial domain-name and requests
// that server performs AAAA update.
TEST_F(FqdnDhcpv6SrvTest, serverAAAAUpdatePartialName) {
    testFqdn(DHCPV6_SOLICIT, Option6ClientFqdn::FLAG_S, "myhost",
             Option6ClientFqdn::PARTIAL, Option6ClientFqdn::FLAG_S,
             "myhost.example.com.");
}

// Test server's response when client provides empty domain-name and requests
// that server performs AAAA update.
TEST_F(FqdnDhcpv6SrvTest, serverAAAAUpdateNoName) {
    testFqdn(DHCPV6_SOLICIT, Option6ClientFqdn::FLAG_S, "",
             Option6ClientFqdn::PARTIAL, Option6ClientFqdn::FLAG_S, "");
}

// Test server's response when client requests no DNS update.
TEST_F(FqdnDhcpv6SrvTest, noUpdate) {
    testFqdn(DHCPV6_SOLICIT, Option6ClientFqdn::FLAG_N,
             "myhost.example.com",
             Option6ClientFqdn::FULL, Option6ClientFqdn::FLAG_N,
             "myhost.example.com.");
}

// Test server's response when client requests that server delegates the AAAA
// update to the client and this delegation is not allowed.
TEST_F(FqdnDhcpv6SrvTest, clientAAAAUpdateNotAllowed) {
    enableD2(OVERRIDE_CLIENT_UPDATE);
    testFqdn(DHCPV6_SOLICIT, 0, "myhost.example.com.",
             Option6ClientFqdn::FULL,
             Option6ClientFqdn::FLAG_S | Option6ClientFqdn::FLAG_O,
             "myhost.example.com.");
}

// Test that exception is thrown if supplied NULL answer packet when
// creating NameChangeRequests.
TEST_F(FqdnDhcpv6SrvTest, createNameChangeRequestsNoAnswer) {
    Pkt6Ptr answer;

    EXPECT_THROW(srv_->createNameChangeRequests(answer),
                 isc::Unexpected);

}

// Test that exception is thrown if supplied answer from the server
// contains no DUID when creating NameChangeRequests.
TEST_F(FqdnDhcpv6SrvTest, createNameChangeRequestsNoDUID) {
    Pkt6Ptr answer = Pkt6Ptr(new Pkt6(DHCPV6_REPLY, 1234));
    Option6ClientFqdnPtr fqdn = createClientFqdn(Option6ClientFqdn::FLAG_S,
                                                 "myhost.example.com",
                                                 Option6ClientFqdn::FULL);
    answer->addOption(fqdn);

    EXPECT_THROW(srv_->createNameChangeRequests(answer), isc::Unexpected);

}

// Test no NameChangeRequests if Client FQDN is not added to the server's
// response.
TEST_F(FqdnDhcpv6SrvTest, createNameChangeRequestsNoFQDN) {
    // Create Reply message with Client Id and Server id.
    Pkt6Ptr answer = generateMessageWithIds(DHCPV6_REPLY);

    ASSERT_NO_THROW(srv_->createNameChangeRequests(answer));

    // There should be no new NameChangeRequests.
    ASSERT_EQ(0, d2_mgr_.getQueueSize());
}

// Test that NameChangeRequests are not generated if an answer message
// contains no addresses.
TEST_F(FqdnDhcpv6SrvTest, createNameChangeRequestsNoAddr) {
    // Create Reply message with Client Id and Server id.
    Pkt6Ptr answer = generateMessageWithIds(DHCPV6_REPLY);

    // Add Client FQDN option.
    Option6ClientFqdnPtr fqdn = createClientFqdn(Option6ClientFqdn::FLAG_S,
                                                 "myhost.example.com",
                                                 Option6ClientFqdn::FULL);
    answer->addOption(fqdn);

    ASSERT_NO_THROW(srv_->createNameChangeRequests(answer));

    // We didn't add any IAs, so there should be no NameChangeRequests in th
    // queue.
    ASSERT_EQ(0, d2_mgr_.getQueueSize());
}

// Test that exactly one NameChangeRequest is created as a result of processing
// the answer message which holds 3 IAs and when FQDN is specified.
TEST_F(FqdnDhcpv6SrvTest, createNameChangeRequests) {
    // Create Reply message with Client Id and Server id.
    Pkt6Ptr answer = generateMessageWithIds(DHCPV6_REPLY);

    // Create three IAs, each having different address.
    addIA(1234, IOAddress("2001:db8:1::1"), answer);
    addIA(2345, IOAddress("2001:db8:1::2"), answer);
    addIA(3456, IOAddress("2001:db8:1::3"), answer);

    // Use domain name in upper case. It should be converted to lower-case
    // before DHCID is calculated. So, we should get the same result as if
    // we typed domain name in lower-case.
    Option6ClientFqdnPtr fqdn = createClientFqdn(Option6ClientFqdn::FLAG_S,
                                                 "MYHOST.EXAMPLE.COM",
                                                 Option6ClientFqdn::FULL);
    answer->addOption(fqdn);

    // Create NameChangeRequest for the first allocated address.
    ASSERT_NO_THROW(srv_->createNameChangeRequests(answer));
    ASSERT_EQ(1, d2_mgr_.getQueueSize());

    // Verify that NameChangeRequest is correct.
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_ADD, true, true,
                            "2001:db8:1::1",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 500);

}

// Checks that NameChangeRequests to add entries are not
// created when ddns updates are disabled.
TEST_F(FqdnDhcpv6SrvTest, noAddRequestsWhenDisabled) {
    // Disable DDNS udpates.
    disableD2();

    // Create Reply message with Client Id and Server id.
    Pkt6Ptr answer = generateMessageWithIds(DHCPV6_REPLY);

    // Create three IAs, each having different address.
    addIA(1234, IOAddress("2001:db8:1::1"), answer);

    // Use domain name in upper case. It should be converted to lower-case
    // before DHCID is calculated. So, we should get the same result as if
    // we typed domain name in lower-case.
    Option6ClientFqdnPtr fqdn = createClientFqdn(Option6ClientFqdn::FLAG_S,
                                                 "MYHOST.EXAMPLE.COM",
                                                 Option6ClientFqdn::FULL);
    answer->addOption(fqdn);

    // An attempt to send a NCR would throw.
    ASSERT_NO_THROW(srv_->createNameChangeRequests(answer));
}


// Test creation of the NameChangeRequest to remove both forward and reverse
// mapping for the given lease.
TEST_F(FqdnDhcpv6SrvTest, createRemovalNameChangeRequestFwdRev) {
    lease_->fqdn_fwd_ = true;
    lease_->fqdn_rev_ = true;
    // Part of the domain name is in upper case, to test that it gets converted
    // to lower case before DHCID is computed. So, we should get the same DHCID
    // as if we typed domain-name in lower case.
    lease_->hostname_ = "MYHOST.example.com.";

    ASSERT_NO_THROW(srv_->createRemovalNameChangeRequest(lease_));

    ASSERT_EQ(1, d2_mgr_.getQueueSize());
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_REMOVE, true, true,
                            "2001:db8:1::1",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 502);

}

// Checks that NameChangeRequests to remove entries are not created
// when ddns updates are disabled.
TEST_F(FqdnDhcpv6SrvTest, noRemovalsWhenDisabled) {
    // Disable DDNS updates.
    disableD2();

    lease_->fqdn_fwd_ = true;
    lease_->fqdn_rev_ = true;
    // Part of the domain name is in upper case, to test that it gets converted
    // to lower case before DHCID is computed. So, we should get the same DHCID
    // as if we typed domain-name in lower case.
    lease_->hostname_ = "MYHOST.example.com.";

    // When DDNS is disabled an attempt to send a request will throw.
    ASSERT_NO_THROW(srv_->createRemovalNameChangeRequest(lease_));
}


// Test creation of the NameChangeRequest to remove reverse mapping for the
// given lease.
TEST_F(FqdnDhcpv6SrvTest, createRemovalNameChangeRequestRev) {
    lease_->fqdn_fwd_ = false;
    lease_->fqdn_rev_ = true;
    lease_->hostname_ = "myhost.example.com.";

    ASSERT_NO_THROW(srv_->createRemovalNameChangeRequest(lease_));

    ASSERT_EQ(1, d2_mgr_.getQueueSize());

    verifyNameChangeRequest(isc::dhcp_ddns::CHG_REMOVE, true, false,
                            "2001:db8:1::1",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 502);

}

// Test that NameChangeRequest to remove DNS records is not generated when
// neither forward nor reverse DNS update has been performed for a lease.
TEST_F(FqdnDhcpv6SrvTest, createRemovalNameChangeRequestNoUpdate) {
    lease_->fqdn_fwd_ = false;
    lease_->fqdn_rev_ = false;

    ASSERT_NO_THROW(srv_->createRemovalNameChangeRequest(lease_));

    ASSERT_EQ(0, d2_mgr_.getQueueSize());

}

// Test that NameChangeRequest is not generated if the hostname hasn't been
// specified for a lease for which forward and reverse mapping has been set.
TEST_F(FqdnDhcpv6SrvTest, createRemovalNameChangeRequestNoHostname) {
    lease_->fqdn_fwd_ = true;
    lease_->fqdn_rev_ = true;
    lease_->hostname_ = "";

    ASSERT_NO_THROW(srv_->createRemovalNameChangeRequest(lease_));

    ASSERT_EQ(0, d2_mgr_.getQueueSize());

}

// Test that NameChangeRequest is not generated if the invalid hostname has
// been specified for a lease for which forward and reverse mapping has been
// set.
TEST_F(FqdnDhcpv6SrvTest, createRemovalNameChangeRequestWrongHostname) {
    lease_->fqdn_fwd_ = true;
    lease_->fqdn_rev_ = true;
    lease_->hostname_ = "myhost..example.com.";

    ASSERT_NO_THROW(srv_->createRemovalNameChangeRequest(lease_));

    ASSERT_EQ(0, d2_mgr_.getQueueSize());

}

// Test that Advertise message generated in a response to the Solicit will
// not result in generation if the NameChangeRequests.
TEST_F(FqdnDhcpv6SrvTest, processSolicit) {
    // Create a Solicit message with FQDN option and generate server's
    // response using processSolicit function.
    testProcessMessage(DHCPV6_SOLICIT, "myhost.example.com",
                       "myhost.example.com.");
    ASSERT_EQ(0, d2_mgr_.getQueueSize());
}

// Test that client may send two requests, each carrying FQDN option with
// a different domain-name. Server should use existing lease for the second
// request but modify the DNS entries for the lease according to the contents
// of the FQDN sent in the second request.
TEST_F(FqdnDhcpv6SrvTest, processTwoRequests) {
    // Create a Request message with FQDN option and generate server's
    // response using processRequest function. This will result in the
    // creation of a new lease and the appropriate NameChangeRequest
    // to add both reverse and forward mapping to DNS.
    testProcessMessage(DHCPV6_REQUEST, "myhost.example.com",
                       "myhost.example.com.");
    ASSERT_EQ(1, d2_mgr_.getQueueSize());
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_ADD, true, true,
                            "2001:db8:1:1::dead:beef",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 4000);

    // Client may send another request message with a new domain-name. In this
    // case the same lease will be returned. The existing DNS entry needs to
    // be replaced with a new one. Server should determine that the different
    // FQDN has been already added to the DNS. As a result, the old DNS
    // entries should be removed and the entries for the new domain-name
    // should be added. Therefore, we expect two NameChangeRequests. One to
    // remove the existing entries, one to add new entries.
    testProcessMessage(DHCPV6_REQUEST, "otherhost.example.com",
                       "otherhost.example.com.");
    ASSERT_EQ(2, d2_mgr_.getQueueSize());
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_REMOVE, true, true,
                            "2001:db8:1:1::dead:beef",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 4000);
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_ADD, true, true,
                            "2001:db8:1:1::dead:beef",
                            "000201D422AA463306223D269B6CB7AFE7AAD265FC"
                            "EA97F93623019B2E0D14E5323D5A",
                            0, 4000);

}

// Test that NameChangeRequest is not generated when Solicit message is sent.
// The Solicit is here sent after a lease has been allocated for a client.
// The Solicit conveys a different hostname which would trigger updates to
// DNS if the Request was sent instead of Soicit. The code should differentiate
// behavior depending whether Solicit or Request is sent.
TEST_F(FqdnDhcpv6SrvTest, processRequestSolicit) {
    // Create a Request message with FQDN option and generate server's
    // response using processRequest function. This will result in the
    // creation of a new lease and the appropriate NameChangeRequest
    // to add both reverse and forward mapping to DNS.
    testProcessMessage(DHCPV6_REQUEST, "myhost.example.com",
                       "myhost.example.com.");
    ASSERT_EQ(1, d2_mgr_.getQueueSize());
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_ADD, true, true,
                            "2001:db8:1:1::dead:beef",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 4000);

    // When the returning client sends Solicit the code should never generate
    // NameChangeRequest and preserve existing DNS entries for the client.
    // The NameChangeRequest should only be generated when a client sends
    // Request or Renew.
    testProcessMessage(DHCPV6_SOLICIT, "otherhost.example.com",
                       "otherhost.example.com.");
    ASSERT_EQ(0, d2_mgr_.getQueueSize());

}


// Test that client may send Request followed by the Renew, both holding
// FQDN options, but each option holding different domain-name. The Renew
// should result in generation of the two NameChangeRequests, one to remove
// DNS entry added previously when Request was processed, another one to
// add a new entry for the FQDN held in the Renew.
TEST_F(FqdnDhcpv6SrvTest, processRequestRenew) {
    // Create a Request message with FQDN option and generate server's
    // response using processRequest function. This will result in the
    // creation of a new lease and the appropriate NameChangeRequest
    // to add both reverse and forward mapping to DNS.
    testProcessMessage(DHCPV6_REQUEST, "myhost.example.com",
                       "myhost.example.com.");
    ASSERT_EQ(1, d2_mgr_.getQueueSize());
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_ADD, true, true,
                            "2001:db8:1:1::dead:beef",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 4000);

    // Client may send Renew message with a new domain-name. In this
    // case the same lease will be returned. The existing DNS entry needs to
    // be replaced with a new one. Server should determine that the different
    // FQDN has been already added to the DNS. As a result, the old DNS
    // entries should be removed and the entries for the new domain-name
    // should be added. Therefore, we expect two NameChangeRequests. One to
    // remove the existing entries, one to add new entries.
    testProcessMessage(DHCPV6_RENEW, "otherhost.example.com",
                       "otherhost.example.com.");
    ASSERT_EQ(2, d2_mgr_.getQueueSize());
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_REMOVE, true, true,
                            "2001:db8:1:1::dead:beef",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 4000);
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_ADD, true, true,
                            "2001:db8:1:1::dead:beef",
                            "000201D422AA463306223D269B6CB7AFE7AAD265FC"
                            "EA97F93623019B2E0D14E5323D5A",
                            0, 4000);

}

TEST_F(FqdnDhcpv6SrvTest, processRequestRelease) {
    // Create a Request message with FQDN option and generate server's
    // response using processRequest function. This will result in the
    // creation of a new lease and the appropriate NameChangeRequest
    // to add both reverse and forward mapping to DNS.
    testProcessMessage(DHCPV6_REQUEST, "myhost.example.com",
                       "myhost.example.com.");
    ASSERT_EQ(1, d2_mgr_.getQueueSize());
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_ADD, true, true,
                            "2001:db8:1:1::dead:beef",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 4000);

    // Client may send Release message. In this case the lease should be
    // removed and all existing DNS entries for this lease should be
    // also removed. Therefore, we expect that single NameChangeRequest to
    // remove DNS entries is generated.
    testProcessMessage(DHCPV6_RELEASE, "otherhost.example.com",
                       "otherhost.example.com.");
    ASSERT_EQ(1, d2_mgr_.getQueueSize());
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_REMOVE, true, true,
                            "2001:db8:1:1::dead:beef",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 4000);

}

// Checks that the server include DHCPv6 Client FQDN option in its
// response even when client doesn't request this option using ORO.
TEST_F(FqdnDhcpv6SrvTest, processRequestWithoutFqdn) {
    // The last parameter disables use of the ORO to request FQDN option
    // In this case, we expect that the FQDN option will not be included
    // in the server's response. The testProcessMessage will check that.
    testProcessMessage(DHCPV6_REQUEST, "myhost.example.com",
                       "myhost.example.com.", false);
    ASSERT_EQ(1, d2_mgr_.getQueueSize());
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_ADD, true, true,
                            "2001:db8:1:1::dead:beef",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 4000);
}

// Checks that FQDN is generated from an ip address, when client sends an empty
// FQDN.
TEST_F(FqdnDhcpv6SrvTest, processRequestEmptyFqdn) {
    testProcessMessage(DHCPV6_REQUEST, "",
                       "myhost-2001-db8-1-1--dead-beef.example.com.", false);
    ASSERT_EQ(1, d2_mgr_.getQueueSize());
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_ADD, true, true,
                            "2001:db8:1:1::dead:beef",
                            "000201C905E54BE12DE6AF92ADE72752B9F362"
                            "13B5A8BC9D217548CD739B4CF31AFB1B",
                            0, 4000);

}

// Checks that when the server reuses expired lease, the NameChangeRequest
// is generated to remove the DNS mapping for the expired lease and second
// NameChangeRequest to add a DNS mapping for a new lease.
TEST_F(FqdnDhcpv6SrvTest, processRequestReuseExpiredLease) {
    // This address will be used throughout the test.
    IOAddress addr("2001:db8:1:1::dead:beef");
    // We are going to configure a subnet with a pool that consists of
    // exactly one address. This address will be handed out to the
    // client, will get expired and then be reused.
    CfgMgr::instance().deleteSubnets6();
    subnet_ = Subnet6Ptr(new Subnet6(IOAddress("2001:db8:1:1::"), 56, 1, 2,
                                     3, 4));
    pool_ = Pool6Ptr(new Pool6(Lease::TYPE_NA, addr, addr));
    subnet_->addPool(pool_);
    CfgMgr::instance().addSubnet6(subnet_);

    // Allocate a lease.
    testProcessMessage(DHCPV6_REQUEST, "myhost.example.com",
                       "myhost.example.com.");
    // Test that the appropriate NameChangeRequest has been generated.
    ASSERT_EQ(1, d2_mgr_.getQueueSize());
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_ADD, true, true,
                            "2001:db8:1:1::dead:beef",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 4);
    // Get the lease acquired and modify it. In particular, expire it.
    Lease6Ptr lease =
        LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, addr);
    ASSERT_TRUE(lease);
    // One of the following: IAID, DUID or subnet identifier has to be changed
    // because otherwise the allocation engine will treat the lease as
    // being renewed by the same client. If we at least change subnet identifier
    // the lease will be treated as expired lease to be reused.
    ++lease->subnet_id_;

    // Move the cllt back in time and make sure that the lease got expired.
    lease->cltt_ = time(NULL) - 10;
    lease->valid_lft_ = 5;
    ASSERT_TRUE(lease->expired());
    // Change the hostname so as the name change request for removing existing
    // DNS mapping is generated.
    lease->hostname_ = "otherhost.example.com.";
    // Update the lease in the lease database.
    LeaseMgrFactory::instance().updateLease6(lease);

    // Simulate another lease acquisition. Since, our pool consists of
    // exactly one address and this address is used by the lease in the
    // lease database, it is guaranteed that the allocation engine will
    // reuse this lease.
    testProcessMessage(DHCPV6_REQUEST, "myhost.example.com.",
                       "myhost.example.com.");
    ASSERT_EQ(2, d2_mgr_.getQueueSize());
    // The first name change request generated, should remove a DNS
    // mapping for an expired lease.
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_REMOVE, true, true,
                            "2001:db8:1:1::dead:beef",
                            "000201D422AA463306223D269B6CB7AFE7AAD2"
                            "65FCEA97F93623019B2E0D14E5323D5A",
                            0, 5);
    // The second name change request should add a DNS mapping for
    // a new lease.
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_ADD, true, true,
                            "2001:db8:1:1::dead:beef",
                            "000201415AA33D1187D148275136FA30300478"
                            "FAAAA3EBD29826B5C907B2C9268A6F52",
                            0, 4);

}

}   // end of anonymous namespace
