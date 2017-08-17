// Copyright (C) 2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef HTTP_LOG_H
#define HTTP_LOG_H

#include <log/logger_support.h>
#include <log/macros.h>
#include <http/http_messages.h>

namespace isc {
namespace http {

/// Define the loggers used within libkea-http library.
extern isc::log::Logger http_logger;

} // namespace http
} // namespace isc

#endif // HTTP_LOG_H
