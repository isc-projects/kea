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

struct DSImpl {
    // straightforward representation of DS RDATA fields
    DSImpl(uint16_t tag, uint8_t algorithm, uint8_t digest_type,
           const vector<uint8_t>& digest) :
        tag_(tag), algorithm_(algorithm), digest_type_(digest_type),
        digest_(digest)
    {}

    uint16_t tag_;
    uint8_t algorithm_;
    uint8_t digest_type_;
    const vector<uint8_t> digest_;
};

template<class RTYPE, uint16_t typeCode>class DS_LIKE : public Rdata {
public:
    DS_LIKE(const string& ds_str) :
	impl_(NULL)
    {
	istringstream iss(ds_str);
	unsigned int tag, algorithm, digest_type;
	stringbuf digestbuf;

	iss >> tag >> algorithm >> digest_type >> &digestbuf;
	if (iss.bad() || iss.fail()) {
	    isc_throw(InvalidRdataText, "Invalid " +
		      RRParamRegistry::getRegistry().codeToTypeText(typeCode) +
		      " text");
	}
	if (tag > 0xffff) {
	    isc_throw(InvalidRdataText,
		      RRParamRegistry::getRegistry().codeToTypeText(typeCode) +
		      " tag out of range");
	}
	if (algorithm > 0xff) {
	    isc_throw(InvalidRdataText,
		      RRParamRegistry::getRegistry().codeToTypeText(typeCode) +
		      " algorithm out of range");
	}
	if (digest_type > 0xff) {
	    isc_throw(InvalidRdataText,
		      RRParamRegistry::getRegistry().codeToTypeText(typeCode) +
		      " digest type out of range");
	}

	vector<uint8_t> digest;
	decodeHex(digestbuf.str(), digest);

	impl_ = new DSImpl(tag, algorithm, digest_type, digest);
    }

    DS_LIKE(InputBuffer& buffer, size_t rdata_len) {
	if (rdata_len < 4) {
	    isc_throw(InvalidRdataLength,
		      RRParamRegistry::getRegistry().codeToTypeText(typeCode) +
		      " too short");
	}

	uint16_t tag = buffer.readUint16();
	uint16_t algorithm = buffer.readUint8();
	uint16_t digest_type = buffer.readUint8();

	rdata_len -= 4;
	vector<uint8_t> digest(rdata_len);
	buffer.readData(&digest[0], rdata_len);

	impl_ = new DSImpl(tag, algorithm, digest_type, digest);
    }

    DS_LIKE(const DS_LIKE& source) :
	Rdata(), impl_(new DSImpl(*source.impl_))
    {}

    DS_LIKE&
    operator=(const DS_LIKE& source) {
	if (impl_ == source.impl_) {
	    return (*this);
	}

	DSImpl* newimpl = new DSImpl(*source.impl_);
	delete impl_;
	impl_ = newimpl;

	return (*this);
    }

    ~DS_LIKE() {
	delete impl_;
    }

    string
    toText() const {
	using namespace boost;
	return (lexical_cast<string>(static_cast<int>(impl_->tag_)) +
	    " " + lexical_cast<string>(static_cast<int>(impl_->algorithm_)) +
	    " " + lexical_cast<string>(static_cast<int>(impl_->digest_type_)) +
	    " " + encodeHex(impl_->digest_));
    }

    void
    toWire(OutputBuffer& buffer) const {
	buffer.writeUint16(impl_->tag_);
	buffer.writeUint8(impl_->algorithm_);
	buffer.writeUint8(impl_->digest_type_);
	buffer.writeData(&impl_->digest_[0], impl_->digest_.size());
    }

    void
    toWire(AbstractMessageRenderer& renderer) const {
	renderer.writeUint16(impl_->tag_);
	renderer.writeUint8(impl_->algorithm_);
	renderer.writeUint8(impl_->digest_type_);
	renderer.writeData(&impl_->digest_[0], impl_->digest_.size());
    }

    int
    compare(const Rdata& other) const {
	const RTYPE& other_ds = dynamic_cast<const RTYPE&>(other);

	if (impl_->tag_ != other_ds.impl_->tag_) {
	    return (impl_->tag_ < other_ds.impl_->tag_ ? -1 : 1);
	}
	if (impl_->algorithm_ != other_ds.impl_->algorithm_) {
	    return (impl_->algorithm_ < other_ds.impl_->algorithm_ ? -1 : 1);
	}
	if (impl_->digest_type_ != other_ds.impl_->digest_type_) {
	    return (impl_->digest_type_ < other_ds.impl_->digest_type_ ? -1 : 1);
	}

	size_t this_len = impl_->digest_.size();
	size_t other_len = other_ds.impl_->digest_.size();
	size_t cmplen = min(this_len, other_len);
	int cmp = memcmp(&impl_->digest_[0], &other_ds.impl_->digest_[0], cmplen);
	if (cmp != 0) {
	    return (cmp);
	} else {
	    return ((this_len == other_len) ? 0 : (this_len < other_len) ? -1 : 1);
	}
    }

    uint16_t
    getTag() const {
	return (impl_->tag_);
    }

private:
    DSImpl* impl_;
};

#endif //  __DS_LIKE_H

// Local Variables: 
// mode: c++
// End: 
