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

#include "buffer.h"
#include "name.h"
#include "messagerenderer.h"

using namespace isc::dns;

using isc::dns::NameComparisonResult;
using isc::dns::MessageRenderer;

namespace isc {
namespace dns {

namespace {
///
/// These are shortcut arrays for efficient character conversion.
/// digitvalue converts a digit character to the corresponding integer.
/// maptolower convert uppercase alphabets to their lowercase counterparts.
/// A helper class and its only instance will initialize the arrays at startup
/// time.
///
static char digitvalue[256];
static unsigned char maptolower[256];

class Initializer {
public:
    Initializer()
    {
        for (unsigned int i = 0; i < 256; i++) {
            if (i >= '0' && i<= '9') {
                digitvalue[i] = i - '0';
            } else {
                digitvalue[i] = -1;
            }
        }
        for (unsigned int i = 0; i < 256; i++) {
            if (i >= 'A' && i <= 'Z') {
                maptolower[i] = i - ('A' - 'a');
            } else {
                maptolower[i] = i;
            }
        }
    }
};
/// This object is defined only to call its constructor.
static Initializer initialier; 
}

typedef enum {
    ft_init = 0,
    ft_start,
    ft_ordinary,
    ft_initialescape,
    ft_escape,
    ft_escdecimal,
    ft_at
} ft_state;

Name::Name(const std::string &namestring, bool downcase)
{
    char c;
    std::vector<char> offsets;
    offsets.reserve(128);
    offsets.push_back(0);

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

    // should we refactor this code using, e.g, the state pattern?  Probably
    // not at this point, as this is based on proved code (derived from BIND9)
    // and it's less likely that we'll have more variations in the domain name
    // syntax.  If this ever happens next time, we should consider refactor
    // the code, rather than adding more states and cases below.
    while (ndata_.size() < Name::MAX_WIRE && s != send && !done) {
        c = *s++;

        switch (state) {
        case ft_init:
            //
            // Is this the root name?
            //
            if (c == '.') {
                if (s != send) {
                    dns_throw(EmptyLabel, "non terminating empty label");
                }
                is_root = true;
            } else if (c == '@' && s == send) {
                // handle a single '@' as the root name.
                is_root = true;
            }

            if (is_root) {
                ndata_.push_back(0);
                done = true;
                break;
            }

            // FALLTHROUGH
        case ft_start:           // begin of a label
            ndata_.push_back(0); // placeholder for the label length field
            count = 0;
            if (c == '\\') {
                state = ft_initialescape;
                break;
            }
            state = ft_ordinary;
            assert(ndata_.size() < Name::MAX_WIRE);
            // FALLTHROUGH
        case ft_ordinary:       // parsing a normal label
            if (c == '.') {
                if (count == 0) {
                    dns_throw(EmptyLabel, "duplicate period");
                }
                ndata_[offsets.back()] = count;
                offsets.push_back(ndata_.size());
                if (s == send) {
                    ndata_.push_back(0);
                    done = true;
                }
                state = ft_start;
            } else if (c == '\\') {
                state = ft_escape;
            } else {
                if (++count > Name::MAX_LABELLEN) {
                    dns_throw(TooLongLabel, "label is too long");
                }
                ndata_.push_back(downcase ? maptolower[c] : c);
            }
            break;
        case ft_initialescape:  // just found '\'
            if (c == '[') {
                // This looks like a bitstring label, which was deprecated.
                // Intentionally drop it.
                dns_throw(BadLabelType, "invalid label type");
            }
            state = ft_escape;
            // FALLTHROUGH
        case ft_escape:         // begin of handling a '\'-escaped sequence
            if (!isdigit(c & 0xff)) {
                if (++count > Name::MAX_LABELLEN) {
                    dns_throw(TooLongLabel, "label is too long");
                }
                ndata_.push_back(downcase ? maptolower[c] : c);
                state = ft_ordinary;
                break;
            }
            digits = 0;
            value = 0;
            state = ft_escdecimal;
            // FALLTHROUGH
        case ft_escdecimal:     // parsing a '\DDD' octet.
            if (!isdigit(c & 0xff)) {
                dns_throw(BadEscape, "mixture of escaped digit and non-digit");
            }
            value *= 10;
            value += digitvalue[c];
            digits++;
            if (digits == 3) {
                if (value > 255) {
                    dns_throw(BadEscape, "escaped decimal is too large");
                }
                if (++count > Name::MAX_LABELLEN) {
                    dns_throw(TooLongLabel, "label is too long");
                }
                ndata_.push_back(downcase ? maptolower[value] : value);
                state = ft_ordinary;
            }
            break;
        default:
            // impossible case
            assert(false);
        }
    }

    if (!done) {                // no trailing '.' was found.
        if (ndata_.size() == Name::MAX_WIRE) {
            dns_throw(TooLongName, "name is too long for termination");
        }
        assert(s == send);
        if (state != ft_ordinary && state != ft_at) {
            dns_throw(BadLabelType, "incomplete label");
        }
        if (state == ft_ordinary) {
            assert(count != 0);
            ndata_[offsets.back()] = count;
            
            offsets.push_back(ndata_.size());
            // add a trailing \0
            ndata_.push_back('\0');
        }
    }

    labels_ = offsets.size();
    assert(labels_ <= 127);
    length_ = ndata_.size();
    offsets_.assign(offsets.begin(), offsets.end());
}

typedef enum {
    fw_start = 0,
    fw_ordinary,
    fw_newcurrent
} fw_state;

Name::Name(InputBuffer& buffer, bool downcase)
{
    unsigned int new_current;
    std::vector<char> offsets;
    offsets.reserve(128);

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
            if (c < 64) {
                offsets.push_back(nused);
                if (nused + c + 1 > Name::MAX_WIRE) {
                    dns_throw(TooLongName, "wire name is too long");
                }
                nused += c + 1;
                ndata_.push_back(c);
                if (c == 0) {
                    done = true;
                }
                n = c;
                state = fw_ordinary;
            } else if (c >= 192) {
                //
                // Ordinary 14-bit pointer.
                //
                new_current = c & 0x3F;
                n = 1;
                state = fw_newcurrent;
            } else {
                // this case includes local compression pointer, which hasn't
                // been standardized.
                dns_throw(BadLabelType, "unknown label character");
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
                dns_throw(BadPointer, "bad compression pointer: out of range");
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
        dns_throw(IncompleteName, "incomplete wire-format name");
    }

    labels_ = offsets.size();
    length_ = nused;
    offsets_.assign(offsets.begin(), offsets.end());
    buffer.setPosition(pos_begin + cused);
}

void
Name::toWire(OutputBuffer& buffer) const
{
    buffer.writeData(ndata_.data(), ndata_.size());
}

void
Name::toWire(MessageRenderer& renderer) const
{
    renderer.writeName(*this);
}

std::string
Name::toText(bool omit_final_dot) const
{
    if (length_ == 1) {
        //
        // Special handling for the root label.  We ignore omit_final_dot.
        //
        assert(labels_ == 1 && ndata_[0] == '\0');
        return (".");
    }

    unsigned int count;
    std::string::const_iterator np = ndata_.begin();
    std::string::const_iterator np_end = ndata_.end();
    unsigned int labels = labels_; // use for integrity check

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
            
        if (count <= Name::MAX_LABELLEN) {
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
            dns_throw(BadLabelType, "unknown label type in name data");
        }
    }

    assert(labels == 0);
    assert(count == 0);         // a valid name must end with a 'dot'.

    return (result);
}

NameComparisonResult
Name::compare(const Name& other) const
{
    unsigned int count1, count2, count;
    int cdiff, chdiff;
    unsigned char label1, label2;
    size_t pos1, pos2;
    NameComparisonResult::NameRelation namereln;

    // Determine the relative ordering under the DNSSEC order relation of
    // 'this' and 'other', and also determine the hierarchical relationship
    // of the names.

    unsigned int nlabels = 0;
    unsigned int l1 = labels_;
    unsigned int l2 = other.labels_;
    int ldiff = (int)l1 - (int)l2;
    unsigned int l = (ldiff < 0) ? l1 : l2;

    while (l > 0) {
        --l;
        --l1;
        --l2;
        pos1 = offsets_[l1];
        pos2 = other.offsets_[l2];
        count1 = ndata_[pos1++];
        count2 = other.ndata_[pos2++];
        label1 = ndata_[pos1];
        label2 = other.ndata_[pos2];

        // We don't support any extended label types including now-obsolete
        // bitstring labels.
        assert(count1 <= Name::MAX_LABELLEN && count2 <= Name::MAX_LABELLEN);

        cdiff = (int)count1 - (int)count2;
        if (cdiff < 0)
            count = count1;
        else
            count = count2;

        while (count > 0) {
            chdiff = (int)maptolower[label1] - (int)maptolower[label2];
            if (chdiff != 0) {
                return (NameComparisonResult(chdiff, nlabels,
                                         NameComparisonResult::COMMONANCESTOR));
            }
            --count;
            label1 = ndata_[++pos1];
            label2 = other.ndata_[++pos2];
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

// Are 'this' name and 'other' equal?
bool
Name::operator==(const Name& other) const
{
    unsigned int l;
    unsigned char c, count;
    std::string::const_iterator label1, label2;

    if (length_ != other.length_ || labels_ != other.labels_) {
        return (false);
    }

    l = labels_;
    label1 = ndata_.begin();
    label2 = other.ndata_.begin();
    while (l > 0) {
        l--;
        count = *label1++;
        if (count != *label2++) {
            return (false);
        }

        while (count-- > 0) {
            c = maptolower[(unsigned char)*label1++]; // XXX should avoid cast
            if (c != maptolower[(unsigned char)*label2++])
                return (false);
        }
    }

    return (true);
}

bool
Name::isWildcard() const
{
    return (length_ >= 2 && ndata_[0] == 1 && ndata_[1] == '*'); 
}

std::ostream&
operator<<(std::ostream& os, const Name& name)
{
    os << name.toText();
    return (os);
}

}
}
