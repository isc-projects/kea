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

#include <stdio.h>
#include <time.h>

using namespace std;
using namespace isc::dns::rdata::generic::detail::nsec;
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

NSEC3::NSEC3(const string& nsec3_str) :
    impl_(NULL)
{
    istringstream iss(nsec3_str);
    unsigned int hashalg, flags, iterations;
    string iterations_str, salthex, nexthash;

    iss >> hashalg >> flags >> iterations_str >> salthex >> nexthash;
    if (iss.bad() || iss.fail()) {
        isc_throw(InvalidRdataText, "Invalid NSEC3 text: " << nsec3_str);
    }
    if (hashalg > 0xff) {
        isc_throw(InvalidRdataText,
                  "NSEC3 hash algorithm out of range: " << hashalg);
    }
    if (flags > 0xff) {
        isc_throw(InvalidRdataText, "NSEC3 flags out of range: " << flags);
    }
    // Convert iteration.  To reject an invalid case where there's no space
    // between iteration and salt, we extract this field as string and convert
    // to integer.
    try {
        iterations = boost::lexical_cast<unsigned int>(iterations_str);
    } catch (const boost::bad_lexical_cast&) {
        isc_throw(InvalidRdataText, "Bad NSEC3 iteration: " << iterations_str);
    }
    if (iterations > 0xffff) {
        isc_throw(InvalidRdataText, "NSEC3 iterations out of range: " <<
            iterations);
    }

    vector<uint8_t> salt;
    if (salthex != "-") {       // "-" means a 0-length salt
        decodeHex(salthex, salt);
    }
    if (salt.size() > 255) {
        isc_throw(InvalidRdataText, "NSEC3 salt is too long: "
                  << salt.size() << " bytes");
    }

    vector<uint8_t> next;
    decodeBase32Hex(nexthash, next);
    if (next.size() > 255) {
        isc_throw(InvalidRdataText, "NSEC3 hash is too long: "
                  << next.size() << " bytes");
    }

    // For NSEC3 empty bitmap is possible and allowed.
    if (iss.eof()) {
        impl_ = new NSEC3Impl(hashalg, flags, iterations, salt, next,
                              vector<uint8_t>());
        return;
    }

    vector<uint8_t> typebits;
    uint8_t bitmap[8 * 1024];       // 64k bits
    memset(bitmap, 0, sizeof(bitmap));
    do { 
        string type;
        iss >> type;
        if (type.length() != 0) {
            try {
                const int code = RRType(type).getCode();
                bitmap[code / 8] |= (0x80 >> (code % 8));
            } catch (...) {
                isc_throw(InvalidRdataText, "Invalid RRtype in NSEC3");
            }
        }
    } while (!iss.eof());

    for (int window = 0; window < 256; window++) {
        int octet;
        for (octet = 31; octet >= 0; octet--) {
            if (bitmap[window * 32 + octet] != 0) {
                break;
            }
        }
        if (octet < 0)
            continue;
        typebits.push_back(window);
        typebits.push_back(octet + 1);
        for (int i = 0; i <= octet; i++) {
            typebits.push_back(bitmap[window * 32 + i]);
        }
    }

    impl_ = new NSEC3Impl(hashalg, flags, iterations, salt, next, typebits);
}

NSEC3::NSEC3(InputBuffer& buffer, size_t rdata_len) {
    // NSEC3 RR must have at least 5 octets:
    // hash algorithm(1), flags(1), iteration(2), saltlen(1)
    if (rdata_len < 5) {
        isc_throw(DNSMessageFORMERR, "NSEC3 too short, length: " << rdata_len);
    }

    const uint8_t hashalg = buffer.readUint8();
    const uint8_t flags = buffer.readUint8();
    const uint16_t iterations = buffer.readUint16();

    const uint8_t saltlen = buffer.readUint8();
    rdata_len -= 5;
    if (rdata_len < saltlen) {
        isc_throw(DNSMessageFORMERR, "NSEC3 salt length is too large: " <<
                  static_cast<unsigned int>(saltlen));
    }

    vector<uint8_t> salt(saltlen);
    if (saltlen > 0) {
        buffer.readData(&salt[0], saltlen);
        rdata_len -= saltlen;
    }

    if (rdata_len < 1) {
        isc_throw(DNSMessageFORMERR, "NSEC3 too short to contain hash length, "
                  "length: " << rdata_len + saltlen + 5);
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

    impl_ = new NSEC3Impl(hashalg, flags, iterations, salt, next, typebits);
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
    int len = 0;
    for (size_t i = 0; i < impl_->typebits_.size(); i += len) {
        assert(i + 2 <= impl_->typebits_.size());
        int window = impl_->typebits_[i];
        len = impl_->typebits_[i + 1];
        assert(len > 0 && len <= 32);
        i += 2;
        for (int j = 0; j < len; j++) {
            if (impl_->typebits_[i + j] == 0) {
                continue;
            }
            for (int k = 0; k < 8; k++) {
                if ((impl_->typebits_[i + j] & (0x80 >> k)) == 0) {
                    continue;
                }
                int t = window * 256 + j * 8 + k;
                s << " " << RRType(t).toText();
            }
        }
    }

    using namespace boost;
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
int
compareVectors(const vector<uint8_t>& v1, const vector<uint8_t>& v2,
               bool check_length_first = true)
{
    const size_t len1 = v1.size();
    const size_t len2 = v2.size();
    const size_t cmplen = min(len1, len2);
    if (check_length_first && len1 != len2) {
        return (len1 < len2 ? -1 : 1);
    }
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
