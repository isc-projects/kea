// File created from ../../../src/lib/hooks/hooks_messages.mes

#ifndef HOOKS_MESSAGES_H
#define HOOKS_MESSAGES_H

#include <log/message_types.h>

namespace isc {
namespace hooks {

extern const isc::log::MessageID HOOKS_ALL_CALLOUTS_DEREGISTERED;
extern const isc::log::MessageID HOOKS_CALLOUTS_BEGIN;
extern const isc::log::MessageID HOOKS_CALLOUTS_COMPLETE;
extern const isc::log::MessageID HOOKS_CALLOUTS_REMOVED;
extern const isc::log::MessageID HOOKS_CALLOUT_CALLED;
extern const isc::log::MessageID HOOKS_CALLOUT_DEREGISTERED;
extern const isc::log::MessageID HOOKS_CALLOUT_ERROR;
extern const isc::log::MessageID HOOKS_CALLOUT_EXCEPTION;
extern const isc::log::MessageID HOOKS_CALLOUT_REGISTRATION;
extern const isc::log::MessageID HOOKS_CLOSE_ERROR;
extern const isc::log::MessageID HOOKS_HOOK_LIST_RESET;
extern const isc::log::MessageID HOOKS_INCORRECT_VERSION;
extern const isc::log::MessageID HOOKS_LIBRARY_CLOSED;
extern const isc::log::MessageID HOOKS_LIBRARY_LOADED;
extern const isc::log::MessageID HOOKS_LIBRARY_LOADING;
extern const isc::log::MessageID HOOKS_LIBRARY_MULTI_THREADING_COMPATIBLE;
extern const isc::log::MessageID HOOKS_LIBRARY_MULTI_THREADING_NOT_COMPATIBLE;
extern const isc::log::MessageID HOOKS_LIBRARY_UNLOADED;
extern const isc::log::MessageID HOOKS_LIBRARY_UNLOADING;
extern const isc::log::MessageID HOOKS_LIBRARY_VERSION;
extern const isc::log::MessageID HOOKS_LOAD_ERROR;
extern const isc::log::MessageID HOOKS_LOAD_EXCEPTION;
extern const isc::log::MessageID HOOKS_LOAD_FRAMEWORK_EXCEPTION;
extern const isc::log::MessageID HOOKS_LOAD_SUCCESS;
extern const isc::log::MessageID HOOKS_MULTI_THREADING_COMPATIBLE_EXCEPTION;
extern const isc::log::MessageID HOOKS_NO_LOAD;
extern const isc::log::MessageID HOOKS_NO_UNLOAD;
extern const isc::log::MessageID HOOKS_NO_VERSION;
extern const isc::log::MessageID HOOKS_OPEN_ERROR;
extern const isc::log::MessageID HOOKS_STD_CALLOUT_REGISTERED;
extern const isc::log::MessageID HOOKS_UNLOAD_ERROR;
extern const isc::log::MessageID HOOKS_UNLOAD_EXCEPTION;
extern const isc::log::MessageID HOOKS_UNLOAD_FRAMEWORK_EXCEPTION;
extern const isc::log::MessageID HOOKS_UNLOAD_SUCCESS;
extern const isc::log::MessageID HOOKS_VERSION_EXCEPTION;

} // namespace hooks
} // namespace isc

#endif // HOOKS_MESSAGES_H
