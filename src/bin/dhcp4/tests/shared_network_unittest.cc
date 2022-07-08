// Copyright (C) 2017-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/io_address.h>
#include <cc/data.h>
#include <dhcp/dhcp4.h>
#include <dhcp/tests/iface_mgr_test_config.h>
#include <dhcp/option.h>
#include <dhcp/option_int.h>
#include <dhcp/option_string.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/cfg_subnets4.h>
#include <dhcpsrv/lease_mgr_factory.h>
#include <dhcp4/json_config_parser.h>
#include <dhcp4/tests/dhcp4_client.h>
#include <dhcp4/tests/dhcp4_test_utils.h>
#include <stats/stats_mgr.h>
#include <boost/pointer_cast.hpp>
#include <boost/shared_ptr.hpp>
#include <functional>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::stats;

namespace {

/// @brief Array of server configurations used throughout the tests.
const char* NETWORKS_CONFIG[] = {
// Configuration #0
// - 1 shared network with 2 subnets (interface specified)
// - 1 "plain" subnet (different interface specified)
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"valid-lifetime\": 600,"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface\": \"eth1\","
    "            \"comment\": \"example\","
    "            \"subnet4\": ["
    "                {"
    "                    \"subnet\": \"192.0.2.0/26\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"192.0.2.63 - 192.0.2.63\""
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"10.0.0.0/24\","
    "                    \"id\": 100,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"10.0.0.16 - 10.0.0.16\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ],"
    "    \"subnet4\": ["
    "        {"
    "            \"subnet\": \"192.0.2.64/26\","
    "            \"id\": 1000,"
    "            \"interface\": \"eth0\","
    "            \"pools\": ["
    "                {"
    "                    \"pool\": \"192.0.2.65 - 192.0.2.65\""
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #1
// - 1 shared networks with 1 subnet, relay ip specified
// - 1 "plain" subnet, relay ip specified
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"valid-lifetime\": 600,"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"relay\": {"
    "                \"ip-address\": \"192.3.5.6\""
    "            },"
    "            \"subnet4\": ["
    "                {"
    "                    \"subnet\": \"192.0.2.0/26\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"192.0.2.63 - 192.0.2.63\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ],"
    "    \"subnet4\": ["
    "        {"
    "            \"subnet\": \"192.0.2.64/26\","
    "            \"id\": 1000,"
    "            \"relay\": {"
    "                \"ip-address\": \"192.1.2.3\""
    "            },"
    "            \"pools\": ["
    "                {"
    "                    \"pool\": \"192.0.2.65 - 192.0.2.65\""
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #2
// - 2 classes defined
// - 1 shared network with 2 subnets (first has class restriction)
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"valid-lifetime\": 600,"
    "    \"client-classes\": ["
    "        {"
    "            \"name\": \"a-devices\","
    "            \"test\": \"option[93].hex == 0x0001\""
    "        },"
    "        {"
    "            \"name\": \"b-devices\","
    "            \"test\": \"option[93].hex == 0x0002\""
    "        }"
    "    ],"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"relay\": {"
    "                \"ip-address\": \"192.3.5.6\""
    "            },"
    "            \"subnet4\": ["
    "                {"
    "                    \"subnet\": \"192.0.2.0/26\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"192.0.2.63 - 192.0.2.63\""
    "                        }"
    "                    ],"
    "                    \"client-class\": \"a-devices\""
    "                },"
    "                {"
    "                    \"subnet\": \"10.0.0.0/24\","
    "                    \"id\": 100,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"10.0.0.16 - 10.0.0.16\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #3
// - 2 classes specified
// - 1 shared network with 2 subnets (each with class restriction)
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"valid-lifetime\": 600,"
    "    \"client-classes\": ["
    "        {"
    "            \"name\": \"a-devices\","
    "            \"test\": \"option[93].hex == 0x0001\""
    "        },"
    "        {"
    "            \"name\": \"b-devices\","
    "            \"test\": \"option[93].hex == 0x0002\""
    "        }"
    "    ],"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"relay\": {"
    "                \"ip-address\": \"192.3.5.6\""
    "            },"
    "            \"subnet4\": ["
    "                {"
    "                    \"subnet\": \"192.0.2.0/26\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"192.0.2.63 - 192.0.2.63\""
    "                        }"
    "                    ],"
    "                    \"client-class\": \"a-devices\""
    "                },"
    "                {"
    "                    \"subnet\": \"10.0.0.0/24\","
    "                    \"id\": 100,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"10.0.0.16 - 10.0.0.16\""
    "                        }"
    "                    ],"
    "                    \"client-class\": \"b-devices\""
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #4
// - 1 shared network with 2 subnets, each has one host reservation
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"valid-lifetime\": 600,"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"relay\": {"
    "                \"ip-address\": \"192.3.5.6\""
    "            },"
    "            \"subnet4\": ["
    "                {"
    "                    \"subnet\": \"192.0.2.0/26\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"192.0.2.1 - 192.0.2.63\""
    "                        }"
    "                    ],"
    "                    \"reservations\": ["
    "                        {"
    "                            \"hw-address\": \"aa:bb:cc:dd:ee:ff\","
    "                            \"ip-address\": \"192.0.2.28\""
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"10.0.0.0/24\","
    "                    \"id\": 100,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"10.0.0.1 - 10.0.0.254\""
    "                        }"
    "                    ],"
    "                    \"reservations\": ["
    "                        {"
    "                            \"hw-address\": \"11:22:33:44:55:66\","
    "                            \"ip-address\": \"10.0.0.29\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #5
// - 1 shared network, with 2 subnets. Each has host reservation
// - similar to config #4, but with different hw-address reserved
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"valid-lifetime\": 600,"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"relay\": {"
    "                \"ip-address\": \"192.3.5.6\""
    "            },"
    "            \"subnet4\": ["
    "                {"
    "                    \"subnet\": \"192.0.2.0/26\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"192.0.2.1 - 192.0.2.63\""
    "                        }"
    "                    ],"
    "                    \"reservations\": ["
    "                        {"
    "                            \"hw-address\": \"11:22:33:44:55:66\","
    "                            \"ip-address\": \"192.0.2.28\""
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"10.0.0.0/24\","
    "                    \"id\": 100,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"10.0.0.1 - 10.0.0.254\""
    "                        }"
    "                    ],"
    "                    \"reservations\": ["
    "                        {"
    "                            \"hw-address\": \"aa:bb:cc:dd:ee:ff\","
    "                            \"ip-address\": \"10.0.0.29\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #6
// - 1 class
// - 1 shared network, with 2 subnets. First has class restriction and
//     host reservation
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"valid-lifetime\": 600,"
    "    \"client-classes\": ["
    "        {"
    "            \"name\": \"a-devices\","
    "            \"test\": \"option[93].hex == 0x0001\""
    "        }"
    "    ],"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"relay\": {"
    "                \"ip-address\": \"192.3.5.6\""
    "            },"
    "            \"subnet4\": ["
    "                {"
    "                    \"subnet\": \"192.0.2.0/26\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"192.0.2.1 - 192.0.2.63\""
    "                        }"
    "                    ],"
    "                    \"client-class\": \"a-devices\","
    "                    \"reservations\": ["
    "                        {"
    "                            \"hw-address\": \"aa:bb:cc:dd:ee:ff\","
    "                            \"ip-address\": \"192.0.2.28\""
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"10.0.0.0/24\","
    "                    \"id\": 100,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"10.0.0.16 - 10.0.0.16\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #7
// - 1 global option
// - 1 shared network with some options and 2 subnets (the first one has extra
//     options)
// - 1 plain subnet (that has an option)
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"valid-lifetime\": 600,"
    "    \"option-data\": ["
    "        {"
    "            \"name\": \"log-servers\","
    "            \"data\": \"1.2.3.4\""
    "        }"
    "    ],"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface\": \"eth1\","
    "            \"option-data\": ["
    "                {"
    "                    \"name\": \"domain-name-servers\","
    "                    \"data\": \"10.1.2.3\""
    "                },"
    "                {"
    "                    \"name\": \"cookie-servers\","
    "                    \"data\": \"10.6.5.4\""
    "                }"
    "            ],"
    "            \"subnet4\": ["
    "                {"
    "                    \"subnet\": \"192.0.2.0/26\","
    "                    \"id\": 10,"
    "                    \"option-data\": ["
    "                        {"
    "                            \"name\": \"routers\","
    "                            \"data\": \"192.0.2.5\""
    "                        },"
    "                        {"
    "                            \"name\": \"cookie-servers\","
    "                            \"data\": \"10.5.4.3\""
    "                        }"
    "                    ],"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"192.0.2.63 - 192.0.2.63\""
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"10.0.0.0/24\","
    "                    \"id\": 100,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"10.0.0.16 - 10.0.0.16\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ],"
    "    \"subnet4\": ["
    "        {"
    "            \"subnet\": \"192.0.2.64/26\","
    "            \"id\": 1000,"
    "            \"interface\": \"eth0\","
    "            \"option-data\": ["
    "                {"
    "                    \"name\": \"cookie-servers\","
    "                    \"data\": \"10.1.1.1\""
    "                }"
    "            ],"
    "            \"pools\": ["
    "                {"
    "                    \"pool\": \"192.0.2.65 - 192.0.2.65\""
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #8
// - two shared networks, each with two subnets (each with interface specified)
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"valid-lifetime\": 600,"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface\": \"eth1\","
    "            \"subnet4\": ["
    "                {"
    "                    \"subnet\": \"192.0.2.0/26\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"192.0.2.1 - 192.0.2.63\""
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"192.0.2.64/26\","
    "                    \"id\": 100,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"192.0.2.65 - 192.0.2.127\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        },"
    "        {"
    "            \"name\": \"dog\","
    "            \"interface\": \"eth0\","
    "            \"subnet4\": ["
    "                {"
    "                    \"subnet\": \"10.0.0.0/26\","
    "                    \"id\": 1000,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"10.0.0.1 - 10.0.0.63\""
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"10.0.0.64/26\","
    "                    \"id\": 10000,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"10.0.0.65 - 10.0.0.127\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #9
// - 2 shared networks, each with relay ip address and 2 subnets
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"valid-lifetime\": 600,"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"relay\": { \"ip-address\": \"10.1.2.3\" },"
    "            \"subnet4\": ["
    "                {"
    "                    \"subnet\": \"192.0.2.0/26\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"192.0.2.1 - 192.0.2.63\""
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"192.0.2.64/26\","
    "                    \"id\": 100,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"192.0.2.65 - 192.0.2.127\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        },"
    "        {"
    "            \"name\": \"dog\","
    "            \"relay\": { \"ip-address\": \"192.1.2.3\" },"
    "            \"subnet4\": ["
    "                {"
    "                    \"subnet\": \"10.0.0.0/26\","
    "                    \"id\": 1000,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"10.0.0.1 - 10.0.0.63\""
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"10.0.0.64/26\","
    "                    \"id\": 10000,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"10.0.0.65 - 10.0.0.127\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",
// Configuration #10.
// - 1 client class
// - 1 shared network with two subnets (second has a host reservation)
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"valid-lifetime\": 600,"
    "    \"client-classes\": ["
    "        {"
    "            \"name\": \"class-with-bootfile\","
    "            \"boot-file-name\": \"/dev/null\""
    "        }"
    "    ],"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"relay\": {"
    "                \"ip-address\": \"192.3.5.6\""
    "            },"
    "            \"subnet4\": ["
    "                {"
    "                    \"subnet\": \"192.0.2.0/26\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"192.0.2.1 - 192.0.2.63\""
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"10.0.0.0/24\","
    "                    \"id\": 100,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"10.0.0.1 - 10.0.0.254\""
    "                        }"
    "                    ],"
    "                    \"reservations\": ["
    "                        {"
    "                            \"hw-address\": \"11:22:33:44:55:66\","
    "                            \"ip-address\": \"10.0.0.29\","
    "                            \"hostname\": \"test.example.org\","
    "                            \"next-server\": \"10.10.10.10\","
    "                            \"client-classes\": [ \"class-with-bootfile\" ]"
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #11.
// - global value of match-client-id set to false
// - 1 shared network (match-client-id set to true) with 2 subnets
// - the first subnet has match-client-id set to false
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"valid-lifetime\": 600,"
    "    \"match-client-id\": false,"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface\": \"eth1\","
    "            \"match-client-id\": true,"
    "            \"subnet4\": ["
    "                {"
    "                    \"subnet\": \"192.0.2.0/26\","
    "                    \"id\": 10,"
    "                    \"match-client-id\": false"
    "                },"
    "                {"
    "                    \"subnet\": \"192.0.2.64/26\","
    "                    \"id\": 100,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"192.0.2.65 - 192.0.2.127\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #12.
// - global value of match-client-id set to false
// - 1 shared network (match-client-id set to false) with 2 subnets
// - the first subnet has match-client-id set to false
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"valid-lifetime\": 600,"
    "    \"match-client-id\": false,"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface\": \"eth1\","
    "            \"match-client-id\": false,"
    "            \"subnet4\": ["
    "                {"
    "                    \"subnet\": \"192.0.2.0/26\","
    "                    \"id\": 10,"
    "                    \"match-client-id\": false"
    "                },"
    "                {"
    "                    \"subnet\": \"192.0.2.64/26\","
    "                    \"id\": 100,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"192.0.2.65 - 192.0.2.127\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #13.
// - 2 classes
// - 2 shared networks, each with 1 subnet and client class restriction
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"client-classes\": ["
    "        {"
    "            \"name\": \"a-devices\","
    "            \"test\": \"option[93].hex == 0x0001\""
    "        },"
    "        {"
    "            \"name\": \"b-devices\","
    "            \"test\": \"option[93].hex == 0x0002\""
    "        }"
    "    ],"
    "    \"valid-lifetime\": 600,"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface\": \"eth1\","
    "            \"client-class\": \"a-devices\","
    "            \"subnet4\": ["
    "                {"
    "                    \"subnet\": \"192.0.2.0/26\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"192.0.2.63 - 192.0.2.63\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        },"
    "        {"
    "            \"name\": \"dog\","
    "            \"interface\": \"eth1\","
    "            \"client-class\": \"b-devices\","
    "            \"subnet4\": ["
    "                {"
    "                    \"subnet\": \"10.0.0.0/26\","
    "                    \"id\": 1000,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"10.0.0.63 - 10.0.0.63\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",
// Configuration #14
// - 1 shared networks with 2 subnets, relay ip specified,
//     each relay has its own relay ip specified
// - 1 "plain" subnet, relay ip specified
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"valid-lifetime\": 600,"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"relay\": {"
    "                \"ip-address\": \"192.3.5.6\""
    "            },"
    "            \"subnet4\": ["
    "                {"
    "                    \"subnet\": \"192.0.2.0/26\","
    "                    \"id\": 10,"
    "                    \"relay\": {"
    "                        \"ip-address\": \"192.1.1.1\""
    "                    },"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"192.0.2.63 - 192.0.2.63\""
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"10.0.0.0/24\","
    "                    \"id\": 100,"
    "                    \"relay\": {"
    "                        \"ip-address\": \"192.2.2.2\""
    "                    },"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"10.0.0.16 - 10.0.0.16\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ],"
    "    \"subnet4\": ["
    "        {"
    "            \"subnet\": \"192.0.2.64/26\","
    "            \"id\": 1000,"
    "            \"relay\": {"
    "                \"ip-address\": \"192.3.3.3\""
    "            },"
    "            \"pools\": ["
    "                {"
    "                    \"pool\": \"192.0.2.65 - 192.0.2.65\""
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #15
// - two shared networks, each comes with its own server identifier.
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"valid-lifetime\": 600,"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface\": \"eth1\","
    "            \"option-data\": ["
    "                {"
    "                    \"name\": \"dhcp-server-identifier\","
    "                    \"data\": \"1.2.3.4\""
    "                }"
    "            ],"
    "            \"subnet4\": ["
    "                {"
    "                    \"subnet\": \"192.0.2.0/26\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"192.0.2.1 - 192.0.2.63\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        },"
    "        {"
    "            \"name\": \"dog\","
    "            \"interface\": \"eth0\","
    "            \"option-data\": ["
    "                {"
    "                    \"name\": \"dhcp-server-identifier\","
    "                    \"data\": \"2.3.4.5\""
    "                }"
    "            ],"
    "            \"subnet4\": ["
    "                {"
    "                    \"subnet\": \"10.0.0.0/26\","
    "                    \"id\": 1000,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"10.0.0.1 - 10.0.0.63\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #16
// - 1 shared network with 1 subnet and 2 pools (first pool has class restriction)
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"client-classes\": ["
    "        {"
    "            \"name\": \"a-devices\","
    "            \"test\": \"option[93].hex == 0x0001\""
    "        },"
    "        {"
    "            \"name\": \"b-devices\","
    "            \"test\": \"option[93].hex == 0x0002\""
    "        }"
    "    ],"
    "    \"valid-lifetime\": 600,"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface\": \"eth1\","
    "            \"subnet4\": ["
    "                {"
    "                    \"subnet\": \"192.0.2.0/24\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"192.0.2.1 - 192.0.2.63\","
    "                            \"client-class\": \"a-devices\""
    "                        },"
    "                        {"
    "                            \"pool\": \"192.0.2.100 - 192.0.2.100\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #17
// - 1 shared network with 1 subnet and 2 pools (each with class restriction)
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"client-classes\": ["
    "        {"
    "            \"name\": \"a-devices\","
    "            \"test\": \"option[93].hex == 0x0001\""
    "        },"
    "        {"
    "            \"name\": \"b-devices\","
    "            \"test\": \"option[93].hex == 0x0002\""
    "        }"
    "    ],"
    "    \"valid-lifetime\": 600,"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"interface\": \"eth1\","
    "            \"subnet4\": ["
    "                {"
    "                    \"subnet\": \"192.0.2.0/24\","
    "                    \"id\": 10,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"192.0.2.1 - 192.0.2.63\","
    "                            \"client-class\": \"a-devices\""
    "                        },"
    "                        {"
    "                            \"pool\": \"192.0.2.100 - 192.0.2.100\","
    "                            \"client-class\": \"b-devices\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #18
// - plain subnet and 2 pools (first pool has class restriction)
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"client-classes\": ["
    "        {"
    "            \"name\": \"a-devices\","
    "            \"test\": \"option[93].hex == 0x0001\""
    "        },"
    "        {"
    "            \"name\": \"b-devices\","
    "            \"test\": \"option[93].hex == 0x0002\""
    "        }"
    "    ],"
    "    \"valid-lifetime\": 600,"
    "    \"subnet4\": ["
    "        {"
    "            \"subnet\": \"192.0.2.0/24\","
    "            \"id\": 10,"
    "            \"interface\": \"eth1\","
    "            \"pools\": ["
    "                {"
    "                    \"pool\": \"192.0.2.1 - 192.0.2.63\","
    "                    \"client-class\": \"a-devices\""
    "                },"
    "                {"
    "                    \"pool\": \"192.0.2.100 - 192.0.2.100\""
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #19
// - plain subnet and 2 pools (each with class restriction)
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"client-classes\": ["
    "        {"
    "            \"name\": \"a-devices\","
    "            \"test\": \"option[93].hex == 0x0001\""
    "        },"
    "        {"
    "            \"name\": \"b-devices\","
    "            \"test\": \"option[93].hex == 0x0002\""
    "        }"
    "    ],"
    "    \"valid-lifetime\": 600,"
    "    \"subnet4\": ["
    "        {"
    "            \"subnet\": \"192.0.2.0/24\","
    "            \"id\": 10,"
    "            \"interface\": \"eth1\","
    "            \"pools\": ["
    "                {"
    "                    \"pool\": \"192.0.2.1 - 192.0.2.63\","
    "                    \"client-class\": \"a-devices\""
    "                },"
    "                {"
    "                    \"pool\": \"192.0.2.100 - 192.0.2.100\","
    "                    \"client-class\": \"b-devices\""
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}",

// Configuration #20
// - a shared network with two subnets
// - first subnet has a dynamic address pool
// - second subnet has no address pool but it has a host reservation
    "{"
    "    \"interfaces-config\": {"
    "        \"interfaces\": [ \"*\" ]"
    "    },"
    "    \"valid-lifetime\": 600,"
    "    \"shared-networks\": ["
    "        {"
    "            \"name\": \"frog\","
    "            \"relay\": {"
    "                \"ip-address\": \"192.3.5.6\""
    "            },"
    "            \"subnet4\": ["
    "                {"
    "                    \"subnet\": \"10.0.0.0/24\","
    "                    \"id\": 100,"
    "                    \"pools\": ["
    "                        {"
    "                            \"pool\": \"10.0.0.1 - 10.0.0.1\""
    "                        }"
    "                    ]"
    "                },"
    "                {"
    "                    \"subnet\": \"192.0.2.0/26\","
    "                    \"id\": 10,"
    "                    \"reservations\": ["
    "                        {"
    "                            \"circuit-id\": \"'charter950'\","
    "                            \"ip-address\": \"192.0.2.28\""
    "                        }"
    "                    ]"
    "                }"
    "            ]"
    "        }"
    "    ]"
    "}"
};

/// @Brief Test fixture class for DHCPv4 server using shared networks.
class Dhcpv4SharedNetworkTest : public Dhcpv4SrvTest {
public:

    /// @brief Constructor.
    Dhcpv4SharedNetworkTest()
        : Dhcpv4SrvTest(),
          iface_mgr_test_config_(true) {
        StatsMgr::instance().removeAll();
    }

    /// @brief Specifies authoritative flag value
    ///
    /// Used to generate authoritative configs
    typedef enum AuthoritativeFlag {
        AUTH_DEFAULT, // explicit value not specified (use default)
        AUTH_YES,     // defined explicitly as yes
        AUTH_NO       // defined explicitly as no
    } AuthoritativeFlag;

    /// @brief Returns subnet having specified address in range.
    ///
    /// @param address Address for which subnet is being searched.
    /// @return Pointer to the subnet having an address in range or null pointer
    /// if no subnet found.
    Subnet4Ptr getConfiguredSubnet(const IOAddress& address) {
        CfgSubnets4Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
        const Subnet4Collection* subnets = cfg->getAll();
        for (auto subnet_it = subnets->cbegin(); subnet_it != subnets->cend();
             ++subnet_it) {
            if ((*subnet_it)->inRange(address)) {
                return (*subnet_it);
            }
        }
        return (Subnet4Ptr());
    }

    /// @brief Perform DORA exchange and checks the result
    ///
    /// This convenience method conducts DORA exchange with client
    /// packets using hint values specified by third parameter.
    /// The response is expected to be either ACK (ack = true) or
    /// NAK (ack = false). The received address is checked against
    /// exp_addr
    ///
    /// @param client client to perform the DORA exchange
    /// @param exp_addr expected address (in yiaddr field)
    /// @param hint the address the client is supposed to sent
    ///             (empty string means send 0.0.0.0)
    /// @param ack expected response (true = ACK, false = NAK)
    void
    doDORA(Dhcp4Client& client, std::string exp_addr, std::string hint = "",
           bool ack = true) {

        if (hint.empty()) {
            ASSERT_NO_THROW(client.doDORA());
        } else {
            boost::shared_ptr<IOAddress> addr(new IOAddress(hint));
            ASSERT_NO_THROW(client.doDORA(addr));
        }
        Pkt4Ptr resp = client.getContext().response_;
        ASSERT_TRUE(resp);
        EXPECT_EQ((ack ? DHCPACK : DHCPNAK), resp->getType());
        if (ack) {
            EXPECT_EQ(exp_addr, resp->getYiaddr().toText());
            Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(IOAddress(resp->getYiaddr()));
            ASSERT_TRUE(lease);
            // Make sure that the subnet id in the lease database is not messed up.
            Subnet4Ptr subnet = getConfiguredSubnet(resp->getYiaddr());
            ASSERT_TRUE(subnet);
            ASSERT_EQ(subnet->getID(), lease->subnet_id_);

        } else {
            EXPECT_EQ("0.0.0.0", resp->getYiaddr().toText());
        }
    }

    /// @brief Perform Discover/Offer exchange and checks the result
    ///
    /// This convenience method conducts Discover/Offer exchange with client
    /// packets using hint values specified by third parameter.
    /// The response is expected to be either ACK (ack = true) or
    /// NAK (ack = false). The received address is checked against
    /// exp_addr
    ///
    /// @param client client to perform the DORA exchange
    /// @param exp_addr expected address (in yiaddr field)
    /// @param hint the address the client is supposed to sent
    ///             (empty string means send 0.0.0.0)
    /// @param ack expected response (true = ACK, false = NAK)
    void
    doDiscover(Dhcp4Client& client, std::string exp_addr, std::string hint,
           bool ack = true) {

        if (hint.empty()) {
            ASSERT_NO_THROW(client.doDiscover());
        } else {
            boost::shared_ptr<IOAddress> addr(new IOAddress(hint));
            ASSERT_NO_THROW(client.doDiscover(addr));
        }
        Pkt4Ptr resp = client.getContext().response_;
        ASSERT_TRUE(resp);
        EXPECT_EQ((ack ? DHCPOFFER : DHCPNAK), resp->getType());
        if (ack) {
            EXPECT_EQ(exp_addr, resp->getYiaddr().toText());
        } else {
            EXPECT_EQ("0.0.0.0", resp->getYiaddr().toText());
        }
    }

    /// @brief Perform Request/Reply exchange and checks the result
    ///
    /// This convenience method conducts Request/Reply exchange with client
    /// packets using hint values specified by a parameter.  The response is
    /// expected to be either ACK if exp_addr has a non-empty length,
    /// or NAK when exp_addr context is empty.
    ///
    /// @param client client to perform the DORA exchange
    /// @param exp_addr expected address (in yiaddr field)
    void
    doRequest(Dhcp4Client& client, std::string exp_addr) {
        ASSERT_NO_THROW(client.doRequest());
        Pkt4Ptr resp = client.getContext().response_;
        ASSERT_TRUE(resp);
        if (exp_addr.empty()) {
            EXPECT_EQ(DHCPNAK, resp->getType());
            EXPECT_EQ("0.0.0.0", resp->getYiaddr().toText());
        } else {
            EXPECT_EQ(DHCPACK, resp->getType());
            EXPECT_EQ(exp_addr, resp->getYiaddr().toText());
            Lease4Ptr lease = LeaseMgrFactory::instance().getLease4(IOAddress(resp->getYiaddr()));
            ASSERT_TRUE(lease);
            // Make sure that the subnet id in the lease database is not messed up.
            Subnet4Ptr subnet = getConfiguredSubnet(resp->getYiaddr());
            ASSERT_TRUE(subnet);
            ASSERT_EQ(subnet->getID(), lease->subnet_id_);
        }
    }

    /// @brief Verifies lease statistics against values held by StatsMgr.
    ///
    /// This method retrieves lease statistics from the database and then compares it
    /// against values held by the StatsMgr. The compared statistics are number of
    /// assigned addresses and prefixes for a subnet.
    void verifyAssignedStats() {
        LeaseStatsQueryPtr query = LeaseMgrFactory::instance().startLeaseStatsQuery4();
        LeaseStatsRow row;
        while (query->getNextRow(row)) {
            // Only check valid leases.
            if (row.lease_state_ == Lease::STATE_DEFAULT) {
                ASSERT_EQ(row.state_count_, getStatsAssignedAddresses(row.subnet_id_))
                    << "test failed for subnet id " << row.subnet_id_;
            }
        }
    }

    /// @brief Retrieves subnet[id].assigned-addresses statistics for a subnet.
    ///
    /// @param subnet_id Identifier of a subnet for which statistics should be
    /// retrieved.
    /// @return Number of assigned addresses for a subnet.
    int64_t getStatsAssignedAddresses(const SubnetID& subnet_id) const {
        // Retrieve statistics name, e.g. subnet[1234].assigned-addresses.
        const std::string stats_name = StatsMgr::generateName("subnet", subnet_id, "assigned-addresses");
        // Top element is a map with a subnet[id].assigned-addresses parameter.
        ConstElementPtr top_element = StatsMgr::instance().get(stats_name);
        if (top_element && (top_element->getType() == Element::map)) {
            // It contains two lists (nested).
            ConstElementPtr first_list = top_element->get(stats_name);
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

    /// @brief Check precedence.
    ///
    /// @param config the configuration.
    /// @param ns_address expected name server address.
    void testPrecedence(const std::string& config, const std::string& ns_address) {
        // Create client and set MAC address to the one that has a reservation.
        Dhcp4Client client(Dhcp4Client::SELECTING);
        client.setIfaceName("eth1");
        client.setIfaceIndex(ETH1_INDEX);
        client.setHWAddress("aa:bb:cc:dd:ee:ff");
        // Request domain-name-servers.
        client.requestOptions(DHO_DOMAIN_NAME_SERVERS);

        // Create server configuration.
        configure(config, *client.getServer());

        // Perform a DORA.
        doDORA(client, "192.0.2.28", "192.0.2.28");

        // Check response.
        Pkt4Ptr resp = client.getContext().response_;
        ASSERT_TRUE(resp);
        EXPECT_EQ(DHCPACK, resp->getType());
        EXPECT_EQ("192.0.2.28", resp->getYiaddr().toText());

        // Check domain-name-servers option.
        OptionPtr opt = resp->getOption(DHO_DOMAIN_NAME_SERVERS);
        ASSERT_TRUE(opt);
        Option4AddrLstPtr servers =
            boost::dynamic_pointer_cast<Option4AddrLst>(opt);
        ASSERT_TRUE(servers);
        auto addrs = servers->getAddresses();
        ASSERT_EQ(1, addrs.size());
        EXPECT_EQ(ns_address, addrs[0].toText());
    }

    /// @brief returns authoritative flag as JSON string
    /// @param f value to be specified (default, true or false)
    string auth(AuthoritativeFlag f) {
        switch (f) {
        case AUTH_DEFAULT:
            return ("");
        case AUTH_YES:
            return ("            \"authoritative\": true,");
            break;
        case AUTH_NO:
            return ("            \"authoritative\": false,");
        }
        return ("");
    }

    /// @brief generates Config file with specified authoritative flag values
    ///
    /// The config file has the same structure:
    /// - 1 shared network with 2 subnets (global authoritative flag)
    ///   - first subnet: authoritative (subnet1 flag here)
    ///   - second subnet: authoritative (subnet2 flag here)
    ///
    /// @param global governs presence/value of global authoritative flag
    /// @param subnet1 governs presence/value of authoritative flag in subnet1
    /// @param subnet2 governs presence/value of authoritative flag in subnet2
    string generateAuthConfig(AuthoritativeFlag global, AuthoritativeFlag subnet1,
                              AuthoritativeFlag subnet2) {
        string cfg = "{"
            "    \"interfaces-config\": {"
            "        \"interfaces\": [ \"*\" ]"
            "    },"
            "    \"valid-lifetime\": 600,"
            "    \"shared-networks\": ["
            "        {"
            "            \"name\": \"frog\","
            "            \"comment\": \"example\",";
        cfg += auth(global);
        cfg +=
            "            \"subnet4\": ["
            "                {"
            "                    \"subnet\": \"192.0.2.0/26\","
            "                    \"id\": 10,";
        cfg += auth(subnet1);

        cfg +=
            "                    \"pools\": ["
            "                        {"
            "                            \"pool\": \"192.0.2.63 - 192.0.2.63\""
            "                        }"
            "                    ]"
            "                },"
            "                {"
            "                    \"subnet\": \"10.0.0.0/24\","
            "                    \"id\": 100,";
        cfg += auth(subnet2);
        cfg +=
            "                    \"pools\": ["
            "                        {"
            "                            \"pool\": \"10.0.0.16 - 10.0.0.16\""
            "                        }"
            "                    ]"
            "                }"
            "            ]"
            "        }"
            "    ]"
            "}";

        return (cfg);
    }

    /// @brief Destructor.
    virtual ~Dhcpv4SharedNetworkTest() {
        StatsMgr::instance().removeAll();
    }

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;
};

// Check user-context parsing
TEST_F(Dhcpv4SharedNetworkTest, parse) {
    // Create client
    Dhcp4Client client1(Dhcp4Client::SELECTING);

    // Don't use configure from utils
    Parser4Context ctx;
    ConstElementPtr json;
    ASSERT_NO_THROW(json = parseDHCP4(NETWORKS_CONFIG[0], true));
    ConstElementPtr status;
    disableIfacesReDetect(json);
    EXPECT_NO_THROW(status = configureDhcp4Server(*client1.getServer(), json));
    ASSERT_TRUE(status);
    int rcode;
    ConstElementPtr comment = config::parseAnswer(rcode, status);
    ASSERT_EQ(0, rcode) << " comment: " << comment->stringValue();
    ASSERT_NO_THROW( {
        CfgDbAccessPtr cfg_db = CfgMgr::instance().getStagingCfg()->getCfgDbAccess();
        cfg_db->setAppendedParameters("universe=4");
        cfg_db->createManagers();
    } );
    CfgMgr::instance().commit();

    CfgSharedNetworks4Ptr cfg = CfgMgr::instance().getCurrentCfg()->getCfgSharedNetworks4();
    SharedNetwork4Ptr network = cfg->getByName("frog");
    ConstElementPtr context = network->getContext();
    ASSERT_TRUE(context);
    ASSERT_EQ(1, context->size());
    ASSERT_TRUE(context->get("comment"));
    EXPECT_EQ("\"example\"", context->get("comment")->str());
}

// Running out of addresses within a subnet in a shared network.
TEST_F(Dhcpv4SharedNetworkTest, poolInSharedNetworkShortage) {
    // Create client #1
    Dhcp4Client client1(Dhcp4Client::SELECTING);
    client1.setIfaceName("eth1");
    client1.setIfaceIndex(ETH1_INDEX);

    // Configure the server with one shared network including two subnets and
    // one subnet outside of the shared network.
    configure(NETWORKS_CONFIG[0], *client1.getServer());

    // Client #1 requests an address in first subnet within a shared network.
    // We'll send a hint of 192.0.2.63 and expect to get it.
    testAssigned([this, &client1]() {
        doDORA(client1, "192.0.2.63", "192.0.2.63");
    });

    // Client #2 The second client will request a lease and should be assigned
    // an address from the second subnet.
    Dhcp4Client client2(client1.getServer(), Dhcp4Client::SELECTING);
    client2.setIfaceName("eth1");
    client2.setIfaceIndex(ETH1_INDEX);
    testAssigned([this, &client2]() {
        doDORA(client2, "10.0.0.16");
    });

    // Client #3. It sends DHCPDISCOVER which should be dropped by the server because
    // the server has no more addresses to assign.
    Dhcp4Client client3(client1.getServer(), Dhcp4Client::SELECTING);
    client3.setIfaceName("eth1");
    client3.setIfaceIndex(ETH1_INDEX);
    testAssigned([&client3]() {
        ASSERT_NO_THROW(client3.doDiscover());
        Pkt4Ptr resp3 = client3.getContext().response_;
        ASSERT_FALSE(resp3);
    });

    // Client #3 should be assigned an address if subnet 3 is selected for this client.
    client3.setIfaceName("eth0");
    client3.setIfaceIndex(ETH0_INDEX);
    testAssigned([this, &client3]() {
        doDORA(client3, "192.0.2.65");
    });

    // Client #1 should be able to renew its address.
    client1.setState(Dhcp4Client::RENEWING);
    testAssigned([this, &client1]() {
        doRequest(client1, "192.0.2.63");
    });

    // Client #2 should be able to renew its address.
    client2.setState(Dhcp4Client::RENEWING);
    testAssigned([this, &client2]() {
        doRequest(client2, "10.0.0.16");
    });
}

// Returning client sends 4-way exchange.
TEST_F(Dhcpv4SharedNetworkTest, returningClientStartsOver) {
    // Create client.
    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.setIfaceName("eth1");
    client.setIfaceIndex(ETH1_INDEX);
    client.includeClientId("01:02:03:04");

    // Configure the server with one shared network including two subnets and
    // one subnet outside of the shared network.
    configure(NETWORKS_CONFIG[0], *client.getServer());

    // Client requests an address in first subnet within a shared network.
    // We'll send a hint of 192.0.2.63 and expect to get it.
    testAssigned([this, &client]() {
        doDORA(client, "192.0.2.63", "192.0.2.63");
    });


    // The client reboots and performs 4-way exchange again without a hint.
    // It should be assigned the same (existing) lease.
    testAssigned([this, &client]() {
        doDORA(client, "192.0.2.63");
    });
}

// Shared network is selected based on giaddr value (relay specified
// on shared network level)
TEST_F(Dhcpv4SharedNetworkTest, sharedNetworkSelectedByRelay1) {
    // Create client #1. This is a relayed client which is using relay
    // address matching configured shared network.
    Dhcp4Client client1(Dhcp4Client::SELECTING);
    client1.useRelay(true, IOAddress("192.3.5.6"), IOAddress("10.0.0.2"));

    // Configure the server with one shared network and one subnet outside of the
    // shared network.
    configure(NETWORKS_CONFIG[1], *client1.getServer());

    // Client #1 should be assigned an address from shared network.
    testAssigned([this, &client1] {
        doDORA(client1, "192.0.2.63", "192.0.2.63");
    });

    // Create client #2. This is a relayed client which is using relay
    // address matching subnet outside of the shared network.
    Dhcp4Client client2(client1.getServer(), Dhcp4Client::SELECTING);
    client2.useRelay(true, IOAddress("192.1.2.3"), IOAddress("10.0.0.3"));
    testAssigned([this, &client2] {
        doDORA(client2, "192.0.2.65", "192.0.2.63");
    });
}

// Shared network is selected based on giaddr value (relay specified
// on subnet in shared network level). Note the relay ip is specified
// on the shared network level, but its value is overridden on subnet
// level.
TEST_F(Dhcpv4SharedNetworkTest, sharedNetworkSelectedByRelay2) {
    // Create client #1. This is a relayed client which is using relay
    // address matching configured subnet 1 in shared network.
    Dhcp4Client client1(Dhcp4Client::SELECTING);
    client1.useRelay(true, IOAddress("192.1.1.1"), IOAddress("10.0.0.2"));

    // Configure the server with one shared network and one subnet outside of the
    // shared network.
    configure(NETWORKS_CONFIG[14], *client1.getServer());

    // Client #1 should be assigned an address from shared network.
    testAssigned([this, &client1] {
        doDORA(client1, "192.0.2.63");
    });

    // Create client #2. This is a relayed client which is using relay
    // address that is used for subnet 2 in the shared network.
    Dhcp4Client client2(client1.getServer(), Dhcp4Client::SELECTING);
    client2.useRelay(true, IOAddress("192.2.2.2"), IOAddress("10.0.0.3"));
    testAssigned([this, &client2] {
        doDORA(client2, "10.0.0.16");
    });

    // Create client #3. This is a relayed client which is using relay
    // address matching subnet outside of the shared network.
    Dhcp4Client client3(client1.getServer(), Dhcp4Client::SELECTING);
    client3.useRelay(true, IOAddress("192.3.3.3"), IOAddress("10.0.0.4"));
    testAssigned([this, &client3] {
        doDORA(client3, "192.0.2.65");
    });
}

// Providing a hint for any address belonging to a shared network.
TEST_F(Dhcpv4SharedNetworkTest, hintWithinSharedNetwork) {
    // Create client.
    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.setIfaceName("eth1");
    client.setIfaceIndex(ETH1_INDEX);

    // Configure the server with one shared network including two subnets and
    // one subnet outside of the shared network.
    configure(NETWORKS_CONFIG[0], *client.getServer());

    // Provide a hint to an existing address within first subnet. This address
    // should be offered out of this subnet.
    testAssigned([this, &client] {
        doDiscover(client, "192.0.2.63", "192.0.2.63");
    });

    // Similarly, we should be offered an address from another subnet within
    // the same shared network when we ask for it.
    testAssigned([this, &client] {
        doDiscover(client, "10.0.0.16", "10.0.0.16");
    });

    // Asking for an address that is not in address pool should result in getting
    // an address from one of the subnets, but generally hard to tell from which one.
    testAssigned([&client] {
        ASSERT_NO_THROW(client.doDiscover(boost::shared_ptr<IOAddress>(new IOAddress("10.0.0.23"))));
    });

    Pkt4Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);

    // We expect one of the two addresses available in this shared network.
    EXPECT_EQ(DHCPOFFER, resp->getType());
    if ((resp->getYiaddr() != IOAddress("10.0.0.16")) &&
        (resp->getYiaddr() != IOAddress("192.0.2.63"))) {
        ADD_FAILURE() << "Unexpected address offered by the server " << resp->getYiaddr();
    }
}

// Access to a subnet within shared network is restricted by client
// classification.
TEST_F(Dhcpv4SharedNetworkTest, subnetInSharedNetworkSelectedByClass) {
    // Create client #1
    Dhcp4Client client1(Dhcp4Client::SELECTING);
    client1.useRelay(true, IOAddress("192.3.5.6"));

    // Configure the server with one shared network including two subnets in
    // it. The access to one of the subnets is restricted by client classification.
    configure(NETWORKS_CONFIG[2], *client1.getServer());

    // Client #1 requests an address in the restricted subnet but can't be assigned
    // this address because the client doesn't belong to a certain class.
    testAssigned([this, &client1] {
        doDORA(client1, "10.0.0.16", "192.0.2.63");
    });

    // Release the lease that the client has got, because we'll need this address
    // further in the test.
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doRelease());
    });

    // Add option93 which would cause the client to be classified as "a-devices".
    OptionPtr option93(new OptionUint16(Option::V4, 93, 0x0001));
    client1.addExtraOption(option93);

    // This time, the allocation of the address provided as hint should be successful.
    testAssigned([this, &client1] {
        doDORA(client1, "192.0.2.63", "192.0.2.63");
    });

    // Client 2 should be assigned an address from the unrestricted subnet.
    Dhcp4Client client2(client1.getServer(), Dhcp4Client::SELECTING);
    client2.useRelay(true, IOAddress("192.3.5.6"));
    client2.setIfaceName("eth1");
    client2.setIfaceIndex(ETH1_INDEX);
    testAssigned([this, &client2] {
        doDORA(client2, "10.0.0.16");
    });

    // Now, let's reconfigure the server to also apply restrictions on the
    // subnet to which client2 now belongs.
    configure(NETWORKS_CONFIG[3], *client1.getServer());

    // The client should be refused to renew the lease because it doesn't belong
    // to "b-devices" class.
    client2.setState(Dhcp4Client::RENEWING);
    testAssigned([this, &client2] {
        doRequest(client2, "");
    });

    // If we add option93 with a value matching this class, the lease should
    // get renewed.
    OptionPtr option93_bis(new OptionUint16(Option::V4, 93, 0x0002));
    client2.addExtraOption(option93_bis);

    testAssigned([this, &client2] {
        doRequest(client2, "10.0.0.16");
    });
}

// IPv4 address reservation exists in one of the subnets within
// shared network. This test also verifies that conflict resolution for
// reserved addresses is working properly in case of shared networks.
TEST_F(Dhcpv4SharedNetworkTest, reservationInSharedNetwork) {
    // Create client #1. Explicitly set client's MAC address to the one that
    // has a reservation in the first subnet within shared network.
    Dhcp4Client client1(Dhcp4Client::SELECTING);
    client1.useRelay(true, IOAddress("192.3.5.6"));
    client1.setHWAddress("11:22:33:44:55:66");

    // Create server configuration with a shared network including two subnets. There
    // is an IP address reservation in each subnet for two respective clients.
    configure(NETWORKS_CONFIG[4], *client1.getServer());

    // Client #1 should get his reserved address from the second subnet.
    testAssigned([this, &client1] {
        doDORA(client1, "10.0.0.29", "192.0.2.28");
    });

    // Create client #2
    Dhcp4Client client2(client1.getServer(), Dhcp4Client::SELECTING);
    client2.useRelay(true, IOAddress("192.3.5.6"));
    client2.setHWAddress("aa:bb:cc:dd:ee:ff");

    // Client #2 should get its reserved address from the first subnet.
    testAssigned([this, &client2] {
        doDORA(client2, "192.0.2.28");
    });

    // Reconfigure the server. Now, the first client gets second client's
    // reservation and vice versa.
    configure(NETWORKS_CONFIG[5], *client1.getServer());

    // The first client is trying to renew the lease and should get a DHCPNAK.
    client1.setState(Dhcp4Client::RENEWING);
    testAssigned([this, &client1] {
        doRequest(client1, "");
    });

    // Similarly, the second client is trying to renew the lease and should
    // get a DHCPNAK.
    client2.setState(Dhcp4Client::RENEWING);
    testAssigned([this, &client2] {
        doRequest(client2, "");
    });

    // But the client should get a lease, if it does 4-way exchange. However, it
    // must not get any of the reserved addresses because one of them is reserved
    // for another client and for another one there is a valid lease.
    client1.setState(Dhcp4Client::SELECTING);
    testAssigned([this, &client1] {
        ASSERT_NO_THROW(doDORA(client1, "192.0.2.29", "192.0.2.29"));
    });
    Pkt4Ptr resp1 = client1.getContext().response_;
    ASSERT_TRUE(resp1);
    EXPECT_EQ(DHCPACK, resp1->getType());
    EXPECT_NE("10.0.0.29", resp1->getYiaddr().toText());
    EXPECT_NE("192.0.2.28", resp1->getYiaddr().toText());
    // Ensure stats are being recorded for HR conflicts
    ObservationPtr subnet_conflicts = StatsMgr::instance().getObservation(
        "subnet[10].v4-reservation-conflicts");
    ASSERT_TRUE(subnet_conflicts);
    ASSERT_EQ(1, subnet_conflicts->getInteger().first);
    subnet_conflicts = StatsMgr::instance().getObservation("v4-reservation-conflicts");
    ASSERT_TRUE(subnet_conflicts);
    ASSERT_EQ(1, subnet_conflicts->getInteger().first);

    // Client #2 is now doing 4-way exchange and should get its newly reserved
    // address, released by the 4-way transaction of client 1.
    client2.setState(Dhcp4Client::SELECTING);
    testAssigned([this, &client2] {
        doDORA(client2, "10.0.0.29");
    });

    // Same for client #1.
    client1.setState(Dhcp4Client::SELECTING);
    testAssigned([this, &client1] {
        doDORA(client1, "192.0.2.28");
    });
}

// Two clients use the same circuit ID and this circuit ID is used to assign a
// host reservation. The clients compete for the reservation, and one of them
// gets it and the other one gets an address from the dynamic pool. This test
// checks that the assigned leases have appropriate subnet IDs. Previously, the
// client getting the lease from the dynamic pool had a wrong subnet ID (not
// matching the address from the dynamic pool).
TEST_F(Dhcpv4SharedNetworkTest, reservationInSharedNetworkTwoClientsSameIdentifier) {
    // Create client #1 which uses a circuit ID as a host identifier.
    Dhcp4Client client1(Dhcp4Client::SELECTING);
    client1.useRelay(true, IOAddress("192.3.5.6"));
    client1.includeClientId("01:02:03:04");
    client1.setCircuitId("charter950");

    // Create server configuration with a shared network including two subnets.
    // One of the subnets includes a reservation identified by the client's
    // circuit ID.
    configure(NETWORKS_CONFIG[20], *client1.getServer());

    // Client #1 should get the reserved address.
    testAssigned([this, &client1] {
        doDORA(client1, "192.0.2.28", "");
    });

    // Create client #2 with the same circuit ID.
    Dhcp4Client client2(client1.getServer(), Dhcp4Client::SELECTING);
    client2.useRelay(true, IOAddress("192.3.5.6"));
    client2.includeClientId("02:03:04:05");
    client2.setCircuitId("charter950");

    // Client #2 presents the same circuit ID but the reserved address has been
    // already allocated. The client should get an address from the dynamic pool.
    testAssigned([this, &client2] {
        doDORA(client2, "10.0.0.1", "192.0.2.28");
    });

    // Client #1 renews the lease.
    client1.setState(Dhcp4Client::RENEWING);
    testAssigned([this, &client1]() {
        doRequest(client1, "192.0.2.28");
    });

    // Client #2 renews the lease.
    client2.setState(Dhcp4Client::RENEWING);
    // Check if the client successfully renewed its address and that the
    // subnet id in the renewed lease is not messed up.
    testAssigned([this, &client2]() {
        doRequest(client2, "10.0.0.1");
    });

    // Ensure stats are being recorded for HR conflicts
    ObservationPtr subnet_conflicts = StatsMgr::instance().getObservation(
        "subnet[10].v4-reservation-conflicts");
    ASSERT_TRUE(subnet_conflicts);
    ASSERT_EQ(1, subnet_conflicts->getInteger().first);
    subnet_conflicts = StatsMgr::instance().getObservation("v4-reservation-conflicts");
    ASSERT_TRUE(subnet_conflicts);
    ASSERT_EQ(1, subnet_conflicts->getInteger().first);
}

// Reserved address can't be assigned as long as access to a subnet is
// restricted by classification.
TEST_F(Dhcpv4SharedNetworkTest, reservationAccessRestrictedByClass) {
    // Create a client and set explicit MAC address for which there is a reservation
    // in first subnet belonging to a shared network.
    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.useRelay(true, IOAddress("192.3.5.6"));
    client.setHWAddress("aa:bb:cc:dd:ee:ff");

    // Create configuration with a shared network including two subnets. Access to
    // one of the subnets is restricted by client classification.
    configure(NETWORKS_CONFIG[6], *client.getServer());

    // Assigned address should be allocated from the second subnet, because the
    // client doesn't belong to the "a-devices" class.
    testAssigned([this, &client] {
        doDORA(client, "10.0.0.16");
    });

    // Add option 93 which would cause the client to be classified as "a-devices".
    OptionPtr option93(new OptionUint16(Option::V4, 93, 0x0001));
    client.addExtraOption(option93);

    // Client renews its lease and should get DHCPNAK because this client now belongs
    // to the "a-devices" class and can be assigned a reserved address instead.
    client.setState(Dhcp4Client::RENEWING);
    testAssigned([this, &client] {
        doRequest(client, "");
    });

    // Perform 4-way exchange again. It should be assigned a reserved address this time.
    client.setState(Dhcp4Client::SELECTING);
    testAssigned([this, &client] {
        doDORA(client, "192.0.2.28");
    });
}

// Some options are specified on the shared subnet level, some on the
// subnets level.
TEST_F(Dhcpv4SharedNetworkTest, optionsDerivation) {
    // Client #1.
    Dhcp4Client client1(Dhcp4Client::SELECTING);
    client1.setIfaceName("eth1");
    client1.setIfaceIndex(ETH1_INDEX);
    client1.requestOptions(DHO_LOG_SERVERS, DHO_COOKIE_SERVERS, DHO_DOMAIN_NAME_SERVERS);

    configure(NETWORKS_CONFIG[7], *client1.getServer());

    // Client #1 belongs to shared network. By providing a hint "192.0.2.63" we force
    // the server to select first subnet within the shared network for this client.
    doDORA(client1, "192.0.2.63", "192.0.2.63");

    // This option is specified at the global level.
    ASSERT_EQ(1, client1.config_.log_servers_.size());
    EXPECT_EQ("1.2.3.4", client1.config_.log_servers_[0].toText());

    // This option is specified on the subnet level.
    ASSERT_EQ(1, client1.config_.routers_.size());
    EXPECT_EQ("192.0.2.5", client1.config_.routers_[0].toText());

    // This option is specified on the shared network level and the subnet level.
    // The instance on the subnet level should take precedence.
    ASSERT_EQ(1, client1.config_.quotes_servers_.size());
    EXPECT_EQ("10.5.4.3", client1.config_.quotes_servers_[0].toText());

    // This option is only specified on the shared network level and should be
    // inherited by all subnets within this network.
    ASSERT_EQ(1, client1.config_.dns_servers_.size());
    EXPECT_EQ("10.1.2.3", client1.config_.dns_servers_[0].toText());

    // Client #2.
    Dhcp4Client client2(Dhcp4Client::SELECTING);
    client2.setIfaceName("eth1");
    client2.setIfaceIndex(ETH1_INDEX);
    client2.requestOptions(DHO_LOG_SERVERS, DHO_COOKIE_SERVERS, DHO_DOMAIN_NAME_SERVERS);

    // Request an address from the second subnet within the shared network.
    doDORA(client2, "10.0.0.16", "10.0.0.16");

    // This option is specified at the global level.
    ASSERT_EQ(1, client2.config_.log_servers_.size());
    EXPECT_EQ("1.2.3.4", client2.config_.log_servers_[0].toText());

    // This option is only specified on the shared network level and should be
    // inherited by all subnets within this network.
    ASSERT_EQ(1, client2.config_.quotes_servers_.size());
    EXPECT_EQ("10.6.5.4", client2.config_.quotes_servers_[0].toText());

    // This option is only specified on the shared network level and should be
    // inherited by all subnets within this network.
    ASSERT_EQ(1, client2.config_.dns_servers_.size());
    EXPECT_EQ("10.1.2.3", client2.config_.dns_servers_[0].toText());

    // Client #3.
    Dhcp4Client client3(Dhcp4Client::SELECTING);
    client3.setIfaceName("eth0");
    client3.setIfaceIndex(ETH0_INDEX);
    client3.requestOptions(DHO_LOG_SERVERS, DHO_COOKIE_SERVERS, DHO_DOMAIN_NAME_SERVERS);

    // Client 3 should get an address from the subnet defined outside of the shared network.
    doDORA(client3, "192.0.2.65");

    // This option is specified at the global level.
    ASSERT_EQ(1, client3.config_.log_servers_.size());
    EXPECT_EQ("1.2.3.4", client3.config_.log_servers_[0].toText());

    // This option is specified on the subnet level.
    ASSERT_EQ(1, client3.config_.quotes_servers_.size());
    EXPECT_EQ("10.1.1.1", client3.config_.quotes_servers_[0].toText());

    // This option is only specified on the shared network level and thus it should
    // not be returned to this client, because the client doesn't belong to the
    // shared network.
    ASSERT_EQ(0, client3.config_.dns_servers_.size());
}

// Client has a lease in a subnet within shared network.
TEST_F(Dhcpv4SharedNetworkTest, initReboot) {
    // Create client #1.
    Dhcp4Client client1(Dhcp4Client::SELECTING);
    client1.setIfaceName("eth1");
    client1.setIfaceIndex(ETH1_INDEX);

    configure(NETWORKS_CONFIG[0], *client1.getServer());

    // Perform 4-way exchange to obtain a lease. The client should get the lease from
    // the second subnet.
    testAssigned([this, &client1] {
        doDORA(client1, "10.0.0.16", "10.0.0.16");
    });

    // The client1 transitions to INIT-REBOOT state in which the client1 remembers the
    // lease and sends DHCPREQUEST to all servers (server id) is not specified. If
    // the server doesn't know the client1 (doesn't have its lease), it should
    // drop the request. We want to make sure that the server responds (resp1) regardless
    // of the subnet from which the lease has been allocated.
    client1.setState(Dhcp4Client::INIT_REBOOT);
    testAssigned([this, &client1] {
        doRequest(client1, "10.0.0.16");
    });

    // Create client #2.
    Dhcp4Client client2(client1.getServer(), Dhcp4Client::SELECTING);
    client2.setIfaceName("eth1");
    client2.setIfaceIndex(ETH1_INDEX);

    // Let's make sure that the behavior is the same for the other subnet within the
    // same shared network.
    testAssigned([this, &client2] {
        doDORA(client2, "192.0.2.63", "192.0.2.63");
    });

    // The client2 transitions to INIT-REBOOT state in which the client2 remembers the
    // lease and sends DHCPREQUEST to all servers (server id) is not specified. If
    // the server doesn't know the client2 (doesn't have its lease), it should
    // drop the request. We want to make sure that the server responds (resp2) regardless
    // of the subnet from which the lease has been allocated.
    client2.setState(Dhcp4Client::INIT_REBOOT);
    testAssigned([this, &client2] {
        doRequest(client2, "192.0.2.63");
    });
}

// Host reservations include hostname, next server and client class.
TEST_F(Dhcpv4SharedNetworkTest, variousFieldsInReservation) {
    // Create client.
    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.setIfaceName("eth1");
    client.setIfaceIndex(ETH1_INDEX);
    client.setHWAddress("11:22:33:44:55:66");

    // Include hostname to force the server to return hostname to
    // the client.
    client.includeHostname("my.example.org");

    // Configure the server with a shared network including two subnets.
    // The client has address/hostname reservation in the second subnet.
    configure(NETWORKS_CONFIG[10], *client.getServer());

    // Perform 4-way exchange.
    testAssigned([&client] {
        ASSERT_NO_THROW(client.doDORA());
    });
    Pkt4Ptr resp = client.getContext().response_;
    ASSERT_TRUE(resp);
    EXPECT_EQ(DHCPACK, resp->getType());
    EXPECT_EQ("10.0.0.29", resp->getYiaddr().toText());

    // The client should get a hostname from the reservation, rather than
    // the hostname it has sent to the server. If there is a logic error,
    // the server would use the first subnet from the shared network to
    // assign the hostname. This subnet has no reservation so it would
    // return the same hostname that the client has sent. We expect
    // that the hostname being sent is the one that is incldued in the
    // reservations.
    OptionStringPtr hostname;
    hostname = boost::dynamic_pointer_cast<OptionString>(resp->getOption(DHO_HOST_NAME));
    ASSERT_TRUE(hostname);
    EXPECT_EQ("test.example.org", hostname->getValue());

    // The next server value should also be set according to the settings
    // in host reservations.
    EXPECT_EQ("10.10.10.10", resp->getSiaddr().toText());

    // The boot-file-name value should be derived from the client class
    // based on the static class reservations.
    const std::string expected_fname = "/dev/null";
    const OptionBuffer fname = resp->getFile();
    const std::string converted_fname(fname.cbegin(),
                                      fname.cbegin() + expected_fname.size());
    EXPECT_EQ(expected_fname, converted_fname);
}

// Different shared network is selected for different local interface.
TEST_F(Dhcpv4SharedNetworkTest, sharedNetworkSelectionByInterface) {
    // Create client #1. The server receives requests from this client
    // via interface eth1 and should assign shared network "frog" for
    // this client.
    Dhcp4Client client1(Dhcp4Client::SELECTING);
    client1.setIfaceName("eth1");
    client1.setIfaceIndex(ETH1_INDEX);

    // Create server configuration with two shared networks selected
    // by the local interface: eth1 and eth0.
    configure(NETWORKS_CONFIG[8], *client1.getServer());

    // Perform 4-way exchange.
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doDORA());
    });
    Pkt4Ptr resp1 = client1.getContext().response_;
    ASSERT_TRUE(resp1);
    EXPECT_EQ(DHCPACK, resp1->getType());
    // The client should be assigned an address from the 192.0.2.X
    // address range.
    EXPECT_EQ("192.0.2", resp1->getYiaddr().toText().substr(0, 7));

    // Create client #2 which requests are received on eth0.
    Dhcp4Client client2(client1.getServer(), Dhcp4Client::SELECTING);
    client2.setIfaceName("eth0");
    client2.setIfaceIndex(ETH0_INDEX);

    // Perform 4-way exchange.
    testAssigned([&client2] {
        ASSERT_NO_THROW(client2.doDORA());
    });
    Pkt4Ptr resp2 = client2.getContext().response_;
    ASSERT_TRUE(resp2);
    EXPECT_EQ(DHCPACK, resp2->getType());
    // The client should be assigned an address from the 10.0.0.X
    // address range.
    EXPECT_EQ("10.0.0", resp2->getYiaddr().toText().substr(0, 6));
}

// Different shared network is selected for different relay address.
TEST_F(Dhcpv4SharedNetworkTest, sharedNetworkSelectionByRelay) {
    // Create relayed client #1.
    Dhcp4Client client1(Dhcp4Client::SELECTING);
    client1.useRelay(true, IOAddress("10.1.2.3"));

    // Create server configuration with two shared networks selected
    // by the relay address.
    configure(NETWORKS_CONFIG[9], *client1.getServer());

    // Perform 4-way exchange.
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doDORA());
    });
    Pkt4Ptr resp1 = client1.getContext().response_;
    ASSERT_TRUE(resp1);
    EXPECT_EQ(DHCPACK, resp1->getType());
    // The client should be assigned an address from the 192.0.2.X
    // address range.
    EXPECT_EQ("192.0.2", resp1->getYiaddr().toText().substr(0, 7));

    // Create relayed client #2.
    Dhcp4Client client2(client1.getServer(), Dhcp4Client::SELECTING);
    client2.useRelay(true, IOAddress("192.1.2.3"));

    // Perform 4-way exchange.
    testAssigned([&client2] {
        ASSERT_NO_THROW(client2.doDORA());
    });
    Pkt4Ptr resp2 = client2.getContext().response_;
    ASSERT_TRUE(resp2);
    EXPECT_EQ(DHCPACK, resp2->getType());
    // The client should be assigned an address from the 10.0.0.X
    // address range.
    EXPECT_EQ("10.0.0", resp2->getYiaddr().toText().substr(0, 6));
}

// Client id matching gets disabled on the shared network level.
TEST_F(Dhcpv4SharedNetworkTest, matchClientId) {
    // Create client using client identifier besides MAC address.
    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.includeClientId("01:02:03:04");
    client.setIfaceName("eth1");
    client.setIfaceIndex(ETH1_INDEX);

    // Create server configuration with match-client-id value initially
    // set to true. The client should be allocated a lease and the
    // client identifier should be included in this lease.
    configure(NETWORKS_CONFIG[11], *client.getServer());

    // Perform 4-way exchange.
    testAssigned([&client] {
        ASSERT_NO_THROW(client.doDORA());
    });
    Pkt4Ptr resp1 = client.getContext().response_;
    ASSERT_TRUE(resp1);
    ASSERT_EQ(DHCPACK, resp1->getType());

    // Reconfigure the server and turn off client identifier matching
    // on the shared network level. The subnet from which the client
    // is allocated an address should derive the match-client-id value
    // and ignore the fact that the client identifier is not matching.
    configure(NETWORKS_CONFIG[12], *client.getServer());

    client.includeClientId("01:01:01:01");
    client.setState(Dhcp4Client::RENEWING);

    // Try to renew the lease with modified MAC address.
    testAssigned([&client] {
        ASSERT_NO_THROW(client.doRequest());
    });
    Pkt4Ptr resp2 = client.getContext().response_;
    ASSERT_TRUE(resp2);
    ASSERT_EQ(DHCPACK, resp2->getType());

    // The lease should get renewed.
    EXPECT_EQ(resp2->getYiaddr().toText(), resp1->getYiaddr().toText());
}

// Shared network is selected based on the client class specified.
TEST_F(Dhcpv4SharedNetworkTest, sharedNetworkSelectedByClass) {
   // Create client #1.
    Dhcp4Client client1(Dhcp4Client::SELECTING);
    client1.setIfaceName("eth1");
    client1.setIfaceIndex(ETH1_INDEX);

    // Add option93 which would cause the client1 to be classified as "b-devices".
    OptionPtr option93(new OptionUint16(Option::V4, 93, 0x0002));
    client1.addExtraOption(option93);

    // Configure the server with two shared networks which can be accessed
    // by clients belonging to "a-devices" and "b-devices" classes
    // respectively.
    configure(NETWORKS_CONFIG[13], *client1.getServer());

    // Simply send DHCPDISCOVER to avoid allocating a lease.
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doDiscover());
    });
    Pkt4Ptr resp1 = client1.getContext().response_;
    ASSERT_TRUE(resp1);
    ASSERT_EQ(DHCPOFFER, resp1->getType());
    // The client should be offered a lease from the second shared network.
    EXPECT_EQ("10.0.0.63", resp1->getYiaddr().toText());

    // Create another client which will belong to a different class.
    Dhcp4Client client2(client1.getServer(), Dhcp4Client::SELECTING);
    client2.setIfaceName("eth1");
    client2.setIfaceIndex(ETH1_INDEX);

    // Add option93 which would cause the client1 to be classified as "a-devices".
    option93.reset(new OptionUint16(Option::V4, 93, 0x0001));
    client2.addExtraOption(option93);

    // Send DHCPDISCOVER. There is no lease in the lease database so the
    // client should be offered a lease based on the client class selection.
    testAssigned([this, &client2] {
        doDiscover(client2, "192.0.2.63", "");
    });
}

// This test verifies that custom server identifier can be specified for a
// shared network.
TEST_F(Dhcpv4SharedNetworkTest, customServerIdentifier) {
    Dhcp4Client client1(Dhcp4Client::SELECTING);
    client1.setIfaceName("eth1");
    client1.setIfaceIndex(ETH1_INDEX);

    // Configure DHCP server.
    ASSERT_NO_THROW(configure(NETWORKS_CONFIG[15], *client1.getServer()));

    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doDORA());
    });

    // Make sure that the server responded.
    ASSERT_TRUE(client1.getContext().response_);
    Pkt4Ptr resp = client1.getContext().response_;
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));
    // The explicitly configured server identifier should take precedence
    // over generated server identifier.
    EXPECT_EQ("1.2.3.4", client1.config_.serverid_.toText());

    // Create another client using different interface.
    Dhcp4Client client2(client1.getServer(), Dhcp4Client::SELECTING);
    client2.setIfaceName("eth0");
    client2.setIfaceIndex(ETH0_INDEX);

    testAssigned([&client2] {
        ASSERT_NO_THROW(client2.doDORA());
    });

    // Make sure that the server responded.
    ASSERT_TRUE(client2.getContext().response_);
    resp = client2.getContext().response_;
    // Make sure that the server has responded with DHCPACK.
    ASSERT_EQ(DHCPACK, static_cast<int>(resp->getType()));
    // The explicitly configured server identifier should take precedence
    // over generated server identifier.
    EXPECT_EQ("2.3.4.5", client2.config_.serverid_.toText());
}

// Access to a pool within shared network is restricted by client
// classification.
TEST_F(Dhcpv4SharedNetworkTest, poolInSharedNetworkSelectedByClass) {
    // Create client #1
    Dhcp4Client client1(Dhcp4Client::SELECTING);
    client1.setIfaceName("eth1");
    client1.setIfaceIndex(ETH1_INDEX);

    // Configure the server with one shared network including one subnet and
    // in 2 pools in it. The access to one of the pools is restricted
    // by client classification.
    configure(NETWORKS_CONFIG[16], *client1.getServer());

    // Client #1 requests an address in the restricted pool but can't be assigned
    // this address because the client doesn't belong to a certain class.
    testAssigned([this, &client1] {
        doDORA(client1, "192.0.2.100", "192.0.2.63");
    });

    // Release the lease that the client has got, because we'll need this address
    // further in the test.
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doRelease());
    });

    // Add option93 which would cause the client to be classified as "a-devices".
    OptionPtr option93(new OptionUint16(Option::V4, 93, 0x0001));
    client1.addExtraOption(option93);

    // This time, the allocation of the address provided as hint should be successful.
    testAssigned([this, &client1] {
        doDORA(client1, "192.0.2.63", "192.0.2.63");
    });

    // Client 2 should be assigned an address from the unrestricted pool.
    Dhcp4Client client2(client1.getServer(), Dhcp4Client::SELECTING);
    client2.setIfaceName("eth1");
    client2.setIfaceIndex(ETH1_INDEX);
    testAssigned([this, &client2] {
        doDORA(client2, "192.0.2.100");
    });

    // Now, let's reconfigure the server to also apply restrictions on the
    // pool to which client2 now belongs.
    configure(NETWORKS_CONFIG[17], *client1.getServer());

    // The client should be refused to renew the lease because it doesn't belong
    // to "b-devices" class.
    client2.setState(Dhcp4Client::RENEWING);
    testAssigned([this, &client2] {
        doRequest(client2, "");
    });

    // If we add option93 with a value matching this class, the lease should
    // get renewed.
    OptionPtr option93_bis(new OptionUint16(Option::V4, 93, 0x0002));
    client2.addExtraOption(option93_bis);

    testAssigned([this, &client2] {
        doRequest(client2, "192.0.2.100");
    });
}

// Access to a pool within plain subnet is restricted by client classification.
TEST_F(Dhcpv4SharedNetworkTest, poolInSubnetSelectedByClass) {
    // Create client #1
    Dhcp4Client client1(Dhcp4Client::SELECTING);
    client1.setIfaceName("eth1");
    client1.setIfaceIndex(ETH1_INDEX);

    // Configure the server with one plain subnet including two pools.
    // The access to one of the pools is restricted by client classification.
    configure(NETWORKS_CONFIG[18], *client1.getServer());

    // Client #1 requests an address in the restricted pool but can't be assigned
    // this address because the client doesn't belong to a certain class.
    testAssigned([this, &client1] {
        doDORA(client1, "192.0.2.100", "192.0.2.63");
    });

    // Release the lease that the client has got, because we'll need this address
    // further in the test.
    testAssigned([&client1] {
        ASSERT_NO_THROW(client1.doRelease());
    });

    // Add option93 which would cause the client to be classified as "a-devices".
    OptionPtr option93(new OptionUint16(Option::V4, 93, 0x0001));
    client1.addExtraOption(option93);

    // This time, the allocation of the address provided as hint should be successful.
    testAssigned([this, &client1] {
        doDORA(client1, "192.0.2.63", "192.0.2.63");
    });

    // Client 2 should be assigned an address from the unrestricted pool.
    Dhcp4Client client2(client1.getServer(), Dhcp4Client::SELECTING);
    client2.setIfaceName("eth1");
    client2.setIfaceIndex(ETH1_INDEX);
    testAssigned([this, &client2] {
        doDORA(client2, "192.0.2.100");
    });

    // Now, let's reconfigure the server to also apply restrictions on the
    // pool to which client2 now belongs.
    configure(NETWORKS_CONFIG[19], *client1.getServer());

    // The client should be refused to renew the lease because it doesn't belong
    // to "b-devices" class.
    client2.setState(Dhcp4Client::RENEWING);
    testAssigned([this, &client2] {
        doRequest(client2, "");
    });

    // If we add option93 with a value matching this class, the lease should
    // get renewed.
    OptionPtr option93_bis(new OptionUint16(Option::V4, 93, 0x0002));
    client2.addExtraOption(option93_bis);

    testAssigned([this, &client2] {
        doRequest(client2, "192.0.2.100");
    });
}

// Shared network is selected based on giaddr value (relay specified
// on shared network level, but response is send to source address.
TEST_F(Dhcpv4SharedNetworkTest, sharedNetworkSendToSourceTestingModeEnabled) {
    // Create client #1. This is a relayed client which is using relay
    // address matching configured shared network.
    // Source address is set to unrelated to configuration.

    Dhcp4Client client1(Dhcp4Client::SELECTING);
    // Put Kea into testing mode.
    client1.getServer()->setSendResponsesToSource(true);
    client1.useRelay(true, IOAddress("192.3.5.6"), IOAddress("1.1.1.2"));
    // Configure the server with one shared network and one subnet outside of the
    // shared network.
    configure(NETWORKS_CONFIG[1], *client1.getServer());
    // Client #1 should be assigned an address from shared network.
    testAssigned([this, &client1] {
        doDORA(client1, "192.0.2.63", "192.0.2.63");
    });

    // normally Kea would send packet to 192.3.5.6 but we want it get from
    // 1.1.1.2 in send to source testing mode but still with correctly
    // assigned address.
    Pkt4Ptr resp1 = client1.getContext().response_;
    EXPECT_EQ("1.1.1.2", resp1->getLocalAddr().toText());

    // Create client #2. This is a relayed client which is using relay
    // address matching subnet outside of the shared network.
    Dhcp4Client client2(client1.getServer(), Dhcp4Client::SELECTING);
    client2.useRelay(true, IOAddress("192.1.2.3"), IOAddress("2.2.2.3"));
    testAssigned([this, &client2] {
        doDORA(client2, "192.0.2.65", "192.0.2.63");
    });

    Pkt4Ptr resp2 = client2.getContext().response_;
    EXPECT_EQ("2.2.2.3", resp2->getLocalAddr().toText());
    // reset testing mode.
    client1.getServer()->setSendResponsesToSource(false);
}

// Verify option processing precedence
// Order is global < class < shared-network < subnet < pool < host reservation
TEST_F(Dhcpv4SharedNetworkTest, precedenceGlobal) {
    const std::string config =
        "{"
        "    \"interfaces-config\": {"
        "        \"interfaces\": [ \"*\" ]"
        "    },"
        "    \"valid-lifetime\": 600,"
        "    \"option-data\": ["
        "        {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"192.0.2.1\""
        "        }"
        "    ],"
        "    \"shared-networks\": ["
        "        {"
        "            \"name\": \"frog\","
        "            \"interface\": \"eth1\","
        "            \"subnet4\": ["
        "                {"
        "                    \"subnet\": \"192.0.2.0/26\","
        "                    \"id\": 10,"
        "                    \"pools\": ["
        "                        {"
        "                            \"pool\": \"192.0.2.1 - 192.0.2.63\""
        "                        }"
        "                    ],"
        "                    \"reservations\": ["
        "                        {"
        "                            \"hw-address\": \"aa:bb:cc:dd:ee:ff\","
        "                            \"ip-address\": \"192.0.2.28\""
        "                        }"
        "                    ]"
        "                }"
        "            ]"
        "        }"
        "    ]"
        "}";

    testPrecedence(config, "192.0.2.1");
}

// Verify option processing precedence
// Order is global < class < shared-network < subnet < pool < host reservation
TEST_F(Dhcpv4SharedNetworkTest, precedenceClass) {
    const std::string config =
        "{"
        "    \"interfaces-config\": {"
        "        \"interfaces\": [ \"*\" ]"
        "    },"
        "    \"valid-lifetime\": 600,"
        "    \"option-data\": ["
        "        {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"192.0.2.1\""
        "        }"
        "    ],"
        "    \"client-classes\": ["
        "        {"
        "            \"name\": \"alpha\","
        "            \"test\": \"'' == ''\","
        "            \"option-data\": ["
        "                {"
        "                   \"name\": \"domain-name-servers\","
        "                   \"data\": \"192.0.2.2\""
        "                }"
        "            ]"
        "        }"
        "    ],"
        "    \"shared-networks\": ["
        "        {"
        "            \"name\": \"frog\","
        "            \"interface\": \"eth1\","
        "            \"subnet4\": ["
        "                {"
        "                    \"subnet\": \"192.0.2.0/26\","
        "                    \"id\": 10,"
        "                    \"pools\": ["
        "                        {"
        "                            \"pool\": \"192.0.2.1 - 192.0.2.63\""
        "                        }"
        "                    ],"
        "                    \"reservations\": ["
        "                        {"
        "                            \"hw-address\": \"aa:bb:cc:dd:ee:ff\","
        "                            \"ip-address\": \"192.0.2.28\""
        "                        }"
        "                    ]"
        "                }"
        "            ]"
        "        }"
        "    ]"
        "}";

    testPrecedence(config, "192.0.2.2");
}

// Verify option processing precedence
// Order is global < class < shared-network < subnet < pool < host reservation
TEST_F(Dhcpv4SharedNetworkTest, precedenceClasses) {
    const std::string config =
        "{"
        "    \"interfaces-config\": {"
        "        \"interfaces\": [ \"*\" ]"
        "    },"
        "    \"valid-lifetime\": 600,"
        "    \"option-data\": ["
        "        {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"192.0.2.1\""
        "        }"
        "    ],"
        "    \"client-classes\": ["
        "        {"
        "            \"name\": \"beta\","
        "            \"test\": \"'' == ''\","
        "            \"option-data\": ["
        "                {"
        "                   \"name\": \"domain-name-servers\","
        "                   \"data\": \"192.0.2.2\""
        "                }"
        "            ]"
        "        },"
        "        {"
        "            \"name\": \"alpha\","
        "            \"test\": \"'' == ''\","
        "            \"option-data\": ["
        "                {"
        "                   \"name\": \"domain-name-servers\","
        "                   \"data\": \"192.0.2.3\""
        "                }"
        "            ]"
        "        }"
        "    ],"
        "    \"shared-networks\": ["
        "        {"
        "            \"name\": \"frog\","
        "            \"interface\": \"eth1\","
        "            \"subnet4\": ["
        "                {"
        "                    \"subnet\": \"192.0.2.0/26\","
        "                    \"id\": 10,"
        "                    \"pools\": ["
        "                        {"
        "                            \"pool\": \"192.0.2.1 - 192.0.2.63\""
        "                        }"
        "                    ],"
        "                    \"reservations\": ["
        "                        {"
        "                            \"hw-address\": \"aa:bb:cc:dd:ee:ff\","
        "                            \"ip-address\": \"192.0.2.28\""
        "                        }"
        "                    ]"
        "                }"
        "            ]"
        "        }"
        "    ]"
        "}";

    // Class order is the insert order
    testPrecedence(config, "192.0.2.2");
}

// Verify option processing precedence
// Order is global < class < shared-network < subnet < pool < host reservation
TEST_F(Dhcpv4SharedNetworkTest, precedenceNetwork) {
    const std::string config =
        "{"
        "    \"interfaces-config\": {"
        "        \"interfaces\": [ \"*\" ]"
        "    },"
        "    \"valid-lifetime\": 600,"
        "    \"option-data\": ["
        "        {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"192.0.2.1\""
        "        }"
        "    ],"
        "    \"client-classes\": ["
        "        {"
        "            \"name\": \"alpha\","
        "            \"test\": \"'' == ''\","
        "            \"option-data\": ["
        "                {"
        "                   \"name\": \"domain-name-servers\","
        "                   \"data\": \"192.0.2.2\""
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
        "                   \"name\": \"domain-name-servers\","
        "                   \"data\": \"192.0.2.3\""
        "                }"
        "            ],"
        "            \"subnet4\": ["
        "                {"
        "                    \"subnet\": \"192.0.2.0/26\","
        "                    \"id\": 10,"
        "                    \"pools\": ["
        "                        {"
        "                            \"pool\": \"192.0.2.1 - 192.0.2.63\""
        "                        }"
        "                    ],"
        "                    \"reservations\": ["
        "                        {"
        "                            \"hw-address\": \"aa:bb:cc:dd:ee:ff\","
        "                            \"ip-address\": \"192.0.2.28\""
        "                        }"
        "                    ]"
        "                }"
        "            ]"
        "        }"
        "    ]"
        "}";

    testPrecedence(config, "192.0.2.3");
}

// Verify option processing precedence
// Order is global < class < shared-network < subnet < pool < host reservation
TEST_F(Dhcpv4SharedNetworkTest, precedenceSubnet) {
    const std::string config =
        "{"
        "    \"interfaces-config\": {"
        "        \"interfaces\": [ \"*\" ]"
        "    },"
        "    \"valid-lifetime\": 600,"
        "    \"option-data\": ["
        "        {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"192.0.2.1\""
        "        }"
        "    ],"
        "    \"client-classes\": ["
        "        {"
        "            \"name\": \"alpha\","
        "            \"test\": \"'' == ''\","
        "            \"option-data\": ["
        "                {"
        "                   \"name\": \"domain-name-servers\","
        "                   \"data\": \"192.0.2.2\""
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
        "                   \"name\": \"domain-name-servers\","
        "                   \"data\": \"192.0.2.3\""
        "                }"
        "            ],"
        "            \"subnet4\": ["
        "                {"
        "                    \"subnet\": \"192.0.2.0/26\","
        "                    \"id\": 10,"
        "                    \"option-data\": ["
        "                        {"
        "                           \"name\": \"domain-name-servers\","
        "                           \"data\": \"192.0.2.4\""
        "                        }"
        "                    ],"
        "                    \"pools\": ["
        "                        {"
        "                            \"pool\": \"192.0.2.1 - 192.0.2.63\""
        "                        }"
        "                    ],"
        "                    \"reservations\": ["
        "                        {"
        "                            \"hw-address\": \"aa:bb:cc:dd:ee:ff\","
        "                            \"ip-address\": \"192.0.2.28\""
        "                        }"
        "                    ]"
        "                }"
        "            ]"
        "        }"
        "    ]"
        "}";

    testPrecedence(config, "192.0.2.4");
}

// Verify option processing precedence
// Order is global < class < shared-network < subnet < pool < host reservation
TEST_F(Dhcpv4SharedNetworkTest, precedencePool) {
    const std::string config =
        "{"
        "    \"interfaces-config\": {"
        "        \"interfaces\": [ \"*\" ]"
        "    },"
        "    \"valid-lifetime\": 600,"
        "    \"option-data\": ["
        "        {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"192.0.2.1\""
        "        }"
        "    ],"
        "    \"client-classes\": ["
        "        {"
        "            \"name\": \"alpha\","
        "            \"test\": \"'' == ''\","
        "            \"option-data\": ["
        "                {"
        "                   \"name\": \"domain-name-servers\","
        "                   \"data\": \"192.0.2.2\""
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
        "                   \"name\": \"domain-name-servers\","
        "                   \"data\": \"192.0.2.3\""
        "                }"
        "            ],"
        "            \"subnet4\": ["
        "                {"
        "                    \"subnet\": \"192.0.2.0/26\","
        "                    \"id\": 10,"
        "                    \"option-data\": ["
        "                        {"
        "                           \"name\": \"domain-name-servers\","
        "                           \"data\": \"192.0.2.4\""
        "                        }"
        "                    ],"
        "                    \"pools\": ["
        "                        {"
        "                            \"pool\": \"192.0.2.1 - 192.0.2.63\","
        "                            \"option-data\": ["
        "                                {"
        "                                   \"name\": \"domain-name-servers\","
        "                                   \"data\": \"192.0.2.5\""
        "                                }"
        "                            ]"
        "                        }"
        "                    ],"
        "                    \"reservations\": ["
        "                        {"
        "                            \"hw-address\": \"aa:bb:cc:dd:ee:ff\","
        "                            \"ip-address\": \"192.0.2.28\""
        "                        }"
        "                    ]"
        "                }"
        "            ]"
        "        }"
        "    ]"
        "}";

    testPrecedence(config, "192.0.2.5");
}

// Verify option processing precedence
// Order is global < class < shared-network < subnet < pool < host reservation
TEST_F(Dhcpv4SharedNetworkTest, precedenceReservation) {
    const std::string config =
        "{"
        "    \"interfaces-config\": {"
        "        \"interfaces\": [ \"*\" ]"
        "    },"
        "    \"valid-lifetime\": 600,"
        "    \"option-data\": ["
        "        {"
        "           \"name\": \"domain-name-servers\","
        "           \"data\": \"192.0.2.1\""
        "        }"
        "    ],"
        "    \"client-classes\": ["
        "        {"
        "            \"name\": \"alpha\","
        "            \"test\": \"'' == ''\","
        "            \"option-data\": ["
        "                {"
        "                   \"name\": \"domain-name-servers\","
        "                   \"data\": \"192.0.2.2\""
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
        "                   \"name\": \"domain-name-servers\","
        "                   \"data\": \"192.0.2.3\""
        "                }"
        "            ],"
        "            \"subnet4\": ["
        "                {"
        "                    \"subnet\": \"192.0.2.0/26\","
        "                    \"id\": 10,"
        "                    \"option-data\": ["
        "                        {"
        "                           \"name\": \"domain-name-servers\","
        "                           \"data\": \"192.0.2.4\""
        "                        }"
        "                    ],"
        "                    \"pools\": ["
        "                        {"
        "                            \"pool\": \"192.0.2.1 - 192.0.2.63\","
        "                            \"option-data\": ["
        "                                {"
        "                                   \"name\": \"domain-name-servers\","
        "                                   \"data\": \"192.0.2.5\""
        "                                }"
        "                            ]"
        "                        }"
        "                    ],"
        "                    \"reservations\": ["
        "                        {"
        "                            \"hw-address\": \"aa:bb:cc:dd:ee:ff\","
        "                            \"ip-address\": \"192.0.2.28\","
        "                            \"option-data\": ["
        "                                {"
        "                                   \"name\": \"domain-name-servers\","
        "                                   \"data\": \"192.0.2.6\""
        "                                }"
        "                            ]"
        "                        }"
        "                    ]"
        "                }"
        "            ]"
        "        }"
        "    ]"
        "}";

    testPrecedence(config, "192.0.2.6");
}

// Verify authoritative sanitization.
// This test generates many similar configs. They all have similar
// structure:
// - 1 shared-network (with possibly authoritative flag in it)
//   2 subnets (with each possibly having its own authoritative flag)
//
// If the flag is specified on subnet-level, the value must match those
// specified on subnet level.
TEST_F(Dhcpv4SharedNetworkTest, authoritative) {

    // Each scenario will be defined using those parameters.
    typedef struct scenario {
        bool exp_success;
        AuthoritativeFlag global;
        AuthoritativeFlag subnet1;
        AuthoritativeFlag subnet2;
    } scenario;

    // We have the following scenarios. The default is no.
    // The only allowed combinations are those that end up with
    // having all three values (global, subnet1, subnet2) agree.
    scenario scenarios[] = {
        //result, global,      subnet1,      subnet2
        { true, AUTH_DEFAULT,  AUTH_DEFAULT, AUTH_DEFAULT },
        { true, AUTH_YES,      AUTH_DEFAULT, AUTH_DEFAULT },
        { true, AUTH_YES,      AUTH_YES,     AUTH_YES },
        { true, AUTH_NO,       AUTH_DEFAULT, AUTH_DEFAULT },
        { true, AUTH_NO,       AUTH_NO,      AUTH_NO },
        { false, AUTH_DEFAULT, AUTH_YES,     AUTH_NO },
        { false, AUTH_DEFAULT, AUTH_NO,      AUTH_YES },
        { false, AUTH_DEFAULT, AUTH_YES,     AUTH_YES },
        { false, AUTH_YES,     AUTH_NO,      AUTH_NO },
        { false, AUTH_YES,     AUTH_DEFAULT, AUTH_NO },
        { false, AUTH_YES,     AUTH_NO,      AUTH_DEFAULT },
        { false, AUTH_YES,     AUTH_NO,      AUTH_NO },
        { false, AUTH_YES,     AUTH_NO,      AUTH_YES },
        { false, AUTH_YES,     AUTH_YES,     AUTH_NO }
    };

    // Let's test them one by one
    int cnt = 0;
    for ( auto s : scenarios) {
        cnt++;

        string cfg = generateAuthConfig(s.global, s.subnet1, s.subnet2);

        // Create client and set MAC address to the one that has a reservation.
        Dhcp4Client client(Dhcp4Client::SELECTING);

        stringstream tmp;
        tmp << "Testing scenario " << cnt;
        SCOPED_TRACE(tmp.str());
        // Create server configuration.
        auto result = configureWithStatus(cfg, *client.getServer(), true, s.exp_success? 0 : 1);
        if (s.exp_success) {
            EXPECT_EQ(result.first, 0) << result.second;
        } else {
            EXPECT_EQ(result.first, 1) << "Configuration expected to fail, but succeeded";
        }
    }
}

} // end of anonymous namespace
