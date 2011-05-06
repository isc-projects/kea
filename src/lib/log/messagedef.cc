// File created from messagedef.mes on Fri May  6 19:06:38 2011

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace log {

extern const isc::log::MessageID MSG_DUPLNS = "MSG_DUPLNS";
extern const isc::log::MessageID MSG_DUPMSGID = "MSG_DUPMSGID";
extern const isc::log::MessageID MSG_IDNOTFND = "MSG_IDNOTFND";
extern const isc::log::MessageID MSG_INVMSGID = "MSG_INVMSGID";
extern const isc::log::MessageID MSG_MSGRDERR = "MSG_MSGRDERR";
extern const isc::log::MessageID MSG_MSGWRTERR = "MSG_MSGWRTERR";
extern const isc::log::MessageID MSG_NOMSGID = "MSG_NOMSGID";
extern const isc::log::MessageID MSG_NOMSGTXT = "MSG_NOMSGTXT";
extern const isc::log::MessageID MSG_NSEXTRARG = "MSG_NSEXTRARG";
extern const isc::log::MessageID MSG_NSINVARG = "MSG_NSINVARG";
extern const isc::log::MessageID MSG_NSNOARG = "MSG_NSNOARG";
extern const isc::log::MessageID MSG_OPNMSGIN = "MSG_OPNMSGIN";
extern const isc::log::MessageID MSG_OPNMSGOUT = "MSG_OPNMSGOUT";
extern const isc::log::MessageID MSG_PRFEXTRARG = "MSG_PRFEXTRARG";
extern const isc::log::MessageID MSG_PRFINVARG = "MSG_PRFINVARG";
extern const isc::log::MessageID MSG_RDLOCMES = "MSG_RDLOCMES";
extern const isc::log::MessageID MSG_UNRECDIR = "MSG_UNRECDIR";

} // namespace log
} // namespace isc

namespace {

const char* values[] = {
    "MSG_DUPLNS", "line %s: duplicate $NAMESPACE directive found",
    "MSG_DUPMSGID", "duplicate message ID (%s) in compiled code",
    "MSG_IDNOTFND", "could not replace message for '%s': no such message identification",
    "MSG_INVMSGID", "line %s: invalid message identification '%s'",
    "MSG_MSGRDERR", "error reading from message file %s: %s",
    "MSG_MSGWRTERR", "error writing to %s: %s",
    "MSG_NOMSGID", "line %s: message definition line found without a message ID",
    "MSG_NOMSGTXT", "line %s: line found containing a message ID ('%s') and nothing else",
    "MSG_NSEXTRARG", "line %s: $NAMESPACE directive has too many arguments",
    "MSG_NSINVARG", "line %s: $NAMESPACE directive has an invalid argument ('%s')",
    "MSG_NSNOARG", "line %s: no arguments were given to the $NAMESPACE directive",
    "MSG_OPNMSGIN", "unable to open message file %s for input: %s",
    "MSG_OPNMSGOUT", "unable to open %s for output: %s",
    "MSG_PRFEXTRARG", "line %s: $PREFIX directive has too many arguments",
    "MSG_PRFINVARG", "line %s: $PREFIX directive has an invalid argument ('%s')",
    "MSG_RDLOCMES", "reading local message file %s",
    "MSG_UNRECDIR", "line %s: unrecognised directive '%s'",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

