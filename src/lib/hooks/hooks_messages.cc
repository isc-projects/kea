// File created from ../../../src/lib/hooks/hooks_messages.mes on Fri Feb 08 2019 20:16

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

namespace isc {
namespace hooks {

extern const isc::log::MessageID HOOKS_ALL_CALLOUTS_DEREGISTERED = "HOOKS_ALL_CALLOUTS_DEREGISTERED";
extern const isc::log::MessageID HOOKS_CALLOUTS_BEGIN = "HOOKS_CALLOUTS_BEGIN";
extern const isc::log::MessageID HOOKS_CALLOUTS_COMPLETE = "HOOKS_CALLOUTS_COMPLETE";
extern const isc::log::MessageID HOOKS_CALLOUTS_REMOVED = "HOOKS_CALLOUTS_REMOVED";
extern const isc::log::MessageID HOOKS_CALLOUT_CALLED = "HOOKS_CALLOUT_CALLED";
extern const isc::log::MessageID HOOKS_CALLOUT_DEREGISTERED = "HOOKS_CALLOUT_DEREGISTERED";
extern const isc::log::MessageID HOOKS_CALLOUT_ERROR = "HOOKS_CALLOUT_ERROR";
extern const isc::log::MessageID HOOKS_CALLOUT_EXCEPTION = "HOOKS_CALLOUT_EXCEPTION";
extern const isc::log::MessageID HOOKS_CALLOUT_REGISTRATION = "HOOKS_CALLOUT_REGISTRATION";
extern const isc::log::MessageID HOOKS_CLOSE_ERROR = "HOOKS_CLOSE_ERROR";
extern const isc::log::MessageID HOOKS_HOOK_LIST_RESET = "HOOKS_HOOK_LIST_RESET";
extern const isc::log::MessageID HOOKS_INCORRECT_VERSION = "HOOKS_INCORRECT_VERSION";
extern const isc::log::MessageID HOOKS_LIBRARY_LOADED = "HOOKS_LIBRARY_LOADED";
extern const isc::log::MessageID HOOKS_LIBRARY_LOADING = "HOOKS_LIBRARY_LOADING";
extern const isc::log::MessageID HOOKS_LIBRARY_UNLOADED = "HOOKS_LIBRARY_UNLOADED";
extern const isc::log::MessageID HOOKS_LIBRARY_UNLOADING = "HOOKS_LIBRARY_UNLOADING";
extern const isc::log::MessageID HOOKS_LIBRARY_VERSION = "HOOKS_LIBRARY_VERSION";
extern const isc::log::MessageID HOOKS_LOAD_ERROR = "HOOKS_LOAD_ERROR";
extern const isc::log::MessageID HOOKS_LOAD_EXCEPTION = "HOOKS_LOAD_EXCEPTION";
extern const isc::log::MessageID HOOKS_LOAD_FRAMEWORK_EXCEPTION = "HOOKS_LOAD_FRAMEWORK_EXCEPTION";
extern const isc::log::MessageID HOOKS_LOAD_SUCCESS = "HOOKS_LOAD_SUCCESS";
extern const isc::log::MessageID HOOKS_NO_LOAD = "HOOKS_NO_LOAD";
extern const isc::log::MessageID HOOKS_NO_UNLOAD = "HOOKS_NO_UNLOAD";
extern const isc::log::MessageID HOOKS_NO_VERSION = "HOOKS_NO_VERSION";
extern const isc::log::MessageID HOOKS_OPEN_ERROR = "HOOKS_OPEN_ERROR";
extern const isc::log::MessageID HOOKS_STD_CALLOUT_REGISTERED = "HOOKS_STD_CALLOUT_REGISTERED";
extern const isc::log::MessageID HOOKS_UNLOAD_ERROR = "HOOKS_UNLOAD_ERROR";
extern const isc::log::MessageID HOOKS_UNLOAD_EXCEPTION = "HOOKS_UNLOAD_EXCEPTION";
extern const isc::log::MessageID HOOKS_UNLOAD_FRAMEWORK_EXCEPTION = "HOOKS_UNLOAD_FRAMEWORK_EXCEPTION";
extern const isc::log::MessageID HOOKS_UNLOAD_SUCCESS = "HOOKS_UNLOAD_SUCCESS";
extern const isc::log::MessageID HOOKS_VERSION_EXCEPTION = "HOOKS_VERSION_EXCEPTION";

} // namespace hooks
} // namespace isc

namespace {

const char* values[] = {
    "HOOKS_ALL_CALLOUTS_DEREGISTERED", "hook library at index %1 removed all callouts on hook %2",
    "HOOKS_CALLOUTS_BEGIN", "begin all callouts for hook %1",
    "HOOKS_CALLOUTS_COMPLETE", "completed callouts for hook %1 (total callouts duration: %2)",
    "HOOKS_CALLOUTS_REMOVED", "callouts removed from hook %1 for library %2",
    "HOOKS_CALLOUT_CALLED", "hooks library with index %1 has called a callout on hook %2 that has address %3 (callout duration: %4)",
    "HOOKS_CALLOUT_DEREGISTERED", "hook library at index %1 deregistered a callout on hook %2",
    "HOOKS_CALLOUT_ERROR", "error returned by callout on hook %1 registered by library with index %2 (callout address %3) (callout duration %4)",
    "HOOKS_CALLOUT_EXCEPTION", "exception thrown by callout on hook %1 registered by library with index %2 (callout address %3): %4 (callout duration: %5)",
    "HOOKS_CALLOUT_REGISTRATION", "hooks library with index %1 registering callout for hook '%2'",
    "HOOKS_CLOSE_ERROR", "failed to close hook library %1: %2",
    "HOOKS_HOOK_LIST_RESET", "the list of hooks has been reset",
    "HOOKS_INCORRECT_VERSION", "hook library %1 is at version %2, require version %3",
    "HOOKS_LIBRARY_LOADED", "hooks library %1 successfully loaded",
    "HOOKS_LIBRARY_LOADING", "loading hooks library %1",
    "HOOKS_LIBRARY_UNLOADED", "hooks library %1 successfully unloaded",
    "HOOKS_LIBRARY_UNLOADING", "unloading library %1",
    "HOOKS_LIBRARY_VERSION", "hooks library %1 reports its version as %2",
    "HOOKS_LOAD_ERROR", "'load' function in hook library %1 returned error %2",
    "HOOKS_LOAD_EXCEPTION", "'load' function in hook library %1 threw an exception",
    "HOOKS_LOAD_FRAMEWORK_EXCEPTION", "'load' function in hook library %1 threw an exception: reason %2",
    "HOOKS_LOAD_SUCCESS", "'load' function in hook library %1 returned success",
    "HOOKS_NO_LOAD", "no 'load' function found in hook library %1",
    "HOOKS_NO_UNLOAD", "no 'unload' function found in hook library %1",
    "HOOKS_NO_VERSION", "no 'version' function found in hook library %1",
    "HOOKS_OPEN_ERROR", "failed to open hook library %1: %2",
    "HOOKS_STD_CALLOUT_REGISTERED", "hooks library %1 registered standard callout for hook %2 at address %3",
    "HOOKS_UNLOAD_ERROR", "'unload' function in hook library %1 returned error %2",
    "HOOKS_UNLOAD_EXCEPTION", "'unload' function in hook library %1 threw an exception",
    "HOOKS_UNLOAD_FRAMEWORK_EXCEPTION", "'unload' function in hook library %1 threw an exception, reason %2",
    "HOOKS_UNLOAD_SUCCESS", "'unload' function in hook library %1 returned success",
    "HOOKS_VERSION_EXCEPTION", "'version' function in hook library %1 threw an exception",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

