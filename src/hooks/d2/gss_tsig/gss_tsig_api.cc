// Copyright (C) 2021-2022 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gss_tsig_api.h>
#include <cstring>
#include <limits>
#include <sstream>

using namespace std;

namespace isc {
namespace gss_tsig {

GssApiLastError::GssApiLastError() : last_error_(0) {
}

GssApiLastError::~GssApiLastError() {
}

string
gssApiErrMsg(OM_uint32 major, OM_uint32 minor) {
    ostringstream msg;
    GssApiBuffer msg_major;
    OM_uint32 minor_stat = 0;
    OM_uint32 msg_ctx = 0;
    OM_uint32 major_stat = gss_display_status(&minor_stat, major,
                                              GSS_C_GSS_CODE, GSS_C_NULL_OID,
                                              &msg_ctx, msg_major.getPtr());
    if (major_stat != GSS_S_COMPLETE) {
        // gssApiErrMsg is likely to be used in exception handles, we
        // can't throw here. But at the same time we want to explain
        // what was the nature of the problem, so at least we print
        // something on stderr, hoping the message will get to the user.
        cerr << "gss_display_status(major=" << major << ") failed with "
             << major_stat << endl;
    }
    msg << "GSSAPI error: Major = '";
    if (!msg_major.empty()) {
        msg << static_cast<char*>(msg_major.getValue());
    }

    if (minor != 0) {
        GssApiBuffer msg_minor;
        minor_stat = msg_ctx = 0;
        major_stat = gss_display_status(&minor_stat, minor,
                                        GSS_C_MECH_CODE, GSS_C_NULL_OID,
                                        &msg_ctx, msg_minor.getPtr());
        if (major_stat != GSS_S_COMPLETE) {
            // gssApiErrMsg is likely to be used in exception handles, we
            // can't throw here. But at the same time we want to explain
            // what was the nature of the problem, so at least we print
            // something on stderr, hoping the message will get to the user.
            cerr << "gss_display_status(minor=" << minor << ") failed with "
                 << major_stat << endl;
        }
        msg << "' (" << major << "), Minor = '";
        if (!msg_minor.empty()) {
            msg << static_cast<char*>(msg_minor.getValue());
        }
        msg << "' (" << minor << ").";
    } else {
        msg << "' (" << major << ").";
    }
    return (msg.str());
}

GssApiBuffer::GssApiBuffer() {
    memset(&buffer_, 0, sizeof(gss_buffer_desc));
}

GssApiBuffer::GssApiBuffer(size_t length, const void* value) {
    memset(&buffer_, 0, sizeof(gss_buffer_desc));
    if (length > numeric_limits<uint32_t>::max()) {
        isc_throw(OutOfRange, "GssApiBuffer constructor: length " << length
                  << " is too large");
    }
    buffer_.length = length;
    if (buffer_.length > 0) {
        // The GSS-API uses gss_release_buffer() to get rid of the buffer.
        // That function uses free(), hence we need to use malloc() to allocate.
        buffer_.value = malloc(buffer_.length);
        if (!buffer_.value) {
            buffer_.length = 0;
            isc_throw(GssApiError, "GssApiBuffer constructor failed with "
                      << "'Cannot allocate memory'");
        }
        memmove(buffer_.value, value, buffer_.length);
    }
}

GssApiBuffer::GssApiBuffer(const vector<uint8_t>& content) {
    memset(&buffer_, 0, sizeof(gss_buffer_desc));
    if (content.size() > numeric_limits<uint32_t>::max()) {
        isc_throw(OutOfRange, "GssApiBuffer constructor: vector size " <<
                  content.size() << " is too large");
    }
    buffer_.length = content.size();
    if (buffer_.length > 0) {
        // The GSS-API uses gss_release_buffer() to get rid of the buffer.
        // That function uses free(), hence we need to use malloc() to allocate.
        buffer_.value = malloc(buffer_.length);
        if (!buffer_.value) {
            buffer_.length = 0;
            isc_throw(GssApiError, "GssApiBuffer constructor failed with "
                      << "'Cannot allocate memory'");
        }
        memmove(buffer_.value, &content[0], buffer_.length);
    }
}

GssApiBuffer::GssApiBuffer(const string& content) {
    memset(&buffer_, 0, sizeof(gss_buffer_desc));
    if (content.empty()) {
        return;
    }
    if (content.size() >= numeric_limits<uint32_t>::max()) {
        isc_throw(OutOfRange, "GssApiBuffer constructor: string size "
                  << content.size() << " is too large");
    }
    // The GSS-API uses gss_release_buffer() to get rid of the buffer.
    // That function uses free(), hence we need to use malloc() to allocate.
    buffer_.length = content.size();
    buffer_.value = malloc(buffer_.length + 1);
    if (!buffer_.value) {
        buffer_.length = 0;
        isc_throw(GssApiError, "GssApiBuffer constructor failed with "
                  << "'Cannot allocate memory'");
    }
    memset(buffer_.value, 0, buffer_.length + 1);
    memmove(buffer_.value, content.c_str(), buffer_.length);
}


GssApiBuffer::~GssApiBuffer() {
    if (buffer_.value) {
        OM_uint32 minor = 0;
        OM_uint32 major = gss_release_buffer(&minor, &buffer_);
        if (major != GSS_S_COMPLETE) {
            cerr << "gss_release_buffer failed with " << major << endl;
        }
    }
}

vector<uint8_t>
GssApiBuffer::getContent() const {
    vector<uint8_t> content;
    content.resize(buffer_.length);
    if (buffer_.length > 0) {
        memmove(&content[0], buffer_.value, buffer_.length);
    }
    return (vector<uint8_t>(content));
}

string
GssApiBuffer::getString(bool trim) const {
    if (buffer_.length == 0) {
        return (string());
    } else if (trim) {
        return (string(static_cast<char*>(buffer_.value)));
    } else {
        return (string(static_cast<char*>(buffer_.value), buffer_.length));
    }
}

GssApiName::GssApiName() : GssApiLastError(), name_(GSS_C_NO_NAME) {
}

GssApiName::GssApiName(const string& gname)
    : GssApiLastError(), name_(GSS_C_NO_NAME) {
    if (gname.size() >= numeric_limits<uint32_t>::max()) {
        isc_throw(OutOfRange, "GssApiName constructor: string size "
                  << gname.size() << " is too large");
    }
    GssApiBuffer buf(gname);
    OM_uint32 minor = 0;
    OM_uint32 major = gss_import_name(&minor, buf.getPtr(),
                                      GSS_C_NO_OID, &name_);
    if (major != GSS_S_COMPLETE) {
        isc_throw(GssApiError, "gss_import_name failed with "
                  << gssApiErrMsg(major, minor));
    }
}

GssApiName::~GssApiName() {
    if (name_) {
        OM_uint32 minor = 0;
        OM_uint32 major = gss_release_name(&minor, &name_);
        if (major != GSS_S_COMPLETE) {
            cerr << "gss_release_name failed with " << major << endl;
        }
    }
}

bool
GssApiName::compare(GssApiName& other) {
    OM_uint32 minor = 0;
    int ret = -1;
    OM_uint32 major = gss_compare_name(&minor, name_, other.name_, &ret);
    if (major != GSS_S_COMPLETE) {
        setLastError(major);
        isc_throw(GssApiError, "gss_compare_name failed with "
                  << gssApiErrMsg(major, minor));
    }
    return (ret == 1);
}

string
GssApiName::toString() {
    GssApiBuffer buf;
    OM_uint32 minor = 0;
    OM_uint32 major = gss_display_name(&minor, name_, buf.getPtr(), 0);
    if (major != GSS_S_COMPLETE) {
        setLastError(major);
        isc_throw(GssApiError, "gss_display_name failed with "
                  << gssApiErrMsg(major, minor));
    }
    return (buf.getString());
}

GssApiCred::GssApiCred() : GssApiLastError(), cred_(GSS_C_NO_CREDENTIAL) {
}

GssApiCred::GssApiCred(GssApiName& gname, gss_cred_usage_t cred_usage,
                       OM_uint32& lifetime)
    : GssApiLastError(), cred_(GSS_C_NO_CREDENTIAL) {
    cred_ = GSS_C_NO_CREDENTIAL;
    lifetime = 0;
    GssApiOidSet mech_oid_set;
    OM_uint32 minor = 0;
    OM_uint32 major = gss_acquire_cred(&minor, gname.get(), GSS_C_INDEFINITE,
                                       mech_oid_set.get(), cred_usage,
                                       &cred_, 0, &lifetime);
    if (major != GSS_S_COMPLETE) {
        isc_throw(GssApiError, "gss_acquire_cred failed with "
                  << gssApiErrMsg(major, minor));
    }
}

GssApiCred::~GssApiCred() {
    if (cred_) {
        OM_uint32 minor = 0;
        OM_uint32 major = gss_release_cred(&minor, &cred_);
        if (major != GSS_S_COMPLETE) {
            cerr << "gss_release_cred failed with " << major << endl;
        }
    }
}

void
GssApiCred::inquire(GssApiName& name, gss_cred_usage_t& cred_usage,
                    OM_uint32& lifetime) {
    // cred_usage 0 means GSS_C_BOTH.
    lifetime = 0;
    OM_uint32 minor = 0;
    OM_uint32 major = gss_inquire_cred(&minor, cred_, name.getPtr(),
                                       &lifetime, &cred_usage, 0);
    if (major != GSS_S_COMPLETE) {
        setLastError(major);
        isc_throw(GssApiError, "gss_inquire_cred failed with "
                  << gssApiErrMsg(major, minor));
    }
}

GssApiSecCtx::GssApiSecCtx(gss_ctx_id_t sec_ctx)
    : GssApiLastError(), sec_ctx_(sec_ctx) {
}

GssApiSecCtx::GssApiSecCtx(const vector<uint8_t>& import)
    : GssApiLastError(), sec_ctx_(GSS_C_NO_CONTEXT) {
    GssApiBuffer buf(import);
    OM_uint32 minor = 0;
    OM_uint32 major = gss_import_sec_context(&minor, buf.getPtr(), &sec_ctx_);
    if (major != GSS_S_COMPLETE) {
        isc_throw(GssApiError, "gss_import_sec_context failed with "
                  << gssApiErrMsg(major, minor));
    }
}

GssApiSecCtx::~GssApiSecCtx() {
    if (sec_ctx_) {
        OM_uint32 minor = 0;
        OM_uint32 major = gss_delete_sec_context(&minor, &sec_ctx_, 0);
        if (major != GSS_S_COMPLETE) {
            cerr << "gss_delete_sec_context failed with " << major << endl;
        }
    }
}

vector<uint8_t>
GssApiSecCtx::serialize() {
    GssApiBuffer buf;
    OM_uint32 minor = 0;
    OM_uint32 major = gss_export_sec_context(&minor, &sec_ctx_, buf.getPtr());
    if (major != GSS_S_COMPLETE) {
        setLastError(major);
        isc_throw(GssApiError, "gss_export_sec_context failed with "
                  << gssApiErrMsg(major, minor));
    }
    return (buf.getContent());
}

OM_uint32
GssApiSecCtx::getLifetime() {
    OM_uint32 lifetime = 0;
    OM_uint32 minor = 0;
    OM_uint32 major = gss_context_time(&minor, sec_ctx_, &lifetime);
    if (major != GSS_S_COMPLETE) {
        setLastError(major);
        isc_throw(GssApiError, "gss_context_time failed with "
                  << gssApiErrMsg(major, minor));
    }
    return (lifetime);
}

void
GssApiSecCtx::inquire(GssApiName& source, GssApiName& target,
                      OM_uint32& lifetime, OM_uint32& flags,
                      bool& local, bool& established) {
    lifetime = flags = 0;
    local = established = false;
    int locally_initiated = 0;
    int open = 0;
    OM_uint32 minor = 0;
    OM_uint32 major = gss_inquire_context(&minor, sec_ctx_,
                                          source.getPtr(), target.getPtr(),
                                          &lifetime, 0, &flags,
                                          &locally_initiated, &open);
    if (major != GSS_S_COMPLETE) {
        setLastError(major);
        isc_throw(GssApiError, "gss_inquire_context failed with "
                  << gssApiErrMsg(major, minor));
    }
    local = (locally_initiated != 0);
    established = (open != 0);
}

void
GssApiSecCtx::sign(GssApiBuffer& gmessage, GssApiBuffer& gsig) {
    OM_uint32 minor = 0;
    OM_uint32 major = gss_get_mic(&minor, sec_ctx_, GSS_C_QOP_DEFAULT,
                                  gmessage.getPtr(), gsig.getPtr());
    if (major != GSS_S_COMPLETE) {
        setLastError(major);
        isc_throw(GssApiError, "gss_get_mic failed with "
                  << gssApiErrMsg(major, minor));
    }
}

void
GssApiSecCtx::verify(GssApiBuffer& gmessage, GssApiBuffer& gsig) {
    OM_uint32 minor = 0;
    OM_uint32 major = gss_verify_mic(&minor, sec_ctx_, gmessage.getPtr(),
                                     gsig.getPtr(), 0);
    if (major != GSS_S_COMPLETE) {
        setLastError(major);
        isc_throw(GssApiError, "gss_verify_mic failed with "
                  << gssApiErrMsg(major, minor));
    }
}

bool
GssApiSecCtx::init(GssApiCredPtr credp, GssApiName& target, OM_uint32 flags,
                   GssApiBuffer& intoken, GssApiBuffer& outtoken,
                   OM_uint32& lifetime) {
    gss_cred_id_t cred = GSS_C_NO_CREDENTIAL;
    if (credp) {
        cred = credp->get();
    }
    lifetime = 0;
    OM_uint32 ret_flags = 0;
    OM_uint32 minor = 0;
    OM_uint32 major = gss_init_sec_context(&minor, cred,
                                           &sec_ctx_, target.get(),
                                           ISC_GSS_SPNEGO_MECHANISM.get(),
                                           flags, GSS_C_INDEFINITE,
                                           GSS_C_NO_CHANNEL_BINDINGS,
                                           intoken.getPtr(), 0,
                                           outtoken.getPtr(), &ret_flags,
                                           &lifetime);
    switch (major) {
    case GSS_S_COMPLETE:
        if ((flags & GSS_C_REPLAY_FLAG) &&
            ((ret_flags & GSS_C_REPLAY_FLAG) == 0)) {
            isc_throw(GssApiError, "gss_init_sec_context failed to grant "
                      "requested anti-replay");
        }
        if ((flags & GSS_C_SEQUENCE_FLAG) &&
            ((ret_flags & GSS_C_SEQUENCE_FLAG) == 0)) {
            isc_throw(GssApiError, "gss_init_sec_context failed to grant "
                      "requested sequence");
        }
        if ((flags & GSS_C_MUTUAL_FLAG) &&
            ((ret_flags & GSS_C_MUTUAL_FLAG) == 0)) {
            isc_throw(GssApiError, "gss_init_sec_context failed to grant "
                      "requested mutual authentication");
        }
        return (true);
    case GSS_S_CONTINUE_NEEDED:
        return (false);
    default:
        setLastError(major);
        isc_throw(GssApiError, "gss_init_sec_context failed with "
                  << gssApiErrMsg(major, minor));
    }
}

bool
GssApiSecCtx::accept(GssApiCred& cred, GssApiBuffer& intoken,
                     GssApiName& source, GssApiBuffer& outtoken) {
    OM_uint32 minor = 0;
    OM_uint32 major = gss_accept_sec_context(&minor, &sec_ctx_, cred.get(),
                                             intoken.getPtr(),
                                             GSS_C_NO_CHANNEL_BINDINGS,
                                             source.getPtr(), 0,
                                             outtoken.getPtr(), 0, 0, 0);
    switch (major) {
    case GSS_S_COMPLETE:
        return (true);
    case GSS_S_CONTINUE_NEEDED:
        return (false);
    default:
        setLastError(major);
        isc_throw(GssApiError, "gss_accept_sec_context failed with "
                  << gssApiErrMsg(major, minor));
    }
}

GssApiOid::GssApiOid() : oid_(GSS_C_NO_OID) {
    // The GSS-API uses gss_release_oid() to release OID buffer. That function
    // uses free(), hence we need to use malloc() to allocate it.
    oid_ = static_cast<gss_OID>(malloc(sizeof(gss_OID_desc)));
    if (!oid_) {
        isc_throw(GssApiError, "GssApiOid constructor failed with "
                  << "'Cannot allocate memory' (desc)");
    }
    memset(oid_, 0, sizeof(gss_OID_desc));
}

GssApiOid::GssApiOid(const vector<uint8_t>& elements) : oid_(GSS_C_NO_OID) {
    if (elements.size() > 1024) {
        isc_throw(OutOfRange, "Too large argument to GssApiOid ("
                  << elements.size() << " > 1024)");
    }
    // The GSS-API uses gss_release_oid() to release OID buffer. That function
    // uses free(), hence we need to use malloc() to allocate it.
    oid_ = static_cast<gss_OID>(malloc(sizeof(gss_OID_desc)));
    if (!oid_) {
        isc_throw(GssApiError, "GssApiOid constructor failed with "
                  << "'Cannot allocate memory' (desc)");
    }
    memset(oid_, 0, sizeof(gss_OID_desc));
    oid_->length = elements.size();
    if (oid_->length > 0) {
        // The GSS-API uses gss_release_oid_set() to release OID buffer.
        // That function uses free(), hence we need to use malloc() to allocate.
        oid_->elements = malloc(oid_->length);
        if (!oid_->elements) {
            oid_->length = 0;
            isc_throw(GssApiError, "GssApiOid constructor failed with "
                      << "'Cannot allocate memory' (elements)");
        }
        memmove(oid_->elements, &elements[0], oid_->length);
    }
}

GssApiOid::GssApiOid(const string& str) : oid_(GSS_C_NO_OID) {
#if HAVE_GSS_STR_TO_OID
    GssApiBuffer buf(str);
    OM_uint32 minor = 0;
    OM_uint32 major = gss_str_to_oid(&minor, buf.getPtr(), &oid_);
    if (major != GSS_S_COMPLETE) {
        isc_throw(GssApiError, "gss_str_to_oid failed with "
                  << gssApiErrMsg(major, minor));
    }
#else
    isc_throw(NotImplemented, "gss_str_to_oid(" << str << ") is not available");
#endif
}

GssApiOid::~GssApiOid() {
    if (oid_) {
        OM_uint32 minor = 0;
        OM_uint32 major = gss_release_oid(&minor, &oid_);
        if (major != GSS_S_COMPLETE) {
            cerr << "gss_release_oid failed with " << major << endl;
        }
    }
}

string
GssApiOid::toString() {
    GssApiBuffer buf;
    OM_uint32 minor = 0;
    OM_uint32 major = gss_oid_to_str(&minor, oid_, buf.getPtr());
    if (major != GSS_S_COMPLETE) {
        isc_throw(GssApiError, "gss_oid_to_str failed with "
                  << gssApiErrMsg(major, minor));
    }
    return (buf.getString(true));
}

namespace {

vector<uint8_t> ISC_GSS_KRB5_MECHANISM_vect =
    { 0x2a, 0x86, 0x48, 0x86, 0xf7, 0x12, 0x01, 0x02, 0x02 };
}

GssApiOid ISC_GSS_KRB5_MECHANISM(ISC_GSS_KRB5_MECHANISM_vect);

namespace {

vector<uint8_t> ISC_GSS_SPNEGO_MECHANISM_vect =
    { 0x2b, 0x06, 0x01, 0x05, 0x05, 0x02 };
}

GssApiOid ISC_GSS_SPNEGO_MECHANISM(ISC_GSS_SPNEGO_MECHANISM_vect);

GssApiOidSet::GssApiOidSet(bool fill) {
    oid_set_ = GSS_C_NO_OID_SET;
    if (!fill) {
        return;
    }
    OM_uint32 minor = 0;
    OM_uint32 major = gss_create_empty_oid_set(&minor, &oid_set_);
    if (major != GSS_S_COMPLETE) {
        isc_throw(GssApiError, "gss_create_empty_oid_set failed with "
                  << gssApiErrMsg(major, minor));
    }
    minor = 0;
    major = gss_add_oid_set_member(&minor, ISC_GSS_KRB5_MECHANISM.get(),
                                   &oid_set_);
    if (major != GSS_S_COMPLETE) {
        isc_throw(GssApiError, "gss_add_oid_set_member(KRB5) failed with "
                  << gssApiErrMsg(major, minor));
    }
    minor = 0;
    major = gss_add_oid_set_member(&minor, ISC_GSS_SPNEGO_MECHANISM.get(),
                                   &oid_set_);
    if (major != GSS_S_COMPLETE) {
        isc_throw(GssApiError, "gss_add_oid_set_member(SPNEGO) failed with "
                  << gssApiErrMsg(major, minor));
    }
}

GssApiOidSet::~GssApiOidSet() {
    if (oid_set_) {
        OM_uint32 minor = 0;
        OM_uint32 major = gss_release_oid_set(&minor, &oid_set_);
        if (major != GSS_S_COMPLETE) {
            cerr << "gss_release_oid_set failed with " << major << endl;
        }
    }
}

} // end of namespace isc::gss_tsig
} // end of namespace isc
