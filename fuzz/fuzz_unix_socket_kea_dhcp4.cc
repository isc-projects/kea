// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <fuzz.h>

#include <asiolink/io_service.h>
#include <cc/data.h>
#include <config/command_mgr.h>
#include <dhcp4/ctrl_dhcp4_srv.h>
#include <dhcpsrv/cfgmgr.h>
#include <testutils/unix_control_client.h>

#include <util/filesystem.h>

#include <cassert>

using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::util;
using namespace isc::util::file;
using namespace std;

namespace {

static pid_t const PID(getpid());
static string const PID_STR(to_string(PID));
static string const KEA_DHCP4_CONF(KEA_FUZZ_DIR + "/kea-dhcp4-" + PID_STR + ".conf");
static string const KEA_DHCP4_CSV(KEA_FUZZ_DIR + "/kea-dhcp4-" + PID_STR + ".csv");
static string const SOCKET(KEA_FUZZ_DIR + "/kea-dhcp4-ctrl-" + PID_STR + ".sock");

static UnixControlClient CLIENT;

}  // namespace

extern "C" {

int
LLVMFuzzerInitialize() {
    static bool initialized(DoInitialization());
    assert(initialized);

    // "control-socket" is of explicit interest, but we also specify the memfile
    // CSV location to make sure that we don't get an error caused by an invalid
    // file path.
    writeToFile(KEA_DHCP4_CONF, R"(
      {
        "Dhcp4": {
          "control-socket": {
            "socket-name": ")" + SOCKET + R"(",
            "socket-type": "unix"
          },
          "lease-database": {
            "name": ")" + KEA_DHCP4_CSV + R"(",
            "persist": false,
            "type": "memfile"
          }
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
        remove(KEA_DHCP4_CONF.c_str());
    } catch (...) {
    }
    try {
        remove(KEA_DHCP4_CSV.c_str());
    } catch (...) {
    }
    try {
        remove(SOCKET.c_str());
    } catch (...) {
    }
    try {
        remove((SOCKET + ".lock").c_str());
    } catch (...) {
    }

    return 0;
}

int
LLVMFuzzerTestOneInput(uint8_t const* data, size_t size) {
    CfgMgr::instance().clear();
    ControlledDhcpv4Srv server;
    server.init(KEA_DHCP4_CONF);
    assert(isSocket(SOCKET));

    string const command(reinterpret_cast<char const*>(data), size);
    CLIENT.connectToServer(SOCKET);
    CLIENT.sendCommand(command);
    ControlledDhcpv4Srv::getInstance()->getIOService()->poll();
    string response;
    CLIENT.getResponse(response);
    ControlledDhcpv4Srv::getInstance()->getIOService()->poll();
    CLIENT.disconnectFromServer();
    ControlledDhcpv4Srv::getInstance()->getIOService()->poll();

    return 0;
}

}  // extern "C"
