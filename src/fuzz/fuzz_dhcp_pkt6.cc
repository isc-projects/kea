// Copyright (C) 2025 Ada Logcis Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
#include <config.h>
#include <fuzzer/FuzzedDataProvider.h>

#include <dhcp/pkt6.h>
#include <dhcp/libdhcp++.h>
#include <dhcp/option.h>
#include <dhcp6/ctrl_dhcp6_srv.h>
#include <dhcp/option_vendor_class.h>
#include <log/logger_support.h>
#include <process/daemon.h>
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

static thread_local FuzzedDataProvider* fdp = nullptr;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 236) {
        // package size requires at least 236 bytes
        return 0;
    }

    // Randomly enable validatePath checking
    fdp = new FuzzedDataProvider(data, size);
    isc::util::file::PathChecker::enableEnforcement(fdp->ConsumeBool());

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

    // Create temporary configuration file
    std::string path = fuzz::writeTempConfig(true);
    if (path.empty()) {
        // Early exit if configuration file creation failed
        fuzz::deleteTempFile(path);
        return 0;
    }

    OptionCollection options;
    std::unique_ptr<ControlledDhcpv6Srv> srv;
    std::vector<uint8_t> buf(data, data + size);

    try {
        Pkt6Ptr pkt = Pkt6Ptr(new Pkt6(data, size));
        pkt->toText();
        pkt->getType();
        pkt->getTransid();
        pkt->unpack();
        pkt->pack();
        pkt->getMAC(fdp->ConsumeIntegral<uint32_t>());
        pkt->getName(fdp->ConsumeIntegral<uint8_t>());
        pkt->getLabel();
    } catch (...) {}

    // OptionVendor parsing
    try {
        OptionBuffer buf(data, data + size);
        OptionVendorClassPtr vendor_class;
        vendor_class = OptionVendorClassPtr(new OptionVendorClass(Option::V6,
            buf.begin(),
            buf.end()));
    }catch(...){}

    try {
        // Package parsing
        Pkt6Ptr pkt = Pkt6Ptr(new Pkt6(data, size));
        pkt->toText();
        pkt->getType();
        pkt->getTransid();

        // Option parsing
        LibDHCP::unpackOptions6(buf, DHCP6_OPTION_SPACE, options);
        for (auto& kv : options) {
            auto opt = kv.second;
            if (!opt) {
                continue;
            }
            opt->getType();
            opt->toText();
        }

        // Server initialisation
        srv.reset(new ControlledDhcpv6Srv());
        srv->init(path);

        // Process packet
        if (srv) {
            srv->processPacket(pkt);
            srv->processDhcp6Query(pkt);
        }
    } catch (const isc::Exception& e) {
        // Slient exceptions
    }

    srv.reset();

    // Remove temp configuration file
    fuzz::deleteTempFile(path);
    delete fdp;
    return 0;
}
