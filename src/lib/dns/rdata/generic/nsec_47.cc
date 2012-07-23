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

#include <util/encode/base64.h>
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
using namespace isc::util;
using namespace isc::util::encode;
using namespace isc::dns::rdata::generic::detail::nsec;

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

NSEC::NSEC(const std::string& nsec_str) :
    impl_(NULL)
{
    istringstream iss(nsec_str);
    string nextname;

    iss >> nextname;
    if (iss.bad() || iss.fail()) {
        isc_throw(InvalidRdataText, "Invalid NSEC name");
    }
    if (iss.eof()) {
        isc_throw(InvalidRdataText, "NSEC bitmap is missing");
    }

    vector<uint8_t> typebits;
    buildBitmapsFromText("NSEC", iss, typebits);

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
    checkRRTypeBitmaps("NSEC", typebits);

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
    s << impl_->nextname_;
    bitmapsToText(impl_->typebits_, s);
    return (s.str());
}

void
NSEC::toWire(OutputBuffer& buffer) const {
    impl_->nextname_.toWire(buffer);
    buffer.writeData(&impl_->typebits_[0], impl_->typebits_.size());
}

void
NSEC::toWire(AbstractMessageRenderer& renderer) const {
    // Type NSEC is not "well-known", and name compression must be disabled
    // per RFC3597.
    renderer.writeName(impl_->nextname_, false);
    renderer.writeData(&impl_->typebits_[0], impl_->typebits_.size());
}

const Name&
NSEC::getNextName() const {
    return (impl_->nextname_);
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
