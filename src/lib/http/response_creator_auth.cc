// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <http/http_log.h>
#include <http/response_creator_auth.h>
#include <util/strutil.h>

using namespace isc;
using namespace isc::util;
using namespace std;

namespace isc {
namespace http {

HttpResponseJsonPtr checkAuth(const HttpResponseCreator& creator,
                              const ConstHttpRequestPtr& request,
                              const BasicHttpAuthMap& credentials,
                              const std::string& realm) {
    bool authentic = false;
    if (credentials.empty()) {
        authentic = true;
    } else try {
        string value = request->getHeaderValue("Authorization");
        // Trim space characters.
        value = str::trim(value);
        if (value.size() < 8) {
            isc_throw(BadValue, "header content is too short");
        }
        // Get the authentication scheme which must be "basic".
        string scheme = value.substr(0, 5);
        str::lowercase(scheme);
        if (scheme != "basic") {
            isc_throw(BadValue, "not basic authentication");
        }
        // Skip the authentication scheme name and space characters.
        value = value.substr(5);
        value = str::trim(value);
        // Verify the credential is in the list.
        const auto it = credentials.find(value);
        if (it != credentials.end()) {
            LOG_DEBUG(http_logger, isc::log::DBGLVL_TRACE_BASIC,
                      HTTP_CLIENT_REQUEST_AUTHORIZED)
                .arg(it->second);
            authentic = true;
        } else {
            LOG_INFO(http_logger, HTTP_CLIENT_REQUEST_NOT_AUTHORIZED);
            authentic = false;
        }
    } catch (const HttpMessageNonExistingHeader&) {
        LOG_INFO(http_logger, HTTP_CLIENT_REQUEST_NO_AUTH_HEADER);
    } catch (const BadValue& ex) {
        LOG_INFO(http_logger, HTTP_CLIENT_REQUEST_BAD_AUTH_HEADER)
            .arg(ex.what());
    }
    if (authentic) {
        return (HttpResponseJsonPtr());
    }
    string scheme = "Basic";
    HttpResponsePtr response =
        creator.createStockHttpResponse(request, HttpStatusCode::UNAUTHORIZED);
    response->reset();
    response->context()->headers_.push_back(
        HttpHeaderContext("WWW-Authenticate",
                          scheme + " realm=\"" + realm + "\""));
    response->finalize();
    return (boost::dynamic_pointer_cast<HttpResponseJson>(response));
}

} // end of namespace isc::http
} // end of namespace isc
