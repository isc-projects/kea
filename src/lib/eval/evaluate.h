// Copyright (C) 2015-2024 Internet Systems Consortium, Inc. ("ISC")
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

/// @brief Evaluate a RPN expression for a v4 or v6 packet
///
/// For tests and as the common part of the two next routines.
///
/// @param expr   the RPN expression, i.e., a vector of parsed tokens
/// @param pkt    The v4 or v6 packet
/// @param values The stack of values
/// @throw EvalBadLabel if there is a forward branch to a not found target.
void evaluateRaw(const Expression& expr, Pkt& pkt, ValueStack& values);

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
/// @throw EvalBadLabel if there is a forward branch to a not found target.
bool evaluateBool(const Expression& expr, Pkt& pkt);


/// @brief Evaluate a RPN expression for a v4 or v6 packet and return
///        a string value
///
/// @param expr the RPN expression, i.e., a vector of parsed tokens
/// @param pkt  The v4 or v6 packet
/// @return the string value
/// @throw EvalStackError if there is not exactly one element on the value
///        stack at the end of the evaluation
/// @throw EvalTypeError if the value at the top of the stack at the
///        end of the evaluation is not "false" or "true"
/// @throw EvalBadLabel if there is a forward branch to a not found target.
std::string evaluateString(const Expression& expr, Pkt& pkt);

}  // end of isc::dhcp namespace
}  // end of isc namespace

#endif
