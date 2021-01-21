// Copyright (C) 2017-2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CTRL_AGENT_RESPONSE_CREATOR_H
#define CTRL_AGENT_RESPONSE_CREATOR_H

#include <agent/ca_command_mgr.h>
#include <http/response_creator.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace agent {

class CtrlAgentResponseCreator;

/// @brief Pointer to the @ref CtrlAgentResponseCreator.
typedef boost::shared_ptr<CtrlAgentResponseCreator> CtrlAgentResponseCreatorPtr;

/// @brief Concrete implementation of the HTTP response creator used
/// by the Control Agent.
///
/// See the documentation of the @ref isc::http::HttpResponseCreator for
/// the basic information how HTTP response creators are utilized by
/// the libkea-http library to generate HTTP responses.
///
/// This creator expects that received requests are encapsulated in the
/// @ref isc::http::PostHttpRequestJson objects. The generated responses
/// are encapsulated in the HttpResponseJson objects.
///
/// This class uses @ref CtrlAgentCommandMgr singleton to process commands
/// conveyed in the HTTP body. The JSON responses returned by the manager
/// are placed in the body of the generated HTTP responses.
class CtrlAgentResponseCreator : public http::HttpResponseCreator {
public:

    /// @brief Create a new request.
    ///
    /// This method creates a bare instance of the @ref
    /// isc::http::PostHttpRequestJson.
    ///
    /// @return Pointer to the new instance of the @ref
    /// isc::http::PostHttpRequestJson.
    virtual http::HttpRequestPtr createNewHttpRequest() const;

    /// @brief Creates stock HTTP response.
    ///
    /// @param request Pointer to an object representing HTTP request.
    /// @param status_code Status code of the response.
    /// @return Pointer to an @ref isc::http::HttpResponseJson object
    /// representing stock HTTP response.
    virtual http::HttpResponsePtr
    createStockHttpResponse(const http::HttpRequestPtr& request,
                            const http::HttpStatusCode& status_code) const;

private:

    /// @brief Creates unfinalized stock HTTP response.
    ///
    /// The unfinalized response is the response that can't be sent over the
    /// wire until @c finalize() is called, which commits the contents of the
    /// message body.
    ///
    /// @param request Pointer to an object representing HTTP request.
    /// @param status_code Status code of the response.
    /// @return Pointer to an @ref isc::http::HttpResponseJson object
    /// representing stock HTTP response.
   http::HttpResponsePtr
   createStockHttpResponseInternal(const http::HttpRequestPtr& request,
                                   const http::HttpStatusCode& status_code) const;

    /// @brief Creates implementation specific HTTP response.
    ///
    /// @param request Pointer to an object representing HTTP request.
    /// @return Pointer to an object representing HTTP response.
    virtual http::HttpResponsePtr
    createDynamicHttpResponse(http::HttpRequestPtr request);
};

} // end of namespace isc::agent
} // end of namespace isc

#endif
