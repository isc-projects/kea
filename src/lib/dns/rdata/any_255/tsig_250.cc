// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#include <config.h>

#include <string>
#include <sstream>
#include <vector>

#include <boost/lexical_cast.hpp>

#include <dns/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rdataclass.h>

#include <dns/util/base64.h>

using namespace std;
using namespace boost;

// BEGIN_ISC_NAMESPACE
// BEGIN_RDATA_NAMESPACE

// This is a straightforward representation of TSIG RDATA fields.
struct TSIG::TSIGImpl {
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

    const Name algorithm_;
    const uint64_t time_signed_;
    const uint16_t fudge_;
    const vector<uint8_t> mac_;
    const uint16_t original_id_;
    const uint16_t error_;
    const vector<uint8_t> other_data_;
};

namespace {
string
getToken(istringstream& iss, const string& full_input) {
    string token;
    iss >> token;
    if (iss.bad() || iss.fail()) {
        isc_throw(InvalidRdataText, "Invalid TSIG text: parse error" <<
                  full_input);
    }
    return (token);
}

// This helper function converts a string token to an *unsigned* integer.
// NumType is a *signed* integral type (e.g. int32_t) that is sufficiently
// wide to store resulting integers.
// BitSize is the maximum number of bits that the resulting integer can take.
// This function first checks whether the given token can be converted to
// an integer of NumType type.  It then confirms the conversion result is
// within the valid range, i.e., [0, 2^NumType - 1].  The second check is
// necessary because lexical_cast<T> where T is an unsigned integer type
// doesn't correctly reject negative numbers when compiled with SunStudio.
template <typename NumType, int BitSize>
NumType
tokenToNum(const string& num_token) {
    NumType num;
    try {
        num = lexical_cast<NumType>(num_token);
    } catch (const boost::bad_lexical_cast& ex) {
        isc_throw(InvalidRdataText, "Invalid TSIG numeric parameter: " <<
                  num_token);
    }
    if (num < 0 || num >= (static_cast<NumType>(1) << BitSize)) {
        isc_throw(InvalidRdataText, "Numeric TSIG parameter out of range: " <<
                  num);
    }
    return (num);
}
}

/// \brief Constructor from string
TSIG::TSIG(const std::string& tsig_str) : impl_(NULL) {
    istringstream iss(tsig_str);

    const Name algorithm(getToken(iss, tsig_str));
    const int64_t time_signed = tokenToNum<int64_t, 48>(getToken(iss,
                                                                 tsig_str));
    const int32_t fudge = tokenToNum<int32_t, 16>(getToken(iss, tsig_str));
    const int32_t macsize = tokenToNum<int32_t, 16>(getToken(iss, tsig_str));

    const string mac_txt = (macsize > 0) ? getToken(iss, tsig_str) : "";
    vector<uint8_t> mac;
    decodeBase64(mac_txt, mac);
    if (mac.size() != macsize) {
        isc_throw(InvalidRdataText, "TSIG MAC size and data are inconsistent");
    }

    const int32_t orig_id = tokenToNum<int32_t, 16>(getToken(iss, tsig_str));

    const string error_txt = getToken(iss, tsig_str);
    int32_t error = 0;
    if (error_txt == "BADSIG") {
        error = 16;             // FIXIT: hardcode
    } else if (error_txt == "BADKEY") {
        error = 17;
    } else if (error_txt == "BADTIME") {
        error = 18;
    } else {
        error = tokenToNum<int32_t, 16>(error_txt);
    }

    const int32_t otherlen = tokenToNum<int32_t, 16>(getToken(iss, tsig_str));
    const string otherdata_txt = (otherlen > 0) ? getToken(iss, tsig_str) : "";
    vector<uint8_t> other_data;
    decodeBase64(otherdata_txt, other_data);

    if (!iss.eof()) {
        isc_throw(InvalidRdataText, "Unexpected input for TSIG RDATA: " <<
                  tsig_str);
    }

    impl_ = new TSIGImpl(algorithm, time_signed, fudge, mac, orig_id,
                         error, other_data);
}

TSIG::TSIG(InputBuffer& buffer, size_t rdata_len UNUSED_PARAM) : impl_(NULL) {
    // we don't need rdata_len for parsing.  if necessary, the caller will
    // check consistency.

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

    impl_ = new TSIGImpl(algorithm, time_signed, fudge, mac, original_id,
                         error, other_data);
}

TSIG::TSIG(const Name& algorithm, uint64_t time_signed, uint16_t fudge,
           size_t mac_size, const void* mac, uint16_t original_id,
           uint16_t error, size_t other_len, const void* other_data) :
    impl_(NULL)
{
    if (time_signed > 0xffffffffffff) {
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
    impl_ = new TSIGImpl(algorithm, time_signed, fudge, mac_size, mac,
                         original_id, error, other_len, other_data);
}

TSIG::TSIG(const TSIG& source) : Rdata(), impl_(new TSIGImpl(*source.impl_))
{}

TSIG&
TSIG::operator=(const TSIG& source) {
    if (impl_ == source.impl_) {
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

std::string
TSIG::toText() const {
    string result;

    result += impl_->algorithm_.toText() + " " +
        lexical_cast<string>(impl_->time_signed_) + " " +
        lexical_cast<string>(impl_->fudge_) + " " +
        lexical_cast<string>(impl_->mac_.size()) + " ";
    if (impl_->mac_.size() > 0) {
        result += encodeBase64(impl_->mac_) + " ";
    }
    result += lexical_cast<string>(impl_->original_id_) + " ";
    if (impl_->error_ == 16) {  // XXX: we'll soon introduce generic converter.
        result += "BADSIG ";
    } else if (impl_->error_ == 17) {
        result += "BADKEY ";
    } else if (impl_->error_ == 18) {
        result += "BADTIME ";
    } else {
        result += lexical_cast<string>(impl_->error_) + " ";
    }
    result += lexical_cast<string>(impl_->other_data_.size());
    if (impl_->other_data_.size() > 0) {
        result += " " + encodeBase64(impl_->other_data_);
    }

    return (result);
}

template <typename Output>
void
toWireCommon(const TSIG::TSIGImpl& impl, Output& output) {
    output.writeUint16(impl.time_signed_ >> 32);
    output.writeUint32(impl.time_signed_ & 0xffffffff);
    output.writeUint16(impl.fudge_);
    const uint16_t mac_size = impl.mac_.size();
    output.writeUint16(mac_size);
    if (mac_size > 0) {
        output.writeData(&impl.mac_[0], mac_size);
    }
    output.writeUint16(impl.original_id_);
    output.writeUint16(impl.error_);
    const uint16_t other_len = impl.other_data_.size();
    output.writeUint16(other_len);
    if (other_len > 0) {
        output.writeData(&impl.other_data_[0], other_len);
    }
}

void
TSIG::toWire(OutputBuffer& buffer) const {
    impl_->algorithm_.toWire(buffer);
    toWireCommon<OutputBuffer>(*impl_, buffer);
}

void
TSIG::toWire(MessageRenderer& renderer) const {
    renderer.writeName(impl_->algorithm_, false);
    toWireCommon<MessageRenderer>(*impl_, renderer);
}

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
    if (impl_->mac_.size() > 0) {
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
    if (impl_->other_data_.size() > 0) {
        return (&impl_->other_data_[0]);
    } else {
        return (NULL);
    }
}

// END_RDATA_NAMESPACE
// END_ISC_NAMESPACE
