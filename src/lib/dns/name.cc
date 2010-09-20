// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#include <cctype>
#include <cassert>
#include <iterator>
#include <functional>
#include <vector>
#include <iostream>
#include <algorithm>

#include <dns/buffer.h>
#include <dns/exceptions.h>
#include <dns/name.h>
#include <dns/messagerenderer.h>

using namespace std;
using isc::dns::NameComparisonResult;
using isc::dns::MessageRenderer;

namespace isc {
namespace dns {

namespace {
///
/// These are shortcut arrays for efficient character conversion.
/// digitvalue converts a digit character to the corresponding integer.
/// maptolower convert uppercase alphabets to their lowercase counterparts.
/// We once used a helper non-local static object to avoid hardcoding the
/// array members, but we then realized it's susceptible to static
/// initialization order fiasco: Since these constants are used in a Name
/// constructor, a non-local static Name object defined in another translation
/// unit than this file may not be initialized correctly.
/// There are several ways to address this issue, but in this specific case
/// we chose the naive but simple hardcoding approach.
///
/// These definitions are derived from BIND 9's libdns module.
/// Note: it was not clear why the maptolower array was needed rather than
/// using the standard tolower() function.  It was perhaps due performance
/// concern, but we were not sure.  Even if it was performance reasons, we
/// should carefully assess the effect via benchmarking to avoid the pitfall of 
/// premature optimization.  We should revisit this point later.
static const char digitvalue[256] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 16
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 32
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 48
     0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1, // 64
    -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 80
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 96
    -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 112
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 128
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 256
};

static const unsigned char maptolower[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
    0x40, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67, // ..., 'A' - 'G'
    0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f, // 'H' - 'O'
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77, // 'P' - 'W'
    0x78, 0x79, 0x7a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f, // 'X' - 'Z', ...
    0x60, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
    0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
    0x78, 0x79, 0x7a, 0x7b, 0x7c, 0x7d, 0x7e, 0x7f,
    0x80, 0x81, 0x82, 0x83, 0x84, 0x85, 0x86, 0x87,
    0x88, 0x89, 0x8a, 0x8b, 0x8c, 0x8d, 0x8e, 0x8f,
    0x90, 0x91, 0x92, 0x93, 0x94, 0x95, 0x96, 0x97,
    0x98, 0x99, 0x9a, 0x9b, 0x9c, 0x9d, 0x9e, 0x9f,
    0xa0, 0xa1, 0xa2, 0xa3, 0xa4, 0xa5, 0xa6, 0xa7,
    0xa8, 0xa9, 0xaa, 0xab, 0xac, 0xad, 0xae, 0xaf,
    0xb0, 0xb1, 0xb2, 0xb3, 0xb4, 0xb5, 0xb6, 0xb7,
    0xb8, 0xb9, 0xba, 0xbb, 0xbc, 0xbd, 0xbe, 0xbf,
    0xc0, 0xc1, 0xc2, 0xc3, 0xc4, 0xc5, 0xc6, 0xc7,
    0xc8, 0xc9, 0xca, 0xcb, 0xcc, 0xcd, 0xce, 0xcf,
    0xd0, 0xd1, 0xd2, 0xd3, 0xd4, 0xd5, 0xd6, 0xd7,
    0xd8, 0xd9, 0xda, 0xdb, 0xdc, 0xdd, 0xde, 0xdf,
    0xe0, 0xe1, 0xe2, 0xe3, 0xe4, 0xe5, 0xe6, 0xe7,
    0xe8, 0xe9, 0xea, 0xeb, 0xec, 0xed, 0xee, 0xef,
    0xf0, 0xf1, 0xf2, 0xf3, 0xf4, 0xf5, 0xf6, 0xf7,
    0xf8, 0xf9, 0xfa, 0xfb, 0xfc, 0xfd, 0xfe, 0xff
};
}

namespace {
///
/// Textual name parser states.
///
typedef enum {
    ft_init = 0,                // begin of the name
    ft_start,                   // begin of a label
    ft_ordinary,                // parsing an ordinary label
    ft_initialescape,           // just found '\'
    ft_escape,                  // begin of handling a '\'-escaped sequence
    ft_escdecimal,              // parsing a '\DDD' octet.

    // Unused at this moment.  We'll revisit this when we support master file
    // parser where @ is used to mean an origin name.
    ft_at                  
} ft_state;
}

Name::Name(const std::string &namestring, bool downcase) {
    //
    // Initialize things to make the compiler happy; they're not required.
    //
    unsigned int digits = 0;
    unsigned int value = 0;
    unsigned int count = 0;

    //
    // Set up the state machine.
    //
    std::string::const_iterator s = namestring.begin();
    std::string::const_iterator send = namestring.end();
    bool done = false;
    bool is_root = false;
    ft_state state = ft_init;

    std::vector<unsigned char> offsets;
    offsets.reserve(Name::MAX_LABELS);
    offsets.push_back(0);

    std::string ndata;
    ndata.reserve(Name::MAX_WIRE);

    // should we refactor this code using, e.g, the state pattern?  Probably
    // not at this point, as this is based on proved code (derived from BIND9)
    // and it's less likely that we'll have more variations in the domain name
    // syntax.  If this ever happens next time, we should consider refactor
    // the code, rather than adding more states and cases below.
    while (ndata.size() < Name::MAX_WIRE && s != send && !done) {
        unsigned char c = *s++;

        switch (state) {
        case ft_init:
            //
            // Is this the root name?
            //
            if (c == '.') {
                if (s != send) {
                    isc_throw(EmptyLabel, "non terminating empty label");
                }
                is_root = true;
            } else if (c == '@' && s == send) {
                // handle a single '@' as the root name.
                is_root = true;
            }

            if (is_root) {
                ndata.push_back(0);
                done = true;
                break;
            }

            // FALLTHROUGH
        case ft_start:
            ndata.push_back(0); // placeholder for the label length field
            count = 0;
            if (c == '\\') {
                state = ft_initialescape;
                break;
            }
            state = ft_ordinary;
            assert(ndata.size() < Name::MAX_WIRE);
            // FALLTHROUGH
        case ft_ordinary:
            if (c == '.') {
                if (count == 0) {
                    isc_throw(EmptyLabel, "duplicate period");
                }
                ndata.at(offsets.back()) = count;
                offsets.push_back(ndata.size());
                if (s == send) {
                    ndata.push_back(0);
                    done = true;
                }
                state = ft_start;
            } else if (c == '\\') {
                state = ft_escape;
            } else {
                if (++count > MAX_LABELLEN) {
                    isc_throw(TooLongLabel, "label is too long");
                }
                ndata.push_back(downcase ? maptolower[c] : c);
            }
            break;
        case ft_initialescape:
            if (c == '[') {
                // This looks like a bitstring label, which was deprecated.
                // Intentionally drop it.
                isc_throw(BadLabelType, "invalid label type");
            }
            state = ft_escape;
            // FALLTHROUGH
        case ft_escape:
            if (!isdigit(c & 0xff)) {
                if (++count > MAX_LABELLEN) {
                    isc_throw(TooLongLabel, "label is too long");
                }
                ndata.push_back(downcase ? maptolower[c] : c);
                state = ft_ordinary;
                break;
            }
            digits = 0;
            value = 0;
            state = ft_escdecimal;
            // FALLTHROUGH
        case ft_escdecimal:
            if (!isdigit(c & 0xff)) {
                isc_throw(BadEscape, "mixture of escaped digit and non-digit");
            }
            value *= 10;
            value += digitvalue[c];
            digits++;
            if (digits == 3) {
                if (value > 255) {
                    isc_throw(BadEscape, "escaped decimal is too large");
                }
                if (++count > MAX_LABELLEN) {
                    isc_throw(TooLongLabel, "label is too long");
                }
                ndata.push_back(downcase ? maptolower[value] : value);
                state = ft_ordinary;
            }
            break;
        default:
            // impossible case
            assert(false);
        }
    }

    if (!done) {                // no trailing '.' was found.
        if (ndata.size() == Name::MAX_WIRE) {
            isc_throw(TooLongName, "name is too long for termination");
        }
        assert(s == send);
        if (state != ft_ordinary && state != ft_at) {
            isc_throw(IncompleteName, "incomplete textual name");
        }
        if (state == ft_ordinary) {
            assert(count != 0);
            ndata.at(offsets.back()) = count;

            offsets.push_back(ndata.size());
            // add a trailing \0
            ndata.push_back('\0');
        }
    }

    labelcount_ = offsets.size();
    assert(labelcount_ > 0 && labelcount_ <= Name::MAX_LABELS);
    ndata_.assign(ndata.data(), ndata.size());
    length_ = ndata_.size();
    offsets_.assign(offsets.begin(), offsets.end());
}

namespace {
///
/// Wire-format name parser states.
///
typedef enum {
    fw_start = 0,               // beginning of a label
    fw_ordinary,                // inside an ordinary (non compressed) label
    fw_newcurrent               // beginning of a compression pointer
} fw_state;
}

Name::Name(InputBuffer& buffer, bool downcase) {
    std::vector<unsigned char> offsets;
    offsets.reserve(Name::MAX_LABELS);

    /*
     * Initialize things to make the compiler happy; they're not required.
     */
    unsigned int n = 0;

    //
    // Set up.
    //
    bool done = false;
    unsigned int nused = 0;
    bool seen_pointer = false;
    fw_state state = fw_start;

    unsigned int cused = 0;     // Bytes of compressed name data used
    unsigned int current = buffer.getPosition();
    unsigned int pos_begin = current;
    unsigned int biggest_pointer = current;

    // Make the compiler happy; this is not required.
    // XXX: bad style in that we initialize it with a dummy value and define
    // it far from where it's used.  But alternatives seemed even worse.
    unsigned int new_current = 0;

    //
    // Note:  The following code is not optimized for speed, but
    // rather for correctness.  Speed will be addressed in the future.
    //
    while (current < buffer.getLength() && !done) {
        unsigned int c = buffer.readUint8();
        current++;
        if (!seen_pointer) {
            cused++;
        }

        switch (state) {
        case fw_start:
            if (c <= MAX_LABELLEN) {
                offsets.push_back(nused);
                if (nused + c + 1 > Name::MAX_WIRE) {
                    isc_throw(DNSMessageFORMERR, "wire name is too long: "
                              << nused + c + 1 << " bytes");
                }
                nused += c + 1;
                ndata_.push_back(c);
                if (c == 0) {
                    done = true;
                }
                n = c;
                state = fw_ordinary;
            } else if ((c & COMPRESS_POINTER_MARK8) == COMPRESS_POINTER_MARK8) {
                //
                // Ordinary 14-bit pointer.
                //
                new_current = c & ~COMPRESS_POINTER_MARK8;
                n = 1;
                state = fw_newcurrent;
            } else {
                // this case includes local compression pointer, which hasn't
                // been standardized.
                isc_throw(DNSMessageFORMERR, "unknown label character: " << c);
            }
            break;
        case fw_ordinary:
            if (downcase) {
                c = maptolower[c];
            }
            ndata_.push_back(c);
            if (--n == 0) {
                state = fw_start;
            }
            break;
        case fw_newcurrent:
            new_current *= 256;
            new_current += c;
            if (--n != 0) {
                break;
            }
            if (new_current >= biggest_pointer) {
                isc_throw(DNSMessageFORMERR,
                          "bad compression pointer (out of range): " <<
                          new_current);
            }
            biggest_pointer = new_current;
            current = new_current;
            buffer.setPosition(current);
            seen_pointer = true;
            state = fw_start;
            break;
        default:
            assert(false);
        }
    }

    if (!done) {
        isc_throw(DNSMessageFORMERR, "incomplete wire-format name");
    }

    labelcount_ = offsets.size();
    length_ = nused;
    offsets_.assign(offsets.begin(), offsets.end());
    buffer.setPosition(pos_begin + cused);
}

void
Name::toWire(OutputBuffer& buffer) const {
    buffer.writeData(ndata_.data(), ndata_.size());
}

void
Name::toWire(MessageRenderer& renderer) const {
    renderer.writeName(*this);
}

std::string
Name::toText(bool omit_final_dot) const {
    if (length_ == 1) {
        //
        // Special handling for the root label.  We ignore omit_final_dot.
        //
        assert(labelcount_ == 1 && ndata_[0] == '\0');
        return (".");
    }

    std::string::const_iterator np = ndata_.begin();
    std::string::const_iterator np_end = ndata_.end();
    unsigned int labels = labelcount_; // use for integrity check
    // init with an impossible value to catch error cases in the end:
    unsigned int count = MAX_LABELLEN + 1;

    // result string: it will roughly have the same length as the wire format
    // name data.  reserve that length to minimize reallocation.
    std::string result;
    result.reserve(length_);

    while (np != np_end) {
        labels--;
        count = *np++;

        if (count == 0) {
            if (!omit_final_dot) {
                result.push_back('.');
            }
            break;
        }
            
        if (count <= MAX_LABELLEN) {
            assert(np_end - np >= count);

            if (!result.empty()) {
                // just after a non-empty label.  add a separating dot.
                result.push_back('.');
            }

            while (count-- > 0) {
                unsigned char c = *np++;
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

    assert(labels == 0);
    assert(count == 0);         // a valid name must end with a 'dot'.

    return (result);
}

NameComparisonResult
Name::compare(const Name& other) const {
    // Determine the relative ordering under the DNSSEC order relation of
    // 'this' and 'other', and also determine the hierarchical relationship
    // of the names.

    unsigned int nlabels = 0;
    unsigned int l1 = labelcount_;
    unsigned int l2 = other.labelcount_;
    int ldiff = (int)l1 - (int)l2;
    unsigned int l = (ldiff < 0) ? l1 : l2;

    while (l > 0) {
        --l;
        --l1;
        --l2;
        size_t pos1 = offsets_[l1];
        size_t pos2 = other.offsets_[l2];
        unsigned int count1 = ndata_[pos1++];
        unsigned int count2 = other.ndata_[pos2++];

        // We don't support any extended label types including now-obsolete
        // bitstring labels.
        assert(count1 <= MAX_LABELLEN && count2 <= MAX_LABELLEN);

        int cdiff = (int)count1 - (int)count2;
        unsigned int count = (cdiff < 0) ? count1 : count2;

        while (count > 0) {
            unsigned char label1 = ndata_[pos1];
            unsigned char label2 = other.ndata_[pos2];

            int chdiff = (int)maptolower[label1] - (int)maptolower[label2];
            if (chdiff != 0) {
                return (NameComparisonResult(chdiff, nlabels,
                                         NameComparisonResult::COMMONANCESTOR));
            }
            --count;
            ++pos1;
            ++pos2;
        }
        if (cdiff != 0) {
                return (NameComparisonResult(cdiff, nlabels,
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

bool
Name::equals(const Name& other) const {
    if (length_ != other.length_ || labelcount_ != other.labelcount_) {
        return (false);
    }

    for (unsigned int l = labelcount_, pos = 0; l > 0; --l) {
        unsigned char count = ndata_[pos];
        if (count != other.ndata_[pos]) {
            return (false);
        }
        ++pos;

        while (count-- > 0) {
            unsigned char label1 = ndata_[pos];
            unsigned char label2 = other.ndata_[pos];

            if (maptolower[label1] != maptolower[label2]) {
                return (false);
            }
            ++pos;
        }
    }

    return (true);
}

bool
Name::leq(const Name& other) const {
    return (compare(other).getOrder() <= 0);
}

bool
Name::geq(const Name& other) const {
    return (compare(other).getOrder() >= 0);
}

bool
Name::lthan(const Name& other) const {
    return (compare(other).getOrder() < 0);
}

bool
Name::gthan(const Name& other) const {
    return (compare(other).getOrder() > 0);
}

bool
Name::isWildcard() const {
    return (length_ >= 2 && ndata_[0] == 1 && ndata_[1] == '*'); 
}

Name
Name::concatenate(const Name& suffix) const {
    assert(length_ > 0 && suffix.length_ > 0);
    assert(labelcount_ > 0 && suffix.labelcount_ > 0);

    unsigned int length = length_ + suffix.length_ - 1;
    if (length > Name::MAX_WIRE) {
        isc_throw(TooLongName, "names are too long to concatenate");
    }

    Name retname;
    retname.ndata_.reserve(length);
    retname.ndata_.assign(ndata_, 0, length_ - 1);
    retname.ndata_.insert(retname.ndata_.end(),
                          suffix.ndata_.begin(), suffix.ndata_.end());
    assert(retname.ndata_.size() == length);
    retname.length_ = length;

    //
    // Setup the offsets vector.  Copy the offsets of this (prefix) name,
    // excluding that for the trailing dot, and append the offsets of the
    // suffix name with the additional offset of the length of the prefix.
    //
    unsigned int labels = labelcount_ + suffix.labelcount_ - 1;
    assert(labels <= Name::MAX_LABELS);
    retname.offsets_.reserve(labels);
    retname.offsets_.assign(&offsets_[0], &offsets_[0] + labelcount_ - 1);
    transform(suffix.offsets_.begin(), suffix.offsets_.end(),
              back_inserter(retname.offsets_),
              bind2nd(plus<char>(), length_ - 1));
    assert(retname.offsets_.size() == labels);
    retname.labelcount_ = labels;

    return (retname);
}

Name
Name::reverse() const {
    Name retname;
    //
    // Set up offsets: The size of the string and number of labels will
    // be the same in as in the original.
    //
    retname.offsets_.reserve(labelcount_);
    retname.ndata_.reserve(length_);

    // Copy the original name, label by label, from tail to head.
    vector<unsigned char>::const_reverse_iterator rit0 = offsets_.rbegin();
    vector<unsigned char>::const_reverse_iterator rit1 = rit0 + 1;
    string::const_iterator n0 = ndata_.begin();
    retname.offsets_.push_back(0);
    while (rit1 != offsets_.rend()) {
        retname.ndata_.append(n0 + *rit1, n0 + *rit0);
        retname.offsets_.push_back(retname.ndata_.size());
        ++rit0;
        ++rit1;
    }
    retname.ndata_.push_back(0);

    retname.labelcount_ = labelcount_;
    retname.length_ = length_;

    return (retname);
}

Name
Name::split(const unsigned int first, const unsigned int n) const {
    if (n == 0 || n > labelcount_ || first > labelcount_ - n) {
        isc_throw(OutOfRange, "Name::split: invalid split range");
    }

    Name retname;
    // If the specified range doesn't include the trailing dot, we need one
    // more label for that.
    unsigned int newlabels = (first + n == labelcount_) ? n : n + 1;

    //
    // Set up offsets: copy the corresponding range of the original offsets
    // with subtracting an offset of the prefix length.
    //
    retname.offsets_.reserve(newlabels);
    transform(offsets_.begin() + first, offsets_.begin() + first + newlabels,
              back_inserter(retname.offsets_),
              bind2nd(plus<char>(), -offsets_[first]));

    //
    // Set up the new name.  At this point the tail of the new offsets specifies
    // the position of the trailing dot, which should be equal to the length of
    // the extracted portion excluding the dot.  First copy that part from the
    // original name, and append the trailing dot explicitly.
    //
    retname.ndata_.reserve(retname.offsets_.back() + 1);
    retname.ndata_.assign(ndata_, offsets_[first], retname.offsets_.back());
    retname.ndata_.push_back(0);

    retname.length_ = retname.ndata_.size();
    retname.labelcount_ = retname.offsets_.size();
    assert(retname.labelcount_ == newlabels);

    return (retname);
}

Name
Name::split(const unsigned level) const {
    if (level >= getLabelCount()) {
        isc_throw(OutOfRange, "invalid level for name split (" << level
                  << ") for name " << *this);
    }

    return (split(level, getLabelCount() - level));
}

Name&
Name::downcase() {
    unsigned int nlen = length_;
    unsigned int labels = labelcount_;
    unsigned int pos = 0;

    while (labels > 0 && nlen > 0) {
        --labels;
        --nlen;

        // we assume a valid name, and do abort() if the assumption fails
        // rather than throwing an exception.
        unsigned int count = ndata_.at(pos++);
        assert(count <= MAX_LABELLEN);
        assert(nlen >= count);

        while (count > 0) {
            ndata_.at(pos) =
                maptolower[static_cast<unsigned char>(ndata_.at(pos))];
            ++pos;
            --nlen;
            --count;
        }
    }

    return (*this);
}

std::ostream&
operator<<(std::ostream& os, const Name& name) {
    os << name.toText();
    return (os);
}
}
}
