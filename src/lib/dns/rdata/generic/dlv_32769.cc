// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

/// \brief Constructor from string.
///
/// A copy of the implementation object is allocated and constructed.
DLV::DLV(const std::string& ds_str) :
    impl_(new DLVImpl(ds_str))
{}

/// \brief Constructor from wire-format data.
///
/// A copy of the implementation object is allocated and constructed.
DLV::DLV(InputBuffer& buffer, size_t rdata_len) :
    impl_(new DLVImpl(buffer, rdata_len))
{}

DLV::DLV(MasterLexer& lexer, const Name* origin, MasterLoader::Options options,
         MasterLoaderCallbacks& callbacks) :
    impl_(new DLVImpl(lexer, origin, options, callbacks))
{}

/// \brief Copy constructor
///
/// A copy of the implementation object is allocated and constructed.
DLV::DLV(const DLV& source) :
    Rdata(), impl_(new DLVImpl(*source.impl_))
{}

/// \brief Assignment operator
///
/// PIMPL-induced logic
DLV&
DLV::operator=(const DLV& source) {
    if (this == &source) {
        return (*this);
    }

    DLVImpl* newimpl = new DLVImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

/// \brief Destructor
///
/// Deallocates an internal resource.
DLV::~DLV() {
    delete impl_;
}

/// \brief Convert the \c DLV to a string.
///
/// A pass-thru to the corresponding implementation method.
string
DLV::toText() const {
    return (impl_->toText());
}

/// \brief Render the \c DLV in the wire format to a OutputBuffer object
///
/// A pass-thru to the corresponding implementation method.
void
DLV::toWire(OutputBuffer& buffer) const {
    impl_->toWire(buffer);
}

/// \brief Render the \c DLV in the wire format to a AbstractMessageRenderer
/// object
///
/// A pass-thru to the corresponding implementation method.
void
DLV::toWire(AbstractMessageRenderer& renderer) const {
    impl_->toWire(renderer);
}

/// \brief Compare two instances of \c DLV RDATA.
///
/// The type check is performed here. Otherwise, a pass-thru to the
/// corresponding implementation method.
int
DLV::compare(const Rdata& other) const {
    const DLV& other_ds = dynamic_cast<const DLV&>(other);

    return (impl_->compare(*other_ds.impl_));
}

/// \brief Tag accessor
uint16_t
DLV::getTag() const {
    return (impl_->getTag());
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
