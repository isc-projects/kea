// Copyright (C) 2012-2013  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <boost/lexical_cast.hpp>

#include <exceptions/exceptions.h>

#include <util/buffer.h>
#include <util/encode/hex.h>
#include <dns/name.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

using namespace std;
using boost::lexical_cast;
using namespace isc::util;
using namespace isc::util::encode;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

struct SSHFPImpl {
    // straightforward representation of SSHFP RDATA fields
    SSHFPImpl(uint8_t algorithm, uint8_t fingerprint_type,
              const vector<uint8_t>& fingerprint) :
        algorithm_(algorithm),
        fingerprint_type_(fingerprint_type),
        fingerprint_(fingerprint)
    {}

    uint8_t algorithm_;
    uint8_t fingerprint_type_;
    const vector<uint8_t> fingerprint_;
};

// helper function for string and lexer constructors
SSHFPImpl*
SSHFP::constructFromLexer(MasterLexer& lexer) {
    const uint32_t algorithm =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (algorithm > 255) {
        isc_throw(InvalidRdataText, "SSHFP algorithm number out of range");
    }

    const uint32_t fingerprint_type =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (fingerprint_type > 255) {
        isc_throw(InvalidRdataText, "SSHFP fingerprint type out of range");
    }

    std::string fingerprint_str;
    std::string fingerprint_substr;
    while (true) {
        const MasterToken& token =
            lexer.getNextToken(MasterToken::STRING, true);
        if ((token.getType() == MasterToken::END_OF_FILE) ||
            (token.getType() == MasterToken::END_OF_LINE)) {
            break;
        }
        token.getString(fingerprint_substr);
        fingerprint_str.append(fingerprint_substr);
    }
    lexer.ungetToken();

    vector<uint8_t> fingerprint;
    // If fingerprint is missing, it's OK. See the API documentation of the
    // constructor.
    if (fingerprint_str.size() > 0) {
        try {
            decodeHex(fingerprint_str, fingerprint);
        } catch (const isc::BadValue& e) {
            isc_throw(InvalidRdataText, "Bad SSHFP fingerprint: " << e.what());
        }
    }

    return (new SSHFPImpl(algorithm, fingerprint_type, fingerprint));
}

/// \brief Constructor from string.
///
/// The given string must represent a valid SSHFP RDATA.  There can be
/// extra space characters at the beginning or end of the text (which
/// are simply ignored), but other extra text, including a new line,
/// will make the construction fail with an exception.
///
/// The Algorithm and Fingerprint Type fields must be within their valid
/// ranges, but are not constrained to the values defined in RFC4255.
///
/// The Fingerprint field may be absent, but if present it must contain a
/// valid hex encoding of the fingerprint. For compatibility with BIND 9,
/// whitespace is allowed in the hex text (RFC4255 is silent on the matter).
///
/// \throw InvalidRdataText if any fields are missing, are out of their
/// valid ranges or are incorrect, or if the fingerprint is not a valid
/// hex string.
///
/// \param sshfp_str A string containing the RDATA to be created
SSHFP::SSHFP(const string& sshfp_str) :
    impl_(NULL)
{
    // We use auto_ptr here because if there is an exception in this
    // constructor, the destructor is not called and there could be a
    // leak of the SSHFPImpl that constructFromLexer() returns.
    std::auto_ptr<SSHFPImpl> impl_ptr(NULL);

    try {
        std::istringstream ss(sshfp_str);
        MasterLexer lexer;
        lexer.pushSource(ss);

        impl_ptr.reset(constructFromLexer(lexer));

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText, "extra input text for SSHFP: "
                      << sshfp_str);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText, "Failed to construct SSHFP from '" <<
                  sshfp_str << "': " << ex.what());
    }

    impl_ = impl_ptr.release();
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual representation
/// of an SSHFP RDATA.
///
/// \throw MasterLexer::LexerError General parsing error such as missing field.
/// \throw InvalidRdataText Fields are out of their valid range or are
/// incorrect, or if the fingerprint is not a valid hex string.
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
SSHFP::SSHFP(MasterLexer& lexer, const Name*,
             MasterLoader::Options, MasterLoaderCallbacks&) :
    impl_(constructFromLexer(lexer))
{
}

/// \brief Constructor from InputBuffer.
///
/// The passed buffer must contain a valid SSHFP RDATA.
///
/// The Algorithm and Fingerprint Type fields are not checked for unknown
/// values.  It is okay for the fingerprint data to be missing (see the
/// description of the constructor from string).
SSHFP::SSHFP(InputBuffer& buffer, size_t rdata_len) {
    if (rdata_len < 2) {
        isc_throw(InvalidRdataLength, "SSHFP record too short");
    }

    const uint8_t algorithm = buffer.readUint8();
    const uint8_t fingerprint_type = buffer.readUint8();

    vector<uint8_t> fingerprint;
    rdata_len -= 2;
    if (rdata_len > 0) {
        fingerprint.resize(rdata_len);
        buffer.readData(&fingerprint[0], rdata_len);
    }

    impl_ = new SSHFPImpl(algorithm, fingerprint_type, fingerprint);
}

SSHFP::SSHFP(uint8_t algorithm, uint8_t fingerprint_type,
             const string& fingerprint_txt) :
    impl_(NULL)
{
    vector<uint8_t> fingerprint;
    try {
        decodeHex(fingerprint_txt, fingerprint);
    } catch (const isc::BadValue& e) {
        isc_throw(InvalidRdataText, "Bad SSHFP fingerprint: " << e.what());
    }

    impl_ = new SSHFPImpl(algorithm, fingerprint_type, fingerprint);
}

SSHFP::SSHFP(const SSHFP& other) :
        Rdata(), impl_(new SSHFPImpl(*other.impl_))
{}

SSHFP&
SSHFP::operator=(const SSHFP& source) {
    if (this == &source) {
        return (*this);
    }

    SSHFPImpl* newimpl = new SSHFPImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

SSHFP::~SSHFP() {
    delete impl_;
}

void
SSHFP::toWire(OutputBuffer& buffer) const {
    buffer.writeUint8(impl_->algorithm_);
    buffer.writeUint8(impl_->fingerprint_type_);

    if (!impl_->fingerprint_.empty()) {
        buffer.writeData(&impl_->fingerprint_[0],
                         impl_->fingerprint_.size());
    }
}

void
SSHFP::toWire(AbstractMessageRenderer& renderer) const {
    renderer.writeUint8(impl_->algorithm_);
    renderer.writeUint8(impl_->fingerprint_type_);

    if (!impl_->fingerprint_.empty()) {
        renderer.writeData(&impl_->fingerprint_[0],
                           impl_->fingerprint_.size());
    }
}

string
SSHFP::toText() const {
    return (lexical_cast<string>(static_cast<int>(impl_->algorithm_)) + " " +
            lexical_cast<string>(static_cast<int>(impl_->fingerprint_type_)) +
            (impl_->fingerprint_.empty() ? "" :
             " " + encodeHex(impl_->fingerprint_)));
}

int
SSHFP::compare(const Rdata& other) const {
    const SSHFP& other_sshfp = dynamic_cast<const SSHFP&>(other);

    if (impl_->algorithm_ < other_sshfp.impl_->algorithm_) {
        return (-1);
    } else if (impl_->algorithm_ > other_sshfp.impl_->algorithm_) {
        return (1);
    }

    if (impl_->fingerprint_type_ < other_sshfp.impl_->fingerprint_type_) {
        return (-1);
    } else if (impl_->fingerprint_type_ >
               other_sshfp.impl_->fingerprint_type_) {
        return (1);
    }

    const size_t this_len = impl_->fingerprint_.size();
    const size_t other_len = other_sshfp.impl_->fingerprint_.size();
    const size_t cmplen = min(this_len, other_len);

    if (cmplen > 0) {
        const int cmp = memcmp(&impl_->fingerprint_[0],
                               &other_sshfp.impl_->fingerprint_[0],
                               cmplen);
        if (cmp != 0) {
            return (cmp);
        }
    }

    if (this_len == other_len) {
        return (0);
    } else if (this_len < other_len) {
        return (-1);
    } else {
        return (1);
    }
}

uint8_t
SSHFP::getAlgorithmNumber() const {
    return (impl_->algorithm_);
}

uint8_t
SSHFP::getFingerprintType() const {
    return (impl_->fingerprint_type_);
}

const std::vector<uint8_t>&
SSHFP::getFingerprint() const {
    return (impl_->fingerprint_);
}

size_t
SSHFP::getFingerprintLength() const {
    return (impl_->fingerprint_.size());
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
