// Copyright (C) 2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef IO_SERVICE_MGR_H
#define IO_SERVICE_MGR_H

#include <asiolink/io_service.h>

#include <boost/noncopyable.hpp>

namespace isc {
namespace asiolink {

class IOServiceMgr;

/// @brief Class which handles events on IOService objects.
///
/// Usually hook libraries create a local IOService object which handles events
/// related to the respective library. To be able to handle these events, the
/// IOService objects need to be registered on the '[X]_srv_configured' or
/// on 'load' hook points (before the MT settings are applied).
/// This class is not thread safe, so all operations must be done on the main
/// thread, while all other threads are either stopped or paused.
class IOServiceMgr : boost::noncopyable {
public:

    /// @brief Access the IOServiceMgr singleton instance.
    ///
    /// @return the singleton instance.
    static IOServiceMgr& instance();

    /// @brief Register IOService.
    ///
    /// Registering a null IOService does nothing.
    /// One IOService object can be registered only once, all consecutive calls
    /// using the same object will be silently ignored.
    ///
    /// @param io_service The IOService to be registered.
    void registerIOService(IOServicePtr io_service);

    /// @brief Unregister IOService.
    ///
    /// Unregistering an non registered IOService object will be silently
    /// ignored.
    ///
    /// @param io_service The IOService to be unregistered.
    void unregisterIOService(IOServicePtr io_service);

    /// @brief Clear the list of IOService objects.
    void clearIOServices() {
        io_services_.clear();
    }

    /// @brief The count of IOService objects.
    ///
    // @return The count of IOService objects.
    size_t getIOServiceCount() {
        return (io_services_.size());
    }

    /// @brief Poll IOService objects.
    void pollIOServices();

private:

    /// @brief Constructor.
    IOServiceMgr() = default;

    /// @brief Destructor.
    ~IOServiceMgr() = default;

    /// @brief The list of IOService objects.
    std::list<IOServicePtr> io_services_;
};

} // namespace asiolink
} // namespace isc

#endif // IO_SERVICE_MGR_H
