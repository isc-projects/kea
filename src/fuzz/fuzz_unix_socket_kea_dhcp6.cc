// Copyright (C) 2024-2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/io_service.h>
#include <cc/data.h>
#include <config/command_mgr.h>
#include <config/unix_command_config.h>
#include <dhcp6/ctrl_dhcp6_srv.h>
#include <dhcpsrv/cfgmgr.h>
#include <testutils/env_var_wrapper.h>
#include <testutils/unix_control_client.h>
#include <util/filesystem.h>

#include <cassert>
#include <chrono>
#include <condition_variable>
#include <cstdlib>
#include <iostream>
#include <mutex>
#include <thread>
#include <unistd.h>

#include <fuzz/fuzz.h>

using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::dhcp::test;
using namespace isc::test;
using namespace isc::util;
using namespace isc::util::file;
using namespace std;
using namespace std::chrono;

namespace {

static pid_t const PID(getpid());
static string const PID_STR(to_string(PID));
static string const KEA_DHCP6_CONF(KEA_FUZZ_DIR() + "/kea-dhcp6-" + PID_STR + ".conf");
static string const KEA_DHCP6_CSV(KEA_FUZZ_DIR() + "/kea-dhcp6-" + PID_STR + ".csv");
static string const SOCKET(KEA_FUZZ_DIR() + "/kea-dhcp6-ctrl-" + PID_STR + ".sock");

static UnixControlClient TEST_CLIENT;

}  // namespace

extern "C" {

int
LLVMFuzzerInitialize() {
    static bool initialized(DoInitialization());
    assert(initialized);

    // "control-sockets" is of explicit interest, but we also specify the memfile
    // CSV location and the server-id to make sure that we don't get an error
    // caused by an invalid file path.
    writeToFile(KEA_DHCP6_CONF, R"(
      {
        "Dhcp6": {
          "control-sockets": [ {
            "socket-name": ")" + SOCKET + R"(",
            "socket-type": "unix"
          } ],
          "lease-database": {
            "name": ")" + KEA_DHCP6_CSV + R"(",
            "persist": false,
            "type": "memfile"
          },
          "server-id": {
            "type": "EN",
            "enterprise-id": 2495,
            "identifier": "0123456789",
            "persist": false
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
        remove(KEA_DHCP6_CONF.c_str());
    } catch (...) {
    }
    try {
        remove(KEA_DHCP6_CSV.c_str());
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
    ControlledDhcpv6Srv server;
    Path socket_path(SOCKET);
    auto dir = socket_path.parentDirectory();
    auto path = UnixCommandConfig::getSocketPath(true, dir);
    UnixCommandConfig::setSocketPathPerms(file::getPermissions(path));

    server.init(KEA_DHCP6_CONF);
    assert(isSocket(SOCKET));

    string const command(reinterpret_cast<char const*>(data), size);
    TEST_CLIENT.connectToServer(SOCKET);

    // On macOS the Unix/local socket sendspace is smaller than
    // the biggest sample so the send() system call hangs until
    // the server reads: using a second thread for sending.
    // Note that poll() and server code in general must be called
    // by the main thread.
    mutex mtx;
    bool sent = false;
    condition_variable cv;
    thread th([&] () {
        TEST_CLIENT.sendCommand(command);
        {
            lock_guard lck(mtx);
            sent = true;
        }
        cv.notify_one();
    });

    for (;;) {
        ControlledDhcpv6Srv::getInstance()->getIOService()->poll();
        unique_lock lck(mtx);
        if (cv.wait_for(lck, 1ms, [&] () { return (sent); })) {
            break;
        }
    }
    th.join();

    ControlledDhcpv6Srv::getInstance()->getIOService()->poll();
    string response;
    TEST_CLIENT.getResponse(response);
    ControlledDhcpv6Srv::getInstance()->getIOService()->poll();
    TEST_CLIENT.disconnectFromServer();
    ControlledDhcpv6Srv::getInstance()->getIOService()->poll();

    return 0;
}

}  // extern "C"
