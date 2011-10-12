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
#include "dhcp6.h"

#include "option.h"
#include "option6_ia.h"
#include "option6_iaaddr.h"

using namespace std;
using namespace isc::dhcp;

// static array with factories for options
std::map<unsigned short, Option::Factory*> LibDHCP::v6factories_;

unsigned int
LibDHCP::unpackOptions6(const boost::shared_array<uint8_t> buf,
                        unsigned int buf_len,
                        unsigned int offset, unsigned int parse_len,
                        isc::dhcp::Option::Option6Collection& options) {
    if (offset + parse_len > buf_len) {
        isc_throw(OutOfRange, "Option parse failed. Tried to parse "
                  << parse_len << " bytes at offset " << offset
                  << ":  out of buffer");
    }
    unsigned int end = offset + parse_len;

    while ( offset +4 <= end ) {
        unsigned int opt_type = buf[offset]*256 + buf[offset+1];
        offset += 2;
        unsigned int opt_len = buf[offset]*256 + buf[offset+1];
        offset += 2;

        if (offset + opt_len > end ) {
            cout << "Option " << opt_type << " truncated." << endl;
            return (offset);
        }
        boost::shared_ptr<Option> opt;
        switch (opt_type) {
        case D6O_IA_NA:
        case D6O_IA_PD:
            // cout << "Creating Option6IA" << endl;
            opt = boost::shared_ptr<Option>(new Option6IA(opt_type,
                                                          buf, buf_len,
                                                          offset,
                                                          opt_len));
            break;
        case D6O_IAADDR:
            // cout << "Creating Option6IAAddr" << endl;
            opt = boost::shared_ptr<Option>(new Option6IAAddr(opt_type,
                                                              buf, buf_len,
                                                              offset, opt_len));
            break;
        default:
            // cout << "Creating Option" << endl;
            opt = boost::shared_ptr<Option>(new Option(Option::V6,
                                                       opt_type,
                                                       buf,
                                                       offset,
                                                       opt_len));
            break;
        }
        // add option to options
        options.insert(pair<int, boost::shared_ptr<Option> >(opt_type, opt));
        offset += opt_len;
    }

    return (offset);
}

unsigned int
LibDHCP::packOptions6(boost::shared_array<uint8_t> data,
                      unsigned int data_len,
                      unsigned int offset,
                      const isc::dhcp::Option::Option6Collection& options) {
    try {
        for (isc::dhcp::Option::Option6Collection::const_iterator it = options.begin();
             it != options.end();
             ++it) {
            unsigned short opt_len = (*it).second->len();
            if (offset + opt_len > data_len) {
                isc_throw(OutOfRange, "Failed to build option " <<
                          (*it).first << ": out of buffer");
            }
            offset = (*it).second->pack(data, data_len, offset);
        }
    }
    catch (Exception e) {
        cout << "Packet build failed." << endl;
        return (-1);
    }
    return (offset);
}

bool
LibDHCP::OptionFactoryRegister(Option::Universe u,
                               unsigned short opt_type,
                               Option::Factory * factory) {
    switch (u) {
    case Option::V6: {
        if (v6factories_.find(opt_type)!=v6factories_.end()) {
            isc_throw(BadValue, "There is already DHCPv6 factory registered "
                     << "for option type "  << opt_type);
        }
        v6factories_[opt_type]=factory;
        return true;
    }
    case Option::V4:
    default:{
        isc_throw(BadValue, "This universe type is not supported yet.");
        return false; // never happens
    }
    }

}
