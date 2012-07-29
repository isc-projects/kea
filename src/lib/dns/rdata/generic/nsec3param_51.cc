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

#include <util/buffer.h>
#include <util/encode/hex.h>

#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rdata/generic/detail/nsec3param_common.h>

#include <boost/lexical_cast.hpp>

#include <string>
#include <sstream>
#include <vector>

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

NSEC3PARAM::NSEC3PARAM(const std::string& nsec3param_str) :
    impl_(NULL)
{
    istringstream iss(nsec3param_str);
    vector<uint8_t> salt;
    const ParseNSEC3ParamResult params =
        parseNSEC3ParamText("NSEC3PARAM", nsec3param_str, iss, salt);

    if (!iss.eof()) {
        isc_throw(InvalidRdataText, "Invalid NSEC3PARAM (redundant text): "
                  << nsec3param_str);
    }

    impl_ = new NSEC3PARAMImpl(params.algorithm, params.flags,
                               params.iterations, salt);
}

NSEC3PARAM::NSEC3PARAM(InputBuffer& buffer, size_t rdata_len) {
    vector<uint8_t> salt;
    const ParseNSEC3ParamResult params =
        parseNSEC3ParamWire("NSEC3PARAM", buffer, rdata_len, salt);

    impl_ = new NSEC3PARAMImpl(params.algorithm, params.flags,
                               params.iterations, salt);
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
    using boost::lexical_cast;
    return (lexical_cast<string>(static_cast<int>(impl_->hashalg_)) +
            " " + lexical_cast<string>(static_cast<int>(impl_->flags_)) +
            " " + lexical_cast<string>(static_cast<int>(impl_->iterations_)) +
            " " + (impl_->salt_.empty() ? "-" : encodeHex(impl_->salt_)));
}

template <typename OUTPUT_TYPE>
void
toWireHelper(const NSEC3PARAMImpl& impl, OUTPUT_TYPE& output) {
    output.writeUint8(impl.hashalg_);
    output.writeUint8(impl.flags_);
    output.writeUint16(impl.iterations_);
    output.writeUint8(impl.salt_.size());
    if (!impl.salt_.empty()) {
        output.writeData(&impl.salt_[0], impl.salt_.size());
    }
}

void
NSEC3PARAM::toWire(OutputBuffer& buffer) const {
    toWireHelper(*impl_, buffer);
}

void
NSEC3PARAM::toWire(AbstractMessageRenderer& renderer) const {
    toWireHelper(*impl_, renderer);
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
