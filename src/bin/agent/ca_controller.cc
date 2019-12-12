// Copyright (C) 2016-2019 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <agent/ca_controller.h>
#include <agent/ca_process.h>
#include <agent/ca_command_mgr.h>
#include <agent/parser_context.h>
#include <boost/bind.hpp>

using namespace isc::process;

namespace isc {
namespace agent {

/// @brief Defines the application name, this is passed into base class
/// it may be used to locate configuration data and appears in log statement.
const char* CtrlAgentController::agent_app_name_ = "Control-agent";

/// @brief Defines the executable name. This is passed into the base class
const char* CtrlAgentController::agent_bin_name_ = "kea-ctrl-agent";

DControllerBasePtr&
CtrlAgentController::instance() {
    // If the instance hasn't been created yet, create it.  Note this method
    // must use the base class singleton instance methods.
    if (!getController()) {
        DControllerBasePtr controller_ptr(new CtrlAgentController());
        setController(controller_ptr);
    }

    return (getController());
}

DProcessBase*
CtrlAgentController::createProcess() {
    // Instantiate and return an instance of the D2 application process. Note
    // that the process is passed the controller's io_service.
    return (new CtrlAgentProcess(getAppName().c_str(), getIOService()));
}

isc::data::ConstElementPtr
CtrlAgentController::parseFile(const std::string& name) {
    ParserContext parser;
    return (parser.parseFile(name, ParserContext::PARSER_AGENT));
}

void
CtrlAgentController::registerCommands() {
    CtrlAgentCommandMgr::instance().registerCommand(BUILD_REPORT_COMMAND,
        boost::bind(&DControllerBase::buildReportHandler, this, _1, _2));

    CtrlAgentCommandMgr::instance().registerCommand(CONFIG_GET_COMMAND,
        boost::bind(&DControllerBase::configGetHandler, this, _1, _2));

    CtrlAgentCommandMgr::instance().registerCommand(CONFIG_RELOAD_COMMAND,
        boost::bind(&DControllerBase::configReloadHandler, this, _1, _2));

    CtrlAgentCommandMgr::instance().registerCommand(CONFIG_SET_COMMAND,
        boost::bind(&DControllerBase::configSetHandler, this, _1, _2));

    CtrlAgentCommandMgr::instance().registerCommand(CONFIG_TEST_COMMAND,
        boost::bind(&DControllerBase::configTestHandler, this, _1, _2));

    CtrlAgentCommandMgr::instance().registerCommand(CONFIG_WRITE_COMMAND,
        boost::bind(&DControllerBase::configWriteHandler, this, _1, _2));

    CtrlAgentCommandMgr::instance().registerCommand(SHUT_DOWN_COMMAND,
        boost::bind(&DControllerBase::shutdownHandler, this, _1, _2));

    CtrlAgentCommandMgr::instance().registerCommand(STATUS_GET_COMMAND,
        boost::bind(&DControllerBase::statusGetHandler, this, _1, _2));

    CtrlAgentCommandMgr::instance().registerCommand(VERSION_GET_COMMAND,
        boost::bind(&DControllerBase::versionGetHandler, this, _1, _2));
}

void
CtrlAgentController::deregisterCommands() {
    CtrlAgentCommandMgr::instance().deregisterCommand(BUILD_REPORT_COMMAND);
    CtrlAgentCommandMgr::instance().deregisterCommand(CONFIG_GET_COMMAND);
    CtrlAgentCommandMgr::instance().deregisterCommand(CONFIG_RELOAD_COMMAND);
    CtrlAgentCommandMgr::instance().deregisterCommand(CONFIG_SET_COMMAND);
    CtrlAgentCommandMgr::instance().deregisterCommand(CONFIG_TEST_COMMAND);
    CtrlAgentCommandMgr::instance().deregisterCommand(CONFIG_WRITE_COMMAND);
    CtrlAgentCommandMgr::instance().deregisterCommand(SHUT_DOWN_COMMAND);
    CtrlAgentCommandMgr::instance().deregisterCommand(STATUS_GET_COMMAND);
    CtrlAgentCommandMgr::instance().deregisterCommand(VERSION_GET_COMMAND);
}

CtrlAgentController::CtrlAgentController()
    : DControllerBase(agent_app_name_, agent_bin_name_) {
}

CtrlAgentController::~CtrlAgentController() {
}

CtrlAgentProcessPtr
CtrlAgentController::getCtrlAgentProcess() {
    return (boost::dynamic_pointer_cast<CtrlAgentProcess>(getProcess()));
}

} // namespace isc::agent
} // namespace isc
