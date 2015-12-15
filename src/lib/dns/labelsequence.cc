// Copyright (C) 2012-2015  Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <dns/labelsequence.h>
#include <dns/name_internal.h>
#include <exceptions/exceptions.h>

#include <boost/functional/hash.hpp>

#include <cstring>

namespace isc {
namespace dns {

LabelSequence::LabelSequence(const void* buf) {
#ifdef ENABLE_DEBUG
    // In non-debug mode, derefencing the NULL pointer further below
    // will lead to a crash, so disabling this check is not
    // unsafe. Except for a programming mistake, this case should not
    // happen.
    if (buf == NULL) {
        isc_throw(BadValue,
                  "Null pointer passed to LabelSequence constructor");
    }
#endif

    const uint8_t* bp = reinterpret_cast<const uint8_t*>(buf);
    first_label_ = 0;
    const uint8_t offsets_len = *bp++;

#ifdef ENABLE_DEBUG
    if (offsets_len == 0 || offsets_len > Name::MAX_LABELS) {
        isc_throw(BadValue,
                  "Bad offsets len in serialized LabelSequence data: "
                  << static_cast<unsigned int>(offsets_len));
    }
#endif

    last_label_ = offsets_len - 1;
    offsets_ = bp;
    data_ = bp + offsets_len;

#ifdef ENABLE_DEBUG
    // Check the integrity on the offsets and the name data
    const uint8_t* dp = data_;
    for (size_t cur_offset = 0; cur_offset < offsets_len; ++cur_offset) {
        if (dp - data_ != offsets_[cur_offset] || *dp > Name::MAX_LABELLEN) {
            isc_throw(BadValue,
                      "Broken offset or name data in serialized "
                      "LabelSequence data");
        }
        dp += (1 + *dp);
    }
#endif
}

LabelSequence::LabelSequence(const LabelSequence& src,
                             uint8_t buf[MAX_SERIALIZED_LENGTH])
{
    size_t data_len;
    const uint8_t *data = src.getData(&data_len);
    std::memcpy(buf, data, data_len);

    for (size_t i = 0; i < src.getLabelCount(); ++i) {
        buf[Name::MAX_WIRE + i] = src.offsets_[i + src.first_label_] -
                                  src.offsets_[src.first_label_];
    }

    first_label_ = 0;
    last_label_ = src.last_label_ - src.first_label_;
    data_ = buf;
    offsets_ = &buf[Name::MAX_WIRE];
}


const uint8_t*
LabelSequence::getData(size_t *len) const {
    *len = getDataLength();
    return (&data_[offsets_[first_label_]]);
}

size_t
LabelSequence::getDataLength() const {
    const size_t last_label_len = data_[offsets_[last_label_]] + 1;
    return (offsets_[last_label_] - offsets_[first_label_] + last_label_len);
}

size_t
LabelSequence::getSerializedLength() const {
    return (1 + getLabelCount() + getDataLength());
}

namespace {
// Check if buf is not in the range of [bp, ep), which means
// - end of buffer is before bp, or
// - beginning of buffer is on or after ep
bool
isOutOfRange(const uint8_t* bp, const uint8_t* ep,
             const uint8_t* buf, size_t buf_len)
{
    return (bp >= buf + buf_len || // end of buffer is before bp
            ep <= buf);            // beginning of buffer is on or after ep
}
}

void
LabelSequence::serialize(void* buf, size_t buf_len) const {
    const size_t expected_size = getSerializedLength();
    if (expected_size > buf_len) {
        isc_throw(BadValue, "buffer too short for LabelSequence::serialize");
    }

    const size_t offsets_len = getLabelCount();
    assert(offsets_len < 256);  // should be in the 8-bit range

    // Overridden check.  Buffer shouldn't overwrap the offset of name data
    // regions.
    uint8_t* bp = reinterpret_cast<uint8_t*>(buf);
    const size_t ndata_len = getDataLength();
    if (!isOutOfRange(offsets_, offsets_ + offsets_len, bp, buf_len) ||
        !isOutOfRange(data_, data_ + ndata_len, bp, buf_len)) {
        isc_throw(BadValue, "serialize would break the source sequence");
    }

    *bp++ = offsets_len;
    for (size_t i = 0; i < offsets_len; ++i) {
        *bp++ = offsets_[first_label_ + i] - offsets_[first_label_];
    }
    std::memcpy(bp, &data_[offsets_[first_label_]], ndata_len);
    bp += ndata_len;

    assert(bp - reinterpret_cast<const uint8_t*>(buf) == expected_size);
}

bool
LabelSequence::equals(const LabelSequence& other, bool case_sensitive) const {
    size_t len, other_len;
    const uint8_t* data = getData(&len);
    const uint8_t* other_data = other.getData(&other_len);

    if (len != other_len) {
        return (false);
    }
    if (case_sensitive) {
        return (std::memcmp(data, other_data, len) == 0);
    }

    // As long as the data was originally validated as (part of) a name,
    // label length must never be a capital ascii character, so we can
    // simply compare them after converting to lower characters.
    for (size_t i = 0; i < len; ++i) {
        const uint8_t ch = data[i];
        const uint8_t other_ch = other_data[i];
        if (isc::dns::name::internal::maptolower[ch] !=
            isc::dns::name::internal::maptolower[other_ch]) {
            return (false);
        }
    }
    return (true);
}

NameComparisonResult
LabelSequence::compare(const LabelSequence& other,
                       bool case_sensitive) const
{
    // Determine the relative ordering under the DNSSEC order relation of
    // 'this' and 'other', and also determine the hierarchical relationship
    // of the labels.

    unsigned int nlabels = 0;
    int l1 = getLabelCount();
    int l2 = other.getLabelCount();
    const int ldiff = static_cast<int>(l1) - static_cast<int>(l2);
    unsigned int l = (ldiff < 0) ? l1 : l2;

    while (l > 0) {
        --l;
        --l1;
        --l2;
        size_t pos1 = offsets_[l1 + first_label_];
        size_t pos2 = other.offsets_[l2 + other.first_label_];
        unsigned int count1 = data_[pos1++];
        unsigned int count2 = other.data_[pos2++];

        // We don't support any extended label types including now-obsolete
        // bitstring labels.
        assert(count1 <= Name::MAX_LABELLEN && count2 <= Name::MAX_LABELLEN);

        const int cdiff = static_cast<int>(count1) - static_cast<int>(count2);
        unsigned int count = (cdiff < 0) ? count1 : count2;

        while (count > 0) {
            const uint8_t label1 = data_[pos1];
            const uint8_t label2 = other.data_[pos2];
            int chdiff;

            if (case_sensitive) {
                chdiff = static_cast<int>(label1) - static_cast<int>(label2);
            } else {
                chdiff = static_cast<int>(
                    isc::dns::name::internal::maptolower[label1]) -
                    static_cast<int>(
                        isc::dns::name::internal::maptolower[label2]);
            }

            if (chdiff != 0) {
                return (NameComparisonResult(
                            chdiff, nlabels,
                            nlabels == 0 ? NameComparisonResult::NONE :
                            NameComparisonResult::COMMONANCESTOR));
            }
            --count;
            ++pos1;
            ++pos2;
        }
        if (cdiff != 0) {
            return (NameComparisonResult(
                        cdiff, nlabels,
                        nlabels == 0 ? NameComparisonResult::NONE :
                        NameComparisonResult::COMMONANCESTOR));
        }
        ++nlabels;
    }

    if (ldiff < 0) {
        return (NameComparisonResult(ldiff, nlabels,
                                     NameComparisonResult::SUPERDOMAIN));
    } else if (ldiff > 0) {
        return (NameComparisonResult(ldiff, nlabels,
                                     NameComparisonResult::SUBDOMAIN));
    }

    return (NameComparisonResult(ldiff, nlabels, NameComparisonResult::EQUAL));
}

void
LabelSequence::stripLeft(size_t i) {
    if (i >= getLabelCount()) {
        isc_throw(OutOfRange, "Cannot strip to zero or less labels; " << i <<
                              " (labelcount: " << getLabelCount() << ")");
    }
    first_label_ += i;
}

void
LabelSequence::stripRight(size_t i) {
    if (i >= getLabelCount()) {
        isc_throw(OutOfRange, "Cannot strip to zero or less labels; " << i <<
                              " (labelcount: " << getLabelCount() << ")");
    }
    last_label_ -= i;
}

bool
LabelSequence::isAbsolute() const {
    return (data_[offsets_[last_label_]] == 0);
}

size_t
LabelSequence::getHash(bool case_sensitive) const {
    size_t length;
    const uint8_t* s = getData(&length);
    if (length > 16) {
        length = 16;
    }

    size_t hash_val = 0;
    while (length > 0) {
        const uint8_t c = *s++;
        boost::hash_combine(hash_val, case_sensitive ? c :
                            isc::dns::name::internal::maptolower[c]);
        --length;
    }
    return (hash_val);
}

std::string
LabelSequence::toText(bool omit_final_dot) const {
    const uint8_t* np = &data_[offsets_[first_label_]];
    const uint8_t* np_end = np + getDataLength();

    // use for integrity check
    unsigned int labels = getLabelCount();
    // init with an impossible value to catch error cases in the end:
    unsigned int count = Name::MAX_LABELLEN + 1;

    // result string: it will roughly have the same length as the wire format
    // label sequence data.  reserve that length to minimize reallocation.
    std::string result;
    result.reserve(getDataLength());

    while (np != np_end) {
        labels--;
        count = *np++;

        if (count == 0) {
            // We've reached the "final dot".  If we've not dumped any
            // character, the entire label sequence is the root name.
            // In that case we don't omit the final dot.
            if (!omit_final_dot || result.empty()) {
                result.push_back('.');
            }
            break;
        }

        if (count <= Name::MAX_LABELLEN) {
            assert(np_end - np >= count);

            if (!result.empty()) {
                // just after a non-empty label.  add a separating dot.
                result.push_back('.');
            }

            while (count-- > 0) {
                const uint8_t c = *np++;
                switch (c) {
                case 0x22: // '"'
                case 0x28: // '('
                case 0x29: // ')'
                case 0x2E: // '.'
                case 0x3B: // ';'
                case 0x5C: // '\\'
                    // Special modifiers in zone files.
                case 0x40: // '@'
                case 0x24: // '$'
                    result.push_back('\\');
                    result.push_back(c);
                    break;
                default:
                    if (c > 0x20 && c < 0x7f) {
                        // append printable characters intact
                        result.push_back(c);
                    } else {
                        // encode non-printable characters in the form of \DDD
                        result.push_back(0x5c);
                        result.push_back(0x30 + ((c / 100) % 10));
                        result.push_back(0x30 + ((c / 10) % 10));
                        result.push_back(0x30 + (c % 10));
                    }
                }
            }
        } else {
            isc_throw(BadLabelType, "unknown label type in name data");
        }
    }

    // We should be at the end of the data and have consumed all labels.
    assert(np == np_end);
    assert(labels == 0);

    return (result);
}

std::string
LabelSequence::toText() const {
    return (toText(!isAbsolute()));
}

void
LabelSequence::extend(const LabelSequence& labels,
                      uint8_t buf[MAX_SERIALIZED_LENGTH])
{
    // collect data to perform steps before anything is changed
    size_t label_count = last_label_ + 1;
    // Since we may have been stripped, do not use getDataLength(), but
    // calculate actual data size this labelsequence currently uses
    size_t data_pos = offsets_[last_label_] + data_[offsets_[last_label_]] + 1;

    // If this labelsequence is absolute, virtually strip the root label.
    if (isAbsolute()) {
        data_pos--;
        label_count--;
    }
    const size_t append_label_count = labels.getLabelCount();
    size_t data_len;
    const uint8_t *data = labels.getData(&data_len);

    // Sanity checks
    if (data_ != buf || offsets_ != &buf[Name::MAX_WIRE]) {
        isc_throw(BadValue,
                  "extend() called with unrelated buffer");
    }
    // Check MAX_LABELS before MAX_WIRE or it will be never reached
    if (label_count + append_label_count > Name::MAX_LABELS) {
        isc_throw(BadValue,
                  "extend() would exceed maximum number of labels");
    }
    if (data_pos + data_len > Name::MAX_WIRE) {
        isc_throw(BadValue,
                  "extend() would exceed maximum wire length");
    }

    // All seems to be reasonably ok, let's proceed.
    std::memmove(&buf[data_pos], data, data_len);

    for (size_t i = 0; i < append_label_count; ++i) {
        buf[Name::MAX_WIRE + label_count + i] =
            data_pos +
            labels.offsets_[i + labels.first_label_] -
            labels.offsets_[labels.first_label_];
    }
    last_label_ = label_count + append_label_count - 1;
}

std::ostream&
operator<<(std::ostream& os, const LabelSequence& label_sequence) {
    os << label_sequence.toText();
    return (os);
}

} // end namespace dns
} // end namespace isc
