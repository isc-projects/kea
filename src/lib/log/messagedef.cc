// File created from messagedef.mes on Fri May 27 14:49:45 2011

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace log {

extern const isc::log::MessageID MSG_BADDESTINATION = "MSG_BADDESTINATION";
extern const isc::log::MessageID MSG_BADSEVERITY = "MSG_BADSEVERITY";
extern const isc::log::MessageID MSG_BADSTREAM = "MSG_BADSTREAM";
extern const isc::log::MessageID MSG_DUPLNS = "MSG_DUPLNS";
extern const isc::log::MessageID MSG_DUPMSGID = "MSG_DUPMSGID";
extern const isc::log::MessageID MSG_IDNOTFND = "MSG_IDNOTFND";
extern const isc::log::MessageID MSG_INVMSGID = "MSG_INVMSGID";
extern const isc::log::MessageID MSG_NOMSGID = "MSG_NOMSGID";
extern const isc::log::MessageID MSG_NOMSGTXT = "MSG_NOMSGTXT";
extern const isc::log::MessageID MSG_NSEXTRARG = "MSG_NSEXTRARG";
extern const isc::log::MessageID MSG_NSINVARG = "MSG_NSINVARG";
extern const isc::log::MessageID MSG_NSNOARG = "MSG_NSNOARG";
extern const isc::log::MessageID MSG_OPENIN = "MSG_OPENIN";
extern const isc::log::MessageID MSG_OPENOUT = "MSG_OPENOUT";
extern const isc::log::MessageID MSG_PRFEXTRARG = "MSG_PRFEXTRARG";
extern const isc::log::MessageID MSG_PRFINVARG = "MSG_PRFINVARG";
extern const isc::log::MessageID MSG_RDLOCMES = "MSG_RDLOCMES";
extern const isc::log::MessageID MSG_READERR = "MSG_READERR";
extern const isc::log::MessageID MSG_UNRECDIR = "MSG_UNRECDIR";
extern const isc::log::MessageID MSG_WRITERR = "MSG_WRITERR";

} // namespace log
} // namespace isc

namespace {

const char* values[] = {
    "MSG_BADDESTINATION", "unrecognized log destination: %1",
    "MSG_BADSEVERITY", "unrecognized log severity: %1",
    "MSG_BADSTREAM", "bad log console output stream: %1",
    "MSG_DUPLNS", "line %1: duplicate $NAMESPACE directive found",
    "MSG_DUPMSGID", "duplicate message ID (%1) in compiled code",
    "MSG_IDNOTFND", "could not replace message text for '%1': no such message",
    "MSG_INVMSGID", "line %1: invalid message identification '%2'",
    "MSG_NOMSGID", "line %1: message definition line found without a message ID",
    "MSG_NOMSGTXT", "line %1: line found containing a message ID ('%2') and no text",
    "MSG_NSEXTRARG", "line %1: $NAMESPACE directive has too many arguments",
    "MSG_NSINVARG", "line %1: $NAMESPACE directive has an invalid argument ('%2')",
    "MSG_NSNOARG", "line %1: no arguments were given to the $NAMESPACE directive",
    "MSG_OPENIN", "unable to open message file %1 for input: %2",
    "MSG_OPENOUT", "unable to open %1 for output: %2",
    "MSG_PRFEXTRARG", "line %1: $PREFIX directive has too many arguments",
    "MSG_PRFINVARG", "line %1: $PREFIX directive has an invalid argument ('%2')",
    "MSG_RDLOCMES", "reading local message file %1",
    "MSG_READERR", "error reading from message file %1: %2",
    "MSG_UNRECDIR", "line %1: unrecognised directive '%2'",
    "MSG_WRITERR", "error writing to %1: %2",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

