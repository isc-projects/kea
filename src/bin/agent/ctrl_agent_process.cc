// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <agent/ctrl_agent_process.h>
#include <agent/ctrl_agent_log.h>
#include <cc/command_interpreter.h>
#include <boost/pointer_cast.hpp>

using namespace isc::process;

namespace isc {
namespace agent {

CtrlAgentProcess::CtrlAgentProcess(const char* name,
                                   const asiolink::IOServicePtr& io_service)
    : DProcessBase(name, io_service, DCfgMgrBasePtr(new CtrlAgentCfgMgr())) {
}

CtrlAgentProcess::~CtrlAgentProcess() {
}

void
CtrlAgentProcess::init() {
}

void
CtrlAgentProcess::run() {
    LOG_INFO(agent_logger, CTRL_AGENT_STARTED).arg(VERSION);

    while (!shouldShutdown()) {
        try {
            getIoService()->run_one();

        } catch (const std::exception& ex) {
            LOG_FATAL(agent_logger, CTRL_AGENT_FAILED).arg(ex.what());
            isc_throw(DProcessBaseError,
                      "Process run method failed: " << ex.what());
        }
    }

    LOG_DEBUG(agent_logger, DBGLVL_START_SHUT, CTRL_AGENT_RUN_EXIT);
}

isc::data::ConstElementPtr
CtrlAgentProcess::shutdown(isc::data::ConstElementPtr args) {
    setShutdownFlag(true);
    return (isc::config::createAnswer(0, "Control Agent is shutting down"));
}

isc::data::ConstElementPtr
CtrlAgentProcess::configure(isc::data::ConstElementPtr config_set) {
    int rcode = 0;
    isc::data::ConstElementPtr answer = getCfgMgr()->parseConfig(config_set);
    config::parseAnswer(rcode, answer);
    return (answer);
}

isc::data::ConstElementPtr
CtrlAgentProcess::command(const std::string& command,
                          isc::data::ConstElementPtr args) {
    return (isc::config::createAnswer(COMMAND_INVALID, "Unrecognized command: "
                                      + command));
}


CtrlAgentCfgMgrPtr
CtrlAgentProcess::getCtrlAgentCfgMgr() {
    return(boost::dynamic_pointer_cast<CtrlAgentCfgMgr>(getCfgMgr()));
}

} // namespace isc::agent
} // namespace isc
