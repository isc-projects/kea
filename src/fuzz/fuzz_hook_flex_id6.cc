// Copyright (C) 2025 Ada Logcis Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
#include <config.h>
#include <fuzzer/FuzzedDataProvider.h>

#include <dhcp/dhcp6.h>
#include <dhcp/pkt6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp6/ctrl_dhcp6_srv.h>
#include <dhcpsrv/callout_handle_store.h>
#include <log/logger_support.h>
#include <util/filesystem.h>

#include <cstddef>
#include <cstdint>
#include <vector>
#include <list>
#include <memory>
#include <iostream>
#include <filesystem>
#include <fstream>
#include <string>
#include <cstdio>
#include <cstdlib>

#include "helper_func.h"

using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::util;

extern "C" int pkt6_receive(CalloutHandle& handle);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 236) {
        // package size requires at least 236 bytes
        return 0;
    }

    // Force DUID file to /tmp
    setenv("KEA_DHCP_DATA_DIR", "/tmp", 1);

    // Initialise logging
    setenv("KEA_LOGGER_DESTINATION", "/dev/null", 0);
    setenv("KEA_LOCKFILE_DIR", "/tmp", 0);
    setenv("KEA_PIDFILE_DIR", "/tmp", 0);
    setenv("KEA_LFC_EXECUTABLE", "/bin/true", 0);
    try {
        isc::log::initLogger("fuzzer");
        isc::process::Daemon::loggerInit("fuzzer", false);
        isc::process::Daemon::setDefaultLoggerName("fuzzer");
    } catch (...) {
        // Early exit if logging initialisation failed
        return 0;
    }

    Pkt6Ptr pkt;

    // Package parsing
    try {
        pkt = Pkt6Ptr(new Pkt6(data, size));
        pkt->unpack();
    } catch (...) {
        // Early exit if package parsing failed.
        return 0;
    }

    // Configure random value in packet
    FuzzedDataProvider fdp(data, size);
    uint8_t typeChoice = fdp.ConsumeIntegralInRange<uint8_t>(0, 37);
    pkt->setType(static_cast<DHCPv6MessageType>(typeChoice));

    CalloutHandlePtr handle = getCalloutHandle(pkt);

    // Fuzz pkt6_receive
    try {
        handle->setArgument("query6", pkt);
        pkt6_receive(*handle);
    } catch (const isc::Exception& e) {
        // Slient exceptions
    } catch (const boost::exception& e) {
        // Slient exceptions
    }

    // Clean handle to avoid mem leak
    if (handle) {
        handle->deleteAllArguments();
    }

    return 0;
}
