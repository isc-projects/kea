// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <util/str.h>
#include <dhcp/dhcp4.h>
#include <radius_utils.h>
#include <cctype>
#include <iomanip>
#include <sstream>

using namespace std;
using namespace isc;
using namespace isc::dhcp;
using namespace isc::util;

namespace isc {
namespace radius {

string
canonize(const string& hexdump) {
    string result(hexdump);
    for (char& c : result) {
        switch (c) {
        case 'A':
        case 'B':
        case 'C':
        case 'D':
        case 'E':
        case 'F':
            // Lower case
            c += 'a' - 'A';
            break;
        case ':':
            // Canonical format use - as the separator.
            c = '-';
            break;
        default:
            break;
        }
    }
    return (result);
}

vector<uint8_t>
pop0(const ClientIdPtr& client_id) {
    vector<uint8_t> content = client_id->getClientId();
    if ((content.size() > 1) && (content[0] == 0)) {
        content.erase(content.begin());
    }
    return (content);
}

vector<uint8_t>
pop0(const DuidPtr& duid) {
    vector<uint8_t> content = duid->getDuid();
    if ((content[0] == 0) && (content[1] == 0)) {
        content.erase(content.begin(), content.begin() + 2);
    }
    return (content);
}

string
toPrintable(const vector<uint8_t>& content) {
    if (content.empty()) {
        return ("");
    }
    if (str::isPrintable(content)) {
        string repr;
        repr.resize(content.size());
        memmove(&repr[0], &content[0], repr.size());
        return (repr);
    } else {
        return (toHex(content));
    }
}

string
toHex(const vector<uint8_t>& content) {
    ostringstream repr;
    repr << hex;
    bool delim = false;
    for (const unsigned char& ch : content) {
        if (delim) {
            repr << ":";
        }
        repr << setw(2) << setfill('0') << static_cast<unsigned>(ch);
        delim = true;
    }
    return (repr.str());
}

vector<uint8_t>
extractDuid(const ClientIdPtr& client_id, bool& extracted) {
    vector<uint8_t> content = client_id->getClientId();
    extracted = false;
    if ((content.size() > 5) && (content[0] == CLIENT_ID_OPTION_TYPE_DUID)) {
        extracted = true;
        content.erase(content.begin(), content.begin() + 5);
    }
    // Not an error condition but likely to be unused anyway...
    return (content);
}

} // end of namespace isc::radius
} // end of namespace isc
