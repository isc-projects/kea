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

#include <stdint.h>
#include <string.h>

#include <string>
#include <vector>

#include <util/buffer.h>
#include <dns/exceptions.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rdata/generic/detail/txt_like.h>

using namespace std;
using namespace isc::util;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

TXT&
TXT::operator=(const TXT& source) {
    if (impl_ == source.impl_) {
        return (*this);
    }

    TXTImpl* newimpl = new TXTImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

TXT::~TXT() {
    delete impl_;
}

TXT::TXT(InputBuffer& buffer, size_t rdata_len) :
    impl_(new TXTImpl(buffer, rdata_len))
{}

/// \brief Constructor using the master lexer.
///
/// This implementation only uses the \c lexer parameters; others are
/// ignored.
///
/// \throw CharStringTooLong the parameter string length exceeds maximum.
/// \throw InvalidRdataText the method cannot process the parameter data
///
/// \param lexer A \c MasterLexer object parsing a master file for this
/// RDATA.
TXT::TXT(MasterLexer& lexer, const Name*, MasterLoader::Options,
         MasterLoaderCallbacks&) :
    impl_(new TXTImpl(lexer))
{}

TXT::TXT(const std::string& txtstr) :
    impl_(new TXTImpl(txtstr))
{}

TXT::TXT(const TXT& other) :
    Rdata(), impl_(new TXTImpl(*other.impl_))
{}

void
TXT::toWire(OutputBuffer& buffer) const {
    impl_->toWire(buffer);
}

void
TXT::toWire(AbstractMessageRenderer& renderer) const {
    impl_->toWire(renderer);
}

string
TXT::toText() const {
    return (impl_->toText());
}

int
TXT::compare(const Rdata& other) const {
    const TXT& other_txt = dynamic_cast<const TXT&>(other);

    return (impl_->compare(*other_txt.impl_));
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
