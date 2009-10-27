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

#include <stdexcept>

#include <dns/buffer.h>
#include <dns/name.h>

using namespace std;
using namespace ISC::DNS;

typedef enum {
    ft_init = 0,
    ft_start,
    ft_ordinary,
    ft_initialescape,
    ft_escape,
    ft_escdecimal,
    ft_at
} ft_state;

typedef enum {
    fw_start = 0,
    fw_ordinary,
    fw_copy,
    fw_newcurrent
} fw_state;

static char digitvalue[256] = {
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, // 16
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, /*32*/
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, /*48*/
    0,  1,  2,  3,  4,  5,  6,  7,  8,  9, -1, -1, -1, -1, -1, -1, /*64*/
    -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, /*80*/
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, /*96*/
    -1, 10, 11, 12, 13, 14, 15, -1, -1, -1, -1, -1, -1, -1, -1, -1, /*112*/
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, /*128*/
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1,
    -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, -1, /*256*/
};

static unsigned char maptolower[] = {
    0x00, 0x01, 0x02, 0x03, 0x04, 0x05, 0x06, 0x07,
    0x08, 0x09, 0x0a, 0x0b, 0x0c, 0x0d, 0x0e, 0x0f,
    0x10, 0x11, 0x12, 0x13, 0x14, 0x15, 0x16, 0x17,
    0x18, 0x19, 0x1a, 0x1b, 0x1c, 0x1d, 0x1e, 0x1f,
    0x20, 0x21, 0x22, 0x23, 0x24, 0x25, 0x26, 0x27,
    0x28, 0x29, 0x2a, 0x2b, 0x2c, 0x2d, 0x2e, 0x2f,
    0x30, 0x31, 0x32, 0x33, 0x34, 0x35, 0x36, 0x37,
    0x38, 0x39, 0x3a, 0x3b, 0x3c, 0x3d, 0x3e, 0x3f,
    0x40, 0x61, 0x62, 0x63, 0x64, 0x65, 0x66, 0x67,
    0x68, 0x69, 0x6a, 0x6b, 0x6c, 0x6d, 0x6e, 0x6f,
    0x70, 0x71, 0x72, 0x73, 0x74, 0x75, 0x76, 0x77,
    0x78, 0x79, 0x7a, 0x5b, 0x5c, 0x5d, 0x5e, 0x5f,
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

Name::Name(const std::string& namestr)
    : length_(0), labels_(0)
{
    char c;
    ft_state state;
    unsigned int value, count, pos, lpos;
    unsigned int n1, n2, tlen, nrem, nused, digits, labels, tused;
    bool done;

    offsets_.reserve(128);
    offsets_[0] = 0;

    //
    // Initialize things to make the compiler happy; they're not required.
    //
    n1 = 0;
    n2 = 0;
    digits = 0;
    value = 0;
    count = 0;

    //
    // Set up the state machine.
    //
    pos = 0;
    tlen = namestr.length();
    tused = 0;
    nrem = 255;
    nused = 0;
    labels = 0;
    done = false;
    state = ft_init;

    while (nrem > 0 && tlen > 0 && !done) {
        c = namestr[pos++];
        tlen--;
        tused++;

        switch (state) {
        case ft_init:
            /*
             * Is this the root name?
             */
            if (c == '.') {
                if (tlen != 0)
                    throw DNSEmptyLabel();
                labels++;
                ndata_.push_back(0);
                nrem--;
                nused++;
                done = true;
                break;
            }
            if (c == '@' && tlen == 0) {
                state = ft_at;
                break;
            }

            /* FALLTHROUGH */
        case ft_start:
            ndata_.push_back(0); // dummy data
            nrem--;
            lpos = nused;
            nused++;
            count = 0;
            if (c == '\\') {
                state = ft_initialescape;
                break;
            }
            state = ft_ordinary;
            if (nrem == 0)
                throw ISCNoSpace();
            /* FALLTHROUGH */
        case ft_ordinary:
            if (c == '.') {
                if (count == 0)
                    throw DNSEmptyLabel();
                ndata_[lpos] = count;
                labels++;
                //INSIST(labels <= 127);
                offsets_[labels] = nused;
                if (tlen == 0) {
                    labels++;
                    ndata_.push_back(0);
                    nrem--;
                    nused++;
                    done = true;
                }
                state = ft_start;
            } else if (c == '\\') {
                state = ft_escape;
            } else {
                if (count >= 63)
                    throw DNSLabelTooLong();
                count++;
                ndata_.push_back(c);
                nrem--;
                nused++;
            }
            break;
        case ft_initialescape:
            if (c == '[') {
                /*
                 * This looks like a bitstring label, which
                 * was deprecated.  Intentionally drop it.
                 */
                throw DNSBadLabelType();
            }
            state = ft_escape;
            /* FALLTHROUGH */
        case ft_escape:
            if (!isdigit(c & 0xff)) {
                if (count >= 63)
                    throw DNSLabelTooLong();
                count++;
                ndata_.push_back(c);
                nrem--;
                nused++;
                state = ft_ordinary;
                break;
            }
            digits = 0;
            value = 0;
            state = ft_escdecimal;
            /* FALLTHROUGH */
        case ft_escdecimal:
            if (!isdigit(c & 0xff))
                throw DNSBadEscape();
            value *= 10;
            value += digitvalue[(int)c];
            digits++;
            if (digits == 3) {
                if (value > 255)
                    throw DNSBadEscape();
                if (count >= 63)
                    throw DNSLabelTooLong();
                count++;
                ndata_.push_back(value);
                nrem--;
                nused++;
                state = ft_ordinary;
            }
            break;
        default:
            throw runtime_error("Unexpected state " + state);
        }
    }

    if (!done) {
        if (nrem == 0)
            throw ISCNoSpace();
        //INSIST(tlen == 0);
        if (state != ft_ordinary && state != ft_at)
            throw runtime_error("Unexpected state " + state);
        if (state == ft_ordinary) {
            //INSIST(count != 0);
            ndata_[lpos] = count;
            labels++;
            //INSIST(labels <= 127);
            offsets_[labels] = nused;

            // added a trailing \0
            ndata_.push_back('\0');
            ++labels;
            ++nused;
            offsets_[labels] = nused;
        }
    }

    labels_ = labels;
    length_ = nused;
}

Name::Name(Buffer& buffer, NameDecompressor& decompressor)
{
    unsigned int nused, labels, n, nmax;
    unsigned int current;
    bool done;
    fw_state state = fw_start;
    unsigned int c;
    bool downcase;
    bool seen_pointer;

    /*
     * Initialize things to make the compiler happy; they're not required.
     */
    n = 0;

    /*
     * Set up.
     */
    labels = 0;
    done = false;
    nused = 0;

    /*
     * Find the maximum number of uncompressed target name
     * bytes we are willing to generate.  This is the smaller
     * of the available target buffer length and the
     * maximum legal domain name length (255).
     */
    nmax = MAXWIRE;

    current = buffer.get_current();

    /*
     * Note:  The following code is not optimized for speed, but
     * rather for correctness.  Speed will be addressed in the future.
     */
    while (current < buffer.get_size() && !done) {
        c = buffer.read_uint8();
        current++;

        switch (state) {
        case fw_start:
            if (c < 64) {
                offsets_.push_back(nused);
                labels++;
                if (nused + c + 1 > nmax)
                full:
                    // The name did not fit even though we had a buffer
                    // big enough to fit a maximum-length name.
                    throw DNSNameTooLong();
                nused += c + 1;
                ndata_.push_back(c);
                if (c == 0)
                    done = true;
                n = c;
                state = fw_ordinary;
            } else if (c >= 128 && c < 192) {
                /*
                 * 14 bit local compression pointer.
                 * Local compression is no longer an
                 * IETF draft.
                 */
                throw DNSBadLabelType();
            } else if (c >= 192) {
                /*
                 * Ordinary 14-bit pointer.
                 */
                throw DNSBadLabelType(); // XXX not implemented
            } else
                throw DNSBadLabelType();
            break;
        case fw_ordinary:
            if (downcase)
                c = maptolower[c];
            /* FALLTHROUGH */
        case fw_copy:
            ndata_.push_back(c);
            n--;
            if (n == 0)
                state = fw_start;
            break;
        case fw_newcurrent:
            // XXX not implemented, fall through
        default:
            throw ISCUnexpected();
        }
    }

    if (!done)
        throw ISCUnexpected();

    labels_ = labels;
    length_ = nused;
}

string
Name::to_text(bool omit_final_dot) const
{
    string tdata;
    unsigned int nlen;
    unsigned char c;
    unsigned int count;
    unsigned int labels;
    bool saw_root = false;
    string::const_iterator iter_ndata;

    /*
     * This function assumes the name is in proper uncompressed
     * wire format.
     */
    iter_ndata = ndata_.begin();
    nlen = length_;
    labels = labels_;

    if (labels == 0 && nlen == 0) {
        /*
         * Special handling for an empty name.
         */

        /*
         * The names of these booleans are misleading in this case.
         * This empty name is not necessarily from the root node of
         * the DNS root zone, nor is a final dot going to be included.
         * They need to be set this way, though, to keep the "@"
         * from being trounced.
         */
        saw_root = true;
        omit_final_dot = false;
        tdata.push_back('@');

        /*
         * Skip the while() loop.
         */
        nlen = 0;
    } else if (nlen == 1 && labels == 1 && *iter_ndata == '\0') {
        /*
         * Special handling for the root label.
         */
        saw_root = true;
        omit_final_dot = false;
        tdata.push_back('.');

        /*
         * Skip the while() loop.
         */
        nlen = 0;
    }

    while (labels > 0 && nlen > 0) {
        labels--;
        count = *iter_ndata++;
        nlen--;
        if (count == 0) {
            saw_root = true;
            break;
        }
        if (count < 64) {
            //INSIST(nlen >= count);
            while (count > 0) {
                c = *iter_ndata;
                switch (c) {
                case 0x22: /* '"' */
                case 0x28: /* '(' */
                case 0x29: /* ')' */
                case 0x2E: /* '.' */
                case 0x3B: /* ';' */
                case 0x5C: /* '\\' */
                    /* Special modifiers in zone files. */
                case 0x40: /* '@' */
                case 0x24: /* '$' */
                    tdata.push_back('\\');
                    tdata.push_back(c);
                    iter_ndata++;
                    nlen--;
                    break;
                default:
                    if (c > 0x20 && c < 0x7f) {
                        tdata.push_back(c);
                        iter_ndata++;
                        nlen--;
                    } else {
                        tdata.push_back(0x5c);
                        tdata.push_back(0x30 + ((c / 100) % 10));
                        tdata.push_back(0x30 + ((c / 10) % 10));
                        tdata.push_back(0x30 + (c % 10));
                        iter_ndata++;
                        nlen--;
                    }
                }
                count--;
            }
        } else
            throw runtime_error("Unexpected label type " + count);
        // The following assumes names are absolute.  If not, we
        // fix things up later.  Note that this means that in some
        // cases one more byte of text buffer is required than is
        // needed in the final output.
        tdata.push_back('.');
    }

    if (nlen != 0)
        throw ISCNoSpace();

    if (!saw_root || omit_final_dot)
        tdata.erase(tdata.end() - 1);

    return (tdata);
}

void
Name::to_wire(Buffer& buffer, NameCompressor& c) const
{
    // TBD: very simple version for prototyping; e.g. it omits compression.
    buffer.write_data(ndata_.c_str(), ndata_.size());
}

// Are 'this' name and 'other' equal?
bool
Name::equals(const Name& other) const
{
    unsigned int l;
    unsigned char c, count;
    string::const_iterator label1, label2;

    if (length_ != other.length_)
        return (false);

    l = labels_;

    if (l != other.labels_)
        return (false);

    label1 = ndata_.begin();
    label2 = other.ndata_.begin();
    while (l > 0) {
        l--;
        count = *label1++;
        if (count != *label2++)
            return (false);

        while (count > 0) {
            count--;
            c = maptolower[(unsigned char)*label1++]; // XXX should avoid cast
            if (c != maptolower[(unsigned char)*label2++])
                return (false);
        }
    }

    return (true);
}

ostream&
operator<<(ostream& os, const Name& name)
{
    os << name.to_text();
    return (os);
}
