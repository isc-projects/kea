// Copyright (C) 2020-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RADIUS_ACCESS_H
#define RADIUS_ACCESS_H

#include <hooks/hooks.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <radius_service.h>
#include <radius_request.h>
#include <map>
#include <mutex>

namespace isc {
namespace radius {

/// @brief Class of pending Radius access request.
///
/// @tparam PktPtrType Either Pkt4Ptr or Pkt6Ptr.
template <class PktPtrType>
class RadiusAuthPendingRequest {
public:

    /// @brief Constructor.
    ///
    /// @param query The query which triggered the access request.
    RadiusAuthPendingRequest(PktPtrType query) : query_(query) { }

    /// @brief The query which triggered the access request.
    PktPtrType query_;
};

/// @brief Pointer to a pending Radius access request.
///
/// @tparam PktPtrType Either Pkt4Ptr or Pkt6Ptr.
template <class PktPtrType>
using RadiusAuthPendingRequestPtr =
    boost::shared_ptr<RadiusAuthPendingRequest<PktPtrType>>;

/// @brief Class of pending Radius access requests.
///
/// @tparam PktPtrType Either Pkt4Ptr or Pkt6Ptr.
template <class PktPtrType>
class RadiusAuthPendingRequests {
public:

    /// @brief Size of the map.
    ///
    /// @return The map size.
    size_t size() const {
        return (map_.size());
    }

    /// @brief Clear the map.
    void clear() {
        map_.clear();
    }

    /// @brief Get a pending access request from the map.
    ///
    /// @param id The Radius id.
    /// @return The pointer to the pending access request or null.
    RadiusAuthPendingRequestPtr<PktPtrType>
        get(const std::vector<uint8_t>& id) const {
        auto const& it = map_.find(id);
        if (it != map_.end()) {
            return (it->second);
        } else {
            return (RadiusAuthPendingRequestPtr<PktPtrType>());
        }
    }

    /// @brief Set a pending access request into the map.
    ///
    /// Assume that get was called before and returned null.
    ///
    /// @param id The Radius id.
    /// @param query The query which triggered the access request.
    void set(const std::vector<uint8_t>& id, PktPtrType query) {
        map_[id] = RadiusAuthPendingRequestPtr<PktPtrType>(
                        new RadiusAuthPendingRequest<PktPtrType>(query));
    }

    /// @brief Remove a pending access request from the map.
    ///
    /// @param id The Radius id.
    void remove(const std::vector<uint8_t>& id) {
        static_cast<void>(map_.erase(id));
    }

private:
    /// @brief The map of pendind Radius access requests.
    std::map<std::vector<uint8_t>, RadiusAuthPendingRequestPtr<PktPtrType>> map_;

public:
    /// @brief The mutex.
    ///
    /// Must be taken before any operation.
    std::mutex mutex_;
};

/// @brief Class of Radius access environments.
///
/// This class is a container for the communication environment so
/// values needed by the handler are in this data holding class.
class RadiusAuthEnv {
public:

    /// Constructor.
    ///
    /// @param subnet_id Subnet ID aka NAS port.
    /// @param id The identifier.
    /// @param send_attrs Attributes to send.
    RadiusAuthEnv(uint32_t subnet_id,
                  const std::vector<uint8_t>& id,
                  AttributesPtr send_attrs);

    /// @brief Subnet Id (aka client/NAS port).
    uint32_t subnet_id_;

    /// @brief Identifier.
    const std::vector<uint8_t> id_;

    /// @brief Attributes to send.
    AttributesPtr send_attrs_;
};

/// @brief Class of Radius access communication handler.
///
/// This class is a wrapper for communication environment and pointer to
/// synchronous authentication communication class.
class RadiusAuthHandler {
public:

    /// Constructor.
    ///
    /// @param env The environment.
    /// @param callback Termination callback.
    RadiusAuthHandler(RadiusAuthEnv env, const CallbackAuth& callback);

    /// Destructor.
    virtual ~RadiusAuthHandler() = default;

    /// @brief Start communication.
    void start();

    /// @brief Environment.
    RadiusAuthEnv env_;

protected:

    /// @brief Pointer to the communication class.
    RadiusAsyncAuthPtr auth_;
};

/// @brief Type of pointers to Radius access communication handler.
typedef boost::shared_ptr<RadiusAuthHandler> RadiusAuthHandlerPtr;

/// @brief Radius access class.
class RadiusAccess : public RadiusService {
public:

    /// @brief Constructor.
    RadiusAccess();

    /// @brief Destructor.
    virtual ~RadiusAccess() = default;

    /// @brief Get Identifier -- IPv4.
    ///
    /// @param query The query packet.
    /// @param[out] id A reference to the identifier.
    /// @param[out] text A reference to the User Name.
    /// @return true if succeeded, false if something went wrong.
    bool getIdentifier(dhcp::Pkt4& query, std::vector<uint8_t>& id,
                       std::string& text);

    /// @brief Get Identifier -- IPv6.
    ///
    /// @param query The query packet.
    /// @param[out] id A reference to the identifier.
    /// @param[out] text A reference to the User Name.
    /// @return true if succeeded, false if something went wrong.
    bool getIdentifier(dhcp::Pkt6& query, std::vector<uint8_t>& id,
                       std::string& text);

    /// @brief Build RadiusAuth handler for Access-Request - IPv4.
    ///
    /// @param query The query packet.
    /// @param subnet_id The subnet ID.
    /// @param id The identifier.
    /// @param text The User Name.
    /// @return RadiusAuth handler.
    RadiusAuthHandlerPtr buildAuth(dhcp::Pkt4& query, uint32_t subnet_id,
                                   const std::vector<uint8_t>& id,
                                   const std::string& text);

    /// @brief Build RadiusAuth handler for Access-Request - IPv6.
    ///
    /// @param query The query packet.
    /// @param subnet_id The subnet ID.
    /// @param id The identifier.
    /// @param text The User Name.
    /// @return RadiusAuth handler.
    RadiusAuthHandlerPtr buildAuth(dhcp::Pkt6& query, uint32_t subnet_id,
                                   const std::vector<uint8_t>& id,
                                   const std::string& text);

    /// @brief Subnet reselect - class/pool IPv4
    ///
    /// First check if the subnet has a pool matching (no guard or
    /// a guard equal to the class) the class from Framed-Pool attribute.
    /// If not rerun the subnet selection process on the collection
    /// of subnets with such pool and update the subnet ID reference
    /// (can be updated to SUBNET_ID_UNUSED if no subnet can be reselected).
    ///
    /// @param query The query packet.
    /// @param[out] subnet_id The selected subnet ID.
    /// @param cclass The client class name.
    /// @param[out] both_global True when both selected and reselected subnets
    /// use global reservations.
    /// @return true if reselected, false if not.
    static bool reselectSubnet(const dhcp::Pkt4Ptr& query, uint32_t& subnet_id,
                               bool& both_global, const std::string& cclass);

    /// @brief Subnet reselect - class/pool IPv6
    ///
    /// First check if the subnet has a pool matching (no guard or
    /// a guard equal to the class) the class from Framed-Pool attribute.
    /// If not rerun the subnet selection process on the collection
    /// of subnets with such pool and update the subnet ID reference
    /// (can be updated to SUBNET_ID_UNUSED if no subnet can be reselected).
    ///
    /// @param query The query packet.
    /// @param[out] subnet_id The selected subnet ID.
    /// @param cclass The client class name.
    /// @param[out] both_global True when both selected and reselected subnets
    /// use global reservations.
    /// @return true if reselected, false if not.
    static bool reselectSubnet(const dhcp::Pkt6Ptr& query, uint32_t& subnet_id,
                               bool& both_global, const std::string& cclass);

    /// @brief Subnet reselect - reserved address IPv4
    ///
    /// First check if the reserved address matches the subnet range.
    /// If not rerun the subnet selection process on the collection
    /// of subnets with such range and update the subnet ID reference
    /// (can be updated to SUBNET_ID_UNUSED if no subnet can be reselected).
    ///
    /// @param query The query packet.
    /// @param[out] subnet_id The selected subnet ID.
    /// @param address The reserved address.
    /// @param[out] both_global True when both selected and reselected subnets
    /// use global reservations.
    /// @return true if reselected, false if not.
    static bool reselectSubnet(const isc::dhcp::Pkt4Ptr& query,
                               uint32_t& subnet_id,
                               bool& both_global,
                               const asiolink::IOAddress& address);

    /// @brief Subnet reselect - reserved address IPv6
    ///
    /// First check if the reserved address matches the subnet range.
    /// If not rerun the subnet selection process on the collection
    /// of subnets with such range and update the subnet ID reference
    /// (can be updated to SUBNET_ID_UNUSED if no subnet can be reselected).
    ///
    /// @param query The query packet.
    /// @param[out] subnet_id The selected subnet ID.
    /// @param address The reserved address.
    /// @param[out] both_global True when both selected and reselected subnets
    /// use global reservations.
    /// @return true if reselected, false if not.
    static bool reselectSubnet(const isc::dhcp::Pkt6Ptr& query,
                               uint32_t& subnet_id,
                               bool& both_global,
                               const asiolink::IOAddress& address);

    /// @brief Termination callback - IPv4
    ///
    /// All post response processing is done here.
    ///
    /// @param env Communication environment.
    /// @param result return code.
    /// @param recv_attrs received attributes.
    static void terminate4(RadiusAuthEnv env, int result,
                           AttributesPtr recv_attrs);

    /// @brief Termination callback - IPv6
    ///
    /// All post response processing is done here.
    ///
    /// @param env Communication environment.
    /// @param result return code.
    /// @param recv_attrs received attributes.
    static void terminate6(RadiusAuthEnv env, int result,
                           AttributesPtr recv_attrs);

    /// @brief Termination callback body - IPv4
    ///
    /// @param env Communication environment.
    /// @param result return code.
    /// @param recv_attrs received attributes.
    /// @param[out] query the query.
    /// @param[out] drop the drop flag.
    static void terminate4Internal(RadiusAuthEnv& env, int result,
                                   AttributesPtr recv_attrs,
                                   dhcp::Pkt4Ptr& query, bool& drop);

    /// @brief Termination callback body - IPv6
    ///
    /// @param env Communication environment.
    /// @param result return code.
    /// @param recv_attrs received attributes.
    /// @param[out] query the query.
    /// @param[out] drop the drop flag.
    static void terminate6Internal(RadiusAuthEnv& env, int result,
                                   AttributesPtr recv_attrs,
                                   dhcp::Pkt6Ptr& query, bool& drop);

    /// @brief Pending RADIUS access requests - IPv4.
    RadiusAuthPendingRequests<dhcp::Pkt4Ptr> requests4_;

    /// @brief Pending RADIUS access requests - IPv6.
    RadiusAuthPendingRequests<dhcp::Pkt6Ptr> requests6_;

};

} // end of namespace isc::radius
} // end of namespace isc

#endif
