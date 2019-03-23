// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <slaac/slaac_controller.h>
#include <slaac/slaac_process.h>
#include <cc/data.h>

using namespace isc::process;

namespace isc {
namespace slaac {

/// @brief Defines the application name, this is passed into base class
/// it may be used to locate configuration data and appears in log statement.
const char* SlaacController::slaac_app_name_ = "Slaac";

/// @brief Defines the executable name. This is passed into the base class
const char* SlaacController::slaac_bin_name_ = "kea-slaac";

DControllerBasePtr&
SlaacController::instance() {
    // If the instance hasn't been created yet, create it.  Note this method
    // must use the base class singleton instance methods.
    if (!getController()) {
        DControllerBasePtr controller_ptr(new SlaacController());
        setController(controller_ptr);
    }

    return (getController());
}

DProcessBase*
SlaacController::createProcess() {
    // Instantiate and return an instance of the D2 application process. Note
    // that the process is passed the controller's io_service.
    return (new SlaacProcess(getAppName().c_str(), getIOService()));
}

isc::data::ConstElementPtr
SlaacController::parseFile(const std::string& name) {

    /// @todo: implement actual parser
    // ParserContext parser;
    // return (parser.parseFile(name, ParserContext::PARSER_SLAAC));
    return (isc::data::Element::fromJSON("{\"Slaac\": { } }"));
}

void
SlaacController::registerCommands() {
    //    SlaacCommandMgr::instance().registerCommand(BUILD_REPORT_COMMAND,
    //    boost::bind(&DControllerBase::buildReportHandler, this, _1, _2));
}

void
SlaacController::deregisterCommands() {
    // SlaacCommandMgr::instance().deregisterCommand(BUILD_REPORT_COMMAND);
}

SlaacController::SlaacController()
    : DControllerBase(slaac_app_name_, slaac_bin_name_) {
}

SlaacController::~SlaacController() {
}

SlaacProcessPtr
SlaacController::getSlaacProcess() {
    return (boost::dynamic_pointer_cast<SlaacProcess>(getProcess()));
}

} // namespace isc::agent
} // namespace isc
