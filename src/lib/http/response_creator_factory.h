// Copyright (C) 2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_RESPONSE_CREATOR_FACTORY_H
#define HTTP_RESPONSE_CREATOR_FACTORY_H

#include <http/request.h>
#include <http/response.h>
#include <http/response_creator.h>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace http {

class HttpResponseCreatorFactory {
public:

    virtual ~HttpResponseCreatorFactory() { }

    virtual HttpResponseCreatorPtr create() const = 0;

};

typedef boost::shared_ptr<HttpResponseCreatorFactory>
HttpResponseCreatorFactoryPtr;

} // end of namespace isc::http
} // end of namespace isc

#endif
