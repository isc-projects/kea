// Copyright (C) 2017-2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cc/data.h>
#include <dhcpsrv/subnet_id.h>
#include <dhcpsrv/cfg_hosts_util.h>
#include <exceptions/exceptions.h>
#include <boost/pointer_cast.hpp>

using namespace isc::data;

namespace isc {
namespace dhcp {

void CfgHostsList::internalize(ConstElementPtr list) {
    if (!list) {
        isc_throw(BadValue, "internal error: CfgHostsList::internalize: "
                  "argument is NULL");
    }
    if (list->getType() != Element::list) {
        isc_throw(BadValue, "internal error: CfgHostsList::internalize: "
                  "argument is not a list Element");
    }
    for (size_t i = 0; i < list->size(); ++i) {
        ConstElementPtr item = list->get(i);
        if (!item) {
            isc_throw(BadValue, "internal error: CfgHostsList::internalize: "
                      "null pointer from the list at " << i);
        }
        if (item->getType() != Element::map) {
            isc_throw(BadValue, "internal error: CfgHostsList::internalize: "
                      "not a map from the list at " << i);
        }
        if (item->size() != 2) {
            isc_throw(BadValue, "internal error: CfgHostsList::internalize: "
                      "bad map size from the list at " << i);
        }
        ConstElementPtr id = item->get("id");
        if (!id) {
            isc_throw(BadValue, "internal error: CfgHostsList::internalize: "
                      "no id from a map at " << i);
        }
        if (id->getType() != Element::integer) {
            isc_throw(BadValue, "internal error: CfgHostsList::internalize: "
                      "not integer id from a map at " <<i);
        }
        SubnetID subnet_id = static_cast<SubnetID>(id->intValue());
        ConstElementPtr resvs = item->get("reservations");
        if (!resvs) {
            isc_throw(BadValue, "internal error: CfgHostsList::internalize: "
                      "no reservations for subnet ID " << subnet_id);
        }
        map_.insert(std::make_pair(subnet_id, 
                                   boost::const_pointer_cast<Element>(resvs)));
    }
}

ElementPtr CfgHostsList::externalize() const {
    ElementPtr result = Element::createList();
    for (CfgHostsMap::const_iterator item = map_.begin();
         item != map_.end(); ++item) {
        ElementPtr pair = Element::createMap();
        pair->set("id", Element::create(static_cast<int64_t>(item->first)));
        pair->set("reservations", item->second);
        result->add(pair);
    }
    return (result);
}

void CfgHostsList::add(SubnetID id, isc::data::ElementPtr resv) {
    CfgHostsMap::iterator item = map_.find(id);
    if (item != map_.end()) {
        item->second->add(resv);
    } else {
        ElementPtr resvs = Element::createList();
        resvs->add(resv);
        map_.insert(std::make_pair(id, resvs));
    }
}

ConstElementPtr CfgHostsList::get(SubnetID id) const {
    CfgHostsMap::const_iterator item = map_.find(id);
    if (item != map_.end()) {
        return (item->second);
    } else {
        return (Element::createList());
    }
}

}
}
