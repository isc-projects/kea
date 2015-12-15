// Copyright (C) 2010-2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <string>
#include <sstream>
#include <vector>

#include <boost/lexical_cast.hpp>

#include <util/buffer.h>
#include <util/encode/base64.h>

#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rcode.h>
#include <dns/tsigkey.h>
#include <dns/tsigerror.h>
#include <dns/rdata/generic/detail/lexer_util.h>

using namespace std;
using boost::lexical_cast;
using namespace isc::util;
using namespace isc::util::encode;
using namespace isc::dns;
using isc::dns::rdata::generic::detail::createNameFromLexer;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

// straightforward representation of TSIG RDATA fields
struct TSIGImpl {
    TSIGImpl(const Name& algorithm, uint64_t time_signed, uint16_t fudge,
             vector<uint8_t>& mac, uint16_t original_id, uint16_t error,
             vector<uint8_t>& other_data) :
        algorithm_(algorithm), time_signed_(time_signed), fudge_(fudge),
        mac_(mac), original_id_(original_id), error_(error),
        other_data_(other_data)
    {}
    TSIGImpl(const Name& algorithm, uint64_t time_signed, uint16_t fudge,
             size_t macsize, const void* mac, uint16_t original_id,
             uint16_t error, size_t other_len, const void* other_data) :
        algorithm_(algorithm), time_signed_(time_signed), fudge_(fudge),
        mac_(static_cast<const uint8_t*>(mac),
             static_cast<const uint8_t*>(mac) + macsize),
        original_id_(original_id), error_(error),
        other_data_(static_cast<const uint8_t*>(other_data),
                    static_cast<const uint8_t*>(other_data) + other_len)
    {}
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
TSIGImpl*
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

    return (new TSIGImpl(canonical_algorithm_name, time_signed, fudge, mac,
                         orig_id, error, other_data));
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
TSIG::TSIG(const std::string& tsig_str) : impl_(NULL) {
    // We use auto_ptr here because if there is an exception in this
    // constructor, the destructor is not called and there could be a
    // leak of the TSIGImpl that constructFromLexer() returns.
    std::auto_ptr<TSIGImpl> impl_ptr(NULL);

    try {
        std::istringstream ss(tsig_str);
        MasterLexer lexer;
        lexer.pushSource(ss);

        impl_ptr.reset(constructFromLexer(lexer, NULL));

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText,
                      "Extra input text for TSIG: " << tsig_str);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText,
                  "Failed to construct TSIG from '" << tsig_str << "': "
                  << ex.what());
    }

    impl_ = impl_ptr.release();
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
           MasterLoader::Options, MasterLoaderCallbacks&) :
    impl_(constructFromLexer(lexer, origin))
{
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
TSIG::TSIG(InputBuffer& buffer, size_t) :
    impl_(NULL)
{
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
    impl_ = new TSIGImpl(canonical_algorithm_name, time_signed, fudge, mac,
                         original_id, error, other_data);
}

TSIG::TSIG(const Name& algorithm, uint64_t time_signed, uint16_t fudge,
           uint16_t mac_size, const void* mac, uint16_t original_id,
           uint16_t error, uint16_t other_len, const void* other_data) :
    impl_(NULL)
{
    // Time Signed is a 48-bit value.
    if ((time_signed >> 48) != 0) {
        isc_throw(OutOfRange, "TSIG Time Signed is too large: " <<
                  time_signed);
    }
    if ((mac_size == 0 && mac != NULL) || (mac_size > 0 && mac == NULL)) {
        isc_throw(InvalidParameter, "TSIG MAC size and data inconsistent");
    }
    if ((other_len == 0 && other_data != NULL) ||
        (other_len > 0 && other_data == NULL)) {
        isc_throw(InvalidParameter,
                  "TSIG Other data length and data inconsistent");
    }
    const Name& canonical_algorithm_name =
        (algorithm == TSIGKey::HMACMD5_SHORT_NAME()) ?
            TSIGKey::HMACMD5_NAME() : algorithm;
    impl_ = new TSIGImpl(canonical_algorithm_name, time_signed, fudge, mac_size,
                         mac, original_id, error, other_len, other_data);
}

/// \brief The copy constructor.
///
/// It internally allocates a resource, and if it fails a corresponding
/// standard exception will be thrown.
/// This constructor never throws an exception otherwise.
TSIG::TSIG(const TSIG& source) : Rdata(), impl_(new TSIGImpl(*source.impl_))
{}

TSIG&
TSIG::operator=(const TSIG& source) {
    if (this == &source) {
        return (*this);
    }

    TSIGImpl* newimpl = new TSIGImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

TSIG::~TSIG() {
    delete impl_;
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
        return (NULL);
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
        return (NULL);
    }
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
