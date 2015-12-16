// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// Defines the logger used by the top-level component of kea-lfc.

#include <lfc/lfc_log.h>

namespace isc {
namespace lfc {

/// @brief Defines the logger used within LFC.
isc::log::Logger lfc_logger("DhcpLFC");

} // namespace lfc
} // namespace isc
