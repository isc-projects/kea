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
#include <util/buffer.h>
#include <dhcp/libdhcp++.h>
#include "config.h"
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option.h>
#include <dhcp/option6_ia.h>
#include <dhcp/option6_iaaddr.h>

using namespace std;
using namespace isc::dhcp;
using namespace isc::util;

// static array with factories for options
std::map<unsigned short, Option::Factory*> LibDHCP::v6factories_;

unsigned int
LibDHCP::unpackOptions6(const boost::shared_array<uint8_t> buf,
                        unsigned int buf_len,
                        unsigned int offset, unsigned int parse_len,
                        isc::dhcp::Option::OptionCollection& options) {
    if (offset + parse_len > buf_len) {
        isc_throw(OutOfRange, "Option parse failed. Tried to parse "
                  << parse_len << " bytes at offset " << offset
                  << ":  out of buffer");
    }
    unsigned int end = offset + parse_len;

    while (offset +4 <= end) {
        uint16_t opt_type = buf[offset]*256 + buf[offset+1];
        offset += 2;
        uint16_t opt_len = buf[offset]*256 + buf[offset+1];
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

void
LibDHCP::unpackOptions4(const std::vector<uint8_t>& buf,
                        isc::dhcp::Option::OptionCollection& options) {
    size_t offset = 0;

    // 2 - header of DHCPv4 option
    while (offset + 1 <= buf.size()) {
        uint8_t opt_type = buf[offset++];

        if (opt_type == DHO_END)
          return; // just return. Don't need to add DHO_END option

        if (offset + 1 >= buf.size()) {
          isc_throw(OutOfRange, "Attempt to parse truncated option "
                    << opt_type);
        }

        uint8_t opt_len =  buf[offset++];
        if (offset + opt_len > buf.size() ) {
            isc_throw(OutOfRange, "Option parse failed. Tried to parse "
                      << offset + opt_len << " bytes from " << buf.size()
                      << "-byte long buffer.");
        }

        boost::shared_ptr<Option> opt;
        switch(opt_type) {
        default:
            opt = boost::shared_ptr<Option>(new Option(Option::V4, opt_type,
                                                       buf.begin()+offset,
                                                       buf.begin()+offset+opt_len));
        }

        options.insert(pair<int, boost::shared_ptr<Option> >(opt_type, opt));
        offset += opt_len;
    }
}

unsigned int
LibDHCP::packOptions6(boost::shared_array<uint8_t> data,
                      unsigned int data_len,
                      unsigned int offset,
                      const isc::dhcp::Option::OptionCollection& options) {
    try {
        for (Option::OptionCollection::const_iterator it = options.begin();
             it != options.end();
             ++it) {
            unsigned short opt_len = (*it).second->len();
            if (offset + opt_len > data_len) {
                isc_throw(OutOfRange, "Failed to build option " <<
                          (*it).first << ": out of buffer");
            }
            offset = it->second->pack(data, data_len, offset);
        }
    }
    catch (const Exception&) {
        cout << "Packet build failed (Option build failed)." << endl;
        throw;
    }
    return (offset);
}

void
LibDHCP::packOptions(isc::util::OutputBuffer& buf,
                     const Option::OptionCollection& options) {
    for (Option::OptionCollection::const_iterator it = options.begin();
         it != options.end();
         ++it) {
        it->second->pack4(buf);
    }
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
