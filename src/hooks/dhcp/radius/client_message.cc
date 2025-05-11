// Copyright (C) 2023-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <client_attribute.h>
#include <client_message.h>
#include <radius_log.h>
#include <cryptolink/crypto_hash.h>
#include <cryptolink/crypto_rng.h>
#include <boost/scoped_ptr.hpp>
#include <sstream>

using namespace isc;
using namespace isc::asiolink;
using namespace isc::cryptolink;
using namespace isc::data;
using namespace isc::util;
using namespace std;

namespace isc {
namespace radius {

string
msgCodeToText(const uint8_t code) {
    ostringstream result;
    switch (code) {
    case PW_ACCESS_REQUEST:
        return ("Access-Request");
    case PW_ACCESS_ACCEPT:
        return ("Access-Accept");
    case PW_ACCESS_REJECT:
        return ("Access-Reject");
    case PW_ACCOUNTING_REQUEST:
        return ("Accounting-Request");
    case PW_ACCOUNTING_RESPONSE:
        return ("Accounting-Response");
    case PW_ACCOUNTING_STATUS:
        return ("Accounting-Status");
    case PW_PASSWORD_REQUEST:
        return ("Password-Request");
    case PW_PASSWORD_ACK:
        return ("Password-Ack");
    case PW_PASSWORD_REJECT:
        return ("Password-Reject");
    case PW_ACCOUNTING_MESSAGE:
        return ("Accounting-Message");
    case PW_ACCESS_CHALLENGE:
        return ("Access-Challenge");
    case PW_STATUS_SERVER:
        return ("Status-Server");
    case PW_STATUS_CLIENT:
        return ("Status-Client");
    default:
        result << "Message-Code-" << static_cast<unsigned>(code);
        return (result.str());
    }
}

Message::Message(const uint8_t code, uint16_t length,
                 const vector<uint8_t>& auth, const string& secret,
                 const AttributesPtr& attributes)
    : code_(code), length_(length), auth_(auth), secret_(secret),
      attributes_(attributes), buffer_() {
}

Message::Message(const Message& other)
    : code_(other.code_),
      length_(other.length_),
      auth_(other.auth_),
      secret_(other.secret_),
      attributes_(AttributesPtr(new Attributes())),
      buffer_(other.buffer_) {
    if (!other.attributes_) {
        attributes_.reset();
    } else {
        for (auto const& attr : *other.attributes_) {
            attributes_->add(attr);
        }
    }
}

Message::Message(const vector<uint8_t>& buffer,
                 const vector<uint8_t>& auth,
                 const string& secret)
    : code_(0), length_(0), auth_(auth), secret_(secret), attributes_(),
      buffer_(buffer) {
}

Message::~Message() {
    if (secret_.size() > 0) {
        memset(&secret_[0], 0, secret_.size());
    }
    secret_.clear();
}

void
Message::randomIdentifier() {
    vector<uint8_t> r = cryptolink::random(1);
    if (r.size() == 0) {
        isc_throw(Unexpected, "random failed");
    }
    identifier_ = r[0];
}

void
Message::setAuth(const vector<uint8_t>& auth) {
    if (auth.size() != AUTH_VECTOR_LEN) {
        isc_throw(BadValue, "authenticator must be 16 bytes long");
    }
    auth_ = auth;
}

void
Message::zeroAuth() {
    auth_.clear();
    auth_.resize(AUTH_VECTOR_LEN, 0);
}

void
Message::randomAuth() {
    auth_ = cryptolink::random(AUTH_VECTOR_LEN);
    if (auth_.size() != AUTH_VECTOR_LEN) {
        isc_throw(Unexpected, "random failed");
    }
}

void
Message::setSecret(const string& secret) {
    if (secret.empty()) {
        isc_throw(BadValue, "empty secret");
    }
    secret_ = secret;
}

vector<uint8_t>
Message::encode() {
    if (secret_.empty()) {
        isc_throw(InvalidOperation, "empty secret");
    }

    // Header.
    buffer_.resize(AUTH_HDR_LEN);
    buffer_[0] = code_;
    buffer_[1] = identifier_;
    buffer_[2] = static_cast<uint8_t>((length_ & 0xff00) >> 8);
    buffer_[3] = static_cast<uint8_t>(length_ & 0xff);
    memmove(&buffer_[4], &auth_[0], auth_.size());

    // Fill attributes.
    if (attributes_) {
        for (auto attr : *attributes_) {
            if (!attr) {
                continue;
            }
            if ((code_ == PW_ACCESS_REQUEST) &&
                (attr->getType() == PW_USER_PASSWORD)) {
                attr = encodeUserPassword(attr);
            }
            vector<uint8_t> binary = attr->toBytes();
            if (binary.empty()) {
                continue;
            }
            if (buffer_.size() + binary.size() > PW_MAX_MSG_SIZE) {
                isc_throw(BadValue, "message becomes too large");
            }
            buffer_.insert(buffer_.end(), binary.cbegin(), binary.cend());
        }
    }

    // Finish.
    length_ = static_cast<uint16_t>(buffer_.size());
    buffer_[2] = static_cast<uint8_t>((length_ & 0xff00) >> 8);
    buffer_[3] = static_cast<uint8_t>(length_ & 0xff);

    if (code_ != PW_ACCESS_REQUEST) {
        boost::scoped_ptr<Hash> md(CryptoLink::getCryptoLink().createHash(MD5));
        md->update(&buffer_[0], buffer_.size());
        md->update(&secret_[0], secret_.size());
        md->final(&auth_[0], AUTH_VECTOR_LEN);
        memmove(&buffer_[4], &auth_[0], auth_.size());
    }

    LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_ENCODE_MESSAGE)
        .arg(msgCodeToText(code_))
        .arg(static_cast<unsigned>(code_))
        .arg(static_cast<unsigned>(identifier_))
        .arg(length_)
        .arg(attributes_ ? attributes_->size() : 0);
    return (buffer_);
}

void
Message::decode() {
    if (secret_.empty()) {
        isc_throw(InvalidOperation, "empty secret");
    }

    // Length.
    if (buffer_.size() < AUTH_HDR_LEN) {
        isc_throw(BadValue, "message is too short " << buffer_.size()
                  << " < " << AUTH_HDR_LEN);
    }
    code_ = buffer_[0];
    identifier_ = buffer_[1];
    length_ = static_cast<uint16_t>(buffer_[2]) << 8;
    length_ |= static_cast<uint16_t>(buffer_[3]);
    if (code_ == PW_ACCESS_REQUEST) {
        auth_.resize(AUTH_VECTOR_LEN);
        memmove(&auth_[0], &buffer_[4], AUTH_VECTOR_LEN);
    } else if (auth_.size() != AUTH_VECTOR_LEN) {
        isc_throw(InvalidOperation, "bad authenticator");
    }
    if (length_ > buffer_.size()) {
        isc_throw(BadValue, "truncated " << msgCodeToText(code_)
                  << " length " << length_ << ", got " << buffer_.size());
    }
    if (length_ < AUTH_HDR_LEN) {
      isc_throw(BadValue, "too short " << msgCodeToText(code_)
                << " length " << length_ << " < " << AUTH_HDR_LEN);
    }
    if (length_ > PW_MAX_MSG_SIZE) {
        isc_throw(BadValue, "too large " << msgCodeToText(code_)
                  << " length " << length_ << " > " << PW_MAX_MSG_SIZE);
    }
    if (length_ < buffer_.size()) {
        buffer_.resize(length_);
    }

    // Verify authentication.
    if (code_ != PW_ACCESS_REQUEST) {
        vector<uint8_t> work = buffer_;
        memmove(&work[4], &auth_[0], auth_.size());
        boost::scoped_ptr<Hash> md(CryptoLink::getCryptoLink().createHash(MD5));
        md->update(&work[0], work.size());
        md->update(&secret_[0], secret_.size());
        vector<uint8_t> digest;
        digest.resize(AUTH_VECTOR_LEN);
        md->final(&digest[0], AUTH_VECTOR_LEN);
        if (memcmp(&digest[0], &buffer_[4], AUTH_VECTOR_LEN) != 0) {
            isc_throw(BadValue, "authentication for " << msgCodeToText(code_)
                      << " failed");
        }
    }
    auth_.resize(AUTH_VECTOR_LEN);
    memmove(&auth_[0], &buffer_[4], auth_.size());

    // Get attributes.
    attributes_.reset(new Attributes());
    size_t ptr = AUTH_HDR_LEN;
    for (;;) {
        if (ptr == length_) {
            break;
        }
        if (ptr + 2 > length_) {
            isc_throw(BadValue, "trailing octet");
        }
        const uint8_t type = buffer_[ptr];
        const uint8_t len = buffer_[ptr + 1];
        if (ptr + len > length_) {
            isc_throw(BadValue, "trailing truncated "
                      << AttrDefs::instance().getName(type) << " ("
                      << static_cast<unsigned>(type) << "): length "
                      << static_cast<unsigned>(len) << ", space "
                      << (length_ - ptr));
        }
        if (len < 3) {
            isc_throw(BadValue, "too small attribute length "
                      << static_cast<unsigned>(len) << " < 3");
        }
        vector<uint8_t> binary;
        binary.resize(len);
        memmove(&binary[0], &buffer_[ptr], binary.size());
        ConstAttributePtr attr = Attribute::fromBytes(binary);
        if ((code_ == PW_ACCESS_REQUEST) && attr &&
            (attr->getType() == PW_USER_PASSWORD)) {
            attr = decodeUserPassword(attr);
        }
        attributes_->add(attr);
        ptr += len;
    }
    if (attributes_->empty()) {
        attributes_.reset();
    }

    LOG_DEBUG(radius_logger, RADIUS_DBG_TRACE, RADIUS_DECODE_MESSAGE)
        .arg(msgCodeToText(code_))
        .arg(static_cast<unsigned>(code_))
        .arg(static_cast<unsigned>(identifier_))
        .arg(length_)
        .arg(attributes_ ? attributes_->size() : 0);
}

ConstAttributePtr
Message::encodeUserPassword(const ConstAttributePtr& attr) {
    if (!attr || (attr->getValueType() != PW_TYPE_STRING) ||
        (attr->getValueLen() == 0) ||
        (auth_.size() != AUTH_VECTOR_LEN)) {
        isc_throw(Unexpected, "Can't encode User-Password");
    }

    // Get padded password.
    vector<uint8_t> password = attr->toBinary();
    size_t len = password.size();
    len = (len + AUTH_VECTOR_LEN - 1) & ~(AUTH_VECTOR_LEN - 1);
    if (len > AUTH_PASS_LEN) {
        len = AUTH_PASS_LEN;
    }
    password.resize(len);

    // Hide password.
    for (size_t i = 0; i < len; i += AUTH_VECTOR_LEN) {
        boost::scoped_ptr<Hash> md(CryptoLink::getCryptoLink().createHash(MD5));
        md->update(&secret_[0], secret_.size());

        uint8_t* to_hash;
        if (i == 0) {
            to_hash = &auth_[0];
        } else {
            to_hash = &password[i - AUTH_VECTOR_LEN];
        }
        md->update(to_hash, AUTH_VECTOR_LEN);

        vector<uint8_t> digest;
        digest.resize(AUTH_VECTOR_LEN);
        md->final(&digest[0], AUTH_VECTOR_LEN);
        for (size_t j = 0; j < AUTH_VECTOR_LEN; j++) {
            password[i + j] ^= digest[j];
        }
        memset(&digest[0], 0, AUTH_VECTOR_LEN);
    }

    // Return hidden attribute.
    return (Attribute::fromBinary(PW_USER_PASSWORD, password));
}

ConstAttributePtr
Message::decodeUserPassword(const ConstAttributePtr& attr) {
    if (!attr || (attr->getValueType() != PW_TYPE_STRING) ||
        (attr->getValueLen() == 0) ||
        ((attr->getValueLen() % AUTH_VECTOR_LEN) != 0) ||
        (auth_.size() != AUTH_VECTOR_LEN)) {
        isc_throw(Unexpected, "can't decode User-Password");
    }

    // Get hidden password.
    vector<uint8_t> password = attr->toBinary();
    size_t len = password.size();
    if (len > AUTH_PASS_LEN) {
        len = AUTH_PASS_LEN;
        password.resize(len);
    }

    // Get plain text password.
    size_t i = len;
    for (;;) {
        if (i < AUTH_VECTOR_LEN) {
            break;
        }
        i -= AUTH_VECTOR_LEN;
        boost::scoped_ptr<Hash> md(CryptoLink::getCryptoLink().createHash(MD5));
        md->update(&secret_[0], secret_.size());

        uint8_t* to_hash;
        if (i == 0) {
            to_hash = &auth_[0];
        } else {
            to_hash = &password[i - AUTH_VECTOR_LEN];
        }
        md->update(to_hash, AUTH_VECTOR_LEN);

        vector<uint8_t> digest;
        digest.resize(AUTH_VECTOR_LEN);
        md->final(&digest[0], AUTH_VECTOR_LEN);
        for (size_t j = 0; j < AUTH_VECTOR_LEN; j++) {
            password[i + j] ^= digest[j];
        }
        memset(&digest[0], 0, AUTH_VECTOR_LEN);
    }

    // Unpad password (requires no trailing nuls).
    while (password.back() == 0) {
        // Never leave an empty password.
        if (password.size() == 1) {
            break;
        }
        password.pop_back();
    }

    // Return plain text attribute.
    return (Attribute::fromBinary(PW_USER_PASSWORD, password));
}

} // end of namespace isc::radius
} // end of namespace isc
