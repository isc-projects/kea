// Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dhcp/dhcp6.h>
#include <dhcp/option6_status_code.h>
#include <util/io_utilities.h>
#include <iterator>
#include <sstream>

using namespace isc;
using namespace isc::dhcp;

namespace {

/// @brief Minimum length of the option (when status message is empty).
const size_t OPTION6_STATUS_CODE_MIN_LEN = sizeof(uint16_t);

}; // end of anonymous namespace

namespace isc {
namespace dhcp {

Option6StatusCode::Option6StatusCode(const uint16_t status_code,
                                     const std::string& status_message)
    : Option(Option::V6, D6O_STATUS_CODE),
      status_code_(status_code), status_message_(status_message) {
}

Option6StatusCode::Option6StatusCode(OptionBufferConstIter begin,
                                     OptionBufferConstIter end)
    : Option(Option::V6, D6O_STATUS_CODE),
      status_code_(STATUS_Success), status_message_() {

    // Parse data 
    unpack(begin, end);
}

OptionPtr
Option6StatusCode::clone() const {
    return (cloneInternal<Option6StatusCode>());
}

void
Option6StatusCode::pack(isc::util::OutputBuffer& buf) const {
    // Pack option header.
    packHeader(buf);
    // Write numeric status code.
    buf.writeUint16(getStatusCode());
    // If there is any status message, write it.
    if (!status_message_.empty()) {
        buf.writeData(&status_message_[0], status_message_.size());
    }

    // Status code has no options, so leave here.
}

void
Option6StatusCode::unpack(OptionBufferConstIter begin, OptionBufferConstIter end) {
    // Make sure that the option is not truncated.
    if (std::distance(begin, end) < OPTION6_STATUS_CODE_MIN_LEN) {
        isc_throw(OutOfRange, "Status Code option ("
                  << D6O_STATUS_CODE << ") truncated");
    }

    status_code_ = util::readUint16(&(*begin), std::distance(begin, end));
    begin += sizeof(uint16_t);

    status_message_.assign(begin, end);
}

uint16_t
Option6StatusCode::len() const {
    return (getHeaderLen() + sizeof(uint16_t) + status_message_.size());
}

std::string
Option6StatusCode::toText(int indent) const {
    std::ostringstream output;
    output << headerToText(indent) << ": " << dataToText();

    return (output.str());
}

std::string
Option6StatusCode::dataToText() const {
    std::ostringstream output;
    // Add status code name and numeric status code.
    output << getStatusCodeName() << "(" << getStatusCode() << ") ";

    // Include status message in quotes if status code is
    // non-empty.
    if (!status_message_.empty()) {
        output << "\"" << status_message_ << "\"";

    } else {
        output << "(no status message)";
    }

    return (output.str());
}

std::string
Option6StatusCode::getStatusCodeName() const {
    switch (getStatusCode()) {
    case STATUS_Success:
        return ("Success");
    case STATUS_UnspecFail:
        return ("UnspecFail");
    case STATUS_NoAddrsAvail:
        return ("NoAddrsAvail");
    case STATUS_NoBinding:
        return ("NoBinding");
    case STATUS_NotOnLink:
        return ("NotOnLink");
    case STATUS_UseMulticast:
        return ("UseMulticast");
    case STATUS_NoPrefixAvail:
        return ("NoPrefixAvail");
    case STATUS_UnknownQueryType:
        return ("UnknownQueryType");
    case STATUS_MalformedQuery:
        return ("MalformedQuery");
    case STATUS_NotConfigured:
        return ("NotConfigured");
    case STATUS_NotAllowed:
        return ("NotAllowed");
    default:
        ;
    }
    return ("(unknown status code)");
}

} // end of namespace isc::dhcp
} // end of namespace isc
