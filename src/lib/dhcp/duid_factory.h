// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DUID_FACTORY_H
#define DUID_FACTORY_H

#include <dhcp/duid.h>
#include <stdint.h>
#include <string>
#include <vector>

namespace isc {
namespace dhcp {

class DUIDFactory {
public:

    DUIDFactory(const std::string& storage_location = "");

    bool isPersisted() const;

    void createLLT(const uint16_t htype, const uint32_t time_in,
                   const std::vector<uint8_t>& ll_identifier);

    void createEN(const uint32_t enterprise_id, const std::vector<uint8_t>& identifier);

    void createLL(const uint16_t htype, const std::vector<uint8_t>& ll_identifier);

    DuidPtr get();

private:

    void createLinkLayerId(std::vector<uint8_t>& identifier) const;

    std::string storage_location_;

    DuidPtr duid_;

};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif /* DUID_FACTORY_H */
