// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <eval/token.h>
#include <eval/eval_log.h>
#include <util/encode/hex.h>
#include <boost/lexical_cast.hpp>
#include <cstring>
#include <string>

using namespace isc::dhcp;
using namespace std;

void
TokenString::evaluate(const Pkt& /*pkt*/, ValueStack& values) {
    // Literals only push, nothing to pop
    values.push(value_);
}

TokenHexString::TokenHexString(const string& str) : value_("") {
    // Check string starts "0x" or "0x" and has at least one additional character.
    if ((str.size() < 3) ||
        (str[0] != '0') ||
        ((str[1] != 'x') && (str[1] != 'X'))) {
        return;
    }
    string digits = str.substr(2);

    // Transform string of hexadecimal digits into binary format
    vector<uint8_t> binary;
    try {
        // The decodeHex function expects that the string contains an
        // even number of digits. If we don't meet this requirement,
        // we have to insert a leading 0.
        if ((digits.length() % 2) != 0) {
            digits = digits.insert(0, "0");
        }
        util::encode::decodeHex(digits, binary);
    } catch (...) {
        return;
    }

    // Convert to a string (note that binary.size() cannot be 0)
    value_.resize(binary.size());
    memmove(&value_[0], &binary[0], binary.size());
}

void
TokenHexString::evaluate(const Pkt& /*pkt*/, ValueStack& values) {
    // Literals only push, nothing to pop
    values.push(value_);
}

OptionPtr
TokenOption::getOption(const Pkt& pkt) {
    return (pkt.getOption(option_code_));
}

void
TokenOption::evaluate(const Pkt& pkt, ValueStack& values) {
    OptionPtr opt = getOption(pkt);
    std::string opt_str;
    if (opt) {
        if (representation_type_ == TEXTUAL) {
            opt_str = opt->toString();
        } else {
            std::vector<uint8_t> binary = opt->toBinary();
            opt_str.resize(binary.size());
            if (!binary.empty()) {
                memmove(&opt_str[0], &binary[0], binary.size());
            }
        }
    }

    // Push value of the option or empty string if there was no such option
    // in the packet.
    values.push(opt_str);
}

void
TokenEqual::evaluate(const Pkt& /*pkt*/, ValueStack& values) {

    if (values.size() < 2) {
        isc_throw(EvalBadStack, "Incorrect stack order. Expected at least "
                  "2 values for == operator, got " << values.size());
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

void
TokenSubstring::evaluate(const Pkt& /*pkt*/, ValueStack& values) {

    if (values.size() < 3) {
        isc_throw(EvalBadStack, "Incorrect stack order. Expected at least "
                  "3 values for substring operator, got " << values.size());
    }

    string len_str = values.top();
    values.pop();
    string start_str = values.top();
    values.pop();
    string string_str = values.top();
    values.pop();

    // If we have no string to start with we push an empty string and leave
    if (string_str.empty()) {
        values.push("");
        return;
    }

    // Convert the starting position and length from strings to numbers
    // the length may also be "all" in which case simply make it the
    // length of the string.
    // If we have a problem push an empty string and leave
    int start_pos;
    int length;
    try {
        start_pos = boost::lexical_cast<int>(start_str);
    } catch (const boost::bad_lexical_cast&) {
        isc_throw(EvalTypeError, "the parameter '" << start_str
                  << "' for the starting postion of the substring "
                  << "couldn't be converted to an integer.");
    }
    try {
        if (len_str == "all") {
            length = string_str.length();
        } else {
            length = boost::lexical_cast<int>(len_str);
        }
    } catch (const boost::bad_lexical_cast&) {
        isc_throw(EvalTypeError, "the parameter '" << len_str
                  << "' for the length of the substring "
                  << "couldn't be converted to an integer.");
    }

    const int string_length = string_str.length();
    // If the starting postion is outside of the string push an
    // empty string and leave
    if ((start_pos < -string_length) || (start_pos >= string_length)) {
        values.push("");
        return;
    }

    // Adjust the values to be something for substr.  We first figure out
    // the starting postion, then update it and the length to get the
    // characters before or after it depending on the sign of length
    if (start_pos < 0) {
        start_pos = string_length + start_pos;
    }

    if (length < 0) {
        length = -length;
        if (length <=  start_pos){
            start_pos -= length;
        } else {
            length = start_pos;
            start_pos = 0;
        }
    }

    // and finally get the substring
    values.push(string_str.substr(start_pos, length));
}

TokenRelay4Option::TokenRelay4Option(const uint16_t option_code,
                                     const RepresentationType& rep_type)
    :TokenOption(option_code, rep_type) {
}

OptionPtr TokenRelay4Option::getOption(const Pkt& pkt) {

    // Check if there is Relay Agent Option.
    OptionPtr rai = pkt.getOption(DHO_DHCP_AGENT_OPTIONS);
    if (!rai) {
        return (OptionPtr());
    }

    // If there is, try to return its suboption
    return (rai->getOption(option_code_));
}
