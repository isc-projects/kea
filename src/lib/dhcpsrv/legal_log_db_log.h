// Copyright (C) 2018-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef LEGAL_LOG_DB_LOG_H
#define LEGAL_LOG_DB_LOG_H

#include <database/db_log.h>

#include <boost/noncopyable.hpp>

namespace isc {
namespace dhcp {

/// @brief Legal log database logger class in RAII style
class LegalLogDbLogger : boost::noncopyable {
public:
    /// @brief Constructor
    ///
    /// Push the legal log database logger on the database logger stack.
    ///
    LegalLogDbLogger(isc::db::DbLogger& legal_log_db_logger);

    /// @brief Destructor
    ///
    /// Pop the legal log database logger from the database logger stack.
    ///
    ~LegalLogDbLogger();
};

} // namespace dhcp
} // namespace isc

#endif // LEGAL_LOG_DB_LOG_H
