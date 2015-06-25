// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <dhcp/dhcp6.h>
#include <dhcpsrv/cfg_sedhcp6.h>

namespace isc {
namespace dhcp {

CfgSeDhcp6::CfgSeDhcp6(bool sign_answers /* = false */,
                       bool timestamp_answers /* = false */,
                       bool check_signatures /* = false */,
                       bool check_authorizations /* = false */,
                       bool check_timestamps /* = false */,
                       bool online_validation /* = false */,
                       CfgSeDhcp6::AsymPtr private_key /* = AsymPtr() */,
                       CfgSeDhcp6::AsymPtr credential /* = AsymPtr() */)
    : sign_answers_(sign_answers),
      timestamp_answers_(timestamp_answers),
      check_signatures_(check_signatures),
      check_authorizations_(check_authorizations),
      check_timestamps_(check_timestamps),
      online_validation_(online_validation),
      private_key_(private_key),
      credential_(credential)
{
}

bool CfgSeDhcp6::getSignAnswers() const {
    return (sign_answers_);
}

bool CfgSeDhcp6::getTimestampAnswers() const {
    return (timestamp_answers_);
}

bool CfgSeDhcp6::getCheckSignatures() const {
    return (check_signatures_);
}

bool CfgSeDhcp6::getCheckAuthorizations() const {
    return (check_authorizations_);
}

bool CfgSeDhcp6::getCheckTimestamps() const {
    return (check_timestamps_);
}

bool CfgSeDhcp6::getOnlineValidation() const {
    return (online_validation_);
}

CfgSeDhcp6::AsymPtr CfgSeDhcp6::getPrivateKey() const {
    return (private_key_);
}

CfgSeDhcp6::AsymPtr CfgSeDhcp6::getCredential() const {
    return (credential_);
}

}
}
