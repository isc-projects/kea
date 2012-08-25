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

#include "rdata_serialization.h"

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
#include <boost/static_assert.hpp>

using namespace isc::dns;
using std::vector;

namespace isc {
namespace datasrc {
namespace memory {

#include "rdata_serialization_priv.cc"

namespace {

// Many types of RDATA can be treated as a single-field, variable length
// field (in terms of our encoding).  The following define such most general
// form of field spec.
const RdataFieldSpec generic_data_fields[] = {
    {RdataFieldSpec::VARLEN_DATA, 0, NAMEATTR_NONE}
};
const uint16_t n_generic_data_fields =
    sizeof(generic_data_fields) / sizeof(RdataFieldSpec);
const RdataEncodeSpec generic_data_spec = {
    n_generic_data_fields, 0, 1, generic_data_fields
};

// RDATA consist of a single IPv4 address field.
const RdataFieldSpec single_ipv4_fields[] = {
    {RdataFieldSpec::FIXEDLEN_DATA, sizeof(uint32_t), NAMEATTR_NONE}
};
const uint16_t n_ipv4_fields =
    sizeof(single_ipv4_fields) / sizeof(RdataFieldSpec);

// RDATA consist of a single IPv6 address field.
const RdataFieldSpec single_ipv6_fields[] = {
    {RdataFieldSpec::FIXEDLEN_DATA, 16, NAMEATTR_NONE} // 128bits = 16 bytes
};
const uint16_t n_ipv6_fields =
    sizeof(single_ipv6_fields) / sizeof(RdataFieldSpec);

// There are several RR types that consist of a single domain name.
const RdataFieldSpec single_noattr_name_fields[] = {
    {RdataFieldSpec::DOMAIN_NAME, 0, NAMEATTR_NONE}
};
const RdataFieldSpec single_compressible_name_fields[] = {
    {RdataFieldSpec::DOMAIN_NAME, 0, NAMEATTR_COMPRESSIBLE}
};
const RdataFieldSpec single_compadditional_name_fields[] = {
    {RdataFieldSpec::DOMAIN_NAME, 0,
     static_cast<RdataNameAttributes>(
         static_cast<unsigned int>(NAMEATTR_COMPRESSIBLE) |
         static_cast<unsigned int>(NAMEATTR_ADDITIONAL))}
};
const uint16_t n_single_name_fields =
    sizeof(single_noattr_name_fields) / sizeof(RdataFieldSpec);

// RDATA consisting of two names.  There are some of this type.
const RdataFieldSpec double_compressible_name_fields[] = {
    {RdataFieldSpec::DOMAIN_NAME, 0, NAMEATTR_COMPRESSIBLE},
    {RdataFieldSpec::DOMAIN_NAME, 0, NAMEATTR_COMPRESSIBLE}
};
const RdataFieldSpec double_noattr_name_fields[] = {
    {RdataFieldSpec::DOMAIN_NAME, 0, NAMEATTR_NONE},
    {RdataFieldSpec::DOMAIN_NAME, 0, NAMEATTR_NONE}
};
const uint16_t n_double_name_fields =
    sizeof(double_compressible_name_fields) / sizeof(RdataFieldSpec);

// SOA specific: two compressible names + 5*32-bit data
const RdataFieldSpec soa_fields[] = {
    {RdataFieldSpec::DOMAIN_NAME, 0, NAMEATTR_COMPRESSIBLE},
    {RdataFieldSpec::DOMAIN_NAME, 0, NAMEATTR_COMPRESSIBLE},
    {RdataFieldSpec::FIXEDLEN_DATA, sizeof(uint32_t) * 5, NAMEATTR_NONE}
};
const uint16_t n_soa_fields = sizeof(soa_fields) / sizeof(RdataFieldSpec);

// MX specific: 16-bit data + compressible/additional name
const RdataFieldSpec mx_fields[] = {
    {RdataFieldSpec::FIXEDLEN_DATA, sizeof(uint16_t), NAMEATTR_NONE},
    {RdataFieldSpec::DOMAIN_NAME, 0,
     static_cast<RdataNameAttributes>(
         static_cast<unsigned int>(NAMEATTR_COMPRESSIBLE) |
         static_cast<unsigned int>(NAMEATTR_ADDITIONAL))}
};
const uint16_t n_mx_fields = sizeof(mx_fields) / sizeof(RdataFieldSpec);

// AFSDB specific: 16-bit data + no-attribute name
const RdataFieldSpec afsdb_fields[] = {
    {RdataFieldSpec::FIXEDLEN_DATA, sizeof(uint16_t), NAMEATTR_NONE},
    {RdataFieldSpec::DOMAIN_NAME, 0, NAMEATTR_NONE}
};
const uint16_t n_afsdb_fields = sizeof(afsdb_fields) / sizeof(RdataFieldSpec);

// SRV specific: 3*16-bit data + additional name
const RdataFieldSpec srv_fields[] = {
    {RdataFieldSpec::FIXEDLEN_DATA, sizeof(uint16_t) * 3, NAMEATTR_NONE},
    {RdataFieldSpec::DOMAIN_NAME, 0, NAMEATTR_ADDITIONAL}
};
const uint16_t n_srv_fields = sizeof(srv_fields) / sizeof(RdataFieldSpec);

// NAPTR specific: (multi-field) variable data + (additional) name
// NAPTR requires complicated additional section handling; for now, we skip
// the additional handling completely.
const RdataFieldSpec naptr_fields[] = {
    {RdataFieldSpec::VARLEN_DATA, 0, NAMEATTR_NONE},
    {RdataFieldSpec::DOMAIN_NAME, 0, NAMEATTR_NONE}
};
const uint16_t n_naptr_fields = sizeof(naptr_fields) / sizeof(RdataFieldSpec);

// NSEC specific: no-attribute name + varlen data
const RdataFieldSpec nsec_fields[] = {
    {RdataFieldSpec::DOMAIN_NAME, 0, NAMEATTR_NONE},
    {RdataFieldSpec::VARLEN_DATA, 0, NAMEATTR_NONE}
};
const uint16_t n_nsec_fields = sizeof(nsec_fields) / sizeof(RdataFieldSpec);

// Class IN encode specs.  This gives a shortcut to the encode spec for
// some well-known types of RDATA specific to class IN (most of which are
// generic and can be used for other classes).  The array index is the
// RR type code.
const RdataEncodeSpec encode_spec_list_in[] = {
    generic_data_spec,                         // #0: (NONE)
    {n_ipv4_fields, 0, 0, single_ipv4_fields},   // #1: A
    {n_single_name_fields, 1, 0, single_compadditional_name_fields}, // #2: NS
    generic_data_spec,          // #3
    generic_data_spec,          // #4
    {n_single_name_fields, 1, 0, single_compressible_name_fields}, // #5: CNAME
    {n_soa_fields, 2, 0, soa_fields}, // #6: SOA
    generic_data_spec,                // #7
    generic_data_spec,                // #8
    generic_data_spec,                // #9
    generic_data_spec,                // #10
    generic_data_spec,                // #11
    {n_single_name_fields, 1, 0, single_compressible_name_fields}, // #12: PTR
    generic_data_spec,          // #13: HINFO
    {n_double_name_fields, 2, 0, double_compressible_name_fields}, // #14:HINFO
    {n_mx_fields, 1, 0, mx_fields}, // #15: MX
    generic_data_spec, // #16: TXT
    {n_double_name_fields, 2, 0, double_noattr_name_fields}, // 17: RP
    {n_afsdb_fields, 1, 0, afsdb_fields}, // #18: AFSDB
    // #19-#26
    generic_data_spec, generic_data_spec, generic_data_spec, generic_data_spec,
    generic_data_spec, generic_data_spec, generic_data_spec, generic_data_spec,
    generic_data_spec,                // #27
    {n_ipv6_fields, 0, 0, single_ipv6_fields},   // #28: AAAA
    // #29-#32
    generic_data_spec, generic_data_spec, generic_data_spec, generic_data_spec,
    {n_srv_fields, 1, 0, srv_fields},   // #33: SRV
    generic_data_spec,                  // #34
    {n_naptr_fields, 1, 1, naptr_fields}, // #35: NAPTR
    generic_data_spec,                  // #36
    generic_data_spec,                  // #37
    generic_data_spec,                  // #38
    {n_single_name_fields, 1, 0, single_noattr_name_fields}, // #39 DNAME
    generic_data_spec,                  // #40
    generic_data_spec,                  // #41 (OPT)
    generic_data_spec,                  // #42
    generic_data_spec, // #43: DS (this is opaque for encoding purposes)
    generic_data_spec, // #44: SSHFP (this is opaque for encoding purposes)
    generic_data_spec,                  // #45
    generic_data_spec, // #46: RRSIG (this is opaque for encoding purposes)
    {n_nsec_fields, 1, 1, nsec_fields} // #47: NSEC

    // All others can be treated as single-field variable length data, at
    // least for currently supported RR types.
};

// # of entries in encode_spec_list_in
const size_t encode_spec_list_in_size =
    sizeof(encode_spec_list_in) / sizeof(encode_spec_list_in[0]);
BOOST_STATIC_ASSERT(encode_spec_list_in_size == 48);

}

/// \brief Get the spec for given class and type
const RdataEncodeSpec&
getRdataEncodeSpec(const RRClass& rrclass, const RRType& rrtype) {
    // Special case: for classes other than IN, we treat RDATA of RR types
    // that are class-IN specific as generic opaque data.
    if (rrclass != RRClass::IN() &&
        (rrtype == RRType::A() || rrtype == RRType::AAAA() ||
         rrtype == RRType::SRV())) {
        return (generic_data_spec);
    }

    // Otherwise, if the type is in the pre-defined range, we use the defined
    // spec; otherwise we treat it as opaque data.
    const uint16_t typecode = rrtype.getCode();
    if (typecode < encode_spec_list_in_size) {
        return (encode_spec_list_in[rrtype.getCode()]);
    }
    return (generic_data_spec);
}

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

RdataReader::RdataReader(const RRClass& rrclass, const RRType& rrtype,
                         const void* data,
                         size_t rdata_count, size_t sig_count,
                         const NameAction& name_action,
                         const DataAction& data_action) :
    name_action_(name_action),
    data_action_(data_action),
    spec_(getRdataEncodeSpec(rrclass, rrtype)),
    var_count_total_(spec_.varlen_count * rdata_count),
    sig_count_(sig_count),
    spec_count_(spec_.field_count * rdata_count),
    // The lenghts are stored first
    lengths_(reinterpret_cast<const uint16_t*>(data)),
    // And the data just after all the lengths
    data_(reinterpret_cast<const uint8_t*>(data) +
          (var_count_total_ + sig_count_) * sizeof(uint16_t)),
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
        const RdataFieldSpec& spec(spec_.fields[(spec_pos_++) %
                                                spec_.field_count]);
        if (spec.type == RdataFieldSpec::DOMAIN_NAME) {
            const LabelSequence sequence(data_ + data_pos_);
            data_pos_ += sequence.getSerializedLength();
            name_action(sequence, spec.name_attributes);
        } else {
            const size_t length(spec.type == RdataFieldSpec::FIXEDLEN_DATA ?
                                spec.fixeddata_len : lengths_[length_pos_++]);
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

void
RdataReader::emptyNameAction(const LabelSequence&, RdataNameAttributes) {
    // Do nothing here.
}

void
RdataReader::emptyDataAction(const void*, size_t) {
    // Do nothing here.
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
        ++sig_pos_;
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

} // namespace memory
} // namespace datasrc
} // datasrc isc
