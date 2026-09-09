// Copyright (C) 2025-2026 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.
//
// Developed by AdaLogics under contract to ISC.

#include <config.h>

#include <dhcp/dhcp6.h>
#include <dhcp/pkt6.h>
#include <eval/dependency.h>
#include <eval/eval_context.h>
#include <eval/evaluate.h>

#include <cstdlib>
#include <iostream>
#include <string>

#include <fuzzer/FuzzedDataProvider.h>

using namespace isc;
using namespace isc::eval;
using namespace isc::dhcp;

extern "C" int LLVMFuzzerTestOneInput(const uint8_t* data, size_t size) {
    // Upper bound on oversized inputs: 16KiB. Last reported timeout was on 20KB.
    if (size > 16384) {
        std::cout << "Skipping: input size > 16KiB: " << size << std::endl;
        return 0;
    }

    FuzzedDataProvider fdp(data, size);
    EvalContext ctx(Option::V6);

    auto idx = fdp.ConsumeIntegralInRange<uint8_t>(1, 18);
    const std::string payload = fdp.ConsumeRemainingBytesAsString();

    try {
        Pkt6 pkt(idx, 0);
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
    } catch(const isc::Exception&) {
        // Silent exceptions
    }

    try {
        // Fuzz string parsing
        Pkt6 pkt(idx, 0);
        if (ctx.parseString(payload, EvalContext::PARSER_STRING)) {
            ValueStack vs;
            Expression& exp_str = ctx.expression_;
            ExpressionPtr exp_str_ptr(new Expression(exp_str));

            evaluateRaw(exp_str, pkt, vs);
            evaluateBool(exp_str, pkt);
            evaluateString(exp_str, pkt);
            dependOnClass(exp_str_ptr, payload);
        }
    } catch (const isc::Exception&) {
        // Silent exceptions
    }

    location loc;
    try {
        // Fuzz converter
        ctx.convertOptionCode(payload, loc);
    } catch (const isc::Exception&) {
        // Silent exceptions
    }

    try {
        ctx.convertOptionName(payload, loc);
    } catch (const isc::Exception&) {
        // Silent exceptions
    }

    try {
        ctx.convertNestLevelNumber(payload, loc);
    } catch (const isc::Exception&) {
        // Silent exceptions
    }

    return 0;
}
