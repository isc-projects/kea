// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

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

void
Option6StatusCode::pack(isc::util::OutputBuffer& buf) {
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
Option6StatusCode::len() {
    return (getHeaderLen() + sizeof(uint16_t) + status_message_.size());
}

std::string
Option6StatusCode::toText(int indent) {
    std::ostringstream output;
    output << headerToText(indent) << ": "
        << getStatusCodeName() << "(" << getStatusCode() << ") "
        << dataToText();

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
