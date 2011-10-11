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

#include <stdint.h>
#include <string.h>

#include <string>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <util/encode/base64.h>
#include <dns/exceptions.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

using namespace std;
using namespace isc::util;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

/// \brief Constructor from string.
///
/// \param dhcid_str A base-64 representation of the DHCID binary data.
/// The data is considered to be opaque, but a sanity check is performed.
///
/// <b>Exceptions</b>
///
/// \c dhcid_str must be a valid  BASE-64 string, otherwise an exception
/// of class \c isc::BadValue will be thrown;
/// the binary data should consist of at leat of 3 octets as per RFC4701:
///           < 2 octets >    Identifier type code
///           < 1 octet >     Digest type code
///           < n octets >    Digest (length depends on digest type)
/// If the data is less than 3 octets (i.e. it cannot contain id type code and
/// digest type code), an exception of class \c InvalidRdataLength is thrown.
DHCID::DHCID(const string& dhcid_str) {
    istringstream iss(dhcid_str);
    stringbuf digestbuf;

    iss >> &digestbuf;
    isc::util::encode::decodeBase64(digestbuf.str(), digest_);

    // RFC4701 states DNS software should consider the RDATA section to
    // be opaque, but there must be at least three bytes in the data:
    // < 2 octets >    Identifier type code
    // < 1 octet >     Digest type code
    if (digest_.size() < 3) {
        isc_throw(InvalidRdataLength, "DHCID length " << digest_.size() <<
                  " too short, need at least 3 bytes");
    }
}

/// \brief Constructor from wire-format data.
///
/// \param buffer A buffer storing the wire format data.
/// \param rdata_len The length of the RDATA in bytes
///
/// <b>Exceptions</b>
/// \c InvalidRdataLength is thrown if \c rdata_len is than minimum of 3 octets
DHCID::DHCID(InputBuffer& buffer, size_t rdata_len) {
    if (rdata_len < 3) {
        isc_throw(InvalidRdataLength, "DHCID length " << rdata_len <<
                  " too short, need at least 3 bytes");
    }

    digest_.resize(rdata_len);
    buffer.readData(&digest_[0], rdata_len);
}

/// \brief The copy constructor.
///
/// This trivial copy constructor never throws an exception.
DHCID::DHCID(const DHCID& other) : Rdata(), digest_(other.digest_)
{}

/// \brief Render the \c DHCID in the wire format.
///
/// \param buffer An output buffer to store the wire data.
void
DHCID::toWire(OutputBuffer& buffer) const {
    buffer.writeData(&digest_[0], digest_.size());
}

/// \brief Render the \c DHCID in the wire format into a
/// \c MessageRenderer object.
///
/// \param renderer DNS message rendering context that encapsulates the
/// output buffer in which the \c DHCID is to be stored.
void
DHCID::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeData(&digest_[0], digest_.size());
}

/// \brief Convert the \c DHCID to a string.
///
/// This method returns a \c std::string object representing the \c DHCID.
///
/// \return A string representation of \c DHCID.
string
DHCID::toText() const {
    return (isc::util::encode::encodeBase64(digest_));
}

/// \brief Compare two instances of \c DHCID RDATA.
///
/// See documentation in \c Rdata.
int
DHCID::compare(const Rdata& other) const {
    const DHCID& other_dhcid = dynamic_cast<const DHCID&>(other);

    size_t this_len = digest_.size();
    size_t other_len = other_dhcid.digest_.size();
    size_t cmplen = min(this_len, other_len);
    int cmp = memcmp(&digest_[0], &other_dhcid.digest_[0], cmplen);
    if (cmp != 0) {
        return (cmp);
    } else {
        return ((this_len == other_len) ? 0 : (this_len < other_len) ? -1 : 1);
    }
}

/// \brief Accessor method to get the DHCID digest
///
/// \return A reference to the binary DHCID data
const std::vector<uint8_t>&
DHCID::getDigest() const {
    return (digest_);
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
