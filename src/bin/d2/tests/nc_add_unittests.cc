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

#include <d2/nc_add.h>

#include <boost/function.hpp>
#include <boost/bind.hpp>
#include <gtest/gtest.h>

using namespace std;
using namespace isc;
using namespace isc::d2;

namespace {

/// @brief Test class derived from NameAddTransaction to provide visiblity
// to protected methods.
class NameAddStub : public NameAddTransaction {
public:
    NameAddStub(IOServicePtr& io_service,
                dhcp_ddns::NameChangeRequestPtr& ncr,
                DdnsDomainPtr& forward_domain,
                DdnsDomainPtr& reverse_domain)
        : NameAddTransaction(io_service, ncr, forward_domain, reverse_domain){
    }

    virtual ~NameAddStub() {
    }

    using NameAddTransaction::defineEvents;
    using NameAddTransaction::verifyEvents;
    using NameAddTransaction::defineStates;
    using NameAddTransaction::verifyStates;
};

typedef boost::shared_ptr<NameAddStub> NameAddStubPtr;

/// @brief Test fixture for testing NameAddTransaction
///
/// Note this class uses NameAddStub class to exercise non-public
/// aspects of NameAddTransaction.
class NameAddTransactionTest : public ::testing::Test {
public:
    IOServicePtr io_service_;
    DdnsDomainPtr forward_domain_;
    DdnsDomainPtr reverse_domain_;

    NameAddTransactionTest() : io_service_(new isc::asiolink::IOService()) {
    }

    virtual ~NameAddTransactionTest() {
    }

    /// @brief Instantiates a NameAddTransaction built around a canned
    /// NameChangeRequest.
    NameAddStubPtr makeCannedTransaction() {
        const char* msg_str =
            "{"
            " \"change_type\" : 0 , "
            " \"forward_change\" : true , "
            " \"reverse_change\" : true , "
            " \"fqdn\" : \"example.com.\" , "
            " \"ip_address\" : \"192.168.2.1\" , "
            " \"dhcid\" : \"0102030405060708\" , "
            " \"lease_expires_on\" : \"20130121132405\" , "
            " \"lease_length\" : 1300 "
            "}";

        dhcp_ddns::NameChangeRequestPtr ncr;

        DnsServerInfoStoragePtr servers(new DnsServerInfoStorage());
        DnsServerInfoPtr server;

        ncr = dhcp_ddns::NameChangeRequest::fromJSON(msg_str);

        // make forward server list
        server.reset(new DnsServerInfo("forward.example.com",
                                       isc::asiolink::IOAddress("1.1.1.1")));
        servers->push_back(server);
        forward_domain_.reset(new DdnsDomain("*", "", servers));

        // make reverse server list
        servers->clear();
        server.reset(new DnsServerInfo("reverse.example.com",
                                       isc::asiolink::IOAddress("2.2.2.2")));
        servers->push_back(server);
        reverse_domain_.reset(new DdnsDomain("*", "", servers));
        return (NameAddStubPtr(new NameAddStub(io_service_, ncr,
                                      forward_domain_, reverse_domain_)));

    }

};

/// @brief Tests NameAddTransaction construction.
/// This test verifies that:
/// 1. Construction with invalid type of request
/// 2. Valid construction functions properly
TEST(NameAddTransaction, construction) {
    IOServicePtr io_service(new isc::asiolink::IOService());

    const char* msg_str =
        "{"
        " \"change_type\" : 1 , "
        " \"forward_change\" : true , "
        " \"reverse_change\" : true , "
        " \"fqdn\" : \"example.com.\" , "
        " \"ip_address\" : \"192.168.2.1\" , "
        " \"dhcid\" : \"0102030405060708\" , "
        " \"lease_expires_on\" : \"20130121132405\" , "
        " \"lease_length\" : 1300 "
        "}";

    dhcp_ddns::NameChangeRequestPtr ncr;
    DnsServerInfoStoragePtr servers;
    DdnsDomainPtr forward_domain;
    DdnsDomainPtr reverse_domain;
    DdnsDomainPtr empty_domain;

    ASSERT_NO_THROW(ncr = dhcp_ddns::NameChangeRequest::fromJSON(msg_str));
    ASSERT_NO_THROW(forward_domain.reset(new DdnsDomain("*", "", servers)));
    ASSERT_NO_THROW(reverse_domain.reset(new DdnsDomain("*", "", servers)));

    // Verify that construction with wrong change type fails.
    EXPECT_THROW(NameAddTransaction(io_service, ncr,
                                    forward_domain, reverse_domain),
                                    NameAddTransactionError);

    // Verify that a valid construction attempt works.
    ncr->setChangeType(isc::dhcp_ddns::CHG_ADD);
    EXPECT_NO_THROW(NameAddTransaction(io_service, ncr,
                                       forward_domain, reverse_domain));
}

/// @brief Tests event and state dictionary construction and verification.
TEST_F(NameAddTransactionTest, dictionaryCheck) {
    NameAddStubPtr name_add;
    ASSERT_NO_THROW(name_add = makeCannedTransaction());

    // Verify that the event and state dictionary validation fails prior
    // dictionary construction.
    ASSERT_THROW(name_add->verifyEvents(), StateModelError);
    ASSERT_THROW(name_add->verifyStates(), StateModelError);

    // Construct both dictionaries.
    ASSERT_NO_THROW(name_add->defineEvents());
    ASSERT_NO_THROW(name_add->defineStates());

    // Verify both event and state dictionaries now pass validation.
    ASSERT_NO_THROW(name_add->verifyEvents());
    ASSERT_NO_THROW(name_add->verifyStates());
}

}
