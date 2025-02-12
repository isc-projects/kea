// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

/// @file gss_tsig_api.h C++ binding for the GSS-API.
///
/// This files provide C++ bindings: each type has its corresponding
/// C++ class: when a type is a structure (descriptor in GSS-API term)
/// it gets a class encapsulating the structure at the exception of
/// ASN.1 Object IDs. Some types are pointers to opaque structures.
///
/// To avoid ownership or memory issues all classes are not copyable
/// and should be passed by references. Note the GSS-API does not make
/// any argument const at a few exceptions so these references are
/// plain (vs const) references.
///
/// The central GSS-API structure is the buffer. Opaque structures so
/// pointer types are names, credential and security contexts.
///
/// Recommended reading:
/// - RFC 2743 (GSS-API protocol) or
/// - RFC 2744 (GSS-API - C Bindings)

#ifndef GSS_TSIG_UTIL_H
#define GSS_TSIG_UTIL_H

#include <exceptions/exceptions.h>
#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>
#include <gssapi/gssapi_krb5.h>
#include <iostream>
#include <string>
#include <vector>

namespace isc {
namespace gss_tsig {

/// @brief GSS-API exception.
class GssApiError : public Exception {
public:
    GssApiError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {
    }
};

class GssCredExpired : public Exception {
public:
    GssCredExpired(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {
    }
};

/// @brief Last error base class.
///
/// This class caches the last error.
class GssApiLastError {
public:
    /// @brief Constructor.
    GssApiLastError();

    /// @brief Destructor.
    virtual ~GssApiLastError();

    /// @brief Get the last error.
    ///
    /// @return The last error.
    int getLastError() const {
        return (last_error_);
    }

    /// @brief Set the last error.
    ///
    /// @param error New error.
    void setLastError(int error) {
        last_error_ = error;
    }

private:
    /// @brief The last error.
    int last_error_;
};

/// @brief An the error message.
///
/// Use the gss_display_status GSS-API function.
///
/// @param major Major error code (GSS).
/// @param minor Minor error code (Mech).
/// @return The corresponding error message.
std::string gssApiErrMsg(OM_uint32 major, OM_uint32 minor);

/// @brief GSS-API buffer.
///
/// Encapsulate the gss_buffer_desc (structure with length and value) type.
///
/// @note: the memory is not shared by constructor and get content methods,
/// i.e. a copy is taken and the source can be destroyed at any time after.
class GssApiBuffer : public boost::noncopyable {
public:
    /// @brief Constructor.
    GssApiBuffer();

    /// @brief Constructor.
    ///
    /// @param length Buffer length.
    /// @param value Buffer value.
    GssApiBuffer(size_t length, const void* value);

    /// @brief Constructor.
    ///
    /// @param content Content as a vector of bytes.
    explicit GssApiBuffer(const std::vector<uint8_t>& content);

    /// @brief Constructor.
    ///
    /// @param content Content as a string.
    explicit GssApiBuffer(const std::string& content);

    /// @brief Destructor.
    ///
    /// Use gss_release_buffer GSS-API function.
    ~GssApiBuffer();

    /// @brief Empty predicate.
    ///
    /// @return true if empty, false is not empty.
    bool empty() const {
        return (buffer_.value == 0);
    }

    /// @brief Get pointer.
    ///
    /// @return a pointer to the buffer.
    gss_buffer_t getPtr() {
        return (&buffer_);
    }

    /// @brief Get the length.
    ///
    /// @return the length.
    size_t getLength() const {
        return (buffer_.length);
    }

    /// @brief Get the value.
    ///
    /// @note: please use this method only to copy the content:
    /// the value lifetime is the same as the object.
    ///
    /// @return the value.
    void* getValue() {
        return (buffer_.value);
    }

    /// @brief Get the content as a vector.
    ///
    /// @return the content as a vector of bytes.
    std::vector<uint8_t> getContent() const;

    /// @brief Get the content as a string.
    ///
    /// @note It is not allowed to overload with a different return type
    /// so the getContent method name is not available.
    /// @note: This is not the same as string(getValue()) because of
    /// the way the nul character is handled in C++ strings.
    ///
    /// @param trim When true treat the buffer as a C string, when false
    /// (the default) treat the buffer as a C++ string.
    /// @return the content as a string.
    std::string getString(bool trim = false) const;

private:
    /// @brief The GSS-API buffer.
    gss_buffer_desc buffer_;
};

/// @brief Shared pointer to GSS-API buffer.
typedef boost::shared_ptr<GssApiBuffer> GssApiBufferPtr;

/// @brief GSS-API name.
///
/// Encapsulate the gss_name_t GSS-API pointer type.

/// @note: some methods should be const but this does not match the API.
class GssApiName : public boost::noncopyable, public GssApiLastError {
public:
    /// @brief Constructor.
    GssApiName();

    /// @brief Constructor.
    ///
    /// @param gname The GSS-API name in a textual form.
    explicit GssApiName(const std::string& gname);

    /// @brief Destructor.
    ///
    /// Use gss_release_name GSS-API function.
    ~GssApiName();

    /// @brief Get the value.
    gss_name_t get() {
        return (name_);
    }

    /// @brief Get pointer.
    ///
    /// @return a pointer to the name.
    gss_name_t* getPtr() {
        return (&name_);
    }

    /// @brief Compare.
    ///
    /// Use the gss_compare_name GSS-API funtion.
    ///
    /// @param other Other GSS-API name.
    /// @return true if identical, false if different.
    bool compare(GssApiName& other);

    /// @brief textual representation.
    ///
    /// Use the gss_display_name GSS-API funtion.
    ///
    /// @return a string representing the GSS-API name.
    std::string toString();

private:
    /// @brief The GSS-API name.
    gss_name_t name_;
};

/// @brief Shared pointer to GSS-API name.
typedef boost::shared_ptr<GssApiName> GssApiNamePtr;

/// @brief GSS-API credential.
///
/// Encapsulate the gss_cred_id_t GSS-API pointer type.
///
/// @note: some methods should be const but this does not match the API.
class GssApiCred : public boost::noncopyable, public GssApiLastError {
public:
    /// @brief Constructor.
    GssApiCred();

    /// @brief Constructor.
    ///
    /// Use the gss_acquire_cred GSS-API function.
    ///
    /// @param gname Desired GSS-API name.
    /// @param cred_usage Credential usage (GSS_C_INITIATE or GSS_C_ACCEPT).
    /// @param[out] lifetime Validity lifetime (number of seconds from now).
    GssApiCred(GssApiName& gname, gss_cred_usage_t cred_usage,
               OM_uint32& lifetime);

    /// @brief Destructor.
    ///
    /// Use the gss_release_cred GSS-API function
    ~GssApiCred();

    /// @brief Get the value.
    gss_cred_id_t get() {
        return (cred_);
    }

    /// @brief Inquire.
    ///
    /// Use the gss_inquire_cred GSS-API function.
    ///
    /// @param[out] name GSS-API name.
    /// @param[out] cred_usage Credential usage.
    /// @param[out] lifetime Validity lifetime (number of seconds from now).
    void inquire(GssApiName& name, gss_cred_usage_t& cred_usage,
                 OM_uint32& lifetime);

private:
    /// @brief The GSS-API credential.
    gss_cred_id_t cred_;
};

/// @brief Shared pointer to GSS-API credential.
typedef boost::shared_ptr<GssApiCred> GssApiCredPtr;

/// @brief GSS-API security context.
///
/// Encapsulate gss_ctx_id_t the GSS-API pointer type.
///
/// @note: some methods should be const but this does not match the API.
class GssApiSecCtx : public boost::noncopyable, public GssApiLastError {
public:
    /// @brief Constructor.
    ///
    /// @param sec_ctx The GSS-API security context.
    explicit GssApiSecCtx(gss_ctx_id_t sec_ctx);

    /// @brief Import constructor.
    ///
    /// Use the gss_import_sec_context GSS-API function.
    ///
    /// @param import Vector of byte representing the GSS-API security context.
    explicit GssApiSecCtx(const std::vector<uint8_t>& import);

    /// @brief Destructor.
    ///
    /// Use the gss_delete_sec_context GSS-API function.
    ~GssApiSecCtx();

    /// @brief Get the value.
    gss_ctx_id_t get() {
        return (sec_ctx_);
    }

    /// @brief Get a pointer to the security context.
    ///
    /// @return a pointer to the security context.
    gss_ctx_id_t* getPtr() {
        return (&sec_ctx_);
    }

    /// @brief Export.
    ///
    /// Use the gss_export_sec_context GSS-API function.
    ///
    /// @return A vector of byte representing the GSS-API security context.
    std::vector<uint8_t> serialize();

    /// @brief Get the lifetime (validity in seconds).
    ///
    /// Use the gss_context_time GSS-API function.
    ///
    OM_uint32 getLifetime();

    /// @brief Inquire.
    ///
    /// Use the gss_inquire_context GSS-API function.
    ///
    /// @param[out] source Source GSS-API name.
    /// @param[out] target Target GSS-API name.
    /// @param[out] lifetime Validity lifetime (number of seconds from now).
    /// @param[out] flags Current flags.
    /// @param[out] local True when locally initialed, false otherwise.
    /// @param[out] established True when established, false when a token is
    /// still expected.
    void inquire(GssApiName& source, GssApiName& target, OM_uint32& lifetime,
                 OM_uint32& flags, bool& local, bool& established);

    /// @brief Sign.
    ///
    /// Use the gss_get_mic GSS-API function.
    ///
    /// @param gmessage GSS-API buffer containing the message to sign.
    /// @param[out] gsig GSS-API buffer to handle the signature.
    void sign(GssApiBuffer& gmessage, GssApiBuffer& gsig);

    /// @brief Verify.
    ///
    /// Use the gss_verify_mic GSS-API function.
    ///
    /// @param gmessage GSS-API buffer containing the message to verify.
    /// @param gsig GSS-API buffer containing the signature to verify.
    void verify(GssApiBuffer& gmessage, GssApiBuffer& gsig);

    /// @brief Init.
    ///
    /// Init is the client setup method: it should be called
    /// until it completes. The input and output tokens are used
    /// for communication with the peer i.e. the acceptor.
    ///
    /// Use the gss_init_sec_context GSS-API function.
    ///
    /// @param credp Pointer to claimant GSS-API credential.
    /// @param target Target GSS-API name.
    /// @param flags Requested flags.
    /// @param intoken Input token (a GSS-API buffer).
    /// @param[out] outtoken Output token (a GSS-API buffer).
    /// @param[out] lifetime Validity lifetime (number of seconds from now).
    /// @return True when complete, false when continue (i.e. must be called
    /// again).
    bool init(GssApiCredPtr credp, GssApiName& target, OM_uint32 flags,
              GssApiBuffer& intoken, GssApiBuffer& outtoken,
              OM_uint32& lifetime);

    /// @brief Accept.
    ///
    /// Accept is the server acceptor method: it should be called
    /// until it completes. The input and output tokens are used
    /// for communication with the peer i.e. a client.
    ///
    /// Use the gss_accept_sec_context GSS-API function.
    ///
    /// @param cred Acceptor GSS-API credential.
    /// @param intoken Input token (a GSS-API buffer).
    /// @param[out] source Source GSS-API name.
    /// @param[out] outtoken Output token (a GSS-API buffer).
    /// @return True when complete, false when continue (i.e. must be called
    /// again).
    bool accept(GssApiCred& cred, GssApiBuffer& intoken, GssApiName& source,
                GssApiBuffer& outtoken);

private:
    /// @brief The GSS-API security context.
    gss_ctx_id_t sec_ctx_;
};

/// @brief GSS-API OID.
///
/// Encapsulate the gss_OID GSS-API pointer type.
///
/// @note: gss_release_oid() releases the descriptor too so this class
/// encapsulate the gss_OID pointer type (vs the gss_OID_desc
/// (structure with length and elements) type.
///
class GssApiOid : public boost::noncopyable {
public:
    /// @brief Constructor.
    GssApiOid();

    /// @brief Constructor.
    ///
    /// @param elements Elements as a vector of bytes.
    explicit GssApiOid(const std::vector<uint8_t>& elements);

    /// @brief Constructor.
    ///
    /// Use the gss_str_to_oid GSS-API function.
    ///
    /// @note: is not available on Heimdal.
    ///
    /// @param str Textual representation.
    explicit GssApiOid(const std::string& str);

    /// @brief Destructor.
    ///
    /// Use the gss_release_oid GSS-API function.
    ~GssApiOid();

    /// @brief Get the value.
    gss_OID get() {
        return (oid_);
    }

    /// @brief Get textual representation.
    ///
    /// Use the gss_oid_to_str GSS-API function.
    ///
    /// @return A textual representation.
    std::string toString();

private:
    /// @brief The GSS-API OID.
    gss_OID oid_;
};

/// @brief The Kerberos 5 OID.
extern GssApiOid ISC_GSS_KRB5_MECHANISM;

/// @brief The SPNEGO OID.
extern GssApiOid ISC_GSS_SPNEGO_MECHANISM;

/// @brief Shared pointer to GSS-API OID.
typedef boost::shared_ptr<GssApiOid> GssApiOidPtr;

/// @brief GSS-API OID set.
///
/// Encapsulate the gss_OID_set pointer type.
///
/// @note: no need yet to give access to the whole C API.
class GssApiOidSet : public boost::noncopyable {
public:
    /// @brief Constructor.
    ///
    /// @param fill True if the set must be filled with Kerberos 5 and
    /// SPNEGO OIDs (the default), false if it must be left null.
    explicit GssApiOidSet(bool fill = true);

    /// @brief Destructor.
    ///
    /// Use the gss_release_oid_set GSS-API function.
    ~GssApiOidSet();

    /// @brief Get the value.
    gss_OID_set get() {
        return (oid_set_);
    }

private:
    /// @brief The GSS-API OID set.
    gss_OID_set oid_set_;
};

/// @brief Shared pointer to GSS-API OID set.
typedef boost::shared_ptr<GssApiOidSet> GssApiOidSetPtr;

} // end of namespace isc::gss_tsig
} // end of namespace isc

#endif // GSS_TSIG_UTIL_H
