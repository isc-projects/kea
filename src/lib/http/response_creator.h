// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_RESPONSE_CREATOR_H
#define HTTP_RESPONSE_CREATOR_H

#include <http/request.h>
#include <http/response.h>

namespace isc {
namespace http {

class HttpResponseCreator {
public:

    virtual ~HttpResponseCreator() { };

    virtual HttpResponsePtr create(const ConstHttpRequestPtr& request) = 0;

};

} // namespace http
} // namespace isc

#endif
