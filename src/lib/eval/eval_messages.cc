// File created from ../../../src/lib/eval/eval_messages.mes

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
extern const isc::log::MessageID EVAL_DEBUG_INT16TOTEXT = "EVAL_DEBUG_INT16TOTEXT";
extern const isc::log::MessageID EVAL_DEBUG_INT32TOTEXT = "EVAL_DEBUG_INT32TOTEXT";
extern const isc::log::MessageID EVAL_DEBUG_INT8TOTEXT = "EVAL_DEBUG_INT8TOTEXT";
extern const isc::log::MessageID EVAL_DEBUG_IPADDRESS = "EVAL_DEBUG_IPADDRESS";
extern const isc::log::MessageID EVAL_DEBUG_IPADDRESSTOTEXT = "EVAL_DEBUG_IPADDRESSTOTEXT";
extern const isc::log::MessageID EVAL_DEBUG_LCASE = "EVAL_DEBUG_LCASE";
extern const isc::log::MessageID EVAL_DEBUG_MATCH = "EVAL_DEBUG_MATCH";
extern const isc::log::MessageID EVAL_DEBUG_MATCH_ERROR = "EVAL_DEBUG_MATCH_ERROR";
extern const isc::log::MessageID EVAL_DEBUG_MEMBER = "EVAL_DEBUG_MEMBER";
extern const isc::log::MessageID EVAL_DEBUG_NOT = "EVAL_DEBUG_NOT";
extern const isc::log::MessageID EVAL_DEBUG_OPTION = "EVAL_DEBUG_OPTION";
extern const isc::log::MessageID EVAL_DEBUG_OR = "EVAL_DEBUG_OR";
extern const isc::log::MessageID EVAL_DEBUG_PKT = "EVAL_DEBUG_PKT";
extern const isc::log::MessageID EVAL_DEBUG_PKT4 = "EVAL_DEBUG_PKT4";
extern const isc::log::MessageID EVAL_DEBUG_PKT6 = "EVAL_DEBUG_PKT6";
extern const isc::log::MessageID EVAL_DEBUG_RELAY6 = "EVAL_DEBUG_RELAY6";
extern const isc::log::MessageID EVAL_DEBUG_RELAY6_RANGE = "EVAL_DEBUG_RELAY6_RANGE";
extern const isc::log::MessageID EVAL_DEBUG_SPLIT = "EVAL_DEBUG_SPLIT";
extern const isc::log::MessageID EVAL_DEBUG_SPLIT_DELIM_EMPTY = "EVAL_DEBUG_SPLIT_DELIM_EMPTY";
extern const isc::log::MessageID EVAL_DEBUG_SPLIT_EMPTY = "EVAL_DEBUG_SPLIT_EMPTY";
extern const isc::log::MessageID EVAL_DEBUG_SPLIT_FIELD_OUT_OF_RANGE = "EVAL_DEBUG_SPLIT_FIELD_OUT_OF_RANGE";
extern const isc::log::MessageID EVAL_DEBUG_STRING = "EVAL_DEBUG_STRING";
extern const isc::log::MessageID EVAL_DEBUG_SUBSTRING = "EVAL_DEBUG_SUBSTRING";
extern const isc::log::MessageID EVAL_DEBUG_SUBSTRING_EMPTY = "EVAL_DEBUG_SUBSTRING_EMPTY";
extern const isc::log::MessageID EVAL_DEBUG_SUBSTRING_RANGE = "EVAL_DEBUG_SUBSTRING_RANGE";
extern const isc::log::MessageID EVAL_DEBUG_SUB_OPTION = "EVAL_DEBUG_SUB_OPTION";
extern const isc::log::MessageID EVAL_DEBUG_SUB_OPTION_NO_OPTION = "EVAL_DEBUG_SUB_OPTION_NO_OPTION";
extern const isc::log::MessageID EVAL_DEBUG_TOHEXSTRING = "EVAL_DEBUG_TOHEXSTRING";
extern const isc::log::MessageID EVAL_DEBUG_UCASE = "EVAL_DEBUG_UCASE";
extern const isc::log::MessageID EVAL_DEBUG_UINT16TOTEXT = "EVAL_DEBUG_UINT16TOTEXT";
extern const isc::log::MessageID EVAL_DEBUG_UINT32TOTEXT = "EVAL_DEBUG_UINT32TOTEXT";
extern const isc::log::MessageID EVAL_DEBUG_UINT8TOTEXT = "EVAL_DEBUG_UINT8TOTEXT";
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
    "EVAL_DEBUG_AND", "%1: Popping %2 and %3 pushing %4",
    "EVAL_DEBUG_CONCAT", "%1: Popping %2 and %3 pushing %4",
    "EVAL_DEBUG_EQUAL", "%1: Popping %2 and %3 pushing result %4",
    "EVAL_DEBUG_HEXSTRING", "%1: Pushing hex string %2",
    "EVAL_DEBUG_IFELSE_FALSE", "%1: Popping %2 (false) and %3, leaving %4",
    "EVAL_DEBUG_IFELSE_TRUE", "%1: Popping %2 (true) and %3, leaving %4",
    "EVAL_DEBUG_INT16TOTEXT", "%1: Pushing Int16 %2",
    "EVAL_DEBUG_INT32TOTEXT", "%1: Pushing Int32 %2",
    "EVAL_DEBUG_INT8TOTEXT", "%1: Pushing Int8 %2",
    "EVAL_DEBUG_IPADDRESS", "%1: Pushing IPAddress %2",
    "EVAL_DEBUG_IPADDRESSTOTEXT", "%1: Pushing IPAddress %2",
    "EVAL_DEBUG_LCASE", "%1: Popping string %2 and pushing converted value to lower case %3",
    "EVAL_DEBUG_MATCH", "Matching '%1' on %2, result %3",
    "EVAL_DEBUG_MATCH_ERROR", "Matching '%1' on %2 raised an error: %3",
    "EVAL_DEBUG_MEMBER", "%1: Checking membership of '%2', pushing result %3",
    "EVAL_DEBUG_NOT", "%1: Popping %2 pushing %3",
    "EVAL_DEBUG_OPTION", "%1: Pushing option %2 with value %3",
    "EVAL_DEBUG_OR", "%1: Popping %2 and %3 pushing %4",
    "EVAL_DEBUG_PKT", "%1: Pushing PKT meta data %2 with value %3",
    "EVAL_DEBUG_PKT4", "%1: Pushing PKT4 field %2 with value %3",
    "EVAL_DEBUG_PKT6", "%1: Pushing PKT6 field %2 with value %3",
    "EVAL_DEBUG_RELAY6", "%1: Pushing PKT6 relay field %2 nest %3 with value %4",
    "EVAL_DEBUG_RELAY6_RANGE", "%1: Pushing PKT6 relay field %2 nest %3 with value %4",
    "EVAL_DEBUG_SPLIT", "%1: Popping field %2, delimiters %3, string %4, pushing result %5",
    "EVAL_DEBUG_SPLIT_DELIM_EMPTY", "%1: Popping field %2, delimiters %3, string %4, pushing result %5",
    "EVAL_DEBUG_SPLIT_EMPTY", "%1: Popping field %2, delimiters %3, string %4, pushing result %5",
    "EVAL_DEBUG_SPLIT_FIELD_OUT_OF_RANGE", "%1: Popping field %2, delimiters %3, string %4, pushing result %5",
    "EVAL_DEBUG_STRING", "%1: Pushing text string %2",
    "EVAL_DEBUG_SUBSTRING", "%1: Popping length %2, start %3, string %4 pushing result %5",
    "EVAL_DEBUG_SUBSTRING_EMPTY", "%1: Popping length %2, start %3, string %4 pushing result %5",
    "EVAL_DEBUG_SUBSTRING_RANGE", "%1: Popping length %2, start %3, string %4 pushing result %5",
    "EVAL_DEBUG_SUB_OPTION", "%1: Pushing option %2 sub-option %3 with value %4",
    "EVAL_DEBUG_SUB_OPTION_NO_OPTION", "%1: Requested option %2 sub-option %3, but the parent option is not present, pushing result %4",
    "EVAL_DEBUG_TOHEXSTRING", "%1: Popping binary value %2 and separator %3, pushing result %4",
    "EVAL_DEBUG_UCASE", "%1: Popping string %2 and pushing converted value to upper case %3",
    "EVAL_DEBUG_UINT16TOTEXT", "%1: Pushing UInt16 %2",
    "EVAL_DEBUG_UINT32TOTEXT", "%1: Pushing UInt32 %2",
    "EVAL_DEBUG_UINT8TOTEXT", "%1: Pushing UInt8 %2",
    "EVAL_DEBUG_VENDOR_CLASS_DATA", "%1: Data %2 (out of %3 received) in vendor class found, pushing result '%4'",
    "EVAL_DEBUG_VENDOR_CLASS_DATA_NOT_FOUND", "%1: Requested data index %2, but option with enterprise-id %3 has only %4 data tuple(s), pushing result '%5'",
    "EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID", "%1: Pushing enterprise-id %2 as result 0x%3",
    "EVAL_DEBUG_VENDOR_CLASS_ENTERPRISE_ID_MISMATCH", "%1: Was looking for %2, option had %3, pushing result '%4'",
    "EVAL_DEBUG_VENDOR_CLASS_EXISTS", "%1: Option with enterprise-id %2 found, pushing result '%3'",
    "EVAL_DEBUG_VENDOR_CLASS_NO_OPTION", "%1: Option with code %2 missing, pushing result '%3'",
    "EVAL_DEBUG_VENDOR_ENTERPRISE_ID", "%1: Pushing enterprise-id %2 as result 0x%3",
    "EVAL_DEBUG_VENDOR_ENTERPRISE_ID_MISMATCH", "%1: Was looking for %2, option had %3, pushing result '%4'",
    "EVAL_DEBUG_VENDOR_EXISTS", "%1: Option with enterprise-id %2 found, pushing result '%3'",
    "EVAL_DEBUG_VENDOR_NO_OPTION", "%1: Option with code %2 missing, pushing result '%3'",
    "EVAL_RESULT", "%1: Expression %2 evaluated to %3",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

