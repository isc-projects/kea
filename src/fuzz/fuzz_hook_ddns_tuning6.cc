// Copyright (C) 2025-2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Developed by AdaLogics under contract to ISC.

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

extern "C" int ddns6_update(CalloutHandle& handle);

namespace isc {
    namespace dhcp {
        class MyDhcpv6Srv : public ControlledDhcpv6Srv {
            public:
                void fuzz_classifyPacket(const Pkt6Ptr& pkt) {
                    classifyPacket(pkt);
                }

                ConstSubnet6Ptr fuzz_selectSubnet(const Pkt6Ptr& question, bool& drop) {
                    return selectSubnet(question, drop);
                }
        };
    }
}

extern "C" int LLVMFuzzerTestOneInput(const uint8_t *data, size_t size) {
    if (size < 236) {
        // package size requires at least 236 bytes
        return 0;
    }

    // Disable validatePath checking to allow writing configuration file to /tmp
    isc::util::file::PathChecker::enableEnforcement(false);

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

    // Creating temp config file
    std::string path = fuzz::writeTempConfig(false);
    std::unique_ptr<void, void(*)(void*)> p(static_cast<void*>(&path), [](void* f) { fuzz::deleteTempFile(*reinterpret_cast<std::string*>(f)); });
    if (path.empty()) {
        // Early exit if configuration file creation failed
        return 0;
    }

    // Creating temp lease file
    std::string lease_path = fuzz::writeTempLease(false);
    std::unique_ptr<void, void(*)(void*)> pl(static_cast<void*>(&lease_path), [](void* f) { fuzz::deleteTempFile(*reinterpret_cast<std::string*>(f)); });

    Pkt6Ptr pkt;
    std::unique_ptr<MyDhcpv6Srv> srv;

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

    // Server initialisation
    try {
        srv.reset(new MyDhcpv6Srv());
        srv->init(path);
    } catch (...) {
        // Early exit if server initialisation failed.
        return 0;
    }

    if (!srv) {
        // Early exit if server initialisation failed.
        return 0;
    }

    // Call classifyPacket for packet checking
    try {
        srv->fuzz_classifyPacket(pkt);
    } catch (const isc::Exception& e) {
        // Silent exceptions
    } catch (const std::exception&) {
        // Silent exceptions
    }

    // Prepare client context
    CalloutHandlePtr handle = getCalloutHandle(pkt);
    AllocEngine::ClientContext6 ctx;

    // Call earlyGHRLookup
    try {
        srv->earlyGHRLookup(pkt, ctx);
    } catch (const isc::Exception& e) {
        // Silent exceptions
    } catch (const std::exception&) {
        // Silent exceptions
    }

    // Call select subnet
    try {
        bool drop = false;
        ctx.subnet_ = srv->fuzz_selectSubnet(pkt, drop);
    } catch (const isc::Exception& e) {
        // Silent exceptions
    } catch (const std::exception&) {
        // Silent exceptions
    }

    // Fuzz ddns6_update
    try {
        Pkt6Ptr rsp;
        handle = getCalloutHandle(pkt);
        handle->setArgument("query6", pkt);
        handle->setArgument("response6", rsp);
        handle->setArgument("hostname", fdp.ConsumeRandomLengthString(32));
        handle->setArgument("fwd-update", fdp.ConsumeBool());
        handle->setArgument("rev-update", fdp.ConsumeBool());
        handle->setArgument("ddns-params", ctx.getDdnsParams());
        handle->setArgument("subnet6", ctx.subnet_);
        ddns6_update(*handle);
    } catch (const isc::Exception& e) {
        // Silent exceptions
    } catch (const std::exception&) {
        // Silent exceptions
    }

    // Clean up to avoid mem leak
    if (handle) {
        handle->deleteAllArguments();
    }

    srv.reset();

    return 0;
}
