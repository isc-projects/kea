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

#ifndef TXT_LIKE_H
#define TXT_LIKE_H 1

#include <stdint.h>

#include <string>
#include <vector>

namespace isc {
namespace dns {
namespace rdata {
namespace generic {
namespace detail {

/// \brief \c rdata::TXTLikeImpl class represents the TXT-like RDATA for TXT
/// and SPF types.
///
/// This class implements the basic interfaces inherited by the TXT and SPF
/// classes from the abstract \c rdata::Rdata class, and provides trivial
/// accessors to TXT-like RDATA.
template<class Type, uint16_t typeCode>class TXTLikeImpl {
public:
    /// \brief Constructor from wire-format data.
    ///
    /// \param buffer A buffer storing the wire format data.
    /// \param rdata_len The length of the RDATA in bytes, normally expected
    /// to be the value of the RDLENGTH field of the corresponding RR.
    ///
    /// <b>Exceptions</b>
    ///
    /// \c InvalidRdataLength is thrown if rdata_len exceeds the maximum.
    /// \c DNSMessageFORMERR is thrown if the RR is misformed.
    TXTLikeImpl(util::InputBuffer& buffer, size_t rdata_len) {
        if (rdata_len > MAX_RDLENGTH) {
            isc_throw(InvalidRdataLength, "RDLENGTH too large: " << rdata_len);
        }

        if (rdata_len == 0) {    // note that this couldn't happen in the loop.
            isc_throw(DNSMessageFORMERR, "Error in parsing " <<
                      RRType(typeCode) << " RDATA: 0-length character string");
        }

        do {
            const uint8_t len = buffer.readUint8();
            if (rdata_len < len + 1) {
                isc_throw(DNSMessageFORMERR, "Error in parsing " <<
                          RRType(typeCode) <<
                          " RDATA: character string length is too large: " <<
                          static_cast<int>(len));
            }
            std::vector<uint8_t> data(len + 1);
            data[0] = len;
            buffer.readData(&data[0] + 1, len);
            string_list_.push_back(data);

            rdata_len -= (len + 1);
        } while (rdata_len > 0);
    }

    /// \brief Constructor from string.
    ///
    /// <b>Exceptions</b>
    ///
    /// \c CharStringTooLong is thrown if the parameter string length exceeds
    /// maximum.
    /// \c InvalidRdataText is thrown if the method cannot process the
    /// parameter data.
    explicit TXTLikeImpl(const std::string& txtstr) {
        // TBD: this is a simple, incomplete implementation that only supports
        // a single character-string.

        size_t length = txtstr.size();
        size_t pos_begin = 0;

        if (length > 1 && txtstr[0] == '"' && txtstr[length - 1] == '"') {
            pos_begin = 1;
            length -= 2;
        }

        if (length > MAX_CHARSTRING_LEN) {
            isc_throw(CharStringTooLong, RRType(typeCode) <<
                      " RDATA construction from text:"
                      " string length is too long: " << length);
        }

        // TBD: right now, we don't support escaped characters
        if (txtstr.find('\\') != string::npos) {
            isc_throw(InvalidRdataText, RRType(typeCode) <<
                      " RDATA from text:"
                      " escaped character is currently not supported: " <<
                      txtstr);
        }

        std::vector<uint8_t> data;
        data.reserve(length + 1);
        data.push_back(length);
        data.insert(data.end(), txtstr.begin() + pos_begin,
                    txtstr.begin() + pos_begin + length);
        string_list_.push_back(data);
    }

    /// \brief The copy constructor.
    ///
    /// Trivial for now, we could've used the default one.
    TXTLikeImpl(const TXTLikeImpl& other) :
        string_list_(other.string_list_)
    {}

    /// \brief Render the TXT-like data in the wire format to an OutputBuffer
    /// object.
    ///
    /// \param buffer An output buffer to store the wire data.
    void
    toWire(util::OutputBuffer& buffer) const {
        for (std::vector<std::vector<uint8_t> >::const_iterator it =
                 string_list_.begin();
             it != string_list_.end();
             ++it)
        {
            buffer.writeData(&(*it)[0], (*it).size());
        }
    }

    /// \brief Render the TXT-like data in the wire format to an
    /// AbstractMessageRenderer object.
    ///
    /// \param buffer An output AbstractMessageRenderer to send the wire data
    /// to.
    void
    toWire(AbstractMessageRenderer& renderer) const {
        for (std::vector<std::vector<uint8_t> >::const_iterator it =
                 string_list_.begin();
             it != string_list_.end();
             ++it)
        {
            renderer.writeData(&(*it)[0], (*it).size());
        }
    }

    /// \brief Convert the TXT-like data to a string.
    ///
    /// \return A \c string object that represents the TXT-like data.
    std::string
    toText() const {
        std::string s;

        // XXX: this implementation is not entirely correct.  for example, it
        // should escape double-quotes if they appear in the character string.
        for (std::vector<std::vector<uint8_t> >::const_iterator it =
                 string_list_.begin();
             it != string_list_.end();
             ++it)
        {
            if (!s.empty()) {
                s.push_back(' ');
            }
            s.push_back('"');
            s.insert(s.end(), (*it).begin() + 1, (*it).end());
            s.push_back('"');
        }

        return (s);
    }

    /// \brief Compare two instances of TXT-like RDATA.
    ///
    /// It is up to the caller to make sure that \c other is an object of the
    /// same \c TXTLikeImpl class.
    ///
    /// \param other the right-hand operand to compare against.
    /// \return < 0 if \c this would be sorted before \c other.
    /// \return 0 if \c this is identical to \c other in terms of sorting
    /// order.
    /// \return > 0 if \c this would be sorted after \c other.
    int
    compare(const TXTLikeImpl& other) const {
        // This implementation is not efficient.  Revisit this (TBD).
        OutputBuffer this_buffer(0);
        toWire(this_buffer);
        uint8_t const* const this_data = (uint8_t const*)this_buffer.getData();
        const size_t this_len = this_buffer.getLength();

        OutputBuffer other_buffer(0);
        other.toWire(other_buffer);
        uint8_t const* const other_data
                                      = (uint8_t const*)other_buffer.getData();
        const size_t other_len = other_buffer.getLength();

        const size_t cmplen = min(this_len, other_len);
        const int cmp = memcmp(this_data, other_data, cmplen);

        if (cmp != 0) {
            return (cmp);
        } else {
            return ((this_len == other_len) ? 0 :
                    (this_len < other_len) ? -1 : 1);
        }
    }

private:
    /// Note: this is a prototype version; we may reconsider
    /// this representation later.
    std::vector<std::vector<uint8_t> > string_list_;
};

}      // namespace detail
}      // namespace generic
}      // namespace rdata
}      // namespace dns
}      // namespace isc

#endif //  TXT_LIKE_H

// Local Variables:
// mode: c++
// End:
