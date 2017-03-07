// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CTRL_AGENT_RESPONSE_CREATOR_FACTORY_H
#define CTRL_AGENT_RESPONSE_CREATOR_FACTORY_H

#include <agent/ca_response_creator.h>
#include <http/response_creator_factory.h>

namespace isc {
namespace agent {

/// @brief HTTP response creator factory for Control Agent.
///
/// See the documentation of the @ref isc::http::HttpResponseCreatorFactory
/// for the details how the response factory object is used by the
/// @ref isc::http::HttpListener.
///
/// This class always returns the same instance of the
/// @ref CtrlAgentResponseCreator which @ref isc::http::HttpListener and
/// @ref isc::http::HttpConnection classes use to generate HTTP response
/// messages which comply with the formats required by the Control Agent.
class CtrlAgentResponseCreatorFactory : public http::HttpResponseCreatorFactory {
public:

    /// @brief Constructor.
    ///
    /// Creates sole instance of the @ref CtrlAgentResponseCreator object
    /// returned by the @ref CtrlAgentResponseCreatorFactory::create.
    CtrlAgentResponseCreatorFactory()
        : sole_creator_(new CtrlAgentResponseCreator()) {
    }

    /// @brief Returns an instance of the @ref CtrlAgentResponseCreator which
    /// is used by HTTP server to generate responses to commands.
    ///
    /// @return Pointer to the @ref CtrlAgentResponseCreator object.
    virtual http::HttpResponseCreatorPtr create() const {
        return (sole_creator_);
    }

private:

    /// @brief Instance of the @ref CtrlAgentResponseCreator returned.
    http::HttpResponseCreatorPtr sole_creator_;

};

} // end of namespace isc::agent
} // end of namespace isc

#endif
