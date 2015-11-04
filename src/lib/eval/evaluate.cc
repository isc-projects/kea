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

#include <eval/evaluate.h>

namespace isc {
namespace dhcp {

bool evaluate(const Expression& expr, const Pkt& pkt) {
    ValueStack values;
    for (Expression::const_iterator it = expr.begin();
         it != expr.end(); ++it) {
        (*it)->evaluate(pkt, values);
    }
    if (values.size() != 1) {
        isc_throw(EvalBadStack, "Incorrect stack order. Expected exactly "
                  "1 value at the end of evaluatuion, got " << values.size());
    }
    if (values.top() == "false") {
        return (false);
    } else if (values.top() == "true") {
        return (true);
    } else {
        isc_throw(EvalNotBoolError, "Incorrect evaluation type. Expected "
                  "\"false\" or \"true\", got \"" << values.top() << "\"");
    }
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
