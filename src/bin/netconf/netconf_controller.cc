// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <netconf/netconf_controller.h>
#include <netconf/netconf_process.h>
#ifdef notyet
#include <netconf/parser_context.h>
#endif

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

DProcessBase*
NetconfController::createProcess() {
    // Instantiate and return an instance of the D2 application process. Note
    // that the process is passed the controller's io_service.
    return (new NetconfProcess(getAppName().c_str(), getIOService()));
}

isc::data::ConstElementPtr
NetconfController::parseFile(const std::string& name) {
#ifdef notyet
    ParserContext parser;
    return (parser.parseFile(name, ParserContext::PARSER_NETCONF));
#else
    isc_throw(NotImplemented, "NetconfController::parseFile("
              << name << ")");
#endif
}

NetconfController::NetconfController()
    : DControllerBase(netconf_app_name_, netconf_bin_name_) {
}

NetconfController::~NetconfController() {
}

NetconfProcessPtr
NetconfController::getNetconfProcess() {
    return (boost::dynamic_pointer_cast<NetconfProcess>(getProcess()));
}

} // namespace isc::netconf
} // namespace isc
