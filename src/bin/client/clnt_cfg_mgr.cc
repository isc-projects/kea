// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Paublic
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <client/clnt_cfg_mgr.h>
#include <client/clnt_config.h>
#include <cc/data.h>

using namespace isc::data;

namespace isc {
namespace client {

ClntCfgMgr::ClntCfgMgr()
  :DCfgMgrBase(process::DCfgContextBasePtr(new ClntConfig())) {
}

std::string
ClntCfgMgr::getConfigSummary(const uint32_t selection) {
  return ("not-implemented");
}

isc::data::ConstElementPtr
ClntCfgMgr::parse(isc::data::ConstElementPtr config, bool check_only) {
    return (ConstElementPtr(new MapElement()));
}

isc::dhcp::ParserPtr
ClntCfgMgr::createConfigParser(const std::string&,
                               const isc::data::Element::Position& pos) {
    return (isc::dhcp::ParserPtr());
}

process::DCfgContextBasePtr
ClntCfgMgr::createNewContext() {
  return (process::DCfgContextBasePtr(new ClntConfig()));
}

void ClntCfgMgr::ensureCurrentAllocated() {

}

};
};

