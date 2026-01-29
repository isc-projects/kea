// Copyright (C) 2023-2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <client_attribute.h>
#include <radius_log.h>
#include <util/encode/encode.h>
#include <util/str.h>
#include <boost/lexical_cast.hpp>
#include <cctype>
#include <limits>
#include <sstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::util;
using namespace std;

namespace isc {
namespace radius {

AttributePtr
Attribute::fromText(const AttrDefPtr& def, const string& value) {
    if (!def) {
        isc_throw(BadValue, "null attribute definition");
    }
    if (value.empty()) {
        isc_throw(BadValue, "empty attribute value");
    }
    AttributePtr attr = fromText0(def, value);
    if (def->vendor_ == 0) {
        return (attr);
    }
    // Encapsulate into a Vendor-Specific attribute.
    const vector<uint8_t> vsa_data = attr->toBytes();
    return (fromVsa(PW_VENDOR_SPECIFIC, def->vendor_, vsa_data));
}

AttributePtr
Attribute::fromText0(const AttrDefPtr& def, const string& value) {
    switch (static_cast<uint8_t>(def->value_type_)) {
    case PW_TYPE_STRING:
        return (AttrString::fromText(def->type_, value));
    case PW_TYPE_INTEGER:
        if (!isdigit(value[0])) {
            IntCstDefPtr ic_def =
                AttrDefs::instance().getByName(def->type_, value,
                                               def->vendor_);
            if (ic_def) {
                return (fromInt(def->type_, ic_def->value_));
            }
        }
        return (AttrInt::fromText(def->type_, value));
    case PW_TYPE_IPADDR:
        return (AttrIpAddr::fromText(def->type_, value));
    case PW_TYPE_IPV6ADDR:
        return (AttrIpv6Addr::fromText(def->type_, value));
    case PW_TYPE_IPV6PREFIX:
        return (AttrIpv6Prefix::fromText(def->type_, value));
    case PW_TYPE_VSA:
        return (AttrVsa::fromText(def->type_, value));
    default:
        // Impossible case.
        isc_throw(OutOfRange, "unknown value type "
                  << static_cast<unsigned>(def->value_type_));
    }
}

AttributePtr
Attribute::fromBytes(const vector<uint8_t>& bytes) {
    // Checked by caller.
    if (bytes.size() < 2) {
        isc_throw(BadValue, "too short byte argument");
    }
    uint8_t type = bytes[0];
    uint8_t len = bytes[1];
    // Checked by caller.
    if (len != bytes.size()) {
        isc_throw(BadValue, "bad byte argument length " << bytes.size()
                  << " != " << static_cast<unsigned>(len));
    }
    vector<uint8_t> value;
    value.resize(len - 2);
    if (value.size() > 0) {
        memmove(&value[0], &bytes[2], value.size());
    }
    AttrDefPtr def = AttrDefs::instance().getByType(type);
    if (!def) {
        return (AttributePtr());
    }
    return (Attribute::fromBytes(def, value));
}

AttributePtr
Attribute::fromBytes(const AttrDefPtr& def, const vector<uint8_t>& value) {
    if (!def) {
        isc_throw(BadValue, "null attribute definition");
    }
    if (value.empty()) {
        isc_throw(BadValue, "empty attribute value");
    }
    AttributePtr attr = fromBytes0(def, value);
    if (def->vendor_ == 0) {
        return (attr);
    }
    // Encapsulate into a Vendor-Specific attribute.
    const vector<uint8_t> vsa_data = attr->toBytes();
    return (fromVsa(PW_VENDOR_SPECIFIC, def->vendor_, vsa_data));
}

AttributePtr
Attribute::fromBytes0(const AttrDefPtr& def, const vector<uint8_t>& value) {
    switch (static_cast<uint8_t>(def->value_type_)) {
    case PW_TYPE_STRING:
        return (AttrString::fromBytes(def->type_, value));
    case PW_TYPE_INTEGER:
        return (AttrInt::fromBytes(def->type_, value));
    case PW_TYPE_IPADDR:
        return (AttrIpAddr::fromBytes(def->type_, value));
    case PW_TYPE_IPV6ADDR:
        return (AttrIpv6Addr::fromBytes(def->type_, value));
    case PW_TYPE_IPV6PREFIX:
        return (AttrIpv6Prefix::fromBytes(def->type_, value));
    case PW_TYPE_VSA:
        return (AttrVsa::fromBytes(def->type_, value));
    default:
        // Impossible case.
        isc_throw(OutOfRange, "unknown value type "
                  << static_cast<unsigned>(def->value_type_));
    }
}

AttributePtr
Attribute::fromString(const uint8_t type, const string& value) {
    if (value.empty()) {
        isc_throw(BadValue, "empty attribute value");
    }
    return (AttributePtr(new AttrString(type, value)));
}

AttributePtr
Attribute::fromBinary(const uint8_t type, const vector<uint8_t>& value) {
    if (value.empty()) {
        isc_throw(BadValue, "empty attribute value");
    }
    return (AttributePtr(new AttrString(type, value)));
}

AttributePtr
Attribute::fromInt(const uint8_t type, const uint32_t value) {
    return (AttributePtr(new AttrInt(type, value)));
}

AttributePtr
Attribute::fromIpAddr(const uint8_t type, const IOAddress& value) {
    return (AttributePtr(new AttrIpAddr(type, value)));
}

AttributePtr
Attribute::fromIpv6Addr(const uint8_t type, const IOAddress& value) {
    return (AttributePtr(new AttrIpv6Addr(type, value)));
}

AttributePtr
Attribute::fromIpv6Prefix(const uint8_t type, const uint8_t len,
                          const IOAddress& value) {
    return (AttributePtr(new AttrIpv6Prefix(type, len, value)));
}

AttributePtr
Attribute::fromVsa(const uint8_t type, const uint32_t vendor,
                   const std::string& value) {
    return (AttributePtr(new AttrVsa(type, vendor, value)));
}

AttributePtr
Attribute::fromVsa(const uint8_t type, const uint32_t vendor,
                   const std::vector<uint8_t>& value) {
    return (AttributePtr(new AttrVsa(type, vendor, value)));
}

string
Attribute::toString() const {
    isc_throw(TypeError, "the attribute value type must be string, not "
              << attrValueTypeToText(getValueType()));
}

vector<uint8_t>
Attribute::toBinary() const {
    isc_throw(TypeError, "the attribute value type must be string, not "
              << attrValueTypeToText(getValueType()));
}

uint32_t
Attribute::toInt() const {
    isc_throw(TypeError, "the attribute value type must be integer, not "
              << attrValueTypeToText(getValueType()));
}

IOAddress
Attribute::toIpAddr() const {
    isc_throw(TypeError, "the attribute value type must be ipaddr, not "
              << attrValueTypeToText(getValueType()));
}

IOAddress
Attribute::toIpv6Addr() const {
    isc_throw(TypeError, "the attribute value type must be ipv6addr, not "
              << attrValueTypeToText(getValueType()));
}

IOAddress
Attribute::toIpv6Prefix() const {
    isc_throw(TypeError, "the attribute value type must be ipv6prefix, not "
              << attrValueTypeToText(getValueType()));
}

uint8_t
Attribute::toIpv6PrefixLen() const {
    isc_throw(TypeError, "the attribute value type must be ipv6prefix, not "
              << attrValueTypeToText(getValueType()));
}

uint32_t
Attribute::toVendorId() const {
    isc_throw(TypeError, "the attribute value type must be vsa, not "
              << attrValueTypeToText(getValueType()));
}

std::vector<uint8_t>
Attribute::toVsaData() const {
    isc_throw(TypeError, "the attribute value type must be vsa, not "
              << attrValueTypeToText(getValueType()));
}

AttrString::AttrString(const uint8_t type, const vector<uint8_t>& value)
    : Attribute(type), value_() {
    if (value.empty()) {
        isc_throw(BadValue, "value is empty");
    }
    if (value.size() > MAX_STRING_LEN) {
        isc_throw(BadValue, "value is too large " << value.size()
                  << " > " << MAX_STRING_LEN);
    }
    value_.resize(value.size());
    memmove(&value_[0], &value[0], value_.size());
}

AttributePtr
AttrString::fromText(const uint8_t type, const string& repr) {
    if (repr.empty()) {
        isc_throw(BadValue, "empty attribute value");
    }
    if (repr.size() > MAX_STRING_LEN) {
        isc_throw(BadValue, "value is too large " << repr.size()
                  << " > " << MAX_STRING_LEN);
    }
    return (AttributePtr(new AttrString(type, repr)));
}

AttributePtr
AttrString::fromBytes(const uint8_t type, const vector<uint8_t>& bytes) {
    if (bytes.empty()) {
        isc_throw(BadValue, "empty attribute value");
    }
    if (bytes.size() > MAX_STRING_LEN) {
        isc_throw(BadValue, "value is too large " << bytes.size()
                  << " > " << MAX_STRING_LEN);
    }
    return (AttributePtr(new AttrString(type, bytes)));
}

string
AttrString::toText(size_t indent) const {
    ostringstream output;
    for (size_t i = 0; i < indent; i++) {
        output << " ";
    }
    output << AttrDefs::instance().getName(getType()) << '=';
    if (str::isPrintable(value_)) {
        output << "'" << value_ << "'";
    } else {
        vector<uint8_t> binary;
        binary.resize(value_.size());
        if (binary.size() > 0) {
            memmove(&binary[0], value_.c_str(), binary.size());
        }
        output << "0x" << encode::encodeHex(binary);
    }
    return (output.str());
}

vector<uint8_t>
AttrString::toBytes() const {
    vector<uint8_t> output;
    output.resize(2 + getValueLen());
    output[0] = getType();
    output[1] = 2 + getValueLen();
    if (output.size() > 2) {
        memmove(&output[2], &value_[0], output.size() - 2);
    }
    return (output);
}

vector<uint8_t>
AttrString::toBinary() const {
    vector<uint8_t> binary;
    binary.resize(getValueLen());
    if (binary.size() > 0) {
        memmove(&binary[0], &value_[0], binary.size());
    }
    return (binary);
}

ElementPtr
AttrString::toElement() const {
    ElementPtr output = Element::createMap();
    AttrDefPtr def = AttrDefs::instance().getByType(getType());
    if (def) {
        output->set("name", Element::create(def->name_));
    }
    output->set("type", Element::create(static_cast<int>(getType())));
    if (str::isPrintable(value_)) {
        output->set("data", Element::create(value_));
    } else {
        vector<uint8_t> binary;
        binary.resize(value_.size());
        if (binary.size() > 0) {
            memmove(&binary[0], value_.c_str(), binary.size());
        }
        string raw = encode::encodeHex(binary);
        output->set("raw", Element::create(raw));
    }
    return (output);
}

AttributePtr
AttrInt::fromText(const uint8_t type, const string& repr) {
    if (repr.empty()) {
        isc_throw(BadValue, "empty attribute value");
    }
    try {
        int64_t val = boost::lexical_cast<int64_t>(repr);
        if ((val < numeric_limits<int32_t>::min()) ||
            (val > numeric_limits<uint32_t>::max())) {
            isc_throw(BadValue, "not 32 bit " << repr);
        }
        return (AttributePtr(new AttrInt(type, static_cast<uint32_t>(val))));
    } catch (...) {
        LOG_ERROR(radius_logger, RADIUS_INTEGER_ATTRIBUTE_FROM_TEXT_FAILED)
            .arg(unsigned(type))
            .arg(AttrDefs::instance().getName(type))
            .arg(repr);
        throw;
    }
}

AttributePtr
AttrInt::fromBytes(const uint8_t type, const vector<uint8_t>& bytes) {
    if (bytes.size() != 4) {
        ostringstream msg;
        msg << "bad value length " << bytes.size() << " != 4";
        LOG_ERROR(radius_logger, RADIUS_INTEGER_ATTRIBUTE_FROM_BYTES_FAILED)
            .arg(unsigned(type))
            .arg(AttrDefs::instance().getName(type))
            .arg(msg.str());
        isc_throw(BadValue, msg.str());
    }
    int32_t val = (static_cast<int32_t>(bytes[0])) << 24;
    val |= (static_cast<int32_t>(bytes[1])) << 16;
    val |= (static_cast<int32_t>(bytes[2])) << 8;
    val |= static_cast<int32_t>(bytes[3]);
    return (AttributePtr(new AttrInt(type, val)));
}

string
AttrInt::toText(size_t indent) const {
    ostringstream output;
    for (size_t i = 0; i < indent; i++) {
        output << " ";
    }
    output << AttrDefs::instance().getName(getType()) << '=';
    IntCstDefPtr ic_def = AttrDefs::instance().getByValue(getType(), value_);
    if (ic_def) {
        output << ic_def->name_;
    } else {
        output << value_;
    }
    return (output.str());
}

vector<uint8_t>
AttrInt::toBytes() const {
    vector<uint8_t> output;
    output.resize(6);
    output[0] = getType();
    output[1] = 6;
    output[2] = static_cast<uint8_t>((value_ & 0xff000000U) >> 24);
    output[3] = static_cast<uint8_t>((value_ & 0xff0000U) >> 16);
    output[4] = static_cast<uint8_t>((value_ & 0xff00U) >> 8);
    output[5] = static_cast<uint8_t>(value_ & 0xffU);
    return (output);
}

ElementPtr
AttrInt::toElement() const {
    ElementPtr output = Element::createMap();
    AttrDefPtr def = AttrDefs::instance().getByType(getType());
    if (def) {
        output->set("name", Element::create(def->name_));
    }
    output->set("type", Element::create(static_cast<int>(getType())));
    ostringstream val;
    val << value_;
    output->set("data", Element::create(val.str()));
    return (output);
}

AttributePtr
AttrIpAddr::fromText(const uint8_t type, const string& repr) {
    try {
        IOAddress val(repr);
        return (AttributePtr(new AttrIpAddr(type, val)));
    } catch (...) {
        LOG_ERROR(radius_logger, RADIUS_IPADDR_ATTRIBUTE_FROM_TEXT_FAILED)
            .arg(unsigned(type))
            .arg(AttrDefs::instance().getName(type))
            .arg(repr);
        throw;
    }
}

AttributePtr
AttrIpAddr::fromBytes(const uint8_t type, const vector<uint8_t>& bytes) {
    if (bytes.size() != 4) {
        ostringstream msg;
        msg << "bad value length " << bytes.size() << " != 4";
        LOG_ERROR(radius_logger, RADIUS_IPADDR_ATTRIBUTE_FROM_BYTES_FAILED)
            .arg(unsigned(type))
            .arg(AttrDefs::instance().getName(type))
            .arg(msg.str());
        isc_throw(BadValue, msg.str());
    }
    IOAddress val = IOAddress::fromBytes(AF_INET, &bytes[0]);
    return (AttributePtr(new AttrIpAddr(type, val)));
}

string
AttrIpAddr::toText(size_t indent) const {
    ostringstream output;
    for (size_t i = 0; i < indent; i++) {
        output << " ";
    }
    output << AttrDefs::instance().getName(getType()) << '='
           << value_.toText();
    return (output.str());
}

vector<uint8_t>
AttrIpAddr::toBytes() const {
    vector<uint8_t> output;
    output.resize(6);
    output[0] = getType();
    output[1] = 6;
    vector<uint8_t> binary = value_.toBytes();
    memmove(&output[2], &binary[0], output.size() - 2);
    return (output);
}

ElementPtr
AttrIpAddr::toElement() const {
    ElementPtr output = Element::createMap();
    AttrDefPtr def = AttrDefs::instance().getByType(getType());
    if (def) {
        output->set("name", Element::create(def->name_));
    }
    output->set("type", Element::create(static_cast<int>(getType())));
    ostringstream val;
    val << value_.toText();
    output->set("data", Element::create(val.str()));
    return (output);
}

AttributePtr
AttrIpv6Addr::fromText(const uint8_t type, const string& repr) {
    try {
        IOAddress val(repr);
        return (AttributePtr(new AttrIpv6Addr(type, val)));
    } catch (...) {
        LOG_ERROR(radius_logger, RADIUS_IPV6ADDR_ATTRIBUTE_FROM_TEXT_FAILED)
            .arg(unsigned(type))
            .arg(AttrDefs::instance().getName(type))
            .arg(repr);
        throw;
    }
}

AttributePtr
AttrIpv6Addr::fromBytes(const uint8_t type, const vector<uint8_t>& bytes) {
    if (bytes.size() != 16) {
        ostringstream msg;
        msg << "bad value length " << bytes.size() << " != 16";
        LOG_ERROR(radius_logger, RADIUS_IPV6ADDR_ATTRIBUTE_FROM_BYTES_FAILED)
            .arg(unsigned(type))
            .arg(AttrDefs::instance().getName(type))
            .arg(msg.str());
        isc_throw(BadValue, msg.str());
    }
    IOAddress val = IOAddress::fromBytes(AF_INET6, &bytes[0]);
    return (AttributePtr(new AttrIpv6Addr(type, val)));
}

string
AttrIpv6Addr::toText(size_t indent) const {
    ostringstream output;
    for (size_t i = 0; i < indent; i++) {
        output << " ";
    }
    output << AttrDefs::instance().getName(getType()) << '='
           << value_.toText();
    return (output.str());
}

vector<uint8_t>
AttrIpv6Addr::toBytes() const {
    vector<uint8_t> output;
    output.resize(18);
    output[0] = getType();
    output[1] = 18;
    vector<uint8_t> binary = value_.toBytes();
    memmove(&output[2], &binary[0], output.size() - 2);
    return (output);
}

ElementPtr
AttrIpv6Addr::toElement() const {
    ElementPtr output = Element::createMap();
    AttrDefPtr def = AttrDefs::instance().getByType(getType());
    if (def) {
        output->set("name", Element::create(def->name_));
    }
    output->set("type", Element::create(static_cast<int>(getType())));
    ostringstream val;
    val << value_.toText();
    output->set("data", Element::create(val.str()));
    return (output);
}

AttributePtr
AttrIpv6Prefix::fromText(const uint8_t type, const string& repr) {
    try {
        auto pos = repr.find('/');
        if ((pos == string::npos) ||
            (pos == repr.size() - 1) ||
            (pos == 0)) {
            isc_throw(BadValue, "unable to parse prefix " << repr);
        }
        IOAddress val(repr.substr(0, pos));
        int len = boost::lexical_cast<int>(repr.substr(pos + 1));
        if ((len < numeric_limits<uint8_t>::min()) ||
            (len > numeric_limits<uint8_t>::max())) {
            isc_throw(BadValue, "not 8 bit prefix length " << repr);
        }
        return (AttributePtr(new AttrIpv6Prefix(type,
                                                static_cast<uint8_t>(len),
                                                val)));
    } catch (...) {
        LOG_ERROR(radius_logger, RADIUS_IPV6PREFIX_ATTRIBUTE_FROM_TEXT_FAILED)
            .arg(unsigned(type))
            .arg(AttrDefs::instance().getName(type))
            .arg(repr);
        throw;
    }
}

AttributePtr
AttrIpv6Prefix::fromBytes(const uint8_t type, const vector<uint8_t>& bytes) {
    /// Checked by caller.
    ostringstream msg;
    if (bytes.size() < 2) {
        msg << "bad value length " << bytes.size() << " < 2";
    } else if (bytes.size() > 18) {
        msg << "bad value length " << bytes.size() << " > 18";
    } else if (bytes[1] > 128) {
        msg << "bad prefix length " << static_cast<unsigned>(bytes[1]) << " > 128";
    }
    string const msg_str(msg.str());
    if (!msg_str.empty()) {
        LOG_ERROR(radius_logger, RADIUS_IPV6PREFIX_ATTRIBUTE_FROM_BYTES_FAILED)
            .arg(static_cast<unsigned>(type))
            .arg(AttrDefs::instance().getName(type))
            .arg(msg.str());
        isc_throw(BadValue, msg_str);
    }
    uint8_t len = bytes[1];
    vector<uint8_t> prefix(16);
    if (bytes.size() > 2) {
        memmove(&prefix[0], &bytes[2], bytes.size() - 2);
    }
    IOAddress val = IOAddress::fromBytes(AF_INET6, &prefix[0]);
    return (AttributePtr(new AttrIpv6Prefix(type, len, val)));
}

string
AttrIpv6Prefix::toText(size_t indent) const {
    ostringstream output;
    for (size_t i = 0; i < indent; i++) {
        output << " ";
    }
    output << AttrDefs::instance().getName(getType()) << '='
           << value_.toText() << "/" << static_cast<unsigned>(len_);
    return (output.str());
}

vector<uint8_t>
AttrIpv6Prefix::toBytes() const {
    vector<uint8_t> output;
    // type(1) + length(1) + reserved(1) + prefix_len(1) + prefix(16)
    output.resize(20);
    output[0] = getType();
    output[1] = 20;
    output[2] = 0;
    output[3] = len_;
    vector<uint8_t> binary = value_.toBytes();
    memmove(&output[4], &binary[0], output.size() - 4);
    return (output);
}

ElementPtr
AttrIpv6Prefix::toElement() const {
    ElementPtr output = Element::createMap();
    AttrDefPtr def = AttrDefs::instance().getByType(getType());
    if (def) {
        output->set("name", Element::create(def->name_));
    }
    output->set("type", Element::create(static_cast<int>(getType())));
    ostringstream val;
    val << value_.toText() << "/" << static_cast<unsigned>(len_);
    output->set("data", Element::create(val.str()));
    return (output);
}

AttrVsa::AttrVsa(const uint8_t type, const uint32_t vendor,
                 const vector<uint8_t>& value)
    : Attribute(type), vendor_(vendor), value_() {
    if (value.empty()) {
        isc_throw(BadValue, "value is empty");
    }
    if (value.size() > MAX_VSA_DATA_LEN) {
        isc_throw(BadValue, "value is too large " << value.size()
                  << " > " << MAX_VSA_DATA_LEN);
    }
    value_.resize(value.size());
    memmove(&value_[0], &value[0], value_.size());
}

AttributePtr
AttrVsa::fromText(const uint8_t /* type */, const string& /* repr */) {
    isc_throw(NotImplemented, "can't decode vsa from text");
}

AttributePtr
AttrVsa::fromBytes(const uint8_t type, const vector<uint8_t>& bytes) {
    if (bytes.empty()) {
        isc_throw(BadValue, "empty attribute value");
    }
    if (bytes.size() < 5) {
        isc_throw(BadValue, "value is too small " << bytes.size() << " < 5");
    } else if (bytes.size() > MAX_STRING_LEN) {
        isc_throw(BadValue, "value is too large " << bytes.size()
                  << " > " << MAX_STRING_LEN);
    }
    uint32_t vendor = bytes[0] << 24;
    vendor |= bytes[1] << 16;
    vendor |= bytes[2] << 8;
    vendor |= bytes[3];
    vector<uint8_t> value;
    value.resize(bytes.size() - 4);
    if (value.size() > 0) {
        memmove(&value[0], &bytes[4], value.size());
    }
    return (AttributePtr(new AttrVsa(type, vendor, value)));
}

string
AttrVsa::toText(size_t indent) const {
    ostringstream output;
    for (size_t i = 0; i < indent; i++) {
        output << " ";
    }
    output << AttrDefs::instance().getName(getType()) << "=["
           << vendor_ << "]";
    vector<uint8_t> binary;
    binary.resize(value_.size());
    if (binary.size() > 0) {
        memmove(&binary[0], value_.c_str(), binary.size());
    }
    output << "0x" << encode::encodeHex(binary);
    return (output.str());
}

std::vector<uint8_t>
AttrVsa::toBytes() const {
    vector<uint8_t> output;
    output.resize(2 + getValueLen());
    output[0] = getType();
    output[1] = 2 + getValueLen();
    output[2] = (vendor_ & 0xff000000U) >> 24;
    output[3] = (vendor_ & 0xff0000U) >> 16;
    output[4] = (vendor_ & 0xff00U) >> 8;
    output[5] = vendor_ & 0xffU;
    if (output.size() > 6) {
        memmove(&output[6], &value_[0], output.size() - 6);
    }
    return (output);
}

std::vector<uint8_t>
AttrVsa::toVsaData() const {
    vector<uint8_t> binary;
    binary.resize(value_.size());
    if (binary.size() > 0) {
        memmove(&binary[0], &value_[0], binary.size());
    }
    return (binary);
}

ElementPtr
AttrVsa::toElement() const {
    ElementPtr output = Element::createMap();
    AttrDefPtr def = AttrDefs::instance().getByType(getType());
    if (def) {
        output->set("name", Element::create(def->name_));
    }
    output->set("type", Element::create(static_cast<int>(getType())));
    ostringstream vendor;
    vendor << vendor_;
    output->set("vendor", Element::create(vendor.str()));
    vector<uint8_t> binary;
    binary.resize(value_.size());
    if (binary.size() > 0) {
        memmove(&binary[0], value_.c_str(), binary.size());
    }
    string raw = encode::encodeHex(binary);
    output->set("vsa-raw", Element::create(raw));
    return (output);
}

void
Attributes::add(const ConstAttributePtr& attr, bool back) {
    if (!attr) {
        return;
    }
    if (back) {
        static_cast<void>(container_.push_back(attr));
    } else {
        static_cast<void>(container_.push_front(attr));
    }
}

bool
Attributes::del(const uint8_t type) {
    auto& idx = container_.get<1>();
    auto it = idx.find(type);
    if (it != idx.end()) {
        idx.erase(it);
        return (true);
    }
    return (false);
}

void
Attributes::append(const Attributes& other) {
    for (auto const& it : other) {
        add(it);
    }
}

size_t
Attributes::count(const uint8_t type) const {
    auto const& idx = container_.get<1>();
    return (idx.count(type));
}

ConstAttributePtr
Attributes::get(const uint8_t type) const {
    auto const& idx = container_.get<1>();
    auto it = idx.find(type);
    if (it != idx.end()) {
        return (*it);
    } else {
        return(ConstAttributePtr());
    }
}

string
Attributes::toText(size_t indent) const {
    ostringstream output;
    bool first = true;
    for (auto const& it : *this) {
        if (!first) {
            output << ",\n";
        } else {
            first = false;
        }
        output << it->toText(indent);
    }
    return (output.str());
}

ElementPtr
Attributes::toElement() const {
    ElementPtr output = Element::createList();
    for (auto const& it : *this) {
        output->add(it->toElement());
    }
    return (output);
}

Attributes
Attributes::fromElement(const ConstElementPtr& attr_list) {
    Attributes attrs;
    if (!attr_list || (attr_list->getType() != Element::list)) {
        return (attrs);
    }
    for (auto const& entry : attr_list->listValue()) {
        if (!entry || (entry->getType() != Element::map)) {
            continue;
        }
        ConstElementPtr attr_type = entry->get("type");
        if (!attr_type || (attr_type->getType() != Element::integer)) {
            continue;
        }
        AttrDefPtr def = AttrDefs::instance().getByType(attr_type->intValue());
        if (!def) {
            continue;
        }
        if (def->value_type_ == PW_TYPE_STRING) {
            ConstElementPtr raw = entry->get("raw");
            if (raw && (raw->getType() == Element::string) &&
                (!raw->stringValue().empty())) {
                try {
                    vector<uint8_t> binary;
                    encode::decodeHex(raw->stringValue(), binary);
                    AttributePtr attr = Attribute::fromBytes(def, binary);
                    attrs.add(attr);
                    continue;
                } catch (...) {
                    continue;
                }
            }
        }
        ConstElementPtr data = entry->get("data");
        if (data && (data->getType() == Element::string) &&
            (!data->stringValue().empty())) {
            AttributePtr attr = Attribute::fromText(def, data->stringValue());
            attrs.add(attr);
            continue;
        }
    }
    return (attrs);
}

} // end of namespace isc::radius
} // end of namespace isc
