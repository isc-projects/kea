// Copyright (C) 2023-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RADIUS_SERVICE_H
#define RADIUS_SERVICE_H

#include <cc/cfg_to_element.h>
#include <cc/data.h>
#include <client_server.h>
#include <cfg_attribute.h>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace radius {

/// @brief Radius service.
///
/// Radius offers two independent services: access/authorization and
/// accounting.
class RadiusService : public data::CfgToElement, public boost::noncopyable {
public:

    /// @brief Constructor.
    ///
    /// @param name service name.
    explicit RadiusService(const std::string& name);

    /// @brief Default destructor.
    virtual ~RadiusService() = default;

    /// @brief Unparse service configuration.
    ///
    /// @return a pointer to unparsed configuration.
    data::ElementPtr toElement() const override;

    /// @brief Name (access or accounting).
    std::string name_;

    /// @brief Enable flag.
    bool enabled_;

    /// @brief Peer updates flag.
    bool peer_updates_;

    /// @brief Server list.
    Servers servers_;

    /// @brief Attribute configurations.
    CfgAttributes attributes_;

    /// @brief Maximum number of pending requests.
    size_t max_pending_requests_;
};

/// @brief Type of pointers to Radius service.
typedef boost::shared_ptr<RadiusService> RadiusServicePtr;

} // end of namespace isc::radius
} // end of namespace isc

#endif
