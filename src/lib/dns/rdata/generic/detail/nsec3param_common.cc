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
parseNSEC3ParamText(const char* const rrtype_name,
                    const string& rdata_str, istringstream& iss, 
                    vector<uint8_t>& salt)
{
    unsigned int hashalg, flags, iterations;
    string iterations_str, salthex;

    iss >> hashalg >> flags >> iterations_str >> salthex;
    if (iss.bad() || iss.fail()) {
        isc_throw(InvalidRdataText, "Invalid " << rrtype_name <<
                  " text: " << rdata_str);
    }
    if (hashalg > 0xff) {
        isc_throw(InvalidRdataText, rrtype_name <<
                  " hash algorithm out of range: " << hashalg);
    }
    if (flags > 0xff) {
        isc_throw(InvalidRdataText, rrtype_name << " flags out of range: " <<
                  flags);
    }
    // Convert iteration.  To reject an invalid case where there's no space
    // between iteration and salt, we extract this field as string and convert
    // to integer.
    try {
        iterations = boost::lexical_cast<unsigned int>(iterations_str);
    } catch (const boost::bad_lexical_cast&) {
        isc_throw(InvalidRdataText, "Bad " << rrtype_name <<
                  " iteration: " << iterations_str);
    }
    if (iterations > 0xffff) {
        isc_throw(InvalidRdataText, rrtype_name <<
                  " iterations out of range: " <<
            iterations);
    }

    if (salthex != "-") {       // "-" means a 0-length salt
        decodeHex(salthex, salt);
    }
    if (salt.size() > 255) {
        isc_throw(InvalidRdataText, rrtype_name << " salt is too long: "
                  << salt.size() << " bytes");
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

