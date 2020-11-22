// Copyright (C) 2016-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <agent/ca_controller.h>
#include <agent/ca_process.h>
#include <agent/ca_command_mgr.h>
#include <agent/parser_context.h>
#include <cfgrpt/config_report.h>
#include <functional>

using namespace isc::process;
namespace ph = std::placeholders;

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
        std::bind(&DControllerBase::buildReportHandler, this, ph::_1, ph::_2));

    CtrlAgentCommandMgr::instance().registerCommand(CONFIG_GET_COMMAND,
        std::bind(&DControllerBase::configGetHandler, this, ph::_1, ph::_2));

    CtrlAgentCommandMgr::instance().registerCommand(CONFIG_RELOAD_COMMAND,
        std::bind(&DControllerBase::configReloadHandler, this, ph::_1, ph::_2));

    CtrlAgentCommandMgr::instance().registerCommand(CONFIG_SET_COMMAND,
        std::bind(&DControllerBase::configSetHandler, this, ph::_1, ph::_2));

    CtrlAgentCommandMgr::instance().registerCommand(CONFIG_TEST_COMMAND,
        std::bind(&DControllerBase::configTestHandler, this, ph::_1, ph::_2));

    CtrlAgentCommandMgr::instance().registerCommand(CONFIG_WRITE_COMMAND,
        std::bind(&DControllerBase::configWriteHandler, this, ph::_1, ph::_2));

    CtrlAgentCommandMgr::instance().registerCommand(SHUT_DOWN_COMMAND,
        std::bind(&DControllerBase::shutdownHandler, this, ph::_1, ph::_2));

    CtrlAgentCommandMgr::instance().registerCommand(STATUS_GET_COMMAND,
        std::bind(&DControllerBase::statusGetHandler, this, ph::_1, ph::_2));

    CtrlAgentCommandMgr::instance().registerCommand(VERSION_GET_COMMAND,
        std::bind(&DControllerBase::versionGetHandler, this, ph::_1, ph::_2));
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

// Refer to config_report so it will be embedded in the binary.
const char* const* ca_config_report = isc::detail::config_report;

} // namespace isc::agent
} // namespace isc
