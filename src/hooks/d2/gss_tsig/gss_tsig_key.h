// Copyright (C) 2021-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef GSS_TSIG_KEY_H
#define GSS_TSIG_KEY_H

#include <d2srv/d2_tsig_key.h>
#include <gss_tsig_api.h>
#include <boost/shared_ptr.hpp>
#include <chrono>

namespace isc {
namespace gss_tsig {

/// @brief GSS-TSIG extension of the D2 TSIG key class.
///
/// Implements a @c isc::d2::D2TsigKey derived class which can be
/// used as the value of D2TsigKeyPtr so with minimal or no update to the
/// DNS++ library. The class adds to the D2TsigKey base a GSS-API security
/// context maintaining 1::1 binding the key and it including for the
/// lifetime: e.g. to get a fresh GSS-API security context a fresh object
/// must be created.
class GssTsigKey : public d2::D2TsigKey {
public:
    /// @brief Constructor.
    ///
    /// @param key_name Domain name of the key.
    /// @param sec_ctx Security context (can be 0).
    GssTsigKey(const std::string& key_name,
               gss_ctx_id_t sec_ctx = GSS_C_NO_CONTEXT);

    /// @brief Constructor.
    ///
    /// Use the gss_import_sec_context GSS-API function. This constructor
    /// is expected to be used for restoring / importing a security context
    /// saved on disk.
    ///
    /// @param key_name Domain name of the key.
    /// @param import Vector of byte representing the GSS-API security context.
    GssTsigKey(const std::string& key_name,
               const std::vector<uint8_t>& import);

    /// @brief Destructor.
    virtual ~GssTsigKey();

    /// @brief Get the security context.
    ///
    /// @note: By construction the sec_ctx_ pointer is never null but
    /// the security context lifetime is the same as the key object.
    ///
    /// @return The security context.
    GssApiSecCtx& getSecCtx() {
        return (*sec_ctx_);
    }

    /// @brief Get the key inception.
    ///
    /// @return The key inception date.
    std::chrono::system_clock::time_point getInception() const {
        return (inception_);
    }

    /// @brief Get the key inception (32 bits).
    ///
    /// @return The key inception date as a 32 bit unsigned.
    uint32_t getInception32() const {
        std::time_t inception = std::chrono::system_clock::to_time_t(inception_);
        return (static_cast<uint32_t>(inception));
    }

    /// @brief Set the key inception.
    ///
    /// @param inception The new key inception date.
    void setInception(const std::chrono::system_clock::time_point& inception) {
        inception_ = inception;
    }

    /// @brief Get the key expire.
    ///
    /// @return The key expire date.
    std::chrono::system_clock::time_point getExpire() const {
        return (expire_);
    }

    /// @brief Get the key expire (32 bits).
    ///
    /// @return The key expire date as a 32 bit unsigned.
    uint32_t getExpire32() const {
        std::time_t expire = std::chrono::system_clock::to_time_t(expire_);
        return (static_cast<uint32_t>(expire));
    }

    /// @brief Set the key expire.
    ///
    /// @param expire The new key expire date.
    void setExpire(const std::chrono::system_clock::time_point& expire) {
        expire_ = expire;
    }

protected:
    /// @brief GSS-API security context.
    std::unique_ptr<GssApiSecCtx> sec_ctx_;

    /// @brief The key inception date.
    std::chrono::system_clock::time_point inception_;

    /// @brief The key expire date.
    std::chrono::system_clock::time_point expire_;
};

/// @brief Type of pointer to a GSS-TSIG key.
typedef boost::shared_ptr<GssTsigKey> GssTsigKeyPtr;

} // end of namespace isc::gss_tsig
} // end of namespace isc

#endif // GSS_TSIG_KEY_H
