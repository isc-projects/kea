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

#include <stdint.h>

#include <cassert>
#include <vector>

#include <exceptions/exceptions.h>

#include <dns/buffer.h>
#include <dns/messagerenderer.h>
#include <dns/name.h>
#include <dns/rdata.h>
#include <dns/rdatafields.h>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace isc {
namespace dns {
namespace rdata {

/// This is a helper class for \c RdataFields.
///
/// It manages a local storage for the data when \c RdataFields is constructed
/// from an \c Rdata.
/// The implementation is hidden here to hide non portable details such as
/// std::vector.
/// To minimize construction overhead in the other case, an instance of
/// this class is instantiated only when necessary.
struct RdataFields::RdataFieldsDetail {
    RdataFieldsDetail(const vector<FieldSpec>& fields,
                      const void* data, size_t data_length) :
        allocated_fields_(fields),
        allocated_data_(static_cast<const uint8_t*>(data),
                        static_cast<const uint8_t*>(data) + data_length)
    {}
    const vector<FieldSpec> allocated_fields_;
    const vector<uint8_t> allocated_data_;
};

namespace {
// This class is used to divide the content of RDATA into \c RdataField
// fields via message rendering logic.
// The idea is to identify domain name fields in the writeName() method,
// and determine whether they are compressible using the "compress"
// parameter.
// Other types of data are simply copied into the internal buffer, and
// consecutive such fields are combined into a single \c RdataField field.
//
// Technically, this use of inheritance may be considered a violation of
// Liskov Substitution Principle in that it doesn't actually compress domain
// names, and some of the methods are not expected to be used.
// In fact, skip() or trim() may not be well defined for the purpose of this
// class.
// Nevertheless we keep this idea at the moment.  Since the usage is limited
// (it's only used within this file, and only used with \c Rdata variants),
// it's hopefully an acceptable practice.
class RdataFieldComposer : public AbstractMessageRenderer {
public:
    RdataFieldComposer(OutputBuffer& buffer) :
        buffer_(buffer), truncated_(false), length_limit_(65535),
        mode_(CASE_INSENSITIVE)
    {}
    virtual ~RdataFieldComposer() {}
    virtual const void* getData() const { return (buffer_.getData()); }
    virtual size_t getLength() const { return (buffer_.getLength()); }
    virtual bool isTruncated() const { return (truncated_); }
    virtual size_t getLengthLimit() const { return (length_limit_); }
    virtual CompressMode getCompressMode() const { return (mode_); }
    virtual void setTruncated() { truncated_ = true; }
    virtual void setLengthLimit(size_t len) { length_limit_ = len; }
    virtual void setCompressMode(CompressMode mode) { mode_ = mode; }
    virtual void writeUint8(uint8_t data);
    virtual void writeUint16(uint16_t data);
    virtual void writeUint32(uint32_t data);
    virtual void writeData(const void *data, size_t len);
    virtual void writeName(const Name& name, bool compress);

    virtual void clear() {
        isc_throw(Unexpected, "unexpected clear() for RdataFieldComposer");
    }
    virtual void skip(size_t) {
        isc_throw(Unexpected, "unexpected skip() for RdataFieldComposer");
    }
    virtual void trim(size_t) {
        isc_throw(Unexpected, "unexpected trim() for RdataFieldComposer");
    }
    virtual void writeUint16At(uint16_t, size_t) {
        isc_throw(Unexpected,
                  "unexpected writeUint16At() for RdataFieldComposer");
    }
    OutputBuffer buffer_;
    bool truncated_;
    size_t length_limit_;
    CompressMode mode_;
    vector<RdataFields::FieldSpec> fields_;
};

void
RdataFieldComposer::writeUint8(uint8_t data) {
    buffer_.writeUint8(data);
    if (fields_.empty() || fields_.back().type != RdataFields::DATA) {
        fields_.push_back(RdataFields::FieldSpec(RdataFields::DATA, 0));
    }
    fields_.back().len += sizeof(data);
}

void
RdataFieldComposer::writeUint16(uint16_t data) {
    buffer_.writeUint16(data);
    if (fields_.empty() || fields_.back().type != RdataFields::DATA) {
        fields_.push_back(RdataFields::FieldSpec(RdataFields::DATA, 0));
    }
    fields_.back().len += sizeof(data);
}

void
RdataFieldComposer::writeUint32(uint32_t data) {
    buffer_.writeUint32(data);
    if (fields_.empty() || fields_.back().type != RdataFields::DATA) {
        fields_.push_back(RdataFields::FieldSpec(RdataFields::DATA, 0));
    }
    fields_.back().len += sizeof(data);
}

void
RdataFieldComposer::writeData(const void *data, size_t len) {
    buffer_.writeData(data, len);
    if (fields_.empty() || fields_.back().type != RdataFields::DATA) {
        fields_.push_back(RdataFields::FieldSpec(RdataFields::DATA, 0));
    }
    fields_.back().len += len;
}

void
RdataFieldComposer::writeName(const Name& name, bool compress) {
    const RdataFields::Type field_type =
        compress ? RdataFields::COMPRESSIBLE_NAME :
        RdataFields::INCOMPRESSIBLE_NAME;
    name.toWire(buffer_);
    fields_.push_back(RdataFields::FieldSpec(field_type, name.getLength()));
}
}

RdataFields::RdataFields(const Rdata& rdata) {
    OutputBuffer buffer(0);
    RdataFieldComposer field_composer(buffer);
    rdata.toWire(field_composer);
    nfields_ = field_composer.fields_.size();
    data_length_ = field_composer.getLength();
    if (nfields_ > 0) {
        assert(data_length_ > 0);
        detail_ = new RdataFieldsDetail(field_composer.fields_,
                                        field_composer.getData(),
                                        field_composer.getLength());
        data_ = &detail_->allocated_data_[0];
        fields_ = &detail_->allocated_fields_[0];
    } else {
        assert(data_length_ == 0);
        detail_ = NULL;
        data_ = NULL;
        fields_ = NULL;
    }
}

RdataFields::RdataFields(const FieldSpec* fields, const unsigned int nfields,
                         const uint8_t* data, const size_t data_length) :
    fields_(fields), nfields_(nfields), data_(data), data_length_(data_length),
    detail_(NULL)
{
    if ((fields_ == NULL && nfields_ > 0) ||
        (fields_ != NULL && nfields_ == 0)) {
        isc_throw(InvalidParameter,
                  "Inconsistent parameters for RdataFields: nfields ("
                  << nfields_ << ") and fields conflict each other");
    }
    if ((data_ == NULL && data_length_ > 0) ||
        (data_ != NULL && data_length_ == 0)) {
        isc_throw(InvalidParameter,
                  "Inconsistent parameters for RdataFields: data length ("
                  << data_length_ << ") and data conflict each other");
    }

    size_t total_length = 0;
    for (int i = 0; i < nfields_; ++i) {
        total_length += fields_[i].len;
    }
    if (total_length != data_length_) {
        isc_throw(InvalidParameter,
                  "Inconsistent parameters for RdataFields; "
                  "fields len: " << total_length <<
                  " data len: " << data_length_);
    }
}

RdataFields::~RdataFields() {
    delete detail_;
}

RdataFields::FieldSpec
RdataFields::getFieldSpec(const unsigned int field_id) const {
    if (field_id >= nfields_) {
        isc_throw(OutOfRange, "Rdata field ID is out of range: " << field_id);
    }
    return (fields_[field_id]);
}

void
RdataFields::toWire(AbstractMessageRenderer& renderer) const {
    size_t offset = 0;

    for (int i = 0; i < nfields_; ++i) {
        if (fields_[i].type == DATA) {
            renderer.writeData(data_ + offset, fields_[i].len);
        } else {
            // XXX: this is inefficient.  Even if it's quite likely the
            // data is a valid wire representation of a name we parse
            // it to construct the Name object in the generic mode.
            // This should be improved in a future version.
            InputBuffer buffer(data_ + offset, fields_[i].len);
            renderer.writeName(Name(buffer),
                               fields_[i].type == COMPRESSIBLE_NAME ?
                               true : false);
        }   
        offset += fields_[i].len;
    }
}

void
RdataFields::toWire(OutputBuffer& buffer) const {
    buffer.writeData(data_, data_length_);
}
} // end of namespace rdata
} // end of namespace dns
} // end of namespace isc
