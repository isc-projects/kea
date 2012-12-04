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

/// This class implements the basic interfaces inherited from the abstract
/// \c rdata::Rdata class. The semantics of the class is provided by
/// a copy of instantiated TXTLikeImpl class common to both TXT and SPF.
#include <dns/rdata/generic/detail/txt_like.h>

using namespace std;
using namespace isc::util;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

/// \brief The assignment operator
///
/// It internally allocates a resource, and if it fails a corresponding
/// standard exception will be thrown.
/// This method never throws an exception otherwise.
SPF&
SPF::operator=(const SPF& source) {
    if (impl_ == source.impl_) {
        return (*this);
    }

    SPFImpl* newimpl = new SPFImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

/// \brief The destructor
SPF::~SPF() {
    delete impl_;
}

/// \brief Constructor from wire-format data.
///
/// It internally allocates a resource, and if it fails a corresponding
/// standard exception will be thrown.
SPF::SPF(InputBuffer& buffer, size_t rdata_len) :
    impl_(new SPFImpl(buffer, rdata_len))
{}


/// \brief Constructor from TBD
SPF::SPF(MasterLexer& lexer, const Name* origin,
         MasterLoader::Options options, MasterLoaderCallbacks& callbacks) :
    impl_(new SPFImpl(lexer, origin, options, callbacks))
{}

/// \brief Constructor from string.
///
/// It internally allocates a resource, and if it fails a corresponding
/// standard exception will be thrown.
SPF::SPF(const std::string& txtstr) :
    impl_(new SPFImpl(txtstr))
{}

/// \brief Copy constructor
///
/// It internally allocates a resource, and if it fails a corresponding
/// standard exception will be thrown.
SPF::SPF(const SPF& other) :
    Rdata(), impl_(new SPFImpl(*other.impl_))
{}

/// \brief Render the \c SPF in the wire format to a OutputBuffer object
///
/// \return is the return of the corresponding implementation method.
void
SPF::toWire(OutputBuffer& buffer) const {
    impl_->toWire(buffer);
}

/// \brief Render the \c SPF in the wire format to an AbstractMessageRenderer
/// object
///
/// \return is the return of the corresponding implementation method.
void
SPF::toWire(AbstractMessageRenderer& renderer) const {
    impl_->toWire(renderer);
}

/// \brief Convert the \c SPF to a string.
///
/// \return is the return of the corresponding implementation method.
string
SPF::toText() const {
    return (impl_->toText());
}

/// \brief Compare two instances of \c SPF RDATA.
///
/// This method compares \c this and the \c other \c SPF objects.
///
/// This method is expected to be used in a polymorphic way, and the
/// parameter to compare against is therefore of the abstract \c Rdata class.
/// However, comparing two \c Rdata objects of different RR types
/// is meaningless, and \c other must point to a \c SPF object;
/// otherwise, the standard \c bad_cast exception will be thrown.
///
/// \param other the right-hand operand to compare against.
/// \return is the return of the corresponding implementation method.
int
SPF::compare(const Rdata& other) const {
    const SPF& other_txt = dynamic_cast<const SPF&>(other);

    return (impl_->compare(*other_txt.impl_));
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
