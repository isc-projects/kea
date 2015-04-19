// Copyright (C) 2012, 2015 Internet Systems Consortium, Inc. ("ISC")
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

#define KEA_DNS_EXPORT

#include <exceptions/exceptions.h>

#include <util/encode/hex.h>
#include <util/buffer.h>

#include <dns/exceptions.h>
#include <dns/rdata.h>
#include <dns/rdata/generic/detail/nsec3param_common.h>

#include <boost/lexical_cast.hpp>

#include <sstream>
#include <vector>
#include <stdint.h>

using namespace std;
using namespace isc::util;
using namespace isc::util::encode;

namespace isc {
namespace dns {
namespace rdata {
namespace generic {
namespace detail {
namespace nsec3 {

ParseNSEC3ParamResult
parseNSEC3ParamFromLexer(const char* const rrtype_name,
                         MasterLexer& lexer, vector<uint8_t>& salt)
{
    const uint32_t hashalg =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (hashalg > 0xff) {
        isc_throw(InvalidRdataText, rrtype_name <<
                  " hash algorithm out of range: " << hashalg);
    }

    const uint32_t flags =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (flags > 0xff) {
        isc_throw(InvalidRdataText, rrtype_name << " flags out of range: " <<
                  flags);
    }

    const uint32_t iterations =
        lexer.getNextToken(MasterToken::NUMBER).getNumber();
    if (iterations > 0xffff) {
        isc_throw(InvalidRdataText, rrtype_name <<
                  " iterations out of range: " << iterations);
    }

    const string salthex =
        lexer.getNextToken(MasterToken::STRING).getString();

    // Salt is up to 255 bytes, and space is not allowed in the HEX encoding,
    // so the encoded string cannot be longer than the double of max length
    // of the actual salt.
    if (salthex.size() > 255 * 2) {
        isc_throw(InvalidRdataText, rrtype_name << " salt is too long: "
                  << salthex.size() << " (encoded) bytes");
    }
    if (salthex != "-") {       // "-" means a 0-length salt
        decodeHex(salthex, salt);
    }

    return (ParseNSEC3ParamResult(hashalg, flags, iterations));
}

ParseNSEC3ParamResult
parseNSEC3ParamWire(const char* const rrtype_name,
                    InputBuffer& buffer,
                    size_t& rdata_len, std::vector<uint8_t>& salt)
{
    // NSEC3/NSEC3PARAM RR must have at least 5 octets:
    // hash algorithm(1), flags(1), iteration(2), saltlen(1)
    if (rdata_len < 5) {
        isc_throw(DNSMessageFORMERR, rrtype_name << " too short, length: "
                  << rdata_len);
    }

    const uint8_t hashalg = buffer.readUint8();
    const uint8_t flags = buffer.readUint8();
    const uint16_t iterations = buffer.readUint16();

    const uint8_t saltlen = buffer.readUint8();
    rdata_len -= 5;
    if (rdata_len < saltlen) {
        isc_throw(DNSMessageFORMERR, rrtype_name <<
                  " salt length is too large: " <<
                  static_cast<unsigned int>(saltlen));
    }

    salt.resize(saltlen);
    if (saltlen > 0) {
        buffer.readData(&salt[0], saltlen);
        rdata_len -= saltlen;
    }

    return (ParseNSEC3ParamResult(hashalg, flags, iterations));
}

} // end of nsec3
} // end of detail
} // end of generic
} // end of rdata
} // end of dns
} // end of isc
