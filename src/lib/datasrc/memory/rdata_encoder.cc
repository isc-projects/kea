// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include "rdata_encoder.h"
#include "rdata_field.h"

#include <exceptions/exceptions.h>

#include <util/buffer.h>

#include <dns/name.h>
#include <dns/labelsequence.h>
#include <dns/messagerenderer.h>
#include <dns/rdata.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>

#include <cassert>
#include <cstring>
#include <vector>

#include <stdint.h>

using namespace isc::dns;
using std::vector;

namespace isc {
namespace datasrc {
namespace memory {

namespace {

// This class is a helper for RdataEncoder to divide the content of RDATA
// fields for encoding by "abusing" the  message rendering logic.
// The idea is to identify domain name fields in the writeName() method,
// while keeping track of the size and position of other types of data
// around the names.
//
// Technically, this use of inheritance may be considered a violation of
// Liskov Substitution Principle in that it doesn't actually compress domain
// names, and some of the methods are not expected to be used.
// In fact, skip() or trim() may not be make much sense in this context.
// Nevertheless we keep this idea at the moment.  Since the usage is limited
// (it's only used within this file, and only used with \c Rdata variants),
// it's hopefully an acceptable practice.
class RdataFieldComposer : public AbstractMessageRenderer {
public:
    RdataFieldComposer() : last_data_pos_(0), encode_spec_(NULL),
                           current_field_(0)
    {}
    virtual ~RdataFieldComposer() {}
    virtual bool isTruncated() const { return (false); }
    virtual size_t getLengthLimit() const { return (65535); }
    virtual CompressMode getCompressMode() const { return (CASE_INSENSITIVE); }
    virtual void setTruncated() {}
    virtual void setLengthLimit(size_t) {}
    virtual void setCompressMode(CompressMode) {}

    // Called for each domain name in the RDATA, from the RDATA's toWire()
    // implementation.
    virtual void writeName(const Name& name, bool compress) {
        // First, see if we have other data already stored in the renderer's
        // buffer, and handle it appropriately.
        updateOtherData();

        // Then, we should still have a field in the spec, and it must be a
        // domain name field.
        if (current_field_ >= encode_spec_->field_count) {
            isc_throw(BadValue,
                      "RDATA encoder encounters an unexpected name data: " <<
                      name);
        }
        const RdataFieldSpec& field =
            encode_spec_->fields[current_field_++];
        // Since we know we've passed any prior data field, the next field
        // must be a domain name as long as it exists; otherwise it's a bug
        // in the spec (not a bogus input).  So we assert() that condition.
        assert(field.type == RdataFieldSpec::DOMAIN_NAME);

        // It would be compressed iff the field has that attribute.
        if (compress !=
            ((field.name_attributes & NAMEATTR_COMPRESSIBLE) != 0)) {
            isc_throw(BadValue, "RDATA encoder error, inconsistent name "
                      "compression policy: " << name);
        }

        const LabelSequence labels(name);
        labels.serialize(labels_placeholder_, sizeof(labels_placeholder_));
        writeData(labels_placeholder_, labels.getSerializedLength());

        last_data_pos_ += labels.getSerializedLength();
    }
    // Clear all internal states and resources for a new set of RDATA.
    void clearLocal(const RdataEncodeSpec* encode_spec) {
        AbstractMessageRenderer::clear();
        encode_spec_ = encode_spec;
        data_lengths_.clear();
        last_data_pos_ = 0;
    }
    // Called at the beginning of an RDATA.
    void startRdata() {
        current_field_ = 0;
    }
    // Called at the end of an RDATA.
    void endRdata() {
        // Handle any remaining data (there should be no more name).  Then
        // we should reach the end of the fields.
        updateOtherData();
        if (current_field_ != encode_spec_->field_count) {
            isc_throw(BadValue,
                      "RDATA encoder didn't find all expected fields");
        }
    }

    // Hold the lengths of variable length fields, in the order of their
    // appearance.  For convenience, allow the encoder to refer to it
    // directly.
    vector<uint16_t> data_lengths_;

private:
    // We use generict write* methods, with the exception of writeName.
    // So new data can arrive without us knowing it, this considers all new
    // data to be just data, checking consistency with the field spec, and
    // if it contains variable-length field, record its length.
    size_t last_data_pos_;
    void updateOtherData() {
        // If we've reached the end of the fields or we are expecting a
        // domain name, there's nothing to do here.
        if (current_field_ >= encode_spec_->field_count ||
            encode_spec_->fields[current_field_].type ==
            RdataFieldSpec::DOMAIN_NAME) {
            return;
        }

        const size_t cur_pos = getLength();
        const size_t data_len = cur_pos - last_data_pos_;

        const RdataFieldSpec& field = encode_spec_->fields[current_field_];
        if (field.type == RdataFieldSpec::FIXEDLEN_DATA) {
            // The data length of a fixed length field must be the one
            // specified in the field spec.
            if (data_len != field.fixeddata_len) {
                isc_throw(BadValue,
                          "RDATA encoding: available data too short for the "
                          "type");
            }
        } else {
            // For encoding purposes, a variable-length data field is
            // a single field covering all data, even if it may
            // consist of multiple fields as DNS RDATA (e.g. TXT).
            if (data_len > 0xffff) {
                isc_throw(RdataEncodingError, "RDATA field is too large: "
                          << data_len << " bytes");
            }
            data_lengths_.push_back(data_len);
        }

        ++current_field_;
        last_data_pos_ = cur_pos;
    }

    // The RDATA field spec of the current session.  Set at the beginning of
    // each session.
    const RdataEncodeSpec* encode_spec_;
    // the RDATA field (for encoding) currently handled.  Reset to 0 for
    // each RDATA of the session.
    size_t current_field_;
    // Placeholder to convert a name object to a label sequence.
    uint8_t labels_placeholder_[LabelSequence::MAX_SERIALIZED_LENGTH];
};
} // end of unnamed namespace

struct RdataEncoder::RdataEncoderImpl {
    RdataEncoderImpl() : encode_spec_(NULL), rrsig_buffer_(0),
                         rdata_count_(0)
    {}

    const RdataEncodeSpec* encode_spec_; // encode spec of current RDATA set
    RdataFieldComposer field_composer_;
    util::OutputBuffer rrsig_buffer_;
    size_t rdata_count_;
    vector<uint16_t> rrsig_lengths_;
};

RdataEncoder::RdataEncoder() :
    impl_(new RdataEncoderImpl)
{}

RdataEncoder::~RdataEncoder() {
    delete impl_;
}

void
RdataEncoder::start(RRClass rrclass, RRType rrtype) {
    if (rrtype == RRType::RRSIG()) {
        isc_throw(BadValue, "RRSIG cannot be encoded as main RDATA type");
    }

    impl_->encode_spec_ = &getRdataEncodeSpec(rrclass, rrtype);
    impl_->field_composer_.clearLocal(impl_->encode_spec_);
    impl_->rrsig_buffer_.clear();
    impl_->rdata_count_ = 0;
    impl_->rrsig_lengths_.clear();
}

void
RdataEncoder::addRdata(const rdata::Rdata& rdata) {
    if (impl_->encode_spec_ == NULL) {
        isc_throw(InvalidOperation,
                  "RdataEncoder::addRdata performed before start");
    }

    impl_->field_composer_.startRdata();
    rdata.toWire(impl_->field_composer_);
    impl_->field_composer_.endRdata();
    ++impl_->rdata_count_;
}

void
RdataEncoder::addSIGRdata(const rdata::Rdata& sig_rdata) {
    if (impl_->encode_spec_ == NULL) {
        isc_throw(InvalidOperation,
                  "RdataEncoder::addSIGRdata performed before start");
    }
    const size_t cur_pos = impl_->rrsig_buffer_.getLength();
    sig_rdata.toWire(impl_->rrsig_buffer_);
    const size_t rrsig_datalen = impl_->rrsig_buffer_.getLength() - cur_pos;
    if (rrsig_datalen > 0xffff) {
        isc_throw(RdataEncodingError, "RRSIG is too large: "
                  << rrsig_datalen << " bytes");
    }
    impl_->rrsig_lengths_.push_back(rrsig_datalen);
}

size_t
RdataEncoder::getStorageLength() const {
    if (impl_->encode_spec_ == NULL) {
        isc_throw(InvalidOperation,
                  "RdataEncoder::getStorageLength performed before start");
    }

    return (sizeof(uint16_t) * impl_->field_composer_.data_lengths_.size() +
            sizeof(uint16_t) * impl_->rrsig_lengths_.size() +
            impl_->rrsig_buffer_.getLength() +
            impl_->field_composer_.getLength());
}

void
RdataEncoder::encode(void* buf, size_t buf_len) const {
    if (impl_->encode_spec_ == NULL) {
        isc_throw(InvalidOperation,
                  "RdataEncoder::encode performed before start");
    }
    if (buf == NULL) {
        isc_throw(BadValue,
                  "RdataEncoder::encode NULL buffer is given");
    }
    if (getStorageLength() > buf_len) {
        isc_throw(BadValue, "RdataEncoder::encode short buffer given");
    }

    uint8_t* const dp_beg = reinterpret_cast<uint8_t*>(buf);
    uint8_t* dp = dp_beg;
    uint16_t* lenp = reinterpret_cast<uint16_t*>(buf);

    // Encode list of lengths for variable length fields (if any)
    if (!impl_->field_composer_.data_lengths_.empty()) {
        const size_t varlen_fields_len =
            impl_->field_composer_.data_lengths_.size() * sizeof(uint16_t);
        std::memcpy(lenp, &impl_->field_composer_.data_lengths_[0],
                    varlen_fields_len);
        lenp += impl_->field_composer_.data_lengths_.size();
        dp += varlen_fields_len;
    }
    // Encode list of lengths for RRSIGs (if any)
    if (!impl_->rrsig_lengths_.empty()) {
        const size_t rrsigs_len =
            impl_->rrsig_lengths_.size() * sizeof(uint16_t);
        std::memcpy(lenp, &impl_->rrsig_lengths_[0], rrsigs_len);
        dp += rrsigs_len;
    }
    // Encode main RDATA
    std::memcpy(dp, impl_->field_composer_.getData(),
                impl_->field_composer_.getLength());
    dp += impl_->field_composer_.getLength();
    // Encode RRSIGs, if any
    std::memcpy(dp, impl_->rrsig_buffer_.getData(),
                impl_->rrsig_buffer_.getLength());
    dp += impl_->rrsig_buffer_.getLength();

    // The validation at the entrance must ensure this
    assert(buf_len >= dp - dp_beg);
}


} // namespace memory
} // namespace datasrc
} // datasrc isc
