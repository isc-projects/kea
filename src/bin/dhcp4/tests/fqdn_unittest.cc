// Copyright (C) 2013-2014 Internet Systems Consortium, Inc. ("ISC")
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
#include <dhcp/option_int_array.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <dhcp_ddns/ncr_msg.h>

#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::dhcp_ddns;

namespace {

class NameDhcpv4SrvTest : public Dhcpv4SrvTest {
public:
    NameDhcpv4SrvTest() : Dhcpv4SrvTest() {
        srv_ = new NakedDhcpv4Srv(0);
    }
    virtual ~NameDhcpv4SrvTest() {
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
                     Option4ClientFqdn::DomainNameType fqdn_type) {
        return (Option4ClientFqdnPtr(new Option4ClientFqdn(flags,
                                                           Option4ClientFqdn::
                                                           RCODE_CLIENT(),
                                                           fqdn_name,
                                                           fqdn_type)));
   }

    // Create an instance of the Hostname option.
    OptionCustomPtr
    createHostname(const std::string& hostname) {
        OptionDefinition def("hostname", DHO_HOST_NAME, "string");
        OptionCustomPtr opt_hostname(new OptionCustom(def, Option::V4));
        opt_hostname->writeString(hostname);
        return (opt_hostname);
    }

    // Generates partial hostname from the address. The format of the
    // generated address is: host-A-B-C-D, where A.B.C.D is an IP
    // address.
    std::string generatedNameFromAddress(const IOAddress& addr) {
        std::string gen_name = addr.toText();
        std::replace(gen_name.begin(), gen_name.end(), '.', '-');
        std::ostringstream hostname;
        hostname << "host-" << gen_name;
        return (hostname.str());
    }

    // Get the Client FQDN Option from the given message.
    Option4ClientFqdnPtr getClientFqdnOption(const Pkt4Ptr& pkt) {
        return (boost::dynamic_pointer_cast<
                Option4ClientFqdn>(pkt->getOption(DHO_FQDN)));
    }

    // get the Hostname option from the given message.
    OptionCustomPtr getHostnameOption(const Pkt4Ptr& pkt) {
        return (boost::dynamic_pointer_cast<
                OptionCustom>(pkt->getOption(DHO_HOST_NAME)));
    }

    // Create a message holding DHCPv4 Client FQDN Option.
    Pkt4Ptr generatePktWithFqdn(const uint8_t msg_type,
                                const uint8_t fqdn_flags,
                                const std::string& fqdn_domain_name,
                                Option4ClientFqdn::DomainNameType fqdn_type,
                                const bool include_prl,
                                const bool include_clientid = true) {
        Pkt4Ptr pkt = Pkt4Ptr(new Pkt4(msg_type, 1234));
        pkt->setRemoteAddr(IOAddress("192.0.2.3"));
        pkt->setIface("eth1");
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

    // Create a message holding a Hostname option.
    Pkt4Ptr generatePktWithHostname(const uint8_t msg_type,
                                    const std::string& hostname) {

        Pkt4Ptr pkt = Pkt4Ptr(new Pkt4(msg_type, 1234));
        pkt->setRemoteAddr(IOAddress("192.0.2.3"));
        // For DISCOVER we don't include server id, because client broadcasts
        // the message to all servers.
        if (msg_type != DHCPDISCOVER) {
            pkt->addOption(srv_->getServerID());
        }

        pkt->addOption(generateClientId());


        // Create Client FQDN Option with the specified flags and
        // domain-name.
        pkt->addOption(createHostname(hostname));

        return (pkt);

    }

    // Test that server generates the appropriate FQDN option in response to
    // client's FQDN option.
    void testProcessFqdn(const Pkt4Ptr& query, const uint8_t exp_flags,
                         const std::string& exp_domain_name,
                         Option4ClientFqdn::DomainNameType
                         exp_domain_type = Option4ClientFqdn::FULL) {
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
        EXPECT_EQ(exp_domain_type, fqdn->getDomainNameType());

    }

    // Processes the Hostname option in the client's message and returns
    // the hostname option which would be sent to the client. It will
    // throw NULL pointer if the hostname option is not to be included
    // in the response.
    OptionCustomPtr processHostname(const Pkt4Ptr& query) {
        if (!getHostnameOption(query)) {
            ADD_FAILURE() << "Hostname option not carried in the query";
        }

        Pkt4Ptr answer;
        if (query->getType() == DHCPDISCOVER) {
            answer.reset(new Pkt4(DHCPOFFER, 1234));

        } else {
            answer.reset(new Pkt4(DHCPACK, 1234));

        }
        srv_->processClientName(query, answer);

        OptionCustomPtr hostname = getHostnameOption(answer);
        return (hostname);

    }

    // Test that the client message holding an FQDN is processed and the
    // NameChangeRequests are generated.
    void testProcessMessageWithFqdn(const uint8_t msg_type,
                            const std::string& hostname) {
        Pkt4Ptr req = generatePktWithFqdn(msg_type, Option4ClientFqdn::FLAG_S |
                                          Option4ClientFqdn::FLAG_E, hostname,
                                          Option4ClientFqdn::FULL, true);
        Pkt4Ptr reply;
        if (msg_type == DHCPDISCOVER) {
            ASSERT_NO_THROW(reply = srv_->processDiscover(req));

        } else if (msg_type == DHCPREQUEST) {
            ASSERT_NO_THROW(reply = srv_->processRequest(req));

        } else if (msg_type == DHCPRELEASE) {
            ASSERT_NO_THROW(srv_->processRelease(req));
            return;

        } else {
            return;
        }

        if (msg_type == DHCPDISCOVER) {
            checkResponse(reply, DHCPOFFER, 1234);

        } else {
            checkResponse(reply, DHCPACK, 1234);
        }

    }

    // Verify that NameChangeRequest holds valid values.
    void verifyNameChangeRequest(const isc::dhcp_ddns::NameChangeType type,
                                 const bool reverse, const bool forward,
                                 const std::string& addr,
                                 const std::string& fqdn,
                                 const std::string& dhcid,
                                 const time_t cltt,
                                 const uint16_t len,
                                 const bool not_strict_expire_check = false) {
        NameChangeRequest ncr = srv_->name_change_reqs_.front();
        EXPECT_EQ(type, ncr.getChangeType());
        EXPECT_EQ(forward, ncr.isForwardChange());
        EXPECT_EQ(reverse, ncr.isReverseChange());
        EXPECT_EQ(addr, ncr.getIpAddress());
        EXPECT_EQ(fqdn, ncr.getFqdn());
        // Compare dhcid if it is not empty. In some cases, the DHCID is
        // not known in advance and can't be compared.
        if (!dhcid.empty()) {
            EXPECT_EQ(dhcid, ncr.getDhcid().toStr());
        }
        // In some cases, the test doesn't have access to the last transmission
        // time for the particular client. In such cases, the test can use the
        // current time as cltt but the it may not check the lease expiration time
        // for equality but rather check that the lease expiration time is not
        // greater than the current time + lease lifetime.
        if (not_strict_expire_check) {
            EXPECT_GE(cltt + len, ncr.getLeaseExpiresOn());
        } else {
            EXPECT_EQ(cltt + len, ncr.getLeaseExpiresOn());
        }
        EXPECT_EQ(len, ncr.getLeaseLength());
        EXPECT_EQ(isc::dhcp_ddns::ST_NEW, ncr.getStatus());
        srv_->name_change_reqs_.pop();
    }

    NakedDhcpv4Srv* srv_;

};

// Test that the exception is thrown if lease pointer specified as the argument
// of computeDhcid function is NULL.
TEST_F(NameDhcpv4SrvTest, dhcidNullLease) {
    Lease4Ptr lease;
    EXPECT_THROW(srv_->computeDhcid(lease), isc::dhcp::DhcidComputeError);

}

// Test that the appropriate exception is thrown if the lease object used
// to compute DHCID comprises wrong hostname.
TEST_F(NameDhcpv4SrvTest, dhcidWrongHostname) {
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
TEST_F(NameDhcpv4SrvTest, dhcidComputeFromClientId) {
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
TEST_F(NameDhcpv4SrvTest, dhcidComputeFromHWAddr) {
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
TEST_F(NameDhcpv4SrvTest, serverUpdateForwardFqdn) {
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

// Test that server processes the Hostname option sent by a client and
// responds with the Hostname option to confirm that the server has
// taken responsibility for the update.
TEST_F(NameDhcpv4SrvTest, serverUpdateHostname) {
    Pkt4Ptr query;
    ASSERT_NO_THROW(query = generatePktWithHostname(DHCPREQUEST,
                                                    "myhost.example.com."));
    OptionCustomPtr hostname;
    ASSERT_NO_THROW(hostname = processHostname(query));

    ASSERT_TRUE(hostname);
    EXPECT_EQ("myhost.example.com.", hostname->readString());

}

// Test that the server skips processing of the empty Hostname option.
TEST_F(NameDhcpv4SrvTest, serverUpdateEmptyHostname) {
    Pkt4Ptr query;
    ASSERT_NO_THROW(query = generatePktWithHostname(DHCPREQUEST, ""));
    OptionCustomPtr hostname;
    ASSERT_NO_THROW(hostname = processHostname(query));
    EXPECT_FALSE(hostname);
}

// Test that the server skips processing of a wrong Hostname option.
TEST_F(NameDhcpv4SrvTest, serverUpdateWrongHostname) {
    Pkt4Ptr query;
    ASSERT_NO_THROW(query = generatePktWithHostname(DHCPREQUEST,
                                                    "abc..example.com"));
    OptionCustomPtr hostname;
    ASSERT_NO_THROW(hostname = processHostname(query));
    EXPECT_FALSE(hostname);
}


// Test that server generates the fully qualified domain name for the client
// if client supplies the partial name.
TEST_F(NameDhcpv4SrvTest, serverUpdateForwardPartialNameFqdn) {
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
// if client supplies the unqualified name in the Hostname option.
TEST_F(NameDhcpv4SrvTest, serverUpdateUnqualifiedHostname) {
    Pkt4Ptr query;
    ASSERT_NO_THROW(query = generatePktWithHostname(DHCPREQUEST, "myhost"));
    OptionCustomPtr hostname;
    ASSERT_NO_THROW(hostname =  processHostname(query));

    ASSERT_TRUE(hostname);
    EXPECT_EQ("myhost.example.com.", hostname->readString());

}

// Test that server sets empty domain-name in the FQDN option when client
// supplied no domain-name. The domain-name is supposed to be set after the
// lease is acquired. The domain-name is then generated from the IP address
// assigned to a client.
TEST_F(NameDhcpv4SrvTest, serverUpdateForwardNoNameFqdn) {
    Pkt4Ptr query = generatePktWithFqdn(DHCPREQUEST,
                                        Option4ClientFqdn::FLAG_E |
                                        Option4ClientFqdn::FLAG_S,
                                        "",
                                        Option4ClientFqdn::PARTIAL,
                                        true);

    testProcessFqdn(query,
                    Option4ClientFqdn::FLAG_E | Option4ClientFqdn::FLAG_S,
                    "", Option4ClientFqdn::PARTIAL);

}

// Test server's response when client requests no DNS update.
TEST_F(NameDhcpv4SrvTest, noUpdateFqdn) {
    Pkt4Ptr query = generatePktWithFqdn(DHCPREQUEST,
                                        Option4ClientFqdn::FLAG_E |
                                        Option4ClientFqdn::FLAG_N,
                                        "myhost.example.com.",
                                        Option4ClientFqdn::FULL,
                                        true);
    testProcessFqdn(query, Option4ClientFqdn::FLAG_E |
                    Option4ClientFqdn::FLAG_N,
                    "myhost.example.com.");
}

// Test that server does not accept delegation of the forward DNS update
// to a client.
TEST_F(NameDhcpv4SrvTest, clientUpdateNotAllowedFqdn) {
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
TEST_F(NameDhcpv4SrvTest, createNameChangeRequestsNewLease) {
    Lease4Ptr lease = createLease(IOAddress("192.0.2.3"), "myhost.example.com.",
                                  true, true);
    Lease4Ptr old_lease;

    ASSERT_NO_THROW(srv_->createNameChangeRequests(lease, old_lease));
    ASSERT_EQ(1, srv_->name_change_reqs_.size());

    verifyNameChangeRequest(isc::dhcp_ddns::CHG_ADD, true, true,
                            "192.0.2.3", "myhost.example.com.",
                            "00010132E91AA355CFBB753C0F0497A5A940436965"
                            "B68B6D438D98E680BF10B09F3BCF",
                            lease->cltt_, 100);
}

// Test that no NameChangeRequest is generated when a lease is renewed and
// the FQDN data hasn't changed.
TEST_F(NameDhcpv4SrvTest, createNameChangeRequestsRenewNoChange) {
    Lease4Ptr lease = createLease(IOAddress("192.0.2.3"), "myhost.example.com.",
                                  true, true);
    Lease4Ptr old_lease = createLease(IOAddress("192.0.2.3"),
                                      "myhost.example.com.", true, true);
    old_lease->valid_lft_ += 100;

    ASSERT_NO_THROW(srv_->createNameChangeRequests(lease, old_lease));
    EXPECT_TRUE(srv_->name_change_reqs_.empty());
}

// Test that no NameChangeRequest is generated when forward and reverse
// DNS update flags are not set in the lease.
TEST_F(NameDhcpv4SrvTest, createNameChangeRequestsNoUpdate) {
    Lease4Ptr lease1 = createLease(IOAddress("192.0.2.3"),
                                   "lease1.example.com.",
                                   true, true);
    Lease4Ptr lease2 = createLease(IOAddress("192.0.2.3"),
                                   "lease2.example.com.",
                                   false, false);
    ASSERT_NO_THROW(srv_->createNameChangeRequests(lease2, lease1));
    EXPECT_EQ(1, srv_->name_change_reqs_.size());

    verifyNameChangeRequest(isc::dhcp_ddns::CHG_REMOVE, true, true,
                            "192.0.2.3", "lease1.example.com.",
                            "0001013A5B311F5B9FB10DDF8E53689B874F25D"
                            "62CC147C2FF237A64C90E5A597C9B7A",
                            lease1->cltt_, 100);

    lease2->hostname_ = "";
    lease2->fqdn_rev_ = true;
    lease2->fqdn_fwd_ = true;
    ASSERT_NO_THROW(srv_->createNameChangeRequests(lease2, lease1));
    EXPECT_EQ(1, srv_->name_change_reqs_.size());

}

// Test that two NameChangeRequests are generated when the lease is being
// renewed and the new lease has updated FQDN data.
TEST_F(NameDhcpv4SrvTest, createNameChangeRequestsRenew) {
    Lease4Ptr lease1 = createLease(IOAddress("192.0.2.3"),
                                   "lease1.example.com.",
                                   true, true);
    Lease4Ptr lease2 = createLease(IOAddress("192.0.2.3"),
                                   "lease2.example.com.",
                                   true, true);
    ASSERT_NO_THROW(srv_->createNameChangeRequests(lease2, lease1));
    ASSERT_EQ(2, srv_->name_change_reqs_.size());

    verifyNameChangeRequest(isc::dhcp_ddns::CHG_REMOVE, true, true,
                            "192.0.2.3", "lease1.example.com.",
                            "0001013A5B311F5B9FB10DDF8E53689B874F25D"
                            "62CC147C2FF237A64C90E5A597C9B7A",
                            lease1->cltt_, 100);

    verifyNameChangeRequest(isc::dhcp_ddns::CHG_ADD, true, true,
                            "192.0.2.3", "lease2.example.com.",
                            "000101F906D2BB752E1B2EECC5FF2BF434C0B2D"
                            "D6D7F7BD873F4F280165DB8C9DBA7CB",
                            lease2->cltt_, 100);

}

// This test verifies that exception is thrown when leases passed to the
// createNameChangeRequests function do not match, i.e. they comprise
// different IP addresses, client ids etc.
TEST_F(NameDhcpv4SrvTest, createNameChangeRequestsLeaseMismatch) {
    Lease4Ptr lease1 = createLease(IOAddress("192.0.2.3"),
                                   "lease1.example.com.",
                                   true, true);
    Lease4Ptr lease2 = createLease(IOAddress("192.0.2.4"),
                                   "lease2.example.com.",
                                   true, true);
    EXPECT_THROW(srv_->createNameChangeRequests(lease2, lease1),
                 isc::Unexpected);
}

// Test that the OFFER message generated as a result of the DISCOVER message
// processing will not result in generation of the NameChangeRequests.
TEST_F(NameDhcpv4SrvTest, processDiscover) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    Pkt4Ptr req = generatePktWithFqdn(DHCPDISCOVER, Option4ClientFqdn::FLAG_S |
                                      Option4ClientFqdn::FLAG_E,
                                      "myhost.example.com.",
                                      Option4ClientFqdn::FULL, true);

    Pkt4Ptr reply;
    ASSERT_NO_THROW(reply = srv_->processDiscover(req));
    checkResponse(reply, DHCPOFFER, 1234);

    EXPECT_TRUE(srv_->name_change_reqs_.empty());
}

// Test that server generates client's hostname from the IP address assigned
// to it when DHCPv4 Client FQDN option specifies an empty domain-name.
TEST_F(NameDhcpv4SrvTest, processRequestFqdnEmptyDomainName) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    Pkt4Ptr req = generatePktWithFqdn(DHCPREQUEST, Option4ClientFqdn::FLAG_S |
                                      Option4ClientFqdn::FLAG_E,
                                      "", Option4ClientFqdn::PARTIAL, true);

    Pkt4Ptr reply;
    ASSERT_NO_THROW(reply = srv_->processRequest(req));

    checkResponse(reply, DHCPACK, 1234);

    // Verify that there is one NameChangeRequest generated.
    ASSERT_EQ(1, srv_->name_change_reqs_.size());
    // The hostname is generated from the IP address acquired (yiaddr).
    std::ostringstream hostname;
    hostname << generatedNameFromAddress(reply->getYiaddr())
             << ".example.com.";
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_ADD, true, true,
                            reply->getYiaddr().toText(), hostname.str(),
                            "", // empty DHCID forces that it is not checked
                            time(NULL) + subnet_->getValid(),
                            subnet_->getValid(), true);
}

// Test that server generates client's hostname from the IP address assigned
// to it when Hostname option carries the top level domain-name.
TEST_F(NameDhcpv4SrvTest, processRequestEmptyHostname) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    Pkt4Ptr req = generatePktWithHostname(DHCPREQUEST, ".");
    // Set interface for the incoming packet. The server requires it to
    // generate client id.
    req->setIface("eth1");

    Pkt4Ptr reply;
    ASSERT_NO_THROW(reply = srv_->processRequest(req));

    checkResponse(reply, DHCPACK, 1234);

    // Verify that there is one NameChangeRequest generated.
    ASSERT_EQ(1, srv_->name_change_reqs_.size());
    // The hostname is generated from the IP address acquired (yiaddr).
    std::ostringstream hostname;
    hostname << generatedNameFromAddress(reply->getYiaddr()) << ".example.com.";
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_ADD, true, true,
                            reply->getYiaddr().toText(), hostname.str(),
                            "", // empty DHCID forces that it is not checked
                            time(NULL), subnet_->getValid(), true);
}

// Test that client may send two requests, each carrying FQDN option with
// a different domain-name. Server should use existing lease for the second
// request but modify the DNS entries for the lease according to the contents
// of the FQDN sent in the second request.
TEST_F(NameDhcpv4SrvTest, processTwoRequestsFqdn) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    Pkt4Ptr req1 = generatePktWithFqdn(DHCPREQUEST, Option4ClientFqdn::FLAG_S |
                                       Option4ClientFqdn::FLAG_E,
                                       "myhost.example.com.",
                                       Option4ClientFqdn::FULL, true);

    Pkt4Ptr reply;
    ASSERT_NO_THROW(reply = srv_->processRequest(req1));

    checkResponse(reply, DHCPACK, 1234);

    // Verify that there is one NameChangeRequest generated.
    ASSERT_EQ(1, srv_->name_change_reqs_.size());
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_ADD, true, true,
                            reply->getYiaddr().toText(), "myhost.example.com.",
                            "00010132E91AA355CFBB753C0F0497A5A940436"
                            "965B68B6D438D98E680BF10B09F3BCF",
                            time(NULL), subnet_->getValid(), true);

    // Create another Request message but with a different FQDN. Server
    // should generate two NameChangeRequests: one to remove existing entry,
    // another one to add new entry with updated domain-name.
    Pkt4Ptr req2 = generatePktWithFqdn(DHCPREQUEST, Option4ClientFqdn::FLAG_S |
                                       Option4ClientFqdn::FLAG_E,
                                       "otherhost.example.com.",
                                       Option4ClientFqdn::FULL, true);

    ASSERT_NO_THROW(reply = srv_->processRequest(req2));

    checkResponse(reply, DHCPACK, 1234);

    // There should be two NameChangeRequests. Verify that they are valid.
    ASSERT_EQ(2, srv_->name_change_reqs_.size());
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_REMOVE, true, true,
                            reply->getYiaddr().toText(),
                            "myhost.example.com.",
                            "00010132E91AA355CFBB753C0F0497A5A940436"
                            "965B68B6D438D98E680BF10B09F3BCF",
                            time(NULL), subnet_->getValid(), true);

    verifyNameChangeRequest(isc::dhcp_ddns::CHG_ADD, true, true,
                            reply->getYiaddr().toText(),
                            "otherhost.example.com.",
                            "000101A5AEEA7498BD5AD9D3BF600E49FF39A7E3"
                            "AFDCE8C3D0E53F35CC584DD63C89CA",
                            time(NULL), subnet_->getValid(), true);
}

// Test that client may send two requests, each carrying Hostname option with
// a different name. Server should use existing lease for the second request
// but modify the DNS entries for the lease according to the contents of the
// Hostname sent in the second request.
TEST_F(NameDhcpv4SrvTest, processTwoRequestsHostname) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    Pkt4Ptr req1 = generatePktWithHostname(DHCPREQUEST, "myhost.example.com.");

    // Set interface for the incoming packet. The server requires it to
    // generate client id.
    req1->setIface("eth1");


    Pkt4Ptr reply;
    ASSERT_NO_THROW(reply = srv_->processRequest(req1));

    checkResponse(reply, DHCPACK, 1234);

    // Verify that there is one NameChangeRequest generated.
    ASSERT_EQ(1, srv_->name_change_reqs_.size());
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_ADD, true, true,
                            reply->getYiaddr().toText(), "myhost.example.com.",
                            "00010132E91AA355CFBB753C0F0497A5A940436"
                            "965B68B6D438D98E680BF10B09F3BCF",
                            time(NULL), subnet_->getValid(), true);

    // Create another Request message but with a different Hostname. Server
    // should generate two NameChangeRequests: one to remove existing entry,
    // another one to add new entry with updated domain-name.
    Pkt4Ptr req2 = generatePktWithHostname(DHCPREQUEST, "otherhost");

    // Set interface for the incoming packet. The server requires it to
    // generate client id.
    req2->setIface("eth1");

    ASSERT_NO_THROW(reply = srv_->processRequest(req2));

    checkResponse(reply, DHCPACK, 1234);

    // There should be two NameChangeRequests. Verify that they are valid.
    ASSERT_EQ(2, srv_->name_change_reqs_.size());
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_REMOVE, true, true,
                            reply->getYiaddr().toText(),
                            "myhost.example.com.",
                            "00010132E91AA355CFBB753C0F0497A5A940436"
                            "965B68B6D438D98E680BF10B09F3BCF",
                            time(NULL), subnet_->getValid(), true);

    verifyNameChangeRequest(isc::dhcp_ddns::CHG_ADD, true, true,
                            reply->getYiaddr().toText(),
                            "otherhost.example.com.",
                            "000101A5AEEA7498BD5AD9D3BF600E49FF39A7E3"
                            "AFDCE8C3D0E53F35CC584DD63C89CA",
                            time(NULL), subnet_->getValid(), true);
}

// Test that when the Release message is sent for the previously acquired
// lease, then server genenerates a NameChangeRequest to remove the entries
// corresponding to the lease being released.
TEST_F(NameDhcpv4SrvTest, processRequestRelease) {
    IfaceMgrTestConfig test_config(true);
    IfaceMgr::instance().openSockets4();

    Pkt4Ptr req = generatePktWithFqdn(DHCPREQUEST, Option4ClientFqdn::FLAG_S |
                                      Option4ClientFqdn::FLAG_E,
                                      "myhost.example.com.",
                                      Option4ClientFqdn::FULL, true);

    Pkt4Ptr reply;
    ASSERT_NO_THROW(reply = srv_->processRequest(req));

    checkResponse(reply, DHCPACK, 1234);

    // Verify that there is one NameChangeRequest generated.
    ASSERT_EQ(1, srv_->name_change_reqs_.size());
    verifyNameChangeRequest(isc::dhcp_ddns::CHG_ADD, true, true,
                            reply->getYiaddr().toText(), "myhost.example.com.",
                            "00010132E91AA355CFBB753C0F0497A5A940436"
                            "965B68B6D438D98E680BF10B09F3BCF",
                            time(NULL), subnet_->getValid(), true);

    // Create a Release message.
    Pkt4Ptr rel = Pkt4Ptr(new Pkt4(DHCPRELEASE, 1234));
    rel->setCiaddr(reply->getYiaddr());
    rel->setRemoteAddr(IOAddress("192.0.2.3"));
    rel->addOption(generateClientId());
    rel->addOption(srv_->getServerID());

    ASSERT_NO_THROW(srv_->processRelease(rel));

    // The lease has been removed, so there should be a NameChangeRequest to
    // remove corresponding DNS entries.
    ASSERT_EQ(1, srv_->name_change_reqs_.size());
}

} // end of anonymous namespace
