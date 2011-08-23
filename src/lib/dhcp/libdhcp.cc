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

#include <boost/shared_array.hpp>
#include <boost/shared_ptr.hpp>
#include "dhcp/libdhcp.h"
#include "config.h"

using namespace std;
using namespace isc::dhcp;

std::string
LibDHCP::version() {
    return PACKAGE_VERSION;
}

/**
 * Parses provided buffer and creates Option objects.
 *
 * Parses provided buf array and stores created Option objects
 * in options container.
 *
 * @param buf Buffer to be parsed.
 * @param offset Specifies offset for the first option.
 * @param options Reference to option container. Options will be
 *        put here.
 *
 * @return offset to first byte after last parsed option
 */
unsigned int
LibDHCP::unpackOptions6(boost::shared_array<char>& buf,
                        int buf_len,
                        unsigned short offset,
                        isc::dhcp::Option::Option6Lst& options) {
    int len = buf_len - offset;
    while (len>4) {
        int opt_type = buf[offset]*256 + buf[offset+1];
        offset += 2;
        len -= 2;
        int opt_len = buf[offset]*256 + buf[offset+1];
        offset += 2;
        len -= 2;

        if (opt_len > len) {
            cout << "Packet truncated. Unable to parse option " << opt_type
                 << ". " << len << " bytes left in buffer, but option "
                 << "len=" << opt_len << endl;
            return (offset);
        }

        boost::shared_ptr<Option> opt(new Option(Option::V6,
                                                 opt_type,
                                                 buf,
                                                 offset,
                                                 opt_len));
        // add option to options
        options.insert(pair<int, boost::shared_ptr<Option> >(opt_type, opt));
        offset += opt_len;
        len -= opt_len;
        cout << "Parse opt=" << opt_type << ", opt_len=" << opt_len << ", bytes left=" << len << endl;
    }

    if (len != 0) {
        cout << "There are " << len << " bytes left to parse." << endl;
    }

    return (offset);
}

unsigned int
LibDHCP::packOptions6(boost::shared_array<char>& data,
                      int data_len,
                      unsigned short offset,
                      isc::dhcp::Option::Option6Lst& options) {
    char* buf = &data[offset];
    char* end = &data[data_len-1]; // last byte in shared array
    try {
        for (isc::dhcp::Option::Option6Lst::iterator it = options.begin();
             it != options.end();
             ++it) {
            unsigned short opt_len = (*it).second->len();
            if (buf+opt_len > end) {
                isc_throw(OutOfRange, "Failed to build option" <<
                          (*it).first << ": out of buffer");
            }
            buf = (*it).second->pack(buf, opt_len);
            offset += opt_len;
            data_len -= opt_len;
        }
    }
    catch (Exception e) {
        cout << "Packet build failed." << endl;
        return (-1);
    }
    cout << "Packet built" << endl;
    return (offset);
}
