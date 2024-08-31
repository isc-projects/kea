// Copyright (C) 2018-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <netconf/netconf_controller.h>
#include <netconf/netconf_process.h>
#include <netconf/parser_context.h>
#include <process/cfgrpt/config_report.h>

#include <signal.h>

using namespace isc::process;

namespace isc {
namespace netconf {

/// @brief Defines the application name, this is passed into base class
/// it may be used to locate configuration data and appears in log statement.
const char* NetconfController::netconf_app_name_ = "Netconf";

/// @brief Defines the executable name. This is passed into the base class
const char* NetconfController::netconf_bin_name_ = "kea-netconf";

DControllerBasePtr&
NetconfController::instance() {
    // If the instance hasn't been created yet, create it.  Note this method
    // must use the base class singleton instance methods.
    if (!getController()) {
        DControllerBasePtr controller_ptr(new NetconfController());
        setController(controller_ptr);
    }

    return (getController());
}

void
NetconfController::processSignal(int signum) {
    if (signum == SIGHUP) {
        LOG_WARN(dctl_logger, DCTL_UNSUPPORTED_SIGNAL).arg(signum);
    } else {
        DControllerBase::processSignal(signum);
    }
}

DProcessBase*
NetconfController::createProcess() {
    // Instantiate and return an instance of the D2 application process. Note
    // that the process is passed the controller's io_service.
    return (new NetconfProcess(getAppName().c_str(), getIOService()));
}

isc::data::ConstElementPtr
NetconfController::parseFile(string const& name) {
    ParserContext parser;
    return (parser.parseFile(name, ParserContext::PARSER_NETCONF));
}

NetconfController::NetconfController()
    : DControllerBase(netconf_app_name_, netconf_bin_name_) {
}

NetconfProcessPtr
NetconfController::getNetconfProcess() {
    return (boost::dynamic_pointer_cast<NetconfProcess>(getProcess()));
}

}  // namespace netconf
}  // namespace isc
