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
#include <dhcp/pgsql/pgsql_cb_impl.h>
#include <dhcp/pgsql/pgsql_cb_dhcp4.h>
#include <dhcpsrv/subnet.h>
#include <dhcpsrv/host.h>
#include <pgsql/pgsql_exchange.h>

#include <log/logger_support.h>
#include <process/daemon.h>
#include <exceptions/exceptions.h>

#include <cstdint>
#include <cstddef>
#include <string>
#include <vector>
#include <map>
#include <utility>
#include <iostream>

using namespace isc::asiolink;
using namespace isc::db;
using namespace isc::dhcp;
using namespace isc::util;

extern "C" void pgmock_load_bytes(const uint8_t* data, size_t size);

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
    pgmock_load_bytes(data, size);

    DbCallback db_cb;
    size_t index = 0;

    // Prepare tags
    std::set<std::string> tags;
    std::string tag = fdp.ConsumeRandomLengthString(16);
    if (tag.size() == 0) {
        tag = "default-tag";
    }
    tags.insert(tag);

    // Preparer DatabaseConnection parameter map
    DatabaseConnection::ParameterMap params;
    params["name"] = fdp.ConsumeRandomLengthString(32);
    params[fdp.ConsumeRandomLengthString(32)] = fdp.ConsumeRandomLengthString(32);
    params[fdp.ConsumeRandomLengthString(32)] = fdp.ConsumeRandomLengthString(32);
    params[fdp.ConsumeRandomLengthString(32)] = fdp.ConsumeRandomLengthString(32);

    // Prepare Binding array
    PsqlBindArray binds;
    binds.add(fdp.ConsumeRandomLengthString(256));
    binds.add(fdp.ConsumeRandomLengthString(256));
    binds.add(fdp.ConsumeRandomLengthString(256));

    // Prepare server selector
    ServerSelector selector = ServerSelector::UNASSIGNED();
    try {
        switch (fdp.ConsumeIntegralInRange<int>(0, 3)) {
            case 0:
                selector = ServerSelector::ALL();
                break;
            case 1:
                selector = ServerSelector::ONE(tag);
                break;
            case 2:
                selector = ServerSelector::MULTIPLE(tags);
                break;
            case 3:
                selector = ServerSelector::ANY();
                break;
        }
    } catch (const isc::Exception&) {
        // Slient exceptions use default unassigned server selector
    }

    try {
        // Prepare PgSql backend
        PgSqlConfigBackendImpl backend(fdp.ConsumeRandomLengthString(32), params, db_cb, index);
        PgSqlConfigBackendDHCPv4 dhcp_backend(params);

        // Target selectQuery
        try {
            backend.selectQuery(0, binds, PgSqlConnection::ConsumeResultRowFun([](PgSqlResult&, int) {}));
        } catch (const isc::Exception&) {
            // Slient exceptions
        }

        // Target insertQuery
        try {
            backend.insertQuery(0, binds);
        } catch (const isc::Exception&) {
            // Slient exceptions
        }

        // Target updateDeleteQuery
        try {
            backend.updateDeleteQuery(0, binds);
        } catch (const isc::Exception&) {
            // Slient exceptions
        }

        // Target upper level getGlobalParameter4
        try {
            dhcp_backend.getGlobalParameter4(selector, fdp.ConsumeRandomLengthString(32));
        } catch (const isc::Exception&) {
            // Slient exceptions
        }

        // Target upper level getAllSubnets4
        try {
            dhcp_backend.getAllSubnets4(selector);
        } catch (const isc::Exception&) {
            // Slient exceptions
        }

        // Target upper level createUpdateSubnet4
        try {
            IOAddress address(fdp.ConsumeRandomLengthString(15));
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

            SubnetID sid = static_cast<SubnetID>(fdp.ConsumeIntegral<uint32_t>());

            Subnet4Ptr subnet(Subnet4::create(address, fdp.ConsumeIntegralInRange(0, 32), t1, t2, t3, sid));
            dhcp_backend.createUpdateSubnet4(selector, subnet);
        } catch (const isc::Exception&) {
            // Slient exceptions
        }

        // Target upper level deleteSubnet4
        try {
            dhcp_backend.deleteSubnet4(selector, fdp.ConsumeRandomLengthString(32));
        } catch (const isc::Exception&) {
            // Slient exceptions
        }

        // Target upper level createUpdateOption4
        try {
            OptionBuffer opt_buf;
            OptionPtr opt(new Option(Option::V4, 0, opt_buf));
            OptionDescriptorPtr opt_desc(new OptionDescriptor(opt, true, true));

            std::string opt_space = "dhcp4";
            std::string opt_name  = fdp.ConsumeRandomLengthString(32);
            if (opt_name.empty()) {
                opt_name = "fuzz-opt";
            }

            dhcp_backend.createUpdateOption4(selector, opt_name, opt_desc);
        } catch (const isc::Exception&) {
            // Slient exceptions
        }
    } catch (const isc::Exception& e) {
        // Slient exceptions
    }

    return 0;
}
