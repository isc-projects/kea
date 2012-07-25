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
#include <iomanip>
#include <string>
#include <sstream>
#include <vector>
#include <cassert>

#include <boost/lexical_cast.hpp>

#include <util/encode/base32hex.h>
#include <util/encode/hex.h>
#include <util/buffer.h>

#include <dns/exceptions.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rdata/generic/detail/nsec_bitmap.h>
#include <dns/rdata/generic/detail/nsec3param_common.h>

#include <stdio.h>
#include <time.h>

using namespace std;
using namespace isc::dns::rdata::generic::detail::nsec;
using namespace isc::dns::rdata::generic::detail::nsec3;
using namespace isc::util::encode;
using namespace isc::util;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

struct NSEC3Impl {
    // straightforward representation of NSEC3 RDATA fields
    NSEC3Impl(uint8_t hashalg, uint8_t flags, uint16_t iterations,
              vector<uint8_t>salt, vector<uint8_t>next,
              vector<uint8_t> typebits) :
        hashalg_(hashalg), flags_(flags), iterations_(iterations),
        salt_(salt), next_(next), typebits_(typebits)
    {}

    const uint8_t hashalg_;
    const uint8_t flags_;
    const uint16_t iterations_;
    const vector<uint8_t> salt_;
    const vector<uint8_t> next_;
    const vector<uint8_t> typebits_;
};

NSEC3::NSEC3(const std::string& nsec3_str) :
    impl_(NULL)
{
    istringstream iss(nsec3_str);
    vector<uint8_t> salt;
    const ParseNSEC3ParamResult params =
        parseNSEC3ParamText("NSEC3", nsec3_str, iss, salt);

    // Extract Next hash.  It must be an unpadded base32hex string.
    string nexthash;
    iss >> nexthash;
    if (iss.bad() || iss.fail()) {
        isc_throw(InvalidRdataText, "Invalid NSEC3 text: " << nsec3_str);
    }
    assert(!nexthash.empty());
    if (*nexthash.rbegin() == '=') {
        isc_throw(InvalidRdataText, "NSEC3 hash has padding: " << nsec3_str);
    }
    vector<uint8_t> next;
    decodeBase32Hex(nexthash, next);
    if (next.size() > 255) {
        isc_throw(InvalidRdataText, "NSEC3 hash is too long: "
                  << next.size() << " bytes");
    }

    // For NSEC3 empty bitmap is possible and allowed.
    if (iss.eof()) {
        impl_ = new NSEC3Impl(params.algorithm, params.flags,
                              params.iterations, salt, next,
                              vector<uint8_t>());
        return;
    }

    vector<uint8_t> typebits;
    buildBitmapsFromText("NSEC3", iss, typebits);

    impl_ = new NSEC3Impl(params.algorithm, params.flags, params.iterations,
                          salt, next, typebits);
}

NSEC3::NSEC3(InputBuffer& buffer, size_t rdata_len) {
    vector<uint8_t> salt;
    const ParseNSEC3ParamResult params =
        parseNSEC3ParamWire("NSEC3", buffer, rdata_len, salt);

    if (rdata_len < 1) {
        isc_throw(DNSMessageFORMERR, "NSEC3 too short to contain hash length, "
                  "length: " << rdata_len + salt.size() + 5);
    }
    const uint8_t nextlen = buffer.readUint8();
    --rdata_len;
    if (nextlen == 0 || rdata_len < nextlen) {
        isc_throw(DNSMessageFORMERR, "NSEC3 invalid hash length: " <<
                  static_cast<unsigned int>(nextlen));
    }

    vector<uint8_t> next(nextlen);
    buffer.readData(&next[0], nextlen);
    rdata_len -= nextlen;

    vector<uint8_t> typebits(rdata_len);
    if (rdata_len > 0) {
        // Read and parse the bitmaps only when they exist; empty bitmap
        // is possible for NSEC3.
        buffer.readData(&typebits[0], rdata_len);
        checkRRTypeBitmaps("NSEC3", typebits);
    }

    impl_ = new NSEC3Impl(params.algorithm, params.flags, params.iterations,
                          salt, next, typebits);
}

NSEC3::NSEC3(const NSEC3& source) :
    Rdata(), impl_(new NSEC3Impl(*source.impl_))
{}

NSEC3&
NSEC3::operator=(const NSEC3& source) {
    if (impl_ == source.impl_) {
        return (*this);
    }

    NSEC3Impl* newimpl = new NSEC3Impl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

NSEC3::~NSEC3() {
    delete impl_;
}

string
NSEC3::toText() const {
    ostringstream s;
    bitmapsToText(impl_->typebits_, s);

    using boost::lexical_cast;
    return (lexical_cast<string>(static_cast<int>(impl_->hashalg_)) +
            " " + lexical_cast<string>(static_cast<int>(impl_->flags_)) +
            " " + lexical_cast<string>(static_cast<int>(impl_->iterations_)) +
            " " + (impl_->salt_.empty() ? "-" : encodeHex(impl_->salt_)) +
            " " + encodeBase32Hex(impl_->next_) + s.str());
}

template <typename OUTPUT_TYPE>
void
toWireHelper(const NSEC3Impl& impl, OUTPUT_TYPE& output) {
    output.writeUint8(impl.hashalg_);
    output.writeUint8(impl.flags_);
    output.writeUint16(impl.iterations_);
    output.writeUint8(impl.salt_.size());
    if (!impl.salt_.empty()) {
        output.writeData(&impl.salt_[0], impl.salt_.size());
    }
    assert(!impl.next_.empty());
    output.writeUint8(impl.next_.size());
    output.writeData(&impl.next_[0], impl.next_.size());
    if (!impl.typebits_.empty()) {
        output.writeData(&impl.typebits_[0], impl.typebits_.size());
    }
}

void
NSEC3::toWire(OutputBuffer& buffer) const {
    toWireHelper(*impl_, buffer);
}

void
NSEC3::toWire(AbstractMessageRenderer& renderer) const {
    toWireHelper(*impl_, renderer);
}

namespace {
// This is a helper subroutine for compare().  It compares two binary
// data stored in vector<uint8_t> objects based on the "Canonical RR Ordering"
// as defined in Section 6.3 of RFC4034, that is, the data are treated
// "as a left-justified unsigned octet sequence in which the absence of an
// octet sorts before a zero octet."
//
// If check_length_first is true, it treats the compared data as if they
// began with a single-octet "length" field whose value is the size of the
// corresponding vector.  In this case, if the sizes of the two vectors are
// different the shorter one is always considered the "smaller"; the contents
// of the vector don't matter.
//
// This function returns:
// -1 if v1 is considered smaller than v2
// 1 if v1 is considered larger than v2
// 0 otherwise
int
compareVectors(const vector<uint8_t>& v1, const vector<uint8_t>& v2,
               bool check_length_first = true)
{
    const size_t len1 = v1.size();
    const size_t len2 = v2.size();
    if (check_length_first && len1 != len2) {
        return (len1 - len2);
    }
    const size_t cmplen = min(len1, len2);
    const int cmp = cmplen == 0 ? 0 : memcmp(&v1.at(0), &v2.at(0), cmplen);
    if (cmp != 0) {
        return (cmp);
    } else {
        return (len1 - len2);
    }
}
}

int
NSEC3::compare(const Rdata& other) const {
    const NSEC3& other_nsec3 = dynamic_cast<const NSEC3&>(other);

    if (impl_->hashalg_ != other_nsec3.impl_->hashalg_) {
        return (impl_->hashalg_ < other_nsec3.impl_->hashalg_ ? -1 : 1);
    }
    if (impl_->flags_ != other_nsec3.impl_->flags_) {
        return (impl_->flags_ < other_nsec3.impl_->flags_ ? -1 : 1);
    }
    if (impl_->iterations_ != other_nsec3.impl_->iterations_) {
        return (impl_->iterations_ < other_nsec3.impl_->iterations_ ? -1 : 1);
    }

    int cmp = compareVectors(impl_->salt_, other_nsec3.impl_->salt_);
    if (cmp != 0) {
        return (cmp);
    }
    cmp = compareVectors(impl_->next_, other_nsec3.impl_->next_);
    if (cmp != 0) {
        return (cmp);
    }
    // Note that bitmap doesn't have a dedicated length field, so we shouldn't
    // terminate the comparison just because the lengths are different.
    return (compareVectors(impl_->typebits_, other_nsec3.impl_->typebits_,
                           false));
}

uint8_t
NSEC3::getHashalg() const {
    return (impl_->hashalg_);
}

uint8_t
NSEC3::getFlags() const {
    return (impl_->flags_);
}

uint16_t
NSEC3::getIterations() const {
    return (impl_->iterations_);
}

const vector<uint8_t>&
NSEC3::getSalt() const {
    return (impl_->salt_);
}

const vector<uint8_t>&
NSEC3::getNext() const {
    return (impl_->next_);
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
