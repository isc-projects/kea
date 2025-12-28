// Copyright (C) 2017-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>
#include <asiolink/asio_wrapper.h>
#include <tcp/tcp_client.h>

namespace isc {
namespace tcp {
namespace test {

/// @brief Completion checker.
///
/// Messages are by 2 byte length header and data of this length.
///
/// @param response Response to check.
/// @param error_msg Reference to the error message.
/// @return status (0 not complete, > 0 complete, < 0 error).
int
TestCompleteCheck(const WireDataPtr& response, std::string& error_msg) {
    if (!response) {
        error_msg = "response is null";
        return (-1);
    }
    size_t length = response->size();
    if (length < 2) {
        return (-2);
    }
    const std::vector<uint8_t>& content = *response;
    size_t wanted = (content[0] << 8) | content[1];
    if (wanted + 2 == response->size()) {
        // Complete.
        return (1);
    } else if (wanted + 2 > response->size()) {
        // Not complete.
        return (0);
    } else {
        // Overrun.
        error_msg = "overrun";
        return (-3);
    }
}

}
}
}
