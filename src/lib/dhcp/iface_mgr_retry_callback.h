// Copyright (C) 2011-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef IFACE_MGR_RETRY_CALLBACK_H
#define IFACE_MGR_RETRY_CALLBACK_H

#include <functional>
#include <dhcp/iface_mgr.h>

namespace isc {
namespace dhcp {

/// @brief An helper to call a function with retry.
///
/// There are certain cases when IfaceMgr may hit an error caused by
/// temporary extarnal factors. A typical case is the function which opens
/// sockets on available interfaces for a DHCP server. If this function
/// fails to open a socket on a specific interface (for example, there is
/// another socket already open on this interface and bound to the same address
/// and port), it may be helpful to repeat an opening procedure.
/// It is allowed that the error handler function is not installed (is NULL).
/// In these cases it is expected that the function is just called without retrying.
///
/// @param f A function to call; template type T is an output type of this function.
/// @param msg A message intended to log with a failed attempt.
/// @param retry_callback A retry callback that decides to continue retries and wait
/// time before next try. It should also log the info/warning message.
template <typename T>
T callWithRetry(std::function<T()> f,
                const std::string& msg,
                IfaceMgrRetryCallback retry_callback) {

    // If the retry callback is NULL, just call the function and return.
    if (retry_callback == nullptr) {
        return f();
    }

    // Counter of the retries.
    uint64_t retries = 0;

    // Leave the loop on success (return statement)
    // or stop retrying (throw statement).
    while (true) {
        try {
            return f();
        } catch (const Exception& ex) {
            std::stringstream message(msg);
            message << ", reason: " << ex.what();
            auto retry_msg = message.str();

            // Callback produces a log message
            const std::pair<bool, uint64_t>& result = retry_callback(retries++, retry_msg);

            bool should_retry = result.first;
            uint64_t wait_time = result.second;

            if (!should_retry) {
                throw;
            } else {
                // Wait before next attempt. The initialization cannot end before
                // opening a socket so we can wait in the foreground.
                std::this_thread::sleep_for(std::chrono::milliseconds(wait_time));
            }
        }
    }
}

}
}

#endif // IFACE_MGR_RETRY_CALLBACK_H
