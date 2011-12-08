// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <string>

#include <util/buffer.h>
#include <util/encode/hex.h>

#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

#include <dns/rdata/generic/detail/ds_like.h>

using namespace std;
using namespace isc::util;
using namespace isc::util::encode;
using namespace isc::dns::rdata::generic::detail;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

DS::DS(const string& ds_str) :
    impl_(new DSImpl(ds_str))
{}

DS::DS(InputBuffer& buffer, size_t rdata_len) :
    impl_(new DSImpl(buffer, rdata_len))
{}

DS::DS(const DS& source) :
    Rdata(), impl_(new DSImpl(*source.impl_))
{}

DS&
DS::operator=(const DS& source) {
    if (impl_ == source.impl_) {
        return (*this);
    }

    DSImpl* newimpl = new DSImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

DS::~DS() {
    delete impl_;
}

string
DS::toText() const {
    return (impl_->toText());
}

void
DS::toWire(OutputBuffer& buffer) const {
    impl_->toWire(buffer);
}

void
DS::toWire(AbstractMessageRenderer& renderer) const {
    impl_->toWire(renderer);
}

int
DS::compare(const Rdata& other) const {
    const DS& other_ds = dynamic_cast<const DS&>(other);

    return (impl_->compare(*other_ds.impl_));
}

uint16_t
DS::getTag() const {
    return (impl_->getTag());
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
