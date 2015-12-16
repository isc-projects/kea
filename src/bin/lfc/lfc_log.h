// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LFC_LOG_H
#define LFC_LOG_H

#include <log/logger_support.h>
#include <log/macros.h>
#include <lfc/lfc_messages.h>

namespace isc {
namespace lfc {

/// Define the logger for the "lfc" logging.
extern isc::log::Logger lfc_logger;


} // namespace lfc
} // namespace isc

#endif // LFC_LOG_H
