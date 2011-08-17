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

#ifndef __DS_LIKE_H
#define __DS_LIKE_H 1

#include <stdint.h>

#include <string>
#include <vector>

template<class Type, uint16_t typeCode>class DSLikeImpl {
public:
    DSLikeImpl(const string& ds_str)
    {
        istringstream iss(ds_str);
        stringbuf digestbuf;
        uint32_t tag, algorithm, digest_type;

        iss >> tag >> algorithm >> digest_type >> &digestbuf;
        if (iss.bad() || iss.fail()) {
            isc_throw(InvalidRdataText,
                      "Invalid " << RRType(typeCode) << " text");
        }
        if (tag > 0xffff) {
            isc_throw(InvalidRdataText,
                      RRType(typeCode) << " tag out of range");
        }
        if (algorithm > 0xff) {
            isc_throw(InvalidRdataText,
                      RRType(typeCode) << " algorithm out of range");
        }
        if (digest_type > 0xff) {
            isc_throw(InvalidRdataText,
                      RRType(typeCode) << " digest type out of range");
        }

        tag_ = tag;
        algorithm_ = algorithm;
        digest_type_ = digest_type;
        decodeHex(digestbuf.str(), digest_);
    }

    DSLikeImpl(InputBuffer& buffer, size_t rdata_len) {
        if (rdata_len < 4) {
            isc_throw(InvalidRdataLength, RRType(typeCode) << " too short");
        }

        uint16_t tag = buffer.readUint16();
        uint16_t algorithm = buffer.readUint8();
        uint16_t digest_type = buffer.readUint8();

        rdata_len -= 4;
        digest_.resize(rdata_len);
        buffer.readData(&digest_[0], rdata_len);

        tag_ = tag;
        algorithm_ = algorithm;
        digest_type_ = digest_type;
    }

    DSLikeImpl(const DSLikeImpl& source)
    {
        digest_ = source.digest_;
        tag_ = source.tag_;
        algorithm_ = source.algorithm_;
        digest_type_ = source.digest_type_;
    }

    string
    toText() const {
        using namespace boost;
        return (lexical_cast<string>(static_cast<int>(tag_)) +
            " " + lexical_cast<string>(static_cast<int>(algorithm_)) +
            " " + lexical_cast<string>(static_cast<int>(digest_type_)) +
            " " + encodeHex(digest_));
    }

    void
    toWire(OutputBuffer& buffer) const {
        buffer.writeUint16(tag_);
        buffer.writeUint8(algorithm_);
        buffer.writeUint8(digest_type_);
        buffer.writeData(&digest_[0], digest_.size());
    }

    void
    toWire(AbstractMessageRenderer& renderer) const {
        renderer.writeUint16(tag_);
        renderer.writeUint8(algorithm_);
        renderer.writeUint8(digest_type_);
        renderer.writeData(&digest_[0], digest_.size());
    }

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

    uint16_t
    getTag() const {
        return (tag_);
    }

private:
    // straightforward representation of DS RDATA fields
    uint16_t tag_;
    uint8_t algorithm_;
    uint8_t digest_type_;
    vector<uint8_t> digest_;
};

#endif //  __DS_LIKE_H

// Local Variables: 
// mode: c++
// End: 
