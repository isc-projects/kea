// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DS_LIKE_H
#define DS_LIKE_H 1

#include <stdint.h>

#include <iostream>
#include <sstream>
#include <string>
#include <vector>

#include <boost/lexical_cast.hpp>

#include <exceptions/exceptions.h>

#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

namespace isc {
namespace dns {
namespace rdata {
namespace generic {
namespace detail {

/// \brief \c rdata::DSLikeImpl class represents the DS-like RDATA for DS
/// and DLV types.
///
/// This class implements the basic interfaces inherited by the DS and DLV
/// classes from the abstract \c rdata::Rdata class, and provides trivial
/// accessors to DS-like RDATA.
template <class Type, uint16_t typeCode> class DSLikeImpl {
    // Common sequence of toWire() operations used for the two versions of
    // toWire().
    template <typename Output>
    void
    toWireCommon(Output& output) const {
        output.writeUint16(tag_);
        output.writeUint8(algorithm_);
        output.writeUint8(digest_type_);
        output.writeData(&digest_[0], digest_.size());
    }

public:
    /// \brief Constructor from string.
    ///
    /// The given string must represent a valid DS-like RDATA.  There
    /// can be extra space characters at the beginning or end of the
    /// text (which are simply ignored), but other extra text, including
    /// a new line, will make the construction fail with an exception.
    ///
    /// The tag field must be a valid decimal representation of an
    /// unsigned 16-bit integer. The protocol and algorithm fields must
    /// be valid decimal representations of unsigned 8-bit integers
    /// respectively. The digest field may contain whitespace.
    ///
    /// \throw InvalidRdataText if any fields are out of their valid range.
    ///
    /// \param ds_str A string containing the RDATA to be created
    DSLikeImpl(const std::string& ds_str) {
        try {
            std::istringstream ss(ds_str);
            MasterLexer lexer;
            lexer.pushSource(ss);

            constructFromLexer(lexer);

            if (lexer.getNextToken().getType() != MasterToken::END_OF_FILE) {
                isc_throw(InvalidRdataText,
                          "Extra input text for " << RRType(typeCode) << ": "
                          << ds_str);
            }
        } catch (const MasterLexer::LexerError& ex) {
            isc_throw(InvalidRdataText,
                      "Failed to construct " << RRType(typeCode) << " from '" <<
                      ds_str << "': " << ex.what());
        }
    }

    /// \brief Constructor with a context of MasterLexer.
    ///
    /// The \c lexer should point to the beginning of valid textual
    /// representation of a DS-like RDATA.
    ///
    /// The tag field must be a valid decimal representation of an
    /// unsigned 16-bit integer. The protocol and algorithm fields must
    /// be valid decimal representations of unsigned 8-bit integers
    /// respectively.
    ///
    /// \throw MasterLexer::LexerError General parsing error such as
    /// missing field.
    /// \throw InvalidRdataText if any fields are out of their valid range.
    ///
    /// \param lexer A \c MasterLexer object parsing a master file for the
    /// RDATA to be created
    DSLikeImpl(MasterLexer& lexer, const Name*, MasterLoader::Options,
               MasterLoaderCallbacks&)
    {
        constructFromLexer(lexer);
    }

private:
    void constructFromLexer(MasterLexer& lexer) {
        const uint32_t tag =
            lexer.getNextToken(MasterToken::NUMBER).getNumber();
        if (tag > 0xffff) {
            isc_throw(InvalidRdataText,
                      "Invalid " << RRType(typeCode) << " tag: " << tag);
        }

        const uint32_t algorithm =
            lexer.getNextToken(MasterToken::NUMBER).getNumber();
        if (algorithm > 0xff) {
            isc_throw(InvalidRdataText,
                      "Invalid " << RRType(typeCode) << " algorithm: "
                      << algorithm);
        }

        const uint32_t digest_type =
            lexer.getNextToken(MasterToken::NUMBER).getNumber();
        if (digest_type > 0xff) {
            isc_throw(InvalidRdataText,
                      "Invalid " << RRType(typeCode) << " digest type: "
                      << digest_type);
        }

        std::string digest;
        while (true) {
            const MasterToken& token = lexer.getNextToken();
            if (token.getType() != MasterToken::STRING) {
                break;
            }
            digest.append(token.getString());
        }

        lexer.ungetToken();

        if (digest.size() == 0) {
            isc_throw(InvalidRdataText,
                      "Missing " << RRType(typeCode) << " digest");
        }

        tag_ = tag;
        algorithm_ = algorithm;
        digest_type_ = digest_type;
        decodeHex(digest, digest_);
    }

public:
    /// \brief Constructor from wire-format data.
    ///
    /// \param buffer A buffer storing the wire format data.
    /// \param rdata_len The length of the RDATA in bytes, normally expected
    /// to be the value of the RDLENGTH field of the corresponding RR.
    ///
    /// <b>Exceptions</b>
    ///
    /// \c InvalidRdataLength is thrown if the input data is too short for the
    /// type.
    DSLikeImpl(InputBuffer& buffer, size_t rdata_len) {
        if (rdata_len < 4) {
            isc_throw(InvalidRdataLength, RRType(typeCode) << " too short");
        }

        tag_ = buffer.readUint16();
        algorithm_ = buffer.readUint8();
        digest_type_ = buffer.readUint8();

        rdata_len -= 4;
        digest_.resize(rdata_len);
        buffer.readData(&digest_[0], rdata_len);
    }

    /// \brief The copy constructor.
    ///
    /// Trivial for now, we could've used the default one.
    DSLikeImpl(const DSLikeImpl& source) :
        tag_(source.tag_),
        algorithm_(source.algorithm_),
        digest_type_(source.digest_type_),
        digest_(source.digest_)
    {}

    /// \brief Convert the DS-like data to a string.
    ///
    /// \return A \c string object that represents the DS-like data.
    std::string
    toText() const {
        using namespace boost;
        return (lexical_cast<string>(static_cast<int>(tag_)) +
            " " + lexical_cast<string>(static_cast<int>(algorithm_)) +
            " " + lexical_cast<string>(static_cast<int>(digest_type_)) +
            " " + encodeHex(digest_));
    }

    /// \brief Render the DS-like data in the wire format to an OutputBuffer
    /// object.
    ///
    /// \param buffer An output buffer to store the wire data.
    void
    toWire(OutputBuffer& buffer) const {
        toWireCommon(buffer);
    }

    /// \brief Render the DS-like data in the wire format to an
    /// AbstractMessageRenderer object.
    ///
    /// \param renderer A renderer object to send the wire data to.
    void
    toWire(AbstractMessageRenderer& renderer) const {
        toWireCommon(renderer);
    }

    /// \brief Compare two instances of DS-like RDATA.
    ///
    /// It is up to the caller to make sure that \c other is an object of the
    /// same \c DSLikeImpl class.
    ///
    /// \param other the right-hand operand to compare against.
    /// \return < 0 if \c this would be sorted before \c other.
    /// \return 0 if \c this is identical to \c other in terms of sorting
    /// order.
    /// \return > 0 if \c this would be sorted after \c other.
    int
    compare(const DSLikeImpl& other_ds) const {
        if (tag_ != other_ds.tag_) {
            return (tag_ < other_ds.tag_ ? -1 : 1);
        }
        if (algorithm_ != other_ds.algorithm_) {
            return (algorithm_ < other_ds.algorithm_ ? -1 : 1);
        }
        if (digest_type_ != other_ds.digest_type_) {
            return (digest_type_ < other_ds.digest_type_ ? -1 : 1);
        }

        size_t this_len = digest_.size();
        size_t other_len = other_ds.digest_.size();
        size_t cmplen = min(this_len, other_len);
        int cmp = memcmp(&digest_[0], &other_ds.digest_[0], cmplen);
        if (cmp != 0) {
            return (cmp);
        } else {
            return ((this_len == other_len)
                    ? 0 : (this_len < other_len) ? -1 : 1);
        }
    }

    /// \brief Accessors
    uint16_t
    getTag() const {
        return (tag_);
    }

private:
    // straightforward representation of DS RDATA fields
    uint16_t tag_;
    uint8_t algorithm_;
    uint8_t digest_type_;
    std::vector<uint8_t> digest_;
};

}
}
}
}
}
#endif //  DS_LIKE_H

// Local Variables: 
// mode: c++
// End: 
