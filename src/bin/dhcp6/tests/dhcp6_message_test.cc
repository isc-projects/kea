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

#include <dhcp6/tests/dhcp6_message_test.h>

using namespace isc::asiolink;

namespace isc {
namespace dhcp {
namespace test {

Dhcpv6MessageTest::Dhcpv6MessageTest()
    : Dhcpv6SrvTest(),
      iface_mgr_test_config_(true) {
}

IOAddress
Dhcpv6MessageTest::bumpAddress(const IOAddress& input_addr) {
    return (bumpByteInAddress(input_addr, V6ADDRESS_LEN - 1));
}

IOAddress
Dhcpv6MessageTest::bumpByteInAddress(const IOAddress& input_addr,
                                     const size_t byte_num) {
    std::vector<uint8_t> input_addr_buffer = input_addr.toBytes();
    if (input_addr_buffer.size() > byte_num) {
        ++input_addr_buffer[byte_num];
        return (IOAddress::fromBytes(AF_INET6, &input_addr_buffer[0]));
    }
    return (input_addr);
}

IOAddress
Dhcpv6MessageTest::bumpSubnet(const IOAddress& input_addr) {
    return (bumpByteInAddress(input_addr, 0));
}

void
Dhcpv6MessageTest::requestLease(const std::string& config,
                                const int subnets_num,
                                Dhcp6Client& client) {
    // Configure the server.
    configure(config, *client.getServer());
    // Make sure we ended-up having expected number of subnets configured.
    const Subnet6Collection* subnets = CfgMgr::instance().getSubnets6();
    ASSERT_EQ(subnets_num, subnets->size());
    // Do the actual 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());
    // Simulate aging of leases, by moving their cltt_ back by 1000s.
    client.fastFwdTime(1000);
    // Make sure that we have obtained a lease that belongs to one of the
    // subnets.
    ASSERT_EQ(1, client.getLeaseNum());
    Lease6 lease_client = client.getLease(0);
    ASSERT_TRUE(CfgMgr::instance().getSubnet6(lease_client.addr_,
                                              ClientClasses()));
    // Check that the client's lease matches the information on the server
    // side.
    Lease6Ptr lease_server = checkLease(lease_client);
    ASSERT_TRUE(lease_server);
    // And that status code was OK.
    ASSERT_EQ(STATUS_Success, client.getStatusCode(0));
}

}
}
}
