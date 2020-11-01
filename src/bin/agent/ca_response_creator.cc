// Copyright (C) 2017-2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <agent/ca_cfg_mgr.h>
#include <agent/ca_command_mgr.h>
#include <agent/ca_controller.h>
#include <agent/ca_process.h>
#include <agent/ca_response_creator.h>
#include <cc/data.h>
#include <hooks/callout_handle.h>
#include <hooks/hooks_log.h>
#include <hooks/hooks_manager.h>
#include <http/post_request_json.h>
#include <http/response_json.h>
#include <boost/pointer_cast.hpp>
#include <iostream>

using namespace isc::data;
using namespace isc::hooks;
using namespace isc::http;

namespace {

/// Structure that holds registered hook indexes.
struct CtrlAgentHooks {
    int hook_index_auth_;     ///< index of "auth" hook point.
    int hook_index_response_; ///< index of "response" hook point.

    /// Constructor that registers hook points.
    CtrlAgentHooks() {
        hook_index_auth_ = HooksManager::registerHook("auth");
        hook_index_response_ = HooksManager::registerHook("response");
    }
};

} // end of anonymous namespace.

// Declare a Hooks object. As this is outside any function or method, it
// will be instantiated (and the constructor run) when the module is loaded.
// As a result, the hook indexes will be defined before any method in this
// module is called.
CtrlAgentHooks Hooks;

namespace isc {
namespace agent {

HttpRequestPtr
CtrlAgentResponseCreator::createNewHttpRequest() const {
    return (HttpRequestPtr(new PostHttpRequestJson()));
}

HttpResponsePtr
CtrlAgentResponseCreator::
createStockHttpResponse(const HttpRequestPtr& request,
                        const HttpStatusCode& status_code) const {
    HttpResponsePtr response = createStockHttpResponseInternal(request, status_code);
    response->finalize();
    return (response);
}

HttpResponsePtr
CtrlAgentResponseCreator::
createStockHttpResponseInternal(const HttpRequestPtr& request,
                                const HttpStatusCode& status_code) const {
    // The request hasn't been finalized so the request object
    // doesn't contain any information about the HTTP version number
    // used. But, the context should have this data (assuming the
    // HTTP version is parsed ok).
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
    return (response);
}

HttpResponsePtr
CtrlAgentResponseCreator::
createDynamicHttpResponse(HttpRequestPtr request) {
    // First check authentication.
    HttpResponseJsonPtr http_response;

    // Context will hold the server configuration.
    CtrlAgentCfgContextPtr ctx;

    // There is a hierarchy of the objects through which we need to pass to get
    // the configuration context. We may simplify this at some point but since
    // we're in the singleton we want to make sure that we're using most current
    // configuration.
    boost::shared_ptr<CtrlAgentController> controller =
        boost::dynamic_pointer_cast<CtrlAgentController>(CtrlAgentController::instance());
    if (controller) {
        CtrlAgentProcessPtr process = controller->getCtrlAgentProcess();
        if (process) {
            CtrlAgentCfgMgrPtr cfgmgr = process->getCtrlAgentCfgMgr();
            if (cfgmgr) {
                ctx = cfgmgr->getCtrlAgentCfgContext();
                if (ctx) {
                    const HttpAuthConfigPtr& auth = ctx->getAuthConfig();
                    if (auth) {
                        // Check authentication.
                        http_response = auth->checkAuth(*this, request);
                    }
                }
            }
        }
    }

    // Callout point for "auth".
    if (HooksManager::calloutsPresent(Hooks.hook_index_auth_)) {
        // Get callout handle.
        CalloutHandlePtr callout_handle = request->getCalloutHandle();
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        // Pass arguments.
        callout_handle->setArgument("request", request);
        callout_handle->setArgument("response", http_response);

        // Call callouts.
        HooksManager::callCallouts(Hooks.hook_index_auth_, *callout_handle);
        callout_handle->getArgument("request", request);
        callout_handle->getArgument("response", http_response);

        // Ignore status as the HTTP response is used instead.
    }

    // The basic HTTP authentication check or a callout failed and
    // left a response.
    if (http_response) {
        return (http_response);
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
    ConstElementPtr response = CtrlAgentCommandMgr::instance().processCommand(command);
    if (!response) {
        // Notify the client that we have a problem with our server.
        return (createStockHttpResponse(request, HttpStatusCode::INTERNAL_SERVER_ERROR));
    }
    // The response is ok, so let's create new HTTP response with the status OK.
    http_response = boost::dynamic_pointer_cast<
        HttpResponseJson>(createStockHttpResponseInternal(request, HttpStatusCode::OK));
    http_response->setBodyAsJson(response);
    http_response->finalize();

    // Callout point for "response".
    if (HooksManager::calloutsPresent(Hooks.hook_index_response_)) {
        // Get callout handle.
        CalloutHandlePtr callout_handle = request->getCalloutHandle();
        ScopedCalloutHandleState callout_handle_state(callout_handle);

        // Pass arguments.
        callout_handle->setArgument("request", request);
        callout_handle->setArgument("response", http_response);

        // Call callouts.
        HooksManager::callCallouts(Hooks.hook_index_response_,
                                   *callout_handle);
        callout_handle->getArgument("response", http_response);

        // Ignore status as the HTTP response is used instead.
    }

    return (http_response);
}

} // end of namespace isc::agent
} // end of namespace isc
