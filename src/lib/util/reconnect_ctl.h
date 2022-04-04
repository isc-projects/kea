// Copyright (C) 2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RECONNECT_CTL_H
#define RECONNECT_CTL_H

#include <string>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace util {

/// @brief Type of action to take on connection loss.
enum class OnFailAction {
    STOP_RETRY_EXIT,
    SERVE_RETRY_EXIT,
    SERVE_RETRY_CONTINUE
};

/// @brief Warehouses reconnect control values
///
/// When any connection loses connectivity to its backend, it
/// creates an instance of this class based on its configuration parameters and
/// passes the instance into connection's lost callback.  This allows
/// the layer(s) above the connection to know how to proceed.
///
class ReconnectCtl {
public:
    /// @brief Constructor.
    ///
    /// @param backend_type type of the caller backend.
    /// @param timer_name timer associated to this object.
    /// @param max_retries maximum number of reconnect attempts to make.
    /// @param retry_interval amount of time to between reconnect attempts.
    /// @param action which should be taken on connection loss.
    ReconnectCtl(const std::string& backend_type, const std::string& timer_name,
                 unsigned int max_retries, unsigned int retry_interval,
                 OnFailAction action) :
          backend_type_(backend_type), timer_name_(timer_name),
          max_retries_(max_retries), retries_left_(max_retries),
          retry_interval_(retry_interval), action_(action) {}

    /// @brief Returns the type of the caller backend.
    std::string backendType() const {
        return (backend_type_);
    }

    /// @brief Returns the associated timer name.
    ///
    /// @return the associated timer.
    std::string timerName() const {
        return (timer_name_);
    }

    /// @brief Decrements the number of retries remaining
    ///
    /// Each call decrements the number of retries by one until zero is reached.
    /// @return true the number of retries remaining is greater than zero.
    bool checkRetries() {
        return (retries_left_ ? --retries_left_ : false);
    }

    /// @brief Returns the maximum number of retries allowed.
    unsigned int maxRetries() const {
        return (max_retries_);
    }

    /// @brief Returns the number for retries remaining.
    unsigned int retriesLeft() const {
        return (retries_left_);
    }

    /// @brief Returns an index of current retry.
    unsigned int retryIndex() const {
        return (max_retries_ - retries_left_);
    }

    /// @brief Returns the amount of time to wait between reconnect attempts.
    unsigned int retryInterval() const {
        return (retry_interval_);
    }

    /// @brief Resets the retries count.
    void resetRetries() {
        retries_left_ = max_retries_;
    }

    /// @brief Return true if the connection loss should affect the service,
    /// false otherwise
    bool alterServiceState() const {
        return (action_ == OnFailAction::STOP_RETRY_EXIT);
    }

    /// @brief Return true if the connection recovery mechanism should shut down
    /// the server on failure, false otherwise.
    bool exitOnFailure() const {
        return ((action_ == OnFailAction::STOP_RETRY_EXIT) ||
                (action_ == OnFailAction::SERVE_RETRY_EXIT));
    }

    /// @brief Convert action to string.
    ///
    /// @param action The action type to be converted to text.
    /// @return The text representation of the action type.
    static std::string onFailActionToText(OnFailAction action);

    /// @brief Convert string to action.
    ///
    /// @param text The text to be converted to action type.
    /// @return The action type corresponding to the text representation.
    static OnFailAction onFailActionFromText(const std::string& text);

private:

    /// @brief Caller backend type.
    const std::string backend_type_;

    /// @brief Timer associated to this object.
    std::string timer_name_;

    /// @brief Maximum number of retry attempts to make.
    unsigned int max_retries_;

    /// @brief Number of attempts remaining.
    unsigned int retries_left_;

    /// @brief The amount of time to wait between reconnect attempts.
    unsigned int retry_interval_;

    /// @brief Action to take on connection loss.
    OnFailAction action_;
};

/// @brief Pointer to an instance of ReconnectCtl
typedef boost::shared_ptr<ReconnectCtl> ReconnectCtlPtr;

}
}

#endif // RECONNECT_CTL_H
