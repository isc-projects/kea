// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#include <server_common/keyring.h>

using namespace isc::dns;
using namespace isc::data;

namespace isc {
namespace server_common {

typedef boost::shared_ptr<TSIGKeyRing> KeyringPtr;

KeyringPtr keyring;

namespace {

void
updateKeyring(const std::string&, ConstElementPtr data) {
    ConstElementPtr list(data->get("keys"));
    KeyringPtr load(new TSIGKeyRing);
    for (size_t i(0); i < list->size(); ++ i) {
        load->add(TSIGKey(list->get(i)->stringValue()));
    }
    keyring.swap(load);
}

}

void
initKeyring(config::ModuleCCSession& session) {
    if (keyring) {
        // We are already initialized
        return;
    }
    session.addRemoteConfig("tsig_keys", updateKeyring);
}

void
deinitKeyring(config::ModuleCCSession& session) {
    if (!keyring) {
        // Not initialized, ignore it
        return;
    }
    keyring.reset();
    session.removeRemoteConfig("tsig_keys");
}

}
}
