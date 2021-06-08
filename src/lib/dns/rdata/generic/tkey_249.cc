// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <string>
#include <sstream>
#include <vector>

#include <boost/lexical_cast.hpp>

#include <util/buffer.h>
#include <util/encode/base64.h>
#include <util/time_utilities.h>

#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rcode.h>
#include <dns/rdata/generic/detail/lexer_util.h>

using namespace std;
using boost::lexical_cast;
using namespace isc::util;
using namespace isc::util::encode;
using namespace isc::dns;
using isc::dns::rdata::generic::detail::createNameFromLexer;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

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
      mode_(mode), error_(error), key_(key), other_data_(other_data)
    {}

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
                    vector<uint8_t>(other_len))
    {}

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
TKEYImpl*
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

    return (new TKEYImpl(algorithm, inception, expire, mode, error,
                         key_data, other_data));
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
TKEY::TKEY(const std::string& tkey_str) : impl_(0) {
    // We use unique_ptr here because if there is an exception in this
    // constructor, the destructor is not called and there could be a
    // leak of the TKEYImpl that constructFromLexer() returns.
    std::unique_ptr<TKEYImpl> impl_ptr;

    try {
        std::istringstream ss(tkey_str);
        MasterLexer lexer;
        lexer.pushSource(ss);

        impl_ptr.reset(constructFromLexer(lexer, 0));

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText,
                      "Extra input text for TKEY: " << tkey_str);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText,
                  "Failed to construct TKEY from '" << tkey_str << "': "
                  << ex.what());
    }

    impl_ = impl_ptr.release();
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
/// of domain name.  But this implementation accepts a %TKEY RR even if that
/// field is compressed.
///
/// \param buffer A buffer storing the wire format data.
/// \param rdata_len The length of the RDATA in bytes, normally expected
/// to be the value of the RDLENGTH field of the corresponding RR.
/// But this constructor does not use this parameter; if necessary, the caller
/// must check consistency between the length parameter and the actual
/// RDATA length.
TKEY::TKEY(InputBuffer& buffer, size_t) :
    impl_(0)
{
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

    impl_ = new TKEYImpl(algorithm, inception, expire, mode, error,
                         key, other_data);
}

TKEY::TKEY(const Name& algorithm, uint32_t inception, uint32_t expire,
           uint16_t mode, uint16_t error, uint16_t key_len,
           const void* key, uint16_t other_len, const void* other_data) :
    impl_(0)
{
    if ((key_len == 0 && key != 0) || (key_len > 0 && key == 0)) {
        isc_throw(InvalidParameter, "TKEY Key length and data inconsistent");
    }
    if ((other_len == 0 && other_data != 0) ||
        (other_len > 0 && other_data == 0)) {
        isc_throw(InvalidParameter,
                  "TKEY Other data length and data inconsistent");
    }
    impl_ = new TKEYImpl(algorithm, inception, expire, mode, error,
                         key_len, key, other_len, other_data);
}

/// \brief The copy constructor.
///
/// It internally allocates a resource, and if it fails a corresponding
/// standard exception will be thrown.
/// This constructor never throws an exception otherwise.
TKEY::TKEY(const TKEY& source) : Rdata(), impl_(new TKEYImpl(*source.impl_))
{}

TKEY&
TKEY::operator=(const TKEY& source) {
    if (this == &source) {
        return (*this);
    }

    TKEYImpl* newimpl = new TKEYImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

TKEY::~TKEY() {
    delete impl_;
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

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
