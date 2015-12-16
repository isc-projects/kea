// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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

DS::DS(const std::string& ds_str) :
    impl_(new DSImpl(ds_str))
{}

DS::DS(InputBuffer& buffer, size_t rdata_len) :
    impl_(new DSImpl(buffer, rdata_len))
{}

DS::DS(MasterLexer& lexer, const Name* origin, MasterLoader::Options options,
       MasterLoaderCallbacks& callbacks) :
    impl_(new DSImpl(lexer, origin, options, callbacks))
{}

DS::DS(const DS& source) :
    Rdata(), impl_(new DSImpl(*source.impl_))
{}

DS&
DS::operator=(const DS& source) {
    if (this == &source) {
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
