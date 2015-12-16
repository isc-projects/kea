// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <iostream>
#include <sstream>

#include <boost/lexical_cast.hpp>

#include <util/buffer.h>
#include <util/strutil.h>

#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

#include <dns/rdata/generic/detail/lexer_util.h>

using namespace std;
using namespace isc::util;
using namespace isc::util::str;
using isc::dns::rdata::generic::detail::createNameFromLexer;

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
/// The given string must represent a valid SRV RDATA.  There can be extra
/// space characters at the beginning or end of the text (which are simply
/// ignored), but other extra text, including a new line, will make the
/// construction fail with an exception.
///
/// The TARGET name must be absolute since there's no parameter that
/// specifies the origin name; if it is not absolute, \c MissingNameOrigin
/// exception will be thrown. It must not be represented as a quoted
/// string.
///
/// See the construction that takes \c MasterLexer for other fields.
///
/// \throw Others Exception from the Name and RRTTL constructors.
/// \throw InvalidRdataText Other general syntax errors.
SRV::SRV(const std::string& srv_str) :
    impl_(NULL)
{
    try {
        std::istringstream ss(srv_str);
        MasterLexer lexer;
        lexer.pushSource(ss);

        uint32_t num = lexer.getNextToken(MasterToken::NUMBER).getNumber();
        if (num > 65535) {
            isc_throw(InvalidRdataText, "Invalid SRV priority in: " << srv_str);
        }
        const uint16_t priority = static_cast<uint16_t>(num);

        num = lexer.getNextToken(MasterToken::NUMBER).getNumber();
        if (num > 65535) {
            isc_throw(InvalidRdataText, "Invalid SRV weight in: " << srv_str);
        }
        const uint16_t weight = static_cast<uint16_t>(num);

        num = lexer.getNextToken(MasterToken::NUMBER).getNumber();
        if (num > 65535) {
            isc_throw(InvalidRdataText, "Invalid SRV port in: " << srv_str);
        }
        const uint16_t port = static_cast<uint16_t>(num);

        const Name targetname = createNameFromLexer(lexer, NULL);

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText, "extra input text for SRV: "
                      << srv_str);
        }

        impl_ = new SRVImpl(priority, weight, port, targetname);
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText, "Failed to construct SRV from '" <<
                  srv_str << "': " << ex.what());
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

    const uint16_t priority = buffer.readUint16();
    const uint16_t weight = buffer.readUint16();
    const uint16_t port = buffer.readUint16();
    const Name targetname(buffer);

    impl_ = new SRVImpl(priority, weight, port, targetname);
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual representation
/// of an SRV RDATA.  The TARGET field can be non-absolute if \c origin
/// is non-NULL, in which case \c origin is used to make it absolute.
/// It must not be represented as a quoted string.
///
/// The PRIORITY, WEIGHT and PORT fields must each be a valid decimal
/// representation of an unsigned 16-bit integers respectively.
///
/// \throw MasterLexer::LexerError General parsing error such as missing field.
/// \throw Other Exceptions from the Name and RRTTL constructors if
/// construction of textual fields as these objects fail.
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
/// \param origin If non NULL, specifies the origin of TARGET when it
/// is non-absolute.
SRV::SRV(MasterLexer& lexer, const Name* origin,
         MasterLoader::Options, MasterLoaderCallbacks&)
{
    uint32_t num = lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (num > 65535) {
        isc_throw(InvalidRdataText, "Invalid SRV priority: " << num);
    }
    const uint16_t priority = static_cast<uint16_t>(num);

    num = lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (num > 65535) {
        isc_throw(InvalidRdataText, "Invalid SRV weight: " << num);
    }
    const uint16_t weight = static_cast<uint16_t>(num);

    num = lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (num > 65535) {
        isc_throw(InvalidRdataText, "Invalid SRV port: " << num);
    }
    const uint16_t port = static_cast<uint16_t>(num);

    const Name targetname = createNameFromLexer(lexer, origin);

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
    if (this == &source) {
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
