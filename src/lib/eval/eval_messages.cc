// File created from ../../../src/lib/eval/eval_messages.mes on Fri Feb 08 2019 20:17

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace dhcp {

extern const isc::log::MessageID EVAL_DEBUG_AND = "EVAL_DEBUG_AND";
extern const isc::log::MessageID EVAL_DEBUG_CONCAT = "EVAL_DEBUG_CONCAT";
extern const isc::log::MessageID EVAL_DEBUG_EQUAL = "EVAL_DEBUG_EQUAL";
extern const isc::log::MessageID EVAL_DEBUG_HEXSTRING = "EVAL_DEBUG_HEXSTRING";
extern const isc::log::MessageID EVAL_DEBUG_IFELSE_FALSE = "EVAL_DEBUG_IFELSE_FALSE";
extern const isc::log::MessageID EVAL_DEBUG_IFELSE_TRUE = "EVAL_DEBUG_IFELSE_TRUE";
extern const isc::log::MessageID EVAL_DEBUG_IPADDRESS = "EVAL_DEBUG_IPADDRESS";
extern const isc::log::MessageID EVAL_DEBUG_MEMBER = "EVAL_DEBUG_MEMBER";
extern const isc::log::MessageID EVAL_DEBUG_NOT = "EVAL_DEBUG_NOT";
extern const isc::log::MessageID EVAL_DEBUG_OPTION = "EVAL_DEBUG_OPTION";
extern const isc::log::MessageID EVAL_DEBUG_OR = "EVAL_DEBUG_OR";
extern const isc::log::MessageID EVAL_DEBUG_PKT = "EVAL_DEBUG_PKT";
extern const isc::log::MessageID EVAL_DEBUG_PKT4 = "EVAL_DEBUG_PKT4";
extern const isc::log::MessageID EVAL_DEBUG_PKT6 = "EVAL_DEBUG_PKT6";
extern const isc::log::MessageID EVAL_DEBUG_RELAY6 = "EVAL_DEBUG_RELAY6";
extern const isc::log::MessageID EVAL_DEBUG_RELAY6_RANGE = "EVAL_DEBUG_RELAY6_RANGE";
extern const isc::log::MessageID EVAL_DEBUG_STRING = "EVAL_DEBUG_STRING";
extern const isc::log::MessageID EVAL_DEBUG_SUBSTRING = "EVAL_DEBUG_SUBSTRING";
extern const isc::log::MessageID EVAL_DEBUG_SUBSTRING_EMPTY = "EVAL_DEBUG_SUBSTRING_EMPTY";
extern const isc::log::MessageID EVAL_DEBUG_SUBSTRING_RANGE = "EVAL_DEBUG_SUBSTRING_RANGE";
extern const isc::log::MessageID EVAL_DEBUG_TOHEXSTRING = "EVAL_DEBUG_TOHEXSTRING";
extern const isc::log::MessageID EVAL_DEBUG_VENDOR_CLASS_DATA = "EVAL_DEBUG_VENDOR_CLASS_DATA";
extern const isc::log::MessageID EVAL_DEBUG_VENDOR_CLASS_DATA_NOT_FOUND = "EVAL_DEBUG_VENDOR_CLASS_DATA_NOT_FOUND";
extern const isc::log::MessageID EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID = "EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID";
extern const isc::log::MessageID EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID_MISMATCH = "EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID_MISMATCH";
extern const isc::log::MessageID EVAL_DEBUG_VENDOR_CLASS_EXISTS = "EVAL_DEBUG_VENDOR_CLASS_EXISTS";
extern const isc::log::MessageID EVAL_DEBUG_VENDOR_CLASS_NO_OPTION = "EVAL_DEBUG_VENDOR_CLASS_NO_OPTION";
extern const isc::log::MessageID EVAL_DEBUG_VENDOR_ENTERPRISE_ID = "EVAL_DEBUG_VENDOR_ENTERPRISE_ID";
extern const isc::log::MessageID EVAL_DEBUG_VENDOR_ENTERPRISE_ID_MISMATCH = "EVAL_DEBUG_VENDOR_ENTERPRISE_ID_MISMATCH";
extern const isc::log::MessageID EVAL_DEBUG_VENDOR_EXISTS = "EVAL_DEBUG_VENDOR_EXISTS";
extern const isc::log::MessageID EVAL_DEBUG_VENDOR_NO_OPTION = "EVAL_DEBUG_VENDOR_NO_OPTION";
extern const isc::log::MessageID EVAL_RESULT = "EVAL_RESULT";

} // namespace dhcp
} // namespace isc

namespace {

const char* values[] = {
    "EVAL_DEBUG_AND", "Popping %1 and %2 pushing %3",
    "EVAL_DEBUG_CONCAT", "Popping %1 and %2 pushing %3",
    "EVAL_DEBUG_EQUAL", "Popping %1 and %2 pushing result %3",
    "EVAL_DEBUG_HEXSTRING", "Pushing hex string %1",
    "EVAL_DEBUG_IFELSE_FALSE", "Popping %1 (false) and %2, leaving %3",
    "EVAL_DEBUG_IFELSE_TRUE", "Popping %1 (true) and %2, leaving %3",
    "EVAL_DEBUG_IPADDRESS", "Pushing IPAddress %1",
    "EVAL_DEBUG_MEMBER", "Checking membership of '%1', pushing result %2",
    "EVAL_DEBUG_NOT", "Popping %1 pushing %2",
    "EVAL_DEBUG_OPTION", "Pushing option %1 with value %2",
    "EVAL_DEBUG_OR", "Popping %1 and %2 pushing %3",
    "EVAL_DEBUG_PKT", "Pushing PKT meta data %1 with value %2",
    "EVAL_DEBUG_PKT4", "Pushing PKT4 field %1 with value %2",
    "EVAL_DEBUG_PKT6", "Pushing PKT6 field %1 with value %2",
    "EVAL_DEBUG_RELAY6", "Pushing PKT6 relay field %1 nest %2 with value %3",
    "EVAL_DEBUG_RELAY6_RANGE", "Pushing PKT6 relay field %1 nest %2 with value %3",
    "EVAL_DEBUG_STRING", "Pushing text string %1",
    "EVAL_DEBUG_SUBSTRING", "Popping length %1, start %2, string %3 pushing result %4",
    "EVAL_DEBUG_SUBSTRING_EMPTY", "Popping length %1, start %2, string %3 pushing result %4",
    "EVAL_DEBUG_SUBSTRING_RANGE", "Popping length %1, start %2, string %3 pushing result %4",
    "EVAL_DEBUG_TOHEXSTRING", "Popping binary value %1 and separator %2, pushing result %3",
    "EVAL_DEBUG_VENDOR_CLASS_DATA", "Data %1 (out of %2 received) in vendor class found, pushing result '%3'",
    "EVAL_DEBUG_VENDOR_CLASS_DATA_NOT_FOUND", "Requested data index %1, but option with enterprise-id %2 has only %3 data tuple(s), pushing result '%4'",
    "EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID", "Pushing enterprise-id %1 as result 0x%2",
    "EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID_MISMATCH", "Was looking for %1, option had %2, pushing result '%3'",
    "EVAL_DEBUG_VENDOR_CLASS_EXISTS", "Option with enterprise-id %1 found, pushing result '%2'",
    "EVAL_DEBUG_VENDOR_CLASS_NO_OPTION", "Option with code %1 missing, pushing result '%2'",
    "EVAL_DEBUG_VENDOR_ENTERPRISE_ID", "Pushing enterprise-id %1 as result 0x%2",
    "EVAL_DEBUG_VENDOR_ENTERPRISE_ID_MISMATCH", "Was looking for %1, option had %2, pushing result '%3'",
    "EVAL_DEBUG_VENDOR_EXISTS", "Option with enterprise-id %1 found, pushing result '%2'",
    "EVAL_DEBUG_VENDOR_NO_OPTION", "Option with code %1 missing, pushing result '%2'",
    "EVAL_RESULT", "Expression %1 evaluated to %2",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

