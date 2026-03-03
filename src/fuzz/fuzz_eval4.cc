// Copyright (C) 2025 Ada Logcis Ltd.
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
////////////////////////////////////////////////////////////////////////////////
#include "config.h"
#include <fuzzer/FuzzedDataProvider.h>

#include <eval/eval_context.h>
#include <eval/evaluate.h>
#include <eval/dependency.h>

#include <dhcp/pkt4.h>
#include <dhcp/dhcp4.h>

#include <cstdlib>
#include <string>

using namespace isc;
using namespace isc::eval;
using namespace isc::dhcp;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* Data, size_t Size) {
    FuzzedDataProvider fdp(Data, Size);
    EvalContext ctx(Option::V4);
    auto idx = fdp.ConsumeIntegralInRange<uint8_t>(1, 18);
    const std::string payload = fdp.ConsumeRemainingBytesAsString();

    try {
        Pkt4 pkt(idx, 0);
        // Fuzz boolean parsing
        if (ctx.parseString(payload, EvalContext::PARSER_BOOL)) {
            ValueStack vs;
            Expression& exp_bool = ctx.expression_;
            ExpressionPtr exp_bool_ptr(new Expression(exp_bool));

            evaluateRaw(exp_bool, pkt, vs);
            evaluateBool(exp_bool, pkt);
            evaluateString(exp_bool, pkt);
            dependOnClass(exp_bool_ptr, payload);
        }
    } catch(const isc::Exception&){}

    // Fuzz string parsing
    try {
        Pkt4 pkt(idx, 0);
        if (ctx.parseString(payload, EvalContext::PARSER_STRING)) {
            ValueStack vs;
            Expression& exp_str = ctx.expression_;
            ExpressionPtr exp_str_ptr(new Expression(exp_str));

            evaluateRaw(exp_str, pkt, vs);
            evaluateBool(exp_str, pkt);
            evaluateString(exp_str, pkt);
            dependOnClass(exp_str_ptr, payload);
        }
    } catch(const isc::Exception&){}

    location loc;
    try {
        // Fuzz converter
        ctx.convertOptionCode(payload, loc);
    } catch(const isc::Exception&) {}

    try {
        ctx.convertOptionName(payload, loc);
    } catch(const isc::Exception&) {}

    try {
        ctx.convertNestLevelNumber(payload, loc);
    } catch(const isc::Exception&) {
        // Slient exceptions
    }

    return 0;
}
