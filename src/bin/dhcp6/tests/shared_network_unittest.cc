// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/option.h>
#include <dhcp/option_int.h>
#include <dhcp/option6_client_fqdn.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcp6/tests/dhcp6_client.h>
#include <dhcp6/tests/dhcp6_test_utils.h>
#include <stats/stats_mgr.h>
#include <boost/pointer_cast.hpp>
#include <vector>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::stats;

namespace {

/// @brief Array of server configurations used throughout the tests.
const char* NETWORKS_CONFIG[] = {
// Configuration #0.
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"preferred-lifetime\": 3000,"
    "    \"rebind-timer\": 2000, "
    "    \"renew-timer\": 1000, "
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface\": \"eth1\","
    "            \"subnet6\": ["
    "                {"
    "                    \"subnet\": \"2001:db8:1::/64\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:1::20 - 2001:db8:1::20\""
    "                        }"
    "                    ],"
    "                    \"pd-pools\": ["
    "                        {"
    "                            \"prefix\": \"4000::\","
    "                            \"prefix-len\": 96,"
    "                            \"delegated-len\": 96"
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"2001:db8:2::/64\","
    "                    \"id\": 100,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:2::20 - 2001:db8:2::20\""
    "                        }"
    "                    ],"
    "                    \"pd-pools\": ["
    "                        {"
    "                            \"prefix\": \"5000::\","
    "                            \"prefix-len\": 96,"
    "                            \"delegated-len\": 96"
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ],"
    "    \"subnet6\": ["
    "        {"
    "            \"subnet\": \"3000::/96\","
    "            \"id\": 1000,"
    "            \"interface\": \"eth0\","
    "            \"pools\": ["
    "                {"
    "                    \"pool\": \"3000::1 - 3000::1\""
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #1.
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"preferred-lifetime\": 3000,"
    "    \"rebind-timer\": 2000, "
    "    \"renew-timer\": 1000, "
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"relay\": {"
    "                \"ip-address\": \"3001::1\""
    "            },"
    "            \"subnet6\": ["
    "                {"
    "                    \"subnet\": \"2001:db8:1::/64\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:1::20 - 2001:db8:1::20\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ],"
    "    \"subnet6\": ["
    "        {"
    "            \"subnet\": \"2001:db8:2::/64\","
    "            \"id\": 1000,"
    "            \"relay\": {"
    "                \"ip-address\": \"3001::2\""
    "            },"
    "            \"pools\": ["
    "                {"
    "                    \"pool\": \"2001:db8:2::20 - 2001:db8:2::20\""
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #2.
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"preferred-lifetime\": 3000,"
    "    \"rebind-timer\": 2000, "
    "    \"renew-timer\": 1000, "
    "    \"client-classes\": ["
    "        {"
    "            \"name\": \"a-devices\","
    "            \"test\": \"option[1234].hex == 0x0001\""
    "        },"
    "        {"
    "            \"name\": \"b-devices\","
    "            \"test\": \"option[1234].hex == 0x0002\""
    "        }"
    "    ],"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface\": \"eth1\","
    "            \"subnet6\": ["
    "                {"
    "                    \"subnet\": \"2001:db8:1::/64\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:1::20 - 2001:db8:1::20\""
    "                        }"
    "                    ],"
    "                    \"client-class\": \"a-devices\""
    "                },"
    "                {"
    "                    \"subnet\": \"2001:db8:2::/64\","
    "                    \"id\": 100,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:2::20 - 2001:db8:2::20\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #3.
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"preferred-lifetime\": 3000,"
    "    \"rebind-timer\": 2000, "
    "    \"renew-timer\": 1000, "
    "    \"client-classes\": ["
    "        {"
    "            \"name\": \"a-devices\","
    "            \"test\": \"option[1234].hex == 0x0001\""
    "        },"
    "        {"
    "            \"name\": \"b-devices\","
    "            \"test\": \"option[1234].hex == 0x0002\""
    "        }"
    "    ],"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface\": \"eth1\","
    "            \"subnet6\": ["
    "                {"
    "                    \"subnet\": \"2001:db8:1::/64\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:1::20 - 2001:db8:1::20\""
    "                        }"
    "                    ],"
    "                    \"client-class\": \"a-devices\""
    "                },"
    "                {"
    "                    \"subnet\": \"2001:db8:2::/64\","
    "                    \"id\": 100,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:2::20 - 2001:db8:2::20\""
    "                        }"
    "                    ],"
    "                    \"client-class\": \"b-devices\""
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #4.
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"preferred-lifetime\": 3000,"
    "    \"rebind-timer\": 2000, "
    "    \"renew-timer\": 1000, "
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface\": \"eth1\","
    "            \"subnet6\": ["
    "                {"
    "                    \"subnet\": \"2001:db8:1::/64\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:1::1 - 2001:db8:1::64\""
    "                        }"
    "                    ],"
    "                    \"pd-pools\": ["
    "                        {"
    "                            \"prefix\": \"4000::\","
    "                            \"prefix-len\": 96,"
    "                            \"delegated-len\": 96"
    "                        }"
    "                    ],"
    "                    \"reservations\": ["
    "                        {"
    "                            \"duid\": \"00:03:00:01:aa:bb:cc:dd:ee:ff\","
    "                            \"ip-addresses\": [ \"2001:db8:1::28\" ]"
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"2001:db8:2::/64\","
    "                    \"id\": 100,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:2::1 - 2001:db8:2::64\""
    "                        }"
    "                    ],"
    "                    \"pd-pools\": ["
    "                        {"
    "                            \"prefix\": \"5000::\","
    "                            \"prefix-len\": 96,"
    "                            \"delegated-len\": 96"
    "                        }"
    "                    ],"
    "                    \"reservations\": ["
    "                        {"
    "                            \"duid\": \"00:03:00:01:11:22:33:44:55:66\","
    "                            \"ip-addresses\": [ \"2001:db8:2::28\" ],"
    "                            \"prefixes\": [ \"1234::/64\" ]"
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #5.
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"preferred-lifetime\": 3000,"
    "    \"rebind-timer\": 2000, "
    "    \"renew-timer\": 1000, "
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface\": \"eth1\","
    "            \"subnet6\": ["
    "                {"
    "                    \"subnet\": \"2001:db8:1::/64\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:1::1 - 2001:db8:1::64\""
    "                        }"
    "                    ],"
    "                    \"reservations\": ["
    "                        {"
    "                            \"duid\": \"00:03:00:01:11:22:33:44:55:66\","
    "                            \"ip-addresses\": [ \"2001:db8:1::28\" ]"
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"2001:db8:2::/64\","
    "                    \"id\": 100,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:2::1 - 2001:db8:2::64\""
    "                        }"
    "                    ],"
    "                    \"reservations\": ["
    "                        {"
    "                            \"duid\": \"00:03:00:01:aa:bb:cc:dd:ee:ff\","
    "                            \"ip-addresses\": [ \"2001:db8:2::28\" ]"
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #6.
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"preferred-lifetime\": 3000,"
    "    \"rebind-timer\": 2000, "
    "    \"renew-timer\": 1000, "
    "    \"client-classes\": ["
    "        {"
    "            \"name\": \"a-devices\","
    "            \"test\": \"option[1234].hex == 0x0001\""
    "        }"
    "    ],"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface\": \"eth1\","
    "            \"subnet6\": ["
    "                {"
    "                    \"subnet\": \"2001:db8:1::/64\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:1::1 - 2001:db8:1::64\""
    "                        }"
    "                    ],"
    "                    \"client-class\": \"a-devices\","
    "                    \"reservations\": ["
    "                        {"
    "                            \"duid\": \"00:03:00:01:aa:bb:cc:dd:ee:ff\","
    "                            \"ip-addresses\": [ \"2001:db8:1::28\" ]"
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"2001:db8:2::/64\","
    "                    \"id\": 100,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:2::16 - 2001:db8:2::16\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #7.
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"preferred-lifetime\": 3000,"
    "    \"rebind-timer\": 2000, "
    "    \"renew-timer\": 1000, "
    "    \"option-data\": ["
    "        {"
    "            \"name\": \"nis-servers\","
    "            \"data\": \"3000::20\""
    "        }"
    "    ],"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface\": \"eth1\","
    "            \"option-data\": ["
    "                {"
    "                    \"name\": \"dns-servers\","
    "                    \"data\": \"3001::21\""
    "                },"
    "                {"
    "                    \"name\": \"nisp-servers\","
    "                    \"data\": \"3002::34\""
    "                }"
    "            ],"
    "            \"subnet6\": ["
    "                {"
    "                    \"subnet\": \"2001:db8:1::/64\","
    "                    \"id\": 10,"
    "                    \"option-data\": ["
    "                        {"
    "                            \"name\": \"sntp-servers\","
    "                            \"data\": \"4004::22\""
    "                        },"
    "                        {"
    "                            \"name\": \"nisp-servers\","
    "                            \"data\": \"3003::33\""
    "                        }"
    "                    ],"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:1::20 - 2001:db8:1::20\""
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"2001:db8:2::/64\","
    "                    \"id\": 100,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:2::20 - 2001:db8:2::20\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ],"
    "    \"subnet6\": ["
    "        \{"
    "            \"subnet\": \"3000::/96\","
    "            \"id\": 1000,"
    "            \"interface\": \"eth0\","
    "            \"option-data\": ["
    "                {"
    "                    \"name\": \"nisp-servers\","
    "                    \"data\": \"4000::5\""
    "                }"
    "            ],"
    "            \"pools\": ["
    "                {"
    "                    \"pool\": \"3000::1 - 3000::1\""
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #8.
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"preferred-lifetime\": 3000,"
    "    \"rebind-timer\": 2000, "
    "    \"renew-timer\": 1000, "
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface\": \"eth1\","
    "            \"subnet6\": ["
    "                {"
    "                    \"subnet\": \"2001:db8:1::/64\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:1::20 - 2001:db8:1::20\""
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"2001:db8:2::/64\","
    "                    \"id\": 100,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:2::20 - 2001:db8:2::20\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        },"
    "        {"
    "            \"name\": \"dog\","
    "            \"interface\": \"eth0\","
    "            \"subnet6\": ["
    "                {"
    "                    \"subnet\": \"2001:db8:3::/64\","
    "                    \"id\": 1000,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:3::20 - 2001:db8:3::20\""
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"2001:db8:4::/64\","
    "                    \"id\": 10000,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:4::20 - 2001:db8:4::20\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #9.
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"preferred-lifetime\": 3000,"
    "    \"rebind-timer\": 2000, "
    "    \"renew-timer\": 1000, "
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"relay\": {"
    "                \"ip-address\": \"3000::1\""
    "            },"
    "            \"subnet6\": ["
    "                {"
    "                    \"subnet\": \"2001:db8:1::/64\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:1::20 - 2001:db8:1::20\""
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"2001:db8:2::/64\","
    "                    \"id\": 100,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:2::20 - 2001:db8:2::20\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        },"
    "        {"
    "            \"name\": \"dog\","
    "            \"relay\": {"
    "                \"ip-address\": \"3000::2\""
    "            },"
    "            \"subnet6\": ["
    "                {"
    "                    \"subnet\": \"2001:db8:3::/64\","
    "                    \"id\": 1000,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:3::20 - 2001:db8:3::20\""
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"2001:db8:4::/64\","
    "                    \"id\": 10000,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:4::20 - 2001:db8:4::20\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #10.
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"preferred-lifetime\": 3000,"
    "    \"rebind-timer\": 2000, "
    "    \"renew-timer\": 1000, "
    "    \"client-classes\": ["
    "        {"
    "            \"name\": \"class-with-dns-servers\","
    "            \"option-data\": ["
    "                {"
    "                    \"name\": \"dns-servers\","
    "                    \"data\": \"2001:db8:1::50\""
    "                }"
    "            ]"
    "        }"
    "    ],"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface\": \"eth1\","
    "            \"subnet6\": ["
    "                {"
    "                    \"subnet\": \"2001:db8:1::/64\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:1::20 - 2001:db8:1::20\""
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"2001:db8:2::/64\","
    "                    \"id\": 100,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:2::20 - 2001:db8:2::30\""
    "                        }"
    "                    ],"
    "                    \"reservations\": ["
    "                        {"
    "                            \"duid\": \"00:03:00:01:11:22:33:44:55:66\","
    "                            \"ip-addresses\": [ \"2001:db8:2::20\" ],"
    "                            \"hostname\": \"test.example.org\","
    "                            \"client-classes\": [ \"class-with-dns-servers\" ]"
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #11.
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"preferred-lifetime\": 3000,"
    "    \"rebind-timer\": 2000, "
    "    \"renew-timer\": 1000, "
    "    \"client-classes\": ["
    "        {"
    "            \"name\": \"a-devices\","
    "            \"test\": \"option[1234].hex == 0x0001\""
    "        },"
    "        {"
    "            \"name\": \"b-devices\","
    "            \"test\": \"option[1234].hex == 0x0002\""
    "        }"
    "    ],"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface\": \"eth1\","
    "            \"client-class\": \"a-devices\","
    "            \"subnet6\": ["
    "                {"
    "                    \"subnet\": \"2001:db8:1::/64\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:1::20 - 2001:db8:1::20\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        },"
    "        {"
    "            \"name\": \"dog\","
    "            \"interface\": \"eth1\","
    "            \"client-class\": \"b-devices\","
    "            \"subnet6\": ["
    "                {"
    "                    \"subnet\": \"2001:db8:2::/64\","
    "                    \"id\": 1000,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:2::20 - 2001:db8:2::20\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}"
};

/// @Brief Test fixture class for DHCPv6 server using shared networks.
class Dhcpv6SharedNetworkTest : public Dhcpv6SrvTest {
public:

    /// @brief Constructor.
    Dhcpv6SharedNetworkTest()
        : Dhcpv6SrvTest(),
          iface_mgr_test_config_(true) {
        IfaceMgr::instance().openSockets6();
        StatsMgr::instance().removeAll();
    }

    /// @brief Conducts 4 packets exchanges for a client
    ///
    /// @param client this client will conduct the exchange
    /// @param exp_addr expected IPv6 address to be assigned
    /// @param iaid the iaid to be used by a client
    /// @param hint hint to be sent (if empty, no hint will be sent)
    void
    doSARR(Dhcp6Client& client, std::string exp_addr, uint32_t iaid,
           std::string hint = "") {
        if (hint.empty()) {
            ASSERT_NO_THROW(client.requestAddress(iaid, IOAddress("::")));
        } else {
            ASSERT_NO_THROW(client.requestAddress(iaid, IOAddress(hint)));
        }
        ASSERT_NO_THROW(client.doSARR());
        ASSERT_TRUE(client.hasLeaseForAddress(IOAddress(exp_addr)));
    }

    /// @brief Destructor.
    virtual ~Dhcpv6SharedNetworkTest() {
        StatsMgr::instance().removeAll();
    }

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;
};

// Running out of addresses within a subnet in a shared network.
TEST_F(Dhcpv6SharedNetworkTest, addressPoolInSharedNetworkShortage) {
    // Create client #1.
    Dhcp6Client client1;
    client1.setInterface("eth1");

    // Configure the server with one shared network including two subnets and
    // one subnet outside of the shared network.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[0], *client1.getServer()));

    // Client #1 requests an address in first subnet within a shared network.
    doSARR(client1, "2001:db8:1::20", 0xabca, "2001:db8:1::20");

    // Client #2 The second client will request a lease and should be assigned
    // an address from the second subnet.
    Dhcp6Client client2(client1.getServer());
    client2.setInterface("eth1");
    doSARR(client2, "2001:db8:2::20", 0xabca0, "");

    // Cient #3. It sends Solicit which should result in NoAddrsAvail status
    // code because all addresses available for this link have been assigned.
    Dhcp6Client client3(client1.getServer());
    client3.setInterface("eth1");
    ASSERT_NO_THROW(client3.requestAddress(0xabca0));
    ASSERT_NO_THROW(client3.doSolicit(true));
    EXPECT_EQ(0, client3.getLeaseNum());

    // Client #3 should be assigned an address if subnet 3 is selected for it.
    client3.setInterface("eth0");
    ASSERT_NO_THROW(client3.doSolicit(true));
    EXPECT_EQ(1, client3.getLeaseNum());

    // Client #1 should be able to renew its lease.
    ASSERT_NO_THROW(client1.doRenew());
    EXPECT_EQ(1, client1.getLeaseNum());
    EXPECT_TRUE(client1.hasLeaseForAddress(IOAddress("2001:db8:1::20")));

    // Client #2 should be able to renew its lease too.
    ASSERT_NO_THROW(client2.doRenew());
    EXPECT_EQ(1, client2.getLeaseNum());
    EXPECT_TRUE(client2.hasLeaseForAddress(IOAddress("2001:db8:2::20")));
}

// Shared network is selected based on relay link address.
TEST_F(Dhcpv6SharedNetworkTest, sharedNetworkSelectedByRelay) {
    // Create client #1. This is a relayed client which is using relay address
    // matching configured shared network.
    Dhcp6Client client1;
    client1.useRelay(true, IOAddress("3001::1"));

    // Configure the server with one shared network and one subnet outside of the
    // shared network.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[1], *client1.getServer()));

    // Client #1 should be assigned an address from shared network.
    doSARR(client1, "2001:db8:1::20", 0xabca, "");

    // Create client #2. This is a relayed client which is using relay
    // address matching subnet outside of the shared network.
    Dhcp6Client client2(client1.getServer());
    client2.useRelay(true, IOAddress("3001::2"));
    ASSERT_NO_THROW(client2.requestAddress(0xabca0));
    ASSERT_NO_THROW(client2.doSARR());
    ASSERT_TRUE(client2.hasLeaseForAddress(IOAddress("2001:db8:2::20")));
}

// Providing a hint for any address belonging to a shared network.
TEST_F(Dhcpv6SharedNetworkTest, hintWithinSharedNetwork) {
    // Create client #1.
    Dhcp6Client client;
    client.setInterface("eth1");

    // Configure the server with one shared network including two subnets and
    // one subnet outside of the shared network.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[0], *client.getServer()));

    // Provide a hint to an existing address within first subnet. This address
    // should be offered out of this subnet.
    ASSERT_NO_THROW(client.requestAddress(0xabca, IOAddress("2001:db8:1::20")));
    ASSERT_NO_THROW(client.doSolicit(true));
    ASSERT_TRUE(client.hasLeaseForAddress(IOAddress("2001:db8:1::20")));

    // Similarly, we should be offerred an address from another subnet within
    // the same shared network when we ask for it.
    client.clearRequestedIAs();
    ASSERT_NO_THROW(client.requestAddress(0xabca, IOAddress("2001:db8:2::20")));
    ASSERT_NO_THROW(client.doSolicit(true));
    ASSERT_TRUE(client.hasLeaseForAddress(IOAddress("2001:db8:2::20")));

    // Asking for an address that is not in address pool should result in getting
    // an address from one of the subnets, but generally hard to tell from which one.
    client.clearRequestedIAs();
    ASSERT_NO_THROW(client.requestAddress(0xabca, IOAddress("3002::123")));
    ASSERT_NO_THROW(client.doSolicit(true));
    std::vector<Lease6> leases = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases.size());
    if (!client.hasLeaseForAddress(IOAddress("2001:db8:1::20")) &&
        !client.hasLeaseForAddress(IOAddress("2001:db8:2::20"))) {
        ADD_FAILURE() << "Unexpected address advertised by the server " << leases.at(0).addr_;
    }
}

// Shared network is selected based on the client class specified.
TEST_F(Dhcpv6SharedNetworkTest, subnetInSharedNetworkSelectedByClass) {
    // Create client #1.
    Dhcp6Client client1;
    client1.setInterface("eth1");

    // Configure the server with one shared network including two subnets and
    // one subnet outside of the shared network.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[2], *client1.getServer()));

    // Client #1 requests an address in the restricted subnet but can't be assigned
    // this address because the client doesn't belong to a certain class.
    ASSERT_NO_THROW(client1.requestAddress(0xabca, IOAddress("2001:db8:1::20")));
    ASSERT_NO_THROW(client1.doSARR());
    ASSERT_TRUE(client1.hasLeaseForAddress(IOAddress("2001:db8:2::20")));

    // Release the lease that the client has got, because we'll need this address
    // further in the test.
    client1.doRelease();

    // Add option 1234 which would cause the client to be classified as "a-devices".
    OptionPtr option1234(new OptionUint16(Option::V6, 1234, 0x0001));
    client1.addExtraOption(option1234);

    // This time, the allocation of the address provided as hint should be successful.
    ASSERT_NO_THROW(client1.doSARR());
    ASSERT_TRUE(client1.hasLeaseForAddress(IOAddress("2001:db8:1::20")));


    // Client 2 should be assigned an address from the unrestricted subnet.
    Dhcp6Client client2(client1.getServer());
    client2.setInterface("eth1");
    ASSERT_NO_THROW(client2.requestAddress(0xabca0));
    ASSERT_NO_THROW(client2.doSARR());
    ASSERT_TRUE(client2.hasLeaseForAddress(IOAddress("2001:db8:2::20")));

    // Now, let's reconfigure the server to also apply restrictions on the
    // subnet to which client2 now belongs.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[3], *client1.getServer()));

    ASSERT_NO_THROW(client2.doRenew());
    EXPECT_EQ(0, client2.getLeaseNum());

    // If we add option 1234 with a value matching this class, the lease should
    // get renewed.
    OptionPtr option1234_bis(new OptionUint16(Option::V6, 1234, 0x0002));
    client2.addExtraOption(option1234_bis);
    ASSERT_NO_THROW(client2.doRenew());
    EXPECT_EQ(1, client2.getLeaseNum());
}

// IPv6 address reservation exists in one of the subnets within shared network.
TEST_F(Dhcpv6SharedNetworkTest, reservationInSharedNetwork) {
    // Create client #1. Explicitly set client's DUID to the one that has a
    // reservation in the second subnet within shared network.
    Dhcp6Client client1;
    client1.setInterface("eth1");
    client1.setDUID("00:03:00:01:11:22:33:44:55:66");

    // Create server configuration with a shared network including two subnets. There
    // is an IP address reservation in each subnet for two respective clients.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[4], *client1.getServer()));

    // Client #1 should get his reserved address from the second subnet.
    ASSERT_NO_THROW(client1.requestAddress(0xabca, IOAddress("2001:db8:1::20")));
    ASSERT_NO_THROW(client1.doSARR());
    ASSERT_TRUE(client1.hasLeaseForAddress(IOAddress("2001:db8:2::28")));

    // Create client #2.
    Dhcp6Client client2;
    client2.setInterface("eth1");
    client2.setDUID("00:03:00:01:aa:bb:cc:dd:ee:ff");

    // Client #2 should get its reserved address from the first subnet.
    ASSERT_NO_THROW(client2.requestAddress(0xabca, IOAddress("2001:db8:1::30")));
    ASSERT_NO_THROW(client2.doSARR());
    ASSERT_TRUE(client2.hasLeaseForAddress(IOAddress("2001:db8:1::28")));

    // Reconfigure the server. Now, the first client get's second client's
    // reservation and vice versa.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[5], *client1.getServer()));

    // The first client is trying to renew the lease but should get a different lease
    // because its lease is now reserved for some other client. The client won't be
    // assigned a lease for which it has a reservation because another client holds
    // this lease.
    ASSERT_NO_THROW(client1.doRenew());
    ASSERT_TRUE(client1.hasLeaseWithZeroLifetimeForAddress(IOAddress("2001:db8:2::28")));
    ASSERT_FALSE(client1.hasLeaseForAddress(IOAddress("2001:db8:1::28")));

    // The client should be allocated a lease from one of the dynamic pools.
    if (!client1.hasLeaseForAddressRange(IOAddress("2001:db8:2::1"), IOAddress("2001:db8:2::64")) &&
        !client1.hasLeaseForAddressRange(IOAddress("2001:db8:1::1"), IOAddress("2001:db8:1::64"))) {
        ADD_FAILURE() << "unexpected lease allocated for renewing client";
    }

    // Client #2 is now renewing its lease and should get its newly reserved address.
    ASSERT_NO_THROW(client2.doRenew());
    ASSERT_TRUE(client2.hasLeaseWithZeroLifetimeForAddress(IOAddress("2001:db8:1::28")));
    ASSERT_TRUE(client2.hasLeaseForAddress(IOAddress("2001:db8:2::28")));

    // Same for client #1.
    ASSERT_NO_THROW(client1.doRenew());
    ASSERT_TRUE(client1.hasLeaseForAddress(IOAddress("2001:db8:1::28")));
}

// Reserved address can't be assigned as long as access to a subnet is
// restricted by classification.
TEST_F(Dhcpv6SharedNetworkTest, reservationAccessRestrictedByClass) {
    // Create client #1. Explicitly set client's DUID to the one that has a
    // reservation in the firstsubnet within shared network.
    Dhcp6Client client;
    client.setInterface("eth1");
    client.setDUID("00:03:00:01:aa:bb:cc:dd:ee:ff");

    // Create server configuration with a shared network including two subnets. Access to
    // one of the subnets is restricted by client classification.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[6], *client.getServer()));

    // Assigned address should be allocated from the second subnet, because the
    // client doesn't belong to the "a-devices" class.
    ASSERT_NO_THROW(client.requestAddress(0xabca));
    ASSERT_NO_THROW(client.doSARR());
    ASSERT_TRUE(client.hasLeaseForAddress(IOAddress("2001:db8:2::16")));

    // Add option 1234 which would cause the client to be classified as "a-devices".
    OptionPtr option1234(new OptionUint16(Option::V6, 1234, 0x0001));
    client.addExtraOption(option1234);

    // The client should now be assigned the reserved address from the first subnet.
    ASSERT_NO_THROW(client.doRenew());
    ASSERT_TRUE(client.hasLeaseWithZeroLifetimeForAddress(IOAddress("2001:db8:2::16")));
    ASSERT_TRUE(client.hasLeaseForAddress(IOAddress("2001:db8:1::28")));
}

// Some options are specified on the shared subnet level, some on the
// subnets level.
TEST_F(Dhcpv6SharedNetworkTest, optionsDerivation) {
    // Client #1.
    Dhcp6Client client1;
    client1.setInterface("eth1");

    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[7], *client1.getServer()));

    // Client #1 belongs to shared network. By providing a hint "2001:db8:1::20 we force
    // the server to select first subnet within the shared network for this client.
    ASSERT_NO_THROW(client1.requestAddress(0xabca, IOAddress("2001:db8:1::20")));

    // Request all configured options.
    ASSERT_NO_THROW(client1.requestOption(D6O_NIS_SERVERS));
    ASSERT_NO_THROW(client1.requestOption(D6O_NISP_SERVERS));
    ASSERT_NO_THROW(client1.requestOption(D6O_NAME_SERVERS));
    ASSERT_NO_THROW(client1.requestOption(D6O_SNTP_SERVERS));

    // Perform 4-way exchange and make sure we have been assigned address from the
    // subnet we wanted.
    ASSERT_NO_THROW(client1.doSARR());
    ASSERT_TRUE(client1.hasLeaseForAddress(IOAddress("2001:db8:1::20")));

    // This option is specified on the global level.
    ASSERT_TRUE(client1.hasOptionWithAddress(D6O_NIS_SERVERS, "3000::20"));

    // Subnet specific value should override a value specified on the shared network level.
    ASSERT_TRUE(client1.hasOptionWithAddress(D6O_NISP_SERVERS, "3003::33"));

    // Shared network level value should be derived to the subnet.
    ASSERT_TRUE(client1.hasOptionWithAddress(D6O_NAME_SERVERS, "3001::21"));

    // This option is only specified in the subnet level.
    ASSERT_TRUE(client1.hasOptionWithAddress(D6O_SNTP_SERVERS, "4004::22"));

    // Client #2.
    Dhcp6Client client2(client1.getServer());
    client2.setInterface("eth1");

    // Request an address from the second subnet within the shared network.
    ASSERT_NO_THROW(client2.requestAddress(0xabca, IOAddress("2001:db8:2::20")));

    // Request all configured options.
    ASSERT_NO_THROW(client2.requestOption(D6O_NIS_SERVERS));
    ASSERT_NO_THROW(client2.requestOption(D6O_NISP_SERVERS));
    ASSERT_NO_THROW(client2.requestOption(D6O_NAME_SERVERS));
    ASSERT_NO_THROW(client2.requestOption(D6O_SNTP_SERVERS));

    // Perform 4-way exchange and make sure we have been assigned address from the
    // subnet we wanted.
    ASSERT_NO_THROW(client2.doSARR());
    ASSERT_TRUE(client2.hasLeaseForAddress(IOAddress("2001:db8:2::20")));

    // This option is specified on the global level.
    ASSERT_TRUE(client2.hasOptionWithAddress(D6O_NIS_SERVERS, "3000::20"));

    // Shared network level value should be derived to the subnet.
    ASSERT_TRUE(client2.hasOptionWithAddress(D6O_NAME_SERVERS, "3001::21"));
    ASSERT_TRUE(client2.hasOptionWithAddress(D6O_NISP_SERVERS, "3002::34"));

    // Client #3.
    Dhcp6Client client3(client1.getServer());
    client3.setInterface("eth0");

    // Request an address from the subnet outside of the shared network.
    ASSERT_NO_THROW(client3.requestAddress(0xabca, IOAddress("3000::1")));

    // Request all configured options.
    ASSERT_NO_THROW(client3.requestOption(D6O_NIS_SERVERS));
    ASSERT_NO_THROW(client3.requestOption(D6O_NISP_SERVERS));
    ASSERT_NO_THROW(client3.requestOption(D6O_NAME_SERVERS));
    ASSERT_NO_THROW(client3.requestOption(D6O_SNTP_SERVERS));

    // Perform 4-way exchange and make sure we have been assigned address from the
    // subnet we wanted.
    ASSERT_NO_THROW(client3.doSARR());
    ASSERT_TRUE(client3.hasLeaseForAddress(IOAddress("3000::1")));

    // This option is specified on the global level.
    ASSERT_TRUE(client3.hasOptionWithAddress(D6O_NIS_SERVERS, "3000::20"));

    // Subnet specific value should be assigned.
    ASSERT_TRUE(client3.hasOptionWithAddress(D6O_NISP_SERVERS, "4000::5"));
}

// Different shared network is selected for different local interface.
TEST_F(Dhcpv6SharedNetworkTest, sharedNetworkSelectionByInterface) {
    // Create client #1. The server receives requests from this client
    // via interface eth1 and should assign shared network "frog" for
    // this client.
    Dhcp6Client client1;
    client1.setInterface("eth1");
    client1.requestAddress(0xabca);

    // Create server configuration with two shared networks selected
    // by the local interface: eth1 and eth0.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[8], *client1.getServer()));

    // Client #1 should be assigned an address from one of the two subnets
    // belonging to the first shared network.
    ASSERT_NO_THROW(client1.doSARR());
    if (!client1.hasLeaseForAddress(IOAddress("2001:db8:1::20")) &&
        !client1.hasLeaseForAddress(IOAddress("2001:db8:2::20"))) {
        ADD_FAILURE() << "unexpected shared network selected for the client";
    }

    // Client #2.
    Dhcp6Client client2;
    client2.setInterface("eth0");
    client2.requestAddress(0xabca);

    // Client #2 should be assigned an address from one of the two subnets
    // belonging to the second shared network.
    ASSERT_NO_THROW(client2.doSARR());
    if (!client2.hasLeaseForAddress(IOAddress("2001:db8:3::20")) &&
        !client2.hasLeaseForAddress(IOAddress("2001:db8:4::20"))) {
        ADD_FAILURE() << "unexpected shared network selected for the client";
    }
}

// Different shared network is selected for different relay address.
TEST_F(Dhcpv6SharedNetworkTest, sharedNetworkSelectionByRelay) {
    // Create relayed client #1.
    Dhcp6Client client1;
    client1.useRelay(true, IOAddress("3000::1"));
    client1.requestAddress(0xabcd);

    // Create server configuration with two shared networks selected
    // by the relay address.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[9], *client1.getServer()));

    // Client #1 should be assigned an address from one of the two subnets
    // belonging to the first shared network.
    ASSERT_NO_THROW(client1.doSARR());
    if (!client1.hasLeaseForAddress(IOAddress("2001:db8:1::20")) &&
        !client1.hasLeaseForAddress(IOAddress("2001:db8:2::20"))) {
        ADD_FAILURE() << "unexpected shared network selected for the client";
    }

    // Create relayed client #2.
    Dhcp6Client client2;
    client2.useRelay(true, IOAddress("3000::2"));
    client2.requestAddress(0xabca);

    // Client #2 should be assigned an address from one of the two subnets
    // belonging to the second shared network.
    ASSERT_NO_THROW(client2.doSARR());
    if (!client2.hasLeaseForAddress(IOAddress("2001:db8:3::20")) &&
        !client2.hasLeaseForAddress(IOAddress("2001:db8:4::20"))) {
        ADD_FAILURE() << "unexpected shared network selected for the client";
    }
}

// Host reservations include hostname and client class.
TEST_F(Dhcpv6SharedNetworkTest, variousFieldsInReservation) {
    // Create client #1.
    Dhcp6Client client;
    client.setInterface("eth1");
    client.setDUID("00:03:00:01:11:22:33:44:55:66");
    ASSERT_NO_THROW(client.requestAddress(0xabcd));
    ASSERT_NO_THROW(client.requestOption(D6O_NAME_SERVERS));

    ASSERT_NO_THROW(client.useFQDN(Option6ClientFqdn::FLAG_S,
                                   "bird.example.org",
                                   Option6ClientFqdn::FULL));

    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[10], *client.getServer()));

    // Perform 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());

    // The client should get an FQDN from the reservation, rather than
    // the FQDN it has sent to the server. If there is a logic error,
    // the server would use the first subnet from the shared network to
    // assign the FQDN. This subnet has no reservation so it would
    // return the same FQDN that the client has sent. We expect
    // that the FQDN being sent is the one that is included in the
    // reservations.
    ASSERT_TRUE(client.getContext().response_);
    OptionPtr opt_fqdn = client.getContext().response_->getOption(D6O_CLIENT_FQDN);
    ASSERT_TRUE(opt_fqdn);
    Option6ClientFqdnPtr fqdn = boost::dynamic_pointer_cast<Option6ClientFqdn>(opt_fqdn);
    ASSERT_TRUE(fqdn);
    ASSERT_EQ("test.example.org.", fqdn->getDomainName());

    // Make sure that the correct hostname has been stored in the database.
    Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA,
                                                            IOAddress("2001:db8:2::20"));
    ASSERT_TRUE(lease);
    EXPECT_EQ("test.example.org.", lease->hostname_);

    // The DNS servers option should be derived from the client class based on the
    // static class reservations.
    ASSERT_TRUE(client.hasOptionWithAddress(D6O_NAME_SERVERS, "2001:db8:1::50"));
}

// Shared network is selected based on the client class specified.
TEST_F(Dhcpv6SharedNetworkTest, sharedNetworkSelectedByClass) {
    // Create client #1.
    Dhcp6Client client1;
    client1.setInterface("eth1");
    client1.requestAddress(0xabcd);

    // Add option 1234 which would cause the client1 to be classified as "b-devices".
    OptionPtr option1234(new OptionUint16(Option::V6, 1234, 0x0002));
    client1.addExtraOption(option1234);

    // Configure the server with two shared networks which can be accessed
    // by clients belonging to "a-devices" and "b-devices" classes
    // respectively.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[11], *client1.getServer()));

    // The client 1 should be offerred an address from the second subnet.
    ASSERT_NO_THROW(client1.doSolicit(true));
    ASSERT_TRUE(client1.hasLeaseForAddress(IOAddress("2001:db8:2::20")));

    // Create another client which will belong to a different class.
    Dhcp6Client client2;
    client2.setInterface("eth1");
    client2.requestAddress(0xabcd);

    /// Add option 1234 which will cause the client 2 to be classified as "a-devices".
    option1234.reset(new OptionUint16(Option::V6, 1234, 0x0001));
    client2.addExtraOption(option1234);

    // Client 2 should be offerred an address from the first subnet.
    ASSERT_NO_THROW(client2.doSolicit(true));
    ASSERT_TRUE(client2.hasLeaseForAddress(IOAddress("2001:db8:1::20")));
}

// Client requests two addresses and two prefixes and obtains them from two
// different subnets.
TEST_F(Dhcpv6SharedNetworkTest, assignmentsFromDifferentSubnets) {
    // Create client.
    Dhcp6Client client;
    client.setInterface("eth1");
    client.requestAddress(0xabcd);
    client.requestAddress(0x1234);
    client.requestPrefix(0x1111);
    client.requestPrefix(0x2222);

    // Configure the server with a shared network including two subnets. Each
    // subnet has an address and prefix pool with a single available address
    // and prefix respectively.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[0], *client.getServer()));

    // 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());
    // The two addresses should come from different subnets.
    ASSERT_TRUE(client.hasLeaseForAddress(IOAddress("2001:db8:1::20")));
    ASSERT_TRUE(client.hasLeaseForAddress(IOAddress("2001:db8:2::20")));
    // Same for prefixes.
    ASSERT_TRUE(client.hasLeaseForPrefixPool(IOAddress("4000::"), 96, 96));
    ASSERT_TRUE(client.hasLeaseForPrefixPool(IOAddress("5000::"), 96, 96));

    // Try to renew.
    ASSERT_NO_THROW(client.doRenew());
    ASSERT_TRUE(client.hasLeaseForAddress(IOAddress("2001:db8:1::20")));
    ASSERT_TRUE(client.hasLeaseForAddress(IOAddress("2001:db8:2::20")));
    ASSERT_TRUE(client.hasLeaseForPrefixPool(IOAddress("4000::"), 96, 96));
    ASSERT_TRUE(client.hasLeaseForPrefixPool(IOAddress("5000::"), 96, 96));
}

// Client requests 2 addresses and 2 prefixes. There is one address and one prefix
// reserved for the client.
TEST_F(Dhcpv6SharedNetworkTest, reservedAddressAndPrefix) {
    // Create client.
    Dhcp6Client client;
    client.setInterface("eth1");
    client.setDUID("00:03:00:01:11:22:33:44:55:66");

    // Client will request two addresses and two prefixes.
    client.requestAddress(0xabcd);
    client.requestAddress(0x1234);
    client.requestPrefix(0x1111);
    client.requestPrefix(0x2222);

    // The server configuration contains a shared network with two subnets. Each
    // subnet has an address and prefix pool. One of the subnets includes a reservation
    // for an address and prefix.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[4], *client.getServer()));

    // 4-way exchange.
    ASSERT_NO_THROW(client.doSARR());
    ASSERT_EQ(4, client.getLeaseNum());
    // The client should have got one reserved address and one reserved prefix.
    ASSERT_TRUE(client.hasLeaseForAddress(IOAddress("2001:db8:2::28")));
    ASSERT_TRUE(client.hasLeaseForPrefix(IOAddress("1234::"), 64, IAID(0x1111)));

    // The client should have got dynamically allocated address too and it must be
    // different than the reserved address.
    std::vector<Lease6> leases_1234 = client.getLeasesByIAID(0x1234);
    ASSERT_EQ(1, leases_1234.size());
    ASSERT_NE("2001:db8:2::28", leases_1234[0].addr_.toText());

    // Same for prefix.
    std::vector<Lease6> leases_2222 = client.getLeasesByIAID(0x2222);
    ASSERT_EQ(1, leases_2222.size());
    ASSERT_NE("1234::", leases_2222[0].addr_.toText());

    // Try to renew and check this again.
    ASSERT_NO_THROW(client.doRenew());
    ASSERT_EQ(4, client.getLeaseNum());
    ASSERT_TRUE(client.hasLeaseForAddress(IOAddress("2001:db8:2::28")));
    ASSERT_TRUE(client.hasLeaseForPrefix(IOAddress("1234::"), 64, IAID(0x1111)));

    leases_1234 = client.getLeasesByIAID(0x1234);
    ASSERT_EQ(1, leases_1234.size());
    ASSERT_NE("2001:db8:2::28", leases_1234[0].addr_.toText());

    leases_2222 = client.getLeasesByIAID(0x2222);
    ASSERT_EQ(1, leases_2222.size());
    ASSERT_NE("1234::", leases_2222[0].addr_.toText());
}

/// @todo: Add a test for relay information specified for shared network.
/// @todo: Add a test for relay information specified on each subnet
///        in a shared network.
/// @todo: Add a test for interface-id specified for shared network.
/// @todo: Add a test for interface-id on each subnet in a shared network.
/// Also, see http://kea.isc.org/ticket/5364 for more ideas.

} // end of anonymous namespace
