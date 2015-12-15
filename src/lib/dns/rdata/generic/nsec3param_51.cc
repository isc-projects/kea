// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <util/buffer.h>
#include <util/encode/hex.h>

#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>
#include <dns/rdata/generic/detail/nsec3param_common.h>

#include <boost/lexical_cast.hpp>

#include <memory>
#include <string>
#include <sstream>
#include <vector>

using namespace std;
using namespace isc::util;
using namespace isc::util::encode;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

struct NSEC3PARAMImpl {
    // straightforward representation of NSEC3PARAM RDATA fields
    NSEC3PARAMImpl(uint8_t hashalg, uint8_t flags, uint16_t iterations,
                   const vector<uint8_t>& salt) :
        hashalg_(hashalg), flags_(flags), iterations_(iterations), salt_(salt)
    {}

    const uint8_t hashalg_;
    const uint8_t flags_;
    const uint16_t iterations_;
    const vector<uint8_t> salt_;
};

/// \brief Constructor from string.
///
/// The given string must represent a valid NSEC3PARAM RDATA.  There
/// can be extra space characters at the beginning or end of the
/// text (which are simply ignored), but other extra text, including
/// a new line, will make the construction fail with an exception.
///
/// The Hash Algorithm, Flags and Iterations fields must be within their
/// valid ranges. The Salt field may contain "-" to indicate that the
/// salt is of length 0. The Salt field must not contain any whitespace.
///
/// \throw InvalidRdataText if any fields are out of their valid range,
/// or are incorrect.
///
/// \param nsec3param_str A string containing the RDATA to be created
NSEC3PARAM::NSEC3PARAM(const std::string& nsec3param_str) :
    impl_(NULL)
{
    // We use auto_ptr here because if there is an exception in this
    // constructor, the destructor is not called and there could be a
    // leak of the NSEC3PARAMImpl that constructFromLexer() returns.
    std::auto_ptr<NSEC3PARAMImpl> impl_ptr(NULL);

    try {
        std::istringstream ss(nsec3param_str);
        MasterLexer lexer;
        lexer.pushSource(ss);

        impl_ptr.reset(constructFromLexer(lexer));

        if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
            isc_throw(InvalidRdataText,
                      "Extra input text for NSEC3PARAM: " << nsec3param_str);
        }
    } catch (const MasterLexer::LexerError& ex) {
        isc_throw(InvalidRdataText,
                  "Failed to construct NSEC3PARAM from '" << nsec3param_str
                  << "': " << ex.what());
    }

    impl_ = impl_ptr.release();
}

/// \brief Constructor with a context of MasterLexer.
///
/// The \c lexer should point to the beginning of valid textual
/// representation of an NSEC3PARAM RDATA.
///
/// See \c NSEC3PARAM::NSEC3PARAM(const std::string&) for description of
/// the expected RDATA fields.
///
/// \throw MasterLexer::LexerError General parsing error such as
/// missing field.
/// \throw InvalidRdataText if any fields are out of their valid range,
/// or are incorrect.
///
/// \param lexer A \c MasterLexer object parsing a master file for the
/// RDATA to be created
NSEC3PARAM::NSEC3PARAM(MasterLexer& lexer, const Name*, MasterLoader::Options,
                       MasterLoaderCallbacks&) :
    impl_(NULL)
{
    impl_ = constructFromLexer(lexer);
}

NSEC3PARAMImpl*
NSEC3PARAM::constructFromLexer(MasterLexer& lexer) {
    vector<uint8_t> salt;
    const ParseNSEC3ParamResult params =
        parseNSEC3ParamFromLexer("NSEC3PARAM", lexer, salt);

    return (new NSEC3PARAMImpl(params.algorithm, params.flags,
                               params.iterations, salt));
}

NSEC3PARAM::NSEC3PARAM(InputBuffer& buffer, size_t rdata_len) :
    impl_(NULL)
{
    vector<uint8_t> salt;
    const ParseNSEC3ParamResult params =
        parseNSEC3ParamWire("NSEC3PARAM", buffer, rdata_len, salt);

    impl_ = new NSEC3PARAMImpl(params.algorithm, params.flags,
                               params.iterations, salt);
}

NSEC3PARAM::NSEC3PARAM(const NSEC3PARAM& source) :
    Rdata(), impl_(new NSEC3PARAMImpl(*source.impl_))
{}

NSEC3PARAM&
NSEC3PARAM::operator=(const NSEC3PARAM& source) {
    if (this == &source) {
        return (*this);
    }

    NSEC3PARAMImpl* newimpl = new NSEC3PARAMImpl(*source.impl_);
    delete impl_;
    impl_ = newimpl;

    return (*this);
}

NSEC3PARAM::~NSEC3PARAM() {
    delete impl_;
}

string
NSEC3PARAM::toText() const {
    using boost::lexical_cast;
    return (lexical_cast<string>(static_cast<int>(impl_->hashalg_)) +
            " " + lexical_cast<string>(static_cast<int>(impl_->flags_)) +
            " " + lexical_cast<string>(static_cast<int>(impl_->iterations_)) +
            " " + (impl_->salt_.empty() ? "-" : encodeHex(impl_->salt_)));
}

template <typename OUTPUT_TYPE>
void
toWireHelper(const NSEC3PARAMImpl& impl, OUTPUT_TYPE& output) {
    output.writeUint8(impl.hashalg_);
    output.writeUint8(impl.flags_);
    output.writeUint16(impl.iterations_);
    output.writeUint8(impl.salt_.size());
    if (!impl.salt_.empty()) {
        output.writeData(&impl.salt_[0], impl.salt_.size());
    }
}

void
NSEC3PARAM::toWire(OutputBuffer& buffer) const {
    toWireHelper(*impl_, buffer);
}

void
NSEC3PARAM::toWire(AbstractMessageRenderer& renderer) const {
    toWireHelper(*impl_, renderer);
}

int
NSEC3PARAM::compare(const Rdata& other) const {
    const NSEC3PARAM& other_param = dynamic_cast<const NSEC3PARAM&>(other);

    if (impl_->hashalg_ != other_param.impl_->hashalg_) {
        return (impl_->hashalg_ < other_param.impl_->hashalg_ ? -1 : 1);
    }
    if (impl_->flags_ != other_param.impl_->flags_) {
        return (impl_->flags_ < other_param.impl_->flags_ ? -1 : 1);
    }
    if (impl_->iterations_ != other_param.impl_->iterations_) {
        return (impl_->iterations_ < other_param.impl_->iterations_ ? -1 : 1);
    }

    const size_t this_len = impl_->salt_.size();
    const size_t other_len = other_param.impl_->salt_.size();
    if (this_len != other_len) {
        return (this_len - other_len);
    }
    const size_t cmplen = min(this_len, other_len);
    const int cmp = (cmplen == 0) ? 0 :
        memcmp(&impl_->salt_.at(0), &other_param.impl_->salt_.at(0), cmplen);
    if (cmp != 0) {
        return (cmp);
    } else {
        return (this_len - other_len);
    }
}

uint8_t
NSEC3PARAM::getHashalg() const {
    return (impl_->hashalg_);
}

uint8_t
NSEC3PARAM::getFlags() const {
    return (impl_->flags_);
}

uint16_t
NSEC3PARAM::getIterations() const {
    return (impl_->iterations_);
}

const vector<uint8_t>&
NSEC3PARAM::getSalt() const {
    return (impl_->salt_);
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
