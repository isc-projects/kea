// Copyright (C) 2021-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <gss_tsig_key.h>

using namespace isc;
using namespace isc::dns;
using namespace std;

namespace isc {
namespace gss_tsig {

GssTsigKey::GssTsigKey(const string& key_name, gss_ctx_id_t sec_ctx)
    : D2TsigKey(key_name + "::gss-tsig"), sec_ctx_(new GssApiSecCtx(sec_ctx)) {
}

GssTsigKey::GssTsigKey(const string& key_name, const vector<uint8_t>& import)
    : D2TsigKey(key_name + "::gss-tsig"), sec_ctx_(new GssApiSecCtx(import)) {
}

GssTsigKey::~GssTsigKey() {
}

} // end of namespace isc::gss_tsig
} // end of namespace isc
