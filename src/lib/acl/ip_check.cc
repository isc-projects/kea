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

#include <sys/socket.h>

#include <exceptions/exceptions.h>

#include <acl/ip_check.h>

using namespace isc;

namespace isc {
namespace acl {

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

std::pair<std::string, int>
splitIPAddress(const std::string& addrmask) {
    // Set the default value for the mask size
    int masksize = -1;

    // Split string into its components.  As the tokenising code ignores
    // leading, trailing nd consecutive delimiters, be strict here and ensures
    // that the string contains at most 0 or 1 slashes.
    if (std::count(addrmask.begin(), addrmask.end(), '/') > 1) {
        isc_throw(isc::InvalidParameter, "address/masksize of " <<
                  addrmask << " is not valid");
    }

    std::vector<std::string> components = isc::util::str::tokens(addrmask, "/");
    if (components.size() == 2) {

        // There appears to be a mask, try converting it to a number.
        try {
            masksize = boost::lexical_cast<int>(components[1]);
        } catch (boost::bad_lexical_cast&) {
            isc_throw(isc::InvalidParameter,
                      "mask size specified in address/masksize " << addrmask <<
                      " is not valid");
        }

        // Ensure that it is positive - a mask size of zero is not a valid
        // value.
        if (masksize <= 0) {
            isc_throw(isc::OutOfRange,
                      "mask size specified in address/masksize " << addrmask <<
                      " must be a positive number");
        }

    } else if (components.size() > 2) {
        isc_throw(isc::InvalidParameter, "address/masksize of " <<
                  addrmask << " is not valid");
    }

    return (std::make_pair(components[0], masksize));
}
} // namespace acl
} // namespace isc
