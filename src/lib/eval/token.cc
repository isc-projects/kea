// Copyright (C) 2015-2016 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <eval/token.h>
#include <eval/eval_log.h>
#include <util/encode/hex.h>
#include <util/io_utilities.h>
#include <asiolink/io_address.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <boost/lexical_cast.hpp>
#include <cstring>
#include <string>

using namespace isc::dhcp;
using namespace isc::util;
using namespace std;

using isc::util::encode::toHex;

void
TokenString::evaluate(Pkt& /*pkt*/, ValueStack& values) {
    // Literals only push, nothing to pop
    values.push(value_);

    // Log what we pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_STRING)
        .arg('\'' + value_ + '\'');
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
TokenHexString::evaluate(Pkt& /*pkt*/, ValueStack& values) {
    // Literals only push, nothing to pop
    values.push(value_);

    // Log what we pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_HEXSTRING)
        .arg(toHex(value_));
}

TokenIpAddress::TokenIpAddress(const string& addr) : value_("") {
    // Transform IP address into binary format
    vector<uint8_t> binary;
    try {
        asiolink::IOAddress ip(addr);
        binary = ip.toBytes();
    } catch (...) {
        return;
    }

    // Convert to a string (note that binary.size() is 4 or 16, so not 0)
    value_.resize(binary.size());
    memmove(&value_[0], &binary[0], binary.size());
}

void
TokenIpAddress::evaluate(Pkt& /*pkt*/, ValueStack& values) {
    // Literals only push, nothing to pop
    values.push(value_);

    // Log what we pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_IPADDRESS)
        .arg(toHex(value_));
}

OptionPtr
TokenOption::getOption(Pkt& pkt) {
    return (pkt.getOption(option_code_));
}

void
TokenOption::evaluate(Pkt& pkt, ValueStack& values) {
    OptionPtr opt = getOption(pkt);
    std::string opt_str;
    if (opt) {
        if (representation_type_ == TEXTUAL) {
            opt_str = opt->toString();
        } else if (representation_type_ == HEXADECIMAL) {
            std::vector<uint8_t> binary = opt->toBinary();
            opt_str.resize(binary.size());
            if (!binary.empty()) {
                memmove(&opt_str[0], &binary[0], binary.size());
            }
        } else {
            opt_str = "true";
        }
    } else if (representation_type_ == EXISTS) {
        opt_str = "false";
    }

    // Push value of the option or empty string if there was no such option
    // in the packet.
    values.push(opt_str);

    // Log what we pushed, both exists and textual are simple text
    // and can be output directly.  We also include the code number
    // of the requested option.
    if (representation_type_ == HEXADECIMAL) {
        LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_OPTION)
            .arg(option_code_)
            .arg(toHex(opt_str));
    } else {
        LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_OPTION)
            .arg(option_code_)
            .arg('\'' + opt_str + '\'');
    }
}

TokenRelay4Option::TokenRelay4Option(const uint16_t option_code,
                                     const RepresentationType& rep_type)
    :TokenOption(option_code, rep_type) {
}

OptionPtr TokenRelay4Option::getOption(Pkt& pkt) {

    // Check if there is Relay Agent Option.
    OptionPtr rai = pkt.getOption(DHO_DHCP_AGENT_OPTIONS);
    if (!rai) {
        return (OptionPtr());
    }

    // If there is, try to return its suboption
    return (rai->getOption(option_code_));
}

OptionPtr TokenRelay6Option::getOption(Pkt& pkt) {

    try {
        // Check if it's a Pkt6.  If it's not the dynamic_cast will
        // throw std::bad_cast.
        const Pkt6& pkt6 = dynamic_cast<const Pkt6&>(pkt);

        try {
            // Now that we have the right type of packet we can
            // get the option and return it.
            return(pkt6.getRelayOption(option_code_, nest_level_));
        }
        catch (const isc::OutOfRange&) {
            // The only exception we expect is OutOfRange if the nest
            // level is out of range of the encapsulations, for example
            // if nest_level_ is 4 and there are only 2 encapsulations.
            // We return a NULL in that case.
           return (OptionPtr());
        }

    } catch (const std::bad_cast&) {
        isc_throw(EvalTypeError, "Specified packet is not Pkt6");
    }

}

void
TokenPkt::evaluate(Pkt& pkt, ValueStack& values) {

    string value;
    vector<uint8_t> binary;
    string type_str;
    uint32_t len;
    bool is_binary = true;
    switch (type_) {
    case IFACE:
        is_binary = false;
        value = pkt.getIface();
        type_str = "iface";
        break;
    case SRC:
        binary = pkt.getRemoteAddr().toBytes();
        type_str = "src";
        break;
    case DST:
        binary = pkt.getLocalAddr().toBytes();
        type_str = "dst";
        break;
    case LEN:
        // len() returns a size_t but in fact it can't be very large
        // (with UDP transport it fits in 16 bits)
        // the len() method is not const because of DHCPv6 relays.
        // We assume here it has no bad side effects...
        len = static_cast<uint32_t>(const_cast<Pkt&>(pkt).len());
        binary.resize(sizeof(uint32_t));
        static_cast<void>(writeUint32(len, &binary[0], binary.size()));
        type_str = "len";
        break;

    default:
        isc_throw(EvalTypeError, "Bad meta data specified: "
                  << static_cast<int>(type_) );
    }

    if (is_binary) {
        value.resize(binary.size());
        if (!binary.empty()) {
            memmove(&value[0], &binary[0], binary.size());
        }
    }
    values.push(value);

    // Log what we pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_PKT)
        .arg(type_str)
        .arg(is_binary ? toHex(value) : value);
}

void
TokenPkt4::evaluate(Pkt& pkt, ValueStack& values) {

    vector<uint8_t> binary;
    string type_str;
    try {
        // Check if it's a Pkt4. If it's not, the dynamic_cast will throw
        // std::bad_cast (failed dynamic_cast returns NULL for pointers and
        // throws for references).
        const Pkt4& pkt4 = dynamic_cast<const Pkt4&>(pkt);

        switch (type_) {
        case CHADDR: {
            HWAddrPtr hwaddr = pkt4.getHWAddr();
            if (!hwaddr) {
                // This should never happen. Every Pkt4 should always have
                // a hardware address.
                isc_throw(EvalTypeError,
                          "Packet does not have hardware address");
            }
            binary = hwaddr->hwaddr_;
            type_str = "mac";
            break;
        }
        case GIADDR:
            binary = pkt4.getGiaddr().toBytes();
            type_str = "giaddr";
            break;

        case CIADDR:
            binary = pkt4.getCiaddr().toBytes();
            type_str = "ciaddr";
            break;

        case YIADDR:
            binary = pkt4.getYiaddr().toBytes();
            type_str = "yiaddr";
            break;

        case SIADDR:
            binary = pkt4.getSiaddr().toBytes();
            type_str = "siaddr";
            break;

        case HLEN:
            // Pad the uint8_t field to 4 bytes.
            binary.push_back(0);
            binary.push_back(0);
            binary.push_back(0);
            binary.push_back(pkt4.getHlen());
            type_str = "hlen";
            break;

        case HTYPE:
            // Pad the uint8_t field to 4 bytes.
            binary.push_back(0);
            binary.push_back(0);
            binary.push_back(0);
            binary.push_back(pkt4.getHtype());
            type_str = "htype";
            break;

        default:
            isc_throw(EvalTypeError, "Bad field specified: "
                      << static_cast<int>(type_) );
        }

    } catch (const std::bad_cast&) {
        isc_throw(EvalTypeError, "Specified packet is not a Pkt4");
    }

    string value;
    value.resize(binary.size());
    if (!binary.empty()) {
        memmove(&value[0], &binary[0], binary.size());
    }
    values.push(value);

    // Log what we pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_PKT4)
        .arg(type_str)
        .arg(toHex(value));
}

void
TokenPkt6::evaluate(Pkt& pkt, ValueStack& values) {

    vector<uint8_t> binary;
    string type_str;
    try {
      // Check if it's a Pkt6.  If it's not the dynamic_cast will throw
      // std::bad_cast (failed dynamic_cast returns NULL for pointers and
      // throws for references).
      const Pkt6& pkt6 = dynamic_cast<const Pkt6&>(pkt);

      switch (type_) {
      case MSGTYPE: {
          // msg type is an uint8_t integer.  We want a 4 byte string so 0 pad.
          binary.push_back(0);
          binary.push_back(0);
          binary.push_back(0);
          binary.push_back(pkt6.getType());
          type_str = "msgtype";
          break;
      }
      case TRANSID: {
          // transaction id is an uint32_t integer.  We want a 4 byte string so copy
          uint32_t transid = pkt6.getTransid();
          binary.push_back(transid >> 24);
          binary.push_back((transid >> 16) & 0xFF);
          binary.push_back((transid >> 8) & 0xFF);
          binary.push_back(transid & 0xFF);
          type_str = "transid";
          break;
      }
      default:
          isc_throw(EvalTypeError, "Bad field specified: "
                    << static_cast<int>(type_) );
      }

    } catch (const std::bad_cast&) {
        isc_throw(EvalTypeError, "Specified packet is not Pkt6");
    }

    string value;
    value.resize(binary.size());
    memmove(&value[0], &binary[0], binary.size());
    values.push(value);

    // Log what we pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_PKT6)
        .arg(type_str)
        .arg(toHex(value));
}

void
TokenRelay6Field::evaluate(Pkt& pkt, ValueStack& values) {

    vector<uint8_t> binary;
    string type_str;
    try {
        // Check if it's a Pkt6.  If it's not the dynamic_cast will
        // throw std::bad_cast.
        const Pkt6& pkt6 = dynamic_cast<const Pkt6&>(pkt);

        try {
        switch (type_) {
            // Now that we have the right type of packet we can
            // get the option and return it.
            case LINKADDR:
                type_str = "linkaddr";
                binary = pkt6.getRelay6LinkAddress(nest_level_).toBytes();
                break;
            case PEERADDR:
                type_str = "peeraddr";
                binary = pkt6.getRelay6PeerAddress(nest_level_).toBytes();
                break;
            }
        } catch (const isc::OutOfRange&) {
            // The only exception we expect is OutOfRange if the nest
            // level is invalid.  We push "" in that case.
            values.push("");
            // Log what we pushed
            LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_RELAY6_RANGE)
              .arg(type_str)
              .arg(unsigned(nest_level_))
              .arg("0x");
            return;
        }
    } catch (const std::bad_cast&) {
        isc_throw(EvalTypeError, "Specified packet is not Pkt6");
    }

    string value;
    value.resize(binary.size());
    if (!binary.empty()) {
        memmove(&value[0], &binary[0], binary.size());
    }
    values.push(value);

    // Log what we pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_RELAY6)
        .arg(type_str)
        .arg(unsigned(nest_level_))
        .arg(toHex(value));
}

void
TokenEqual::evaluate(Pkt& /*pkt*/, ValueStack& values) {

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

    // Log what we popped and pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_EQUAL)
        .arg(toHex(op1))
        .arg(toHex(op2))
        .arg('\'' + values.top() + '\'');
}

void
TokenSubstring::evaluate(Pkt& /*pkt*/, ValueStack& values) {

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

        // Log what we popped and pushed
        LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_SUBSTRING_EMPTY)
            .arg(len_str)
            .arg(start_str)
            .arg("0x")
            .arg("0x");
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

        // Log what we popped and pushed
        LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_SUBSTRING_RANGE)
            .arg(len_str)
            .arg(start_str)
            .arg(toHex(string_str))
            .arg("0x");
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

    // Log what we popped and pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_SUBSTRING)
        .arg(len_str)
        .arg(start_str)
        .arg(toHex(string_str))
        .arg(toHex(values.top()));
}

void
TokenConcat::evaluate(Pkt& /*pkt*/, ValueStack& values) {

    if (values.size() < 2) {
        isc_throw(EvalBadStack, "Incorrect stack order. Expected at least "
                  "2 values for concat, got " << values.size());
    }

    string op1 = values.top();
    values.pop();
    string op2 = values.top();
    values.pop(); // Dammit, std::stack interface is awkward.

    // The top of the stack was evaluated last so this is the right order
    values.push(op2 + op1);

    // Log what we popped and pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_CONCAT)
        .arg(toHex(op1))
        .arg(toHex(op2))
        .arg(toHex(values.top()));
}

void
TokenNot::evaluate(Pkt& /*pkt*/, ValueStack& values) {

    if (values.size() == 0) {
        isc_throw(EvalBadStack, "Incorrect empty stack.");
    }

    string op = values.top();
    values.pop();
    bool val = toBool(op);

    if (!val) {
        values.push("true");
    } else {
        values.push("false");
    }

    // Log what we popped and pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_NOT)
        .arg('\'' + op + '\'')
        .arg('\'' + values.top() + '\'');
}

void
TokenAnd::evaluate(Pkt& /*pkt*/, ValueStack& values) {

    if (values.size() < 2) {
        isc_throw(EvalBadStack, "Incorrect stack order. Expected at least "
                  "2 values for and operator, got " << values.size());
    }

    string op1 = values.top();
    values.pop();
    bool val1 = toBool(op1);
    string op2 = values.top();
    values.pop(); // Dammit, std::stack interface is awkward.
    bool val2 = toBool(op2);

    if (val1 && val2) {
        values.push("true");
    } else {
        values.push("false");
    }

    // Log what we popped and pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_AND)
        .arg('\'' + op1 + '\'')
        .arg('\'' + op2 + '\'')
        .arg('\'' + values.top() + '\'');
}

void
TokenOr::evaluate(Pkt& /*pkt*/, ValueStack& values) {

    if (values.size() < 2) {
        isc_throw(EvalBadStack, "Incorrect stack order. Expected at least "
                  "2 values for or operator, got " << values.size());
    }

    string op1 = values.top();
    values.pop();
    bool val1 = toBool(op1);
    string op2 = values.top();
    values.pop(); // Dammit, std::stack interface is awkward.
    bool val2 = toBool(op2);

    if (val1 || val2) {
        values.push("true");
    } else {
        values.push("false");
    }

    // Log what we popped and pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_OR)
        .arg('\'' + op1 + '\'')
        .arg('\'' + op2 + '\'')
        .arg('\'' + values.top() + '\'');
}
