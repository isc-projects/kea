// Copyright (C) 2012-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef DUID_H
#define DUID_H

#include <asiolink/io_address.h>
#include <util/strutil.h>
#include <boost/shared_ptr.hpp>
#include <vector>
#include <stdint.h>
#include <unistd.h>

namespace isc {
namespace dhcp {

/// @brief Base type used to define a common smart pointer for all derived types.
class IdentifierBaseType {
protected:
    /// @brief Pure virtual destructor.
    ///
    /// This class can not be instantiated.
    virtual ~IdentifierBaseType() = 0;
};

/// @brief Shared pointer to a IdentifierType
typedef boost::shared_ptr<IdentifierBaseType> IdentifierBaseTypePtr;

template<size_t min_size, size_t max_size>
class IdentifierType : public IdentifierBaseType {
public:

    /// @brief Constructor from vector
    ///
    /// @param data The data used to create the IdentifierType
    IdentifierType(const std::vector<uint8_t>& data) {
        if (data.size() < min_size) {
            isc_throw(isc::BadValue, "identifier is too short (" << data.size()
                      << "), at least "<< min_size << " is required");
        }
        if (data.size() > max_size) {
            isc_throw(isc::BadValue, "identifier is too large (" << data.size()
                      << "), at most " << max_size << " is required");
        }
        data_ = data;
    }

    /// @brief Constructor from array and array size
    ///
    /// @param data The data used to create the Identifier
    /// @param len The data len used to create the Identifier
    IdentifierType(const uint8_t* data, size_t len) {
        if (len < min_size) {
            isc_throw(isc::BadValue, "identifier is too short (" << len
                      << "), at least "<< min_size << " is required");
        }
        if (len > max_size) {
            isc_throw(isc::BadValue, "identifier is too large (" << len
                      << "), at most " << max_size << " is required");
        }
        data_ = std::vector<uint8_t>(data, data + len);
    }

    /// @brief Return the minimum size of the acceptable data.
    ///
    /// @return the minimum size of the acceptable data.
    static constexpr size_t getMinSize() {
        return (min_size);
    }

    /// @brief Return the maximum size of the acceptable data.
    ///
    /// @return the maximum size of the acceptable data.
    static constexpr size_t getMaxSize() {
        return (max_size);
    }

    /// @brief Returns textual representation of the identifier (e.g. 00:01:02:03:ff)
    ///
    /// @return textual representation of the identifier (e.g. 00:01:02:03:ff)
    std::string toText() const {
        std::stringstream tmp;
        tmp << std::hex;
        bool delim = false;
        for (auto const data : data_) {
            if (delim) {
                tmp << ":";
            }
            tmp << std::setw(2) << std::setfill('0') << static_cast<unsigned int>(data);
            delim = true;
        }
        return (tmp.str());
    }

    /// @brief This static function parses an Identifier specified in the
    /// textual format.
    ///
    /// @param text Identifier in the hexadecimal format with digits
    /// representing individual bytes separated by colons.
    /// @return The data resulted from parsing the textual format.
    static std::vector<uint8_t> fromText(const std::string& text) {
        std::vector<uint8_t> binary;
        util::str::decodeFormattedHexString(text, binary);
        return (binary);
    }

    /// @brief Compares two identifiers for equality
    ///
    /// @return True if the two identifiers are equal, false otherwise.
    bool operator==(const IdentifierType& other) const {
        return (data_ == other.data_);
    }

    /// @brief Compares two identifiers for inequality
    ///
    /// @return True if the two identifiers are different, false otherwise.
    bool operator!=(const IdentifierType& other) const {
        return (data_ != other.data_);
    }

protected:

   /// @brief The actual content of the Identifier
   std::vector<uint8_t> data_;
};

/// @brief Shared pointer to a DUID
class DUID;
typedef boost::shared_ptr<DUID> DuidPtr;

/// @brief Holds DUID (DHCPv6 Unique Identifier)
///
/// This class holds DUID, that is used in client-id, server-id and
/// several other options. It is used to identify DHCPv6 entity.
class DUID : public IdentifierType<3, 130> {
public:

    /// @brief minimum duid size
    ///
    /// The minimal DUID size specified in RFC 8415, section 11.1 is 3:
    /// 2 fixed octets for the type + 1 minimum octet for the value.
    static constexpr size_t MIN_DUID_LEN = IdentifierType::getMinSize();

    /// @brief maximum duid size
    ///
    /// The maximum DUID size specified in RFC 8415, section 11.1 is 130:
    /// 2 fixed octets for the type + 128 maximum octets for the value.
    static constexpr size_t MAX_DUID_LEN = IdentifierType::getMaxSize();

    /// @brief specifies DUID type
    typedef enum {
        DUID_UNKNOWN = 0, ///< invalid/unknown type
        DUID_LLT = 1,     ///< link-layer + time, see RFC3315, section 11.2
        DUID_EN = 2,      ///< enterprise-id, see RFC3315, section 11.3
        DUID_LL = 3,      ///< link-layer, see RFC3315, section 11.4
        DUID_UUID = 4,    ///< UUID, see RFC3315, section 11.5
        DUID_MAX          ///< not a real type, just maximum defined value + 1
    } DUIDType;

    /// @brief Constructor from vector
    ///
    /// @param data The data used to create the DUID
    DUID(const std::vector<uint8_t>& data);

    /// @brief Constructor from array and array size
    ///
    /// @param data The data used to create the DUID
    /// @param len The data len used to create the DUID
    DUID(const uint8_t* data, size_t len);

    /// @brief Returns a const reference to the actual DUID value
    ///
    /// @warning Since this function returns a reference to the vector (not a
    /// copy) the returned object must be used with caution because it remains
    /// valid only for the time period when the object which returned it is
    /// valid.
    ///
    /// @return A reference to a vector holding a DUID.
    const std::vector<uint8_t>& getDuid() const;

    /// @brief Defines the constant "empty" DUID
    ///
    /// In general, empty DUID is not allowed. The only case where it is really
    /// valid is to designate declined IPv6 Leases. We have a broad assumption
    /// that the Lease->duid_ must always be set. However, declined lease
    /// doesn't have any DUID associated with it. Hence we need a way to
    /// indicate that fact.
    //
    /// @return reference to the static constant empty DUID
    static const DUID& EMPTY();

    /// @brief Returns the DUID type
    DUIDType getType() const;

    /// @brief Create DUID from the textual format.
    ///
    /// This static function parses a DUID specified in the textual format.
    ///
    /// @param text DUID in the hexadecimal format with digits representing
    /// individual bytes separated by colons.
    ///
    /// @throw isc::BadValue if parsing the DUID failed.
    static DUID fromText(const std::string& text);
};

/// @brief Forward declaration to the @c ClientId class.
class ClientId;
/// @brief Shared pointer to a Client ID.
typedef boost::shared_ptr<ClientId> ClientIdPtr;

/// @brief Holds Client identifier or client IPv4 address
///
/// This class is intended to be a generic IPv4 client identifier. It can hold
/// a client-id
class ClientId : public IdentifierType<2, 255> {
public:

    /// @brief Minimum size of a client ID
    ///
    /// Excerpt from RFC2132, section 9.14.
    /// The code for this option is 61, and its minimum length is 2.
    static constexpr size_t MIN_CLIENT_ID_LEN = IdentifierType::getMinSize();

    /// @brief Maximum size of a client ID
    ///
    /// @note RFC 2131 does not specify an upper length of a client ID, but the
    /// byte used to specify the option size byte can only go up to 255.
    static constexpr size_t MAX_CLIENT_ID_LEN = IdentifierType::getMaxSize();

    /// @brief Constructor based on vector<uint8_t>
    ///
    /// @param data The data used to create the ClientId
    ClientId(const std::vector<uint8_t>& data);

    /// @brief Constructor based on array and array size
    ///
    /// @param data The data used to create the ClientId
    /// @param len The data len used to create the ClientId
    ClientId(const uint8_t* data, size_t len);

    /// @brief Returns reference to the client-id data.
    ///
    /// @warning Since this function returns a reference to the vector (not a
    /// copy) the returned object must be used with caution because it remains
    /// valid only for the time period when the object which returned it is
    /// valid.
    ///
    /// @return A reference to a vector holding a client identifier.
    const std::vector<uint8_t>& getClientId() const;

    /// @brief Create client identifier from the textual format.
    ///
    /// This static function creates the instance of the @c ClientId from the
    /// textual format.
    ///
    /// @param text Client identifier in the textual format.
    ///
    /// @return Pointer to the instance of the @c ClientId.
    /// @throw isc::BadValue if parsing the client identifier failed.
    /// @throw isc::OutOfRange if the client identifier is truncated.
    static ClientIdPtr fromText(const std::string& text);
};

}  // namespace dhcp
}  // namespace isc

#endif /* DUID_H */
