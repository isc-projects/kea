// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <string>

#include <boost/lexical_cast.hpp>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <util/encode/hex.h>
#include <dns/name.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

using namespace std;
using boost::lexical_cast;
using namespace isc::util;
using namespace isc::util::encode;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

SSHFP::SSHFP(InputBuffer& buffer, size_t rdata_len) {
    if (rdata_len < 2) {
        isc_throw(InvalidRdataLength, "SSHFP record too short");
    }

    algorithm_ = buffer.readUint8();
    fingerprint_type_ = buffer.readUint8();

    rdata_len -= 2;
    if (rdata_len > 0) {
        fingerprint_.resize(rdata_len);
        buffer.readData(&fingerprint_[0], rdata_len);
    }
}

SSHFP::SSHFP(const std::string& sshfp_str) {
    std::istringstream iss(sshfp_str);
    std::stringbuf fingerprintbuf;
    uint32_t algorithm, fingerprint_type;

    iss >> algorithm >> fingerprint_type;
    if (iss.bad() || iss.fail()) {
        isc_throw(InvalidRdataText, "Invalid SSHFP text");
    }

    if (algorithm > 255) {
        isc_throw(InvalidRdataText, "SSHFP algorithm number out of range");
    }

    if (fingerprint_type > 255) {
        isc_throw(InvalidRdataText, "SSHFP fingerprint type out of range");
    }

    iss >> &fingerprintbuf;
    try {
        decodeHex(fingerprintbuf.str(), fingerprint_);
    } catch (const isc::BadValue& e) {
        isc_throw(InvalidRdataText,
                  "Bad SSHFP fingerprint: " << e.what());
    }

    algorithm_ = algorithm;
    fingerprint_type_ = fingerprint_type;
}

SSHFP::SSHFP(uint8_t algorithm, uint8_t fingerprint_type,
             const std::string& fingerprint)
{
    algorithm_ = algorithm;
    fingerprint_type_ = fingerprint_type;

    try {
        decodeHex(fingerprint, fingerprint_);
    } catch (const isc::BadValue& e) {
        isc_throw(InvalidRdataText, "Bad SSHFP fingerprint: " << e.what());
    }
}

SSHFP::SSHFP(const SSHFP& other) :
  Rdata(), algorithm_(other.algorithm_),
  fingerprint_type_(other.fingerprint_type_),
  fingerprint_(other.fingerprint_)
{}

void
SSHFP::toWire(OutputBuffer& buffer) const {
    buffer.writeUint8(algorithm_);
    buffer.writeUint8(fingerprint_type_);

    if (!fingerprint_.empty()) {
        buffer.writeData(&fingerprint_[0], fingerprint_.size());
    }
}

void
SSHFP::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeUint8(algorithm_);
    renderer.writeUint8(fingerprint_type_);

    if (!fingerprint_.empty()) {
        renderer.writeData(&fingerprint_[0], fingerprint_.size());
    }
}

string
SSHFP::toText() const {
    return (lexical_cast<string>(static_cast<int>(algorithm_)) +
            " " + lexical_cast<string>(static_cast<int>(fingerprint_type_)) +
            (fingerprint_.empty() ? "" : " " + encodeHex(fingerprint_)));
}

int
SSHFP::compare(const Rdata& other) const {
    const SSHFP& other_sshfp = dynamic_cast<const SSHFP&>(other);

    /* This doesn't really make any sort of sense, but in the name of
       consistency... */

    if (algorithm_ < other_sshfp.algorithm_) {
        return (-1);
    } else if (algorithm_ > other_sshfp.algorithm_) {
        return (1);
    }

    if (fingerprint_type_ < other_sshfp.fingerprint_type_) {
        return (-1);
    } else if (fingerprint_type_ > other_sshfp.fingerprint_type_) {
        return (1);
    }

    const size_t this_len = fingerprint_.size();
    const size_t other_len = other_sshfp.fingerprint_.size();
    const size_t cmplen = min(this_len, other_len);

    if (cmplen > 0) {
        const int cmp = memcmp(&fingerprint_[0], &other_sshfp.fingerprint_[0],
                               cmplen);
        if (cmp != 0) {
            return (cmp);
        }
    }

    if (this_len == other_len) {
        return (0);
    } else if (this_len < other_len) {
        return (-1);
    } else {
        return (1);
    }
}

uint8_t
SSHFP::getAlgorithmNumber() const {
    return (algorithm_);
}

uint8_t
SSHFP::getFingerprintType() const {
    return (fingerprint_type_);
}

size_t
SSHFP::getFingerprintLen() const {
    return (fingerprint_.size());
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
