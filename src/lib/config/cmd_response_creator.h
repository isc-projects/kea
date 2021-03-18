// Copyright (C) 2021 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CMD__RESPONSE_CREATOR_H
#define CMD__RESPONSE_CREATOR_H

#include <http/response_creator.h>
#include <http/basic_auth_config.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace config {

/// @brief Concrete implementation of the HTTP response creator used
/// for processing API commands
///
/// See the documentation of the @ref isc::http::HttpResponseCreator for
/// the basic information how HTTP response creators are utilized by
/// the libkea-http library to generate HTTP responses.
///
/// This creator expects that received requests are encapsulated in the
/// @ref isc::http::PostHttpRequestJson objects. The generated responses
/// are encapsulated in the HttpResponseJson objects.
///
/// This class uses @ref CommandMgr singleton to process commands
/// conveyed in the HTTP body. The JSON responses returned by the manager
/// are placed in the body of the generated HTTP responses.
class CmdResponseCreator : public http::HttpResponseCreator {
public:

    /// @brief Constructor
    ///
    /// @param emulate_agent_response if true, responses for normal
    /// command outcomes are guaranteed to be wrapped in an Element::list.
    /// This emulates how kea-ctrl-agent forms responses.  Defaults to true.
    CmdResponseCreator(bool emulate_agent_response = true)
    : emulate_agent_response_(emulate_agent_response) {};

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

    /// @brief Fetches the current authentication configuration.
    ///
    /// @todo The constructor will have to accept either a pointer
    /// to the authorization config to use, or a pointer to a function to
    /// return the authorization config.  For now we just return an empty
    /// pointer.
    ///
    /// @return an empty HttpAuthConfigPtr.
    const http::HttpAuthConfigPtr& getHttpAuthConfig() {
        static http::HttpAuthConfigPtr no_config;
        return (no_config);
    }

    /// @brief Indicates whether or not agent response emulation is enabled.
    ///
    /// @return true if emulation is enabled.
    bool emulateAgentResponse() {
        return (emulate_agent_response_);
    }

private:

    /// @brief Creates un-finalized stock HTTP response.
    ///
    /// The un-finalized response is the response that can't be sent over the
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

    /// @brief Determines whether or not responses are enclosed in an Element::list.
    /// Currently kea-ctrl-agent wraps all responses in a list, as it may have
    /// response from more than one server.  If this is true, we'll ensure
    /// responses (other than error responses) are in a list.
    bool emulate_agent_response_;
};

/// @brief Pointer to the @ref CmdResponseCreator.
typedef boost::shared_ptr<CmdResponseCreator> CmdResponseCreatorPtr;

} // end of namespace isc::config
} // end of namespace isc

#endif
