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

#ifndef CFG_DUID_H
#define CFG_DUID_H

#include <dhcp/duid.h>
#include <boost/shared_ptr.hpp>
#include <stdint.h>
#include <vector>

namespace isc {
namespace dhcp {

/// @brief Holds manual configuration of the server identifier (DUID).
///
/// The DHCPv6 server uses DHCPv6 Unique Identifier (DUID) to identify itself
/// to the clients. Typically, the server generates the DUID on the first
/// startup and writes it to the persistent storage so as it doesn't change
/// across restarts of the server. RFC3315 and RFC6355 define different DUID
/// types. Kea allows for selecting a type of DUID that the server should
/// generate. It also allows for overriding entire default DUID or parts of
/// it via configuration file. This class holds the DUID configuration
/// specified in the server configuration file.
class CfgDUID {
public:

    /// @brief Constructor.
    CfgDUID();

    /// @brief Returns DUID type.
    DUID::DUIDType getType() const {
        return (type_);
    }

    /// @brief Sets DUID type.
    void setType(const DUID::DUIDType& type) {
        type_ = type;
    }

    /// @brief Returns identifier.
    ///
    /// Identifier is a link layer address for the DUID-LLT and DUID-LL. It
    /// is also a variable length identifier in DUID-EN. It may be used for
    /// all other existing and future DUID types when there is a need to
    /// represent some variable length identifier.
    ///
    /// @return Vector holding an identifier belonging to a particular
    /// DUID type.
    std::vector<uint8_t> getIdentifier() const {
        return (identifier_);
    }

    /// @brief Sets new identifier as hex string.
    ///
    /// @param identifier_as_hex String of hexadecimal digits representing
    /// variable length identifier within a DUID.
    void setIdentifier(const std::string& identifier_as_hex);

    /// @brief Returns hardware type for DUID-LLT and DUID-LL.
    uint16_t getHType() const {
        return (htype_);
    }

    /// @brief Sets new hardware type for DUID-LLT and DUID-LL.
    void setHType(const uint16_t htype) {
        htype_ = htype;
    }

    /// @brief Returns time for the DUID-LLT.
    uint32_t getTime() const {
        return (time_);
    }

    /// @brief Sets new time for DUID-LLT.
    void setTime(const uint32_t new_time) {
        time_ = new_time;
    }

    /// @brief Returns enterprise id for the DUID-EN.
    uint32_t getEnterpriseId() const {
        return (enterprise_id_);
    }

    /// @brief Sets new enterprise id.
    ///
    /// @param enterprise_id New enterprise id.
    void setEnterpriseId(const uint32_t enterprise_id) {
        enterprise_id_ = enterprise_id;
    }

    /// @brief Creates instance of a DUID from the current configuration.
    ///
    /// @param duid_file_path Absolute path to a DUID file.
    /// @return Pointer to an instance of new DUID.
    DuidPtr create(const std::string& duid_file_path) const;

private:

    /// @brief DUID type.
    DUID::DUIDType type_;

    /// @brief Variable length identifier in a DUID.
    std::vector<uint8_t> identifier_;

    /// @brief Hardware type.
    uint16_t htype_;

    /// @brief Time used for DUID-LLT.
    uint32_t time_;

    /// @brief Enterprise id used for DUID-EN.
    uint32_t enterprise_id_;

};

/// @name Pointers to the @c CfgDUID objects.
//@{
/// @brief Pointer to the Non-const object.
typedef boost::shared_ptr<CfgDUID> CfgDUIDPtr;

/// @brief Pointer to the const object.
typedef boost::shared_ptr<const CfgDUID> ConstCfgDUIDPtr;

//@}

}
}

#endif // CFG_DUID_H
