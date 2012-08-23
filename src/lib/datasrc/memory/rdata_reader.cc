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

RdataReader::RdataReader(const RRClass& rrclass, const RRType& rrtype,
                         const uint8_t* data,
                         size_t rdata_count, size_t sig_count,
                         const NameAction& name_action,
                         const DataAction& data_action) :
    name_action_(name_action),
    data_action_(data_action),
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
    sigs_(NULL)
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

RdataReader::Boundary
RdataReader::nextInternal(const NameAction& name_action,
                          const DataAction& data_action)
{

    if (spec_pos_ < spec_count_) {
        const RdataFieldSpec& spec(spec_.fields[(spec_pos_ ++) %
                                                spec_.field_count]);
        if (spec.type == RdataFieldSpec::DOMAIN_NAME) {
            const LabelSequence sequence(data_ + data_pos_);
            data_pos_ += sequence.getSerializedLength();
            name_action(sequence, spec.name_attributes);
        } else {
            const size_t length(spec.type == RdataFieldSpec::FIXEDLEN_DATA ?
                                spec.fixeddata_len : lengths_[length_pos_ ++]);
            const uint8_t* const pos = data_ + data_pos_;
            data_pos_ += length;
            data_action(pos, length);
        }
        return (spec_pos_ % spec_.field_count == 0 ?
                RDATA_BOUNDARY : NO_BOUNDARY);
    } else {
        sigs_ = data_ + data_pos_;
        return (RRSET_BOUNDARY);
    }
}

RdataReader::Boundary
RdataReader::next() {
    return (nextInternal(name_action_, data_action_));
}

RdataReader::Boundary
RdataReader::nextSig() {
    if (sig_pos_ < sig_count_) {
        if (sigs_ == NULL) {
            // We didn't find where the signatures start yet. We do it
            // by iterating the whole data and then returning the state
            // back.
            const size_t data_pos = data_pos_;
            const size_t spec_pos = spec_pos_;
            const size_t length_pos = length_pos_;
            // When the next() gets to the last item, it sets the sigs_
            while (nextInternal(emptyNameAction, emptyDataAction) !=
                   RRSET_BOUNDARY) {}
            assert(sigs_ != NULL);
            // Return the state
            data_pos_ = data_pos;
            spec_pos_ = spec_pos;
            length_pos_ = length_pos;
        }
        // Extract the result
        const size_t length = lengths_[var_count_total_ + sig_pos_];
        const uint8_t* const pos = sigs_ + sig_data_pos_;
        // Move the position of iterator.
        sig_data_pos_ += lengths_[var_count_total_ + sig_pos_];
        sig_pos_ ++;
        // Call the callback
        data_action_(pos, length);
        return (RDATA_BOUNDARY);
    } else {
        return (RRSET_BOUNDARY);
    }
}

size_t
RdataReader::getSize() const {
    size_t storage_size = 0;    // this will be the end result
    size_t data_pos = 0;
    size_t length_pos = 0;

    // Go over all data fields, adding their lengths to storage_size
    for (size_t spec_pos = 0; spec_pos < spec_count_; ++spec_pos) {
        const RdataFieldSpec& spec =
            spec_.fields[spec_pos % spec_.field_count];
        if (spec.type == RdataFieldSpec::DOMAIN_NAME) {
            const size_t seq_len =
                LabelSequence(data_ + data_pos).getSerializedLength();
            data_pos += seq_len;
            storage_size += seq_len;
        } else {
            const size_t data_len =
                (spec.type == RdataFieldSpec::FIXEDLEN_DATA ?
                 spec.fixeddata_len : lengths_[length_pos++]);
            data_pos += data_len;
            storage_size += data_len;
        }
    }
    // Same for all RRSIG data
    for (size_t sig_pos = 0; sig_pos < sig_count_; ++sig_pos) {
        const size_t sig_data_len = lengths_[length_pos++];
        storage_size += sig_data_len;
    }

    // Finally, add the size for 16-bit length fields
    storage_size += (var_count_total_ * sizeof(uint16_t) +
                     sig_count_ * sizeof(uint16_t));

    return (storage_size);
}

}
}
}
