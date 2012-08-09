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

#include "rdata_reader.h"

using namespace isc::dns;

namespace isc {
namespace datasrc {
namespace memory {

void
RdataReader::emptyNameAction(const LabelSequence&, unsigned) {
    // Do nothing here. On purpose, it's not unfinished.
}

void
RdataReader::emptyDataAction(const uint8_t*, size_t) {
    // Do nothing here. On purpose, it's not unfinished.
}

RdataReader::Result::Result(const LabelSequence& label,
                            unsigned attributes) :
    label_(label),
    data_(NULL),
    size_(0),
    type_(NAME),
    compressible_((attributes & NAMEATTR_COMPRESSIBLE) != 0),
    additional_((attributes & NAMEATTR_ADDITIONAL) != 0)
{}

RdataReader::Result::Result(const uint8_t* data, size_t size) :
    label_(Name::ROOT_NAME()),
    data_(data),
    size_(size),
    type_(DATA),
    compressible_(false),
    additional_(false)
{}

const uint8_t*
RdataReader::findSigs() const {
    // Validate the lengths - we want to make sure all the lengths
    // fit. The base would be the beginning of all the data.
    const uint8_t* const
        base(static_cast<const uint8_t*>(static_cast<const void*>(lengths_)));
    if (base + size_ < data_) {
        isc_throw(isc::BadValue, "Size won't even hold all the length fields");
    }
    // It is easier to look from the end than from the beginning -
    // this way we just need to sum all the sig lenghs together.
    size_t sum(0);
    for (size_t i(0); i < sig_count_; ++ i) {
        sum += lengths_[var_count_total_ + i];
    }
    const uint8_t* const result(data_ + size_ - sum);
    // Validate the signatures fit.
    if (result < data_) {
        isc_throw(isc::BadValue, "Size won't even hold all the RRSigs");
    }
    return (result);
}

RdataReader::RdataReader(const RRClass& rrclass, const RRType& rrtype,
                         size_t size, const uint8_t* data,
                         size_t rdata_count, size_t sig_count,
                         const NameAction& name_action,
                         const DataAction& data_action) :
    name_action_(name_action),
    data_action_(data_action),
    size_(size),
    spec_(getRdataEncodeSpec(rrclass, rrtype)),
    var_count_total_(spec_.varlen_count * rdata_count),
    sig_count_(sig_count),
    spec_count_(spec_.field_count * rdata_count),
    // The casts, well, C++ decided it doesn't like completely valid
    // and explicitly allowed cast in C, so we need to fool it through
    // void.
    lengths_(static_cast<const uint16_t*>(
             static_cast<const void*>(data))), // The lenghts are stored first
    // And the data just after all the lengths
    data_(data + (var_count_total_ + sig_count_) * sizeof(uint16_t)),
    sigs_(findSigs())
{
    rewind();
}

void
RdataReader::rewind() {
    data_pos_ = 0;
    spec_pos_ = 0;
    length_pos_ = 0;
    sig_data_pos_ = 0;
    sig_pos_ = 0;
}

RdataReader::Result
RdataReader::next() {
    // TODO: Add checks we are in the valid part of memory
    if (spec_pos_ < spec_count_) {
        const RdataFieldSpec& spec(spec_.fields[(spec_pos_ ++) %
                                                spec_.field_count]);
        if (spec.type == RdataFieldSpec::DOMAIN_NAME) {
            const LabelSequence sequence(&data_[data_pos_]);
            data_pos_ += sequence.getSerializedLength();
            name_action_(sequence, spec.name_attributes);
            return (Result(sequence, spec.name_attributes));
        } else {
            const size_t length(spec.type == RdataFieldSpec::FIXEDLEN_DATA ?
                                spec.fixeddata_len : lengths_[length_pos_ ++]);
            Result result(&data_[data_pos_], length);
            data_pos_ += length;
            data_action_(result.data(), result.size());
            return (result);
        }
    } else {
        return (Result());
    }
}

RdataReader::Result
RdataReader::nextSig() {
    // We ensured the whole block of signatures is in the valid block,
    // so we don't need any checking here.
    if (sig_pos_ < sig_count_) {
        // Extract the result
        Result result(sigs_ + sig_data_pos_, lengths_[var_count_total_ +
                      sig_pos_]);
        // Move the position of iterator.
        sig_data_pos_ += lengths_[var_count_total_ + sig_pos_];
        sig_pos_ ++;
        // Call the callback
        data_action_(result.data(), result.size());
        return (result);
    } else {
        return (Result());
    }
}

}
}
}
