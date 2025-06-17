// Copyright (C) 2024-2025 Internet Systems Consortium, Inc. ("ISC")
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

#include <cassert>
#include <util/filesystem.h>
#include <string>

using namespace isc;
using namespace isc::config;
using namespace isc::data;
using namespace isc::dhcp;
using namespace isc::process;
using namespace std;

namespace {

static pid_t const PID(getpid());
static string const PID_STR(to_string(PID));
static string const KEA_DHCP6_CONF(KEA_FUZZ_DIR() + "/kea-dhcp6-" + PID_STR + ".conf");

}  // namespace

extern "C" {

int
LLVMFuzzerInitialize() {
    static bool initialized(DoInitialization());
    assert(initialized);

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
    // Create the config file.
    string const string_config(reinterpret_cast<char const*>(data), size);
    writeToFile(KEA_DHCP6_CONF, string_config);

    // Configure the server.
    ControlledDhcpv6Srv server;
    try {
        server.init(KEA_DHCP6_CONF);
    } catch (BadValue const&) {
    } catch (Dhcp6ParseError const&) {
    }

    return 0;
}

}  // extern "C"
