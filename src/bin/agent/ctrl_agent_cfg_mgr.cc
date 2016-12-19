// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <agent/ctrl_agent_cfg_mgr.h>

using namespace isc::dhcp;
using namespace isc::process;

namespace isc {
namespace agent {

CtrlAgentCfgMgr::CtrlAgentCfgMgr()
    : DCfgMgrBase(DCfgContextBasePtr(new CtrlAgentCfgContext())) {
}

CtrlAgentCfgMgr::~CtrlAgentCfgMgr() {
}

std::string
CtrlAgentCfgMgr::getConfigSummary(const uint32_t selection) {
    return ("Control Agent is currently not configurable.");
}

isc::dhcp::ParserPtr
CtrlAgentCfgMgr::createConfigParser(const std::string& element_id,
                                    const isc::data::Element::Position& pos) {
    // Create dummy parser, so as we don't return null pointer.
    isc::dhcp::ParserPtr parser;
    parser.reset(new Uint32Parser(element_id, getContext()->getUint32Storage()));
    return (parser);
}

DCfgContextBasePtr
CtrlAgentCfgMgr::createNewContext() {
    return (DCfgContextBasePtr(new CtrlAgentCfgContext()));
}

} // namespace isc::agent
} // namespace isc
