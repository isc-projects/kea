// Copyright (C) 2025 Ada Logcis Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
#include <config.h>
#include <fuzzer/FuzzedDataProvider.h>

#include <dhcp/dhcp4.h>
#include <dhcp/pkt4.h>
#include <dhcp/libdhcp++.h>
#include <dhcp4/ctrl_dhcp4_srv.h>
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

#include "helper_func.h"

using namespace isc::dhcp;
using namespace isc::hooks;
using namespace isc::util;

extern "C" int buffer4_receive(CalloutHandle& handle);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 236) {
        // package size requires at least 236 bytes
        return 0;
    }

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

    Pkt4Ptr pkt;

    // Package parsing
    try {
        // Add fixed magic cookie and correct hardware address
        std::vector<uint8_t> buf(data, data + size);
        if (size >= 240) {
            // Max hardware address length is 20
            buf[2] = 20;

            // Magic cookie fixed value 0x63825363
            buf[236] = 0x63;
            buf[237] = 0x82;
            buf[238] = 0x53;
            buf[239] = 0x63;
        }

        pkt = Pkt4Ptr(new Pkt4(buf.data(), buf.size()));
        pkt->unpack();
    } catch (...) {
        // Early exit if package parsing failed.
        return 0;
    }

    // Configure random value in packet
    FuzzedDataProvider fdp(data, size);
    uint8_t typeChoice = fdp.ConsumeIntegralInRange<uint8_t>(0, 8);
    pkt->setType(static_cast<DHCPMessageType>(typeChoice));

    CalloutHandlePtr handle = getCalloutHandle(pkt);

    // Fuzz buffer4_receive
    try {
        handle = getCalloutHandle(pkt);
        handle->setArgument("query4", pkt);
        buffer4_receive(*handle);
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
