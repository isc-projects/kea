// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <sys/types.h>
#include <sys/socket.h>

#include <exceptions/exceptions.h>

#include <boost/lexical_cast.hpp>

#include <acl/ip_check.h>

using namespace std;
using namespace isc;

namespace isc {
namespace acl {
namespace internal {

uint8_t
createMask(size_t prefixlen) {

    if (prefixlen == 0) {
        return (0);

    } else if (prefixlen <= 8) {

        // In the following discussion:
        //
        // w is the width of the data type in bits.
        // m is the value of prefixlen, the number of most signifcant bits we
        // want to set.
        // ** is exponentiation (i.e. 2**n is 2 raised to the power of n).
        //
        // We note that the value of 2**m - 1 gives a value with the least
        // significant m bits set.  For a data type of width w, this means that
        // the most signficant (w-m) bits are clear.
        //
        // Hence the value 2**(w-m) - 1 gives a result with the least signficant
        // w-m bits set and the most significant m bits clear.  The 1's
        // complement of this value gives is the result we want.
        //
        // Final note: at this point in the logic, m is non-zero, so w-m < w.
        // This means 1<<(w-m) will fit into a variable of width w bits.  In
        // other words, in the expression below, no term will cause an integer
        // overflow.
        return (~((1 << (8 - prefixlen)) - 1));
    }

    // Mask size is too large. (Note that prefixlen is unsigned, so can't be
    // negative.)
    isc_throw(isc::OutOfRange, "prefixlen argument must be between 0 and 8");
}

pair<string, int>
splitIPAddress(const string& ipprefix) {

    // Split string into its components - an address and a prefix length.
    // We initialize by assuming that there is no slash in the string given.
    string address = ipprefix;
    string prefixlen = "";

    const size_t slashpos = ipprefix.find('/');
    if ((ipprefix.size() == 0) || (slashpos == 0) ||
        (slashpos == (ipprefix.size() - 1))) {
        // Nothing in prefix, or it starts with or ends with a slash.
        isc_throw(isc::InvalidParameter, "address prefix of " << ipprefix <<
                                         " is not valid");

    } else if (slashpos != string::npos) {
        // There is a slash somewhere in the string, split the string on it.
        // Don't worry about multiple slashes - if there are some, they will
        // appear in the prefixlen segment and will be detected when an attempt
        // is made to convert it to a number.
        address = ipprefix.substr(0, slashpos);
        prefixlen = ipprefix.substr(slashpos + 1);
    }

    // Set the default value for the prefix length.  As the type of the address
    // is not known at the point this function is called, the maximum
    // allowable value is also not known.  The value of 0 is reserved for
    // a "match any address" match.
    int prefix_size = -1;

    // If there is a prefixlength, attempt to convert it.
    if (!prefixlen.empty()) {
        try {
            prefix_size = boost::lexical_cast<int>(prefixlen);
            if (prefix_size < 0) {
                isc_throw(isc::InvalidParameter, "address prefix of " <<
                          ipprefix << " is not valid");
            }
        } catch (boost::bad_lexical_cast&) {
            isc_throw(isc::InvalidParameter, "prefix length of '" <<
                      prefixlen << "' is not valid");
        }
    }

    return (make_pair(address, prefix_size));
}
} // namespace internal

namespace {
const uint8_t*
getSockAddrData(const struct sockaddr& sa) {
    const void* sa_ptr = &sa;
    const void* data_ptr;
    if (sa.sa_family == AF_INET) {
        const struct sockaddr_in* sin =
            static_cast<const struct sockaddr_in*>(sa_ptr);
        data_ptr = &sin->sin_addr;
    } else if (sa.sa_family == AF_INET6) {
        const struct sockaddr_in6* sin6 =
            static_cast<const struct sockaddr_in6*>(sa_ptr);
        data_ptr = &sin6->sin6_addr;
    } else {
        isc_throw(BadValue, "Unsupported address family for IPAddress: " <<
                  static_cast<int>(sa.sa_family));
    }
    return (static_cast<const uint8_t*>(data_ptr));
}
}

IPAddress::IPAddress(const struct sockaddr& sa) :
    family(sa.sa_family),
    data(getSockAddrData(sa)),
    length(family == AF_INET ?
           sizeof(struct in_addr) : sizeof(struct in6_addr))
{}
} // namespace acl
} // namespace isc
