// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <tcp/tcp_stream_msg.h>
#include <util/strutil.h>

#include <iomanip>
#include <sstream>
#include <functional>

namespace isc {
namespace tcp {

bool
TcpStreamRequest::needData() const {
    return (!expected_size_ || (wire_data_.size() < expected_size_));
}

size_t
TcpStreamRequest::postBuffer(const void* buf,  const size_t nbytes) {
    if (nbytes) {
        const char* bufptr = static_cast<const char*>(buf);
        wire_data_.insert(wire_data_.end(), bufptr, bufptr + nbytes);
        if (!expected_size_ && wire_data_.size() >= sizeof(uint16_t)) {
            const uint8_t* cp = static_cast<const uint8_t*>(wire_data_.data());
            uint16_t len = ((unsigned int)(cp[0])) << 8;
            len |= ((unsigned int)(cp[1]));
            expected_size_ = len + sizeof(len);
        }
    }

    return (nbytes);
}

std::string
TcpStreamRequest::logFormatRequest(const size_t limit) const {
    std::stringstream output;
    try {
        size_t max = (limit && (limit < wire_data_.size()) ? limit : wire_data_.size());
        output << "expected_size_: " << expected_size_ << ", current size: " << wire_data_.size()
               << ", data: "
               << isc::util::str::dumpAsHex(wire_data_.data(), max);
    } catch (const std::exception& ex) {
        std::stringstream output;
        output << "logFormatRequest error: " << ex.what();
    }

    return (output.str());
}

void TcpStreamRequest::unpack() {
    if (needData()) {
        isc_throw(InvalidOperation, "Cannot unpack an incomplete request");
    }

    if (wire_data_.size() < sizeof(uint16_t)) {
        isc_throw(Unexpected, "Request is malformed, too short");
    }

    request_ = std::vector<uint8_t>(wire_data_.begin() + sizeof(uint16_t), wire_data_.end());
}

void
TcpStreamResponse::setResponseData(const uint8_t* data, size_t length) {
    response_.assign(data, data + length);
}

void
TcpStreamResponse::appendResponseData(const uint8_t* data, size_t length) {
    response_.insert(response_.end(), data, data + length);
}

void
TcpStreamResponse::setResponseData(const std::string& str) {
    response_.assign(str.begin(), str.end());
}

void
TcpStreamResponse::appendResponseData(const std::string& str) {
    response_.insert(response_.end(), str.begin(), str.end());
}

void
TcpStreamResponse::pack() {
    wire_data_.clear();
    // Prepend the length of the request.
    uint16_t size = static_cast<uint16_t>(response_.size());
    wire_data_.push_back(static_cast<uint8_t>((size & 0xff00U) >> 8));
    wire_data_.push_back(static_cast<uint8_t>(size & 0x00ffU));
    wire_data_.insert(wire_data_.end(), response_.begin(), response_.end());
}

} // end of namespace isc::tcp
} // end of namespace isc
