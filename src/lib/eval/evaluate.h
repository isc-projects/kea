// Copyright (C) 2015-2017 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef EVALUATE_H
#define EVALUATE_H

#include <eval/token.h>
#include <string>

namespace isc {
namespace dhcp {

/// @brief Evaluate a RPN expression for a v4 or v6 packet and return
///        a true or false decision
///
/// @param expr the RPN expression, i.e., a vector of parsed tokens
/// @param pkt  The v4 or v6 packet
/// @return the boolean decision
/// @throw EvalStackError if there is not exactly one element on the value
///        stack at the end of the evaluation
/// @throw EvalTypeError if the value at the top of the stack at the
///        end of the evaluation is not "false" or "true"
bool evaluateBool(const Expression& expr, Pkt& pkt);


std::string evaluateString(const Expression& expr, Pkt& pkt);

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif
