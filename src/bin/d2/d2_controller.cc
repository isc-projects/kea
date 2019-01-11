// Copyright (C) 2013-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <config/command_mgr.h>
#include <d2/d2_controller.h>
#include <d2/d2_process.h>
#include <d2/parser_context.h>

#include <stdlib.h>

using namespace isc::config;
using namespace isc::process;

namespace isc {
namespace d2 {

/// @brief Defines the application name, this is passed into base class
/// it may be used to locate configuration data and appears in log statement.
const char* D2Controller::d2_app_name_ = "DhcpDdns";

/// @brief Defines the executable name. This is passed into the base class
const char* D2Controller::d2_bin_name_ = "kea-dhcp-ddns";

DControllerBasePtr&
D2Controller::instance() {
    // If the instance hasn't been created yet, create it.  Note this method
    // must use the base class singleton instance methods.
    if (!getController()) {
        DControllerBasePtr controller_ptr(new D2Controller());
        setController(controller_ptr);
    }

    return (getController());
}

DProcessBase* D2Controller::createProcess() {
    // Instantiate and return an instance of the D2 application process. Note
    // that the process is passed the controller's io_service.
    return (new D2Process(getAppName().c_str(), getIOService()));
}

D2Controller::D2Controller()
    : DControllerBase(d2_app_name_, d2_bin_name_) {
}

void
D2Controller::registerCommands() {
    // These are the commands always supported by the D2 server.
    // Please keep the list in alphabetic order.
    CommandMgr::instance().registerCommand(BUILD_REPORT_COMMAND,
        boost::bind(&D2Controller::buildReportHandler, this, _1, _2));

    CommandMgr::instance().registerCommand(CONFIG_GET_COMMAND,
        boost::bind(&D2Controller::configGetHandler, this, _1, _2));

    CommandMgr::instance().registerCommand(CONFIG_SET_COMMAND,
        boost::bind(&D2Controller::configSetHandler, this, _1, _2));

    CommandMgr::instance().registerCommand(CONFIG_TEST_COMMAND,
        boost::bind(&D2Controller::configTestHandler, this, _1, _2));

    CommandMgr::instance().registerCommand(CONFIG_WRITE_COMMAND,
        boost::bind(&D2Controller::configWriteHandler, this, _1, _2));

    CommandMgr::instance().registerCommand(SHUT_DOWN_COMMAND,
        boost::bind(&D2Controller::shutdownHandler, this, _1, _2));

    CommandMgr::instance().registerCommand(VERSION_GET_COMMAND,
        boost::bind(&D2Controller::versionGetHandler, this, _1, _2));
}

void
D2Controller::deregisterCommands() {
    try {
        // Close the command socket (if it exists).
        CommandMgr::instance().closeCommandSocket();

        // Deregister any registered commands (please keep in alphabetic order)
        CommandMgr::instance().deregisterCommand(BUILD_REPORT_COMMAND);
        CommandMgr::instance().deregisterCommand(CONFIG_GET_COMMAND);
        CommandMgr::instance().deregisterCommand(CONFIG_SET_COMMAND);
        CommandMgr::instance().deregisterCommand(CONFIG_TEST_COMMAND);
        CommandMgr::instance().deregisterCommand(CONFIG_WRITE_COMMAND);
        CommandMgr::instance().deregisterCommand(SHUT_DOWN_COMMAND);
        CommandMgr::instance().deregisterCommand(VERSION_GET_COMMAND);

    } catch (...) {
        // What to do? Simply ignore...
    }
}



isc::data::ConstElementPtr
D2Controller::parseFile(const std::string& file_name) {
    isc::data::ConstElementPtr elements;

    // Read contents of the file and parse it as JSON
    D2ParserContext parser;
    elements = parser.parseFile(file_name, D2ParserContext::PARSER_DHCPDDNS);
    if (!elements) {
        isc_throw(isc::BadValue, "no configuration found in file");
    }

    return (elements);
}

D2Controller::~D2Controller() {
}

std::string
D2Controller::getVersionAddendum() {
    std::stringstream stream;
    // Currently the only dependency D2 adds to base is cryptolink
    stream << isc::cryptolink::CryptoLink::getVersion() << std::endl;
    return (stream.str());

}

}; // end namespace isc::d2
}; // end namespace isc
