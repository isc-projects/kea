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

#ifndef LIBDHCP_H_
#define LIBDHCP_H_

#include <iostream>
#include "dhcp/pkt6.h"

namespace isc {
namespace dhcp {

class LibDHCP {

public:
    LibDHCP();
    static std::string version();

    bool parsePkt6(Pkt6& pkt);
    bool builtPkt6(Pkt6& pkt);

    static unsigned int
    packOptions6(boost::shared_array<char> buf, unsigned int buf_len,
                 unsigned int offset,
                 isc::dhcp::Option::Option6Lst& options_);
    static unsigned int
    unpackOptions6(boost::shared_array<char> buf, unsigned int buf_len,
                   unsigned int offset, unsigned int parse_len,
                   isc::dhcp::Option::Option6Lst& options_);

    bool OptionFactorRegister(Option::Universe u,
                              unsigned short type,
                              Option::Factory * factory);
protected:
    // pointers to factories that produce DHCPv6 options
    static std::map<unsigned short, Option::Factory*> v6factories_;
};

}
}

#endif
