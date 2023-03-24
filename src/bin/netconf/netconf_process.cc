// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <asiolink/asio_wrapper.h>
#include <asiolink/io_address.h>
#include <asiolink/io_error.h>
#include <cc/command_interpreter.h>
#include <config/timeouts.h>
#include <netconf/netconf.h>
#include <netconf/netconf_controller.h>
#include <netconf/netconf_log.h>
#include <netconf/netconf_process.h>

using namespace isc::asiolink;
using namespace isc::config;
using namespace isc::data;
using namespace isc::http;
using namespace isc::process;

namespace isc {
namespace netconf {

NetconfProcess::NetconfProcess(const char* name,
                               const asiolink::IOServicePtr& io_service)
    : DProcessBase(name, io_service, DCfgMgrBasePtr(new NetconfCfgMgr())) {
}

void
NetconfProcess::init() {
}

void
NetconfProcess::run() {
    LOG_INFO(netconf_logger, NETCONF_STARTED).arg(VERSION);

    try {
        // Call init.
        agent_.init(getNetconfCfgMgr());

        // Let's process incoming data or expiring timers in a loop until
        // shutdown condition is detected.
        while (!shouldShutdown()) {
            runIO();
        }
        stopIOService();

    } catch (const std::exception& ex) {
        LOG_FATAL(netconf_logger, NETCONF_FAILED).arg(ex.what());
        try {
            stopIOService();
        } catch (...) {
            // Ignore double errors
        }
        isc_throw(DProcessBaseError,
                  "Process run method failed: " << ex.what());
    }

    LOG_DEBUG(netconf_logger, isc::log::DBGLVL_START_SHUT, NETCONF_RUN_EXIT);
}

size_t
NetconfProcess::runIO() {
    size_t cnt = getIoService()->get_io_service().poll();
    if (!cnt) {
        cnt = getIoService()->get_io_service().run_one();
    }
    return (cnt);
}

isc::data::ConstElementPtr
NetconfProcess::shutdown(isc::data::ConstElementPtr /*args*/) {
    setShutdownFlag(true);
    return (isc::config::createAnswer(CONTROL_RESULT_SUCCESS, "Netconf is shutting down"));
}

isc::data::ConstElementPtr
NetconfProcess::configure(isc::data::ConstElementPtr config_set,
                          bool check_only) {
    ConstElementPtr answer =
        getCfgMgr()->simpleParseConfig(config_set, check_only);
    int rcode = 0;
    config::parseAnswer(rcode, answer);
    return (answer);
}

NetconfCfgMgrPtr
NetconfProcess::getNetconfCfgMgr() {
    return (boost::dynamic_pointer_cast<NetconfCfgMgr>(getCfgMgr()));
}

}  // namespace netconf
}  // namespace isc
