// Copyright (C) 2018 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef ISC_WATCHER_H
#define ISC_WATCHER_H

#include <config.h>

#include <boost/shared_ptr.hpp>
#include <cc/data.h>
#include <yang/sysrepo_connection.h>

namespace isc {
namespace yang {

/// @brief This represents a base class for all watchers.
///
/// Isc_Watcher is an object that receives callback notification
/// from sysrepo (in YANG format) and converts it to appropriate
/// JSON that can be sent over control channel and understood by Kea.
class Watcher {
public:
    // @brief Constructor (requires xpath to install a callback).
    //
    // @param connection The sysrepo connection.
    // @param xpath The xpath to watch to.
    Watcher(SysrepoConnection& connection, const std::string& xpath);

    // @brief Destructor (doing nothing).
    virtual ~Watcher();

    // @brief Get the xpath.
    // @return The xpath to watch to.
    virtual const std::string& getXPath() const;

    // This method will be called when the callback returns.
    // Need to figure out the type used.
    //
    // @param data The yang data.
    void setYangData(void* data);

    // @brief This method translates Netconf data to JSON format
    // understood by Kea.
    virtual void translate() = 0;

    // @brief Get JSON once setYangData is called,
    // @return The JSON representation of the yang data.
    isc::data::ElementPtr getJSON();

protected:
    // @brief The xpath to watch to.
    const std::string& xpath_;

    // @brief The yang data.
    void* netconf_data_;

    // @brief The JSON representation of the yang data.
    isc::data::ElementPtr json_;

    // @brief The sysrepo connection.
    SysrepoConnection &connection_;
};

/// @brief The type of shared pointers to watcher objects.
typedef boost::shared_ptr<Watcher> WatcherPtr;

}  // namespace isc::yang
}  // namespace isc

#endif /* ISC_WATCHER_H */
