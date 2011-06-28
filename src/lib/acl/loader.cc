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

#include "loader.h"

using namespace std;

namespace isc {
namespace acl {

BasicAction defaultActionLoader(data::ConstElementPtr actionEl) {
    try {
        const string action(actionEl->stringValue());
        if (action == "ACCEPT") {
            return (ACCEPT);
        } else if (action == "REJECT") {
            return (REJECT);
        } else if (action == "DROP") {
            return (DROP);
        } else {
            throw LoaderError(__FILE__, __LINE__,
                              string("Unknown action '" + action + "'").
                                  c_str(),
                              actionEl);
        }
    }
    catch (const data::TypeError&) {
        throw LoaderError(__FILE__, __LINE__,
                          "Invalid element type for action, must be string",
                          actionEl);
    }
}

}
}
