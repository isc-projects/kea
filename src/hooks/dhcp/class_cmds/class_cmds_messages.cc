// File created from ../../../../src/hooks/dhcp/class_cmds/class_cmds_messages.mes

#include <cstddef>
#include <log/message_types.h>
#include <log/message_initializer.h>

extern const isc::log::MessageID CLASS_CMDS_CLASS_ADD = "CLASS_CMDS_CLASS_ADD";
extern const isc::log::MessageID CLASS_CMDS_CLASS_ADD_FAILED = "CLASS_CMDS_CLASS_ADD_FAILED";
extern const isc::log::MessageID CLASS_CMDS_CLASS_ADD_HANDLER_FAILED = "CLASS_CMDS_CLASS_ADD_HANDLER_FAILED";
extern const isc::log::MessageID CLASS_CMDS_CLASS_DEL = "CLASS_CMDS_CLASS_DEL";
extern const isc::log::MessageID CLASS_CMDS_CLASS_DEL_EMPTY = "CLASS_CMDS_CLASS_DEL_EMPTY";
extern const isc::log::MessageID CLASS_CMDS_CLASS_DEL_FAILED = "CLASS_CMDS_CLASS_DEL_FAILED";
extern const isc::log::MessageID CLASS_CMDS_CLASS_DEL_HANDLER_FAILED = "CLASS_CMDS_CLASS_DEL_HANDLER_FAILED";
extern const isc::log::MessageID CLASS_CMDS_CLASS_GET = "CLASS_CMDS_CLASS_GET";
extern const isc::log::MessageID CLASS_CMDS_CLASS_GET_EMPTY = "CLASS_CMDS_CLASS_GET_EMPTY";
extern const isc::log::MessageID CLASS_CMDS_CLASS_GET_FAILED = "CLASS_CMDS_CLASS_GET_FAILED";
extern const isc::log::MessageID CLASS_CMDS_CLASS_GET_HANDLER_FAILED = "CLASS_CMDS_CLASS_GET_HANDLER_FAILED";
extern const isc::log::MessageID CLASS_CMDS_CLASS_LIST = "CLASS_CMDS_CLASS_LIST";
extern const isc::log::MessageID CLASS_CMDS_CLASS_LIST_EMPTY = "CLASS_CMDS_CLASS_LIST_EMPTY";
extern const isc::log::MessageID CLASS_CMDS_CLASS_LIST_FAILED = "CLASS_CMDS_CLASS_LIST_FAILED";
extern const isc::log::MessageID CLASS_CMDS_CLASS_LIST_HANDLER_FAILED = "CLASS_CMDS_CLASS_LIST_HANDLER_FAILED";
extern const isc::log::MessageID CLASS_CMDS_CLASS_UPDATE = "CLASS_CMDS_CLASS_UPDATE";
extern const isc::log::MessageID CLASS_CMDS_CLASS_UPDATE_EMPTY = "CLASS_CMDS_CLASS_UPDATE_EMPTY";
extern const isc::log::MessageID CLASS_CMDS_CLASS_UPDATE_FAILED = "CLASS_CMDS_CLASS_UPDATE_FAILED";
extern const isc::log::MessageID CLASS_CMDS_CLASS_UPDATE_HANDLER_FAILED = "CLASS_CMDS_CLASS_UPDATE_HANDLER_FAILED";
extern const isc::log::MessageID CLASS_CMDS_DEINIT_OK = "CLASS_CMDS_DEINIT_OK";
extern const isc::log::MessageID CLASS_CMDS_INIT_FAILED = "CLASS_CMDS_INIT_FAILED";
extern const isc::log::MessageID CLASS_CMDS_INIT_OK = "CLASS_CMDS_INIT_OK";

namespace {

const char* values[] = {
    "CLASS_CMDS_CLASS_ADD", "class added: %1",
    "CLASS_CMDS_CLASS_ADD_FAILED", "failed to add a new class: %1",
    "CLASS_CMDS_CLASS_ADD_HANDLER_FAILED", "failed to run handler for 'class-add' command",
    "CLASS_CMDS_CLASS_DEL", "class deleted: %1",
    "CLASS_CMDS_CLASS_DEL_EMPTY", "class not deleted (not found): %1",
    "CLASS_CMDS_CLASS_DEL_FAILED", "failed to delete a class: %1",
    "CLASS_CMDS_CLASS_DEL_HANDLER_FAILED", "failed to run handler for 'class-del' command",
    "CLASS_CMDS_CLASS_GET", "successfully retrieved a class: %1",
    "CLASS_CMDS_CLASS_GET_EMPTY", "specified class was not found: %1",
    "CLASS_CMDS_CLASS_GET_FAILED", "failed to retrieve a class: %1",
    "CLASS_CMDS_CLASS_GET_HANDLER_FAILED", "failed to run handler for 'class-get' command",
    "CLASS_CMDS_CLASS_LIST", "successfully retrieved classes names",
    "CLASS_CMDS_CLASS_LIST_EMPTY", "no class was found",
    "CLASS_CMDS_CLASS_LIST_FAILED", "failed to retrieve classes names: %1",
    "CLASS_CMDS_CLASS_LIST_HANDLER_FAILED", "failed to run handler for 'class-list' command",
    "CLASS_CMDS_CLASS_UPDATE", "class updated: %1",
    "CLASS_CMDS_CLASS_UPDATE_EMPTY", "class not updated (not found): %1",
    "CLASS_CMDS_CLASS_UPDATE_FAILED", "failed to update a class: %1",
    "CLASS_CMDS_CLASS_UPDATE_HANDLER_FAILED", "failed to run handler for 'class-update' command",
    "CLASS_CMDS_DEINIT_OK", "unloading Class Commands hooks library successful",
    "CLASS_CMDS_INIT_FAILED", "loading Class Commands hooks library failed: %1",
    "CLASS_CMDS_INIT_OK", "loading Class Commands hooks library successful",
    NULL
};

const isc::log::MessageInitializer initializer(values);

} // Anonymous namespace

