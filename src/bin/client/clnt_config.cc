// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <client/clnt_cfg_mgr.h>
#include <cc/data.h>

using namespace isc::data;

namespace isc {
namespace client {

ClntConfig::ClntConfig() {

}

isc::data::ElementPtr ClntConfig::toElement() const {
    ElementPtr map(new MapElement());
    return (map);
}

std::string ClntConfig::getConfigSummary(const uint32_t selection) const {
  return ("not-impl");
}

};
};
