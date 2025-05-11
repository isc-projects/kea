// Copyright (C) 2020-2025 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <config.h>

#include <class_cmds.h>
#include <class_cmds_log.h>
#include <cc/command_interpreter.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/client_class_def.h>
#include <dhcpsrv/parsers/client_class_def_parser.h>
#include <util/multi_threading_mgr.h>
#include <string>
#include <sstream>

using namespace isc::config;
using namespace isc::dhcp;
using namespace isc::data;
using namespace isc::hooks;
using namespace isc::util;
using namespace std;

namespace isc {
namespace class_cmds {

/// @brief Implementation of the @c ClassCmds class.
///
/// It provides functions for class manipulations.
class ClassCmdsImpl {
public:
    /// @brief Constructor.
    ClassCmdsImpl() {
        family_ = CfgMgr::instance().getFamily();
    }

    /// @brief Destructor.
    ~ClassCmdsImpl() { }

private:

    /// @brief Retrieves mandatory arguments from the command encapsulated
    /// within the callout handle.
    ///
    /// @param callout_handle Callout handle encapsulating the command.
    ///
    /// @return Pointer to the data structure encapsulating arguments being
    /// a map.
    /// @throw CtrlChannelError if the arguments are not present or aren't
    /// a map.
    ConstElementPtr getMandatoryArguments(CalloutHandle& callout_handle) const {
        ConstElementPtr command;
        callout_handle.getArgument("command", command);
        ConstElementPtr arguments;
        static_cast<void>(parseCommandWithArgs(arguments, command));
        return (arguments);
    }

    /// @brief Parses and validates arguments of the class-add and class-update
    /// commands.
    ///
    /// @param command_name Command name, used for error reporting.
    /// @param arguments Command arguments to be parsed and validated.
    ///
    /// @return JSON list of classes. Currently only one class is allowed
    /// on the list.
    ConstElementPtr parseReceivedClass(const std::string& command_name,
                                       const ConstElementPtr& arguments) {
        // Arguments must have one entry.
        if (arguments->size() != 1) {
            isc_throw(BadValue,
                      "invalid number of arguments " << arguments->size()
                      << " for the '" << command_name << "' command. "
                      << "Expecting 'client-classes' list");
        }

        // The map must contain a 'client-classes' list.
        ConstElementPtr list = arguments->get("client-classes");
        if (!list) {
            isc_throw(BadValue,
                      "missing 'client-classes' argument for the '"
                       << command_name << "' command");
        }

        // Make sure it is a list.
        if (list->getType() != Element::list) {
            isc_throw(BadValue,
                      "'client-classes' argument specified for the '"
                      << command_name << "' command is not a list");
        }

        // Currently we allow only one class in the list.
        if (list->size() != 1) {
            isc_throw(BadValue,
                      "invalid number of classes specified for the '"
                       << command_name << "' command. Expected one class");
        }

        return (list);
    }

public:

    /// @brief Returns a response to a 'class-add' command.
    ///
    /// @param callout_handle Reference to the callout handle holding command
    /// to be processed and where result should be stored.
    void addClass(CalloutHandle& callout_handle) {
        ConstElementPtr response;

        try {
            // Fetch command arguments.
            ConstElementPtr arguments = getMandatoryArguments(callout_handle);

            // Parse arguments and extract the class list. This list
            // is expected to contain exactly one class.
            ConstElementPtr class_list = parseReceivedClass("class-add", arguments);

            // Make sure that the class definition is a map.
            ConstElementPtr class_def = class_list->get(0);
            if (class_def->getType() != Element::map) {
                isc_throw(BadValue,
                          "invalid class definition specified for the "
                          "'class-add' command. Expected a map");
            }

            // Make sure that there are no unsupported parameters in the client
            // class definition.
            ClientClassDefParser parser;
            parser.checkParametersSupported(class_def, family_);

            // Finally, let's parse the class definition extended with the
            // default values.
            ClientClassDictionaryPtr dictionary =
                CfgMgr::instance().getCurrentCfg()->getClientClassDictionary();
            parser.parse(dictionary, class_def, family_, false);

            // Add text stating that client class has been added.

            // This is an additional sanity check. This should be caught by
            // the ClientClassDefParser earlier (and throw if name is missing)
            if (!class_def->contains("name")) {
                isc_throw(BadValue, "missing 'name' argument for the 'class-get' command");
            }
            ostringstream text;
            string name = class_def->get("name")->stringValue();
            text << "Class '" << name << "' added";

            // Create the response.
            response = createAnswer(CONTROL_RESULT_SUCCESS, text.str());

            LOG_INFO(class_cmds_logger, CLASS_CMDS_CLASS_ADD).arg(class_def->str());

        } catch (const std::exception& ex) {
            LOG_INFO(class_cmds_logger, CLASS_CMDS_CLASS_ADD_FAILED)
                .arg(ex.what());

            response = createAnswer(CONTROL_RESULT_ERROR, ex.what());
        }

        callout_handle.setArgument("response", response);
    }

    /// @brief Returns a response to a 'class-get' command
    ///
    /// @param callout_handle Reference to the callout handle holding command
    /// to be processed and where result should be stored.
    void getClass(CalloutHandle& callout_handle) const {
        ConstElementPtr response;

        try {
            // Fetch command arguments.
            ConstElementPtr arguments = getMandatoryArguments(callout_handle);

            // Arguments must have one entry.
            if (arguments->size() != 1) {
                isc_throw(BadValue,
                          "invalid number of arguments " << arguments->size()
                          << " for the 'class-get' command. "
                          << "Expecting 'name' string");
            }

            // The map must contain a 'name' string.
            ConstElementPtr name = arguments->get("name");
            if (!name) {
                isc_throw(BadValue,
                          "missing 'name' argument for the 'class-get' command");
            }

            // Make sure it is a string.
            if (name->getType() != Element::string) {
                isc_throw(BadValue,
                          "'name' argument specified for the 'class-get' "
                          "command is not a string");
            }

            string name_str = name->stringValue();
            ClientClassDictionaryPtr dictionary =
                CfgMgr::instance().getCurrentCfg()->getClientClassDictionary();
            ClientClassDefPtr def = dictionary->findClass(name_str);

            // If class found, wrap its definition in the successful response.
            if (def) {
                ElementPtr list = Element::createList();
                list->add(def->toElement());
                ElementPtr map = Element::createMap();
                map->set("client-classes", list);

                ostringstream text;
                text << "Class '" << name_str << "' definition returned";
                response = createAnswer(CONTROL_RESULT_SUCCESS, text.str(), map);

                LOG_INFO(class_cmds_logger, CLASS_CMDS_CLASS_GET).arg(name_str);

            } else {
                ostringstream text;
                text << "Class '" << name_str << "' not found";

                response = createAnswer(CONTROL_RESULT_EMPTY, text.str());

                LOG_INFO(class_cmds_logger, CLASS_CMDS_CLASS_GET_EMPTY).arg(name_str);
            }

        } catch (const std::exception& ex) {
            LOG_INFO(class_cmds_logger, CLASS_CMDS_CLASS_GET_FAILED)
                .arg(ex.what());

            response = createAnswer(CONTROL_RESULT_ERROR, ex.what());
        }

        callout_handle.setArgument("response", response);
    }

    /// @brief Returns a response to a 'class-list' command.
    ///
    /// @param callout_handle Reference to the callout handle holding command
    /// to be processed and where result should be stored.
    void getClassList(CalloutHandle& callout_handle) const {

        ConstElementPtr response;

        try {
            // Create a list where we're going to store classes' names.
            ElementPtr list = Element::createList();
            // Create arguments map and add client classes map.
            ElementPtr args = Element::createMap();
            args->set("client-classes", list);

            // Retrieve all classes from the configuration structure.
            auto const& classes = CfgMgr::instance().getCurrentCfg()->
                getClientClassDictionary()->getClasses();

            // Iterate over all classes and retrieve names.
            for (auto const& c : *classes) {
                ElementPtr entry = Element::createMap();
                entry->set("name", Element::create(c->getName()));
                list->add(entry);
            }

            // Generate the status message including the number of classes found.
            ostringstream text;
            text << classes->size() << " class";
            // For 0 classes or more than 1 classes returned, we use plural form 'classes'.
            if (classes->size() != 1) {
                text << "es";
            }
            text << " found";

            if (classes->size() > 0) {
                response = createAnswer(CONTROL_RESULT_SUCCESS, text.str(), args);

                LOG_INFO(class_cmds_logger, CLASS_CMDS_CLASS_LIST);
            } else {
                response = createAnswer(CONTROL_RESULT_EMPTY, text.str(),args);

                LOG_INFO(class_cmds_logger, CLASS_CMDS_CLASS_LIST_EMPTY);
            }

        } catch (const std::exception& ex) {
            LOG_INFO(class_cmds_logger, CLASS_CMDS_CLASS_LIST_FAILED)
                .arg(ex.what());

            response = createAnswer(CONTROL_RESULT_ERROR, ex.what());
        }

        callout_handle.setArgument("response", response);
    }

    /// @brief Returns a response to a 'class-update' command
    ///
    /// @param callout_handle Reference to the callout handle holding command
    /// to be processed and where result should be stored.
    void updateClass(CalloutHandle& callout_handle) {
        ConstElementPtr response;

        try {
            // Fetch command arguments.
            ConstElementPtr arguments = getMandatoryArguments(callout_handle);

            // Parse arguments and extract the class list. This list
            // is expected to contain exactly one class.
            ConstElementPtr class_list = parseReceivedClass("class-update", arguments);

            // Make sure that the class definition is a map.
            ConstElementPtr class_def = class_list->get(0);
            if (class_def->getType() != Element::map) {
                isc_throw(BadValue,
                          "invalid class definition specified for the "
                          "'class-update' command. Expected a map");
            }

            // Check the class is configured. But before we get to that, need to
            // do some basic sanity check first.
            if (!class_def->contains("name")) {
                isc_throw(BadValue, "the first class definition is missing a "
                          "mandatory 'name' parameter");
            }

            // Make sure that there are no unsupported parameters in the client
            // class definition.
            ClientClassDefParser parser;
            parser.checkParametersSupported(class_def, family_);

            string name = class_def->get("name")->stringValue();
            ClientClassDictionaryPtr dictionary =
                CfgMgr::instance().getCurrentCfg()->getClientClassDictionary();
            ClientClassDefPtr previous = dictionary->findClass(name);
            if (previous) {
                auto const& template_cfg = class_def->get("template-test");
                if (!template_cfg && dynamic_cast<TemplateClientClassDef*>(previous.get())) {
                    ElementPtr mutable_class_def = boost::const_pointer_cast<Element>(class_def);
                    mutable_class_def->set("template-test", Element::create(previous->getTest()));
                }
            } else {
                ostringstream text;
                text << "Class '" << name << "' is not found";

                response = createAnswer(CONTROL_RESULT_EMPTY, text.str());
                callout_handle.setArgument("response", response);

                LOG_INFO(class_cmds_logger, CLASS_CMDS_CLASS_UPDATE_EMPTY).arg(name);
                return;
            }

            // Build the before and after part of the dictionary.
            ClientClassDictionaryPtr before(new ClientClassDictionary());
            ClientClassDictionaryPtr after(new ClientClassDictionary());
            ClientClassDefListPtr classes = dictionary->getClasses();
            bool found = false;
            for (auto const& it : *classes) {
                if (it->getName() == name) {
                    found = true;
                } else if (found) {
                    after->addClass(it);
                } else {
                    before->addClass(it);
                }
            }

            // Finally, let's parse the class definition extended with the
            // default values.
            parser.parse(before, class_def, family_, false);
            ClientClassDefPtr next = before->findClass(name);
            if (!next) {
                isc_throw(Unexpected,
                          "Class '" << name << "' updated but does not show");
            }

            // The dependency on the KNOWN or UNKNOWN built-in class must not
            // change during the class update. The reason is that such dependency
            // may be indirect, i.e. some other class may depend on those built-in
            // classes via this class.
            if (previous->getDependOnKnown() != next->getDependOnKnown()) {
                isc_throw(DependOnKnownError,
                          "modification of the class '" << name << "' would "
                          "affect its dependency on the KNOWN and/or UNKNOWN built-in "
                          "classes. Such modification is not allowed because "
                          "there may be other classes depending on those built-ins "
                          "via the updated class");
            }

            // Merge after part.
            classes = after->getClasses();
            for (auto const& it : *classes) {
                before->addClass(it);
            }

            // Set the dictionary.
            CfgMgr::instance().getCurrentCfg()->setClientClassDictionary(before);

            // Add text stating that client class has been updated.
            ostringstream text;
            text << "Class '" << name << "' updated";

            // Create the response.
            response = createAnswer(CONTROL_RESULT_SUCCESS, text.str());

            LOG_INFO(class_cmds_logger, CLASS_CMDS_CLASS_UPDATE).arg(class_def->str());

        } catch (const std::exception& ex) {
            LOG_INFO(class_cmds_logger, CLASS_CMDS_CLASS_UPDATE_FAILED)
                .arg(ex.what());

            response = createAnswer(CONTROL_RESULT_ERROR, ex.what());
        }

        callout_handle.setArgument("response", response);
    }

    /// @brief Processes and returns a response to 'class-del' command.
    ///
    /// @param callout_handle Reference to the callout handle holding command
    /// to be processed and where result should be stored.
    void delClass(CalloutHandle& callout_handle) {
        ConstElementPtr response;

        try {
            // Fetch command arguments.
            ConstElementPtr arguments = getMandatoryArguments(callout_handle);

            // Arguments must have one entry.
            if (arguments->size() != 1) {
                isc_throw(BadValue,
                          "invalid number of arguments " << arguments->size()
                          << " for the 'class-del' command. "
                          << "Expecting 'name' string");
            }

            // The map must contain a 'name' string.
            ConstElementPtr name = arguments->get("name");
            if (!name) {
                isc_throw(BadValue,
                          "missing 'name' argument for the 'class-del' command");
            }

            // Make sure it is a string.
            if (name->getType() != Element::string) {
                isc_throw(BadValue,
                          "'name' argument specified for the 'class-del' "
                          "command is not a string");
            }

            string name_str = name->stringValue();
            ClientClassDictionaryPtr dictionary =
                CfgMgr::instance().getCurrentCfg()->getClientClassDictionary();
            ClientClassDefPtr def = dictionary->findClass(name_str);

            ostringstream text;

            // Check if the class was found.
            if (!def) {
                text << "Class '" << name_str << "' not found";

                response = createAnswer(CONTROL_RESULT_EMPTY, text.str());
                callout_handle.setArgument("response", response);

                LOG_INFO(class_cmds_logger, CLASS_CMDS_CLASS_DEL_EMPTY).arg(name_str);
                return;
            }

            // Check against dangling dependencies.
            string depend;
            if (dictionary->dependOnClass(name_str, depend)) {
                isc_throw(InUseError,
                          "Class '" << name_str << "' is used by class '"
                          << depend << "'");
            }

            // Remove the class from the configuration.
            dictionary->removeClass(name_str);

            text << "Class '" << name_str << "' deleted";

            response = createAnswer(CONTROL_RESULT_SUCCESS, text.str());

            LOG_INFO(class_cmds_logger, CLASS_CMDS_CLASS_DEL).arg(name_str);

        } catch (const std::exception& ex) {
            LOG_INFO(class_cmds_logger, CLASS_CMDS_CLASS_DEL_FAILED)
                .arg(ex.what());

            response = createAnswer(CONTROL_RESULT_ERROR, ex.what());
        }

        callout_handle.setArgument("response", response);
    }

private:

    /// @brief Protocol family (IPv4 or IPv6)
    uint16_t family_;
};

ClassCmds::ClassCmds()
    :impl_(new ClassCmdsImpl()) {
}

void
ClassCmds::getClass(CalloutHandle& callout_handle) const {
    impl_->getClass(callout_handle);
}

void
ClassCmds::getClassList(CalloutHandle& callout_handle) const {
    impl_->getClassList(callout_handle);
}

// Modifying the class configuration requires a critical section.

void
ClassCmds::addClass(CalloutHandle& callout_handle) {
    MultiThreadingCriticalSection sc;
    impl_->addClass(callout_handle);
}

void
ClassCmds::updateClass(CalloutHandle& callout_handle) {
    MultiThreadingCriticalSection sc;
    impl_->updateClass(callout_handle);
}

void
ClassCmds::delClass(CalloutHandle& callout_handle) {
    MultiThreadingCriticalSection sc;
    impl_->delClass(callout_handle);
}

}
}
