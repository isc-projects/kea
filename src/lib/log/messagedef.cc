// File created from messagedef.mes on Thu May  5 16:57:11 2011

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace log {

extern const isc::log::MessageID MSG_DUPLNS = "DUPLNS";
extern const isc::log::MessageID MSG_DUPLPRFX = "DUPLPRFX";
extern const isc::log::MessageID MSG_DUPMSGID = "DUPMSGID";
extern const isc::log::MessageID MSG_IDNOTFND = "IDNOTFND";
extern const isc::log::MessageID MSG_MSGRDERR = "MSGRDERR";
extern const isc::log::MessageID MSG_MSGWRTERR = "MSGWRTERR";
extern const isc::log::MessageID MSG_NOMSGTXT = "NOMSGTXT";
extern const isc::log::MessageID MSG_NSEXTRARG = "NSEXTRARG";
extern const isc::log::MessageID MSG_NSINVARG = "NSINVARG";
extern const isc::log::MessageID MSG_NSNOARG = "NSNOARG";
extern const isc::log::MessageID MSG_OPNMSGIN = "OPNMSGIN";
extern const isc::log::MessageID MSG_OPNMSGOUT = "OPNMSGOUT";
extern const isc::log::MessageID MSG_PRFEXTRARG = "PRFEXTRARG";
extern const isc::log::MessageID MSG_PRFINVARG = "PRFINVARG";
extern const isc::log::MessageID MSG_PRFNOARG = "PRFNOARG";
extern const isc::log::MessageID MSG_RDLOCMES = "RDLOCMES";
extern const isc::log::MessageID MSG_UNRECDIR = "UNRECDIR";

} // namespace log
} // namespace isc

namespace {

const char* values[] = {
    "DUPLNS", "duplicate $NAMESPACE directive found",
    "DUPLPRFX", "duplicate $PREFIX directive found",
    "DUPMSGID", "duplicate message ID (%1) in compiled code",
    "IDNOTFND", "could not replace message for '%1': no such message identification",
    "MSGRDERR", "error reading from message file %1: %2",
    "MSGWRTERR", "error writing to %1: %2",
    "NOMSGTXT", "a line containing a message ID ('%1') and nothing else was found",
    "NSEXTRARG", "$NAMESPACE directive has too many arguments",
    "NSINVARG", "$NAMESPACE directive has an invalid argument ('%1')",
    "NSNOARG", "no arguments were given to the $NAMESPACE directive",
    "OPNMSGIN", "unable to open message file %1 for input: %2",
    "OPNMSGOUT", "unable to open %1 for output: %2",
    "PRFEXTRARG", "$PREFIX directive has too many arguments",
    "PRFINVARG", "$PREFIX directive has an invalid argument ('%1')",
    "PRFNOARG", "no arguments were given to the $PREFIX directive",
    "RDLOCMES", "reading local message file %1",
    "UNRECDIR", "unrecognised directive '%1'",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

