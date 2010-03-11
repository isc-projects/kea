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

#include "config.h"

#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include "base64.h"
#include "buffer.h"
#include "messagerenderer.h"
#include "name.h"
#include "rrtype.h"
#include "rrttl.h"
#include "rdata.h"
#include "rdataclass.h"

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
    } while(!iss.eof());

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

NSEC::NSEC(InputBuffer& buffer, size_t rdata_len)
{
    size_t pos = buffer.getPosition();
    Name nextname(buffer);

    // rdata_len must be sufficiently large to hold non empty bitmap.
    if (rdata_len <= buffer.getPosition() - pos) {
        isc_throw(InvalidRdataLength, "NSEC too short");
    }
    rdata_len -= (buffer.getPosition() - pos);

    vector<uint8_t> typebits(rdata_len);
    buffer.readData(&typebits[0], rdata_len);

    int len = 0;
    for (int i = 0; i < typebits.size(); i += len) {
        if (i + 2 > typebits.size()) {
            isc_throw(InvalidRdata, "Bad NSEC typebits");
        }
        len = typebits[i + 1];
        if (len > 31) {
            isc_throw(InvalidRdata, "Bad NSEC typebits");
        }
        i += 2;
    }

    impl_ = new NSECImpl(nextname, typebits);
}

NSEC::NSEC(const NSEC& source) :
    Rdata(), impl_(new NSECImpl(*source.impl_))
{}

NSEC&
NSEC::operator=(const NSEC& source)
{
    if (impl_ == source.impl_) {
        return (*this);
    }

    NSECImpl* newimpl = new NSECImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

NSEC::~NSEC()
{
    delete impl_;
}

string
NSEC::toText() const
{
    ostringstream s;
    int len = 0;
    s << impl_->nextname_;
    for (int i = 0; i < impl_->typebits_.size(); i += len) {
        assert(i + 2 <= impl_->typebits_.size());
        int window = impl_->typebits_[i];
        len = impl_->typebits_[i + 1];
        assert(len >= 0 && len < 32);
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

    return (s.str());
}

void
NSEC::toWire(OutputBuffer& buffer) const
{
    impl_->nextname_.toWire(buffer);
    buffer.writeData(&impl_->typebits_[0], impl_->typebits_.size());
}

void
NSEC::toWire(MessageRenderer& renderer) const
{
    impl_->nextname_.toWire(renderer);
    renderer.writeData(&impl_->typebits_[0], impl_->typebits_.size());
}

int
NSEC::compare(const Rdata& other) const
{
    const NSEC& other_nsec = dynamic_cast<const NSEC&>(other);

    int cmp = compareNames(impl_->nextname_, other_nsec.impl_->nextname_);
    if (cmp != 0) {
        return (cmp);
    }

    size_t this_len = impl_->typebits_.size();
    size_t other_len = other_nsec.impl_->typebits_.size();
    size_t cmplen = min(this_len, other_len);
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
