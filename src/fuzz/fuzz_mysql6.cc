// Copyright (C) 2025 Ada Logcis Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
#include <config.h>
#include <fuzzer/FuzzedDataProvider.h>

#include <asiolink/io_address.h>
#include <database/database_connection.h>
#include <database/server_selector.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/host.h>
#include <dhcpsrv/cfg_option.h>

#include <log/logger_support.h>
#include <process/daemon.h>
#include <exceptions/exceptions.h>

#include <mysql_cb_impl.h>
#include <mysql_cb_dhcp6.h>

#include <cstdint>
#include <cstddef>
#include <string>
#include <set>
#include <vector>
#include <map>
#include <utility>
#include <iostream>

using namespace isc::asiolink;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::util;

extern "C" void mysqlmock_load_bytes(const uint8_t* data, size_t size);

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
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

    FuzzedDataProvider fdp(data, size);
    mysqlmock_load_bytes(data, size);
    DbCallback db_cb;

    // Prepare tags
    std::set<std::string> tags;
    std::string tag = fdp.ConsumeRandomLengthString(16);
    if (tag.empty()) {
        tag = "default-tag";
    }
    tags.insert(tag);

    // Prepare DatabaseConnection parameter maps
    DatabaseConnection::ParameterMap params;
    std::string dbname = fdp.ConsumeRandomLengthString(16);
    if (dbname.empty()) {
        dbname = "kea_fuzz";
    }
    params["name"] = dbname;
    params[fdp.ConsumeRandomLengthString(16)] = fdp.ConsumeRandomLengthString(16);
    params[fdp.ConsumeRandomLengthString(16)] = fdp.ConsumeRandomLengthString(16);

    // Prepare server selector
    ServerSelector selector = ServerSelector::UNASSIGNED();
    try {
        switch (fdp.ConsumeIntegralInRange<int>(0, 3)) {
            case 0: selector = ServerSelector::ALL(); break;
            case 1: selector = ServerSelector::ONE(tag); break;
            case 2: selector = ServerSelector::MULTIPLE(tags); break;
            case 3: selector = ServerSelector::ANY(); break;
        }
    } catch (const isc::Exception&) {
        // Silent exceptions use default UNASSIGNED
    }

    try {
        MySqlConfigBackendImpl backend("v6", params, db_cb);
        MySqlConfigBackendDHCPv6 dhcp_backend(params);

        // Target getGlobalParameter6
        try {
            dhcp_backend.getGlobalParameter6(selector, fdp.ConsumeRandomLengthString(32));
        } catch (const isc::Exception& e) {
            // Slient exceptions
        }

        // Target getAllSubnets6
        try {
            dhcp_backend.getAllSubnets6(selector);
        } catch (const isc::Exception& e) {
            // Slient exceptions
        }

        // Target createUpdateSubnet6
        try {
            IOAddress address("::1");

            uint32_t a1 = fdp.ConsumeIntegral<uint32_t>();
            uint32_t b1 = fdp.ConsumeIntegral<uint32_t>();
            uint32_t c1 = fdp.ConsumeIntegral<uint32_t>();
            Triplet<uint32_t> t1(a1, b1, c1);

            uint32_t a2 = fdp.ConsumeIntegral<uint32_t>();
            uint32_t b2 = fdp.ConsumeIntegral<uint32_t>();
            uint32_t c2 = fdp.ConsumeIntegral<uint32_t>();
            Triplet<uint32_t> t2(a2, b2, c2);

            uint32_t a3 = fdp.ConsumeIntegral<uint32_t>();
            uint32_t b3 = fdp.ConsumeIntegral<uint32_t>();
            uint32_t c3 = fdp.ConsumeIntegral<uint32_t>();
            Triplet<uint32_t> t3(a3, b3, c3);

            uint32_t a4 = fdp.ConsumeIntegral<uint32_t>();
            uint32_t b4 = fdp.ConsumeIntegral<uint32_t>();
            uint32_t c4 = fdp.ConsumeIntegral<uint32_t>();
            Triplet<uint32_t> t4(a4, b4, c4);

            SubnetID sid = static_cast<SubnetID>(fdp.ConsumeIntegralInRange<uint32_t>(1, UINT32_MAX));
            Subnet6Ptr subnet(Subnet6::create(address,
                                              fdp.ConsumeIntegralInRange(0, 32),
                                              t1, t2, t3, t4, sid));
            dhcp_backend.createUpdateSubnet6(selector, subnet);
        } catch (const isc::Exception& e) {
            // Slient exceptions
        }

        // Target deleteSubnet6
        try {
            dhcp_backend.deleteSubnet6(selector, fdp.ConsumeRandomLengthString(32));
        } catch (const isc::Exception& e) {
            // Slient exceptions
        }

        // Target createUpdateOption6
        try {
            OptionBuffer opt_buf;
            OptionPtr opt(new Option(Option::V4, fdp.ConsumeIntegralInRange<uint16_t>(1, 254), opt_buf));
            OptionDescriptorPtr opt_desc(new OptionDescriptor(opt, true, true));

            std::string opt_space = "dhcp4";
            std::string opt_name  = fdp.ConsumeRandomLengthString(32);
            if (opt_name.empty()) {
                opt_name = "fuzz-opt";
            }

            dhcp_backend.createUpdateOption6(selector, opt_name, opt_desc);
        } catch (const isc::Exception& e) {
            // Slient exceptions
        }
    } catch (const isc::Exception&) {
        // Silent top-level exceptions
    }

    return 0;
}
