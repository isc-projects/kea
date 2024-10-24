// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <fuzz.h>

#include <cc/command_interpreter.h>
#include <cc/user_context.h>
#include <dhcp6/ctrl_dhcp6_srv.h>
#include <dhcp6/json_config_parser.h>
#include <dhcp6/parser_context.h>
#include <dhcpsrv/packet_fuzzer.h>
#include <util/encode/encode.h>

#include <cassert>
#include <cstdlib>
#include <util/filesystem.h>
#include <vector>

using namespace isc;
using namespace isc::config;
using namespace isc::util;
using namespace std;

namespace {

static string const KEA_DHCP6_CONF(KEA_FUZZ_DIR + "/kea-dhcp6.conf");
static string KEA_DHCP6_FUZZING_INTERFACE;
static string KEA_DHCP6_FUZZING_ADDRESS;

}  // namespace

extern "C" {

int
LLVMFuzzerInitialize() {
    static bool initialized(DoInitialization());
    assert(initialized);

    setenv("KEA_DHCP6_FUZZING_ROTATE_PORT", "true", 0);

    if (if_nametoindex("lo") > 0) {
        KEA_DHCP6_FUZZING_INTERFACE = string("lo");
    } else if (if_nametoindex("lo0") > 0) {
        KEA_DHCP6_FUZZING_INTERFACE = string("lo0");
    }

    char const* interface(getenv("KEA_DHCP6_FUZZING_INTERFACE"));
    if (interface) {
        KEA_DHCP6_FUZZING_INTERFACE = string(interface);
    }

    char const* address(getenv("KEA_DHCP6_FUZZING_ADDRESS"));
    KEA_DHCP6_FUZZING_ADDRESS = string(address ? address : "::1");

    writeToFile(KEA_DHCP6_CONF, R"(
      {
        "Dhcp6": {
          "interfaces-config": {
            "interfaces": [
              ")" + KEA_DHCP6_FUZZING_INTERFACE + R"("
            ]
          },
          "lease-database": {
            "persist": false,
            "type": "memfile"
          },
          "server-id": {
            "type": "EN",
            "persist": false
          },
          "subnet6": [
            {
              "id": 1,
              "pools": [
                {
                  "pool": "2001:db8::/80"
                }
              ],
              "subnet": "2001:db8::/64"
            }
          ]
        }
      }
    )");

    // Iterate through the interfaces and expect no errors.
    for (IfacePtr const& interface : IfaceMgr::instance().getIfaces()) {
        for (string const& error : interface->getErrors()) {
            cout << error << endl;
        }
        assert(interface->getErrors().empty());
    }

    return 0;
}

int
LLVMFuzzerTearDown() {
    try {
        remove(KEA_DHCP6_CONF.c_str());
    } catch (...) {
    }
    return 0;
}

int
LLVMFuzzerTestOneInput(uint8_t const* data, size_t size) {
    vector<uint8_t> byte_stream;
    bool const valid(byteStreamToPacketData(data, size, byte_stream));
    if (!valid) {
        cout << "Invalid input. Skipping..." << endl;
        return 0;
    }

    ControlledDhcpv6Srv server;
    server.init(KEA_DHCP6_CONF);

    // Fuzz.
    PacketFuzzer fuzzer(ControlledDhcpv6Srv::getInstance()->getServerPort(),
                        KEA_DHCP6_FUZZING_INTERFACE, KEA_DHCP6_FUZZING_ADDRESS);
    fuzzer.transfer(byte_stream.data(), byte_stream.size());
    ControlledDhcpv6Srv::getInstance()->runOne();

    return 0;
}

}  // extern "C"
