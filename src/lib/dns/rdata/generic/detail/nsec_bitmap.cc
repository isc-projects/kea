// Copyright (C) 2011-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <exceptions/exceptions.h>

#include <dns/exceptions.h>
#include <dns/rdata.h>
#include <dns/rrtype.h>

#include <cassert>
#include <sstream>
#include <vector>
#include <cstring>
#include <stdint.h>

using namespace std;

namespace isc {
namespace dns {
namespace rdata {
namespace generic {
namespace detail {
namespace nsec {
void
checkRRTypeBitmaps(const char* const rrtype_name,
                   const vector<uint8_t>& typebits)
{
    bool first = true;
    unsigned int lastblock = 0;
    const size_t total_len = typebits.size();
    size_t i = 0;

    while (i < total_len) {
        if (i + 2 > total_len) {
            isc_throw(DNSMessageFORMERR, rrtype_name <<
                      " RDATA from wire: incomplete bit map field");
        }
        const unsigned int block = typebits[i];
        const size_t len = typebits[i + 1];
        // Check that bitmap window blocks are in the correct order.
        if (!first && block <= lastblock) {
            isc_throw(DNSMessageFORMERR, rrtype_name <<
                      " RDATA from wire: Disordered window blocks found: "
                      << lastblock << " then " << block);
        }
        // Check for legal length
        if (len < 1 || len > 32) {
            isc_throw(DNSMessageFORMERR, rrtype_name <<
                      " RDATA from wire: Invalid bitmap length: " << len);
        }
        // Check for overflow.
        i += 2;
        if (i + len > total_len) {
            isc_throw(DNSMessageFORMERR, rrtype_name <<
                      " RDATA from wire: bitmap length too large: " << len);
        }
        // The last octet of the bitmap must be non zero.
        if (typebits[i + len - 1] == 0) {
            isc_throw(DNSMessageFORMERR, rrtype_name <<
                      " RDATA from wire: bitmap ending an all-zero byte");
        }

        i += len;
        lastblock = block;
        first = false;
    }
}

void
buildBitmapsFromLexer(const char* const rrtype_name,
                      MasterLexer& lexer, vector<uint8_t>& typebits,
                      bool allow_empty)
{
    uint8_t bitmap[8 * 1024];       // 64k bits
    memset(bitmap, 0, sizeof(bitmap));

    bool have_rrtypes = false;
    std::string type_str;
    while (true) {
        const MasterToken& token =
            lexer.getNextToken(MasterToken::STRING, true);
        if ((token.getType() == MasterToken::END_OF_FILE) ||
            (token.getType() == MasterToken::END_OF_LINE)) {
            break;
        }

        // token is now assured to be of type STRING.

        have_rrtypes = true;
        token.getString(type_str);
        try {
            const int code = RRType(type_str).getCode();
            bitmap[code / 8] |= (0x80 >> (code % 8));
        } catch (const InvalidRRType&) {
            isc_throw(InvalidRdataText, "Invalid RRtype in "
                      << rrtype_name << " bitmap: " << type_str);
        }
    }

    lexer.ungetToken();

    if (!have_rrtypes) {
         if (allow_empty) {
              return;
         }
         isc_throw(InvalidRdataText,
                   rrtype_name <<
                   " record does not end with RR type mnemonic");
    }

    for (int window = 0; window < 256; ++window) {
        int octet;
        for (octet = 31; octet >= 0; octet--) {
            if (bitmap[window * 32 + octet] != 0) {
                break;
            }
        }
        if (octet < 0) {
            continue;
        }
        typebits.push_back(window);
        typebits.push_back(octet + 1);
        for (int i = 0; i <= octet; ++i) {
            typebits.push_back(bitmap[window * 32 + i]);
        }
    }
}

void
bitmapsToText(const vector<uint8_t>& typebits, ostringstream& oss) {
    // In the following loop we use string::at() rather than operator[].
    // Since the index calculation is a bit complicated, it will be safer
    // and easier to find a bug (if any).  Note that this conversion method
    // is generally not expected to be very efficient, so the slight overhead
    // of at() should be acceptable.
    const size_t typebits_len = typebits.size();
    size_t len = 0;
    for (size_t i = 0; i < typebits_len; i += len) {
        assert(i + 2 <= typebits.size());
        const unsigned int block = typebits.at(i);
        len = typebits.at(i + 1);
        assert(len > 0 && len <= 32);
        i += 2;
        for (size_t j = 0; j < len; ++j) {
            if (typebits.at(i + j) == 0) {
                continue;
            }
            for (size_t k = 0; k < 8; ++k) {
                if ((typebits.at(i + j) & (0x80 >> k)) == 0) {
                    continue;
                }
                const unsigned int t = block * 256 + j * 8 + k;
                assert(t < 65536);
                oss << " " << RRType(t);
            }
        }
    }
}
}
}
}
}
}
}
