// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_HEADER_CONTEXT_H
#define HTTP_HEADER_CONTEXT_H

#include <string>

namespace isc {
namespace http {

struct HttpHeaderContext {
    std::string name_;
    std::string value_;
};

} // namespace http
} // namespace isc

#endif
