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

// $Id$

#include <stdint.h>
#include <cassert>
#include <iterator>
#include <string>
#include <vector>

#include <boost/archive/iterators/base64_from_binary.hpp>
#include <boost/archive/iterators/binary_from_base64.hpp>
#include <boost/archive/iterators/transform_width.hpp>

#include "base64.h"
#include <exceptions/exceptions.h>

using namespace std;
using namespace boost::archive::iterators;

namespace isc {
namespace dns {

namespace {
const char BASE64_PADDING_CHAR = '=';
const uint8_t BINARY_ZERO_CODE = 0;
  
class BinaryNormalizer : public iterator<input_iterator_tag, uint8_t> {
public:
    BinaryNormalizer(const vector<uint8_t>::const_iterator& base,
                     const vector<uint8_t>::const_iterator& base_end) :
        base_(base), base_end_(base_end), in_pad_(false)
    {}
    BinaryNormalizer& operator++()
    {
        if (!in_pad_) {
            ++base_;
        }
        if (base_ == base_end_) {
            in_pad_ = true;
        }
        return (*this);
    }
    const uint8_t& operator*() const {
        if (in_pad_) {
            return (BINARY_ZERO_CODE);
        } else {
            return (*base_);
        }
    }
    bool operator==(const BinaryNormalizer& other) const
    {
        return (base_ == other.base_);
    }
private:
    vector<uint8_t>::const_iterator base_;
    const vector<uint8_t>::const_iterator base_end_;
    bool in_pad_;
};

typedef
base64_from_binary<transform_width<BinaryNormalizer, 6, 8> > base64_encoder;
} // end of anonymous namespace

string
encodeBase64(const vector<uint8_t>& binary)
{
    // calculate the resulting length.  it's the smallest multiple of 4
    // equal to or larger than 4/3 * original data length.
    size_t len = ((binary.size() * 4 / 3) + 3) & ~3;

    string base64;
    base64.reserve(len);
    base64.assign(base64_encoder(BinaryNormalizer(binary.begin(),
                                                  binary.end())),
                  base64_encoder(BinaryNormalizer(binary.end(), binary.end())));
    assert(len >= base64.length());
    base64.append(len - base64.length(), BASE64_PADDING_CHAR);
    return (base64);
}

namespace {
const size_t BASE64_MAX_PADDING_CHARS = 2;
const char BASE64_ZERO_CODE = 'A'; // correspond to 000000(2)

class Base64Normalizer : public iterator<input_iterator_tag, char> {
public:
    Base64Normalizer(const string::const_iterator& base,
                     const string::const_iterator& base_beginpad,
                     const string::const_iterator& base_end) :
        base_(base), base_beginpad_(base_beginpad), base_end_(base_end),
        in_pad_(false)
    {}
    Base64Normalizer& operator++()
    {
        ++base_;
        while (base_ != base_end_ && isspace(*base_)) {
            ++base_;
        }
        if (base_ == base_beginpad_) {
            in_pad_ = true;
        }
        return (*this);
    }
    const char operator*() const {
        if (in_pad_ && *base_ == BASE64_PADDING_CHAR) {
            return (BASE64_ZERO_CODE);
        } else {
            return (*base_);
        }
    }
    bool operator==(const Base64Normalizer& other) const
    {
        return (base_ == other.base_);
    }
private:
    string::const_iterator base_;
    const string::const_iterator base_beginpad_;
    const string::const_iterator base_end_;
    bool in_pad_;
};

typedef
transform_width<binary_from_base64<Base64Normalizer, char>, 8, 6, char>
base64_decoder;
} // end of anonymous namespace

void
decodeBase64(const string& base64, vector<uint8_t>& result)
{
    // enumerate the number of trailing padding characters (=), ignoring
    // white spaces.  since base64_from_binary doesn't accept padding,
    // we handle it explicitly.
    size_t padlen = 0;
    string::const_reverse_iterator srit = base64.rbegin();
    string::const_reverse_iterator srit_end = base64.rend();
    while (srit != srit_end) {
        char ch = *srit;
        if (ch == BASE64_PADDING_CHAR) {
            if (++padlen > BASE64_MAX_PADDING_CHARS) {
                dns_throw(BadBase64String,
                          "Too many Base64 padding characters");
            }
        } else if (!isspace(ch)) {
            break;
        }
        ++srit;
    }

    try {
        result.assign(base64_decoder(Base64Normalizer(base64.begin(),
                                                      srit.base(),
                                                      base64.end())),
                      base64_decoder(Base64Normalizer(base64.end(),
                                                      base64.end(),
                                                      base64.end())));
    } catch (dataflow_exception& ex) {
        dns_throw(BadBase64String, ex.what());
    }

    // Confirm the original base64 text is the canonical encoding of the
    // data.
    assert(result.size() >= padlen);
    vector<uint8_t>::const_reverse_iterator rit = result.rbegin();
    for (int i = 0; i < padlen; ++i, ++rit) {
        if (*rit != 0) {
            dns_throw(BadBase64String, "Non 0 bits included in padding");
        }
    }

    // strip the padded zero-bit fields
    result.resize(result.size() - padlen);
}

}
}
