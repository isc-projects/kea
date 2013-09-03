// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/option4_client_fqdn.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <dhcp_ddns/ncr_msg.h>

#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp_ddns;
using namespace isc::test;

namespace {
class FqdnDhcpv4SrvTest : public Dhcpv4SrvTest {
public:
    FqdnDhcpv4SrvTest() : Dhcpv4SrvTest() {
        srv_ = new NakedDhcpv4Srv(0);
    }

    virtual ~FqdnDhcpv4SrvTest() {
        delete srv_;
    }

    // Create a lease to be used by various tests.
    Lease4Ptr createLease(const isc::asiolink::IOAddress& addr,
                          const std::string& hostname,
                          const bool fqdn_fwd,
                          const bool fqdn_rev) {
        const uint8_t hwaddr[] = { 0, 1, 2, 3, 4, 5, 6 };
        Lease4Ptr lease(new Lease4(addr, hwaddr, sizeof(hwaddr),
                                   &generateClientId()->getData()[0],
                                   generateClientId()->getData().size(),
                                   100, 50, 75, time(NULL), subnet_->getID()));
        // @todo Set this through the Lease4 constructor.
        lease->hostname_ = hostname;
        lease->fqdn_fwd_ = fqdn_fwd;
        lease->fqdn_rev_ = fqdn_rev;

        return (lease);
    }

    // Create an instance of the DHCPv4 Client FQDN Option.
    Option4ClientFqdnPtr
    createClientFqdn(const uint8_t flags,
                     const std::string& fqdn_name,
                     const Option4ClientFqdn::DomainNameType fqdn_type) {
        return (Option4ClientFqdnPtr(new Option4ClientFqdn(flags,
                                                           Option4ClientFqdn::
                                                           RCODE_CLIENT(),
                                                           fqdn_name,
                                                           fqdn_type)));
    }

    Option4ClientFqdnPtr getClientFqdnOption(const Pkt4Ptr& pkt) {
        return (boost::dynamic_pointer_cast<
                Option4ClientFqdn>(pkt->getOption(DHO_FQDN)));
    }

    // Create a message holding DHCPv4 Client FQDN Option.
    Pkt4Ptr generatePktWithFqdn(const uint8_t msg_type,
                                const uint8_t fqdn_flags,
                                const std::string& fqdn_domain_name,
                                const Option4ClientFqdn::DomainNameType
                                fqdn_type,
                                const bool include_prl,
                                const bool include_clientid = true) {
        Pkt4Ptr pkt = Pkt4Ptr(new Pkt4(msg_type, 1234));
        pkt->setRemoteAddr(IOAddress("192.0.2.3"));
        // For DISCOVER we don't include server id, because client broadcasts
        // the message to all servers.
        if (msg_type != DHCPDISCOVER) {
            pkt->addOption(srv_->getServerID());
        }

        if (include_clientid) {
            pkt->addOption(generateClientId());
        }

        // Create Client FQDN Option with the specified flags and
        // domain-name.
        pkt->addOption(createClientFqdn(fqdn_flags, fqdn_domain_name,
                                        fqdn_type));

        // Control whether or not to request that server returns the FQDN
        // option. Server may be configured to always return it or return
        // only in case client requested it.
        if (include_prl) {
            OptionUint8ArrayPtr option_prl =
                OptionUint8ArrayPtr(new OptionUint8Array(Option::V4,
                                    DHO_DHCP_PARAMETER_REQUEST_LIST));
            option_prl->addValue(DHO_FQDN);
        }
        return (pkt);
    }

    // Test that server generates the appropriate FQDN option in response to
    // client's FQDN option.
    void testProcessFqdn(const Pkt4Ptr& query, const uint8_t exp_flags,
                         const std::string& exp_domain_name) {
        ASSERT_TRUE(getClientFqdnOption(query));

        Pkt4Ptr answer;
        if (query->getType() == DHCPDISCOVER) {
            answer.reset(new Pkt4(DHCPOFFER, 1234));

        } else {
            answer.reset(new Pkt4(DHCPACK, 1234));

        }
        ASSERT_NO_THROW(srv_->processClientName(query, answer));

        Option4ClientFqdnPtr fqdn = getClientFqdnOption(answer);
        ASSERT_TRUE(fqdn);

        const bool flag_n = (exp_flags & Option4ClientFqdn::FLAG_N) != 0;
        const bool flag_s = (exp_flags & Option4ClientFqdn::FLAG_S) != 0;
        const bool flag_o = (exp_flags & Option4ClientFqdn::FLAG_O) != 0;
        const bool flag_e = (exp_flags & Option4ClientFqdn::FLAG_E) != 0;

        EXPECT_EQ(flag_n, fqdn->getFlag(Option4ClientFqdn::FLAG_N));
        EXPECT_EQ(flag_s, fqdn->getFlag(Option4ClientFqdn::FLAG_S));
        EXPECT_EQ(flag_o, fqdn->getFlag(Option4ClientFqdn::FLAG_O));
        EXPECT_EQ(flag_e, fqdn->getFlag(Option4ClientFqdn::FLAG_E));

        EXPECT_EQ(exp_domain_name, fqdn->getDomainName());
        EXPECT_EQ(Option4ClientFqdn::FULL, fqdn->getDomainNameType());

    }

    // Verify that NameChangeRequest holds valid values.
    void verifyNameChangeRequest(const isc::dhcp_ddns::NameChangeType type,
                                 const bool reverse, const bool forward,
                                 const std::string& addr,
                                 const std::string& dhcid,
                                 const uint16_t expires,
                                 const uint16_t len) {
        NameChangeRequest ncr = srv_->name_change_reqs_.front();
        EXPECT_EQ(type, ncr.getChangeType());
        EXPECT_EQ(forward, ncr.isForwardChange());
        EXPECT_EQ(reverse, ncr.isReverseChange());
        EXPECT_EQ(addr, ncr.getIpAddress());
        EXPECT_EQ(dhcid, ncr.getDhcid().toStr());
        EXPECT_EQ(expires, ncr.getLeaseExpiresOn());
        EXPECT_EQ(len, ncr.getLeaseLength());
        EXPECT_EQ(isc::dhcp_ddns::ST_NEW, ncr.getStatus());
        srv_->name_change_reqs_.pop();
    }

    NakedDhcpv4Srv* srv_;

};

// Test that the exception is thrown if lease pointer specified as the argument
// of computeDhcid function is NULL.
TEST_F(FqdnDhcpv4SrvTest, dhcidNullLease) {
    Lease4Ptr lease;
    EXPECT_THROW(srv_->computeDhcid(lease), isc::dhcp::DhcidComputeError);

}

// Test that the appropriate exception is thrown if the lease object used
// to compute DHCID comprises wrong hostname.
TEST_F(FqdnDhcpv4SrvTest, dhcidWrongHostname) {
    // First, make sure that the lease with the correct hostname is accepted.
    Lease4Ptr lease = createLease(IOAddress("192.0.2.3"),
                                  "myhost.example.com.", true, true);
    ASSERT_NO_THROW(srv_->computeDhcid(lease));

    // Now, use the wrong hostname. It should result in the exception.
    lease->hostname_ = "myhost...example.com.";
    EXPECT_THROW(srv_->computeDhcid(lease), isc::dhcp::DhcidComputeError);

    // Also, empty hostname is wrong.
    lease->hostname_ = "";
    EXPECT_THROW(srv_->computeDhcid(lease), isc::dhcp::DhcidComputeError);
}

// Test that the DHCID is computed correctly, when the lease holds
// correct hostname and non-NULL client id.
TEST_F(FqdnDhcpv4SrvTest, dhcidComputeFromClientId) {
    Lease4Ptr lease = createLease(IOAddress("192.0.2.3"),
                                  "myhost.example.com.",
                                  true, true);
    isc::dhcp_ddns::D2Dhcid dhcid;
    ASSERT_NO_THROW(dhcid = srv_->computeDhcid(lease));

    // Make sure that the computed DHCID is valid.
    std::string dhcid_ref = "00010132E91AA355CFBB753C0F0497A5A9404"
        "36965B68B6D438D98E680BF10B09F3BCF";
    EXPECT_EQ(dhcid_ref, dhcid.toStr());
}

// Test that the DHCID is computed correctly, when the lease holds correct
// hostname and NULL client id.
TEST_F(FqdnDhcpv4SrvTest, dhcidComputeFromHWAddr) {
    Lease4Ptr lease = createLease(IOAddress("192.0.2.3"),
                                  "myhost.example.com.",
                                  true, true);
    lease->client_id_.reset();

    isc::dhcp_ddns::D2Dhcid dhcid;
    ASSERT_NO_THROW(dhcid = srv_->computeDhcid(lease));

    // Make sure that the computed DHCID is valid.
    std::string dhcid_ref = "0000012247F6DC4423C3E8627434A9D6868609"
        "D88948F78018B215EDCAA30C0C135035";
    EXPECT_EQ(dhcid_ref, dhcid.toStr());
}


// Test that server confirms to perform the forward and reverse DNS update,
// when client asks for it.
TEST_F(FqdnDhcpv4SrvTest, serverUpdateForward) {
    Pkt4Ptr query = generatePktWithFqdn(DHCPREQUEST,
                                        Option4ClientFqdn::FLAG_E |
                                        Option4ClientFqdn::FLAG_S,
                                        "myhost.example.com.",
                                        Option4ClientFqdn::FULL,
                                        true);

    testProcessFqdn(query,
                    Option4ClientFqdn::FLAG_E | Option4ClientFqdn::FLAG_S,
                    "myhost.example.com.");

}

// Test that server generates the fully qualified domain name for the client
// if client supplies the partial name.
TEST_F(FqdnDhcpv4SrvTest, serverUpdateForwardPartialName) {
    Pkt4Ptr query = generatePktWithFqdn(DHCPREQUEST,
                                        Option4ClientFqdn::FLAG_E |
                                        Option4ClientFqdn::FLAG_S,
                                        "myhost",
                                        Option4ClientFqdn::PARTIAL,
                                        true);

    testProcessFqdn(query,
                    Option4ClientFqdn::FLAG_E | Option4ClientFqdn::FLAG_S,
                    "myhost.example.com.");

}

// Test that server generates the fully qualified domain name for the client
// if clietn supplies empty domain name.
TEST_F(FqdnDhcpv4SrvTest, serverUpdateForwardNoName) {
    Pkt4Ptr query = generatePktWithFqdn(DHCPREQUEST,
                                        Option4ClientFqdn::FLAG_E |
                                        Option4ClientFqdn::FLAG_S,
                                        "",
                                        Option4ClientFqdn::PARTIAL,
                                        true);

    testProcessFqdn(query,
                    Option4ClientFqdn::FLAG_E | Option4ClientFqdn::FLAG_S,
                    "myhost.example.com.");

}

// Test server's response when client requests no DNS update.
TEST_F(FqdnDhcpv4SrvTest, noUpdate) {
    Pkt4Ptr query = generatePktWithFqdn(DHCPREQUEST,
                                        Option4ClientFqdn::FLAG_E |
                                        Option4ClientFqdn::FLAG_N,
                                        "myhost.example.com.",
                                        Option4ClientFqdn::FULL,
                                        true);
    testProcessFqdn(query, Option4ClientFqdn::FLAG_E | Option4ClientFqdn::FLAG_N,
                    "myhost.example.com.");
}

// Test that server does not accept delegation of the forward DNS update
// to a client.
TEST_F(FqdnDhcpv4SrvTest, clientUpdateNotAllowed) {
    Pkt4Ptr query = generatePktWithFqdn(DHCPREQUEST,
                                        Option4ClientFqdn::FLAG_E,
                                        "myhost.example.com.",
                                        Option4ClientFqdn::FULL,
                                        true);

    testProcessFqdn(query, Option4ClientFqdn::FLAG_E |
                    Option4ClientFqdn::FLAG_S | Option4ClientFqdn::FLAG_O,
                    "myhost.example.com.");

}

// Test that exactly one NameChangeRequest is generated when the new lease
// has been acquired (old lease is NULL).
TEST_F(FqdnDhcpv4SrvTest, createNameChangeRequestsNewLease) {
    Lease4Ptr lease = createLease(IOAddress("192.0.2.3"), "myhost.example.com.",
                                  true, true);
    Lease4Ptr old_lease;

    ASSERT_NO_THROW(srv_->createNameChangeRequests(lease, old_lease));
    ASSERT_EQ(1, srv_->name_change_reqs_.size());

    verifyNameChangeRequest(isc::dhcp_ddns::CHG_ADD, true, true,
                            "192.0.2.3", "00010132E91AA355CFBB753C0F049"
                            "7A5A940436965B68B6D438D98E680BF10B09F3BCF",
                            0, 100);
}

// Test that no NameChangeRequest is generated when a lease is renewed and
// the FQDN data hasn't changed.
TEST_F(FqdnDhcpv4SrvTest, createNameChangeRequestsRenewNoChange) {
    Lease4Ptr lease = createLease(IOAddress("192.0.2.3"), "myhost.example.com.",
                                  true, true);
    Lease4Ptr old_lease = createLease(IOAddress("192.0.2.3"),
                                      "myhost.example.com.", true, true);
    old_lease->valid_lft_ += 100;

    ASSERT_NO_THROW(srv_->createNameChangeRequests(lease, old_lease));
    EXPECT_TRUE(srv_->name_change_reqs_.empty());
}


} // end of anonymous namespace
