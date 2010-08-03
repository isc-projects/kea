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

#include <dns/util/base64.h>
#include <dns/buffer.h>
#include <dns/exceptions.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

#include <stdio.h>
#include <time.h>

using namespace std;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

struct NSECImpl {
    // straightforward representation of NSEC RDATA fields
    NSECImpl(const Name& next, vector<uint8_t> typebits) :
        nextname_(next), typebits_(typebits)
    {}

    Name nextname_;
    vector<uint8_t> typebits_;
};

NSEC::NSEC(const string& nsec_str) :
    impl_(NULL)
{
    istringstream iss(nsec_str);
    string nextname;
    uint8_t bitmap[8 * 1024];       // 64k bits
    vector<uint8_t> typebits;

    iss >> nextname;
    if (iss.bad() || iss.fail()) {
        isc_throw(InvalidRdataText, "Invalid NSEC name");
    }

    memset(bitmap, 0, sizeof(bitmap));
    do { 
        string type;
        int code;
        iss >> type;
        try {
            code = RRType(type).getCode();
            bitmap[code / 8] |= (0x80 >> (code % 8));
        } catch (...) {
            isc_throw(InvalidRdataText, "Invalid RRtype in NSEC");
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

    impl_ = new NSECImpl(Name(nextname), typebits);
}

NSEC::NSEC(InputBuffer& buffer, size_t rdata_len) {
    const size_t pos = buffer.getPosition();
    const Name nextname(buffer);

    // rdata_len must be sufficiently large to hold non empty bitmap.
    if (rdata_len <= buffer.getPosition() - pos) {
        isc_throw(DNSMessageFORMERR,
                  "NSEC RDATA from wire too short: " << rdata_len << "bytes");
    }
    rdata_len -= (buffer.getPosition() - pos);

    vector<uint8_t> typebits(rdata_len);
    buffer.readData(&typebits[0], rdata_len);

    int len = 0;
    bool first = true;
    unsigned int block, lastblock = 0;
    for (int i = 0; i < rdata_len; i += len) {
        if (i + 2 > rdata_len) {
            isc_throw(DNSMessageFORMERR, "NSEC RDATA from wire: "
                      "incomplete bit map field");
        }
        block = typebits[i];
        len = typebits[i + 1];
        // Check that bitmap window blocks are in the correct order.
        if (!first && block <= lastblock) {
            isc_throw(DNSMessageFORMERR, "NSEC RDATA from wire: Disordered "
                      "window blocks found: " << lastblock <<
                      " then " << block);
        }
        // Check for legal length
        if (len < 1 || len > 32) {
            isc_throw(DNSMessageFORMERR, "NSEC RDATA from wire: Invalid bitmap "
                      "length: " << len);
        }
        // Check for overflow.
        i += 2;
        if (i + len > rdata_len) {
            isc_throw(DNSMessageFORMERR, "NSEC RDATA from wire: bitmap length "
                      "too large: " << len);
        }
        // The last octet of the bitmap must be non zero.
        if (typebits[i + len - 1] == 0) {
            isc_throw(DNSMessageFORMERR, "NSEC RDATA from wire: bitmap ending "
                      "an all-zero byte");
        }

        lastblock = block;
        first = false;
    }

    impl_ = new NSECImpl(nextname, typebits);
}

NSEC::NSEC(const NSEC& source) :
    Rdata(), impl_(new NSECImpl(*source.impl_))
{}

NSEC&
NSEC::operator=(const NSEC& source) {
    if (impl_ == source.impl_) {
        return (*this);
    }

    NSECImpl* newimpl = new NSECImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

NSEC::~NSEC() {
    delete impl_;
}

string
NSEC::toText() const {
    ostringstream s;
    int len = 0;
    s << impl_->nextname_;

    // In the following loop we use string::at() rather than operator[].
    // Since the index calculation is a bit complicated, it will be safer
    // and easier to find a bug (if any).  Note that this conversion method
    // is generally not expected to be very efficient, so the slight overhead
    // of at() should be acceptable.
    for (int i = 0; i < impl_->typebits_.size(); i += len) {
        assert(i + 2 <= impl_->typebits_.size());
        const int block = impl_->typebits_.at(i);
        len = impl_->typebits_.at(i + 1);
        assert(len > 0 && len <= 32);
        i += 2;
        for (int j = 0; j < len; j++) {
            if (impl_->typebits_.at(i + j) == 0) {
                continue;
            }
            for (int k = 0; k < 8; k++) {
                if ((impl_->typebits_.at(i + j) & (0x80 >> k)) == 0) {
                    continue;
                }
                const int t = block * 256 + j * 8 + k;
                s << " " << RRType(t);
            }
        }
    }

    return (s.str());
}

void
NSEC::toWire(OutputBuffer& buffer) const {
    impl_->nextname_.toWire(buffer);
    buffer.writeData(&impl_->typebits_[0], impl_->typebits_.size());
}

void
NSEC::toWire(MessageRenderer& renderer) const {
    impl_->nextname_.toWire(renderer);
    renderer.writeData(&impl_->typebits_[0], impl_->typebits_.size());
}

int
NSEC::compare(const Rdata& other) const {
    const NSEC& other_nsec = dynamic_cast<const NSEC&>(other);

    int cmp = compareNames(impl_->nextname_, other_nsec.impl_->nextname_);
    if (cmp != 0) {
        return (cmp);
    }

    const size_t this_len = impl_->typebits_.size();
    const size_t other_len = other_nsec.impl_->typebits_.size();
    const size_t cmplen = min(this_len, other_len);
    cmp = memcmp(&impl_->typebits_[0], &other_nsec.impl_->typebits_[0],
                 cmplen);
    if (cmp != 0) {
        return (cmp);
    } else {
        return ((this_len == other_len) ? 0 : (this_len < other_len) ? -1 : 1);
    }
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
