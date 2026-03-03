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
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/lease_mgr_factory.h>
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

extern "C" int subnet4_select(CalloutHandle& handle);
extern "C" int lease4_release(CalloutHandle& handle);
extern "C" int lease4_decline(CalloutHandle& handle);

namespace isc {
    namespace dhcp {
        class MyDhcpv4Srv : public ControlledDhcpv4Srv {
            public:
                void fuzz_classifyPacket(const Pkt4Ptr& pkt) {
                    classifyPacket(pkt);
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
    std::string path = fuzz::writeTempConfig(true);
    if (path.empty()) {
        // Early exit if configuration file creation failed
        fuzz::deleteTempFile(path);
        return 0;
    }

    // Creating temp lease file
    std::string lease_path = fuzz::writeTempLease(true);

    Pkt4Ptr pkt;
    std::unique_ptr<MyDhcpv4Srv> srv;

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

    // Server initialisation
    try {
        srv.reset(new MyDhcpv4Srv());
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
        // Slient exceptions
    } catch (const boost::exception& e) {
        // Slient exceptions
    }

    // Prepare client context
    CalloutHandlePtr handle = nullptr;
    AllocEngine::ClientContext4Ptr ctx(new AllocEngine::ClientContext4());

    // Call earlyGHRLookup
    try {
        srv->earlyGHRLookup(pkt, ctx);
    } catch (const isc::Exception& e) {
        // Slient exceptions
    } catch (const boost::exception& e) {
        // Slient exceptions
    }

    // Fuzz subnet4_select
    try {
        handle = getCalloutHandle(pkt);
        Pkt4Ptr rsp;
        CfgMgr& cfgmgr = CfgMgr::instance();
        handle = getCalloutHandle(pkt);
        handle->setArgument("query4", pkt);
        handle->setArgument("subnet4collection",
                            cfgmgr.getCurrentCfg()->getCfgSubnets4()->getAll());
        if (!ctx) {
            ctx.reset(new AllocEngine::ClientContext4());
        }
        if (ctx) {
            handle->setArgument("subnet4", ctx->subnet_);
        }
        subnet4_select(*handle);
    } catch (const isc::Exception& e) {
        // Slient exceptions
    } catch (const boost::exception& e) {
        // Slient exceptions
    }

    // Clean handle to avoid mem leak
    if (handle) {
        handle->deleteAllArguments();
    }

    // Call lease4_release
    try {
        handle = getCalloutHandle(pkt);
        uint8_t mac_addr[6];
        for (size_t i = 0; i < 6; ++i) {
            mac_addr[i] = fdp.ConsumeIntegral<uint8_t>();
        }
        HWAddr hw(mac_addr, sizeof(mac_addr), HTYPE_ETHER);
        Lease4Collection leases = LeaseMgrFactory::instance().getLease4(hw);
        handle->setArgument("leases4", leases);
        handle->setArgument("query4", pkt);

        lease4_release(*handle);
    } catch (const isc::Exception& e) {
        // Slient exceptions
    } catch (const boost::exception& e) {
        // Slient exceptions
    }

    // Clean up to avoid mem leak
    if (handle) {
        handle->deleteAllArguments();
    }

    // Call lease4_decline
    try {
        uint8_t mac_addr[6];
        for (size_t i = 0; i < 6; ++i) {
            mac_addr[i] = fdp.ConsumeIntegral<uint8_t>();
        }
        HWAddr hw(mac_addr, sizeof(mac_addr), HTYPE_ETHER);
        Lease4Collection leases = LeaseMgrFactory::instance().getLease4(hw);
        handle->setArgument("leases4", leases);
        handle->setArgument("query4", pkt);

        lease4_decline(*handle);
    } catch (const isc::Exception& e) {
        // Slient exceptions
    } catch (const boost::exception& e) {
        // Slient exceptions
    }

    // Clean up to avoid mem leak
    if (handle) {
        handle->deleteAllArguments();
    }

    srv.reset();

    // Remove temp files
    fuzz::deleteTempFile(path);
    fuzz::deleteTempFile(lease_path);
    return 0;
}
