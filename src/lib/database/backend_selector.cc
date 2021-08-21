// Copyright (C) 2018-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <database/backend_selector.h>
#include <exceptions/exceptions.h>
#include <limits>
#include <sstream>

using namespace isc::data;

namespace isc {
namespace db {

BackendSelector::BackendSelector()
    : backend_type_(BackendSelector::Type::UNSPEC),
      host_(), port_(0) {
}

BackendSelector::BackendSelector(const Type& backend_type)
    : backend_type_(backend_type),
      host_(), port_(0) {
}

BackendSelector::BackendSelector(const std::string& host,
                                             const uint16_t port)
    : backend_type_(BackendSelector::Type::UNSPEC),
      host_(host), port_(port) {
    validate();
}

BackendSelector::BackendSelector(const data::ConstElementPtr& access_map)
    : backend_type_(BackendSelector::Type::UNSPEC),
      host_(), port_(0) {
    if (access_map->getType() != Element::map) {
        isc_throw(BadValue, "database access information must be a map");
    }

    ConstElementPtr t = access_map->get("type");
    if (t) {
        if (t->getType() != Element::string) {
            isc_throw(BadValue, "'type' parameter must be a string");
        }
        backend_type_ = stringToBackendType(t->stringValue());
    }

    ConstElementPtr h = access_map->get("host");
    if (h) {
        if (h->getType() != Element::string) {
            isc_throw(BadValue, "'host' parameter must be a string");
        }
        host_ = h->stringValue();
    }

    ConstElementPtr p = access_map->get("port");
    if (p) {
        if ((p->getType() != Element::integer) ||
            (p->intValue() < 0) ||
            (p->intValue() > std::numeric_limits<uint16_t>::max())) {
            isc_throw(BadValue, "'port' parameter must be a number in range from 0 "
                      "to " << std::numeric_limits<uint16_t>::max());
        }
        port_ = static_cast<uint16_t>(p->intValue());
    }

    validate();
}

const BackendSelector&
BackendSelector::UNSPEC() {
    static BackendSelector selector;
    return (selector);
}

bool
BackendSelector::amUnspecified() const {
    return ((backend_type_ == BackendSelector::Type::UNSPEC) &&
            (host_.empty()) &&
            (port_ == 0));
}

std::string
BackendSelector::toText() const {
    std::ostringstream s;
    if (amUnspecified()) {
        s << "unspecified";

    } else {
        if (backend_type_ != BackendSelector::Type::UNSPEC) {
            s << "type=" << backendTypeToString(backend_type_) << ",";
        }

        if (!host_.empty()) {
            s << "host=" << host_ << ",";

            if (port_ > 0) {
                s << "port=" << port_ << ",";
            }
        }
    }

    std::string text = s.str();
    if ((!text.empty() && (text.back() == ','))) {
        text.pop_back();
    }

    return (text);
}

ElementPtr
BackendSelector::toElement() const {
    if (backend_type_ == BackendSelector::Type::UNSPEC) {
        isc_throw(BadValue, "toElement: backend selector type is unspecified");
    }
    ElementPtr result = Element::createMap();
    result->set("type", Element::create(backendTypeToString(backend_type_)));
    if (!host_.empty()) {
        result->set("host", Element::create(host_));
        if (port_ > 0) {
            result->set("port", Element::create(static_cast<long int>(port_)));
        }
    }
    return (result);
}

BackendSelector::Type
BackendSelector::stringToBackendType(const std::string& type) {
    if (type == "mysql") {
        return (BackendSelector::Type::MYSQL);

    } else if (type == "pgsql") {
        return (BackendSelector::Type::PGSQL);

    } else if (type == "cql") {
        return (BackendSelector::Type::CQL);

    } else {
        isc_throw(BadValue, "unsupported configuration backend type '" << type << "'");
    }
}

std::string
BackendSelector::backendTypeToString(const BackendSelector::Type& type) {
    switch (type) {
    case BackendSelector::Type::MYSQL:
        return ("mysql");
    case BackendSelector::Type::PGSQL:
        return ("pgsql");
    case BackendSelector::Type::CQL:
        return ("cql");
    default:
        ;
    }

    return (std::string());
}

void
BackendSelector::validate() const {
    if ((port_ != 0) && (host_.empty())) {
        isc_throw(BadValue, "'host' must be specified along with 'port' parameter");
    }
}

} // end of namespace isc::db
} // end of namespace isc
