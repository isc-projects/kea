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

/// \brief Constructor from string.
///
/// A copy of the implementation object is allocated and constructed.
DLV::DLV(const string& ds_str) :
    impl_(new DLVImpl(ds_str))
{}

/// \brief Constructor from wire-format data.
///
/// A copy of the implementation object is allocated and constructed.
DLV::DLV(InputBuffer& buffer, size_t rdata_len) :
    impl_(new DLVImpl(buffer, rdata_len))
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
    if (impl_ == source.impl_) {
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
