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

#include <gtest/gtest.h>
#include <boost/scoped_ptr.hpp>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
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
                                const bool include_prl) {
        Pkt4Ptr pkt = Pkt4Ptr(new Pkt4(msg_type, 1234));
        pkt->setRemoteAddr(IOAddress("192.0.2.3"));
        // For DISCOVER we don't include server id, because client broadcasts
        // the message to all servers.
        if (msg_type != DHCPDISCOVER) {
            pkt->addOption(srv_->getServerID());
        }
        // Client id is required.
        pkt->addOption(generateClientId());

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

private:
    NakedDhcpv4Srv* srv_;

};

TEST_F(FqdnDhcpv4SrvTest, basic) {
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

} // end of anonymous namespace
