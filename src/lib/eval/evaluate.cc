// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

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
        isc_throw(EvalTypeError, "Incorrect evaluation type. Expected "
                  "\"false\" or \"true\", got \"" << values.top() << "\"");
    }
}

}; // end of isc::dhcp namespace
}; // end of isc namespace
