// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <cfg_attribute.h>
#include <eval/evaluate.h>
#include <util/encode/encode.h>
#include <sstream>
#include <iomanip>

using namespace std;
using namespace isc;
using namespace isc::data;
using namespace isc::dhcp;

namespace isc {
namespace radius {

void
CfgAttributes::add(const AttrDefPtr& def,
                   const ConstAttributePtr& attr,
                   const dhcp::ExpressionPtr& expr,
                   const std::string& test) {
    if (!def) {
        isc_throw(BadValue, "no attribute definition");
    }
    container_.insert(pair<const uint8_t, AttributeValue>
                (def->type_, AttributeValue(def, attr, expr, test)));
}

bool
CfgAttributes::del(const uint8_t type) {
    auto it = container_.find(type);
    if (it != container_.end()) {
        container_.erase(it);
        return (true);
    }
    return (false);
}

AttrDefPtr
CfgAttributes::getDef(const uint8_t type) const {
    auto it = container_.find(type);
    if (it == container_.end()) {
        return (AttrDefPtr());
    }
    return (it->second.def_);
}

ConstAttributePtr
CfgAttributes::get(const uint8_t type) const {
    auto it = container_.find(type);
    if (it == container_.end()) {
        return (AttributePtr());
    }
    return (it->second.attr_);
}

ExpressionPtr
CfgAttributes::getExpr(const uint8_t type) const {
    auto it = container_.find(type);
    if (it == container_.end()) {
        return (ExpressionPtr());
    }
    return (it->second.expr_);
}

string
CfgAttributes::getTest(const uint8_t type) const {
    auto it = container_.find(type);
    if (it == container_.end()) {
        return ("");
    }
    return (it->second.test_);
}

Attributes
CfgAttributes::getAll() const {
    Attributes attrs;
    for (auto const& it : container_) {
        attrs.add(it.second.attr_);
    }
    return (attrs);
}

Attributes
CfgAttributes::getEvalAll(Pkt& pkt) {
    Attributes attrs;
    for (auto const& it : container_) {
        const ExpressionPtr& match_expr = it.second.expr_;
        if (!match_expr) {
            attrs.add(it.second.attr_);
            continue;
        }
        string value = evaluateString(*match_expr, pkt);
        if (value.empty()) {
            continue;
        }
        AttrDefPtr def = it.second.def_;
        if (!def) {
            continue;
        }
        AttributePtr attr;
        vector<uint8_t> binary;
        binary.resize(value.size());
        memmove(&binary[0], value.c_str(), binary.size());
        attrs.add(Attribute::fromBytes(def, binary));
    }
    return (attrs);
}

ElementPtr
CfgAttributes::toElement() const {
    ElementPtr result = Element::createList();
    for (auto const& it : container_) {
        AttrDefPtr def = it.second.def_;
        if (!def) {
            continue;
        }
        ElementPtr map;
        if (!it.second.test_.empty()) {
            map = Element::createMap();
            map->set("type", Element::create(static_cast<int>(it.first)));
            map->set("expr", Element::create(it.second.test_));
            map->set("name", Element::create(def->name_));
        } else if (it.second.attr_) {
            map = it.second.attr_->toElement();
        }
        result->add(map);
    }
    return (result);
}

} // end of namespace isc::radius
} // end of namespace isc
