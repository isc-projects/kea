// Copyright (C) 2015-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <eval/evaluate.h>

namespace isc {
namespace dhcp {

bool evaluateBool(const Expression& expr, Pkt& pkt) {
    ValueStack values;
    for (Expression::const_iterator it = expr.begin();
         it != expr.end(); ++it) {
        (*it)->evaluate(pkt, values);
    }
    if (values.size() != 1) {
        isc_throw(EvalBadStack, "Incorrect stack order. Expected exactly "
                  "1 value at the end of evaluation, got " << values.size());
    }
    return (Token::toBool(values.top()));
}

std::string
evaluateString(const Expression& expr, Pkt& pkt) {
    ValueStack values;
    for (auto it = expr.begin(); it != expr.end(); ++it) {
        (*it)->evaluate(pkt, values);
    }
    if (values.size() != 1) {
        isc_throw(EvalBadStack, "Incorrect stack order. Expected exactly "
                  "1 value at the end of evaluation, got " << values.size());
    }
    return (values.top());
}


}; // end of isc::dhcp namespace
}; // end of isc namespace
