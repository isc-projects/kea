// Copyright (C) 2018-2024 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/encode/encode.h>
#include <util/str.h>
#include <yang/adaptor_host.h>

#include <iomanip>
#include <sstream>
#include <vector>

using namespace std;
using namespace isc::data;
using namespace isc::util;
using namespace isc::util::str;

namespace isc {
namespace yang {

const string
AdaptorHost::STD_CHARACTERS =
    "0123456789@ABCDEFGHIJKLMNOPQRSTUVWXYZabcdefghijklmnopqrstuvwxyz-.@_";

void
AdaptorHost::quoteIdentifier(ElementPtr host) {
    ConstElementPtr flex_id = host->get("flex-id");
    if (!flex_id) {
        return;
    }
    const string& id = flex_id->stringValue();
    // Empty is allowed.
    if (id.empty()) {
        return;
    }
    // No special and no not printable characters?
    if (id.find_first_not_of(STD_CHARACTERS) == string::npos) {
        return;
    }
    // Quoted identifier?
    vector<uint8_t> binary = quotedStringToBinary(id);
    if (binary.empty()) {
        binary.assign(id.begin(), id.end());
    }
    // Convert in hexadecimal (from DUID::toText()).
    host->set("flex-id", Element::create(dumpAsHex(binary)));
}

}  // namespace yang
}  // namespace isc
