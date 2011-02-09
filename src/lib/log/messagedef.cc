// File created from messagedef.mes on Wed Feb  9 10:11:36 2011

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace log {

extern const isc::log::MessageID MSG_DUPLNS = "DUPLNS";
extern const isc::log::MessageID MSG_DUPLPRFX = "DUPLPRFX";
extern const isc::log::MessageID MSG_IDNOTFND = "IDNOTFND";
extern const isc::log::MessageID MSG_NSEXTRARG = "NSEXTRARG";
extern const isc::log::MessageID MSG_NSINVARG = "NSINVARG";
extern const isc::log::MessageID MSG_NSNOARG = "NSNOARG";
extern const isc::log::MessageID MSG_ONETOKEN = "ONETOKEN";
extern const isc::log::MessageID MSG_OPENIN = "OPENIN";
extern const isc::log::MessageID MSG_OPENOUT = "OPENOUT";
extern const isc::log::MessageID MSG_PRFEXTRARG = "PRFEXTRARG";
extern const isc::log::MessageID MSG_PRFINVARG = "PRFINVARG";
extern const isc::log::MessageID MSG_PRFNOARG = "PRFNOARG";
extern const isc::log::MessageID MSG_READERR = "READERR";
extern const isc::log::MessageID MSG_UNRECDIR = "UNRECDIR";
extern const isc::log::MessageID MSG_WRITERR = "WRITERR";

} // namespace log
} // namespace isc

namespace {

const char* values[] = {
    "DUPLNS", "duplicate $NAMESPACE directive found",
    "DUPLPRFX", "duplicate $PREFIX directive found",
    "IDNOTFND", "could not replace message for '%s': no such message identification",
    "NSEXTRARG", "$NAMESPACE directive has too many arguments",
    "NSINVARG", "$NAMESPACE directive has an invalid argument ('%s')",
    "NSNOARG", "no arguments were given to the $NAMESPACE directive",
    "ONETOKEN", "a line containing a message ID ('%s') and nothing else was found",
    "OPENIN", "unable to open message file %s for input: %s",
    "OPENOUT", "unable to open %s for output: %s",
    "PRFEXTRARG", "$PREFIX directive has too many arguments",
    "PRFINVARG", "$PREFIX directive has an invalid argument ('%s')",
    "PRFNOARG", "no arguments were given to the $PREFIX directive",
    "READERR", "error reading from %s: %s",
    "UNRECDIR", "unrecognised directive '%s'",
    "WRITERR", "error writing to %s: %s",
    NULL
};

isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

