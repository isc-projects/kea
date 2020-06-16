// Copyright (C) 2015-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CFG_DUID_H
#define CFG_DUID_H

#include <dhcp/duid.h>
#include <cc/cfg_to_element.h>
#include <cc/user_context.h>
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
/// across restarts of the server. RFC 8415 defines different DUID types.
/// Kea allows for selecting a type of DUID that the server should generate.
/// It also allows for overriding entire default DUID or parts of it via
/// configuration file. This class holds the DUID configuration specified
/// in the server configuration file.
class CfgDUID : public data::UserContext, public isc::data::CfgToElement {
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

    /// @brief Checks if server identifier should be stored on disk.
    ///
    /// @return true if the server identifier should be stored on
    /// the disk, false otherwise.
    bool persist() const {
        return (persist_);
    }

    /// @brief Sets a boolean flag indicating if the server identifier
    /// should be stored on the disk (if true) or not (if false).
    ///
    /// @param persist New value of the flag.
    void setPersist(const bool persist) {
        persist_ = persist;
    }

    /// @brief Creates instance of a DUID from the current configuration.
    ///
    /// The newly created DUID is retained internally to make it accessible
    /// anywhere.
    ///
    /// @param duid_file_path Absolute path to a DUID file.
    /// @return Pointer to an instance of new DUID.
    DuidPtr create(const std::string& duid_file_path);

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to unparsed configuration
    virtual isc::data::ElementPtr toElement() const;

    /// @brief Fetches the duid created by @ref create()
    /// @return a pointer to created duid. Pointer will
    /// empty if the duid has not yet been created.
    const DuidPtr getCurrentDuid() const {
        return (current_duid_);
    }

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

    /// @brief Boolean flag which indicates if server identifier should
    /// be stored on the disk.
    bool persist_;

    DuidPtr current_duid_;
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
