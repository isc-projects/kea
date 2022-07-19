// Copyright (C) 2017-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <dhcp/option.h>
#include <dhcp/option_int.h>
#include <dhcp/option6_client_fqdn.h>
#include <dhcp/option6_addrlst.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcpsrv/cfg_subnets6.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcp6/json_config_parser.h>
#include <dhcp6/tests/dhcp6_client.h>
#include <dhcp6/tests/dhcp6_test_utils.h>
#include <cc/command_interpreter.h>
#include <stats/stats_mgr.h>
#include <boost/pointer_cast.hpp>
#include <functional>
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
// - one shared network with two subnets, each with address and prefix pools
// - one plain subnet
    "{"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface\": \"eth1\","
    "            \"comment\": \"example\","
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
// - one shared network with relay-ip specified and one subnet with address pool
// - one plain subnet with relay-ip specified and one address pool
    "{"
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
// - two classes specified
// - one shared network with two subnets (the first has class restrictions)
    "{"
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
// - two classes defined
// - one shared network with two subnets, each with a different class restriction
    "{"
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
// - one shared network with two subnets. Each subnet has:
//   - address and prefix pool
//   - reservation
    "{"
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
    "                            \"delegated-len\": 112"
    "                        }"
    "                    ],"
    "                    \"reservations\": ["
    "                        {"
    "                            \"duid\": \"00:03:00:01:11:22:33:44:55:66\","
    "                            \"ip-addresses\": [ \"2001:db8:2::28\" ],"
    "                            \"prefixes\": [ \"5000::8:0000/112\" ]"
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #5 (similar to #4, but without prefix pool and using different
// DUID for reservations)
    "{"
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
// - one class
// - one shared network with two subnets:
//   - first subnet has address pool, class restriction and a reservation
//   - second subnet has just an address pool
    "{"
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
// - option defined on global level
// - one shared network with two options and two subnets
// - the first subnet has its own options defined as well
// - plain subnet with its own options
    "{"
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
// - two shared networks
//   - first network with two subnets, each with its own address pool
//   - second network with two subnets, each with its own address pool
    "{"
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

// Configuration #9 (similar to #8, but with relay-ip addresses specified)
// - two shared networks, each with relay IP addresses specified
    "{"
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
// - one class with an option (and not test expression)
// - one shared network with two subnets
//   - first subnet with one address pool
//   - second with a pool and reservation that assigns client to a class
    "{"
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
// - two classes defined
// - two shared networks, each with one subnet and class restriction
    "{"
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
    "}",

// Configuration #12.
// - one client class
// - one shared network with two subnets, the second subnet has class restriction
    "{"
    "    \"client-classes\": ["
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
    "                    \"client-class\": \"b-devices\""
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #13.
// - one shared network, with two subnets, each with the same relay-ip addresses
// - one plain subnet, with its own (different) relay-ip address
    "{"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"subnet6\": ["
    "                {"
    "                    \"subnet\": \"2001:db8:1::/64\","
    "                    \"id\": 10,"
    "                    \"relay\": {"
    "                        \"ip-address\": \"3001::1\""
    "                    },"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:1::20 - 2001:db8:1::20\""
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"2001:db8:2::/64\","
    "                    \"id\": 100,"
    "                    \"relay\": {"
    "                        \"ip-address\": \"3001::1\""
    "                    },"
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
    "        {"
    "            \"subnet\": \"2001:db8:3::/64\","
    "            \"id\": 1000,"
    "            \"relay\": {"
    "                \"ip-address\": \"3001::2\""
    "            },"
    "            \"pools\": ["
    "                {"
    "                    \"pool\": \"2001:db8:3::20 - 2001:db8:3::20\""
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #14.
// - one share network with interface-id specified and one subnet
// - one plain subnet, with its own interface-id
    "{"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface-id\": \"vlan10\","
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
    "            \"interface-id\": \"vlan1000\","
    "            \"pools\": ["
    "                {"
    "                    \"pool\": \"2001:db8:2::20 - 2001:db8:2::20\""
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #15.
// - one shared network, with two subnets, each with the same interface-id
// - one plain subnet, with its own interface-id
    "{"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"subnet6\": ["
    "                {"
    "                    \"subnet\": \"2001:db8:1::/64\","
    "                    \"id\": 10,"
    "                    \"interface-id\": \"vlan10\","
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:1::20 - 2001:db8:1::20\""
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"2001:db8:2::/64\","
    "                    \"id\": 11,"
    "                    \"interface-id\": \"vlan10\","
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:2::10 - 2001:db8:2::10\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ],"
    "    \"subnet6\": ["
    "        {"
    "            \"subnet\": \"2001:db8:2::1/64\","
    "            \"id\": 1000,"
    "            \"interface-id\": \"vlan1000\","
    "            \"pools\": ["
    "                {"
    "                    \"pool\": \"2001:db8:2::20 - 2001:db8:2::20\""
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #16.
// - one shared network with three subnets, each with different option value
    "{"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface\": \"eth1\","
    "            \"subnet6\": ["
    "                {"
    "                    \"subnet\": \"2001:db8:1::/64\","
    "                    \"id\": 10,"
    "                    \"option-data\": ["
    "                        {"
    "                            \"name\": \"dns-servers\","
    "                            \"data\": \"4004::22\""
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
    "                    \"option-data\": ["
    "                        {"
    "                            \"name\": \"dns-servers\","
    "                            \"data\": \"5555::33\""
    "                        }"
    "                    ],"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:2::20 - 2001:db8:2::20\""
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"2001:db8:3::/64\","
    "                    \"id\": 1000,"
    "                    \"option-data\": ["
    "                        {"
    "                            \"name\": \"dns-servers\","
    "                            \"data\": \"1234::23\""
    "                        }"
    "                    ],"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:3::20 - 2001:db8:3::20\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #17.
// - one shared network with two subnets, both have rapid-commit enabled
    "{"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface\": \"eth1\","
    "            \"subnet6\": ["
    "                {"
    "                    \"subnet\": \"2001:db8:1::/64\","
    "                    \"id\": 10,"
    "                    \"rapid-commit\": true,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"2001:db8:1::20 - 2001:db8:1::20\""
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"2001:db8:2::/64\","
    "                    \"id\": 100,"
    "                    \"rapid-commit\": true,"
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


// Configuration #18.
// - one shared network with rapid-commit enabled
// - two subnets (which should derive the rapid-commit setting)
    "{"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface\": \"eth1\","
    "            \"rapid-commit\": true,"
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
    "        }"
    "    ]"
    "}",

// Configuration #19.
// - one shared network with one subnet and two pools (the first has
//   class restrictions)
    "{"
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
    "                            \"pool\": \"2001:db8:1::20 - 2001:db8:1::20\","
    "                            \"client-class\": \"a-devices\""
    "                        },"
    "                        {"
    "                            \"pool\": \"2001:db8:1::50 - 2001:db8:1::50\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #20.
// - one shared network with one subnet and two pools (each with class
//   restriction)
    "{"
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
    "                            \"pool\": \"2001:db8:1::20 - 2001:db8:1::20\","
    "                            \"client-class\": \"a-devices\""
    "                        },"
    "                        {"
    "                            \"pool\": \"2001:db8:1::50 - 2001:db8:1::50\","
    "                            \"client-class\": \"b-devices\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #21.
// - one plain subnet with two pools (the first has class restrictions)
    "{"
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
    "    \"subnet6\": ["
    "        {"
    "            \"subnet\": \"2001:db8:1::/64\","
    "            \"id\": 10,"
    "            \"interface\": \"eth1\","
    "            \"pools\": ["
    "                {"
    "                    \"pool\": \"2001:db8:1::20 - 2001:db8:1::20\","
    "                    \"client-class\": \"a-devices\""
    "                },"
    "                {"
    "                    \"pool\": \"2001:db8:1::50 - 2001:db8:1::50\""
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #22.
// - one plain subnet with two pools (each with class restriction)
    "{"
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
    "                            \"pool\": \"2001:db8:1::20 - 2001:db8:1::20\","
    "                            \"client-class\": \"a-devices\""
    "                        },"
    "                        {"
    "                            \"pool\": \"2001:db8:1::50 - 2001:db8:1::50\","
    "                            \"client-class\": \"b-devices\""
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

    /// @brief Indicates how test functions should check presence of a lease on
    /// the server.
    enum class LeaseOnServer{
        MUST_EXIST,
        MUST_NOT_EXIST,
    };

    /// @brief Constructor.
    Dhcpv6SharedNetworkTest()
        : Dhcpv6SrvTest(),
          iface_mgr_test_config_(true) {
        IfaceMgr::instance().openSockets6();
        StatsMgr::instance().removeAll();
    }

    /// @brief Verifies lease statistics against values held by StatsMgr.
    ///
    /// This method retrieves lease statistics from the database and then compares it
    /// against values held by the StatsMgr. The compared statistics are number of
    /// assigned addresses and prefixes for a subnet.
    void verifyAssignedStats() {
        LeaseStatsQueryPtr query = LeaseMgrFactory::instance().startLeaseStatsQuery6();
        LeaseStatsRow row;
        while (query->getNextRow(row)) {
            // Only check valid leases.
            if (row.lease_state_ == Lease::STATE_DEFAULT) {
                std::string stat_name;
                // Addresses
                if (row.lease_type_ == Lease::TYPE_NA) {
                    stat_name = StatsMgr::generateName("subnet", row.subnet_id_,
                                                       "assigned-nas");
                // Prefixes.
                } else if (row.lease_type_ == Lease::TYPE_PD) {
                    stat_name = StatsMgr::generateName("subnet", row.subnet_id_,
                                                       "assigned-pds");
                }

                // Number of leases held in the database should match the information
                // held in the Stats Manager.
                if (!stat_name.empty()) {
                    ASSERT_EQ(row.state_count_, getStatsAssignedLeases(stat_name))
                        << "test failed for statistic " << stat_name;
                }
            }
        }
    }

    /// @brief Retrieves statistics for a subnet.
    ///
    /// @param stat_name Name of the statistics to be retrieved, e.g. subnet[1234].assigned-nas.
    /// @return Number of assigned leases for a subnet.
    int64_t getStatsAssignedLeases(const std::string& stat_name) const {
        // Top element is a map with a subnet[id].assigned-addresses parameter.
        ConstElementPtr top_element = StatsMgr::instance().get(stat_name);
        if (top_element && (top_element->getType() == Element::map)) {
            // It contains two lists (nested).
            ConstElementPtr first_list = top_element->get(stat_name);
            if (first_list && (first_list->getType() == Element::list) &&
                (first_list->size() > 0)) {
                // Get the nested list which should have two elements, of which first
                // is the statistics value we're looking for.
                ConstElementPtr second_list = first_list->get(0);
                if (second_list && (second_list->getType() == Element::list)) {
                    ConstElementPtr addresses_element = second_list->get(0);
                    if (addresses_element && (addresses_element->getType() == Element::integer)) {
                        return (addresses_element->intValue());
                    }
                }
            }
        }

        // Statistics invalid or not found.
        return (0);
    }

    /// @brief Launches specific operation and verifies lease statistics before and
    /// after this operation.
    ///
    /// @param operation Operation to be launched.
    void testAssigned(const std::function<void()>& operation) {
        ASSERT_NO_FATAL_FAILURE(verifyAssignedStats());
        operation();
        ASSERT_NO_FATAL_FAILURE(verifyAssignedStats());
    }

    /// @brief Returns subnet having specified address or prefix in range.
    ///
    /// @param type Resource type: NA or PD.
    /// @param resource Address or prefix for which subnet is being searched.
    /// @return Pointer to the subnet having an resource in range or null pointer
    /// if no subnet found.
    Subnet6Ptr getConfiguredSubnet(const Lease::Type& type, const IOAddress& resource) const {
        CfgSubnets6Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets6();
        const Subnet6Collection* subnets = cfg->getAll();
        for (auto subnet_it = subnets->cbegin(); subnet_it != subnets->cend(); ++subnet_it) {
            if ((*subnet_it)->inPool(type, resource)) {
                return (*subnet_it);
            }
        }

        return (Subnet6Ptr());

    }

    /// @brief Check if client has a lease for the specified address.
    ///
    /// Apart from checking whether the client has got the lease it also
    /// checks whether this lease is stored in the lease database and that
    /// it holds valid subnet identifier.
    ///
    /// @param client Reference to the client.
    /// @param address Leased address.
    /// @param lease_on_server Specify whether the lease should be also present or
    /// absent in the lease database.
    ///
    /// @return true if the lease for the client has been found both in the
    /// database and in the server's response.
    bool hasLeaseForAddress(Dhcp6Client& client, const IOAddress& address,
                            const LeaseOnServer& lease_on_server = LeaseOnServer::MUST_EXIST) {
        Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, address);
        // Sanity check the lease.
        if (lease) {
            Subnet6Ptr subnet = getConfiguredSubnet(Lease::TYPE_NA, address);
            if (!subnet) {
                ADD_FAILURE() << "unable to find configured subnet for the"
                    " address " << address;
                return (false);
            }
            // Make sure that the subnet id is not messed up in the lease.
            if (subnet->getID() != lease->subnet_id_) {
                ADD_FAILURE() << "invalid subnet identifier found in the lease for"
                    " address " << address << ", expected " << subnet->getID()
                              << ", got " << lease->subnet_id_;
                return (false);
            }
        }
        return ((((lease_on_server == LeaseOnServer::MUST_EXIST) && lease) ||
                ((lease_on_server == LeaseOnServer::MUST_NOT_EXIST) && !lease)) &&
                client.hasLeaseForAddress(address));
    }

    /// @brief Check if client has a lease for the specified prefix.
    ///
    /// Apart from checking whether the client has got the lease it also
    /// checks whether this lease is stored in the lease database and that
    /// it holds valid subnet identifier.
    ///
    /// @param client Reference to the client.
    /// @param prefix Leased prefix.
    /// @param prefix_len Leased prefix length.
    /// @param lease_on_server Specify whether the lease should be also present or
    /// absent in the lease database.
    ///
    /// @return true if the lease for the client has been found both in the
    /// database and in the server's response.
    bool hasLeaseForPrefix(Dhcp6Client& client, const IOAddress& prefix,
                           const uint8_t prefix_len, const IAID& iaid,
                           const LeaseOnServer& lease_on_server = LeaseOnServer::MUST_EXIST) {
        Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_PD, prefix);

        // Sanity check the lease.
        if (lease) {
            Subnet6Ptr subnet = getConfiguredSubnet(Lease::TYPE_PD, prefix);
            if (!subnet) {
                ADD_FAILURE() << "unable to find configured subnet for the"
                    " prefix " << prefix;
                return (false);
            }
            // Make sure that the subnet id is not messed up in the lease.
            if (subnet->getID() != lease->subnet_id_) {
                ADD_FAILURE() << "invalid subnet identifier found in the lease for"
                    " prefix " << prefix;
                return (false);
            }
        }

        return ((((lease_on_server == LeaseOnServer::MUST_EXIST) && lease &&
                  (lease->prefixlen_ = prefix_len) && (lease->iaid_ == iaid)) ||
                ((lease_on_server == LeaseOnServer::MUST_NOT_EXIST) && !lease)) &&
                client.hasLeaseForPrefix(prefix, prefix_len, iaid));
    }

    /// @brief Check if client has a lease belonging to address range.
    ///
    /// Apart from checking whether the client has got the lease it also
    /// checks whether this lease is stored in the lease database.
    ///
    /// @param client Reference to the client.
    /// @param first Lower bound of the address range.
    /// @param last Upper bound of the address range.
    /// @param lease_on_server Specify whether the lease should be also present or
    /// absent in the lease database.
    bool hasLeaseForAddressRange(Dhcp6Client& client, const IOAddress& first, const IOAddress& last,
                                 const LeaseOnServer& lease_on_server = LeaseOnServer::MUST_EXIST) {
        std::vector<Lease6> leases = client.getLeasesByAddressRange(first, last);
        for (auto lease_it = leases.cbegin(); lease_it != leases.cend(); ++lease_it) {
            // Take into account only valid leases.
            if (lease_it->valid_lft_ == 0) {
                continue;
            }

            Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_NA, lease_it->addr_);
            if ((lease && (lease_on_server == LeaseOnServer::MUST_NOT_EXIST)) ||
                (!lease && (lease_on_server == LeaseOnServer::MUST_EXIST))) {
                return (false);
            }
        }

        return (!leases.empty());
    }

    /// @brief Check if client has a lease belonging to a prefix pool.
    ///
    /// Apart from checking whether the client has got the lease it also
    /// checks whether this lease is stored in the lease database.
    ///
    /// @param client Reference to the client.
    /// @param prefix Pool prefix.
    /// @param prefix_len Prefix length.
    /// @param delegated_len Delegated prefix length.
    /// @param lease_on_server Specify whether the lease should be also present or
    /// absent in the lease database.
    ///
    /// @return true if client has a lease belonging to specified pool,
    /// false otherwise.
    bool hasLeaseForPrefixPool(Dhcp6Client& client, const asiolink::IOAddress& prefix,
                               const uint8_t prefix_len, const uint8_t delegated_len,
                               const LeaseOnServer& lease_on_server = LeaseOnServer::MUST_EXIST) {
        std::vector<Lease6> leases = client.getLeasesByPrefixPool(prefix, prefix_len, delegated_len);

        for (auto lease_it = leases.cbegin(); lease_it != leases.cend(); ++lease_it) {
            // Take into account only valid leases.
            if (lease_it->valid_lft_ == 0) {
                continue;
            }

            Lease6Ptr lease = LeaseMgrFactory::instance().getLease6(Lease::TYPE_PD, lease_it->addr_);
            if ((lease && (lease->prefixlen_ == lease->prefixlen_) &&
                 (lease_on_server == LeaseOnServer::MUST_NOT_EXIST)) ||
                (!lease && (lease_on_server == LeaseOnServer::MUST_EXIST))) {
                return (false);
            }
        }

        return (!leases.empty());

    }

    /// @brief Tests that for a given configuration the rapid-commit works (or not)
    ///
    /// The provided configuration is expected to be able to handle two clients.
    /// The second parameter governs whether rapid-commit is expected to be enabled
    /// or disabled. Third and fourth parameters are text representations of expected
    /// leases to be assigned (if rapid-commit is enabled)
    ///
    /// @param config - text version of the configuration to be tested
    /// @param enabled - true = rapid-commit is expected to work
    /// @param exp_addr1 - an address the first client is expected to get (if
    ///                    rapid-commit is enabled).
    /// @param exp_addr2 - an address the second client is expected to get (if
    ///                    rapid-commit is enabled).
    void testRapidCommit(const std::string& config, bool enabled,
                         const std::string& exp_addr1,
                         const std::string& exp_addr2) {

        // Create client #1. This clients wants to use rapid-commit.
        Dhcp6Client client1;
        client1.setInterface("eth1");
        client1.useRapidCommit(true);

        Dhcp6Client client2;
        client2.setInterface("eth1");
        client2.useRapidCommit(true);

        // Configure the server with a shared network.
        ASSERT_NO_FATAL_FAILURE(configure(config, *client1.getServer()));

        // Ok, client should have one
        EXPECT_EQ(0, client1.getLeaseNum());

        // Client #1 should be assigned an address from shared network. The first
        // subnet has rapid-commit enabled, so the address should be assigned.
        // We provide a hint for this allocation to make sure that the address
        // from the first subnet is allocated. In theory, an address from the
        // second subnet could be allocated as well if the hint was not provided.
        IOAddress requested_address = exp_addr1.empty() ? IOAddress::IPV6_ZERO_ADDRESS() :
            IOAddress(exp_addr1);
        ASSERT_NO_THROW(client1.requestAddress(0xabca0, requested_address));
        testAssigned([&client1] {
            ASSERT_NO_THROW(client1.doSolicit());
        });

        // Make sure something was sent back.
        ASSERT_TRUE(client1.getContext().response_);

        if (enabled) {
            // rapid-commit enabled.

            // Make sure that REPLY was sent back.
            EXPECT_EQ(DHCPV6_REPLY, client1.getContext().response_->getType());

            // Just make sure the client didn't get an address.
            EXPECT_TRUE(hasLeaseForAddress(client1, IOAddress(exp_addr1),
                                           LeaseOnServer::MUST_EXIST));
        } else {
            // rapid-commit disabled.

            // Make sure that ADVERTISE was sent back.
            EXPECT_EQ(DHCPV6_ADVERTISE, client1.getContext().response_->getType());

            // And that it doesn't have any leases.
            EXPECT_EQ(0, client1.getLeaseNum());
        }

        // Create client #2. This client behaves the same as the first one, but the
        // first subnet is already full (it's a really small subnet) and the second
        // subnet does not allow rapid-commit.
        ASSERT_NO_THROW(client2.requestAddress(0xabca0));
        testAssigned([&client2] {
            ASSERT_NO_THROW(client2.doSolicit());
        });

        // Make sure something was sent back.
        ASSERT_TRUE(client2.getContext().response_);

        if (enabled) {
            // rapid-commit enabled.

            // Make sure that REPLY was sent back.
            EXPECT_EQ(DHCPV6_REPLY, client2.getContext().response_->getType());

            // Just make sure the client didn't get an address.
            EXPECT_TRUE(hasLeaseForAddress(client2, IOAddress(exp_addr2),
                                           LeaseOnServer::MUST_EXIST));
        } else {
            // rapid-commit disabled.

            // Make sure that ADVERTISE was sent back.
            EXPECT_EQ(DHCPV6_ADVERTISE, client1.getContext().response_->getType());

            // And that it doesn't have any leases.
            EXPECT_EQ(0, client1.getLeaseNum());
        }
    }

    /// @brief Check precedence.
    ///
    /// @param config the configuration.
    /// @param ns_address expected name server address.
    void testPrecedence(const std::string& config, const std::string& ns_address) {
        // Create client and set DUID to the one that has a reservation.
        Dhcp6Client client;
        client.setInterface("eth1");
        client.setDUID("00:03:00:01:aa:bb:cc:dd:ee:ff");
        client.requestAddress(0xabca, IOAddress("2001:db8:1::28"));
        // Request dns-servers.
        client.requestOption(D6O_NAME_SERVERS);

        // Create server configuration.
        configure(config, *client.getServer());

        // Perform SARR.
        ASSERT_NO_THROW(client.doSARR());

        // Check response.
        EXPECT_EQ(1, client.getLeaseNum());
        Pkt6Ptr resp = client.getContext().response_;
        ASSERT_TRUE(resp);

        // Check dns-servers option.
        OptionPtr opt = resp->getOption(D6O_NAME_SERVERS);
        ASSERT_TRUE(opt);
        Option6AddrLstPtr servers =
            boost::dynamic_pointer_cast<Option6AddrLst>(opt);
        ASSERT_TRUE(servers);
        auto addrs = servers->getAddresses();
        ASSERT_EQ(1, addrs.size());
        EXPECT_EQ(ns_address, addrs[0].toText());
    }

    /// @brief Destructor.
    virtual ~Dhcpv6SharedNetworkTest() {
        StatsMgr::instance().removeAll();
    }

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;
};

// Check user-context parsing
TEST_F(Dhcpv6SharedNetworkTest, parse) {
    // Create client
    Dhcp6Client client1;

    // Don't use configure from utils
    Parser6Context ctx;
    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP6(NETWORKS_CONFIG[0], true));
    ConstElementPtr status;
    disableIfacesReDetect(json);
    EXPECT_NO_THROW(status = configureDhcp6Server(*client1.getServer(), json));
    ASSERT_TRUE(status);
    int rcode;
    ConstElementPtr comment = config::parseAnswer(rcode, status);
    ASSERT_EQ(0, rcode);
    CfgMgr::instance().commit();

    CfgSharedNetworks6Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSharedNetworks6();
    SharedNetwork6Ptr network = cfg->getByName("frog");
    ConstElementPtr context = network->getContext();
    ASSERT_TRUE(context);
    ASSERT_EQ(1, context->size());
    ASSERT_TRUE(context->get("comment"));
    EXPECT_EQ("\"example\"", context->get("comment")->str());
}

// Running out of addresses within a subnet in a shared network.
TEST_F(Dhcpv6SharedNetworkTest, addressPoolInSharedNetworkShortage) {
    // Create client #1.
    Dhcp6Client client1;
    client1.setInterface("eth1");

    // Configure the server with one shared network including two subnets and
    // one subnet outside of the shared network.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[0], *client1.getServer()));

    // Client #1 requests an address in first subnet within a shared network.
    ASSERT_NO_THROW(client1.requestAddress(0xabca0, IOAddress("2001:db8:1::20")));
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client1, IOAddress("2001:db8:1::20")));

    // Client #2 The second client will request a lease and should be assigned
    // an address from the second subnet.
    Dhcp6Client client2(client1.getServer());
    client2.setInterface("eth1");
    ASSERT_NO_THROW(client2.requestAddress(0xabca0));
    testAssigned([&client2] {
        ASSERT_NO_THROW(client2.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client2, IOAddress("2001:db8:2::20")));

    // Client #3. It sends Solicit which should result in NoAddrsAvail status
    // code because all addresses available for this link have been assigned.
    Dhcp6Client client3(client1.getServer());
    client3.setInterface("eth1");
    ASSERT_NO_THROW(client3.requestAddress(0xabca0));
    testAssigned([&client3] {
        ASSERT_NO_THROW(client3.doSolicit(true));
    });
    EXPECT_EQ(0, client3.getLeaseNum());

    // Client #3 should be assigned an address if subnet 3 is selected for it.
    client3.setInterface("eth0");
    testAssigned([&client3] {
        ASSERT_NO_THROW(client3.doSolicit(true));
    });
    EXPECT_EQ(1, client3.getLeaseNum());

    // Client #1 should be able to renew its lease.
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doRenew());
    });
    EXPECT_EQ(1, client1.getLeaseNum());
    EXPECT_TRUE(hasLeaseForAddress(client1, IOAddress("2001:db8:1::20")));

    // Client #2 should be able to renew its lease too.
    testAssigned([&client2] {
        ASSERT_NO_THROW(client2.doRenew());
    });
    EXPECT_EQ(1, client2.getLeaseNum());
    EXPECT_TRUE(hasLeaseForAddress(client2, IOAddress("2001:db8:2::20")));
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
    ASSERT_NO_THROW(client1.requestAddress(0xabca0));
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client1, IOAddress("2001:db8:1::20")));

    // Create client #2. This is a relayed client which is using relay
    // address matching subnet outside of the shared network.
    Dhcp6Client client2(client1.getServer());
    client2.useRelay(true, IOAddress("3001::2"));
    ASSERT_NO_THROW(client2.requestAddress(0xabca0));
    testAssigned([&client2] {
        ASSERT_NO_THROW(client2.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client2, IOAddress("2001:db8:2::20")));
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
    testAssigned([&client] {
        ASSERT_NO_THROW(client.doSolicit(true));
    });
    ASSERT_TRUE(hasLeaseForAddress(client, IOAddress("2001:db8:1::20"),
                                   LeaseOnServer::MUST_NOT_EXIST));

    // Similarly, we should be offered an address from another subnet within
    // the same shared network when we ask for it.
    client.clearRequestedIAs();
    ASSERT_NO_THROW(client.requestAddress(0xabca, IOAddress("2001:db8:2::20")));
    testAssigned([&client] {
        ASSERT_NO_THROW(client.doSolicit(true));
    });
    ASSERT_TRUE(hasLeaseForAddress(client, IOAddress("2001:db8:2::20"),
                                   LeaseOnServer::MUST_NOT_EXIST));

    // Asking for an address that is not in address pool should result in getting
    // an address from one of the subnets, but generally hard to tell from which one.
    client.clearRequestedIAs();
    ASSERT_NO_THROW(client.requestAddress(0xabca, IOAddress("3002::123")));
    testAssigned([&client] {
        ASSERT_NO_THROW(client.doSolicit(true));
    });
    std::vector<Lease6> leases = client.getLeasesByType(Lease::TYPE_NA);
    ASSERT_EQ(1, leases.size());
    if (!hasLeaseForAddress(client, IOAddress("2001:db8:1::20"),
                            LeaseOnServer::MUST_NOT_EXIST) &&
        !hasLeaseForAddress(client, IOAddress("2001:db8:2::20"),
                            LeaseOnServer::MUST_NOT_EXIST)) {
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
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client1, IOAddress("2001:db8:2::20")));

    // Release the lease that the client has got, because we'll need this address
    // further in the test.
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doRelease());
    });

    // Add option 1234 which would cause the client to be classified as "a-devices".
    OptionPtr option1234(new OptionUint16(Option::V6, 1234, 0x0001));
    client1.addExtraOption(option1234);

    // This time, the allocation of the address provided as hint should be successful.
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client1, IOAddress("2001:db8:1::20")));

    // Client 2 should be assigned an address from the unrestricted subnet.
    Dhcp6Client client2(client1.getServer());
    client2.setInterface("eth1");
    ASSERT_NO_THROW(client2.requestAddress(0xabca0));
    testAssigned([&client2] {
        ASSERT_NO_THROW(client2.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client2, IOAddress("2001:db8:2::20")));

    // Now, let's reconfigure the server to also apply restrictions on the
    // subnet to which client2 now belongs.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[3], *client1.getServer()));

    testAssigned([&client2] {
        ASSERT_NO_THROW(client2.doRenew());
    });
    EXPECT_EQ(0, client2.getLeaseNum());

    // If we add option 1234 with a value matching this class, the lease should
    // get renewed.
    OptionPtr option1234_bis(new OptionUint16(Option::V6, 1234, 0x0002));
    client2.addExtraOption(option1234_bis);
    testAssigned([&client2] {
        ASSERT_NO_THROW(client2.doRenew());
    });
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
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client1, IOAddress("2001:db8:2::28")));

    // Create client #2.
    Dhcp6Client client2;
    client2.setInterface("eth1");
    client2.setDUID("00:03:00:01:aa:bb:cc:dd:ee:ff");

    // Client #2 should get its reserved address from the first subnet.
    ASSERT_NO_THROW(client2.requestAddress(0xabca, IOAddress("2001:db8:1::30")));
    testAssigned([&client2] {
        ASSERT_NO_THROW(client2.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client2, IOAddress("2001:db8:1::28")));

    // Reconfigure the server. Now, the first client get's second client's
    // reservation and vice versa.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[5], *client1.getServer(), true, true, false));

    // The first client is trying to renew the lease but should get a different lease
    // because its lease is now reserved for some other client. The client won't be
    // assigned a lease for which it has a reservation because another client holds
    // this lease.
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doRenew());
    });
    ASSERT_TRUE(client1.hasLeaseWithZeroLifetimeForAddress(IOAddress("2001:db8:2::28")));
    ASSERT_FALSE(hasLeaseForAddress(client1, IOAddress("2001:db8:1::28")));

    // The client should be allocated a lease from one of the dynamic pools.
    if (!hasLeaseForAddressRange(client1, IOAddress("2001:db8:2::1"), IOAddress("2001:db8:2::64")) &&
        !hasLeaseForAddressRange(client1, IOAddress("2001:db8:1::1"), IOAddress("2001:db8:1::64"))) {
        ADD_FAILURE() << "unexpected lease allocated for renewing client";
    }

    // Client #2 is now renewing its lease and should get its newly reserved address.
    testAssigned([&client2] {
        ASSERT_NO_THROW(client2.doRenew());
    });
    ASSERT_TRUE(client2.hasLeaseWithZeroLifetimeForAddress(IOAddress("2001:db8:1::28")));
    ASSERT_TRUE(hasLeaseForAddress(client2, IOAddress("2001:db8:2::28")));

    // Same for client #1.
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doRenew());
    });
    ASSERT_TRUE(hasLeaseForAddress(client1, IOAddress("2001:db8:1::28")));
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
    testAssigned([&client] {
        ASSERT_NO_THROW(client.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client, IOAddress("2001:db8:2::16")));

    // Add option 1234 which would cause the client to be classified as "a-devices".
    OptionPtr option1234(new OptionUint16(Option::V6, 1234, 0x0001));
    client.addExtraOption(option1234);

    // The client should now be assigned the reserved address from the first subnet.
    testAssigned([&client] {
        ASSERT_NO_THROW(client.doRenew());
    });
    ASSERT_TRUE(client.hasLeaseWithZeroLifetimeForAddress(IOAddress("2001:db8:2::16")));
    ASSERT_TRUE(hasLeaseForAddress(client, IOAddress("2001:db8:1::28")));
}

// Subnet in which the client is renewing an address is restricted by classification.
TEST_F(Dhcpv6SharedNetworkTest, renewalRestrictedByClass) {
    // Create client.
    Dhcp6Client client;
    client.setInterface("eth1");

    // Create server configuration with a shared network including two subnets. Access to
    // the second subnet is restricted by client classification.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[12], *client.getServer()));

    // Add option 1234 to cause the client to belong to the class.
    OptionPtr option1234(new OptionUint16(Option::V6, 1234, 0x0002));
    client.addExtraOption(option1234);

    // Client requests an address from the second subnet which should be successful.
    ASSERT_NO_THROW(client.requestAddress(0xabca, IOAddress("2001:db8:2::20")));
    testAssigned([&client] {
        ASSERT_NO_THROW(client.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client, IOAddress("2001:db8:2::20")));

    // Now remove the client from this class.
    client.clearExtraOptions();

    // The client should not be able to renew the existing lease because it is now
    // prohibited by the classification. Instead, the client should get a lease from the
    // unrestricted subnet.
    testAssigned([&client] {
        ASSERT_NO_THROW(client.doRenew());
    });
    ASSERT_TRUE(client.hasLeaseWithZeroLifetimeForAddress(IOAddress("2001:db8:2::20")));
    ASSERT_TRUE(hasLeaseForAddress(client, IOAddress("2001:db8:1::20")));
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
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client1, IOAddress("2001:db8:1::20")));

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
    testAssigned([&client2] {
        ASSERT_NO_THROW(client2.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client2, IOAddress("2001:db8:2::20")));

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
    testAssigned([&client3] {
        ASSERT_NO_THROW(client3.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client3, IOAddress("3000::1")));

    // This option is specified on the global level.
    ASSERT_TRUE(client3.hasOptionWithAddress(D6O_NIS_SERVERS, "3000::20"));

    // Subnet specific value should be assigned.
    ASSERT_TRUE(client3.hasOptionWithAddress(D6O_NISP_SERVERS, "4000::5"));
}

// The same option is specified differently for each subnet belonging to the
// same shared network.
TEST_F(Dhcpv6SharedNetworkTest, optionsFromSelectedSubnet) {
    // Create a client.
    Dhcp6Client client;
    client.setInterface("eth1");

    // Create configuration with one shared network including three subnets with
    // the same option having different values.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[16], *client.getServer()));

    // Client provides no hint and any subnet can be picked from the shared network.
    ASSERT_NO_THROW(client.requestAddress(0xabca));

    // Request Name Servers option.
    ASSERT_NO_THROW(client.requestOption(D6O_NAME_SERVERS));

    // Send solicit without a hint. The client should be offered an address from the
    // shared network. Depending on the subnet from which the address has been allocated
    // a specific value of the Name Servers option should be returned.
    testAssigned([&client] {
        ASSERT_NO_THROW(client.doSolicit(true));
    });

    if (client.hasLeaseForAddress(IOAddress("2001:db8:1::20"))) {
        ASSERT_TRUE(client.hasOptionWithAddress(D6O_NAME_SERVERS, "4004::22"));

    } else if (client.hasLeaseForAddress(IOAddress("2001:db8:2::20"))) {
        ASSERT_TRUE(client.hasOptionWithAddress(D6O_NAME_SERVERS, "5555::33"));

    } else if (client.hasLeaseForAddress(IOAddress("2001:db8:3::20"))) {
        ASSERT_TRUE(client.hasOptionWithAddress(D6O_NAME_SERVERS, "1234::23"));
    }

    // This time let's provide a hint.
    client.clearRequestedIAs();
    client.requestAddress(0xabca, IOAddress("2001:db8:2::20"));

    testAssigned([&client] {
        ASSERT_NO_THROW(client.doSolicit(true));
    });

    ASSERT_TRUE(client.hasLeaseForAddress(IOAddress("2001:db8:2::20")));
    ASSERT_TRUE(client.hasOptionWithAddress(D6O_NAME_SERVERS, "5555::33"));

    // This time, let's do the 4-way exchange.
    testAssigned([&client] {
        ASSERT_NO_THROW(client.doSARR());
    });

    ASSERT_TRUE(client.hasLeaseForAddress(IOAddress("2001:db8:2::20")));
    ASSERT_TRUE(client.hasOptionWithAddress(D6O_NAME_SERVERS, "5555::33"));

    // And renew the lease.
    testAssigned([&client] {
        ASSERT_NO_THROW(client.doRenew());
    });
    ASSERT_TRUE(client.hasLeaseForAddress(IOAddress("2001:db8:2::20")));
    ASSERT_TRUE(client.hasOptionWithAddress(D6O_NAME_SERVERS, "5555::33"));
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
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doSARR());
    });
    if (!hasLeaseForAddress(client1, IOAddress("2001:db8:1::20")) &&
        !hasLeaseForAddress(client1, IOAddress("2001:db8:2::20"))) {
        ADD_FAILURE() << "unexpected shared network selected for the client";
    }

    // Client #2.
    Dhcp6Client client2;
    client2.setInterface("eth0");
    client2.requestAddress(0xabca);

    // Client #2 should be assigned an address from one of the two subnets
    // belonging to the second shared network.
    testAssigned([&client2] {
        ASSERT_NO_THROW(client2.doSARR());
    });
    if (!hasLeaseForAddress(client2, IOAddress("2001:db8:3::20")) &&
        !hasLeaseForAddress(client2, IOAddress("2001:db8:4::20"))) {
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
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doSARR());
    });
    if (!hasLeaseForAddress(client1, IOAddress("2001:db8:1::20")) &&
        !hasLeaseForAddress(client1, IOAddress("2001:db8:2::20"))) {
        ADD_FAILURE() << "unexpected shared network selected for the client";
    }

    // Create relayed client #2.
    Dhcp6Client client2;
    client2.useRelay(true, IOAddress("3000::2"));
    client2.requestAddress(0xabca);

    // Client #2 should be assigned an address from one of the two subnets
    // belonging to the second shared network
    testAssigned([&client2] {
        ASSERT_NO_THROW(client2.doSARR());
    });
    if (!hasLeaseForAddress(client2, IOAddress("2001:db8:3::20")) &&
        !hasLeaseForAddress(client2, IOAddress("2001:db8:4::20"))) {
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
    testAssigned([&client] {
        ASSERT_NO_THROW(client.doSARR());
    });

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

    // The client 1 should be offered an address from the second subnet.
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doSolicit(true));
    });
    ASSERT_TRUE(hasLeaseForAddress(client1, IOAddress("2001:db8:2::20"),
                                   LeaseOnServer::MUST_NOT_EXIST));

    // Create another client which will belong to a different class.
    Dhcp6Client client2;
    client2.setInterface("eth1");
    client2.requestAddress(0xabcd);

    /// Add option 1234 which will cause the client 2 to be classified as "a-devices".
    option1234.reset(new OptionUint16(Option::V6, 1234, 0x0001));
    client2.addExtraOption(option1234);

    // Client 2 should be offered an address from the first subnet.
    testAssigned([&client2] {
        ASSERT_NO_THROW(client2.doSolicit(true));
    });
    ASSERT_TRUE(hasLeaseForAddress(client2, IOAddress("2001:db8:1::20"),
                                   LeaseOnServer::MUST_NOT_EXIST));
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
    testAssigned([&client] {
        ASSERT_NO_THROW(client.doSARR());
    });
    // The two addresses should come from different subnets.
    ASSERT_TRUE(hasLeaseForAddress(client, IOAddress("2001:db8:1::20")));
    ASSERT_TRUE(hasLeaseForAddress(client, IOAddress("2001:db8:2::20")));
    // Same for prefixes.
    ASSERT_TRUE(hasLeaseForPrefixPool(client, IOAddress("4000::"), 96, 96));
    ASSERT_TRUE(hasLeaseForPrefixPool(client, IOAddress("5000::"), 96, 96));

    // Try to renew.
    testAssigned([&client] {
        ASSERT_NO_THROW(client.doRenew());
    });
    ASSERT_TRUE(hasLeaseForAddress(client, IOAddress("2001:db8:1::20")));
    ASSERT_TRUE(hasLeaseForAddress(client, IOAddress("2001:db8:2::20")));
    ASSERT_TRUE(hasLeaseForPrefixPool(client, IOAddress("4000::"), 96, 96));
    ASSERT_TRUE(hasLeaseForPrefixPool(client, IOAddress("5000::"), 96, 96));
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
    testAssigned([&client] {
        ASSERT_NO_THROW(client.doSARR());
    });
    ASSERT_EQ(4, client.getLeaseNum());
    // The client should have got one reserved address and one reserved prefix.
    ASSERT_TRUE(hasLeaseForAddress(client, IOAddress("2001:db8:2::28")));
    ASSERT_TRUE(hasLeaseForPrefix(client, IOAddress("5000::8:0000"), 112, IAID(0x1111)));

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
    testAssigned([&client] {
        ASSERT_NO_THROW(client.doRenew());
    });
    ASSERT_EQ(4, client.getLeaseNum());
    ASSERT_TRUE(hasLeaseForAddress(client, IOAddress("2001:db8:2::28")));
    ASSERT_TRUE(hasLeaseForPrefix(client, IOAddress("5000::8:0000"), 112, IAID(0x1111)));

    leases_1234 = client.getLeasesByIAID(0x1234);
    ASSERT_EQ(1, leases_1234.size());
    ASSERT_NE("2001:db8:2::28", leases_1234[0].addr_.toText());

    leases_2222 = client.getLeasesByIAID(0x2222);
    ASSERT_EQ(1, leases_2222.size());
    ASSERT_NE(IOAddress("5000::8:0000").toText(), leases_2222[0].addr_.toText());
}

// Relay address is specified for each subnet within shared network.
TEST_F(Dhcpv6SharedNetworkTest, relaySpecifiedForEachSubnet) {
    // Create client.
    Dhcp6Client client;
    client.useRelay(true, IOAddress("3001::1"));

    // Client will request two addresses.
    client.requestAddress(0xabcd);
    client.requestAddress(0x1234);

    // Configure the server with three subnets. Two of them belong to a shared network.
    // Each subnet is configured with relay info, i.e. IP address of the relay agent
    // for which the shared network is used.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[13], *client.getServer()));

    // 4-way exchange.
    testAssigned([&client] {
        ASSERT_NO_THROW(client.doSARR());
    });
    ASSERT_EQ(2, client.getLeaseNum());

    // The client should have got two leases, one from each subnet within the
    // shared network.
    ASSERT_TRUE(hasLeaseForAddress(client, IOAddress("2001:db8:1::20")));
    ASSERT_TRUE(hasLeaseForAddress(client, IOAddress("2001:db8:2::20")));
}

// Shared network is selected based on interface id.
TEST_F(Dhcpv6SharedNetworkTest, sharedNetworkSelectedByInterfaceId) {
    // Create client #1. This is a relayed client for which interface id
    // has been specified and this interface id is matching the one specified
    // for the shared network.
    Dhcp6Client client1;
    client1.useRelay(true, IOAddress("3001::1"));
    client1.useInterfaceId("vlan10");

    // Configure the server with one shared network and one subnet outside of the
    // shared network.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[14], *client1.getServer()));

    // Client #1 should be assigned an address from shared network.
    ASSERT_NO_THROW(client1.requestAddress(0xabca0));
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client1, IOAddress("2001:db8:1::20")));

    // Create client #2. This is a relayed client which is using interface id
    // matching a subnet outside of the shared network.
    Dhcp6Client client2(client1.getServer());
    client2.useRelay(true, IOAddress("3001::2"));
    client2.useInterfaceId("vlan1000");
    ASSERT_NO_THROW(client2.requestAddress(0xabca0));
    testAssigned([&client2] {
        ASSERT_NO_THROW(client2.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client2, IOAddress("2001:db8:2::20")));
}

// Shared network is selected based on interface id specified for a subnet
// belonging to a shared network.
TEST_F(Dhcpv6SharedNetworkTest, sharedNetworkSelectedByInterfaceIdInSubnet) {
    // Create client #1. This is a relayed client for which interface id
    // has been specified and this interface id is matching the one specified
    // for the shared network.
    Dhcp6Client client1;
    client1.useRelay(true, IOAddress("3001::1"));
    client1.useInterfaceId("vlan10");

    // Configure the server with one shared network and one subnet outside of the
    // shared network.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[15], *client1.getServer()));

    // Client #1 should be assigned an address from shared network.
    ASSERT_NO_THROW(client1.requestAddress(0xabca0));
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client1, IOAddress("2001:db8:1::20")));

    // Create client #2. This is a relayed client which is using interface id
    // matching a subnet outside of the shared network.
    Dhcp6Client client2(client1.getServer());
    client2.useRelay(true, IOAddress("3001::2"));
    client2.useInterfaceId("vlan1000");
    ASSERT_NO_THROW(client2.requestAddress(0xabca0));
    testAssigned([&client2] {
        ASSERT_NO_THROW(client2.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client2, IOAddress("2001:db8:2::20")));
}

// Check that the rapid-commit works with shared networks. Rapid-commit
// enabled on each subnet separately.
TEST_F(Dhcpv6SharedNetworkTest, sharedNetworkRapidCommit1) {
    testRapidCommit(NETWORKS_CONFIG[17], true, "2001:db8:1::20", "2001:db8:2::20");
}

// Check that the rapid-commit works with shared networks. Rapid-commit
// enabled for the whole shared network. This should be applied to both
// subnets.
TEST_F(Dhcpv6SharedNetworkTest, sharedNetworkRapidCommit2) {
    testRapidCommit(NETWORKS_CONFIG[18], true, "2001:db8:1::20", "2001:db8:2::20");
}

// Check that the rapid-commit is disabled by default.
TEST_F(Dhcpv6SharedNetworkTest, sharedNetworkRapidCommit3) {
    testRapidCommit(NETWORKS_CONFIG[1], false, "", "");
}

// Pool is selected based on the client class specified.
TEST_F(Dhcpv6SharedNetworkTest, poolInSharedNetworkSelectedByClass) {
    // Create client #1.
    Dhcp6Client client1;
    client1.setInterface("eth1");

    // Configure the server with one shared network including one subnet and
    // two pools. The access to one of the pools is restricted by
    // by client classification.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[19], *client1.getServer()));

    // Client #1 requests an address in the restricted pool but can't be assigned
    // this address because the client doesn't belong to a certain class.
    ASSERT_NO_THROW(client1.requestAddress(0xabca, IOAddress("2001:db8:1::20")));
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client1, IOAddress("2001:db8:1::50")));

    // Release the lease that the client has got, because we'll need this address
    // further in the test.
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doRelease());
    });

    // Add option 1234 which would cause the client to be classified as "a-devices".
    OptionPtr option1234(new OptionUint16(Option::V6, 1234, 0x0001));
    client1.addExtraOption(option1234);

    // This time, the allocation of the address provided as hint should be successful.
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client1, IOAddress("2001:db8:1::20")));

    // Client 2 should be assigned an address from the unrestricted pool.
    Dhcp6Client client2(client1.getServer());
    client2.setInterface("eth1");
    ASSERT_NO_THROW(client2.requestAddress(0xabca0));
    testAssigned([&client2] {
        ASSERT_NO_THROW(client2.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client2, IOAddress("2001:db8:1::50")));

    // Now, let's reconfigure the server to also apply restrictions on the
    // pool to which client2 now belongs.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[20], *client1.getServer()));

    testAssigned([&client2] {
        ASSERT_NO_THROW(client2.doRenew());
    });
    EXPECT_EQ(0, client2.getLeasesWithNonZeroLifetime().size());

    // If we add option 1234 with a value matching this class, the lease should
    // get renewed.
    OptionPtr option1234_bis(new OptionUint16(Option::V6, 1234, 0x0002));
    client2.addExtraOption(option1234_bis);
    testAssigned([&client2] {
        ASSERT_NO_THROW(client2.doRenew());
    });
    EXPECT_EQ(1, client2.getLeaseNum());
    EXPECT_EQ(1, client2.getLeasesWithNonZeroLifetime().size());
}

// Pool is selected based on the client class specified using a plain subnet.
TEST_F(Dhcpv6SharedNetworkTest, poolInSubnetSelectedByClass) {
    // Create client #1.
    Dhcp6Client client1;
    client1.setInterface("eth1");

    // Configure the server with one plain subnet including two pools.
    // The access to one of the pools is restricted by client classification.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[21], *client1.getServer()));

    // Client #1 requests an address in the restricted pool but can't be assigned
    // this address because the client doesn't belong to a certain class.
    ASSERT_NO_THROW(client1.requestAddress(0xabca, IOAddress("2001:db8:1::20")));
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client1, IOAddress("2001:db8:1::50")));

    // Release the lease that the client has got, because we'll need this address
    // further in the test.
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doRelease());
    });

    // Add option 1234 which would cause the client to be classified as "a-devices".
    OptionPtr option1234(new OptionUint16(Option::V6, 1234, 0x0001));
    client1.addExtraOption(option1234);

    // This time, the allocation of the address provided as hint should be successful.
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client1, IOAddress("2001:db8:1::20")));

    // Client 2 should be assigned an address from the unrestricted pool.
    Dhcp6Client client2(client1.getServer());
    client2.setInterface("eth1");
    ASSERT_NO_THROW(client2.requestAddress(0xabca0));
    testAssigned([&client2] {
        ASSERT_NO_THROW(client2.doSARR());
    });
    ASSERT_TRUE(hasLeaseForAddress(client2, IOAddress("2001:db8:1::50")));

    // Now, let's reconfigure the server to also apply restrictions on the
    // pool to which client2 now belongs.
    ASSERT_NO_FATAL_FAILURE(configure(NETWORKS_CONFIG[22], *client1.getServer()));

    testAssigned([&client2] {
        ASSERT_NO_THROW(client2.doRenew());
    });
    EXPECT_EQ(0, client2.getLeasesWithNonZeroLifetime().size());

    // If we add option 1234 with a value matching this class, the lease should
    // get renewed.
    OptionPtr option1234_bis(new OptionUint16(Option::V6, 1234, 0x0002));
    client2.addExtraOption(option1234_bis);
    testAssigned([&client2] {
        ASSERT_NO_THROW(client2.doRenew());
    });
    EXPECT_EQ(1, client2.getLeaseNum());
    EXPECT_EQ(1, client2.getLeasesWithNonZeroLifetime().size());
}

// Verify option processing precedence
// Order is global < class < shared-network < subnet < pools < host reservation
TEST_F(Dhcpv6SharedNetworkTest, precedenceGlobal) {
    const std::string config =
        "{"
        "    \"option-data\": ["
        "        {"
        "           \"name\": \"dns-servers\","
        "           \"data\": \"2001:db8:1::1\""
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
        "                    \"reservations\": ["
        "                        {"
        "                            \"duid\": \"00:03:00:01:aa:bb:cc:dd:ee:ff\","
        "                            \"ip-addresses\": [ \"2001:db8:1::28\" ]"
        "                        }"
        "                    ]"
        "                }"
        "            ]"
        "        }"
        "    ]"
        "}";

    testPrecedence(config, "2001:db8:1::1");
}

// Verify option processing precedence
// Order is global < class < shared-network < subnet < pools < host reservation
TEST_F(Dhcpv6SharedNetworkTest, precedenceClass) {
    const std::string config =
        "{"
        "    \"option-data\": ["
        "        {"
        "           \"name\": \"dns-servers\","
        "           \"data\": \"2001:db8:1::1\""
        "        }"
        "    ],"
        "    \"client-classes\": ["
        "        {"
        "            \"name\": \"alpha\","
        "            \"test\": \"'' == ''\","
        "            \"option-data\": ["
        "                {"
        "                   \"name\": \"dns-servers\","
        "                   \"data\": \"2001:db8:1::2\""
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
        "                            \"pool\": \"2001:db8:1::1 - 2001:db8:1::64\""
        "                        }"
        "                    ],"
        "                    \"reservations\": ["
        "                        {"
        "                            \"duid\": \"00:03:00:01:aa:bb:cc:dd:ee:ff\","
        "                            \"ip-addresses\": [ \"2001:db8:1::28\" ]"
        "                        }"
        "                    ]"
        "                }"
        "            ]"
        "        }"
        "    ]"
        "}";

    testPrecedence(config, "2001:db8:1::2");
}

// Verify option processing precedence
// Order is global < class < shared-network < subnet < pools < host reservation
TEST_F(Dhcpv6SharedNetworkTest, precedenceClasses) {
    const std::string config =
        "{"
        "    \"option-data\": ["
        "        {"
        "           \"name\": \"dns-servers\","
        "           \"data\": \"2001:db8:1::1\""
        "        }"
        "    ],"
        "    \"client-classes\": ["
        "        {"
        "            \"name\": \"beta\","
        "            \"test\": \"'' == ''\","
        "            \"option-data\": ["
        "                {"
        "                   \"name\": \"dns-servers\","
        "                   \"data\": \"2001:db8:1::2\""
        "                }"
        "            ]"
        "        },"
        "        {"
        "            \"name\": \"alpha\","
        "            \"test\": \"'' == ''\","
        "            \"option-data\": ["
        "                {"
        "                   \"name\": \"dns-servers\","
        "                   \"data\": \"2001:db8:1::3\""
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
        "                            \"pool\": \"2001:db8:1::1 - 2001:db8:1::64\""
        "                        }"
        "                    ],"
        "                    \"reservations\": ["
        "                        {"
        "                            \"duid\": \"00:03:00:01:aa:bb:cc:dd:ee:ff\","
        "                            \"ip-addresses\": [ \"2001:db8:1::28\" ]"
        "                        }"
        "                    ]"
        "                }"
        "            ]"
        "        }"
        "    ]"
        "}";

    // Class order is the insert order
    testPrecedence(config, "2001:db8:1::2");
}

// Verify option processing precedence
// Order is global < class < shared-network < subnet < pools < host reservation
TEST_F(Dhcpv6SharedNetworkTest, precedenceNetworkClass) {
    const std::string config =
        "{"
        "    \"option-data\": ["
        "        {"
        "           \"name\": \"dns-servers\","
        "           \"data\": \"2001:db8:1::1\""
        "        }"
        "    ],"
        "    \"client-classes\": ["
        "        {"
        "            \"name\": \"alpha\","
        "            \"test\": \"'' == ''\","
        "            \"option-data\": ["
        "                {"
        "                   \"name\": \"dns-servers\","
        "                   \"data\": \"2001:db8:1::2\""
        "                }"
        "            ]"
        "        }"
        "    ],"
        "    \"shared-networks\": ["
        "        {"
        "            \"name\": \"frog\","
        "            \"interface\": \"eth1\","
        "            \"option-data\": ["
        "                {"
        "                   \"name\": \"dns-servers\","
        "                   \"data\": \"2001:db8:1::3\""
        "                }"
        "            ],"
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
        "                            \"duid\": \"00:03:00:01:aa:bb:cc:dd:ee:ff\","
        "                            \"ip-addresses\": [ \"2001:db8:1::28\" ]"
        "                        }"
        "                    ]"
        "                }"
        "            ]"
        "        }"
        "    ]"
        "}";

    testPrecedence(config, "2001:db8:1::3");
}

// Verify option processing precedence
// Order is global < class < shared-network < subnet < pools < host reservation
TEST_F(Dhcpv6SharedNetworkTest, precedenceSubnet) {
    const std::string config =
        "{"
        "    \"option-data\": ["
        "        {"
        "           \"name\": \"dns-servers\","
        "           \"data\": \"2001:db8:1::1\""
        "        }"
        "    ],"
        "    \"client-classes\": ["
        "        {"
        "            \"name\": \"alpha\","
        "            \"test\": \"'' == ''\","
        "            \"option-data\": ["
        "                {"
        "                   \"name\": \"dns-servers\","
        "                   \"data\": \"2001:db8:1::2\""
        "                }"
        "            ]"
        "        }"
        "    ],"
        "    \"shared-networks\": ["
        "        {"
        "            \"name\": \"frog\","
        "            \"interface\": \"eth1\","
        "            \"option-data\": ["
        "                {"
        "                   \"name\": \"dns-servers\","
        "                   \"data\": \"2001:db8:1::3\""
        "                }"
        "            ],"
        "            \"subnet6\": ["
        "                {"
        "                    \"subnet\": \"2001:db8:1::/64\","
        "                    \"id\": 10,"
        "                    \"option-data\": ["
        "                        {"
        "                           \"name\": \"dns-servers\","
        "                           \"data\": \"2001:db8:1::4\""
        "                        }"
        "                    ],"
        "                    \"pools\": ["
        "                        {"
        "                            \"pool\": \"2001:db8:1::1 - 2001:db8:1::64\""
        "                        }"
        "                    ],"
        "                    \"reservations\": ["
        "                        {"
        "                            \"duid\": \"00:03:00:01:aa:bb:cc:dd:ee:ff\","
        "                            \"ip-addresses\": [ \"2001:db8:1::28\" ]"
        "                        }"
        "                    ]"
        "                }"
        "            ]"
        "        }"
        "    ]"
        "}";

    testPrecedence(config, "2001:db8:1::4");
}

// Verify option processing precedence
// Order is global < class < shared-network < subnet < pools < host reservation
TEST_F(Dhcpv6SharedNetworkTest, precedencePool) {
    const std::string config =
        "{"
        "    \"option-data\": ["
        "        {"
        "           \"name\": \"dns-servers\","
        "           \"data\": \"2001:db8:1::1\""
        "        }"
        "    ],"
        "    \"client-classes\": ["
        "        {"
        "            \"name\": \"alpha\","
        "            \"test\": \"'' == ''\","
        "            \"option-data\": ["
        "                {"
        "                   \"name\": \"dns-servers\","
        "                   \"data\": \"2001:db8:1::2\""
        "                }"
        "            ]"
        "        }"
        "    ],"
        "    \"shared-networks\": ["
        "        {"
        "            \"name\": \"frog\","
        "            \"interface\": \"eth1\","
        "            \"option-data\": ["
        "                {"
        "                   \"name\": \"dns-servers\","
        "                   \"data\": \"2001:db8:1::3\""
        "                }"
        "            ],"
        "            \"subnet6\": ["
        "                {"
        "                    \"subnet\": \"2001:db8:1::/64\","
        "                    \"id\": 10,"
        "                    \"option-data\": ["
        "                        {"
        "                           \"name\": \"dns-servers\","
        "                           \"data\": \"2001:db8:1::4\""
        "                        }"
        "                    ],"
        "                    \"pools\": ["
        "                        {"
        "                            \"pool\": \"2001:db8:1::1 - 2001:db8:1::64\","
        "                            \"option-data\": ["
        "                                {"
        "                                   \"name\": \"dns-servers\","
        "                                   \"data\": \"2001:db8:1::5\""
        "                                }"
        "                            ]"
        "                        }"
        "                    ],"
        "                    \"reservations\": ["
        "                        {"
        "                            \"duid\": \"00:03:00:01:aa:bb:cc:dd:ee:ff\","
        "                            \"ip-addresses\": [ \"2001:db8:1::28\" ]"
        "                        }"
        "                    ]"
        "                }"
        "            ]"
        "        }"
        "    ]"
        "}";

    testPrecedence(config, "2001:db8:1::5");
}

// Verify option processing precedence
// Order is global < class < shared-network < subnet < pools < host reservation
TEST_F(Dhcpv6SharedNetworkTest, precedenceReservation) {
    const std::string config =
        "{"
        "    \"option-data\": ["
        "        {"
        "           \"name\": \"dns-servers\","
        "           \"data\": \"2001:db8:1::1\""
        "        }"
        "    ],"
        "    \"client-classes\": ["
        "        {"
        "            \"name\": \"alpha\","
        "            \"test\": \"'' == ''\","
        "            \"option-data\": ["
        "                {"
        "                   \"name\": \"dns-servers\","
        "                   \"data\": \"2001:db8:1::2\""
        "                }"
        "            ]"
        "        }"
        "    ],"
        "    \"shared-networks\": ["
        "        {"
        "            \"name\": \"frog\","
        "            \"interface\": \"eth1\","
        "            \"option-data\": ["
        "                {"
        "                   \"name\": \"dns-servers\","
        "                   \"data\": \"2001:db8:1::3\""
        "                }"
        "            ],"
        "            \"subnet6\": ["
        "                {"
        "                    \"subnet\": \"2001:db8:1::/64\","
        "                    \"id\": 10,"
        "                    \"option-data\": ["
        "                        {"
        "                           \"name\": \"dns-servers\","
        "                           \"data\": \"2001:db8:1::4\""
        "                        }"
        "                    ],"
        "                    \"pools\": ["
        "                        {"
        "                            \"pool\": \"2001:db8:1::1 - 2001:db8:1::64\","
        "                            \"option-data\": ["
        "                                {"
        "                                   \"name\": \"dns-servers\","
        "                                   \"data\": \"2001:db8:1::5\""
        "                                }"
        "                            ]"
        "                        }"
        "                    ],"
        "                    \"reservations\": ["
        "                        {"
        "                            \"duid\": \"00:03:00:01:aa:bb:cc:dd:ee:ff\","
        "                            \"ip-addresses\": [ \"2001:db8:1::28\" ],"
        "                            \"option-data\": ["
        "                                {"
        "                                   \"name\": \"dns-servers\","
        "                                   \"data\": \"2001:db8:1::6\""
        "                                }"
        "                            ]"
        "                        }"
        "                    ]"
        "                }"
        "            ]"
        "        }"
        "    ]"
        "}";

    testPrecedence(config, "2001:db8:1::6");
}

} // end of anonymous namespace
