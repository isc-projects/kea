// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <agent/ca_command_mgr.h>
#include <cc/data.h>
#include <boost/pointer_cast.hpp>

using namespace isc::data;

namespace isc {
namespace agent {

CtrlAgentCommandMgr&
CtrlAgentCommandMgr::instance() {
    static CtrlAgentCommandMgr command_mgr;
    return (command_mgr);
}

CtrlAgentCommandMgr::CtrlAgentCommandMgr()
    : HookedCommandMgr() {
}

ConstElementPtr
CtrlAgentCommandMgr::handleCommand(const std::string& cmd_name,
                                   const isc::data::ConstElementPtr& params) {
    ElementPtr answer_list = Element::createList();
    answer_list->add(boost::const_pointer_cast<
                     Element>(HookedCommandMgr::handleCommand(cmd_name, params)));
    return (answer_list);
}


} // end of namespace isc::agent
} // end of namespace isc
