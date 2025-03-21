// Copyright (C) 2021-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef MANAGED_KEY_H
#define MANAGED_KEY_H

#include <cc/cfg_to_element.h>
#include <gss_tsig_key.h>
#include <tkey_exchange.h>
#include <list>
#include <mutex>

namespace isc {
namespace gss_tsig {

/// @brief Managed GSS-TSIG key.
///
/// This class extends @c GssTsigKey with data which are defined in headers
/// which include the class definition.
class ManagedKey : public GssTsigKey, public TKeyExchange::Callback,
                   public isc::data::CfgToElement {
public:
    /// @brief A key status.
    ///
    /// Standard flow is initialized as not ready, after the setup usable
    /// and at expire finishes as expired. When the setup fails it is
    /// in error, the TKEY exchange status giving more details on the
    /// failure reason.
    enum Status {
        NOT_READY,        ///< Not yet ready (not yet usable).
        USABLE,           ///< Usable.
        EXPIRED,          ///< Expired (no longer usable).
        IN_ERROR          ///< Setup failed.
    };

    /// @brief Convert a status to its textual form.
    static std::string statusToText(Status status);

    /// @brief Constructor.
    ///
    /// @param name Key name.
    ManagedKey(const std::string& name);

    /// @brief Destructor.
    virtual ~ManagedKey() = default;

    /// @brief Get the key name as a string.
    ///
    /// @return the key name as a string.
    std::string getKeyNameStr() const {
        return (getKeyName().toText());
    }

    /// @brief Get the DNS server (parent) ID.
    ///
    /// @return The DNS server (parent) ID.
    std::string getParentID() const {
        return (parent_id_);
    }

    /// @brief Set the DNS server (parent) ID.
    ///
    /// @param parent_id DNS server (parent) ID.
    void setParentID(const std::string& parent_id) {
        parent_id_ = parent_id;
    }

    /// @brief Get the key status.
    ///
    /// @return The key status.
    Status getStatus() const {
        return (status_);
    }

    /// @brief Set the key status.
    ///
    /// @param status The new key status.
    void setStatus(Status status) {
        status_ = status;
    }

    /// @brief Get the TKEY exchange status.
    ///
    /// @return The TKEY exchange status.
    TKeyExchange::Status getTKeyStatus() const {
        return (tkey_status_);
    }

    /// @brief Set the TKEY exchange status.
    ///
    /// @param tkey_status The new TKEY exchange status.
    void setTKeyStatus(TKeyExchange::Status tkey_status) {
        tkey_status_ = tkey_status;
    }

    /// @brief Get the TKEY exchange.
    ///
    /// @return A reference to the TKEY exchange pointer.
    TKeyExchangePtr& getTKeyExchange() {
        return (tkey_ex_);
    }

    /// @brief The TKEY exchange completion handler.
    ///
    /// @param tkey_status The completion status.
    void operator()(TKeyExchange::Status tkey_status);

    /// @brief Create a random name from a suffix.
    ///
    /// @param server The server suffix.
    static std::string genName(const std::string& server);

    /// @brief Unparse a key object.
    ///
    /// Used to get the full state of a key:
    ///  - name
    ///  - status
    ///  - security-context-lifetime (usable or expired key)
    ///  - tkey-status (in case of error)
    ///  - tkey-exchange (not yet ready key)
    ///  - inception-date
    ///  - expire-date
    ///
    /// @return a pointer to unparsed key object.
    isc::data::ElementPtr toElement() const;

    /// @brief Create GssTsigContext context.
    ///
    /// @note overwritten @c isc::d2::D2TsigKey method.
    ///
    /// @return The specific @ref GssTsigContext of the @ref GssTsigKey.
    virtual dns::TSIGContextPtr createContext();

private:
    /// @brief DNS server (parent) ID.
    std::string parent_id_;

    /// @brief Key status.
    Status status_;

    /// @brief TKEY exchange status.
    TKeyExchange::Status tkey_status_;

    /// @brief TKEY exchange (not null during setup).
    TKeyExchangePtr tkey_ex_;

public:
    /// @brief Mutex for protecting key state.
    boost::scoped_ptr<std::mutex> mutex_;
};

/// @brief Type of pointer to a Managed GSS-TSIG key.
typedef boost::shared_ptr<ManagedKey> ManagedKeyPtr;

} // end of namespace isc::gss_tsig
} // end of namespace isc

#endif // MANAGED_KEY_H
