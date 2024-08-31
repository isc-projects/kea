// Copyright (C) 2010-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <exceptions/exceptions.h>
#include <exceptions/isc_assert.h>
#include <dns/exceptions.h>
#include <dns/master_lexer.h>
#include <dns/master_loader.h>
#include <dns/master_loader_callbacks.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rcode.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rrtype.h>
#include <dns/time_utils.h>
#include <dns/tsigkey.h>
#include <dns/tsigerror.h>
#include <dns/txt_like.h>
#include <util/buffer.h>
#include <util/encode/encode.h>
#include <util/buffer.h>

#include <cerrno>
#include <cstring>
#include <iomanip>
#include <iostream>
#include <string>
#include <sstream>
#include <vector>

#include <arpa/inet.h> // XXX: for inet_pton/ntop(), not exist in C++ standards
#include <stdio.h>
#include <stdint.h>
#include <sys/socket.h> // for AF_INET/AF_INET6
#include <time.h>

#include <boost/lexical_cast.hpp>
#include <boost/shared_ptr.hpp>

using namespace isc::util;
using namespace isc::util::encode;
using namespace isc::dns;
using isc::dns::rdata::generic::detail::createNameFromLexer;

using namespace std;
using boost::lexical_cast;

namespace isc {
namespace dns {
namespace rdata {
namespace any {

// straightforward representation of TSIG RDATA fields
struct TSIGImpl {
    TSIGImpl(const Name& algorithm, uint64_t time_signed, uint16_t fudge,
             vector<uint8_t>& mac, uint16_t original_id, uint16_t error,
             vector<uint8_t>& other_data) :
        algorithm_(algorithm), time_signed_(time_signed), fudge_(fudge),
        mac_(mac), original_id_(original_id), error_(error),
        other_data_(other_data) {
    }
    TSIGImpl(const Name& algorithm, uint64_t time_signed, uint16_t fudge,
             size_t macsize, const void* mac, uint16_t original_id,
             uint16_t error, size_t other_len, const void* other_data) :
        algorithm_(algorithm), time_signed_(time_signed), fudge_(fudge),
        mac_(static_cast<const uint8_t*>(mac),
             static_cast<const uint8_t*>(mac) + macsize),
        original_id_(original_id), error_(error),
        other_data_(static_cast<const uint8_t*>(other_data),
                    static_cast<const uint8_t*>(other_data) + other_len) {
    }
    template <typename Output>
    void toWireCommon(Output& output) const;

    const Name algorithm_;
    const uint64_t time_signed_;
    const uint16_t fudge_;
    const vector<uint8_t> mac_;
    const uint16_t original_id_;
    const uint16_t error_;
    const vector<uint8_t> other_data_;
};

// helper function for string and lexer constructors
std::unique_ptr<TSIGImpl>
TSIG::constructFromLexer(MasterLexer& lexer, const Name* origin) {
    const Name& algorithm =
        createNameFromLexer(lexer, origin ? origin : &Name::ROOT_NAME());
    const Name& canonical_algorithm_name =
        (algorithm == TSIGKey::HMACMD5_SHORT_NAME()) ?
            TSIGKey::HMACMD5_NAME() : algorithm;

    const string& time_txt =
        lexer.getNextToken(MasterToken::STRING).getString();
    uint64_t time_signed;
    try {
        time_signed = boost::lexical_cast<uint64_t>(time_txt);
    } catch (const boost::bad_lexical_cast&) {
        isc_throw(InvalidRdataText, "Invalid TSIG Time");
    }
    if ((time_signed >> 48) != 0) {
        isc_throw(InvalidRdataText, "TSIG Time out of range");
    }

    const uint32_t fudge = lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (fudge > 0xffff) {
        isc_throw(InvalidRdataText, "TSIG Fudge out of range");
    }
    const uint32_t macsize =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (macsize > 0xffff) {
        isc_throw(InvalidRdataText, "TSIG MAC Size out of range");
    }

    const string& mac_txt = (macsize > 0) ?
            lexer.getNextToken(MasterToken::STRING).getString() : "";
    vector<uint8_t> mac;
    decodeBase64(mac_txt, mac);
    if (mac.size() != macsize) {
        isc_throw(InvalidRdataText, "TSIG MAC Size and data are inconsistent");
    }

    const uint32_t orig_id =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (orig_id > 0xffff) {
        isc_throw(InvalidRdataText, "TSIG Original ID out of range");
    }

    const string& error_txt =
        lexer.getNextToken(MasterToken::STRING).getString();
    uint32_t error = 0;
    // XXX: In the initial implementation we hardcode the mnemonics.
    // We'll soon generalize this.
    if (error_txt == "NOERROR") {
        error = Rcode::NOERROR_CODE;
    } else if (error_txt == "BADSIG") {
        error = TSIGError::BAD_SIG_CODE;
    } else if (error_txt == "BADKEY") {
        error = TSIGError::BAD_KEY_CODE;
    } else if (error_txt == "BADTIME") {
        error = TSIGError::BAD_TIME_CODE;
    } else if (error_txt == "BADMODE") {
        error = TSIGError::BAD_MODE_CODE;
    } else if (error_txt == "BADNAME") {
        error = TSIGError::BAD_NAME_CODE;
    } else if (error_txt == "BADALG") {
        error = TSIGError::BAD_ALG_CODE;
    } else if (error_txt == "BADTRUNC") {
        error = TSIGError::BAD_TRUNC_CODE;
    } else {
        /// we cast to uint32_t and range-check, because casting directly to
        /// uint16_t will convert negative numbers to large positive numbers
        try {
            error = boost::lexical_cast<uint32_t>(error_txt);
        } catch (const boost::bad_lexical_cast&) {
            isc_throw(InvalidRdataText, "Invalid TSIG Error");
        }
        if (error > 0xffff) {
            isc_throw(InvalidRdataText, "TSIG Error out of range");
        }
    }

    const uint32_t otherlen =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (otherlen > 0xffff) {
        isc_throw(InvalidRdataText, "TSIG Other Len out of range");
    }
    const string otherdata_txt = (otherlen > 0) ?
            lexer.getNextToken(MasterToken::STRING).getString() : "";
    vector<uint8_t> other_data;
    decodeBase64(otherdata_txt, other_data);
    if (other_data.size() != otherlen) {
        isc_throw(InvalidRdataText,
                  "TSIG Other Data length does not match Other Len");
    }
    // RFC2845 says Other Data is "empty unless Error == BADTIME".
    // However, we don't enforce that.

    return (std::unique_ptr<TSIGImpl>(new TSIGImpl(canonical_algorithm_name, time_signed, fudge, mac,
                                                   orig_id, error, other_data)));
}

/// \brief Constructor from string.
///
/// The given string must represent a valid TSIG RDATA.  There can be extra
/// space characters at the beginning or end of the text (which are simply
/// ignored), but other extra text, including a new line, will make the
/// construction fail with an exception.
///
/// \c tsig_str must be formatted as follows:
/// \code <Algorithm Name> <Time Signed> <Fudge> <MAC Size> [<MAC>]
/// <Original ID> <Error> <Other Len> [<Other Data>]
/// \endcode
///
/// Note that, since the Algorithm Name field is defined to be "in domain name
/// syntax", but it is not actually a domain name, it does not have to be
/// fully qualified.
///
/// The Error field is an unsigned 16-bit decimal integer or a valid mnemonic
/// as specified in RFC2845.  Currently, "NOERROR", "BADSIG", "BADKEY", and
/// "BADTIME" are supported (case sensitive).  In future versions other
/// representations that are compatible with the DNS RCODE may be supported.
///
/// The MAC and Other Data fields are base-64 encoded strings that do not
/// contain space characters.
/// If the MAC Size field is 0, the MAC field must not appear in \c tsig_str.
/// If the Other Len field is 0, the Other Data field must not appear in
/// \c tsig_str.
/// The decoded data of the MAC field is MAC Size bytes of binary stream.
/// The decoded data of the Other Data field is Other Len bytes of binary
/// stream.
///
/// An example of valid string is:
/// \code "hmac-sha256. 853804800 300 3 AAAA 2845 0 0" \endcode
/// In this example Other Data is missing because Other Len is 0.
///
/// Note that RFC2845 does not define the standard presentation format
/// of %TSIG RR, so the above syntax is implementation specific.
/// This is, however, compatible with the format acceptable to BIND 9's
/// RDATA parser.
///
/// \throw Others Exception from the Name constructors.
/// \throw InvalidRdataText if any fields are out of their valid range,
/// or are incorrect.
/// \throw BadValue if MAC or Other Data is not validly encoded in base-64.
///
/// \param tsig_str A string containing the RDATA to be created
TSIG::TSIG(const std::string& tsig_str) {
    try {
        std::istringstream ss(tsig_str);
        MasterLexer lexer;
        lexer.pushSource(ss);

        impl_ = constructFromLexer(lexer, 0);

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText,
                      "Extra input text for TSIG: " << tsig_str);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText,
                  "Failed to construct TSIG from '" << tsig_str << "': "
                  << ex.what());
    }
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual
/// representation of an TSIG RDATA.
///
/// See \c TSIG::TSIG(const std::string&) for description of the
/// expected RDATA fields.
///
/// \throw MasterLexer::LexerError General parsing error such as
/// missing field.
/// \throw InvalidRdataText if any fields are out of their valid range,
/// or are incorrect.
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
TSIG::TSIG(MasterLexer& lexer, const Name* origin,
           MasterLoader::Options, MasterLoaderCallbacks&) {
    impl_ = constructFromLexer(lexer, origin);
}

/// \brief Constructor from wire-format data.
///
/// When a read operation on \c buffer fails (e.g., due to a corrupted
/// message) a corresponding exception from the \c InputBuffer class will
/// be thrown.
/// If the wire-format data does not begin with a valid domain name,
/// a corresponding exception from the \c Name class will be thrown.
/// In addition, this constructor internally involves resource allocation,
/// and if it fails a corresponding standard exception will be thrown.
///
/// According to RFC3597, the Algorithm field must be a non compressed form
/// of domain name.  But this implementation accepts a %TSIG RR even if that
/// field is compressed.
///
/// \param buffer A buffer storing the wire format data.
/// \param rdata_len The length of the RDATA in bytes, normally expected
/// to be the value of the RDLENGTH field of the corresponding RR.
/// But this constructor does not use this parameter; if necessary, the caller
/// must check consistency between the length parameter and the actual
/// RDATA length.
TSIG::TSIG(InputBuffer& buffer, size_t) {
    Name algorithm(buffer);

    uint8_t time_signed_buf[6];
    buffer.readData(time_signed_buf, sizeof(time_signed_buf));
    const uint64_t time_signed =
        (static_cast<uint64_t>(time_signed_buf[0]) << 40 |
         static_cast<uint64_t>(time_signed_buf[1]) << 32 |
         static_cast<uint64_t>(time_signed_buf[2]) << 24 |
         static_cast<uint64_t>(time_signed_buf[3]) << 16 |
         static_cast<uint64_t>(time_signed_buf[4]) << 8 |
         static_cast<uint64_t>(time_signed_buf[5]));

    const uint16_t fudge = buffer.readUint16();

    const uint16_t mac_size = buffer.readUint16();
    vector<uint8_t> mac(mac_size);
    if (mac_size > 0) {
        buffer.readData(&mac[0], mac_size);
    }

    const uint16_t original_id = buffer.readUint16();
    const uint16_t error = buffer.readUint16();

    const uint16_t other_len = buffer.readUint16();
    vector<uint8_t> other_data(other_len);
    if (other_len > 0) {
        buffer.readData(&other_data[0], other_len);
    }

    const Name& canonical_algorithm_name =
        (algorithm == TSIGKey::HMACMD5_SHORT_NAME()) ?
            TSIGKey::HMACMD5_NAME() : algorithm;
    impl_.reset(new TSIGImpl(canonical_algorithm_name, time_signed, fudge, mac,
                             original_id, error, other_data));
}

TSIG::TSIG(const Name& algorithm, uint64_t time_signed, uint16_t fudge,
           uint16_t mac_size, const void* mac, uint16_t original_id,
           uint16_t error, uint16_t other_len, const void* other_data) {
    // Time Signed is a 48-bit value.
    if ((time_signed >> 48) != 0) {
        isc_throw(OutOfRange, "TSIG Time Signed is too large: " <<
                  time_signed);
    }
    if ((mac_size == 0 && mac) || (mac_size > 0 && !mac)) {
        isc_throw(InvalidParameter, "TSIG MAC size and data inconsistent");
    }
    if ((other_len == 0 && other_data) || (other_len > 0 && !other_data)) {
        isc_throw(InvalidParameter,
                  "TSIG Other data length and data inconsistent");
    }
    const Name& canonical_algorithm_name =
        (algorithm == TSIGKey::HMACMD5_SHORT_NAME()) ?
            TSIGKey::HMACMD5_NAME() : algorithm;
    impl_.reset(new TSIGImpl(canonical_algorithm_name, time_signed, fudge, mac_size,
                             mac, original_id, error, other_len, other_data));
}

/// \brief The copy constructor.
///
/// It internally allocates a resource, and if it fails a corresponding
/// standard exception will be thrown.
/// This constructor never throws an exception otherwise.
TSIG::TSIG(const TSIG& source) : Rdata(), impl_(new TSIGImpl(*source.impl_)) {
}

TSIG&
TSIG::operator=(const TSIG& source) {
    if (this == &source) {
        return (*this);
    }

    impl_.reset(new TSIGImpl(*source.impl_));

    return (*this);
}

TSIG::~TSIG() {
}

/// \brief Convert the \c TSIG to a string.
///
/// The output of this method is formatted as described in the "from string"
/// constructor (\c TSIG(const std::string&))).
///
/// If internal resource allocation fails, a corresponding
/// standard exception will be thrown.
///
/// \return A \c string object that represents the \c TSIG object.
std::string
TSIG::toText() const {
    string result;

    result += impl_->algorithm_.toText() + " " +
        lexical_cast<string>(impl_->time_signed_) + " " +
        lexical_cast<string>(impl_->fudge_) + " " +
        lexical_cast<string>(impl_->mac_.size()) + " ";
    if (!impl_->mac_.empty()) {
        result += encodeBase64(impl_->mac_) + " ";
    }
    result += lexical_cast<string>(impl_->original_id_) + " ";
    result += TSIGError(impl_->error_).toText() + " ";
    result += lexical_cast<string>(impl_->other_data_.size());
    if (!impl_->other_data_.empty()) {
        result += " " + encodeBase64(impl_->other_data_);
    }

    return (result);
}

// Common sequence of toWire() operations used for the two versions of
// toWire().
template <typename Output>
void
TSIGImpl::toWireCommon(Output& output) const {
    output.writeUint16(time_signed_ >> 32);
    output.writeUint32(time_signed_ & 0xffffffff);
    output.writeUint16(fudge_);
    const uint16_t mac_size = mac_.size();
    output.writeUint16(mac_size);
    if (mac_size > 0) {
        output.writeData(&mac_[0], mac_size);
    }
    output.writeUint16(original_id_);
    output.writeUint16(error_);
    const uint16_t other_len = other_data_.size();
    output.writeUint16(other_len);
    if (other_len > 0) {
        output.writeData(&other_data_[0], other_len);
    }
}

/// \brief Render the \c TSIG in the wire format without name compression.
///
/// If internal resource allocation fails, a corresponding
/// standard exception will be thrown.
/// This method never throws an exception otherwise.
///
/// \param buffer An output buffer to store the wire data.
void
TSIG::toWire(OutputBuffer& buffer) const {
    impl_->algorithm_.toWire(buffer);
    impl_->toWireCommon<OutputBuffer>(buffer);
}

/// \brief Render the \c TSIG in the wire format with taking into account
/// compression.
///
/// As specified in RFC3597, the Algorithm field (a domain name) will not
/// be compressed.  However, the domain name could be a target of compression
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
TSIG::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeName(impl_->algorithm_, false);
    impl_->toWireCommon<AbstractMessageRenderer>(renderer);
}

// A helper function commonly used for TSIG::compare().
int
vectorComp(const vector<uint8_t>& v1, const vector<uint8_t>& v2) {
    const size_t this_size = v1.size();
    const size_t other_size = v2.size();
    if (this_size != other_size) {
        return (this_size < other_size ? -1 : 1);
    }
    if (this_size > 0) {
        return (memcmp(&v1[0], &v2[0], this_size));
    }
    return (0);
}

/// \brief Compare two instances of \c TSIG RDATA.
///
/// This method compares \c this and the \c other \c TSIG objects
/// in terms of the DNSSEC sorting order as defined in RFC4034, and returns
/// the result as an integer.
///
/// This method is expected to be used in a polymorphic way, and the
/// parameter to compare against is therefore of the abstract \c Rdata class.
/// However, comparing two \c Rdata objects of different RR types
/// is meaningless, and \c other must point to a \c TSIG object;
/// otherwise, the standard \c bad_cast exception will be thrown.
/// This method never throws an exception otherwise.
///
/// \param other the right-hand operand to compare against.
/// \return < 0 if \c this would be sorted before \c other.
/// \return 0 if \c this is identical to \c other in terms of sorting order.
/// \return > 0 if \c this would be sorted after \c other.
int
TSIG::compare(const Rdata& other) const {
    const TSIG& other_tsig = dynamic_cast<const TSIG&>(other);

    const int ncmp = compareNames(impl_->algorithm_,
                                  other_tsig.impl_->algorithm_);
    if (ncmp != 0) {
        return (ncmp);
    }

    if (impl_->time_signed_ != other_tsig.impl_->time_signed_) {
        return (impl_->time_signed_ < other_tsig.impl_->time_signed_ ? -1 : 1);
    }
    if (impl_->fudge_ != other_tsig.impl_->fudge_) {
        return (impl_->fudge_ < other_tsig.impl_->fudge_ ? -1 : 1);
    }
    const int vcmp = vectorComp(impl_->mac_, other_tsig.impl_->mac_);
    if (vcmp != 0) {
        return (vcmp);
    }
    if (impl_->original_id_ != other_tsig.impl_->original_id_) {
        return (impl_->original_id_ < other_tsig.impl_->original_id_ ? -1 : 1);
    }
    if (impl_->error_ != other_tsig.impl_->error_) {
        return (impl_->error_ < other_tsig.impl_->error_ ? -1 : 1);
    }
    return (vectorComp(impl_->other_data_, other_tsig.impl_->other_data_));
}

const Name&
TSIG::getAlgorithm() const {
    return (impl_->algorithm_);
}

uint64_t
TSIG::getTimeSigned() const {
    return (impl_->time_signed_);
}

uint16_t
TSIG::getFudge() const {
    return (impl_->fudge_);
}

uint16_t
TSIG::getMACSize() const {
    return (impl_->mac_.size());
}

const void*
TSIG::getMAC() const {
    if (!impl_->mac_.empty()) {
        return (&impl_->mac_[0]);
    } else {
        return (0);
    }
}

uint16_t
TSIG::getOriginalID() const {
    return (impl_->original_id_);
}

uint16_t
TSIG::getError() const {
    return (impl_->error_);
}

uint16_t
TSIG::getOtherLen() const {
    return (impl_->other_data_.size());
}

const void*
TSIG::getOtherData() const {
    if (!impl_->other_data_.empty()) {
        return (&impl_->other_data_[0]);
    } else {
        return (0);
    }
}

} // end of namespace "any"

namespace ch {

A::A(const std::string&) {
    // TBD
}

A::A(MasterLexer&, const Name*,
     MasterLoader::Options, MasterLoaderCallbacks&) {
    // TBD
}

A::A(InputBuffer&, size_t) {
    // TBD
}

A::A(const A&) : Rdata() {
    // TBD
}

void
A::toWire(OutputBuffer&) const {
    // TBD
}

void
A::toWire(AbstractMessageRenderer&) const {
    // TBD
}

string
A::toText() const {
    // TBD
    isc_throw(InvalidRdataText, "Not implemented yet");
}

int
A::compare(const Rdata&) const {
    // TBD
    return (0);
}

} // end of namespace "ch"

namespace generic {

/// \brief Constructor from string.
///
/// The given string must represent a valid NS RDATA.  There can be extra
/// space characters at the beginning or end of the text (which are simply
/// ignored), but other extra text, including a new line, will make the
/// construction fail with an exception.
///
/// The NSDNAME must be absolute since there's no parameter that
/// specifies the origin name; if it is not absolute, \c
/// MissingNameOrigin exception will be thrown.  These must not be
/// represented as a quoted string.
///
/// \throw Others Exception from the Name and RRTTL constructors.
/// \throw InvalidRdataText Other general syntax errors.
NS::NS(const std::string& namestr) :
    // Fill in dummy name and replace them soon below.
    nsname_(Name::ROOT_NAME()) {
    try {
        std::istringstream ss(namestr);
        MasterLexer lexer;
        lexer.pushSource(ss);

        nsname_ = createNameFromLexer(lexer, 0);

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText, "extra input text for NS: "
                      << namestr);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText, "Failed to construct NS from '" <<
                  namestr << "': " << ex.what());
    }
}

NS::NS(InputBuffer& buffer, size_t) :
    nsname_(buffer) {
    // we don't need rdata_len for parsing.  if necessary, the caller will
    // check consistency.
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual
/// representation of an NS RDATA.  The NSDNAME field can be
/// non-absolute if \c origin is non-null, in which case \c origin is
/// used to make it absolute.  It must not be represented as a quoted
/// string.
///
/// \throw MasterLexer::LexerError General parsing error such as missing field.
/// \throw Other Exceptions from the Name and RRTTL constructors if
/// construction of textual fields as these objects fail.
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
/// \param origin If non null, specifies the origin of NSDNAME when it
/// is non-absolute.
NS::NS(MasterLexer& lexer, const Name* origin,
       MasterLoader::Options, MasterLoaderCallbacks&) :
    nsname_(createNameFromLexer(lexer, origin)) {
}

NS::NS(const NS& other) :
    Rdata(), nsname_(other.nsname_) {
}

void
NS::toWire(OutputBuffer& buffer) const {
    nsname_.toWire(buffer);
}

void
NS::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeName(nsname_);
}

string
NS::toText() const {
    return (nsname_.toText());
}

int
NS::compare(const Rdata& other) const {
    const NS& other_ns = dynamic_cast<const NS&>(other);

    return (compareNames(nsname_, other_ns.nsname_));
}

const Name&
NS::getNSName() const {
    return (nsname_);
}

/// \brief Constructor.
OPT::PseudoRR::PseudoRR(uint16_t code,
                        boost::shared_ptr<std::vector<uint8_t> >& data) :
    code_(code),
    data_(data) {
}

uint16_t
OPT::PseudoRR::getCode() const {
    return (code_);
}

const uint8_t*
OPT::PseudoRR::getData() const {
    return (&(*data_)[0]);
}

uint16_t
OPT::PseudoRR::getLength() const {
    return (data_->size());
}

struct OPTImpl {
    OPTImpl() :
        rdlength_(0) {
    }

    uint16_t rdlength_;
    std::vector<OPT::PseudoRR> pseudo_rrs_;
};

/// \brief Default constructor.
OPT::OPT() :
    impl_(new OPTImpl()) {
}

/// \brief Constructor from string.
///
/// This constructor cannot be used, and always throws an exception.
///
/// \throw InvalidRdataText OPT RR cannot be constructed from text.
OPT::OPT(const std::string&) {
    isc_throw(InvalidRdataText, "OPT RR cannot be constructed from text");
}

/// \brief Constructor with a context of MasterLexer.
///
/// This constructor cannot be used, and always throws an exception.
///
/// \throw InvalidRdataText OPT RR cannot be constructed from text.
OPT::OPT(MasterLexer&, const Name*,
         MasterLoader::Options, MasterLoaderCallbacks&) {
    isc_throw(InvalidRdataText, "OPT RR cannot be constructed from text");
}

OPT::OPT(InputBuffer& buffer, size_t rdata_len) {
    impl_.reset(new OPTImpl());

    while (true) {
        if (rdata_len == 0) {
            break;
        }

        if (rdata_len < 4) {
            isc_throw(InvalidRdataLength,
                      "Pseudo OPT RR record too short: "
                      << rdata_len << " bytes");
        }

        const uint16_t option_code = buffer.readUint16();
        const uint16_t option_length = buffer.readUint16();
        rdata_len -= 4;

        if (static_cast<uint16_t>(impl_->rdlength_ + option_length) <
            impl_->rdlength_) {
            isc_throw(InvalidRdataText,
                      "Option length " << option_length
                      << " would overflow OPT RR RDLEN (currently "
                      << impl_->rdlength_ << ").");
        }

        if (rdata_len < option_length) {
            isc_throw(InvalidRdataLength, "Corrupt pseudo OPT RR record");
        }

        boost::shared_ptr<std::vector<uint8_t> >
            option_data(new std::vector<uint8_t>(option_length));
        buffer.readData(&(*option_data)[0], option_length);
        impl_->pseudo_rrs_.push_back(PseudoRR(option_code, option_data));
        impl_->rdlength_ += option_length;
        rdata_len -= option_length;
    }
}

OPT::OPT(const OPT& other) :
    Rdata(), impl_(new OPTImpl(*other.impl_)) {
}

OPT&
OPT::operator=(const OPT& source) {
    if (this == &source) {
        return (*this);
    }

    impl_.reset(new OPTImpl(*source.impl_));

    return (*this);
}

OPT::~OPT() {
}

std::string
OPT::toText() const {
    isc_throw(isc::InvalidOperation,
              "OPT RRs do not have a presentation format");
}

void
OPT::toWire(OutputBuffer& buffer) const {
    for (auto const& pseudo_rr : impl_->pseudo_rrs_) {
        buffer.writeUint16(pseudo_rr.getCode());
        const uint16_t length = pseudo_rr.getLength();
        buffer.writeUint16(length);
        if (length > 0) {
            buffer.writeData(pseudo_rr.getData(), length);
        }
    }
}

void
OPT::toWire(AbstractMessageRenderer& renderer) const {
    for (auto const& pseudo_rr : impl_->pseudo_rrs_) {
        renderer.writeUint16(pseudo_rr.getCode());
        const uint16_t length = pseudo_rr.getLength();
        renderer.writeUint16(length);
        if (length > 0) {
            renderer.writeData(pseudo_rr.getData(), length);
        }
    }
}

int
OPT::compare(const Rdata&) const {
    isc_throw(isc::InvalidOperation,
              "It is meaningless to compare a set of OPT pseudo RRs; "
              "they have unspecified order");
    return (0);
}

void
OPT::appendPseudoRR(uint16_t code, const uint8_t* data, uint16_t length) {
    // See if it overflows 16-bit length field. We only worry about the
    // pseudo-RR length here, not the whole message length (which should
    // be checked and enforced elsewhere).
    if (static_cast<uint16_t>(impl_->rdlength_ + length) <
        impl_->rdlength_) {
        isc_throw(isc::InvalidParameter,
                  "Option length " << length
                  << " would overflow OPT RR RDLEN (currently "
                  << impl_->rdlength_ << ").");
    }

    boost::shared_ptr<std::vector<uint8_t> >
        option_data(new std::vector<uint8_t>(length));
    if (length != 0) {
        std::memcpy(&(*option_data)[0], data, length);
    }
    impl_->pseudo_rrs_.push_back(PseudoRR(code, option_data));
    impl_->rdlength_ += length;
}

const std::vector<OPT::PseudoRR>&
OPT::getPseudoRRs() const {
    return (impl_->pseudo_rrs_);
}

/// \brief Constructor from string.
///
/// The given string must represent a valid PTR RDATA. There can be
/// extra space characters at the beginning or end of the text (which
/// are simply ignored), but other extra text, including a new line,
/// will make the construction fail with an exception.
///
/// The PTRDNAME must be absolute since there's no parameter that
/// specifies the origin name; if it is not absolute, \c
/// MissingNameOrigin exception will be thrown. These must not be
/// represented as a quoted string.
///
/// \throw Others Exception from the Name and RRTTL constructors.
/// \throw InvalidRdataText Other general syntax errors.
PTR::PTR(const std::string& type_str) :
    // Fill in dummy name and replace them soon below.
    ptr_name_(Name::ROOT_NAME()) {
    try {
        std::istringstream ss(type_str);
        MasterLexer lexer;
        lexer.pushSource(ss);

        ptr_name_ = createNameFromLexer(lexer, 0);

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText, "extra input text for PTR: "
                      << type_str);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText, "Failed to construct PTR from '" <<
                  type_str << "': " << ex.what());
    }
}

PTR::PTR(InputBuffer& buffer, size_t) :
    ptr_name_(buffer) {
    // we don't need rdata_len for parsing.  if necessary, the caller will
    // check consistency.
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual
/// representation of a PTR RDATA.  The PTRDNAME field can be
/// non-absolute if \c origin is non-null, in which case \c origin is
/// used to make it absolute.  It must not be represented as a quoted
/// string.
///
/// \throw MasterLexer::LexerError General parsing error such as missing field.
/// \throw Other Exceptions from the Name and RRTTL constructors if
/// construction of textual fields as these objects fail.
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
/// \param origin If non null, specifies the origin of PTRDNAME when it
/// is non-absolute.
PTR::PTR(MasterLexer& lexer, const Name* origin,
         MasterLoader::Options, MasterLoaderCallbacks&) :
    ptr_name_(createNameFromLexer(lexer, origin)) {
}

PTR::PTR(const PTR& source) :
    Rdata(), ptr_name_(source.ptr_name_) {
}

std::string
PTR::toText() const {
    return (ptr_name_.toText());
}

void
PTR::toWire(OutputBuffer& buffer) const {
    ptr_name_.toWire(buffer);
}

void
PTR::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeName(ptr_name_);
}

int
PTR::compare(const Rdata& other) const {
    // The compare method normally begins with this dynamic cast.
    const PTR& other_ptr = dynamic_cast<const PTR&>(other);

    return (compareNames(ptr_name_, other_ptr.ptr_name_));

}

const Name&
PTR::getPTRName() const {
    return (ptr_name_);
}

namespace {
// This is the minimum necessary length of all wire-format RRSIG RDATA:
// - two 8-bit fields (algorithm and labels)
// - two 16-bit fields (covered and tag)
// - three 32-bit fields (original TTL, expire and inception)
const size_t RRSIG_MINIMUM_LEN = 2 * sizeof(uint8_t) + 2 * sizeof(uint16_t) +
    3 * sizeof(uint32_t);
}

struct RRSIGImpl {
    // straightforward representation of RRSIG RDATA fields
    RRSIGImpl(const RRType& covered, uint8_t algorithm, uint8_t labels,
              uint32_t originalttl, uint32_t timeexpire,
              uint32_t timeinception, uint16_t tag, const Name& signer,
              const vector<uint8_t>& signature) :
        covered_(covered), algorithm_(algorithm), labels_(labels),
        originalttl_(originalttl), timeexpire_(timeexpire),
        timeinception_(timeinception), tag_(tag), signer_(signer),
        signature_(signature) {
    }

    const RRType covered_;
    uint8_t algorithm_;
    uint8_t labels_;
    uint32_t originalttl_;
    uint32_t timeexpire_;
    uint32_t timeinception_;
    uint16_t tag_;
    const Name signer_;
    const vector<uint8_t> signature_;
};

// helper function for string and lexer constructors
std::unique_ptr<RRSIGImpl>
RRSIG::constructFromLexer(MasterLexer& lexer, const Name* origin) {
    const RRType covered(lexer.getNextToken(MasterToken::STRING).getString());
    const uint32_t algorithm =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (algorithm > 0xff) {
        isc_throw(InvalidRdataText, "RRSIG algorithm out of range");
    }
    const uint32_t labels =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (labels > 0xff) {
        isc_throw(InvalidRdataText, "RRSIG labels out of range");
    }
    const uint32_t originalttl =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    const uint32_t timeexpire =
        timeFromText32(lexer.getNextToken(MasterToken::STRING).getString());
    const uint32_t timeinception =
        timeFromText32(lexer.getNextToken(MasterToken::STRING).getString());
    const uint32_t tag =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (tag > 0xffff) {
        isc_throw(InvalidRdataText, "RRSIG key tag out of range");
    }
    const Name& signer = createNameFromLexer(lexer, origin);

    string signature_txt;
    string signature_part;
    // Whitespace is allowed within base64 text, so read to the end of input.
    while (true) {
        const MasterToken& token =
            lexer.getNextToken(MasterToken::STRING, true);
        if ((token.getType() == MasterToken::END_OF_FILE) ||
            (token.getType() == MasterToken::END_OF_LINE)) {
            break;
        }
        token.getString(signature_part);
        signature_txt.append(signature_part);
    }
    lexer.ungetToken();

    vector<uint8_t> signature;
    // missing signature is okay
    if (signature_txt.size() > 0) {
        decodeBase64(signature_txt, signature);
    }

    return (std::unique_ptr<RRSIGImpl>(new RRSIGImpl(covered,
                                                     algorithm,
                                                     labels,
                                                     originalttl,
                                                     timeexpire,
                                                     timeinception,
                                                     static_cast<uint16_t>(tag),
                                                     signer,
                                                     signature)));
}

/// \brief Constructor from string.
///
/// The given string must represent a valid RRSIG RDATA.  There can be extra
/// space characters at the beginning or end of the text (which are simply
/// ignored), but other extra text, including a new line, will make the
/// construction fail with an exception.
///
/// The Signer's Name must be absolute since there's no parameter that
/// specifies the origin name; if this is not absolute, \c MissingNameOrigin
/// exception will be thrown.  This must not be represented as a quoted
/// string.
///
/// See the construction that takes \c MasterLexer for other fields.
///
/// \throw Others Exception from the Name constructor.
/// \throw InvalidRdataText Other general syntax errors.
RRSIG::RRSIG(const std::string& rrsig_str) {
    // We use unique_ptr here because if there is an exception in this
    // constructor, the destructor is not called and there could be a
    // leak of the RRSIGImpl that constructFromLexer() returns.
    boost::shared_ptr<RRSIGImpl> impl_ptr;

    try {
        std::istringstream iss(rrsig_str);
        MasterLexer lexer;
        lexer.pushSource(iss);

        impl_ = constructFromLexer(lexer, 0);

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText, "extra input text for RRSIG: "
                      << rrsig_str);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText, "Failed to construct RRSIG from '" <<
                  rrsig_str << "': " << ex.what());
    }
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual representation
/// of an RRSIG RDATA.  The Signer's Name fields can be non absolute if \c
/// origin is non null, in which case \c origin is used to make it absolute.
/// This must not be represented as a quoted string.
///
/// The Original TTL field is a valid decimal representation of an unsigned
/// 32-bit integer. Note that alternate textual representations of \c RRTTL,
/// such as "1H" for 3600 seconds, are not allowed here.
///
/// \throw MasterLexer::LexerError General parsing error such as missing field.
/// \throw Other Exceptions from the Name constructor if
/// construction of textual fields as these objects fail.
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
/// \param origin If non null, specifies the origin of Signer's Name when
/// it is non absolute.
RRSIG::RRSIG(MasterLexer& lexer, const Name* origin,
             MasterLoader::Options, MasterLoaderCallbacks&) {
    impl_ = constructFromLexer(lexer, origin);
}

RRSIG::RRSIG(InputBuffer& buffer, size_t rdata_len) {
    size_t pos = buffer.getPosition();

    if (rdata_len < RRSIG_MINIMUM_LEN) {
        isc_throw(InvalidRdataLength, "RRSIG too short");
    }

    RRType covered(buffer);
    uint8_t algorithm = buffer.readUint8();
    uint8_t labels = buffer.readUint8();
    uint32_t originalttl = buffer.readUint32();
    uint32_t timeexpire = buffer.readUint32();
    uint32_t timeinception = buffer.readUint32();
    uint16_t tag = buffer.readUint16();
    Name signer(buffer);

    // rdata_len must be sufficiently large to hold non empty signature data.
    if (rdata_len <= buffer.getPosition() - pos) {
        isc_throw(InvalidRdataLength, "RRSIG too short");
    }
    rdata_len -= (buffer.getPosition() - pos);

    vector<uint8_t> signature(rdata_len);
    buffer.readData(&signature[0], rdata_len);

    impl_.reset(new RRSIGImpl(covered, algorithm, labels,
                              originalttl, timeexpire, timeinception, tag,
                              signer, signature));
}

RRSIG::RRSIG(const RRSIG& source) :
    Rdata(), impl_(new RRSIGImpl(*source.impl_)) {
}

RRSIG&
RRSIG::operator=(const RRSIG& source) {
    if (this == &source) {
        return (*this);
    }

    impl_.reset(new RRSIGImpl(*source.impl_));

    return (*this);
}

RRSIG::~RRSIG() {
}

string
RRSIG::toText() const {
    return (impl_->covered_.toText() +
            " " + boost::lexical_cast<string>(static_cast<int>(impl_->algorithm_))
            + " " + boost::lexical_cast<string>(static_cast<int>(impl_->labels_))
            + " " + boost::lexical_cast<string>(impl_->originalttl_)
            + " " + timeToText32(impl_->timeexpire_)
            + " " + timeToText32(impl_->timeinception_)
            + " " + boost::lexical_cast<string>(impl_->tag_)
            + " " + impl_->signer_.toText()
            + " " + encodeBase64(impl_->signature_));
}

void
RRSIG::toWire(OutputBuffer& buffer) const {
    impl_->covered_.toWire(buffer);
    buffer.writeUint8(impl_->algorithm_);
    buffer.writeUint8(impl_->labels_);
    buffer.writeUint32(impl_->originalttl_);
    buffer.writeUint32(impl_->timeexpire_);
    buffer.writeUint32(impl_->timeinception_);
    buffer.writeUint16(impl_->tag_);
    impl_->signer_.toWire(buffer);
    buffer.writeData(&impl_->signature_[0], impl_->signature_.size());
}

void
RRSIG::toWire(AbstractMessageRenderer& renderer) const {
    impl_->covered_.toWire(renderer);
    renderer.writeUint8(impl_->algorithm_);
    renderer.writeUint8(impl_->labels_);
    renderer.writeUint32(impl_->originalttl_);
    renderer.writeUint32(impl_->timeexpire_);
    renderer.writeUint32(impl_->timeinception_);
    renderer.writeUint16(impl_->tag_);
    renderer.writeName(impl_->signer_, false);
    renderer.writeData(&impl_->signature_[0], impl_->signature_.size());
}

int
RRSIG::compare(const Rdata& other) const {
    const RRSIG& other_rrsig = dynamic_cast<const RRSIG&>(other);

    if (impl_->covered_.getCode() != other_rrsig.impl_->covered_.getCode()) {
        return (impl_->covered_.getCode() <
                other_rrsig.impl_->covered_.getCode() ? -1 : 1);
    }
    if (impl_->algorithm_ != other_rrsig.impl_->algorithm_) {
        return (impl_->algorithm_ < other_rrsig.impl_->algorithm_ ? -1 : 1);
    }
    if (impl_->labels_ != other_rrsig.impl_->labels_) {
        return (impl_->labels_ < other_rrsig.impl_->labels_ ? -1 : 1);
    }
    if (impl_->originalttl_ != other_rrsig.impl_->originalttl_) {
        return (impl_->originalttl_ < other_rrsig.impl_->originalttl_ ?
                -1 : 1);
    }
    if (impl_->timeexpire_ != other_rrsig.impl_->timeexpire_) {
        return (impl_->timeexpire_ < other_rrsig.impl_->timeexpire_ ?
                -1 : 1);
    }
    if (impl_->timeinception_ != other_rrsig.impl_->timeinception_) {
        return (impl_->timeinception_ < other_rrsig.impl_->timeinception_ ?
                -1 : 1);
    }
    if (impl_->tag_ != other_rrsig.impl_->tag_) {
        return (impl_->tag_ < other_rrsig.impl_->tag_ ? -1 : 1);
    }

    int cmp = compareNames(impl_->signer_, other_rrsig.impl_->signer_);
    if (cmp != 0) {
        return (cmp);
    }

    size_t this_len = impl_->signature_.size();
    size_t other_len = other_rrsig.impl_->signature_.size();
    size_t cmplen = min(this_len, other_len);
    cmp = memcmp(&impl_->signature_[0], &other_rrsig.impl_->signature_[0],
                 cmplen);
    if (cmp != 0) {
        return (cmp);
    } else {
        return ((this_len == other_len) ? 0 : (this_len < other_len) ? -1 : 1);
    }
}

const RRType&
RRSIG::typeCovered() const {
    return (impl_->covered_);
}

SOA::SOA(InputBuffer& buffer, size_t) :
    mname_(buffer), rname_(buffer) {
    // we don't need rdata_len for parsing.  if necessary, the caller will
    // check consistency.
    buffer.readData(numdata_, sizeof(numdata_));
}

namespace {
void
fillParameters(MasterLexer& lexer, uint8_t numdata[20]) {
    // Copy serial, refresh, retry, expire, minimum.  We accept the extended
    // TTL-compatible style for the latter four.
    OutputBuffer buffer(20);
    buffer.writeUint32(lexer.getNextToken(MasterToken::NUMBER).getNumber());
    for (int i = 0; i < 4; ++i) {
        buffer.writeUint32(RRTTL(lexer.getNextToken(MasterToken::STRING).
                                 getString()).getValue());
    }
    memcpy(numdata,  buffer.getData(), buffer.getLength());
}
}

/// \brief Constructor from string.
///
/// The given string must represent a valid SOA RDATA.  There can be extra
/// space characters at the beginning or end of the text (which are simply
/// ignored), but other extra text, including a new line, will make the
/// construction fail with an exception.
///
/// The MNAME and RNAME must be absolute since there's no parameter that
/// specifies the origin name; if these are not absolute, \c MissingNameOrigin
/// exception will be thrown.  These must not be represented as a quoted
/// string.
///
/// See the construction that takes \c MasterLexer for other fields.
///
/// \throw Others Exception from the Name and RRTTL constructors.
/// \throw InvalidRdataText Other general syntax errors.
SOA::SOA(const std::string& soastr) :
    // Fill in dummy name and replace them soon below.
    mname_(Name::ROOT_NAME()), rname_(Name::ROOT_NAME()) {
    try {
        std::istringstream ss(soastr);
        MasterLexer lexer;
        lexer.pushSource(ss);

        mname_ = createNameFromLexer(lexer, 0);
        rname_ = createNameFromLexer(lexer, 0);
        fillParameters(lexer, numdata_);

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText, "extra input text for SOA: "
                      << soastr);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText, "Failed to construct SOA from '" <<
                  soastr << "': " << ex.what());
    }
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual representation
/// of an SOA RDATA.  The MNAME and RNAME fields can be non absolute if
/// \c origin is non null, in which case \c origin is used to make them
/// absolute.  These must not be represented as a quoted string.
///
/// The REFRESH, RETRY, EXPIRE, and MINIMUM fields can be either a valid
/// decimal representation of an unsigned 32-bit integer or other
/// valid textual representation of \c RRTTL such as "1H" (which means 3600).
///
/// \throw MasterLexer::LexerError General parsing error such as missing field.
/// \throw Other Exceptions from the Name and RRTTL constructors if
/// construction of textual fields as these objects fail.
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
/// \param origin If non null, specifies the origin of MNAME and RNAME when
/// they are non absolute.
SOA::SOA(MasterLexer& lexer, const Name* origin,
         MasterLoader::Options, MasterLoaderCallbacks&) :
    mname_(createNameFromLexer(lexer, origin)),
    rname_(createNameFromLexer(lexer, origin)) {
    fillParameters(lexer, numdata_);
}

SOA::SOA(const Name& mname, const Name& rname, uint32_t serial,
         uint32_t refresh, uint32_t retry, uint32_t expire, uint32_t minimum) :
    mname_(mname), rname_(rname) {
    OutputBuffer b(20);
    b.writeUint32(serial);
    b.writeUint32(refresh);
    b.writeUint32(retry);
    b.writeUint32(expire);
    b.writeUint32(minimum);
    isc_throw_assert(b.getLength() == sizeof(numdata_));
    memcpy(numdata_, b.getData(), sizeof(numdata_));
}

SOA::SOA(const SOA& other) :
    Rdata(), mname_(other.mname_), rname_(other.rname_) {
    memcpy(numdata_, other.numdata_, sizeof(numdata_));
}

void
SOA::toWire(OutputBuffer& buffer) const {
    mname_.toWire(buffer);
    rname_.toWire(buffer);
    buffer.writeData(numdata_, sizeof(numdata_));
}

void
SOA::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeName(mname_);
    renderer.writeName(rname_);
    renderer.writeData(numdata_, sizeof(numdata_));
}

Serial
SOA::getSerial() const {
    InputBuffer b(numdata_, sizeof(numdata_));
    return (Serial(b.readUint32()));
}

uint32_t
SOA::getMinimum() const {
    // Make sure the buffer access is safe.
    BOOST_STATIC_ASSERT(sizeof(numdata_) ==
                        sizeof(uint32_t) * 4 + sizeof(uint32_t));

    InputBuffer b(&numdata_[sizeof(uint32_t) * 4], sizeof(uint32_t));
    return (b.readUint32());
}

string
SOA::toText() const {
    InputBuffer b(numdata_, sizeof(numdata_));
    uint32_t serial = b.readUint32();
    uint32_t refresh = b.readUint32();
    uint32_t retry = b.readUint32();
    uint32_t expire = b.readUint32();
    uint32_t minimum = b.readUint32();

    return (mname_.toText() + " " + rname_.toText() + " " +
            lexical_cast<string>(serial) + " " +
            lexical_cast<string>(refresh) + " " +
            lexical_cast<string>(retry) + " " +
            lexical_cast<string>(expire) + " " +
            lexical_cast<string>(minimum));
}

int
SOA::compare(const Rdata& other) const {
    const SOA& other_soa = dynamic_cast<const SOA&>(other);

    int order = compareNames(mname_, other_soa.mname_);
    if (order != 0) {
        return (order);
    }

    order = compareNames(rname_, other_soa.rname_);
    if (order != 0) {
        return (order);
    }

    return (memcmp(numdata_, other_soa.numdata_, sizeof(numdata_)));
}

const uint16_t TKEY::GSS_API_MODE = 3;

// straightforward representation of TKEY RDATA fields
struct TKEYImpl {
    /// \brief Constructor from RDATA field parameters.
    ///
    /// \param algorithm The DNS name of the algorithm e.g. gss-tsig.
    /// \param inception The inception time (in seconds since 1970).
    /// \param expire The expire time (in seconds since 1970).
    /// \param mode The mode e.g. Diffie-Hellman (2) or GSS-API (3).
    /// \param error The error code (extended error space shared with TSIG).
    /// \param key The key (can be empty).
    /// \param other_data The other data (can be and usually is empty).
    TKEYImpl(const Name& algorithm, uint32_t inception, uint32_t expire,
             uint16_t mode, uint16_t error, vector<uint8_t>& key,
             vector<uint8_t>& other_data) :
      algorithm_(algorithm), inception_(inception), expire_(expire),
      mode_(mode), error_(error), key_(key), other_data_(other_data) {
    }

    /// \brief Constructor from RDATA field parameters.
    ///
    /// \param algorithm The DNS name of the algorithm e.g. gss-tsig.
    /// \param inception The inception time (in seconds since 1970).
    /// \param expire The expire time (in seconds since 1970).
    /// \param mode The mode e.g. Diffie-Hellman (2) or GSS-API (3).
    /// \param error The error code (extended error space shared with TSIG).
    /// \param key_len The key length (0 means no key).
    /// \param key The key (can be 0).
    /// \param other_len The other data length (0 means no other data).
    /// \param other_data The other data (can be and usually is 0).
    TKEYImpl(const Name& algorithm, uint32_t inception, uint32_t expire,
             uint16_t mode, uint16_t error, size_t key_len,
             const void* key, size_t other_len, const void* other_data) :
        algorithm_(algorithm), inception_(inception), expire_(expire),
        mode_(mode), error_(error),
        key_(key_len > 0 ?
             vector<uint8_t>(static_cast<const uint8_t*>(key),
                             static_cast<const uint8_t*>(key) + key_len) :
             vector<uint8_t>(key_len)),
        other_data_(other_len > 0 ?
                    vector<uint8_t>(static_cast<const uint8_t*>(other_data),
                                    static_cast<const uint8_t*>(other_data) +
                                    other_len) :
                    vector<uint8_t>(other_len)) {
    }

    /// \brief Common part of toWire methods.
    /// \tparam Output \c OutputBuffer or \c AbstractMessageRenderer.
    template <typename Output>
    void toWireCommon(Output& output) const;

    /// \brief The DNS name of the algorithm e.g. gss-tsig.
    const Name algorithm_;

    /// \brief The inception time (in seconds since 1970).
    const uint32_t inception_;

    /// \brief The expire time (in seconds since 1970).
    const uint32_t expire_;

    /// \brief The mode e.g. Diffie-Hellman (2) or GSS-API (3).
    const uint16_t mode_;

    /// \brief The error code (extended error space shared with TSIG).
    const uint16_t error_;

    /// \brief The key (can be empty).
    const vector<uint8_t> key_;

    /// \brief The other data (can be and usually is empty).
    const vector<uint8_t> other_data_;
};

// helper function for string and lexer constructors
std::unique_ptr<TKEYImpl>
TKEY::constructFromLexer(MasterLexer& lexer, const Name* origin) {
    const Name& algorithm =
        createNameFromLexer(lexer, origin ? origin : &Name::ROOT_NAME());

    const uint32_t inception =
        timeFromText32(lexer.getNextToken(MasterToken::STRING).getString());

    const uint32_t expire =
        timeFromText32(lexer.getNextToken(MasterToken::STRING).getString());

    /// The mode is either a mnemonic (only one is defined: GSS-API) or
    /// a number.
    const string& mode_txt =
        lexer.getNextToken(MasterToken::STRING).getString();
    uint32_t mode = 0;
    if (mode_txt == "GSS-API") {
        mode = GSS_API_MODE;
    } else {
        /// we cast to uint32_t and range-check, because casting directly to
        /// uint16_t will convert negative numbers to large positive numbers
        try {
            mode = boost::lexical_cast<uint32_t>(mode_txt);
        } catch (const boost::bad_lexical_cast&) {
            isc_throw(InvalidRdataText, "Invalid TKEY Mode");
        }
        if (mode > 0xffff) {
            isc_throw(InvalidRdataText, "TKEY Mode out of range");
        }
    }

    const string& error_txt =
        lexer.getNextToken(MasterToken::STRING).getString();
    uint32_t error = 0;
    // XXX: In the initial implementation we hardcode the mnemonics.
    // We'll soon generalize this.
    if (error_txt == "NOERROR") {
        error = Rcode::NOERROR_CODE;
    } else if (error_txt == "BADSIG") {
        error = TSIGError::BAD_SIG_CODE;
    } else if (error_txt == "BADKEY") {
        error = TSIGError::BAD_KEY_CODE;
    } else if (error_txt == "BADTIME") {
        error = TSIGError::BAD_TIME_CODE;
    } else if (error_txt == "BADMODE") {
        error = TSIGError::BAD_MODE_CODE;
    } else if (error_txt == "BADNAME") {
        error = TSIGError::BAD_NAME_CODE;
    } else if (error_txt == "BADALG") {
        error = TSIGError::BAD_ALG_CODE;
    } else if (error_txt == "BADTRUNC") {
        error = TSIGError::BAD_TRUNC_CODE;
    } else {
        /// we cast to uint32_t and range-check, because casting directly to
        /// uint16_t will convert negative numbers to large positive numbers
        try {
            error = boost::lexical_cast<uint32_t>(error_txt);
        } catch (const boost::bad_lexical_cast&) {
            isc_throw(InvalidRdataText, "Invalid TKEY Error");
        }
        if (error > 0xffff) {
            isc_throw(InvalidRdataText, "TKEY Error out of range");
        }
    }

    const uint32_t keylen =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (keylen > 0xffff) {
        isc_throw(InvalidRdataText, "TKEY Key Len out of range");
    }
    const string keydata_txt = (keylen > 0) ?
            lexer.getNextToken(MasterToken::STRING).getString() : "";
    vector<uint8_t> key_data;
    decodeBase64(keydata_txt, key_data);
    if (key_data.size() != keylen) {
        isc_throw(InvalidRdataText,
                  "TKEY Key Data length does not match Other Len");
    }

    const uint32_t otherlen =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (otherlen > 0xffff) {
        isc_throw(InvalidRdataText, "TKEY Other Len out of range");
    }
    const string otherdata_txt = (otherlen > 0) ?
            lexer.getNextToken(MasterToken::STRING).getString() : "";
    vector<uint8_t> other_data;
    decodeBase64(otherdata_txt, other_data);
    if (other_data.size() != otherlen) {
        isc_throw(InvalidRdataText,
                  "TKEY Other Data length does not match Other Len");
    }
    // RFC2845 says Other Data is "empty unless Error == BADTIME".
    // However, we don't enforce that.

    return (std::unique_ptr<TKEYImpl>(new TKEYImpl(algorithm, inception,
                                                   expire, mode, error,
                                                   key_data, other_data)));
}

/// \brief Constructor from string.
///
/// The given string must represent a valid TKEY RDATA.  There can be extra
/// space characters at the beginning or end of the text (which are simply
/// ignored), but other extra text, including a new line, will make the
/// construction fail with an exception.
///
/// \c tkey_str must be formatted as follows:
/// \code <Algorithm Name> <Inception> <Expire> <Mode> <Error>
/// <Key Len> [<Key Data>] <Other Len> [<Other Data>]
/// \endcode
///
/// Note that, since the Algorithm Name field is defined to be "in domain name
/// syntax", but it is not actually a domain name, it does not have to be
/// fully qualified.
///
/// The Mode field is an unsigned 16-bit decimal integer as specified
/// in RFC2930 or a common mnemonic. Currently only "GSS-API" (case sensitive)
/// is supported ("Diffie-Hellman" is not).
///
/// The Error field is an unsigned 16-bit decimal integer or a valid mnemonic
/// as specified in RFC2845.  Currently, "NOERROR", "BADSIG", "BADKEY",
/// "BADTIME", "BADMODE", "BADNAME", and "BADALG" are supported
/// (case sensitive).  In future versions other representations that
/// are compatible with the DNS RCODE may be supported.
///
/// The Key Data and Other Data fields are base-64 encoded strings that do not
/// contain space characters.
/// If the Key Len field is 0, the Key Data field must not appear in
/// \c tkey_str.
/// If the Other Len field is 0, the Other Data field must not appear in
/// \c tkey_str.
/// The decoded data of the Key Data field is Key Len bytes of binary stream.
/// The decoded data of the Other Data field is Other Len bytes of binary
/// stream.
///
/// An example of valid string is:
/// \code "gss-tsig. 20210501120000 20210501130000 0 3 aabbcc 0" \endcode
/// In this example Other Data is missing because Other Len is 0.
///
/// Note that RFC2930 does not define the standard presentation format
/// of %TKEY RR, so the above syntax is implementation specific.
/// This is, however, compatible with the format acceptable to BIND 9's
/// RDATA parser.
///
/// \throw Others Exception from the Name constructors.
/// \throw InvalidRdataText if any fields are out of their valid range,
/// or are incorrect.
/// \throw BadValue if Key Data or Other Data is not validly encoded
/// in base-64.
///
/// \param tkey_str A string containing the RDATA to be created
TKEY::TKEY(const std::string& tkey_str) {

    try {
        std::istringstream ss(tkey_str);
        MasterLexer lexer;
        lexer.pushSource(ss);

        impl_ = constructFromLexer(lexer, 0);

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText,
                      "Extra input text for TKEY: " << tkey_str);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText,
                  "Failed to construct TKEY from '" << tkey_str << "': "
                  << ex.what());
    }
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual
/// representation of an TKEY RDATA.
///
/// See \c TKEY::TKEY(const std::string&) for description of the
/// expected RDATA fields.
///
/// \throw MasterLexer::LexerError General parsing error such as
/// missing field.
/// \throw InvalidRdataText if any fields are out of their valid range,
/// or are incorrect.
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
TKEY::TKEY(MasterLexer& lexer, const Name* origin,
           MasterLoader::Options, MasterLoaderCallbacks&) {
    impl_ = constructFromLexer(lexer, origin);
}

/// \brief Constructor from wire-format data.
///
/// When a read operation on \c buffer fails (e.g., due to a corrupted
/// message) a corresponding exception from the \c InputBuffer class will
/// be thrown.
/// If the wire-format data does not begin with a valid domain name,
/// a corresponding exception from the \c Name class will be thrown.
/// In addition, this constructor internally involves resource allocation,
/// and if it fails a corresponding standard exception will be thrown.
///
/// According to RFC3597, the Algorithm field must be a non compressed form
/// of domain name.  But this implementation accepts a %TKEY RR even if that
/// field is compressed.
///
/// \param buffer A buffer storing the wire format data.
/// \param rdata_len The length of the RDATA in bytes, normally expected
/// to be the value of the RDLENGTH field of the corresponding RR.
/// But this constructor does not use this parameter; if necessary, the caller
/// must check consistency between the length parameter and the actual
/// RDATA length.
TKEY::TKEY(InputBuffer& buffer, size_t) {
    Name algorithm(buffer);

    const uint32_t inception = buffer.readUint32();

    const uint32_t expire = buffer.readUint32();

    const uint16_t mode = buffer.readUint16();

    const uint16_t error = buffer.readUint16();

    const uint16_t key_len = buffer.readUint16();
    vector<uint8_t> key(key_len);
    if (key_len > 0) {
        buffer.readData(&key[0], key_len);
    }

    const uint16_t other_len = buffer.readUint16();
    vector<uint8_t> other_data(other_len);
    if (other_len > 0) {
        buffer.readData(&other_data[0], other_len);
    }

    impl_.reset(new TKEYImpl(algorithm, inception, expire, mode, error,
                             key, other_data));
}

TKEY::TKEY(const Name& algorithm, uint32_t inception, uint32_t expire,
           uint16_t mode, uint16_t error, uint16_t key_len,
           const void* key, uint16_t other_len, const void* other_data) {
    if ((key_len == 0 && key != 0) || (key_len > 0 && key == 0)) {
        isc_throw(InvalidParameter, "TKEY Key length and data inconsistent");
    }
    if ((other_len == 0 && other_data != 0) ||
        (other_len > 0 && other_data == 0)) {
        isc_throw(InvalidParameter,
                  "TKEY Other data length and data inconsistent");
    }
    impl_.reset(new TKEYImpl(algorithm, inception, expire, mode, error,
                             key_len, key, other_len, other_data));
}

/// \brief The copy constructor.
///
/// It internally allocates a resource, and if it fails a corresponding
/// standard exception will be thrown.
/// This constructor never throws an exception otherwise.
TKEY::TKEY(const TKEY& source) : Rdata(), impl_(new TKEYImpl(*source.impl_)) {
}

TKEY&
TKEY::operator=(const TKEY& source) {
    if (this == &source) {
        return (*this);
    }

    impl_.reset(new TKEYImpl(*source.impl_));

    return (*this);
}

TKEY::~TKEY() {
}

/// \brief Convert the \c TKEY to a string.
///
/// The output of this method is formatted as described in the "from string"
/// constructor (\c TKEY(const std::string&))).
///
/// If internal resource allocation fails, a corresponding
/// standard exception will be thrown.
///
/// \return A \c string object that represents the \c TKEY object.
std::string
TKEY::toText() const {
    string result;

    result += impl_->algorithm_.toText() + " " +
        timeToText32(impl_->inception_) + " " +
        timeToText32(impl_->expire_) + " ";
    if (impl_->mode_ == GSS_API_MODE) {
        result += "GSS-API ";
    } else {
        result += lexical_cast<string>(impl_->mode_) + " ";
    }
    result += TSIGError(impl_->error_).toText() + " " +
        lexical_cast<string>(impl_->key_.size()) + " ";
    if (!impl_->key_.empty()) {
        result += encodeBase64(impl_->key_) + " ";
    }
    result += lexical_cast<string>(impl_->other_data_.size());
    if (!impl_->other_data_.empty()) {
        result += " " + encodeBase64(impl_->other_data_);
    }

    return (result);
}

// Common sequence of toWire() operations used for the two versions of
// toWire().
template <typename Output>
void
TKEYImpl::toWireCommon(Output& output) const {
    output.writeUint32(inception_);
    output.writeUint32(expire_);
    output.writeUint16(mode_);
    output.writeUint16(error_);
    const uint16_t key_len = key_.size();
    output.writeUint16(key_len);
    if (key_len > 0) {
        output.writeData(&key_[0], key_len);
    }
    const uint16_t other_len = other_data_.size();
    output.writeUint16(other_len);
    if (other_len > 0) {
        output.writeData(&other_data_[0], other_len);
    }
}

/// \brief Render the \c TKEY in the wire format without name compression.
///
/// If internal resource allocation fails, a corresponding
/// standard exception will be thrown.
/// This method never throws an exception otherwise.
///
/// \param buffer An output buffer to store the wire data.
void
TKEY::toWire(OutputBuffer& buffer) const {
    impl_->algorithm_.toWire(buffer);
    impl_->toWireCommon<OutputBuffer>(buffer);
}

/// \brief Render the \c TKEY in the wire format with taking into account
/// compression.
///
/// As specified in RFC3597, the Algorithm field (a domain name) will not
/// be compressed.  However, the domain name could be a target of compression
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
TKEY::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeName(impl_->algorithm_, false);
    impl_->toWireCommon<AbstractMessageRenderer>(renderer);
}

// A helper function commonly used for TKEY::compare().
int
vectorComp(const vector<uint8_t>& v1, const vector<uint8_t>& v2) {
    const size_t this_size = v1.size();
    const size_t other_size = v2.size();
    if (this_size != other_size) {
        return (this_size < other_size ? -1 : 1);
    }
    if (this_size > 0) {
        return (memcmp(&v1[0], &v2[0], this_size));
    }
    return (0);
}

/// \brief Compare two instances of \c TKEY RDATA.
///
/// This method compares \c this and the \c other \c TKEY objects
/// in terms of the DNSSEC sorting order as defined in RFC4034, and returns
/// the result as an integer.
///
/// This method is expected to be used in a polymorphic way, and the
/// parameter to compare against is therefore of the abstract \c Rdata class.
/// However, comparing two \c Rdata objects of different RR types
/// is meaningless, and \c other must point to a \c TKEY object;
/// otherwise, the standard \c bad_cast exception will be thrown.
/// This method never throws an exception otherwise.
///
/// \param other the right-hand operand to compare against.
/// \return < 0 if \c this would be sorted before \c other.
/// \return 0 if \c this is identical to \c other in terms of sorting order.
/// \return > 0 if \c this would be sorted after \c other.
int
TKEY::compare(const Rdata& other) const {
    const TKEY& other_tkey = dynamic_cast<const TKEY&>(other);

    const int ncmp = compareNames(impl_->algorithm_,
                                  other_tkey.impl_->algorithm_);
    if (ncmp != 0) {
        return (ncmp);
    }

    if (impl_->inception_ != other_tkey.impl_->inception_) {
        return (impl_->inception_ < other_tkey.impl_->inception_ ? -1 : 1);
    }
    if (impl_->expire_ != other_tkey.impl_->expire_) {
        return (impl_->expire_ < other_tkey.impl_->expire_ ? -1 : 1);
    }
    if (impl_->mode_ != other_tkey.impl_->mode_) {
        return (impl_->mode_ < other_tkey.impl_->mode_ ? -1 : 1);
    }
    if (impl_->error_ != other_tkey.impl_->error_) {
        return (impl_->error_ < other_tkey.impl_->error_ ? -1 : 1);
    }

    const int vcmp = vectorComp(impl_->key_, other_tkey.impl_->key_);
    if (vcmp != 0) {
        return (vcmp);
    }
    return (vectorComp(impl_->other_data_, other_tkey.impl_->other_data_));
}

const Name&
TKEY::getAlgorithm() const {
    return (impl_->algorithm_);
}

uint32_t
TKEY::getInception() const {
    return (impl_->inception_);
}

string
TKEY::getInceptionDate() const {
    return (timeToText32(impl_->inception_));
}

uint32_t
TKEY::getExpire() const {
    return (impl_->expire_);
}

string
TKEY::getExpireDate() const {
    return (timeToText32(impl_->expire_));
}

uint16_t
TKEY::getMode() const {
    return (impl_->mode_);
}

uint16_t
TKEY::getError() const {
    return (impl_->error_);
}

uint16_t
TKEY::getKeyLen() const {
    return (impl_->key_.size());
}

const void*
TKEY::getKey() const {
    if (!impl_->key_.empty()) {
        return (&impl_->key_[0]);
    } else {
        return (0);
    }
}

uint16_t
TKEY::getOtherLen() const {
    return (impl_->other_data_.size());
}

const void*
TKEY::getOtherData() const {
    if (!impl_->other_data_.empty()) {
        return (&impl_->other_data_[0]);
    } else {
        return (0);
    }
}


TXT&
TXT::operator=(const TXT& source) {
    if (this == &source) {
        return (*this);
    }

    impl_.reset(new TXTImpl(*source.impl_));

    return (*this);
}

TXT::~TXT() {
}

TXT::TXT(InputBuffer& buffer, size_t rdata_len) :
    impl_(new TXTImpl(buffer, rdata_len)) {
}

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
    impl_(new TXTImpl(lexer)) {
}

TXT::TXT(const std::string& txtstr) :
    impl_(new TXTImpl(txtstr)) {
}

TXT::TXT(const TXT& other) :
    Rdata(), impl_(new TXTImpl(*other.impl_)) {
}

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

} // end of namespace "generic"

namespace in {

namespace {
void
convertToIPv4Addr(const char* src, size_t src_len, uint32_t* dst) {
    // This check specifically rejects invalid input that begins with valid
    // address text followed by a nul character (and possibly followed by
    // further garbage).  It cannot be detected by inet_pton().
    //
    // Note that this is private subroutine of the in::A constructors, which
    // pass std::string.size() or StringRegion::len as src_len, so it should
    // be equal to strlen() unless there's an intermediate nul character.
    if (src_len != strlen(src)) {
        isc_throw(InvalidRdataText,
                  "Bad IN/A RDATA text: unexpected nul in string: '"
                  << src << "'");
    }
    const int result = inet_pton(AF_INET, src, dst);
    if (result == 0) {
        isc_throw(InvalidRdataText, "Bad IN/A RDATA text: '" << src << "'");
    } else if (result < 0) {
        isc_throw(isc::Unexpected,
                  "Unexpected failure in parsing IN/A RDATA text: '"
                  << src << "': " << std::strerror(errno));
    }
}
}

/// \brief Constructor from string.
///
/// The given string must be a valid textual representation of an IPv4
/// address as specified in RFC1035, that is, four decimal numbers separated
/// by dots without any embedded spaces.  Note that it excludes abbreviated
/// forms such as "10.1" to mean "10.0.0.1".
///
/// Internally, this implementation uses the standard inet_pton() library
/// function for the AF_INET family to parse and convert the textual
/// representation.  While standard compliant implementations of this function
/// should accept exactly what this constructor expects, specific
/// implementation may behave differently, in which case this constructor
/// will simply accept the result of inet_pton().  In any case, the user of
/// the class shouldn't assume such specific implementation behavior of
/// inet_pton().
///
/// No extra character should be contained in \c addrstr other than the
/// textual address.  These include spaces and the nul character.
///
/// \throw InvalidRdata The text extracted by the lexer isn't recognized as
/// a valid IPv4 address.
/// \throw Unexpected Unexpected system error in conversion (this should be
/// very rare).
///
/// \param addrstr Textual representation of IPv4 address to be used as the
/// RDATA.
A::A(const std::string& addrstr) {
    convertToIPv4Addr(addrstr.c_str(), addrstr.size(), &addr_);
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual representation
/// of a class IN A RDATA.
///
/// The acceptable form of the textual address is generally the same as the
/// string version of the constructor, but this version accepts beginning
/// spaces and trailing spaces or other characters.  Trailing non space
/// characters would be considered an invalid form in an RR representation,
/// but handling such errors is not the responsibility of this constructor.
/// It also accepts other unusual syntax that would be considered valid
/// in the context of DNS master file; for example, it accepts an IPv4
/// address surrounded by parentheses, such as "(192.0.2.1)", although it's
/// very unlikely to be used for this type of RDATA.
///
/// \throw MasterLexer::LexerError General parsing error such as missing field.
/// \throw InvalidRdata The text extracted by the lexer isn't recognized as
/// a valid IPv4 address.
/// \throw Unexpected Unexpected system error in conversion (this should be
/// very rare).
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
A::A(MasterLexer& lexer, const Name*,
     MasterLoader::Options, MasterLoaderCallbacks&) {
    const MasterToken& token = lexer.getNextToken(MasterToken::STRING);
    convertToIPv4Addr(token.getStringRegion().beg, token.getStringRegion().len,
                      &addr_);
}

A::A(InputBuffer& buffer, size_t rdata_len) {
    if (rdata_len != sizeof(addr_)) {
        isc_throw(DNSMessageFORMERR,
                  "IN/A RDATA construction from wire failed: Invalid length: "
                  << rdata_len);
    }
    if (buffer.getLength() - buffer.getPosition() < sizeof(addr_)) {
        isc_throw(DNSMessageFORMERR,
                  "IN/A RDATA construction from wire failed: "
                  "insufficient buffer length: "
                  << buffer.getLength() - buffer.getPosition());
    }
    buffer.readData(&addr_, sizeof(addr_));
}

/// \brief Copy constructor.
A::A(const A& other) : Rdata(), addr_(other.addr_) {
}

void
A::toWire(OutputBuffer& buffer) const {
    buffer.writeData(&addr_, sizeof(addr_));
}

void
A::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeData(&addr_, sizeof(addr_));
}

/// \brief Return a textual form of the underlying IPv4 address of the RDATA.
string
A::toText() const {
    char addr_string[sizeof("255.255.255.255")];

    if (inet_ntop(AF_INET, &addr_, addr_string, sizeof(addr_string)) == 0) {
        isc_throw(Unexpected,
                  "Failed to convert IN/A RDATA to textual IPv4 address");
    }

    return (addr_string);
}

/// \brief Compare two in::A RDATAs.
///
/// In effect, it compares the two RDATA as an unsigned 32-bit integer.
int
A::compare(const Rdata& other) const {
    const A& other_a = dynamic_cast<const A&>(other);
    return (memcmp(&addr_, &other_a.addr_, sizeof(addr_)));
}

namespace {
void
convertToIPv6Addr(const char* src, size_t src_len, void* dst) {
    // See a_1.cc for this check.
    if (src_len != strlen(src)) {
        isc_throw(InvalidRdataText,
                  "Bad IN/AAAA RDATA text: unexpected nul in string: '"
                  << src << "'");
    }
    const int result = inet_pton(AF_INET6, src, dst);
    if (result == 0) {
        isc_throw(InvalidRdataText, "Bad IN/AAAA RDATA text: '" << src << "'");
    } else if (result < 0) {
        isc_throw(isc::Unexpected,
                  "Unexpected failure in parsing IN/AAAA RDATA text: '"
                  << src << "': " << std::strerror(errno));
    }
}
}

/// \brief Constructor from string.
///
/// The given string must be a valid textual representation of an IPv6
/// address as specified in RFC1886.
///
/// No extra character should be contained in \c addrstr other than the
/// textual address.  These include spaces and the nul character.
///
/// \throw InvalidRdata The text extracted by the lexer isn't recognized as
/// a valid IPv6 address.
/// \throw Unexpected Unexpected system error in conversion (this should be
/// very rare).
///
/// \param addrstr Textual representation of IPv6 address to be used as the
/// RDATA.
AAAA::AAAA(const std::string& addrstr) {
    convertToIPv6Addr(addrstr.c_str(), addrstr.size(), addr_);
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual representation
/// of a class IN AAAA RDATA.
///
/// The acceptable form of the textual address is generally the same as the
/// string version of the constructor, but this version is slightly more
/// flexible.  See the similar constructor of \c in::A class; the same
/// notes apply here.
///
/// \throw MasterLexer::LexerError General parsing error such as missing field.
/// \throw InvalidRdata The text extracted by the lexer isn't recognized as
/// a valid IPv6 address.
/// \throw Unexpected Unexpected system error in conversion (this should be
/// very rare).
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
AAAA::AAAA(MasterLexer& lexer, const Name*,
           MasterLoader::Options, MasterLoaderCallbacks&) {
    const MasterToken& token = lexer.getNextToken(MasterToken::STRING);
    convertToIPv6Addr(token.getStringRegion().beg, token.getStringRegion().len,
                      addr_);
}

/// \brief Copy constructor.
AAAA::AAAA(InputBuffer& buffer, size_t rdata_len) {
    if (rdata_len != sizeof(addr_)) {
        isc_throw(DNSMessageFORMERR,
                  "IN/AAAA RDATA construction from wire failed: "
                  "Invalid length: " << rdata_len);
    }
    if (buffer.getLength() - buffer.getPosition() < sizeof(addr_)) {
        isc_throw(DNSMessageFORMERR,
                  "IN/AAAA RDATA construction from wire failed: "
                  "insufficient buffer length: "
                  << buffer.getLength() - buffer.getPosition());
    }
    buffer.readData(&addr_, sizeof(addr_));
}

AAAA::AAAA(const AAAA& other) : Rdata() {
    memcpy(addr_, other.addr_, sizeof(addr_));
}

/// \brief Return a textual form of the underlying IPv6 address of the RDATA.
void
AAAA::toWire(OutputBuffer& buffer) const {
    buffer.writeData(&addr_, sizeof(addr_));
}

void
AAAA::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeData(&addr_, sizeof(addr_));
}

string
AAAA::toText() const {
    char addr_string[sizeof("ffff:ffff:ffff:ffff:ffff:ffff:255.255.255.255")];

    if (inet_ntop(AF_INET6, &addr_, addr_string, sizeof(addr_string)) == 0) {
        isc_throw(Unexpected,
                  "Failed to convert IN/AAAA RDATA to textual IPv6 address");
    }

    return (string(addr_string));
}

/// \brief Compare two in::AAAA RDATAs.
///
/// In effect, it compares the two RDATA as an unsigned 128-bit integer.
int
AAAA::compare(const Rdata& other) const {
    const AAAA& other_a = dynamic_cast<const AAAA&>(other);
    return (memcmp(&addr_, &other_a.addr_, sizeof(addr_)));
}

void
DHCID::constructFromLexer(MasterLexer& lexer) {
    string digest_txt = lexer.getNextToken(MasterToken::STRING).getString();

    // Whitespace is allowed within base64 text, so read to the end of input.
    string digest_part;
    while (true) {
        const MasterToken& token =
            lexer.getNextToken(MasterToken::STRING, true);
        if ((token.getType() == MasterToken::END_OF_FILE) ||
            (token.getType() == MasterToken::END_OF_LINE)) {
            break;
        }
        token.getString(digest_part);
        digest_txt.append(digest_part);
    }
    lexer.ungetToken();

    decodeBase64(digest_txt, digest_);
}

/// \brief Constructor from string.
///
/// \param dhcid_str A base-64 representation of the DHCID binary data.
///
/// \throw InvalidRdataText if the string could not be parsed correctly.
DHCID::DHCID(const std::string& dhcid_str) {
    try {
        std::istringstream iss(dhcid_str);
        MasterLexer lexer;
        lexer.pushSource(iss);

        constructFromLexer(lexer);

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText, "extra input text for DHCID: "
                      << dhcid_str);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText, "Failed to construct DHCID from '" <<
                  dhcid_str << "': " << ex.what());
    }
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual representation
/// of a DHCID RDATA.
///
/// \throw BadValue if the text is not valid base-64.
/// \throw MasterLexer::LexerError General parsing error such as missing field.
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
DHCID::DHCID(MasterLexer& lexer, const Name*,
             MasterLoader::Options, MasterLoaderCallbacks&) {
    constructFromLexer(lexer);
}

/// \brief Constructor from wire-format data.
///
/// \param buffer A buffer storing the wire format data.
/// \param rdata_len The length of the RDATA in bytes
DHCID::DHCID(InputBuffer& buffer, size_t rdata_len) {
    if (rdata_len == 0) {
        isc_throw(InvalidRdataLength, "Missing DHCID rdata");
    }

    digest_.resize(rdata_len);
    buffer.readData(&digest_[0], rdata_len);
}

/// \brief The copy constructor.
///
/// This trivial copy constructor never throws an exception.
DHCID::DHCID(const DHCID& other) : Rdata(), digest_(other.digest_) {
}

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
    return (encodeBase64(digest_));
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

} // end of namespace "in"
} // end of namespace "rdata"
} // end of namespace "dns"
} // end of namespace "isc"
