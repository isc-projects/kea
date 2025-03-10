// Copyright (C) 2021-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <config/http_command_response_creator.h>
#include <config/command_mgr.h>
#include <config/config_log.h>
#include <hooks/callout_handle.h>
#include <hooks/hooks_log.h>
#include <hooks/hooks_manager.h>
#include <http/post_request_json.h>
#include <http/response_json.h>
#include <boost/pointer_cast.hpp>
#include <iostream>

using namespace isc::config;
using namespace isc::data;
using namespace isc::hooks;
using namespace isc::http;
using namespace std;

namespace {

/// Structure that holds registered hook indexes.
struct HttpCommandHooks {
    int hook_index_http_auth_;     ///< index of "http_auth" hook point.
    int hook_index_http_response_; ///< index of "http_response" hook point.

    /// Constructor that registers hook points.
    HttpCommandHooks() {
        hook_index_http_auth_ = HooksManager::registerHook("http_auth");
        hook_index_http_response_ = HooksManager::registerHook("http_response");
    }
};

} // end of anonymous namespace.

// Declare a Hooks object. As this is outside any function or method, it
// will be instantiated (and the constructor run) when the module is loaded.
// As a result, the hook indexes will be defined before any method in this
// module is called.
HttpCommandHooks Hooks;

namespace isc {
namespace config {

HttpRequestPtr
HttpCommandResponseCreator::createNewHttpRequest() const {
    return (HttpRequestPtr(new PostHttpRequestJson()));
}

HttpResponsePtr
HttpCommandResponseCreator::
createStockHttpResponse(const HttpRequestPtr& request,
                        const HttpStatusCode& status_code) const {
    HttpResponsePtr response = createStockHttpResponseInternal(request, status_code);
    response->finalize();
    return (response);
}

HttpResponsePtr
HttpCommandResponseCreator::
createStockHttpResponseInternal(const HttpRequestPtr& request,
                                const HttpStatusCode& status_code) const {
    // The request hasn't been finalized so the request object
    // doesn't contain any information about the HTTP version number
    // used. But, the context should have this data (assuming the
    // HTTP version is parsed OK).
    HttpVersion http_version(request->context()->http_version_major_,
                             request->context()->http_version_minor_);
    // We only accept HTTP version 1.0 or 1.1. If other version number is found
    // we fall back to HTTP/1.0.
    if ((http_version < HttpVersion(1, 0)) || (HttpVersion(1, 1) < http_version)) {
        http_version.major_ = 1;
        http_version.minor_ = 0;
    }
    // This will generate the response holding JSON content.
    HttpResponsePtr response(new HttpResponseJson(http_version, status_code));
    // Add extra headers.
    if (config_) {
        copyHttpHeaders(config_->getHttpHeaders(), *response);
    }
    return (response);
}

HttpResponsePtr
HttpCommandResponseCreator::createDynamicHttpResponse(HttpRequestPtr request) {
    CfgHttpHeaders headers;
    HttpResponseJsonPtr http_response;

    // Check the basic HTTP authentication.
    if (config_) {
        headers = config_->getHttpHeaders();
        const HttpAuthConfigPtr& auth = config_->getAuthConfig();
        if (auth) {
            http_response = auth->checkAuth(*this, request);
        }
    }

    // Pass extra headers to the hook.
    bool auth_failed = false;
    if (http_response) {
        auth_failed = true;
        copyHttpHeaders(headers, *http_response);
    }

    // Callout point for "http_auth".
    bool reset_handle = false;
    if (HooksManager::calloutsPresent(Hooks.hook_index_http_auth_)) {
        // Get callout handle.
        CalloutHandlePtr callout_handle = request->getCalloutHandle();
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        // Pass arguments.
        callout_handle->setArgument("request", request);
        callout_handle->setArgument("response", http_response);

        // Call callouts.
        HooksManager::callCallouts(Hooks.hook_index_http_auth_,
                                   *callout_handle);
        callout_handle->getArgument("request", request);
        callout_handle->getArgument("response", http_response);

        // Status other than continue means 'please reset the handle'.
        if (callout_handle->getStatus() != CalloutHandle::NEXT_STEP_CONTINUE) {
            reset_handle = true;
        }
    }

    // The basic HTTP authentication check or a callout failed and
    // left a response.
    if (http_response) {
        // Avoid to copy extra headers twice even this should not be required.
        if (!auth_failed && !headers.empty()) {
            copyHttpHeaders(headers, *http_response);
            if (http_response->isFinalized()) {
                // Argh! The response was already finalized.
                http_response->reset();
                http_response->finalize();
            }
        }
        return (http_response);
    }

    // Reset the handle when a hook asks for.
    if (reset_handle) {
        request->resetCalloutHandle();
    }

    // The request is always non-null, because this is verified by the
    // createHttpResponse method. Let's try to convert it to the
    // PostHttpRequestJson type as this is the type generated by the
    // createNewHttpRequest. If the conversion result is null it means that
    // the caller did not use createNewHttpRequest method to create this
    // instance. This is considered an error in the server logic.
    PostHttpRequestJsonPtr request_json =
        boost::dynamic_pointer_cast<PostHttpRequestJson>(request);
    if (!request_json) {
        // Notify the client that we have a problem with our server.
        return (createStockHttpResponse(request, HttpStatusCode::INTERNAL_SERVER_ERROR));
    }

    // We have already checked that the request is finalized so the call
    // to getBodyAsJson must not trigger an exception.
    ConstElementPtr command = request_json->getBodyAsJson();

    // Process command doesn't generate exceptions but can possibly return
    // null response, if the handler is not implemented properly. This is
    // again an internal server issue.
    ConstElementPtr response = config::CommandMgr::instance().processCommand(command);

    if (!response) {
        // Notify the client that we have a problem with our server.
        return (createStockHttpResponse(request, HttpStatusCode::INTERNAL_SERVER_ERROR));
    }

    // Normal Responses coming from the Kea server must always be wrapped in
    // a list as they may contain responses from multiple daemons.
    // If we're emulating that for backward compatibility, then we need to wrap
    // the answer in a list if it isn't in one already.
    if ((!config_ || config_->getEmulateAgentResponse()) &&
        (response->getType() != Element::list)) {
        ElementPtr response_list = Element::createList();
        response_list->add(boost::const_pointer_cast<Element>(response));
        response = response_list;
    }

    // The response is OK, so let's create new HTTP response with the status OK.
    http_response = boost::dynamic_pointer_cast<
        HttpResponseJson>(createStockHttpResponseInternal(request, HttpStatusCode::OK));
    http_response->setBodyAsJson(response);
    http_response->finalize();

    // Callout point for "http_response".
    if (HooksManager::calloutsPresent(Hooks.hook_index_http_response_)) {
        // Get callout handle.
        CalloutHandlePtr callout_handle = request->getCalloutHandle();
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        // Pass arguments.
        callout_handle->setArgument("request", request);
        callout_handle->setArgument("response", http_response);

        // Call callouts.
        HooksManager::callCallouts(Hooks.hook_index_http_response_,
                                   *callout_handle);
        callout_handle->getArgument("response", http_response);

        // Ignore status as the HTTP response is used instead.
    }

    return (http_response);
}

} // end of namespace isc::config
} // end of namespace isc
