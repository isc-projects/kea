// Copyright (C) 2012 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DUID_H
#define DUID_H

#include <asiolink/io_address.h>

#include <vector>

#include <stdint.h>
#include <unistd.h>

namespace isc {
namespace dhcp {

/// @brief Holds DUID (DHCPv6 Unique Identifier)
///
/// This class holds DUID, that is used in client-id, server-id and
/// several other options. It is used to identify DHCPv6 entity.
class DUID {
 public:
    /// @brief maximum duid size
    /// As defined in RFC3315, section 9.1
    static const size_t MAX_DUID_LEN = 128;

    /// @brief specifies DUID type
    typedef enum {
        DUID_UNKNOWN = 0, ///< invalid/unknown type
        DUID_LLT = 1,     ///< link-layer + time, see RFC3315, section 9.2
        DUID_EN = 2,      ///< enterprise-id, see RFC3315, section 9.3
        DUID_LL = 3,      ///< link-layer, see RFC3315, section 9.4
        DUID_UUID = 4,    ///< UUID, see RFC6355
        DUID_MAX          ///< not a real type, just maximum defined value + 1
    } DUIDType;

    /// @brief creates a DUID
    DUID(const std::vector<uint8_t>& duid);

    /// @brief creates a DUID
    DUID(const uint8_t *duid, size_t len);

    /// @brief returns a const reference to the actual DUID value
    ///
    /// Note: For safety reasons, this method returns a copy of data as
    /// otherwise the reference would be only valid as long as the object that
    /// returned it. In any case, this method should be used only sporadically.
    /// If there are frequent uses, we must implement some other method
    /// (e.g. storeSelf()) that will avoid data copying.
    const std::vector<uint8_t> getDuid() const;

    /// @brief returns DUID type
    DUIDType getType() const;

    /// returns textual prepresentation (e.g. 00:01:02:03:ff)
    std::string toText() const;

    /// compares two DUIDs
    bool operator==(const DUID& other) const;

    /// compares two DUIDs
    bool operator!=(const DUID& other) const;

 protected:
    /// the actual content of the DUID
    std::vector<uint8_t> duid_;
};

typedef boost::shared_ptr<DUID> DuidPtr;

/// @brief Holds Client identifier or client IPv4 address
///
/// This class is intended to be a generic IPv4 client identifier. It can hold
/// a client-id
class ClientId : DUID {
 public:

    /// constructor based on vector<uint8_t>
    ClientId(const std::vector<uint8_t>& clientid);

    /// constructor based on C-style data
    ClientId(const uint8_t *clientid, size_t len);

    /// @brief returns reference to the client-id data
    ///
    const std::vector<uint8_t> getClientId() const;

    // compares two client-ids
    bool operator == (const ClientId& other) const;

    // compares two client-ids
    bool operator != (const ClientId& other) const;
};

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif /* DUID_H */
