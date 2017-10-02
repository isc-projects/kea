// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
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
// - 2 shared networks, each with 1 subnet and client class restricton
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

};

/// @Brief Test fixture class for DHCPv4 server using shared networks.
class Dhcpv4SharedNetworkTest : public Dhcpv4SrvTest {
public:

    /// @brief Wrapper around statistics value before transaction.
    struct StatBefore {
        /// @brief Constructor.
        ///
        /// @param value Statistic value.
        explicit StatBefore(const int64_t value)
            : value_(value) {
        }
        /// @brief Holds numeric statistic value.
        int64_t value_;
    };

    /// @brief Wrapper around statistics value after transaction.
    struct StatAfter {
        /// @brief Constructor.
        ///
        /// @param value Statistic value.
        StatAfter(const int64_t value)
            : value_(value) {
        }
        /// @brief Holds numeric statistic value.
        int64_t value_;
    };

    /// @brief Mode of statistics verificiation in statistics tests.
    enum class StatsVerify {
        NEW_ALLOCATION,
        TRANSFER
    };

    /// @brief Constructor.
    Dhcpv4SharedNetworkTest()
        : Dhcpv4SrvTest(),
          iface_mgr_test_config_(true) {
        IfaceMgr::instance().openSockets4();
        StatsMgr::instance().removeAll();
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
        }
    }

    /// @brief Tests subnet[id].assigned-addresses statistics changes as a result of
    /// address allocations.
    ///
    /// This method first gathers values of subnet[id].assigned-addresses statistics for
    /// all subnets. These values will be later used for further verifications. Then,
    /// it launches a desired operation (specified as lambda), e.g. DORA 4-way exchange
    /// or two way exchanges such as Discover-Offer, renewal, release etc.
    ///
    /// When the exchange with the server is completed, this method will try to identify
    /// a subnet from which the client has obtained a new lease, in which the client
    /// has renewed a lease or from which the client has released a lease. For the
    /// former cases it is performed by matching yiaddr in the response with the
    /// configured subnets. In the last case, the ciaddr in the query is used.
    ///
    /// The caller provides expected initial statistics of assigned addresses for
    /// this subnet and the expected final statistics. This method will compare
    /// the actual statistics with expected values for this subnet.
    ///
    /// This method also checks statistics for other subnets. If the @c verify
    /// parameter is set to @c StatsVerify::NEW_ALLOCATION it expects that
    /// statistics hasn't changed for all other subnets. If the @c verify
    /// parameter is set to @c StatsVerify::TRANSFER it iterates over the subnets
    /// within the shared network to which selected subnet belongs and verifies
    /// that the total number of allocated leases hasn't changed (only some leases
    /// have been replaced with new allocations, possibly from different subnets).
    ///
    /// @param client Reference to the client.
    /// @param before Statistics of assigned addresses before interaction with the
    /// DHCP server.
    /// @param after Statistics of assigned addresses after interaction with the
    /// DHCP server.
    /// @param operation Set of operations to be executed (interactions with the
    /// DHCP server).
    /// @param verify Verification mode (new allocation or transfer of a lease
    /// between subnets within shared networks).
    void testAssigned(Dhcp4Client& client, const StatBefore& before,
                      const StatAfter& after, const std::function<void()>& operation,
                      const StatsVerify& verify = StatsVerify::NEW_ALLOCATION) {
        // Collect statistics of assigned addresses for all existing subnets.
        std::map<SubnetID, int64_t> before_stats;
        CfgSubnets4Ptr cfg_subnets = CfgMgr::instance().getCurrentCfg()->getCfgSubnets4();
        const Subnet4Collection* subnets = cfg_subnets->getAll();
        for (auto subnet_it = subnets->cbegin(); subnet_it != subnets->end(); ++subnet_it) {
            before_stats[(*subnet_it)->getID()] = getStatsAssignedAddresses((*subnet_it)->getID());
        }

        // Perform exchanges with a server.
        operation();

        Subnet4Ptr subnet;
        IOAddress address = IOAddress::IPV4_ZERO_ADDRESS();
        Pkt4Ptr query = client.getContext().query_;
        Pkt4Ptr resp = client.getContext().response_;

        // If we have received a response from the server, it is likely to be
        // DHCPOFFER or DHCPACK. Use yiaddr to find a matching subnet.
        if (resp) {
            address = resp->getYiaddr();

        // In the DHCPRELEASE case there is no response from the server so let's use
        // the ciaddr provided by the client to find a matching subnet.
        } else if (query && (query->getType() == DHCPRELEASE)) {
            address = query->getCiaddr();
        }

        // If we found the matching subnet, we'll verify the actual statistics against
        // the values provided by the caller.
        if (!address.isV4Zero()) {
            for (auto subnet_it = subnets->cbegin(); subnet_it != subnets->cend(); ++subnet_it) {
                if ((*subnet_it)->inRange(address)) {
                    subnet = *subnet_it;
                    ASSERT_TRUE(subnet);
                    int64_t after_stat = getStatsAssignedAddresses(subnet->getID());
                    ASSERT_EQ(before.before_, before_stats[subnet->getID()]);
                    ASSERT_EQ(after.after_, after_stat);
                }
            }
        }

        // New address allocation or renewal of the same addres.
        if (verify == StatsVerify::NEW_ALLOCATION) {
            for (auto subnet_it = subnets->cbegin(); subnet_it != subnets->end(); ++subnet_it) {
                if  (!subnet || (*subnet_it)->getID() != subnet->getID()) {
                    ASSERT_EQ(before_stats[(*subnet_it)->getID()],
                              getStatsAssignedAddresses((*subnet_it)->getID()));
                }
            }

        // Renewal of the lease which caused replacement of the existing lease with
        // a new one belonging to the same shared network.
        } else if (verify == StatsVerify::TRANSFER) {
            Subnet4Ptr current_subnet;
            int64_t allocated = 0;
            int64_t allocated_before = 0;
            // Iterate over all subnets within shared network and count the number of
            // allocated leases.
            while (current_subnet) {
                allocated += getStatsAssignedAddresses(current_subnet->getID());
                allocated_before += before_stats[current_subnet->getID()];
                current_subnet = subnet->getNextSubnet(subnet);
            }

            // The number of leases then and now should be equal.
            ASSERT_EQ(allocated_before, allocated);
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
                if (second_list && (second_list->getType() == Element::list) &&
                    (second_list->size() == 2)) {
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

    /// @brief Destructor.
    virtual ~Dhcpv4SharedNetworkTest() {
        StatsMgr::instance().removeAll();
    }

    /// @brief Interface Manager's fake configuration control.
    IfaceMgrTestConfig iface_mgr_test_config_;
};

// Running out of addresses within a subnet in a shared network.
TEST_F(Dhcpv4SharedNetworkTest, poolInSharedNetworkShortage) {
    // Create client #1
    Dhcp4Client client1(Dhcp4Client::SELECTING);
    client1.setIfaceName("eth1");

    // Configure the server with one shared network including two subnets and
    // one subnet outside of the shared network.
    configure(NETWORKS_CONFIG[0], *client1.getServer());

    // Client #1 requests an address in first subnet within a shared network.
    // We'll send a hint of 192.0.2.63 and expect to get it.
    testAssigned(client1, StatBefore(0), StatAfter(1), [this, &client1]() {
        doDORA(client1, "192.0.2.63", "192.0.2.63");
    });

    // Client #2 The second client will request a lease and should be assigned
    // an address from the second subnet.
    Dhcp4Client client2(client1.getServer(), Dhcp4Client::SELECTING);
    client2.setIfaceName("eth1");
    testAssigned(client2, StatBefore(0), StatAfter(1), [this, &client2]() {
        doDORA(client2, "10.0.0.16");
    });

    // Client #3. It sends DHCPDISCOVER which should be dropped by the server because
    // the server has no more addresses to assign.
    Dhcp4Client client3(client1.getServer(), Dhcp4Client::SELECTING);
    client3.setIfaceName("eth1");
    testAssigned(client3, StatBefore(1), StatAfter(1), [this, &client3]() {
        ASSERT_NO_THROW(client3.doDiscover());
        Pkt4Ptr resp3 = client3.getContext().response_;
        ASSERT_FALSE(resp3);
    });

    // Client #3 should be assigned an address if subnet 3 is selected for this client.
    client3.setIfaceName("eth0");
    testAssigned(client3, StatBefore(0), StatAfter(1), [this, &client3]() {
        doDORA(client3, "192.0.2.65");
    });

    // Client #1 should be able to renew its address.
    client1.setState(Dhcp4Client::RENEWING);
    testAssigned(client1, StatBefore(1), StatAfter(1), [this, &client1]() {
        doRequest(client1, "192.0.2.63");
    });

    // Client #2 should be able to renew its address.
    client2.setState(Dhcp4Client::RENEWING);
    testAssigned(client1, StatBefore(1), StatAfter(1), [this, &client2]() {
        doRequest(client2, "10.0.0.16");
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
    testAssigned(client1, StatBefore(0), StatAfter(1), [this, &client1] {
        doDORA(client1, "192.0.2.63", "192.0.2.63");
    });

    // Create client #2. This is a relayed client which is using relay
    // address matching subnet outside of the shared network.
    Dhcp4Client client2(client1.getServer(), Dhcp4Client::SELECTING);
    client2.useRelay(true, IOAddress("192.1.2.3"), IOAddress("10.0.0.3"));
    testAssigned(client2, StatBefore(0), StatAfter(1), [this, &client2] {
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
    testAssigned(client1, StatBefore(0), StatAfter(1), [this, &client1] {
        doDORA(client1, "192.0.2.63");
    });

    // Create client #2. This is a relayed client which is using relay
    // address that is used for subnet 2 in the shared network.
    Dhcp4Client client2(client1.getServer(), Dhcp4Client::SELECTING);
    client2.useRelay(true, IOAddress("192.2.2.2"), IOAddress("10.0.0.3"));
    testAssigned(client2, StatBefore(0), StatAfter(1), [this, &client2] {
        doDORA(client2, "10.0.0.16");
    });

    // Create client #3. This is a relayed client which is using relay
    // address matching subnet outside of the shared network.
    Dhcp4Client client3(client1.getServer(), Dhcp4Client::SELECTING);
    client3.useRelay(true, IOAddress("192.3.3.3"), IOAddress("10.0.0.4"));
    testAssigned(client3, StatBefore(0), StatAfter(1), [this, &client3] {
        doDORA(client3, "192.0.2.65");
    });
}

// Providing a hint for any address belonging to a shared network.
TEST_F(Dhcpv4SharedNetworkTest, hintWithinSharedNetwork) {
    // Create client.
    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.setIfaceName("eth1");

    // Configure the server with one shared network including two subnets and
    // one subnet outside of the shared network.
    configure(NETWORKS_CONFIG[0], *client.getServer());

    // Provide a hint to an existing address within first subnet. This address
    // should be offered out of this subnet.
    testAssigned(client, StatBefore(0), StatAfter(0), [this, &client] {
        doDiscover(client, "192.0.2.63", "192.0.2.63");
    });

    // Similarly, we should be offered an address from another subnet within
    // the same shared network when we ask for it.
    testAssigned(client, StatBefore(0), StatAfter(0), [this, &client] {
        doDiscover(client, "10.0.0.16", "10.0.0.16");
    });

    // Asking for an address that is not in address pool should result in getting
    // an address from one of the subnets, but generally hard to tell from which one.
    testAssigned(client, StatBefore(0), StatAfter(0), [this, &client] {
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
    testAssigned(client1, StatBefore(0), StatAfter(1), [this, &client1] {
        doDORA(client1, "10.0.0.16", "192.0.2.63");
    });

    // Release the lease that the client has got, because we'll need this address
    // further in the test.
    testAssigned(client1, StatBefore(1), StatAfter(0), [this, &client1] {
        ASSERT_NO_THROW(client1.doRelease());
    });

    return;

    // Add option93 which would cause the client to be classified as "a-devices".
    OptionPtr option93(new OptionUint16(Option::V4, 93, 0x0001));
    client1.addExtraOption(option93);

    // This time, the allocation of the address provided as hint should be successful.
    testAssigned(client1, StatBefore(0), StatAfter(1), [this, &client1] {
        doDORA(client1, "192.0.2.63", "192.0.2.63");
    });

    // Client 2 should be assigned an address from the unrestricted subnet.
    Dhcp4Client client2(client1.getServer(), Dhcp4Client::SELECTING);
    client2.useRelay(true, IOAddress("192.3.5.6"));
    client2.setIfaceName("eth1");
    testAssigned(client2, StatBefore(0), StatAfter(1), [this, &client2] {
        doDORA(client2, "10.0.0.16");
    });

    // Now, let's reconfigure the server to also apply restrictions on the
    // subnet to which client2 now belongs.
    configure(NETWORKS_CONFIG[3], *client1.getServer());

    // The client should be refused to renew the lease because it doesn't belong
    // to "b-devices" class.
    client2.setState(Dhcp4Client::RENEWING);
    testAssigned(client2, StatBefore(1), StatAfter(1), [this, &client2] {
        doRequest(client2, "");
    });

    // If we add option93 with a value matching this class, the lease should
    // get renewed.
    OptionPtr option93_bis(new OptionUint16(Option::V4, 93, 0x0002));
    client2.addExtraOption(option93_bis);

    testAssigned(client2, StatBefore(1), StatAfter(1), [this, &client2] {
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
    testAssigned(client1, StatBefore(0), StatAfter(1), [this, &client1] {
        doDORA(client1, "10.0.0.29", "192.0.2.28");
    });

    // Create client #2
    Dhcp4Client client2(client1.getServer(), Dhcp4Client::SELECTING);
    client2.useRelay(true, IOAddress("192.3.5.6"));
    client2.setHWAddress("aa:bb:cc:dd:ee:ff");

    // Client #2 should get its reserved address from the first subnet.
    testAssigned(client2, StatBefore(0), StatAfter(1), [this, &client2] {
        doDORA(client2, "192.0.2.28");
    });

    // Reconfigure the server. Now, the first client gets second client's
    // reservation and vice versa.
    configure(NETWORKS_CONFIG[5], *client1.getServer());

    // The first client is trying to renew the lease and should get a DHCPNAK.
    client1.setState(Dhcp4Client::RENEWING);
    testAssigned(client1, StatBefore(1), StatAfter(1), [this, &client1] {
        doRequest(client1, "");
    });

    // Similarly, the second client is trying to renew the lease and should
    // get a DHCPNAK.
    client2.setState(Dhcp4Client::RENEWING);
    testAssigned(client2, StatBefore(1), StatAfter(1), [this, &client2] {
        doRequest(client2, "");
    });

    // But the client should get a lease, if it does 4-way exchange. However, it
    // must not get any of the reserved addresses because one of them is reserved
    // for another client and for another one there is a valid lease.
    client1.setState(Dhcp4Client::SELECTING);
    testAssigned(client1, StatBefore(1), StatAfter(2), [this, &client1] {
        ASSERT_NO_THROW(doDORA(client1, "192.0.2.29", "192.0.2.29"));
    }, StatsVerify::TRANSFER);
    Pkt4Ptr resp1 = client1.getContext().response_;
    ASSERT_TRUE(resp1);
    EXPECT_EQ(DHCPACK, resp1->getType());
    EXPECT_NE("10.0.0.29", resp1->getYiaddr().toText());
    EXPECT_NE("192.0.2.28", resp1->getYiaddr().toText());

    // Client #2 is now doing 4-way exchange and should get its newly reserved
    // address, released by the 4-way transaction of client 1.
    client2.setState(Dhcp4Client::SELECTING);
    testAssigned(client2, StatBefore(0), StatAfter(1), [this, &client2] {
        doDORA(client2, "10.0.0.29");
    }, StatsVerify::TRANSFER);

    // Same for client #1.
    client1.setState(Dhcp4Client::SELECTING);
    testAssigned(client1, StatBefore(1), StatAfter(1), [this, &client1] {
        doDORA(client1, "192.0.2.28");
    }, StatsVerify::TRANSFER);
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
    testAssigned(client, StatBefore(0), StatAfter(1), [this, &client] {
        doDORA(client, "10.0.0.16");
    });

    // Add option 93 which would cause the client to be classified as "a-devices".
    OptionPtr option93(new OptionUint16(Option::V4, 93, 0x0001));
    client.addExtraOption(option93);

    // Client renews its lease and should get DHCPNAK because this client now belongs
    // to the "a-devices" class and can be assigned a reserved address instead.
    client.setState(Dhcp4Client::RENEWING);
    testAssigned(client, StatBefore(1), StatAfter(1), [this, &client] {
        doRequest(client, "");
    });

    // Perform 4-way exchange again. It should be assigned a reserved address this time.
    client.setState(Dhcp4Client::SELECTING);
    testAssigned(client, StatBefore(0), StatAfter(1), [this, &client] {
        doDORA(client, "192.0.2.28");
    }, StatsVerify::TRANSFER);
}

// Some options are specified on the shared subnet level, some on the
// subnets level.
TEST_F(Dhcpv4SharedNetworkTest, optionsDerivation) {
    // Client #1.
    Dhcp4Client client1(Dhcp4Client::SELECTING);
    client1.setIfaceName("eth1");
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

    configure(NETWORKS_CONFIG[0], *client1.getServer());

    // Perform 4-way exchange to obtain a lease. The client should get the lease from
    // the second subnet.
    testAssigned(client1, StatBefore(0), StatAfter(1), [this, &client1] {
        doDORA(client1, "10.0.0.16", "10.0.0.16");
    });

    // The client1 transitions to INIT-REBOOT state in which the client1 remembers the
    // lease and sends DHCPREQUEST to all servers (server id) is not specified. If
    // the server doesn't know the client1 (doesn't have its lease), it should
    // drop the request. We want to make sure that the server responds (resp1) regardless
    // of the subnet from which the lease has been allocated.
    client1.setState(Dhcp4Client::INIT_REBOOT);
    testAssigned(client1, StatBefore(1), StatAfter(1), [this, &client1] {
        doRequest(client1, "10.0.0.16");
    });

    // Create client #2.
    Dhcp4Client client2(client1.getServer(), Dhcp4Client::SELECTING);
    client2.setIfaceName("eth1");

    // Let's make sure that the behavior is the same for the other subnet within the
    // same shared network.
    testAssigned(client2, StatBefore(0), StatAfter(1), [this, &client2] {
        doDORA(client2, "192.0.2.63", "192.0.2.63");
    });

    // The client2 transitions to INIT-REBOOT state in which the client2 remembers the
    // lease and sends DHCPREQUEST to all servers (server id) is not specified. If
    // the server doesn't know the client2 (doesn't have its lease), it should
    // drop the request. We want to make sure that the server responds (resp2) regardless
    // of the subnet from which the lease has been allocated.
    client2.setState(Dhcp4Client::INIT_REBOOT);
    testAssigned(client2, StatBefore(1), StatAfter(1), [this, &client2] {
        doRequest(client2, "192.0.2.63");
    });
}

// Host reservations include hostname, next server and client class.
TEST_F(Dhcpv4SharedNetworkTest, variousFieldsInReservation) {
    // Create client.
    Dhcp4Client client(Dhcp4Client::SELECTING);
    client.setIfaceName("eth1");
    client.setHWAddress("11:22:33:44:55:66");

    // Include hostname to force the server to return hostname to
    // the client.
    client.includeHostname("my.example.org");

    // Configure the server with a shared network including two subnets.
    // The client has address/hostname reservation in the second subnet.
    configure(NETWORKS_CONFIG[10], *client.getServer());

    // Perform 4-way exchange.
    testAssigned(client, StatBefore(0), StatAfter(1), [this, &client] {
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

    // Create server configuration with two shared networks selected
    // by the local interface: eth1 and eth0.
    configure(NETWORKS_CONFIG[8], *client1.getServer());

    // Perform 4-way exchange.
    testAssigned(client1, StatBefore(0), StatAfter(1), [this, &client1] {
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

    // Perform 4-way exchange.
    testAssigned(client2, StatBefore(0), StatAfter(1), [this, &client2] {
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
    testAssigned(client1, StatBefore(0), StatAfter(1), [this, &client1] {
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
    testAssigned(client2, StatBefore(0), StatAfter(1), [this, &client2] {
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

    // Create server configuration with match-client-id value initially
    // set to true. The client should be allocated a lease and the
    // client identifier should be included in this lease.
    configure(NETWORKS_CONFIG[11], *client.getServer());

    // Perform 4-way exchange.
    testAssigned(client, StatBefore(0), StatAfter(1), [this, &client] {
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
    testAssigned(client, StatBefore(1), StatAfter(1), [this, &client] {
        ASSERT_NO_THROW(client.doRequest());
    });
    Pkt4Ptr resp2 = client.getContext().response_;
    ASSERT_TRUE(resp2);
    ASSERT_EQ(DHCPACK, resp2->getType());

    // The lease should get rewnewed.
    EXPECT_EQ(resp2->getYiaddr().toText(), resp1->getYiaddr().toText());
}

// Shared network is selected based on the client class specified.
TEST_F(Dhcpv4SharedNetworkTest, sharedNetworkSelectedByClass) {
   // Create client #1.
    Dhcp4Client client1(Dhcp4Client::SELECTING);
    client1.setIfaceName("eth1");

    // Add option93 which would cause the client1 to be classified as "b-devices".
    OptionPtr option93(new OptionUint16(Option::V4, 93, 0x0002));
    client1.addExtraOption(option93);

    // Configure the server with two shared networks which can be accessed
    // by clients belonging to "a-devices" and "b-devices" classes
    // respectively.
    configure(NETWORKS_CONFIG[13], *client1.getServer());

    // Simply send DHCPDISCOVER to avoid allocating a lease.
    testAssigned(client1, StatBefore(0), StatAfter(0), [this, &client1] {
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

    // Add option93 which would cause the client1 to be classified as "a-devices".
    option93.reset(new OptionUint16(Option::V4, 93, 0x0001));
    client2.addExtraOption(option93);

    // Send DHCPDISCOVER. There is no lease in the lease database so the
    // client should be offered a lease based on the client class selection.
    testAssigned(client2, StatBefore(0), StatAfter(0), [this, &client2] {
        doDiscover(client2, "192.0.2.63", "");
    });
}

} // end of anonymous namespace
