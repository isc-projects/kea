// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file
/// @brief Basic HTTP Authentication callout library

#include <config.h>

#include <cc/command_interpreter.h>
#include <cc/data.h>
#include <exceptions/exceptions.h>
#include <hooks/hooks.h>
#include <http/basic_auth_config.h>
#include <http/post_request_json.h>
#include <http/response_creator.h>
#include <boost/shared_ptr.hpp>
#include <boost/pointer_cast.hpp>

using namespace isc::data;
using namespace isc::hooks;
using namespace isc::http;
using namespace isc;
using namespace std;

namespace {

/// @brief Response creator.
class ResponseCreator : public HttpResponseCreator {
public:
    /// @brief Create a new request.
    /// @return Pointer to the new instance of the @ref
    /// isc::http::PostHttpRequestJson.
    virtual HttpRequestPtr
    createNewHttpRequest() const;

    /// @brief Create stock HTTP response.
    ///
    /// @param request Pointer to an object representing HTTP request.
    /// @param status_code Status code of the response.
    /// @return Pointer to an @ref isc::http::HttpResponseJson object
    /// representing stock HTTP response.
    virtual HttpResponsePtr
    createStockHttpResponse(const HttpRequestPtr& request,
                            const HttpStatusCode& status_code) const;

    /// @brief Creates implementation specific HTTP response.
    ///
    /// @param request Pointer to an object representing HTTP request.
    /// @return Pointer to an object representing HTTP response.
    virtual HttpResponsePtr
    createDynamicHttpResponse(HttpRequestPtr request);
};

HttpRequestPtr
ResponseCreator::createNewHttpRequest() const {
    return (HttpRequestPtr(new PostHttpRequestJson()));
}

HttpResponsePtr
ResponseCreator::createStockHttpResponse(const HttpRequestPtr& /*request*/,
                                         const HttpStatusCode& status_code) const {
    HttpVersion http_version(1, 1);
    HttpResponsePtr response(new HttpResponseJson(http_version, status_code));
    response->finalize();
    return (response);
}

HttpResponsePtr
ResponseCreator::createDynamicHttpResponse(HttpRequestPtr /*request*/) {
    isc_throw(NotImplemented, "createDynamicHttpResponse should not be called");
}

/// @brief The type of shared pointers to response creators.
typedef boost::shared_ptr<ResponseCreator> ResponseCreatorPtr;

/// @brief Implementation.
class Impl {
public:

    /// @brief Constructor.
    Impl();

    /// @brief Destructor.
    ~Impl();

    /// @brief Configure.
    ///
    /// @param config element pointer to client list.
    void configure(ConstElementPtr config);

    /// @brief Basic HTTP authentication configuration.
    BasicHttpAuthConfigPtr config_;

    /// @brief Response creator.
    ResponseCreatorPtr creator_;
};

Impl::Impl()
    : config_(new BasicHttpAuthConfig()), creator_(new ResponseCreator()) {
}

Impl::~Impl() {
}

void
Impl::configure(ConstElementPtr config) {
    config_->parse(config);
}

/// @brief The type of shared pointers to implementations.
typedef boost::shared_ptr<Impl> ImplPtr;

/// @brief The implementation.
ImplPtr impl;

extern "C" {

// Framework functions.

/// @brief returns Kea hooks version.
int
version() {
    return (KEA_HOOKS_VERSION);
}

/// @brief This function is called when the library is loaded.
///
/// @param handle library handle.
/// @return 0 when initialization is successful, 1 otherwise.
int
load(LibraryHandle& handle) {
#ifdef USE_STATIC_LINK
    hooksStaticLinkInit();
#endif
    try {
        impl.reset(new Impl());
        ConstElementPtr config = handle.getParameter("config");
        impl->configure(config);
    } catch (const std::exception& ex) {
        std::cerr << "load error: " << ex.what() << std::endl;
        return (1);
    }

    return (0);
}

/// @brief This function is called when the library is unloaded.
///
/// @return always 0.
int
unload() {
    impl.reset();
    return (0);
}

// Callout functions.

/// @brief This callout is called at the "auth" hook.
///
/// @param handle CalloutHandle.
/// @return 0 upon success, non-zero otherwise.
int
auth(CalloutHandle& handle) {
    // Sanity.
    if (!impl) {
        std::cerr << "no implementation" << std::endl;
        return (0);
    }

    // Get the parameters.
    HttpRequestPtr request;
    HttpResponseJsonPtr response;
    handle.getArgument("request", request);
    handle.getArgument("response", response);

    if (response) {
        std::cerr << "response already set" << std::endl;
        return (0);
    }
    if (!request) {
        std::cerr << "no request" << std::endl;
        return (0);
    }
    PostHttpRequestJsonPtr request_json =
        boost::dynamic_pointer_cast<PostHttpRequestJson>(request);
    if (!request_json) {
        std::cerr << "no json post request" << std::endl;
        return (0);
    }
    ConstElementPtr command = request_json->getBodyAsJson();
    if (!command) {
        std::cerr << "no command" << std::endl;
        return (0);
    }
    if (command->getType() != Element::map) {
        std::cerr << "command is not a map" << std::endl;
        return (0);
    }

    // Modify request.
    int extra = 0;
    ConstElementPtr extra_elem = command->get("extra");
    ElementPtr mutable_command = boost::const_pointer_cast<Element>(command);
    if (extra_elem) {
        if (extra_elem->getType() == Element::integer) {
            extra = extra_elem->intValue();
        }
        mutable_command->remove("extra");
        request_json->setBodyAsJson(command);
    }
    handle.setContext("extra", extra);

    // Perform authentication.
    response = impl->config_->checkAuth(*impl->creator_, request);

    // Set parameters.
    handle.setArgument("request", request);
    handle.setArgument("response", response);
    return (0);
}

/// @brief This callout is called at the "response" hook.
///
/// @param handle CalloutHandle.
/// @return 0 upon success, non-zero otherwise.
int
response(CalloutHandle& handle) {
    // Sanity.
    if (!impl) {
        std::cerr << "no implementation" << std::endl;
        return (0);
    }

    // Get the parameters.
    HttpRequestPtr request;
    HttpResponseJsonPtr response;
    handle.getArgument("request", request);
    handle.getArgument("response", response);

    if (!request) {
        std::cerr << "no request" << std::endl;
        return (0);
    }
    if (!response) {
        std::cerr << "no response" << std::endl;
        return (0);
    }

    // Modify response.
    ConstElementPtr body = response->getBodyAsJson();
    if (!body) {
        std::cerr << "no body" << std::endl;
        return (0);
    }
    if (body->getType() != Element::list) {
        std::cerr << "body is not a list" << std::endl;
        return (0);
    }
    if (body->size() < 1) {
        std::cerr << "body is empty" << std::endl;
        return (0);
    }
    ConstElementPtr answer = body->get(0);
    if (!answer || (answer->getType() != Element::map)) {
        std::cerr << "answer is not map" << std::endl;
        return (0);
    }
    ElementPtr mutable_answer = boost::const_pointer_cast<Element>(answer);
    try {
        int extra = 0;
        handle.getContext("extra", extra);
        mutable_answer->set("got", Element::create(extra));
    } catch (const NoSuchCalloutContext&) {
        std::cerr << "can't find 'extra' context\n";
    } catch (...) {
        std::cerr << "getContext('extra') failed\n";
    }
    response->setBodyAsJson(body);

    // Set parameters.
    handle.setArgument("response", response);
    return (0);
}

}
}
