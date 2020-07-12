// Copyright (C) 2020 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_RESPONSE_CREATOR_AUTH_H
#define HTTP_RESPONSE_CREATOR_AUTH_H

#include <http/basic_auth_config.h>
#include <http/response_creator.h>
#include <http/response_json.h>
#include <string.h>
#include <unordered_map>

namespace isc {
namespace http {

/// @brief Validate basic HTTP authentication.
///
/// @param creator The HTTP response creator.
/// @param request The HTTP request to validate.
/// @param credentials Authorized credentials and user id map.
/// @param realm Realm name.
/// @return Error HTTP response if validation failed, null otherwise.
HttpResponseJsonPtr checkBasicHttpAuth(const HttpResponseCreator& creator,
                                       const ConstHttpRequestPtr& request,
                                       const BasicHttpAuthMap& credentials,
                                       const std::string& realm);

} // end of namespace isc::http
} // end of namespace isc

#endif // endif HTTP_RESPONSE_CREATOR_AUTH_H
