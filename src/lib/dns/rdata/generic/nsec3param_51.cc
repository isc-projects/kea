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

// $Id$

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <boost/lexical_cast.hpp>

#include <dns/buffer.h>
#include <dns/util/hex.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

#include <stdio.h>
#include <time.h>

using namespace std;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

struct NSEC3PARAMImpl {
    // straightforward representation of NSEC3PARAM RDATA fields
    NSEC3PARAMImpl(uint8_t hashalg, uint8_t flags, uint16_t iterations,
                   const vector<uint8_t>& salt) :
        hashalg_(hashalg), flags_(flags), iterations_(iterations), salt_(salt)
    {}

    uint8_t hashalg_;
    uint8_t flags_;
    uint16_t iterations_;
    const vector<uint8_t> salt_;
};

NSEC3PARAM::NSEC3PARAM(const string& nsec3param_str) :
    impl_(NULL)
{
    istringstream iss(nsec3param_str);
    uint16_t hashalg, flags, iterations;
    stringbuf saltbuf;

    iss >> hashalg >> flags >> iterations >> &saltbuf;
    if (iss.bad() || iss.fail()) {
        isc_throw(InvalidRdataText, "Invalid NSEC3PARAM text");
    }
    if (hashalg > 0xf) {
        isc_throw(InvalidRdataText, "NSEC3PARAM hash algorithm out of range");
    }
    if (flags > 0xff) {
        isc_throw(InvalidRdataText, "NSEC3PARAM flags out of range");
    }

    vector<uint8_t> salt;
    decodeHex(saltbuf.str(), salt);

    impl_ = new NSEC3PARAMImpl(hashalg, flags, iterations, salt);
}

NSEC3PARAM::NSEC3PARAM(InputBuffer& buffer, size_t rdata_len)
{
    if (rdata_len < 4) {
        isc_throw(InvalidRdataLength, "NSEC3PARAM too short");
    }

    uint8_t hashalg = buffer.readUint8();
    uint8_t flags = buffer.readUint8();
    uint16_t iterations = buffer.readUint16();
    rdata_len -= 4;

    uint8_t saltlen = buffer.readUint8();
    --rdata_len;

    if (rdata_len < saltlen) {
        isc_throw(InvalidRdataLength, "NSEC3PARAM salt too short");
    }

    vector<uint8_t> salt(saltlen);
    buffer.readData(&salt[0], saltlen);

    impl_ = new NSEC3PARAMImpl(hashalg, flags, iterations, salt);
}

NSEC3PARAM::NSEC3PARAM(const NSEC3PARAM& source) :
    Rdata(), impl_(new NSEC3PARAMImpl(*source.impl_))
{}

NSEC3PARAM&
NSEC3PARAM::operator=(const NSEC3PARAM& source)
{
    if (impl_ == source.impl_) {
        return (*this);
    }

    NSEC3PARAMImpl* newimpl = new NSEC3PARAMImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

NSEC3PARAM::~NSEC3PARAM()
{
    delete impl_;
}

string
NSEC3PARAM::toText() const
{
    using namespace boost;
    return (lexical_cast<string>(static_cast<int>(impl_->hashalg_)) +
        " " + lexical_cast<string>(static_cast<int>(impl_->flags_)) +
        " " + lexical_cast<string>(static_cast<int>(impl_->iterations_)) +
        " " + encodeHex(impl_->salt_));
}

void
NSEC3PARAM::toWire(OutputBuffer& buffer) const
{
    buffer.writeUint8(impl_->hashalg_);
    buffer.writeUint8(impl_->flags_);
    buffer.writeUint16(impl_->iterations_);
    buffer.writeUint8(impl_->salt_.size());
    buffer.writeData(&impl_->salt_[0], impl_->salt_.size());
}

void
NSEC3PARAM::toWire(MessageRenderer& renderer) const
{
    renderer.writeUint8(impl_->hashalg_);
    renderer.writeUint8(impl_->flags_);
    renderer.writeUint16(impl_->iterations_);
    renderer.writeUint8(impl_->salt_.size());
    renderer.writeData(&impl_->salt_[0], impl_->salt_.size());
}

int
NSEC3PARAM::compare(const Rdata& other) const
{
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

    size_t this_len = impl_->salt_.size();
    size_t other_len = other_param.impl_->salt_.size();
    size_t cmplen = min(this_len, other_len);
    int cmp = memcmp(&impl_->salt_[0], &other_param.impl_->salt_[0],
                     cmplen);
    if (cmp != 0) {
        return (cmp);
    } else {
        return ((this_len == other_len) ? 0 : (this_len < other_len) ? -1 : 1);
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
