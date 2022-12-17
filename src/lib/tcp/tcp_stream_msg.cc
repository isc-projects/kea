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
TcpStreamRequest::postBuffer(const void* buf, const size_t nbytes) {
    if (!nbytes) {
        // Nothing to do.
        return (0);
    }

    const char* bufptr = static_cast<const char*>(buf);
    size_t bytes_left = nbytes;
    size_t wire_size = wire_data_.size();
    size_t bytes_used = 0;
    while (bytes_left) {
        if (expected_size_) {
            // We have the length, copy as much of what we still need as we can.
            size_t need_bytes = expected_size_ - wire_size;
            size_t copy_bytes = (need_bytes <= bytes_left ? need_bytes : bytes_left);
            wire_data_.insert(wire_data_.end(), bufptr, bufptr + copy_bytes);
            bytes_left -= copy_bytes;
            bytes_used += copy_bytes;
            break;
        }

        // Otherwise we don't know the length yet.
        while (wire_size < 2 && bytes_left) {
            wire_data_.push_back(*bufptr);
            ++bufptr;
            --bytes_left;
            ++bytes_used;
            ++wire_size;
        }

        // If we have enough to do it, calculate the expected length.
        if (wire_size == 2 ) {
            const uint8_t* cp = static_cast<const uint8_t*>(wire_data_.data());
            uint16_t len = static_cast<unsigned int>(cp[0]) << 8;
            len |= static_cast<unsigned int>(cp[1]);
            expected_size_ = len + sizeof(len);
        }
    }

    // Return how much we used.
    return (bytes_used);
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
