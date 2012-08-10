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

#include <iostream>
#include <sstream>

#include <boost/lexical_cast.hpp>

#include <util/buffer.h>
#include <util/strutil.h>

#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

using namespace std;
using namespace isc::util;
using namespace isc::util::str;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

struct SRVImpl {
    // straightforward representation of SRV RDATA fields
    SRVImpl(uint16_t priority, uint16_t weight, uint16_t port,
           const Name& target) :
        priority_(priority), weight_(weight), port_(port),
        target_(target)
    {}

    uint16_t priority_;
    uint16_t weight_;
    uint16_t port_;
    Name target_;
};

/// \brief Constructor from string.
///
/// \c srv_str must be formatted as follows:
/// \code <Priority> <Weight> <Port> <Target>
/// \endcode
/// where
/// - &lt;Priority&gt;, &lt;Weight&gt;, and &lt;Port&gt; are an unsigned
///   16-bit decimal integer.
/// - &lt;Target&gt; is a valid textual representation of domain name.
///
/// An example of valid string is:
/// \code "1 5 1500 example.com." \endcode
///
/// <b>Exceptions</b>
///
/// If &lt;Target&gt; is not a valid domain name, a corresponding exception
/// from the \c Name class will be thrown;
/// if %any of the other bullet points above is not met, an exception of
/// class \c InvalidRdataText will be thrown.
/// This constructor internally involves resource allocation, and if it fails
/// a corresponding standard exception will be thrown.
SRV::SRV(const std::string& srv_str) :
    impl_(NULL)
{
    istringstream iss(srv_str);

    try {
        const int32_t priority = tokenToNum<int32_t, 16>(getToken(iss));
        const int32_t weight = tokenToNum<int32_t, 16>(getToken(iss));
        const int32_t port = tokenToNum<int32_t, 16>(getToken(iss));
        const Name targetname(getToken(iss));

        if (!iss.eof()) {
            isc_throw(InvalidRdataText, "Unexpected input for SRV RDATA: " <<
                    srv_str);
        }

        impl_ = new SRVImpl(priority, weight, port, targetname);
    } catch (const StringTokenError& ste) {
        isc_throw(InvalidRdataText, "Invalid SRV text: " <<
                  ste.what() << ": " << srv_str);
    }
}

/// \brief Constructor from wire-format data.
///
/// When a read operation on \c buffer fails (e.g., due to a corrupted
/// message) a corresponding exception from the \c InputBuffer class will
/// be thrown.
/// If the wire-format data does not end with a valid domain name,
/// a corresponding exception from the \c Name class will be thrown.
/// In addition, this constructor internally involves resource allocation,
/// and if it fails a corresponding standard exception will be thrown.
///
/// According to RFC2782, the Target field must be a non compressed form
/// of domain name.  But this implementation accepts a %SRV RR even if that
/// field is compressed as suggested in RFC3597.
///
/// \param buffer A buffer storing the wire format data.
/// \param rdata_len The length of the RDATA in bytes, normally expected
/// to be the value of the RDLENGTH field of the corresponding RR.
SRV::SRV(InputBuffer& buffer, size_t rdata_len) {
    if (rdata_len < 6) {
        isc_throw(InvalidRdataLength, "SRV too short");
    }

    uint16_t priority = buffer.readUint16();
    uint16_t weight = buffer.readUint16();
    uint16_t port = buffer.readUint16();
    const Name targetname(buffer);

    impl_ = new SRVImpl(priority, weight, port, targetname);
}

/// \brief The copy constructor.
///
/// It internally allocates a resource, and if it fails a corresponding
/// standard exception will be thrown.
/// This constructor never throws an exception otherwise.
SRV::SRV(const SRV& source) :
    Rdata(), impl_(new SRVImpl(*source.impl_))
{}

SRV&
SRV::operator=(const SRV& source) {
    if (impl_ == source.impl_) {
        return (*this);
    }

    SRVImpl* newimpl = new SRVImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

SRV::~SRV() {
    delete impl_;
}

/// \brief Convert the \c SRV to a string.
///
/// The output of this method is formatted as described in the "from string"
/// constructor (\c SRV(const std::string&))).
///
/// If internal resource allocation fails, a corresponding
/// standard exception will be thrown.
///
/// \return A \c string object that represents the \c SRV object.
string
SRV::toText() const {
    using boost::lexical_cast;
    return (lexical_cast<string>(impl_->priority_) +
        " " + lexical_cast<string>(impl_->weight_) +
        " " + lexical_cast<string>(impl_->port_) +
        " " + impl_->target_.toText());
}

/// \brief Render the \c SRV in the wire format without name compression.
///
/// If internal resource allocation fails, a corresponding
/// standard exception will be thrown.
/// This method never throws an exception otherwise.
///
/// \param buffer An output buffer to store the wire data.
void
SRV::toWire(OutputBuffer& buffer) const {
    buffer.writeUint16(impl_->priority_);
    buffer.writeUint16(impl_->weight_);
    buffer.writeUint16(impl_->port_);
    impl_->target_.toWire(buffer);
}

/// \brief Render the \c SRV in the wire format with taking into account
/// compression.
///
/// As specified in RFC2782, the Target field (a domain name) will not be
/// compressed.  However, the domain name could be a target of compression
/// of other compressible names (though pretty unlikely), the offset
/// information of the algorithm name may be recorded in \c renderer.
///
/// If internal resource allocation fails, a corresponding
/// standard exception will be thrown.
/// This method never throws an exception otherwise.
///
/// \param renderer DNS message rendering context that encapsulates the
/// output buffer and name compression information.
void
SRV::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeUint16(impl_->priority_);
    renderer.writeUint16(impl_->weight_);
    renderer.writeUint16(impl_->port_);
    renderer.writeName(impl_->target_, false);
}

/// \brief Compare two instances of \c SRV RDATA.
///
/// See documentation in \c Rdata.
int
SRV::compare(const Rdata& other) const {
    const SRV& other_srv = dynamic_cast<const SRV&>(other);

    if (impl_->priority_ != other_srv.impl_->priority_) {
        return (impl_->priority_ < other_srv.impl_->priority_ ? -1 : 1);
    }
    if (impl_->weight_ != other_srv.impl_->weight_) {
        return (impl_->weight_ < other_srv.impl_->weight_ ? -1 : 1);
    }
    if (impl_->port_ != other_srv.impl_->port_) {
        return (impl_->port_ < other_srv.impl_->port_ ? -1 : 1);
    }

    return (compareNames(impl_->target_, other_srv.impl_->target_));
}

uint16_t
SRV::getPriority() const {
    return (impl_->priority_);
}

uint16_t
SRV::getWeight() const {
    return (impl_->weight_);
}

uint16_t
SRV::getPort() const {
    return (impl_->port_);
}

const Name&
SRV::getTarget() const {
    return (impl_->target_);
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
