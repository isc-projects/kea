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

#include <dns/rdata/generic/detail/ds_like.h>

DLV::DLV(const string& ds_str) :
    impl_(new DLVImpl(ds_str))
{}

DLV::DLV(InputBuffer& buffer, size_t rdata_len) :
    impl_(new DLVImpl(buffer, rdata_len))
{}

DLV::DLV(const DLV& source) :
    Rdata(), impl_(new DLVImpl(*source.impl_))
{}

DLV&
DLV::operator=(const DLV& source) {
    if (impl_ == source.impl_) {
        return (*this);
    }

    DLVImpl* newimpl = new DLVImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

DLV::~DLV() {
    delete impl_;
}

string
DLV::toText() const {
    return (impl_->toText());
}

void
DLV::toWire(OutputBuffer& buffer) const {
    impl_->toWire(buffer);
}

void
DLV::toWire(AbstractMessageRenderer& renderer) const {
    impl_->toWire(renderer);
}

int
DLV::compare(const Rdata& other) const {
    const DLV& other_ds = dynamic_cast<const DLV&>(other);

    return (impl_->compare(*other_ds.impl_));
}

uint16_t
DLV::getTag() const {
    return (impl_->getTag());
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
