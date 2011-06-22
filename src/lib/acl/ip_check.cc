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

#include <acl/ip_check.h>
#include <util/strutil.h>

using namespace std;

// Split the IP Address prefix

namespace isc {
namespace acl {
namespace internal {

pair<string, int>
splitIPAddress(const string& ipprefix) {

    // Set the default value for the prefix length.  As the type of the address
    // is not known at the point this function is called, the maximum
    // allowable value is also not known.  And the value of 0 is reserved for
    // a "match any address" match.
    int prefix_size = -1;

    // Only deal with the string after we've removed leading and trailing
    // spaces.
    string mod_prefix = isc::util::str::trim(ipprefix);

    // Split string into its components - an address and a prefix length.
    // We initialize by assuming that there is no slash in the string given.
    string address = mod_prefix;
    string prefixlen = "";

    size_t slashpos = mod_prefix.find('/');
    if ((mod_prefix.size() == 0) || (slashpos == 0) ||
        (slashpos == (mod_prefix.size() - 1))) {
        // Nothing in prefix, or it starts with or ends with a slash.
        isc_throw(isc::InvalidParameter, "address prefix of " << ipprefix <<
                                         " is not valid");

    } else if (slashpos != string::npos) {
        // There is a slash somewhere in the string, split the string on it.
        // Don't worry about multiple slashes - if there are some, they will
        // appear in the prefixlen segment and will be detected when an attempt
        // is made to convert it to a number.
        address = mod_prefix.substr(0, slashpos);
        prefixlen = mod_prefix.substr(slashpos + 1);
    }

    // If there is a prefixlength, attempt to convert it.
    if (!prefixlen.empty()) {
        try {
            prefix_size = boost::lexical_cast<int>(prefixlen);
            if (prefix_size < 0) {
                isc_throw(isc::InvalidParameter, "address prefix of " <<
                          ipprefix << " is not valid");
            }
        } catch (boost::bad_lexical_cast&) {
            isc_throw(isc::InvalidParameter, "prefix length of " << prefixlen <<
                                             " is not valid");
        }
    }

    return (make_pair(address, prefix_size));
}

} // namespace internal
} // namespace acl
} // namespace isc
