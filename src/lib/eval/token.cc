// Copyright (C) 2015-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <eval/token.h>
#include <eval/eval_log.h>
#include <eval/eval_context.h>
#include <util/encode/encode.h>
#include <util/io.h>
#include <asiolink/io_address.h>
#include <dhcp/pkt4.h>
#include <dhcp/pkt6.h>
#include <boost/lexical_cast.hpp>
#include <dhcp/dhcp4.h>
#include <dhcp/dhcp6.h>
#include <dhcp/option_vendor.h>
#include <dhcp/option_vendor_class.h>

#include <boost/algorithm/string.hpp>
#include <boost/algorithm/string/classification.hpp>
#include <boost/algorithm/string/split.hpp>

#include <cstring>
#include <string>
#include <iomanip>
#include <sstream>

using namespace isc::asiolink;
using namespace isc::dhcp;
using namespace isc::util;
using namespace std;

using isc::util::encode::toHex;

unsigned
TokenString::evaluate(Pkt& pkt, ValueStack& values) {
    // Literals only push, nothing to pop
    values.push(value_);

    // Log what we pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_STRING)
        .arg(pkt.getLabel())
        .arg('\'' + value_ + '\'');

    return (0);
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

unsigned
TokenHexString::evaluate(Pkt& pkt, ValueStack& values) {
    // Literals only push, nothing to pop
    values.push(value_);

    // Log what we pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_HEXSTRING)
        .arg(pkt.getLabel())
        .arg(toHex(value_));

    return (0);
}

unsigned
TokenLowerCase::evaluate(Pkt& pkt, ValueStack& values) {
    if (values.size() == 0) {
        isc_throw(EvalBadStack, "Incorrect empty stack.");
    }

    string op = values.top();

    values.pop();
    string result(boost::algorithm::to_lower_copy(op));
    values.push(result);

    // Log what we pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_LCASE)
        .arg(pkt.getLabel())
        .arg('\'' + op + '\'')
        .arg('\'' + result + '\'');

    return (0);
}

unsigned
TokenUpperCase::evaluate(Pkt& pkt, ValueStack& values) {
    if (values.size() == 0) {
        isc_throw(EvalBadStack, "Incorrect empty stack.");
    }

    string op = values.top();

    values.pop();
    string result(boost::algorithm::to_upper_copy(op));
    values.push(result);

    // Log what we pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_UCASE)
        .arg(pkt.getLabel())
        .arg('\'' + op + '\'')
        .arg('\'' + result + '\'');

    return (0);
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

unsigned
TokenIpAddress::evaluate(Pkt& pkt, ValueStack& values) {
    // Literals only push, nothing to pop
    values.push(value_);

    // Log what we pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_IPADDRESS)
        .arg(pkt.getLabel())
        .arg(toHex(value_));

    return (0);
}

unsigned
TokenIpAddressToText::evaluate(Pkt& pkt, ValueStack& values) {
    if (values.size() == 0) {
        isc_throw(EvalBadStack, "Incorrect empty stack.");
    }

    string op = values.top();
    size_t size = op.size();

    if (!size) {
        return (0);
    }

    values.pop();

    if ((size != V4ADDRESS_LEN) && (size != V6ADDRESS_LEN)) {
        isc_throw(EvalTypeError, "Can not convert to valid address.");
    }

    std::vector<uint8_t> binary(op.begin(), op.end());

    if (size == V4ADDRESS_LEN) {
        op = asiolink::IOAddress::fromBytes(AF_INET, binary.data()).toText();
    } else {
        op = asiolink::IOAddress::fromBytes(AF_INET6, binary.data()).toText();
    }

    values.push(op);

    // Log what we pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_IPADDRESSTOTEXT)
        .arg(pkt.getLabel())
        .arg(op);

    return (0);
}

unsigned
TokenInt8ToText::evaluate(Pkt& pkt, ValueStack& values) {
    if (values.size() == 0) {
        isc_throw(EvalBadStack, "Incorrect empty stack.");
    }

    string op = values.top();
    size_t size = op.size();

    if (!size) {
      return (0);
    }

    values.pop();

    if (size != sizeof(int8_t)) {
        isc_throw(EvalTypeError, "Can not convert to valid int8.");
    }

    stringstream tmp;
    tmp << static_cast<int32_t>(*(reinterpret_cast<const int8_t*>(op.data())));
    op = tmp.str();
    values.push(op);

    // Log what we pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_INT8TOTEXT)
        .arg(pkt.getLabel())
        .arg(op);

    return (0);
}

unsigned
TokenInt16ToText::evaluate(Pkt& pkt, ValueStack& values) {
    if (values.size() == 0) {
        isc_throw(EvalBadStack, "Incorrect empty stack.");
    }

    string op = values.top();
    size_t size = op.size();

    if (!size) {
      return (0);
    }

    values.pop();

    if (size != sizeof(int16_t)) {
        isc_throw(EvalTypeError, "Can not convert to valid int16.");
    }

    stringstream tmp;
    int16_t value = static_cast<int16_t>(readUint16(const_cast<const char*>(op.data()), size));
    tmp << value;
    op = tmp.str();
    values.push(op);

    // Log what we pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_INT16TOTEXT)
        .arg(pkt.getLabel())
        .arg(op);

    return (0);
}

unsigned
TokenInt32ToText::evaluate(Pkt& pkt, ValueStack& values) {
    if (values.size() == 0) {
        isc_throw(EvalBadStack, "Incorrect empty stack.");
    }

    string op = values.top();
    size_t size = op.size();

    if (!size) {
      return (0);
    }

    values.pop();

    if (size != sizeof(int32_t)) {
        isc_throw(EvalTypeError, "Can not convert to valid int32.");
    }

    stringstream tmp;
    int32_t value = static_cast<int32_t>(readUint32(const_cast<const char*>(op.data()), size));
    tmp << value;
    op = tmp.str();
    values.push(op);

    // Log what we pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_INT32TOTEXT)
        .arg(pkt.getLabel())
        .arg(op);

    return (0);
}

unsigned
TokenUInt8ToText::evaluate(Pkt& pkt, ValueStack& values) {
    if (values.size() == 0) {
        isc_throw(EvalBadStack, "Incorrect empty stack.");
    }

    string op = values.top();
    size_t size = op.size();

    if (!size) {
      return (0);
    }

    values.pop();

    if (size != sizeof(uint8_t)) {
        isc_throw(EvalTypeError, "Can not convert to valid uint8.");
    }

    stringstream tmp;
    tmp << static_cast<uint32_t>(*(reinterpret_cast<const uint8_t*>(op.data())));
    op = tmp.str();
    values.push(op);

    // Log what we pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_UINT8TOTEXT)
        .arg(pkt.getLabel())
        .arg(op);

    return (0);
}

unsigned
TokenUInt16ToText::evaluate(Pkt& pkt, ValueStack& values) {
    if (values.size() == 0) {
        isc_throw(EvalBadStack, "Incorrect empty stack.");
    }

    string op = values.top();
    size_t size = op.size();

    if (!size) {
      return (0);
    }

    values.pop();

    if (size != sizeof(uint16_t)) {
        isc_throw(EvalTypeError, "Can not convert to valid uint16.");
    }

    stringstream tmp;
    uint16_t value = readUint16(const_cast<const char*>(op.data()), size);
    tmp << value;
    op = tmp.str();
    values.push(op);

    // Log what we pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_UINT16TOTEXT)
        .arg(pkt.getLabel())
        .arg(op);

    return (0);
}

unsigned
TokenUInt32ToText::evaluate(Pkt& pkt, ValueStack& values) {
    if (values.size() == 0) {
        isc_throw(EvalBadStack, "Incorrect empty stack.");
    }

    string op = values.top();
    size_t size = op.size();

    if (!size) {
      return (0);
    }

    values.pop();

    if (size != sizeof(uint32_t)) {
        isc_throw(EvalTypeError, "Can not convert to valid uint32.");
    }

    stringstream tmp;
    uint32_t value = readUint32(const_cast<const char*>(op.data()), size);
    tmp << value;
    op = tmp.str();
    values.push(op);

    // Log what we pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_UINT32TOTEXT)
        .arg(pkt.getLabel())
        .arg(op);

    return (0);
}

OptionPtr
TokenOption::getOption(Pkt& pkt) {
    return (pkt.getOption(option_code_));
}

unsigned
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
            .arg(pkt.getLabel())
            .arg(option_code_)
            .arg(toHex(opt_str));
    } else {
        LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_OPTION)
            .arg(pkt.getLabel())
            .arg(option_code_)
            .arg('\'' + opt_str + '\'');
    }

    return (0);
}

std::string
TokenOption::pushFailure(ValueStack& values) {
    std::string txt;
    if (representation_type_ == EXISTS) {
        txt = "false";
    }
    values.push(txt);
    return (txt);
}

TokenRelay4Option::TokenRelay4Option(const uint16_t option_code,
                                     const RepresentationType& rep_type)
    : TokenOption(option_code, rep_type) {
}

OptionPtr
TokenRelay4Option::getOption(Pkt& pkt) {
    // Check if there is Relay Agent Option.
    OptionPtr rai = pkt.getOption(DHO_DHCP_AGENT_OPTIONS);
    if (!rai) {
        return (OptionPtr());
    }

    // If there is, try to return its suboption
    return (rai->getOption(option_code_));
}

OptionPtr
TokenRelay6Option::getOption(Pkt& pkt) {
    try {
        // Check if it's a Pkt6.  If it's not the dynamic_cast will
        // throw std::bad_cast.
        Pkt6& pkt6 = dynamic_cast<Pkt6&>(pkt);

        try {
            // Now that we have the right type of packet we can
            // get the option and return it.
            if (nest_level_ >= 0) {
                uint8_t nesting_level = static_cast<uint8_t>(nest_level_);
                return(pkt6.getRelayOption(option_code_, nesting_level));
            } else {
                int nesting_level = pkt6.relay_info_.size() + nest_level_;
                if (nesting_level < 0) {
                    return (OptionPtr());
                }
                return(pkt6.getRelayOption(option_code_,
                                           static_cast<uint8_t>(nesting_level)));
            }
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

unsigned
TokenPkt::evaluate(Pkt& pkt, ValueStack& values) {
    string value;
    vector<uint8_t> binary;
    string type_str;
    bool is_binary = true;
    bool print_hex = true;
    switch (type_) {
    case IFACE:
        is_binary = false;
        print_hex = false;
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
        value = EvalContext::fromUint32(static_cast<uint32_t>(const_cast<Pkt&>(pkt).len()));
        is_binary = false;
        type_str = "len";
        break;

    default:
        isc_throw(EvalTypeError, "Bad meta data specified: " << static_cast<int>(type_));
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
        .arg(pkt.getLabel())
        .arg(type_str)
        .arg(print_hex ? toHex(value) : value);

    return (0);
}

unsigned
TokenPkt4::evaluate(Pkt& pkt, ValueStack& values) {
    vector<uint8_t> binary;
    string value;
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
            value = EvalContext::fromUint32(pkt4.getHlen());
            type_str = "hlen";
            break;
        case HTYPE:
            // Pad the uint8_t field to 4 bytes.
            value = EvalContext::fromUint32(pkt4.getHtype());
            type_str = "htype";
            break;
        case MSGTYPE:
            value = EvalContext::fromUint32(pkt4.getType());
            type_str = "msgtype";
            break;
        case TRANSID:
            value = EvalContext::fromUint32(pkt4.getTransid());
            type_str = "transid";
            break;
        default:
            isc_throw(EvalTypeError, "Bad field specified: " << static_cast<int>(type_));
        }

    } catch (const std::bad_cast&) {
        isc_throw(EvalTypeError, "Specified packet is not a Pkt4");
    }

    if (!binary.empty()) {
        value.resize(binary.size());
        memmove(&value[0], &binary[0], binary.size());
    }
    values.push(value);

    // Log what we pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_PKT4)
        .arg(pkt.getLabel())
        .arg(type_str)
        .arg(toHex(value));

    return (0);
}

unsigned
TokenPkt6::evaluate(Pkt& pkt, ValueStack& values) {
    string value;
    string type_str;
    try {
      // Check if it's a Pkt6.  If it's not the dynamic_cast will throw
      // std::bad_cast (failed dynamic_cast returns NULL for pointers and
      // throws for references).
      const Pkt6& pkt6 = dynamic_cast<const Pkt6&>(pkt);

      switch (type_) {
      case MSGTYPE: {
          // msg type is an uint8_t integer.  We want a 4 byte string so 0 pad.
          value = EvalContext::fromUint32(pkt6.getType());
          type_str = "msgtype";
          break;
      }
      case TRANSID: {
          // transaction id is an uint32_t integer.  We want a 4 byte string so copy
          value = EvalContext::fromUint32(pkt6.getTransid());
          type_str = "transid";
          break;
      }
      default:
          isc_throw(EvalTypeError, "Bad field specified: " << static_cast<int>(type_));
      }

    } catch (const std::bad_cast&) {
        isc_throw(EvalTypeError, "Specified packet is not Pkt6");
    }

    values.push(value);

    // Log what we pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_PKT6)
        .arg(pkt.getLabel())
        .arg(type_str)
        .arg(toHex(value));

    return (0);
}

unsigned
TokenRelay6Field::evaluate(Pkt& pkt, ValueStack& values) {
    vector<uint8_t> binary;
    string type_str;
    try {
        // Check if it's a Pkt6.  If it's not the dynamic_cast will
        // throw std::bad_cast.
        const Pkt6& pkt6 = dynamic_cast<const Pkt6&>(pkt);
        uint8_t relay_level;

        try {
            if (nest_level_ >= 0) {
                relay_level = static_cast<uint8_t>(nest_level_);
            } else {
                int nesting_level = pkt6.relay_info_.size() + nest_level_;
                if (nesting_level < 0) {
                    // Don't throw OutOfRange here
                    nesting_level = 32;
                }
                relay_level = static_cast<uint8_t>(nesting_level);
            }
            switch (type_) {
            // Now that we have the right type of packet we can
            // get the option and return it.
            case LINKADDR:
                type_str = "linkaddr";
                binary = pkt6.getRelay6LinkAddress(relay_level).toBytes();
                break;
            case PEERADDR:
                type_str = "peeraddr";
                binary = pkt6.getRelay6PeerAddress(relay_level).toBytes();
                break;
            }
        } catch (const isc::OutOfRange&) {
            // The only exception we expect is OutOfRange if the nest
            // level is invalid.  We push "" in that case.
            values.push("");
            // Log what we pushed
            LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_RELAY6_RANGE)
                .arg(pkt.getLabel())
                .arg(type_str)
                .arg(int(nest_level_))
                .arg("0x");
            return (0);
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
        .arg(pkt.getLabel())
        .arg(type_str)
        .arg(int(nest_level_))
        .arg(toHex(value));

    return (0);
}

unsigned
TokenEqual::evaluate(Pkt& pkt, ValueStack& values) {
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
        .arg(pkt.getLabel())
        .arg(toHex(op1))
        .arg(toHex(op2))
        .arg('\'' + values.top() + '\'');

    return (0);
}

unsigned
TokenSubstring::evaluate(Pkt& pkt, ValueStack& values) {
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
            .arg(pkt.getLabel())
            .arg(len_str)
            .arg(start_str)
            .arg("0x")
            .arg("0x");
        return (0);
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
                  << "' for the starting position of the substring "
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
    // If the starting position is outside of the string push an
    // empty string and leave
    if ((start_pos < -string_length) || (start_pos >= string_length)) {
        values.push("");

        // Log what we popped and pushed
        LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_SUBSTRING_RANGE)
            .arg(pkt.getLabel())
            .arg(len_str)
            .arg(start_str)
            .arg(toHex(string_str))
            .arg("0x");
        return (0);
    }

    // Adjust the values to be something for substr.  We first figure out
    // the starting position, then update it and the length to get the
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
        .arg(pkt.getLabel())
        .arg(len_str)
        .arg(start_str)
        .arg(toHex(string_str))
        .arg(toHex(values.top()));

    return (0);
}

unsigned
TokenSplit::evaluate(Pkt& pkt, ValueStack& values) {
    if (values.size() < 3) {
        isc_throw(EvalBadStack, "Incorrect stack order. Expected at least "
                  "3 values for split operator, got " << values.size());
    }

    // Pop the parameters.
    string field_str = values.top();
    values.pop();
    string delim_str = values.top();
    values.pop();
    string string_str = values.top();
    values.pop();

    // If we have no string to start with we push an empty string and leave
    if (string_str.empty()) {
        values.push("");

        // Log what we popped and pushed
        LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_SPLIT_EMPTY)
            .arg(pkt.getLabel())
            .arg(field_str)
            .arg(delim_str)
            .arg(string_str)
            .arg("0x");
        return (0);
    }

    // Convert the field position from string to number
    // If we have a problem push an empty string and leave
    int field;
    try {
        field = boost::lexical_cast<int>(field_str);
    } catch (const boost::bad_lexical_cast&) {
        isc_throw(EvalTypeError, "the parameter '" << field_str
                  << "' for the field field for split "
                  << "couldn't be converted to an integer.");
    }

    // If we have no delimiter to start with we push the input string and leave
    if (delim_str.empty()) {
        values.push(string_str);

        // Log what we popped and pushed
        LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_SPLIT_DELIM_EMPTY)
            .arg(pkt.getLabel())
            .arg(field_str)
            .arg(delim_str)
            .arg(string_str)
            .arg(toHex(values.top()));
        return (0);
    }

    // Split the string into fields.
    std::vector<std::string> fields;
    boost::split(fields, string_str, boost::is_any_of(delim_str),
                 boost::algorithm::token_compress_off);

    // Range check the field.
    if (field < 1 || static_cast<size_t>(field) > fields.size()) {
        // Push an empty string if field is out of range.
        values.push("");

        // Log what we popped and pushed
        LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_SPLIT_FIELD_OUT_OF_RANGE)
            .arg(pkt.getLabel())
            .arg(field_str)
            .arg(delim_str)
            .arg(string_str)
            .arg("0x");
        return (0);
    }

    // Push the desired field.
    values.push(fields[field - 1]);

    // Log what we popped and pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_SPLIT)
            .arg(pkt.getLabel())
            .arg(field_str)
            .arg(delim_str)
            .arg(string_str)
            .arg(toHex(values.top()));

    return (0);
}

unsigned
TokenConcat::evaluate(Pkt& pkt, ValueStack& values) {
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
        .arg(pkt.getLabel())
        .arg(toHex(op1))
        .arg(toHex(op2))
        .arg(toHex(values.top()));

    return (0);
}

unsigned
TokenIfElse::evaluate(Pkt& pkt, ValueStack& values) {
    if (values.size() < 3) {
        isc_throw(EvalBadStack, "Incorrect stack order. Expected at least "
                  "3 values for ifelse, got " << values.size());
    }

    string iffalse = values.top();
    values.pop();
    string iftrue = values.top();
    values.pop();
    string cond = values.top();
    values.pop();
    bool val = toBool(cond);

    if (val) {
        values.push(iftrue);
    } else {
        values.push(iffalse);
    }

    // Log what we popped and pushed
    if (val) {
        LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_IFELSE_TRUE)
            .arg(pkt.getLabel())
            .arg('\'' + cond + '\'')
            .arg(toHex(iffalse))
            .arg(toHex(iftrue));
    } else {
        LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_IFELSE_FALSE)
            .arg(pkt.getLabel())
            .arg('\'' +cond + '\'')
            .arg(toHex(iftrue))
            .arg(toHex(iffalse));
    }

    return (0);
}

unsigned
TokenToHexString::evaluate(Pkt& pkt, ValueStack& values) {
    if (values.size() < 2) {
        isc_throw(EvalBadStack, "Incorrect stack order. Expected at least "
                  "2 values for hexstring, got " << values.size());
    }

    string separator = values.top();
    values.pop();
    string binary = values.top();
    values.pop();

    bool first = true;
    stringstream tmp;
    tmp << hex;
    for (size_t i = 0; i < binary.size(); ++i) {
        if (!first) {
            tmp << separator;
        } else {
            first = false;
        }
        tmp << setw(2) << setfill('0')
            << (static_cast<unsigned>(binary[i]) & 0xff);
    }
    values.push(tmp.str());

    // Log what we popped and pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_TOHEXSTRING)
        .arg(pkt.getLabel())
        .arg(toHex(binary))
        .arg(separator)
        .arg(tmp.str());

    return (0);
}

unsigned
TokenNot::evaluate(Pkt& pkt, ValueStack& values) {
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
        .arg(pkt.getLabel())
        .arg('\'' + op + '\'')
        .arg('\'' + values.top() + '\'');

    return (0);
}

unsigned
TokenAnd::evaluate(Pkt& pkt, ValueStack& values) {
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
        .arg(pkt.getLabel())
        .arg('\'' + op1 + '\'')
        .arg('\'' + op2 + '\'')
        .arg('\'' + values.top() + '\'');

    return (0);
}

unsigned
TokenOr::evaluate(Pkt& pkt, ValueStack& values) {
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
        .arg(pkt.getLabel())
        .arg('\'' + op1 + '\'')
        .arg('\'' + op2 + '\'')
        .arg('\'' + values.top() + '\'');

    return (0);
}

unsigned
TokenMember::evaluate(Pkt& pkt, ValueStack& values) {
    if (pkt.inClass(client_class_)) {
        values.push("true");
    } else {
        values.push("false");
    }

    // Log what we pushed
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_MEMBER)
        .arg(pkt.getLabel())
        .arg(client_class_)
        .arg('\'' + values.top() + '\'');

    return (0);
}

TokenVendor::TokenVendor(Option::Universe u, uint32_t vendor_id, RepresentationType repr,
                         uint16_t option_code)
    : TokenOption(option_code, repr), universe_(u), vendor_id_(vendor_id),
      field_(option_code ? SUBOPTION : EXISTS) {
}

TokenVendor::TokenVendor(Option::Universe u, uint32_t vendor_id, FieldType field)
    : TokenOption(0, TokenOption::HEXADECIMAL), universe_(u), vendor_id_(vendor_id),
      field_(field) {
    if (field_ == EXISTS) {
        representation_type_ = TokenOption::EXISTS;
    }
}

uint32_t
TokenVendor::getVendorId() const {
    return (vendor_id_);
}

TokenVendor::FieldType
TokenVendor::getField() const {
    return (field_);
}

unsigned
TokenVendor::evaluate(Pkt& pkt, ValueStack& values) {
    // Get the option first.
    uint16_t code = 0;
    switch (universe_) {
    case Option::V4:
        code = DHO_VIVSO_SUBOPTIONS;
        break;
    case Option::V6:
        code = D6O_VENDOR_OPTS;
        break;
    }

    OptionPtr opt = pkt.getOption(code);
    OptionVendorPtr vendor = boost::dynamic_pointer_cast<OptionVendor>(opt);
    if (!vendor) {
        // There's no vendor option, give up.
        std::string txt = pushFailure(values);
        LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_VENDOR_NO_OPTION)
            .arg(pkt.getLabel())
            .arg(code)
            .arg(txt);
        return (0);
    }

    if (vendor_id_ && (vendor_id_ != vendor->getVendorId())) {
        // There is vendor option, but it has other vendor-id value
        // than we're looking for. (0 means accept any vendor-id)
        std::string txt = pushFailure(values);
        LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_VENDOR_ENTERPRISE_ID_MISMATCH)
            .arg(pkt.getLabel())
            .arg(vendor_id_)
            .arg(vendor->getVendorId())
            .arg(txt);
        return (0);
    }

    switch (field_) {
    case ENTERPRISE_ID:
    {
        // Extract enterprise-id
        string txt(sizeof(uint32_t), 0);
        uint32_t value = htonl(vendor->getVendorId());
        memcpy(&txt[0], &value, sizeof(uint32_t));
        values.push(txt);
        LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_VENDOR_ENTERPRISE_ID)
            .arg(pkt.getLabel())
            .arg(vendor->getVendorId())
            .arg(util::encode::encodeHex(std::vector<uint8_t>(txt.begin(),
                                                              txt.end())));
        break;
    }
    case SUBOPTION:
        /// This is vendor[X].option[Y].exists, let's try to
        /// extract the option
        return (TokenOption::evaluate(pkt, values));
    case EXISTS:
        // We already passed all the checks: the option is there and has specified
        // enterprise-id.
        LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_VENDOR_EXISTS)
            .arg(pkt.getLabel())
            .arg(vendor->getVendorId())
            .arg("true");
        values.push("true");
        break;
    case DATA:
        // This is for vendor-class option, we can skip it here.
        isc_throw(EvalTypeError, "Field None is not valid for vendor-class");
        break;
    }

    return (0);
}

OptionPtr
TokenVendor::getOption(Pkt& pkt) {
   uint16_t code = 0;
    switch (universe_) {
    case Option::V4:
        code = DHO_VIVSO_SUBOPTIONS;
        break;
    case Option::V6:
        code = D6O_VENDOR_OPTS;
        break;
    }

    OptionPtr opt = pkt.getOption(code);
    if (!opt) {
        // If vendor option is not found, return NULL
        return (opt);
    }

    // If vendor option is found, try to return its
    // encapsulated option.
    return (opt->getOption(option_code_));
}

TokenVendorClass::TokenVendorClass(Option::Universe u, uint32_t vendor_id,
                                   RepresentationType repr)
    : TokenVendor(u, vendor_id, repr, 0), index_(0) {
}

TokenVendorClass::TokenVendorClass(Option::Universe u, uint32_t vendor_id,
                                   FieldType field, uint16_t index)
    : TokenVendor(u, vendor_id, TokenOption::HEXADECIMAL, 0), index_(index) {
    field_ = field;
}

uint16_t
TokenVendorClass::getDataIndex() const {
    return (index_);
}

unsigned
TokenVendorClass::evaluate(Pkt& pkt, ValueStack& values) {
    // Get the option first.
    uint16_t code = 0;
    switch (universe_) {
    case Option::V4:
        code = DHO_VIVCO_SUBOPTIONS;
        break;
    case Option::V6:
        code = D6O_VENDOR_CLASS;
        break;
    }

    OptionPtr opt = pkt.getOption(code);
    OptionVendorClassPtr vendor = boost::dynamic_pointer_cast<OptionVendorClass>(opt);
    if (!vendor) {
        // There's no vendor class option, give up.
        std::string txt = pushFailure(values);
        LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_VENDOR_CLASS_NO_OPTION)
            .arg(pkt.getLabel())
            .arg(code)
            .arg(txt);
        return (0);
    }

    if (vendor_id_ && (vendor_id_ != vendor->getVendorId())) {
        // There is vendor option, but it has other vendor-id value
        // than we're looking for. (0 means accept any vendor-id)
        std::string txt = pushFailure(values);
        LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID_MISMATCH)
            .arg(pkt.getLabel())
            .arg(vendor_id_)
            .arg(vendor->getVendorId())
            .arg(txt);
        return (0);
    }

    switch (field_) {
    case ENTERPRISE_ID:
    {
        // Extract enterprise-id
        string txt(sizeof(uint32_t), 0);
        uint32_t value = htonl(vendor->getVendorId());
        memcpy(&txt[0], &value, sizeof(uint32_t));
        values.push(txt);
        LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID)
            .arg(pkt.getLabel())
            .arg(vendor->getVendorId())
            .arg(util::encode::encodeHex(std::vector<uint8_t>(txt.begin(),
                                                              txt.end())));
        break;
    }
    case SUBOPTION:
        // Extract sub-options
        isc_throw(EvalTypeError, "Field None is not valid for vendor-class");
        break;
    case EXISTS:
        // We already passed all the checks: the option is there and has specified
        // enterprise-id.
        LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_VENDOR_CLASS_EXISTS)
            .arg(pkt.getLabel())
            .arg(vendor->getVendorId())
            .arg("true");
        values.push("true");
        break;
    case DATA:
    {
        size_t max = vendor->getTuplesNum();
        if (static_cast<size_t>(index_ + 1) > max) {
            // The index specified is out of bounds, e.g. there are only
            // 2 tuples and index specified is 5.
            LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_VENDOR_CLASS_DATA_NOT_FOUND)
                .arg(pkt.getLabel())
                .arg(index_)
                .arg(vendor->getVendorId())
                .arg(max)
                .arg("");
            values.push("");
            break;
        }

        OpaqueDataTuple tuple = vendor->getTuple(index_);
        OpaqueDataTuple::Buffer buf = tuple.getData();
        string txt(buf.begin(), buf.end());

        LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_VENDOR_CLASS_DATA)
            .arg(pkt.getLabel())
            .arg(index_)
            .arg(max)
            .arg(txt);

        values.push(txt);
        break;
    }
    default:
        isc_throw(EvalTypeError, "Invalid field specified." << field_);
    }

    return (0);
}

TokenInteger::TokenInteger(const uint32_t value)
    : TokenString(EvalContext::fromUint32(value)), int_value_(value) {
}

OptionPtr
TokenSubOption::getSubOption(const OptionPtr& parent) {
    if (!parent) {
        return (OptionPtr());
    }
    return (parent->getOption(sub_option_code_));
}

unsigned
TokenSubOption::evaluate(Pkt& pkt, ValueStack& values) {
    OptionPtr parent = getOption(pkt);
    std::string txt;
    isc::log::MessageID msgid = EVAL_DEBUG_SUB_OPTION;
    if (!parent) {
        // There's no parent option, notify that.
        msgid = EVAL_DEBUG_SUB_OPTION_NO_OPTION;
        if (representation_type_ == EXISTS) {
            txt = "false";
        }
    } else {
        OptionPtr sub = getSubOption(parent);
        if (!sub) {
            // Failed to find the sub-option
            if (representation_type_ == EXISTS) {
                txt = "false";
            }
        } else {
            if (representation_type_ == TEXTUAL) {
                txt = sub->toString();
            } else if (representation_type_ == HEXADECIMAL) {
                std::vector<uint8_t> binary = sub->toBinary();
                txt.resize(binary.size());
                if (!binary.empty()) {
                    memmove(&txt[0], &binary[0], binary.size());
                }
            } else {
                txt = "true";
            }
        }
    }

    // Push value of the sub-option or empty string if there was no
    // such parent option in the packet or sub-option in the parent.
    values.push(txt);

    // Log what we pushed, both exists and textual are simple text
    // and can be output directly.  We also include the code numbers
    // of the requested parent option and sub-option.
    if (representation_type_ == HEXADECIMAL) {
        LOG_DEBUG(eval_logger, EVAL_DBG_STACK, msgid)
            .arg(pkt.getLabel())
            .arg(option_code_)
            .arg(sub_option_code_)
            .arg(toHex(txt));
    } else {
        LOG_DEBUG(eval_logger, EVAL_DBG_STACK, msgid)
            .arg(pkt.getLabel())
            .arg(option_code_)
            .arg(sub_option_code_)
            .arg('\'' + txt + '\'');
    }

    return (0);
}

TokenMatch::TokenMatch(const std::string& reg_exp) : reg_exp_str_(reg_exp) {
    try {
        reg_exp_ = regex(reg_exp);
    } catch (const exception& ex) {
        isc_throw(EvalParseError, "invalid regular expression '" << reg_exp
                  << "': " << ex.what());
    }
}

unsigned
TokenMatch::evaluate(Pkt&, ValueStack& values) {
    if (values.size() == 0) {
        isc_throw(EvalBadStack, "Incorrect empty stack.");
    }

    string val = values.top();
    values.pop();
    string txt = "false";
    try {
        if (regex_match(val, reg_exp_)) {
            txt = "true";
        }
        LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_MATCH)
            .arg(reg_exp_str_)
            .arg(val)
            .arg(txt);
    } catch (const exception& ex) {
        LOG_ERROR(eval_logger, EVAL_DEBUG_MATCH_ERROR)
            .arg(reg_exp_str_)
            .arg(val)
            .arg(ex.what());
    }
    values.push(txt);

    return (0);
}

TokenLabel::TokenLabel(const unsigned label) : label_(label) {
    if (label == 0) {
        isc_throw(EvalParseError, "label must be not zero");
    }
}

unsigned
TokenLabel::evaluate(Pkt&, ValueStack&) {
    return (0);
}

TokenBranch::TokenBranch(const unsigned target) : target_(target) {
    if (target == 0) {
        isc_throw(EvalParseError, "target must be not zero");
    }
}

unsigned
TokenBranch::evaluate(Pkt&, ValueStack&) {
    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_BRANCH)
        .arg(target_);
    return (target_);
}

TokenPopOrBranchTrue::TokenPopOrBranchTrue(const unsigned target)
    : TokenBranch(target) {
}

unsigned
TokenPopOrBranchTrue::evaluate(Pkt&, ValueStack& values) {
    if (values.size() == 0) {
        isc_throw(EvalBadStack, "Incorrect empty stack.");
    }

    string op = values.top();
    bool val = toBool(op);

    if (!val) {
        values.pop();
        return (0);
    }

    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_POP_OR_BRANCH_TRUE)
        .arg(target_);
    return (target_);
}

TokenPopOrBranchFalse::TokenPopOrBranchFalse(const unsigned target)
    : TokenBranch(target) {
}

unsigned
TokenPopOrBranchFalse::evaluate(Pkt&, ValueStack& values) {
    if (values.size() == 0) {
        isc_throw(EvalBadStack, "Incorrect empty stack.");
    }

    string op = values.top();
    bool val = toBool(op);

    if (val) {
        values.pop();
        return (0);
    }

    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_POP_OR_BRANCH_FALSE)
        .arg(target_);
    return (target_);
}

TokenPopAndBranchFalse::TokenPopAndBranchFalse(const unsigned target)
    : TokenBranch(target) {
}

unsigned
TokenPopAndBranchFalse::evaluate(Pkt&, ValueStack& values) {
    if (values.size() == 0) {
        isc_throw(EvalBadStack, "Incorrect empty stack.");
    }

    string op = values.top();
    values.pop();
    bool val = toBool(op);

    if (val) {
        return (0);
    }

    LOG_DEBUG(eval_logger, EVAL_DBG_STACK, EVAL_DEBUG_POP_AND_BRANCH_FALSE)
        .arg(target_);
    return (target_);
}
