// Copyright (C) 2011-2012 Internet Systems Consortium, Inc. ("ISC")
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
std::map<unsigned short, Option::Factory*> LibDHCP::v4factories_;

// static array with factories for options
std::map<unsigned short, Option::Factory*> LibDHCP::v6factories_;


size_t LibDHCP::unpackOptions6(const OptionBuffer& buf,
                               isc::dhcp::Option::OptionCollection& options) {
    size_t offset = 0;
    size_t end = buf.size();

    while (offset +4 <= end) {
        uint16_t opt_type = buf[offset] * 256 + buf[offset + 1];
        offset += 2;
        uint16_t opt_len = buf[offset] * 256 + buf[offset + 1];
        offset += 2;

        if (offset + opt_len > end) {
            cout << "Option " << opt_type << " truncated." << endl;
            return (offset);
        }
        OptionPtr opt;
        switch (opt_type) {
        case D6O_IA_NA:
        case D6O_IA_PD:
            // cout << "Creating Option6IA" << endl;
            opt = OptionPtr(new Option6IA(opt_type,
                                          buf.begin() + offset,
                                          buf.begin() + offset + opt_len));
            break;
        case D6O_IAADDR:
            // cout << "Creating Option6IAAddr" << endl;
            opt = OptionPtr(new Option6IAAddr(opt_type,
                                              buf.begin() + offset,
                                              buf.begin() + offset + opt_len));
            break;
        default:
            // cout << "Creating Option" << endl;
            opt = OptionPtr(new Option(Option::V6,
                                       opt_type,
                                       buf.begin() + offset,
                                       buf.begin() + offset + opt_len));
            break;
        }
        // add option to options
        options.insert(std::make_pair(opt_type, opt));
        offset += opt_len;
    }

    return (offset);
}

size_t LibDHCP::unpackOptions4(const OptionBuffer& buf,
                                 isc::dhcp::Option::OptionCollection& options) {
    size_t offset = 0;

    // 2 byte - header of DHCPv4 option
    while (offset + 1 <= buf.size()) {
        uint8_t opt_type = buf[offset++];

        // DHO_END is a special, one octet long option
        if (opt_type == DHO_END)
            return (offset); // just return. Don't need to add DHO_END option

        // DHO_PAD is just a padding after DHO_END. Let's continue parsing
        // in case we receive a message without DHO_END.
        if (opt_type == DHO_PAD)
            continue;

        if (offset + 1 >= buf.size()) {
            isc_throw(OutOfRange, "Attempt to parse truncated option "
                      << opt_type);
        }

        uint8_t opt_len =  buf[offset++];
        if (offset + opt_len > buf.size()) {
            isc_throw(OutOfRange, "Option parse failed. Tried to parse "
                      << offset + opt_len << " bytes from " << buf.size()
                      << "-byte long buffer.");
        }

        OptionPtr opt;
        switch(opt_type) {
        default:
            opt = OptionPtr(new Option(Option::V4, opt_type,
                                       buf.begin()+offset,
                                       buf.begin()+offset+opt_len));
        }

        options.insert(std::make_pair(opt_type, opt));
        offset += opt_len;
    }
    return (offset);
}

void LibDHCP::packOptions6(isc::util::OutputBuffer &buf,
                           const isc::dhcp::Option::OptionCollection& options) {
    try {
        for (Option::OptionCollection::const_iterator it = options.begin();
             it != options.end(); ++it) {
            it->second->pack(buf);
        }
    }
    catch (const Exception&) {
        cout << "Packet build failed (Option build failed)." << endl;
        throw;
    }
}

void
LibDHCP::packOptions(isc::util::OutputBuffer& buf,
                     const Option::OptionCollection& options) {
    for (Option::OptionCollection::const_iterator it = options.begin();
         it != options.end(); ++it) {
        it->second->pack4(buf);
    }
}

void LibDHCP::OptionFactoryRegister(Option::Universe u,
                                    uint16_t opt_type,
                                    Option::Factory* factory) {
    switch (u) {
    case Option::V6: {
        if (v6factories_.find(opt_type) != v6factories_.end()) {
            isc_throw(BadValue, "There is already DHCPv6 factory registered "
                     << "for option type "  << opt_type);
        }
        v6factories_[opt_type]=factory;
        return;
    }
    case Option::V4:
    {
        // Option 0 is special (a one octet-long, equal 0) PAD option. It is never
        // instantiated as an Option object, but rather consumed during packet parsing.
        if (opt_type == 0) {
            isc_throw(BadValue, "Cannot redefine PAD option (code=0)");
        }
        // Option 255 is never instantiated as an option object. It is special
        // (a one-octet equal 255) option that is added at the end of all options
        // during packet assembly. It is also silently consumed during packet parsing.
        if (opt_type > 254) {
            isc_throw(BadValue, "Too big option type for DHCPv4, only 0-254 allowed.");
        }
        if (v4factories_.find(opt_type)!=v4factories_.end()) {
            isc_throw(BadValue, "There is already DHCPv4 factory registered "
                     << "for option type "  << opt_type);
        }
        v4factories_[opt_type]=factory;
        return;
    }
    default:
        isc_throw(BadValue, "Invalid universe type specified.");
    }

    return;
}
