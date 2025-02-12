// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/str.h>
#include <client_dictionary.h>
#include <radius_log.h>
#include <boost/lexical_cast.hpp>
#include <fstream>
#include <limits>
#include <sstream>

using namespace isc;
using namespace isc::util;
using namespace std;

namespace isc {
namespace radius {

string
attrValueTypeToText(const AttrValueType value) {
    switch (static_cast<uint8_t>(value)) {
    case PW_TYPE_STRING:
        return ("string");
    case PW_TYPE_INTEGER:
        return ("integer");
    case PW_TYPE_IPADDR:
        return ("ipaddr");
    case PW_TYPE_IPV6ADDR:
        return ("ipv6addr");
    case PW_TYPE_IPV6PREFIX:
        return ("ipv6prefix");
    default:
        // Impossible case.
        return ("unknown?");
    }
}

AttrValueType
textToAttrValueType(const string& name) {
    if (name == "string") {
        return (PW_TYPE_STRING);
    } else if ((name == "integer") || (name == "date")) {
        return (PW_TYPE_INTEGER);
    } else if (name == "ipaddr") {
        return (PW_TYPE_IPADDR);
    } else if (name == "ipv6addr") {
        return (PW_TYPE_IPV6ADDR);
    } else if (name == "ipv6prefix") {
        return (PW_TYPE_IPV6PREFIX);
    } else {
        isc_throw(OutOfRange, "unknown AttrValueType name " << name);
    }
}

AttrDefs&
AttrDefs::instance() {
    static AttrDefs defs;
    return (defs);
}

AttrDefPtr
AttrDefs::getByType(const uint8_t type) const {
    auto const& idx = container_.get<0>();
    auto it = idx.find(type);
    if (it != idx.end()) {
        return (*it);
    }
    return (AttrDefPtr());
}

AttrDefPtr
AttrDefs::getByName(const string& name) const {
    auto const& idx = container_.get<1>();
    auto it = idx.find(name);
    if (it != idx.end()) {
        return (*it);
    }
    auto alias = aliases_.find(name);
    if (alias != aliases_.end()) {
        auto ita = idx.find(alias->second);
        if (ita != idx.end()) {
            return (*ita);
        }
    }
    return (AttrDefPtr());
}

void
AttrDefs::add(AttrDefPtr def) {
    if (!def) {
        return;
    }
    auto& idx1 = container_.get<1>();
    auto it1 = idx1.find(def->name_);
    if (it1 != idx1.end()) {
        if ((def->type_ == (*it1)->type_) &&
            (def->value_type_ == (*it1)->value_type_)) {
            // Duplicate: ignore.
            return;
        }
        isc_throw(BadValue, "Illegal attribute redefinition of '" << def->name_
                  << "' type " << static_cast<unsigned>((*it1)->type_)
                  << " value type " << attrValueTypeToText((*it1)->value_type_)
                  << " by " << static_cast<unsigned>(def->type_)
                  << " " << attrValueTypeToText(def->value_type_));
    }
    auto& idx0 = container_.get<0>();
    auto it0 = idx0.find(def->type_);
    if (it0 != idx0.end()) {
        if (def->value_type_ == (*it0)->value_type_) {
            // Alias.
            auto p = pair<string, string>(def->name_, (*it0)->name_);
            static_cast<void>(aliases_.insert(p));
            return;
        }
        isc_throw(BadValue, "Illegal attribute redefinition of '"
                  << (*it0)->name_ << "' type "
                  << static_cast<unsigned>((*it0)->type_) << " value type "
                  << attrValueTypeToText((*it0)->value_type_)
                  << " by '" << def->name_ << "' "
                  << static_cast<unsigned>(def->type_) << " "
                  << attrValueTypeToText(def->value_type_));
    }
    static_cast<void>(container_.insert(def));
}

string
AttrDefs::getName(const uint8_t type) const {
    AttrDefPtr def = getByType(type);
    if (def) {
        return (def->name_);
    }
    ostringstream oss;
    oss << "Attribute-" << static_cast<unsigned>(type);
    return (oss.str());
}

IntCstDefPtr
AttrDefs::getByName(const uint8_t type, const string& name) const {
    auto const& idx = ic_container_.get<0>();
    auto it = idx.find(boost::make_tuple(type, name));
    if (it != idx.end()) {
        return (*it);
    }
    return (IntCstDefPtr());
}

IntCstDefPtr
AttrDefs::getByValue(const uint8_t type, const uint32_t value) const {
    auto const& idx = ic_container_.get<1>();
    auto it = idx.find(boost::make_tuple(type, value));
    if (it != idx.end()) {
        return (*it);
    }
    return (IntCstDefPtr());
}

void
AttrDefs::add(IntCstDefPtr def) {
    if (!def) {
        return;
    }
    auto& idx = ic_container_.get<0>();
    auto it = idx.find(boost::make_tuple(def->type_, def->name_));
    if (it != idx.end()) {
        if (def->value_ == (*it)->value_) {
            // Duplicate: ignore.
            return;
        }
        isc_throw(BadValue, "Illegal integer constant redefinition of '"
                  << def->name_ << "' for attribute '" << getName(def->type_)
                  << "' value " << (*it)->value_ << " by " << def->value_);
    }
    static_cast<void>(ic_container_.insert(def));
}

void
AttrDefs::parseLine(const string& line) {
    // Ignore empty lines.
    if (line.empty()) {
        return;
    }
    // Ignore comments.
    /// @todo: consider end of line comments?
    if (line[0] == '#') {
        return;
    }
    // Take tokens.
    auto tokens = str::tokens(line);
    // Ignore blank lines.
    if (tokens.empty()) {
        return;
    }
    // Attribute definition.
    if (tokens[0] == "ATTRIBUTE") {
        if (tokens.size() != 4) {
            isc_throw(Unexpected, "expected 4 tokens, got " << tokens.size());
        }
        const string& name = tokens[1];
        const string& type_str = tokens[2];
        uint8_t type = 0;
        try {
            int64_t type64 = boost::lexical_cast<int64_t>(type_str);
            // Ignore attribute types outside [0..255].
            if ((type64 < numeric_limits<uint8_t>::min()) ||
                (type64 > numeric_limits<uint8_t>::max())) {
                return;
            }
            type = static_cast<uint8_t>(type64);
        } catch (...) {
            isc_throw(Unexpected, "can't parse attribute type " << type_str);
        }
        AttrValueType value_type = textToAttrValueType(tokens[3]);
        AttrDefPtr def(new AttrDef(type, name, value_type));
        add(def);
        return;
    }
    // Integer constant definition.
    if (tokens[0] == "VALUE") {
        if (tokens.size() != 4) {
            isc_throw(Unexpected, "expected 4 tokens, got " << tokens.size());
        }
        const string& attr_str = tokens[1];
        AttrDefPtr attr = getByName(attr_str);
        if (!attr) {
            isc_throw(Unexpected, "unknown attribute '" << attr_str << "'");
        }
        if (attr->value_type_ != PW_TYPE_INTEGER) {
            isc_throw(Unexpected, "attribute '" << attr_str
                      << "' is not an integer attribute");
        }
        const string& name = tokens[2];
        const string& value_str = tokens[3];
        uint32_t value = 0;
        try {
            int64_t val = boost::lexical_cast<int64_t>(value_str);
            if ((val < numeric_limits<int32_t>::min()) ||
                (val > numeric_limits<uint32_t>::max())) {
                isc_throw(Unexpected, "not 32 bit " << value_str);
            }
            value = static_cast<uint32_t>(val);
        } catch (...) {
            isc_throw(Unexpected, "can't parse integer value " << value_str);
        }
        IntCstDefPtr def(new IntCstDef(attr->type_, name, value));
        add(def);
        return;
    }
    isc_throw(Unexpected, "unknown dictionary entry '" << tokens[0] << "'");
}

void
AttrDefs::readDictionary(const string& path) {
    ifstream ifs(path);
    if (!ifs.is_open()) {
        isc_throw(BadValue, "can't open dictionary '" << path << "': "
                  << strerror(errno));
    }
    if (!ifs.good()) {
        isc_throw(BadValue, "bad dictionary '" << path << "'");
    }
    try {
        readDictionary(ifs);
        ifs.close();
    } catch (const exception& ex) {
        ifs.close();
        isc_throw(BadValue, ex.what() << " in dictionary '" << path << "'");
    }
}

void
AttrDefs::readDictionary(istream& is) {
    size_t lines = 0;
    string line;
    try {
        while (is.good()) {
            ++lines;
            getline(is, line);
            parseLine(line);
        }
        if (!is.eof()) {
            isc_throw(BadValue, "I/O error: " << strerror(errno));
        }
    } catch (const exception& ex) {
        isc_throw(BadValue, ex.what() << " at line " << lines);
    }
}

void
AttrDefs::checkStandardDefs(const AttrDefList& defs) const {
    for (auto const& it : defs) {
        // Check by name.
        AttrDefPtr def = getByName(it.name_);
        if (!def) {
            isc_throw(Unexpected, "missing standard attribute definition for '"
                      << it.name_ << "'");
        }
        if (def->type_ != it.type_) {
            isc_throw(Unexpected, "incorrect standard attribute definition "
                      << "for '" << it.name_ << "': type is "
                      << static_cast<unsigned>(def->type_) << ", must be "
                      << static_cast<unsigned>(it.type_));
        }
        if (def->value_type_ != it.value_type_) {
            isc_throw(Unexpected, "incorrect standard attribute definition "
                      << "for '" << it.name_ << "': value type is "
                      << attrValueTypeToText(def->value_type_)
                      << ", must be "
                      << attrValueTypeToText(it.value_type_));
        }
    }
}

} // end of namespace isc::radius
} // end of namespace isc
