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

#include <dns/labelsequence.h>
#include <dns/name_internal.h>
#include <exceptions/exceptions.h>

#include <boost/functional/hash.hpp>

#include <cstring>

namespace isc {
namespace dns {

const uint8_t*
LabelSequence::getData(size_t *len) const {
    *len = getDataLength();
    return &(data_[offsets_[first_label_]]);
}

size_t
LabelSequence::getDataLength() const {
    // If the labelsequence is absolute, the current last_label_ falls
    // out of the vector (since it points to the 'label' after the
    // root label, which doesn't exist; in that case, return
    // the length for the 'previous' label (the root label) plus
    // one (for the root label zero octet)
    if (isAbsolute()) {
        return (offsets_[last_label_ - 1] -
                offsets_[first_label_] + 1);
    } else {
        return (offsets_[last_label_] - offsets_[first_label_]);
    }
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
                       bool case_sensitive) const {
    if (isAbsolute() ^ other.isAbsolute()) {
        return (NameComparisonResult(0, 0, NameComparisonResult::NONE));
    }

    // Determine the relative ordering under the DNSSEC order relation of
    // 'this' and 'other', and also determine the hierarchical relationship
    // of the names.

    unsigned int nlabels = 0;
    int l1 = last_label_ - first_label_;
    int l2 = other.last_label_ - other.first_label_;
    int ldiff = (int)l1 - (int)l2;
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

        int cdiff = (int)count1 - (int)count2;
        unsigned int count = (cdiff < 0) ? count1 : count2;

        while (count > 0) {
            uint8_t label1 = data_[pos1];
            uint8_t label2 = other.data_[pos2];
            int chdiff;

            if (case_sensitive) {
                chdiff = (int)label1 - (int)label2;
            } else {
                chdiff = (int)isc::dns::name::internal::maptolower[label1] -
                         (int)isc::dns::name::internal::maptolower[label2];
            }

            if (chdiff != 0) {
                if ((nlabels == 0) &&
                     (!isAbsolute() ||
                     ((last_label_ < getLabelCount()) ||
                      (other.last_label_ < other.getLabelCount())))) {
                    return (NameComparisonResult(0, 0,
                                                 NameComparisonResult::NONE));
                } else {
                    return (NameComparisonResult(chdiff, nlabels,
                                                 NameComparisonResult::COMMONANCESTOR));
                }
            }
            --count;
            ++pos1;
            ++pos2;
        }
        if (cdiff != 0) {
            if ((nlabels == 0) &&
                ((last_label_ < getLabelCount()) ||
                 (other.last_label_ < other.getLabelCount()))) {
                return (NameComparisonResult(0, 0,
                                             NameComparisonResult::NONE));
            } else {
                return (NameComparisonResult(cdiff, nlabels,
                                             NameComparisonResult::COMMONANCESTOR));
            }
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
    return (last_label_ == offsets_size_);
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
    unsigned int labels = last_label_ - first_label_;
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

std::ostream&
operator<<(std::ostream& os, const LabelSequence& label_sequence) {
    os << label_sequence.toText();
    return (os);
}

} // end namespace dns
} // end namespace isc
