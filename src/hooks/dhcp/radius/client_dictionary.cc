// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
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
    case PW_TYPE_VSA:
        return ("vsa");
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
    } else if (name == "vsa") {
        return (PW_TYPE_VSA);
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
AttrDefs::getByType(const uint8_t type, const uint32_t vendor) const {
    auto const& idx = container_.get<0>();
    auto it = idx.find(boost::make_tuple(vendor, type));
    if (it != idx.end()) {
        return (*it);
    }
    return (AttrDefPtr());
}

AttrDefPtr
AttrDefs::getByName(const string& name, const uint32_t vendor) const {
    auto const& idx = container_.get<1>();
    auto it = idx.find(boost::make_tuple(vendor, name));
    if (it != idx.end()) {
        return (*it);
    }
    auto alias = aliases_.find(boost::make_tuple(vendor, name));
    if (alias != aliases_.end()) {
        auto ita = idx.find(boost::make_tuple(vendor, alias->name_));
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
    auto it1 = idx1.find(boost::make_tuple(def->vendor_, def->name_));
    if (it1 != idx1.end()) {
        if ((def->type_ == (*it1)->type_) &&
            (def->value_type_ == (*it1)->value_type_)) {
            // Duplicate: ignore.
            return;
        }
        ostringstream msg;
        msg << "Illegal attribute redefinition of '" << def->name_ << "'";
        if (def->vendor_ != 0) {
            msg << " vendor " << def->vendor_;
        }
        msg << " type " << static_cast<unsigned>((*it1)->type_)
            << " value type " << attrValueTypeToText((*it1)->value_type_)
            << " by " << static_cast<unsigned>(def->type_)
            << " " << attrValueTypeToText(def->value_type_);
        isc_throw(BadValue, msg.str());
    }
    auto& idx0 = container_.get<0>();
    auto it0 = idx0.find(boost::make_tuple(def->vendor_, def->type_));
    if (it0 != idx0.end()) {
        if (def->value_type_ == (*it0)->value_type_) {
            // Alias.
            AttrDefAlias alias(def->name_, (*it0)->name_, def->vendor_);
            static_cast<void>(aliases_.insert(alias));
            return;
        }
        ostringstream msg;
        msg << "Illegal attribute redefinition of '" << (*it0)->name_ << "'";
        if (def->vendor_ != 0) {
            msg << " vendor " << def->vendor_;
        }
        msg << " type " << static_cast<unsigned>((*it0)->type_)
            << " value type " << attrValueTypeToText((*it0)->value_type_)
            << " by '" << def->name_ << "' "
            << static_cast<unsigned>(def->type_) << " "
            << attrValueTypeToText(def->value_type_);
        isc_throw(BadValue, msg.str());
    }
    static_cast<void>(container_.insert(def));
}

string
AttrDefs::getName(const uint8_t type, const uint32_t vendor) const {
    AttrDefPtr def = getByType(type, vendor);
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
        if (def->type_ == PW_VENDOR_SPECIFIC) {
            // Vendor id special case.
            isc_throw(BadValue, "Illegal vendor id redefinition of '"
                      << def->name_ << "' value " << (*it)->value_
                      << " by " << def->value_);
        }
        isc_throw(BadValue, "Illegal integer constant redefinition of '"
                  << def->name_ << "' for attribute '" << getName(def->type_)
                  << "' value " << (*it)->value_ << " by " << def->value_);
    }
    static_cast<void>(ic_container_.insert(def));
}

void
AttrDefs::parseLine(const string& line, uint32_t& vendor, unsigned int depth) {
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
    // $INCLUDE include.
    if (tokens[0] == "$INCLUDE") {
        if (tokens.size() != 2) {
            isc_throw(Unexpected, "expected 2 tokens, got " << tokens.size());
        }
        readDictionary(tokens[1], vendor, depth + 1);
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
        if ((value_type == PW_TYPE_VSA) &&
            ((vendor != 0) || (type != PW_VENDOR_SPECIFIC))) {
            isc_throw(BadValue, "only Vendor-Specific (26) attribute can "
                      << "have the vsa data type");
        }
        AttrDefPtr def(new AttrDef(type, name, value_type, vendor));
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
    // Vendor id definition.
    if (tokens[0] == "VENDOR") {
        if (tokens.size() != 3) {
            isc_throw(Unexpected, "expected 3 tokens, got " << tokens.size());
        }
        const string& name = tokens[1];
        const string& value_str = tokens[2];
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
        if (value == 0) {
            isc_throw(Unexpected, "0 is reserved");
        }
        IntCstDefPtr def(new IntCstDef(PW_VENDOR_SPECIFIC, name, value));
        add(def);
        return;
    }
    // Begin vendor attribute definitions.
    if (tokens[0] == "BEGIN-VENDOR") {
        if (vendor != 0) {
            isc_throw(Unexpected, "unsupported embedded begin vendor, "
                      << vendor << " is still open");
        }
        if (tokens.size() != 2) {
            isc_throw(Unexpected, "expected 2 tokens, got " << tokens.size());
        }
        const string& vendor_str = tokens[1];
        IntCstDefPtr vendor_cst = getByName(PW_VENDOR_SPECIFIC, vendor_str);
        if (vendor_cst) {
            vendor = vendor_cst->value_;
            return;
        }
        try {
            int64_t val = boost::lexical_cast<int64_t>(vendor_str);
            if ((val < numeric_limits<int32_t>::min()) ||
                (val > numeric_limits<uint32_t>::max())) {
                isc_throw(Unexpected, "not 32 bit " << vendor_str);
            }
            vendor = static_cast<uint32_t>(val);
        } catch (...) {
            isc_throw(Unexpected, "can't parse integer value " << vendor_str);
        }
        if (vendor == 0) {
            isc_throw(Unexpected, "0 is reserved");
        }
        return;
    }
    // End vendor attribute definitions.
    if (tokens[0] == "END-VENDOR") {
        if (vendor == 0) {
            isc_throw(Unexpected, "no matching begin vendor");
        }
        if (tokens.size() != 2) {
            isc_throw(Unexpected, "expected 2 tokens, got " << tokens.size());
        }
        const string& vendor_str = tokens[1];
        IntCstDefPtr vendor_cst = getByName(PW_VENDOR_SPECIFIC, vendor_str);
        if (vendor_cst) {
            if (vendor_cst->value_ == vendor) {
                vendor = 0;
                return;
            } else {
                isc_throw(Unexpected, "begin vendor " << vendor
                          << " and end vendor " << vendor_cst->value_
                          << " do not match");
            }
        }
        uint32_t value;
        try {
            int64_t val = boost::lexical_cast<int64_t>(vendor_str);
            if ((val < numeric_limits<int32_t>::min()) ||
                (val > numeric_limits<uint32_t>::max())) {
                isc_throw(Unexpected, "not 32 bit " << vendor_str);
            }
            value = static_cast<uint32_t>(val);
        } catch (...) {
            isc_throw(Unexpected, "can't parse integer value " << vendor_str);
        }
        if (vendor == value) {
            vendor = 0;
            return;
        }
        isc_throw(Unexpected, "begin vendor " << vendor
                  << " and end vendor " << value << " do not match");
    }
    isc_throw(Unexpected, "unknown dictionary entry '" << tokens[0] << "'");
}

void
AttrDefs::readDictionary(const string& path, uint32_t& vendor, unsigned depth) {
    if (depth >= 5) {
        isc_throw(BadValue, "Too many nested $INCLUDE");
    }
    ifstream ifs(path);
    if (!ifs.is_open()) {
        isc_throw(BadValue, "can't open dictionary '" << path << "': "
                  << strerror(errno));
    }
    if (!ifs.good()) {
        isc_throw(BadValue, "bad dictionary '" << path << "'");
    }
    try {
        readDictionary(ifs, vendor, depth);
        ifs.close();
    } catch (const exception& ex) {
        ifs.close();
        isc_throw(BadValue, ex.what() << " in dictionary '" << path << "'"
                  << (depth > 0 ? "," : ""));
    }
}

void
AttrDefs::readDictionary(istream& is, uint32_t& vendor, unsigned int depth) {
    size_t lines = 0;
    string line;
    try {
        while (is.good()) {
            ++lines;
            getline(is, line);
            parseLine(line, vendor, depth);
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
