// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <boost/lexical_cast.hpp>

#include <util/buffer.h>
#include <util/encode/hex.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

#include <stdio.h>
#include <time.h>

using namespace std;
using namespace isc::util;
using namespace isc::util::encode;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

struct NSEC3PARAMImpl {
    // straightforward representation of NSEC3PARAM RDATA fields
    NSEC3PARAMImpl(uint8_t hashalg, uint8_t flags, uint16_t iterations,
                   const vector<uint8_t>& salt) :
        hashalg_(hashalg), flags_(flags), iterations_(iterations), salt_(salt)
    {}

    const uint8_t hashalg_;
    const uint8_t flags_;
    const uint16_t iterations_;
    const vector<uint8_t> salt_;
};

NSEC3PARAM::NSEC3PARAM(const string& nsec3param_str) :
    impl_(NULL)
{
    istringstream iss(nsec3param_str);
    unsigned int hashalg, flags, iterations;
    string iterations_str, salt_str;

    iss >> hashalg >> flags >> iterations_str >> salt_str;
    if (iss.bad() || iss.fail()) {
        isc_throw(InvalidRdataText, "Invalid NSEC3PARAM text");
    }
    if (hashalg > 0xff) {
        isc_throw(InvalidRdataText, "NSEC3PARAM hash algorithm out of range");
    }
    if (flags > 0xff) {
        isc_throw(InvalidRdataText, "NSEC3PARAM flags out of range");
    }
    // Convert iteration.  To reject an invalid case where there's no space
    // between iteration and salt, we extract this field as string and convert
    // to integer.
    try {
        iterations = boost::lexical_cast<unsigned int>(iterations_str);
    } catch (const boost::bad_lexical_cast&) {
        isc_throw(InvalidRdataText, "Bad NSEC3PARAM iteration: " <<
                  iterations_str);
    }
    if (iterations > 0xffff) {
        isc_throw(InvalidRdataText, "NSEC3PARAM iterations out of range: " <<
            iterations);
    }

    vector<uint8_t> salt;
    if (salt_str != "-") { // "-" means an empty salt, no need to touch vector
        decodeHex(salt_str, salt);
    }
    if (salt.size() > 255) {
        isc_throw(InvalidRdataText, "NSEC3PARAM salt is too long: "
                  << salt.size() << " bytes");
    }

    if (!iss.eof()) {
        isc_throw(InvalidRdataText, "Invalid NSEC3PARAM (redundant text): "
                  << nsec3param_str);
    }

    impl_ = new NSEC3PARAMImpl(hashalg, flags, iterations, salt);
}

NSEC3PARAM::NSEC3PARAM(InputBuffer& buffer, size_t rdata_len) {
    // NSEC3 RR must have at least 5 octets:
    // hash algorithm(1), flags(1), iteration(2), saltlen(1)
    if (rdata_len < 5) {
        isc_throw(DNSMessageFORMERR, "NSEC3PARAM too short, length: "
                  << rdata_len);
    }

    const uint8_t hashalg = buffer.readUint8();
    const uint8_t flags = buffer.readUint8();
    const uint16_t iterations = buffer.readUint16();

    const uint8_t saltlen = buffer.readUint8();
    rdata_len -= 5;
    if (rdata_len < saltlen) {
        isc_throw(DNSMessageFORMERR, "NSEC3PARAM salt length is too large: "
                  << static_cast<unsigned int>(saltlen));
    }

    vector<uint8_t> salt(saltlen);
    if (saltlen > 0) {
        buffer.readData(&salt[0], saltlen);
    }

    impl_ = new NSEC3PARAMImpl(hashalg, flags, iterations, salt);
}

NSEC3PARAM::NSEC3PARAM(const NSEC3PARAM& source) :
    Rdata(), impl_(new NSEC3PARAMImpl(*source.impl_))
{}

NSEC3PARAM&
NSEC3PARAM::operator=(const NSEC3PARAM& source) {
    if (impl_ == source.impl_) {
        return (*this);
    }

    NSEC3PARAMImpl* newimpl = new NSEC3PARAMImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

NSEC3PARAM::~NSEC3PARAM() {
    delete impl_;
}

string
NSEC3PARAM::toText() const {
    using namespace boost;
    return (lexical_cast<string>(static_cast<int>(impl_->hashalg_)) +
            " " + lexical_cast<string>(static_cast<int>(impl_->flags_)) +
            " " + lexical_cast<string>(static_cast<int>(impl_->iterations_)) +
            " " + (impl_->salt_.empty() ? "-" : encodeHex(impl_->salt_)));
}

void
NSEC3PARAM::toWire(OutputBuffer& buffer) const {
    buffer.writeUint8(impl_->hashalg_);
    buffer.writeUint8(impl_->flags_);
    buffer.writeUint16(impl_->iterations_);
    buffer.writeUint8(impl_->salt_.size());
    buffer.writeData(&impl_->salt_[0], impl_->salt_.size());
}

void
NSEC3PARAM::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeUint8(impl_->hashalg_);
    renderer.writeUint8(impl_->flags_);
    renderer.writeUint16(impl_->iterations_);
    renderer.writeUint8(impl_->salt_.size());
    renderer.writeData(&impl_->salt_[0], impl_->salt_.size());
}

int
NSEC3PARAM::compare(const Rdata& other) const {
    const NSEC3PARAM& other_param = dynamic_cast<const NSEC3PARAM&>(other);

    if (impl_->hashalg_ != other_param.impl_->hashalg_) {
        return (impl_->hashalg_ < other_param.impl_->hashalg_ ? -1 : 1);
    }
    if (impl_->flags_ != other_param.impl_->flags_) {
        return (impl_->flags_ < other_param.impl_->flags_ ? -1 : 1);
    }
    if (impl_->iterations_ != other_param.impl_->iterations_) {
        return (impl_->iterations_ < other_param.impl_->iterations_ ? -1 : 1);
    }

    const size_t this_len = impl_->salt_.size();
    const size_t other_len = other_param.impl_->salt_.size();
    if (this_len != other_len) {
        return (this_len - other_len);
    }
    const size_t cmplen = min(this_len, other_len);
    const int cmp = (cmplen == 0) ? 0 :
        memcmp(&impl_->salt_.at(0), &other_param.impl_->salt_.at(0), cmplen);
    if (cmp != 0) {
        return (cmp);
    } else {
        return (this_len - other_len);
    }
}

uint8_t
NSEC3PARAM::getHashalg() const {
    return (impl_->hashalg_);
}

uint8_t
NSEC3PARAM::getFlags() const {
    return (impl_->flags_);
}

uint16_t
NSEC3PARAM::getIterations() const {
    return (impl_->iterations_);
}

const vector<uint8_t>&
NSEC3PARAM::getSalt() const {
    return (impl_->salt_);
}


// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
