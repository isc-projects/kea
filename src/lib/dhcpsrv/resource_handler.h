// Copyright (C) 2020-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RESOURCE_HANDLER_H
#define RESOURCE_HANDLER_H

#include <asiolink/io_address.h>
#include <dhcpsrv/lease.h>

#include <boost/noncopyable.hpp>
#include <boost/multi_index_container.hpp>
#include <boost/multi_index/composite_key.hpp>
#include <boost/multi_index/hashed_index.hpp>
#include <boost/multi_index/member.hpp>
#include <boost/multi_index/mem_fun.hpp>
#include <boost/shared_ptr.hpp>

#include <mutex>

namespace isc {
namespace dhcp {

/// @brief Thrown by lock users when a resource lock cannot be obtained.
class ResourceBusy : public Exception {
public:
    ResourceBusy(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};

/// @brief Resource race avoidance RAII handler.
class ResourceHandler : public boost::noncopyable {
public:

    /// @brief Constructor.
    ResourceHandler();

    /// @brief Destructor.
    ///
    /// Releases owned resources.
    virtual ~ResourceHandler();

    /// @brief Tries to acquires a resource.
    ///
    /// Lookup the resource, if not found insert the resource
    /// in the resource container and return true, if found return false
    ///
    /// @param type Type of the resource, member of @c Lease::Type enum.
    /// @param addr The address or prefix aka the resource.
    /// @return true if the resource was acquired, false if the resource is
    /// busy i.e. owned by a handler.
    bool tryLock(Lease::Type type, const asiolink::IOAddress& addr);

    /// @brief Checks if a resource is owned by this handler.
    ///
    /// @param type Type of the resource, member of @c Lease::Type enum.
    /// @param addr The address or prefix aka the resource.
    /// @return true if this handler owns the resource, false otherwise.
    bool isLocked(Lease::Type type, const asiolink::IOAddress& addr);

    /// @brief Releases a resource.
    ///
    /// Remove the resource from the resource container.
    ///
    /// @param type Type of the resource, member of @c Lease::Type enum.
    /// @param addr The address or prefix aka the resource.
    /// @throw when we do not own the resource.
    void unLock(Lease::Type type, const asiolink::IOAddress& addr);

private:

    /// Type definitions.
    //@{

    /// @brief Structure representing a resource.
    struct Resource {

        /// @brief Constructor.
        ///
        /// @param addr The address or prefix aka the resource..
        Resource(Lease::Type type, const asiolink::IOAddress& addr)
            : type_(type), addr_(addr) {
        }

        /// @brief The type.
        Lease::Type type_;

        /// @brief The resource.
        asiolink::IOAddress addr_;

        /// @brief The key extractor.
        std::vector<uint8_t> toBytes() const {
            return (addr_.toBytes());
        }
    };

    /// @brief The type of shared pointers to resources.
    typedef boost::shared_ptr<Resource> ResourcePtr;

    /// @brief The type of the resource container.
    typedef boost::multi_index_container<

        // This container stores pointers to resource objects.
        ResourcePtr,

        // Start specification of indexes here.
        boost::multi_index::indexed_by<

            // First index is used to search by type and address.
            boost::multi_index::hashed_unique<
                boost::multi_index::composite_key<
                    Resource,
                    // Lease type.
                    boost::multi_index::member<
                        Resource, Lease::Type, &Resource::type_
                    >,
                    // Address bytes.
                    boost::multi_index::const_mem_fun<
                        Resource, std::vector<uint8_t>, &Resource::toBytes
                    >
                >
            >
        >
    > ResourceContainer;

    //@}

    /// Class members.
    //@{

    /// @brief The resource container.
    static ResourceContainer resources_;

    /// @brief Mutex to protect the resource container.
    static std::mutex mutex_;

    /// @brief Lookup a resource.
    ///
    /// The mutex must be held by the caller.
    ///
    /// @param type Type of the resource, member of @c Lease::Type enum.
    /// @param addr The address or prefix aka the resource.
    /// @return The busy resource or null.
    static ResourcePtr
    lookup(Lease::Type type, const asiolink::IOAddress& addr);

    //@}

    /// Instance members.
    //@{

    /// @brief Acquire a resource.
    ///
    /// The mutex must be held by the caller.
    ///
    /// @param type Type of the resource, member of @c Lease::Type enum.
    /// @param addr The address or prefix aka the resource.
    void lock(Lease::Type type, const asiolink::IOAddress& addr);

    /// @brief Release a resource.
    ///
    /// The mutex must be held by the caller.
    ///
    /// Remove the resource from the resource container.
    ///
    /// @param type Type of the resource, member of @c Lease::Type enum.
    /// @param addr The address or prefix aka the resource.
    void unLockInternal(Lease::Type type, const asiolink::IOAddress& addr);

    /// @brief List of resources this handler owns.
    ResourceContainer owned_;

    //@}
};

/// @brief Resource race avoidance RAII handler for DHCPv4.
class ResourceHandler4 : public ResourceHandler {
public:

    /// @brief Destructor.
    ///
    /// Releases owned resources.
    virtual ~ResourceHandler4() { }

    /// @brief Tries to acquires a resource.
    ///
    /// Lookup the resource, if not found insert the resource
    /// in the resource container and return true, if found return false
    ///
    /// @param addr The address aka the resource.
    /// @return true if the resource was acquired, false if the resource is
    /// busy i.e. owned by a handler.
    bool tryLock4(const asiolink::IOAddress& addr) {
        return (tryLock(Lease::TYPE_V4, addr));
    }

    /// @brief Checks if a resource is owned by this handler.
    ///
    /// @param addr The address aka the resource.
    /// @return true if this handler owns the resource, false otherwise.
    bool isLocked4(const asiolink::IOAddress& addr) {
        return (isLocked(Lease::TYPE_V4, addr));
    }

    /// @brief Releases a resource.
    ///
    /// Remove the resource from the resource container.
    ///
    /// @param addr The address aka the resource.
    /// @throw when we do not own the resource.
    void unLock4(const asiolink::IOAddress& addr) {
        unLock(Lease::TYPE_V4, addr);
    }
};

} // namespace isc
} // namespace dhcp

#endif // RESOURCE_HANDLER_H
