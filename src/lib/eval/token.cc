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

#include <eval/token.h>
#include <string>

using namespace isc::dhcp;
using namespace std;

void
TokenString::evaluate(const Pkt& /*pkt*/, ValueStack& values) {
    // Literals only push, nothing to pop
    values.push(value_);
}

void
TokenOption::evaluate(const Pkt& pkt, ValueStack& values) {
    OptionPtr opt = pkt.getOption(option_code_);
    if (opt) {
        values.push(opt->toString());
    } else {
        // Option not found, push empty string
        values.push("");
    }
}

void
TokenEqual::evaluate(const Pkt& /*pkt*/, ValueStack& values) {

    if (values.size() < 2) {
        isc_throw(EvalBadStack, "Incorrect stack order. Expected at least "
                  "2 values, got " << values.size());
    }

    string op1 = values.top();
    values.pop();
    string op2 = values.top();
    values.pop(); // Dammit, std::stack interface is awkward.

    if (op1 == op2)
        values.push("true");
    else
        values.push("false");
}
