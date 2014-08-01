// Copyright (C) 2013-2014 Internet Systems Consortium, Inc. ("ISC")
//
// Permission to use, copy, modify, and/or distribute this software for any
// purpose with or without fee is hereby granted, provided that the above
// copyright notice and this permission notice appear in all copies.
//
// THE SOFTWARE IS PROVIDED "AS IS" AND ISC DISCLAIMS ALL WARRANTIES WITH
// REGARD TO THIS SOFTWARE INCLUDING ALL IMPLIED WARRANTIES OF MERCHANTABILITY
// AND FITNESS.  IN NO EVENT SHALL ISC BE LIABLE FOR ANY SPECIAL, DIRECT,
// INDIRECT, OR CONSEQUENTIAL DAMAGES OR ANY DAMAGES WHATSOEVER RESULTING FROM
// LOSS OF USE, DATA OR PROFITS, WHETHER IN AN ACTION OF CONTRACT, NEGLIGENCE
// OR OTHER TORTIOUS ACTION, ARISING OUT OF OR IN CONNECTION WITH THE USE OR
// PERFORMANCE OF THIS SOFTWARE.

#include <dhcp/iface_mgr.h>
#include <dhcp/libdhcp++.h>
#include <dhcpsrv/cfgmgr.h>
#include <dhcpsrv/dhcp_parsers.h>
#include <hooks/hooks_manager.h>
#include <util/encode/hex.h>
#include <util/strutil.h>

#include <boost/algorithm/string.hpp>
#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>

#include <map>
#include <string>
#include <vector>

using namespace std;
using namespace isc::asiolink;
using namespace isc::data;
using namespace isc::hooks;

namespace isc {
namespace dhcp {

namespace {
const char* ALL_IFACES_KEYWORD = "*";
}

// *********************** ParserContext  *************************

ParserContext::ParserContext(Option::Universe universe):
    boolean_values_(new BooleanStorage()),
    uint32_values_(new Uint32Storage()),
    string_values_(new StringStorage()),
    options_(new OptionStorage()),
    option_defs_(new OptionDefStorage()),
    hooks_libraries_(),
    universe_(universe)
{
}

ParserContext::ParserContext(const ParserContext& rhs):
    boolean_values_(),
    uint32_values_(),
    string_values_(),
    options_(),
    option_defs_(),
    hooks_libraries_(),
    universe_(rhs.universe_)
{
    copyContext(rhs);
}

ParserContext&
// The cppcheck version 1.56 doesn't recognize that copyContext
// copies all context fields.
// cppcheck-suppress operatorEqVarError
ParserContext::operator=(const ParserContext& rhs) {
    if (this != &rhs) {
        copyContext(rhs);
    }

    return (*this);
}

void
ParserContext::copyContext(const ParserContext& ctx) {
    copyContextPointer(ctx.boolean_values_, boolean_values_);
    copyContextPointer(ctx.uint32_values_, uint32_values_);
    copyContextPointer(ctx.string_values_, string_values_);
    copyContextPointer(ctx.options_, options_);
    copyContextPointer(ctx.option_defs_, option_defs_);
    copyContextPointer(ctx.hooks_libraries_, hooks_libraries_);
    // Copy universe.
    universe_ = ctx.universe_;
}

template<typename T>
void
ParserContext::copyContextPointer(const boost::shared_ptr<T>& source_ptr,
                                  boost::shared_ptr<T>& dest_ptr) {
    if (source_ptr) {
        dest_ptr.reset(new T(*source_ptr));
    } else {
        dest_ptr.reset();
    }
}


// **************************** DebugParser *************************

DebugParser::DebugParser(const std::string& param_name)
    :param_name_(param_name) {
}

void
DebugParser::build(ConstElementPtr new_config) {
    value_ = new_config;
    std::cout << "Build for token: [" << param_name_ << "] = ["
        << value_->str() << "]" << std::endl;
}

void
DebugParser::commit() {
    // Debug message. The whole DebugParser class is used only for parser
    // debugging, and is not used in production code. It is very convenient
    // to keep it around. Please do not turn this cout into logger calls.
    std::cout << "Commit for token: [" << param_name_ << "] = ["
                  << value_->str() << "]" << std::endl;
}

// **************************** BooleanParser  *************************

template<> void ValueParser<bool>::build(isc::data::ConstElementPtr value) {
    // Invoke common code for all specializations of build().
    buildCommon(value);
    // The Config Manager checks if user specified a
    // valid value for a boolean parameter: True or False.
    // We should have a boolean Element, use value directly
    try {
        value_ = value->boolValue();
    } catch (const isc::data::TypeError &) {
        isc_throw(BadValue, " Wrong value type for " << param_name_
                  << " : build called with a non-boolean element "
                  << "(" << value->getPosition() << ").");
    }
}

// **************************** Uin32Parser  *************************

template<> void ValueParser<uint32_t>::build(ConstElementPtr value) {
    // Invoke common code for all specializations of build().
    buildCommon(value);

    int64_t check;
    string x = value->str();
    try {
        check = boost::lexical_cast<int64_t>(x);
    } catch (const boost::bad_lexical_cast &) {
        isc_throw(BadValue, "Failed to parse value " << value->str()
                  << " as unsigned 32-bit integer "
                  "(" << value->getPosition() << ").");
    }
    if (check > std::numeric_limits<uint32_t>::max()) {
        isc_throw(BadValue, "Value " << value->str() << " is too large"
                  " for unsigned 32-bit integer "
                  "(" << value->getPosition() << ").");
    }
    if (check < 0) {
        isc_throw(BadValue, "Value " << value->str() << " is negative."
               << " Only 0 or larger are allowed for unsigned 32-bit integer "
                  "(" << value->getPosition() << ").");
    }

    // value is small enough to fit
    value_ = static_cast<uint32_t>(check);
}

// **************************** StringParser  *************************

template <> void ValueParser<std::string>::build(ConstElementPtr value) {
    // Invoke common code for all specializations of build().
    buildCommon(value);

    value_ = value->str();
    boost::erase_all(value_, "\"");
}

// ******************** InterfaceListConfigParser *************************

InterfaceListConfigParser::
InterfaceListConfigParser(const std::string& param_name)
    : activate_all_(false),
      param_name_(param_name) {
    if (param_name_ != "interfaces") {
        isc_throw(BadValue, "Internal error. Interface configuration "
            "parser called for the wrong parameter: " << param_name);
    }
}

void
InterfaceListConfigParser::build(ConstElementPtr value) {
    // First, we iterate over all specified entries and add it to the
    // local container so as we can do some basic validation, e.g. eliminate
    // duplicates.
    BOOST_FOREACH(ConstElementPtr iface, value->listValue()) {
        std::string iface_name = iface->stringValue();
        if (iface_name != ALL_IFACES_KEYWORD) {
            // Let's eliminate duplicates. We could possibly allow duplicates,
            // but if someone specified duplicated interface name it is likely
            // that he mistyped the configuration. Failing here should draw his
            // attention.
            if (isIfaceAdded(iface_name)) {
                isc_throw(isc::dhcp::DhcpConfigError, "duplicate interface"
                          << " name '" << iface_name << "' specified in '"
                          << param_name_ << "' configuration parameter "
                          "(" << value->getPosition() << ")");
            }
            // @todo check that this interface exists in the system!
            // The IfaceMgr exposes mechanisms to check this.

            // Add the interface name if ok.
            interfaces_.push_back(iface_name);

        } else {
            activate_all_ = true;

        }
    }
}

void
InterfaceListConfigParser::commit() {
    CfgMgr& cfg_mgr = CfgMgr::instance();
    // Remove active interfaces and clear a flag which marks all interfaces
    // active
    cfg_mgr.deleteActiveIfaces();

    if (activate_all_) {
        // Activate all interfaces. There is not need to add their names
        // explicitly.
        cfg_mgr.activateAllIfaces();

    } else {
        // Explicitly add names of the interfaces which server should listen on.
        BOOST_FOREACH(std::string iface, interfaces_) {
            cfg_mgr.addActiveIface(iface);
        }
    }
}

bool
InterfaceListConfigParser::isIfaceAdded(const std::string& iface) const {

    for (IfaceListStorage::const_iterator it = interfaces_.begin();
         it != interfaces_.end(); ++it) {
        if (iface == *it) {
            return (true);
        }
    }
    return (false);
}

// ******************** HooksLibrariesParser *************************

HooksLibrariesParser::HooksLibrariesParser(const std::string& param_name)
    : libraries_(), changed_(false)
{
    // Sanity check on the name.
    if (param_name != "hooks-libraries") {
        isc_throw(BadValue, "Internal error. Hooks libraries "
            "parser called for the wrong parameter: " << param_name);
    }
}

void
HooksLibrariesParser::build(ConstElementPtr value) {
    // Initialize.
    libraries_.clear();
    changed_ = false;

    // Extract the list of libraries.
    BOOST_FOREACH(ConstElementPtr iface, value->listValue()) {
        string libname = iface->str();
        boost::erase_all(libname, "\"");
        libraries_.push_back(libname);
    }

    // Check if the list of libraries has changed.  If not, nothing is done
    // - the command "DhcpN libreload" is required to reload the same
    // libraries (this prevents needless reloads when anything else in the
    // configuration is changed).
    vector<string> current_libraries = HooksManager::getLibraryNames();
    if (current_libraries == libraries_) {
        return;
    }

    // Library list has changed, validate each of the libraries specified.
    vector<string> error_libs = HooksManager::validateLibraries(libraries_);
    if (!error_libs.empty()) {

        // Construct the list of libraries in error for the message.
        string error_list = error_libs[0];
        for (int i = 1; i < error_libs.size(); ++i) {
            error_list += (string(", ") + error_libs[i]);
        }
        isc_throw(DhcpConfigError, "hooks libraries failed to validate - "
                  "library or libraries in error are: " << error_list
                  << " (" << value->getPosition() << ")");
    }

    // The library list has changed and the libraries are valid, so flag for
    // update when commit() is called.
    changed_ = true;
}

void
HooksLibrariesParser::commit() {
    /// Commits the list of libraries to the configuration manager storage if
    /// the list of libraries has changed.
    if (changed_) {
        // TODO Delete any stored CalloutHandles before reloading the
        // libraries
        HooksManager::loadLibraries(libraries_);
    }
}

// Method for testing
void
HooksLibrariesParser::getLibraries(std::vector<std::string>& libraries,
                                   bool& changed) {
    libraries = libraries_;
    changed = changed_;
}

// **************************** OptionDataParser *************************
OptionDataParser::OptionDataParser(const std::string&, OptionStoragePtr options,
                                  ParserContextPtr global_context)
    : boolean_values_(new BooleanStorage()),
    string_values_(new StringStorage()), uint32_values_(new Uint32Storage()),
    options_(options), option_descriptor_(false),
    global_context_(global_context) {
    if (!options_) {
        isc_throw(isc::dhcp::DhcpConfigError, "parser logic error: "
             << "options storage may not be NULL");
    }

    if (!global_context_) {
        isc_throw(isc::dhcp::DhcpConfigError, "parser logic error: "
             << "context may may not be NULL");
    }
}

void
OptionDataParser::build(ConstElementPtr option_data_entries) {
    BOOST_FOREACH(ConfigPair param, option_data_entries->mapValue()) {
        ParserPtr parser;
        if (param.first == "name" || param.first == "data" ||
            param.first == "space") {
            StringParserPtr name_parser(new StringParser(param.first,
                                        string_values_));
            parser = name_parser;
        } else if (param.first == "code") {
            Uint32ParserPtr code_parser(new Uint32Parser(param.first,
                                       uint32_values_));
            parser = code_parser;
        } else if (param.first == "csv-format") {
            BooleanParserPtr value_parser(new BooleanParser(param.first,
                                         boolean_values_));
            parser = value_parser;
        } else {
            isc_throw(DhcpConfigError,
                      "option-data parameter not supported: " << param.first
                      << " (" << param.second->getPosition() << ")");
        }

        parser->build(param.second);
        // Before we can create an option we need to get the data from
        // the child parsers. The only way to do it is to invoke commit
        // on them so as they store the values in appropriate storages
        // that this class provided to them. Note that this will not
        // modify values stored in the global storages so the configuration
        // will remain consistent even parsing fails somewhere further on.
        parser->commit();
    }

    // Try to create the option instance.
    createOption(option_data_entries);
}

void
OptionDataParser::commit() {
    if (!option_descriptor_.option) {
        // Before we can commit the new option should be configured. If it is
        // not than somebody must have called commit() before build().
        isc_throw(isc::InvalidOperation,
            "parser logic error: no option has been configured and"
            " thus there is nothing to commit. Has build() been called?");
    }

    uint16_t opt_type = option_descriptor_.option->getType();
    Subnet::OptionContainerPtr options = options_->getItems(option_space_);
    // The getItems() should never return NULL pointer. If there are no
    // options configured for the particular option space a pointer
    // to an empty container should be returned.
    assert(options);
    Subnet::OptionContainerTypeIndex& idx = options->get<1>();
    // Try to find options with the particular option code in the main
    // storage. If found, remove these options because they will be
    // replaced with new one.
    Subnet::OptionContainerTypeRange range = idx.equal_range(opt_type);
    if (std::distance(range.first, range.second) > 0) {
        idx.erase(range.first, range.second);
    }

    // Append new option to the main storage.
    options_->addItem(option_descriptor_, option_space_);
}

void
OptionDataParser::createOption(ConstElementPtr option_data) {
    // Check if mandatory parameters are specified.
    uint32_t code;
    std::string name;
    std::string data;
    try {
        code = uint32_values_->getParam("code");
        name = string_values_->getParam("name");
        data = string_values_->getParam("data");
    } catch (const std::exception& ex) {
        isc_throw(DhcpConfigError,
                  ex.what() << "(" << option_data->getPosition() << ")");
    }
    // Check parameters having default values.
    std::string space = string_values_->getOptionalParam("space",
              global_context_->universe_ == Option::V4 ? "dhcp4" : "dhcp6");
    bool csv_format = boolean_values_->getOptionalParam("csv-format", false);

    // Option code is held in the uint32_t storage but is supposed to
    // be uint16_t value. We need to check that value in the configuration
    // does not exceed range of uint8_t for DHCPv4, uint16_t for DHCPv6 and
    // is not zero.
    if (code == 0) {
        isc_throw(DhcpConfigError, "option code must not be zero "
                  "(" << uint32_values_->getPosition("code") << ")");

    } else if (global_context_->universe_ == Option::V4 &&
               code > std::numeric_limits<uint8_t>::max()) {
        isc_throw(DhcpConfigError, "invalid option code '" << code
                << "', it must not exceed '"
                  << static_cast<int>(std::numeric_limits<uint8_t>::max())
                  << "' (" << uint32_values_->getPosition("code") << ")");

    } else if (global_context_->universe_ == Option::V6 &&
               code > std::numeric_limits<uint16_t>::max()) {
        isc_throw(DhcpConfigError, "invalid option code '" << code
                << "', it must not exceed '"
                  << std::numeric_limits<uint16_t>::max()
                  << "' (" << uint32_values_->getPosition("code") << ")");

    }

    // Check that the option name is non-empty and does not contain spaces
    if (name.empty()) {
        isc_throw(DhcpConfigError, "name of the option with code '"
                  << code << "' is empty ("
                  << string_values_->getPosition("name") << ")");
    } else if (name.find(" ") != std::string::npos) {
        isc_throw(DhcpConfigError, "invalid option name '" << name
                  << "', space character is not allowed ("
                  << string_values_->getPosition("name") << ")");
    }

    if (!OptionSpace::validateName(space)) {
        isc_throw(DhcpConfigError, "invalid option space name '"
                << space << "' specified for option '"
                << name << "', code '" << code
                  << "' (" << string_values_->getPosition("space") << ")");
    }

    // Find the Option Definition for the option by its option code.
    // findOptionDefinition will throw if not found, no need to test.
    // Find the definition for the option by its code. This function
    // may throw so we catch exceptions to log the culprit line of the
    // configuration.
    OptionDefinitionPtr def;
    try {
        def = findServerSpaceOptionDefinition(space, code);

    } catch (const std::exception& ex) {
        isc_throw(DhcpConfigError, ex.what()
                  << " (" << string_values_->getPosition("space") << ")");
    }
    if (!def) {
        // If we are not dealing with a standard option then we
        // need to search for its definition among user-configured
        // options. They are expected to be in the global storage
        // already.
        OptionDefContainerPtr defs =
            global_context_->option_defs_->getItems(space);

        // The getItems() should never return the NULL pointer. If there are
        // no option definitions for the particular option space a pointer
        // to an empty container should be returned.
        assert(defs);
        const OptionDefContainerTypeIndex& idx = defs->get<1>();
        OptionDefContainerTypeRange range = idx.equal_range(code);
        if (std::distance(range.first, range.second) > 0) {
            def = *range.first;
        }

        // It's ok if we don't have option format if the option is
        // specified as hex
        if (!def && csv_format) {
            isc_throw(DhcpConfigError, "definition for the option '"
                      << space << "." << name
                      << "' having code '" << code
                      << "' does not exist ("
                      << string_values_->getPosition("name") << ")");
        }
    }

    // Transform string of hexadecimal digits into binary format.
    std::vector<uint8_t> binary;
    std::vector<std::string> data_tokens;

    if (csv_format) {
        // If the option data is specified as a string of comma
        // separated values then we need to split this string into
        // individual values - each value will be used to initialize
        // one data field of an option.
        data_tokens = isc::util::str::tokens(data, ",");
    } else {
        // Otherwise, the option data is specified as a string of
        // hexadecimal digits that we have to turn into binary format.
        try {
            // The decodeHex function expects that the string contains an
            // even number of digits. If we don't meet this requirement,
            // we have to insert a leading 0.
            if (!data.empty() && data.length() % 2) {
                data = data.insert(0, "0");
            }
            util::encode::decodeHex(data, binary);
        } catch (...) {
            isc_throw(DhcpConfigError, "option data is not a valid"
                      << " string of hexadecimal digits: " << data
                      << " (" << string_values_->getPosition("data") << ")");
        }
    }

    OptionPtr option;
    if (!def) {
        if (csv_format) {
            isc_throw(DhcpConfigError, "the CSV option data format can be"
                      " used to specify values for an option that has a"
                      " definition. The option with code " << code
                      << " does not have a definition ("
                      << boolean_values_->getPosition("csv-format") << ")");
        }

        // @todo We have a limited set of option definitions initalized at
        // the moment.  In the future we want to initialize option definitions
        // for all options.  Consequently an error will be issued if an option
        // definition does not exist for a particular option code. For now it is
        // ok to create generic option if definition does not exist.
        OptionPtr option(new Option(global_context_->universe_,
                        static_cast<uint16_t>(code), binary));
        // The created option is stored in option_descriptor_ class member
        // until the commit stage when it is inserted into the main storage.
        // If an option with the same code exists in main storage already the
        // old option is replaced.
        option_descriptor_.option = option;
        option_descriptor_.persistent = false;
    } else {

        // Option name should match the definition. The option name
        // may seem to be redundant but in the future we may want
        // to reference options and definitions using their names
        // and/or option codes so keeping the option name in the
        // definition of option value makes sense.
        if (def->getName() != name) {
            isc_throw(DhcpConfigError, "specified option name '"
                      << name << "' does not match the "
                      << "option definition: '" << space
                      << "." << def->getName() << "' ("
                      << string_values_->getPosition("name") << ")");
        }

        // Option definition has been found so let's use it to create
        // an instance of our option.
        try {
            OptionPtr option = csv_format ?
                def->optionFactory(global_context_->universe_,
                                  code, data_tokens) :
                def->optionFactory(global_context_->universe_,
                                   code, binary);
            Subnet::OptionDescriptor desc(option, false);
            option_descriptor_.option = option;
            option_descriptor_.persistent = false;
        } catch (const isc::Exception& ex) {
            isc_throw(DhcpConfigError, "option data does not match"
                      << " option definition (space: " << space
                      << ", code: " << code << "): "
                      << ex.what() << " ("
                      << string_values_->getPosition("data") << ")");
        }
    }

    // All went good, so we can set the option space name.
    option_space_ = space;
}

// **************************** OptionDataListParser *************************
OptionDataListParser::OptionDataListParser(const std::string&,
    OptionStoragePtr options, ParserContextPtr global_context,
    OptionDataParserFactory* optionDataParserFactory)
    : options_(options), local_options_(new OptionStorage()),
    global_context_(global_context),
    optionDataParserFactory_(optionDataParserFactory) {
    if (!options_) {
        isc_throw(isc::dhcp::DhcpConfigError, "parser logic error: "
             << "options storage may not be NULL");
    }

    if (!options_) {
        isc_throw(isc::dhcp::DhcpConfigError, "parser logic error: "
             << "context may not be NULL");
    }

    if (!optionDataParserFactory_) {
        isc_throw(isc::dhcp::DhcpConfigError, "parser logic error: "
             << "option data parser factory may not be NULL");
    }
}

void
OptionDataListParser::build(ConstElementPtr option_data_list) {
    BOOST_FOREACH(ConstElementPtr option_value, option_data_list->listValue()) {
        boost::shared_ptr<OptionDataParser>
            parser((*optionDataParserFactory_)("option-data",
                    local_options_, global_context_));

        // options_ member will hold instances of all options thus
        // each OptionDataParser takes it as a storage.
        // Build the instance of a single option.
        parser->build(option_value);
        // Store a parser as it will be used to commit.
        parsers_.push_back(parser);
    }
}

void
OptionDataListParser::commit() {
    BOOST_FOREACH(ParserPtr parser, parsers_) {
        parser->commit();
    }

    // Parsing was successful and we have all configured
    // options in local storage. We can now replace old values
    // with new values.
    std::swap(*local_options_, *options_);
}

// ******************************** OptionDefParser ****************************
OptionDefParser::OptionDefParser(const std::string&,
                                 OptionDefStoragePtr storage,
                                 ParserContextPtr global_context)
    : storage_(storage),
      boolean_values_(new BooleanStorage()),
      string_values_(new StringStorage()),
      uint32_values_(new Uint32Storage()),
      global_context_(global_context) {
    if (!storage_) {
        isc_throw(isc::dhcp::DhcpConfigError, "parser logic error: "
             << "options storage may not be NULL");
    }
}

void
OptionDefParser::build(ConstElementPtr option_def) {
    // Parse the elements that make up the option definition.
    BOOST_FOREACH(ConfigPair param, option_def->mapValue()) {
        std::string entry(param.first);
        ParserPtr parser;
        if (entry == "name" || entry == "type" || entry == "record-types"
            || entry == "space" || entry == "encapsulate") {
            StringParserPtr str_parser(new StringParser(entry,
                                       string_values_));
            parser = str_parser;
        } else if (entry == "code") {
            Uint32ParserPtr code_parser(new Uint32Parser(entry,
                                        uint32_values_));
            parser = code_parser;
        } else if (entry == "array") {
            BooleanParserPtr array_parser(new BooleanParser(entry,
                                         boolean_values_));
            parser = array_parser;
        } else {
            isc_throw(DhcpConfigError, "invalid parameter '" << entry
                      << "' (" << param.second->getPosition() << ")");
        }

        parser->build(param.second);
        parser->commit();
    }
    // Create an instance of option definition.
    createOptionDef(option_def);

    // Get all items we collected so far for the particular option space.
    OptionDefContainerPtr defs = storage_->getItems(option_space_name_);

    // Check if there are any items with option code the same as the
    // one specified for the definition we are now creating.
    const OptionDefContainerTypeIndex& idx = defs->get<1>();
    const OptionDefContainerTypeRange& range =
            idx.equal_range(option_definition_->getCode());

    // If there are any items with this option code already we need
    // to issue an error because we don't allow duplicates for
    // option definitions within an option space.
    if (std::distance(range.first, range.second) > 0) {
        isc_throw(DhcpConfigError, "duplicated option definition for"
                  << " code '" << option_definition_->getCode() << "' ("
                  << option_def->getPosition() << ")");
    }
}

void
OptionDefParser::commit() {
    if (storage_ && option_definition_ &&
        OptionSpace::validateName(option_space_name_)) {
            storage_->addItem(option_definition_, option_space_name_);
    }
}

void
OptionDefParser::createOptionDef(ConstElementPtr option_def_element) {
    // Check if mandatory parameters have been specified.
    std::string name;
    uint32_t code;
    std::string type;
    try {
        name = string_values_->getParam("name");
        code = uint32_values_->getParam("code");
        type = string_values_->getParam("type");
    } catch (const std::exception& ex) {
        isc_throw(DhcpConfigError, ex.what() << " ("
                  << option_def_element->getPosition() << ")");
    }

    bool array_type = boolean_values_->getOptionalParam("array", false);
    std::string record_types =
        string_values_->getOptionalParam("record-types", "");
    std::string space = string_values_->getOptionalParam("space",
              global_context_->universe_ == Option::V4 ? "dhcp4" : "dhcp6");
    std::string encapsulates =
        string_values_->getOptionalParam("encapsulate", "");

    if (!OptionSpace::validateName(space)) {
        isc_throw(DhcpConfigError, "invalid option space name '"
                  << space << "' ("
                  << string_values_->getPosition("space") << ")");
    }

    // Create option definition.
    OptionDefinitionPtr def;
    // We need to check if user has set encapsulated option space
    // name. If so, different constructor will be used.
    if (!encapsulates.empty()) {
        // Arrays can't be used together with sub-options.
        if (array_type) {
            isc_throw(DhcpConfigError, "option '" << space << "."
                      << "name" << "', comprising an array of data"
                      << " fields may not encapsulate any option space ("
                      << option_def_element->getPosition() << ")");

        } else if (encapsulates == space) {
            isc_throw(DhcpConfigError, "option must not encapsulate"
                      << " an option space it belongs to: '"
                      << space << "." << name << "' is set to"
                      << " encapsulate '" << space << "' ("
                      << option_def_element->getPosition() << ")");

        } else {
            def.reset(new OptionDefinition(name, code, type,
                        encapsulates.c_str()));
        }

    } else {
        def.reset(new OptionDefinition(name, code, type, array_type));

    }

    // Split the list of record types into tokens.
    std::vector<std::string> record_tokens =
    isc::util::str::tokens(record_types, ",");
    // Iterate over each token and add a record type into
    // option definition.
    BOOST_FOREACH(std::string record_type, record_tokens) {
        try {
            boost::trim(record_type);
            if (!record_type.empty()) {
                    def->addRecordField(record_type);
            }
        } catch (const Exception& ex) {
            isc_throw(DhcpConfigError, "invalid record type values"
                      << " specified for the option definition: "
                      << ex.what() << " ("
                      << string_values_->getPosition("record-types") << ")");
        }
    }

    // Validate the definition.
    try {
        def->validate();
    } catch (const std::exception& ex) {
        isc_throw(DhcpConfigError, ex.what()
                  << " (" << option_def_element->getPosition() << ")");
    }

    // Option definition has been created successfully.
    option_space_name_ = space;
    option_definition_ = def;
}

// ******************************** OptionDefListParser ************************
OptionDefListParser::OptionDefListParser(const std::string&,
                                         ParserContextPtr global_context)
    : storage_(global_context->option_defs_),
      global_context_(global_context) {
    if (!storage_) {
        isc_throw(isc::dhcp::DhcpConfigError, "parser logic error: "
             << "storage may not be NULL");
    }
}

void
OptionDefListParser::build(ConstElementPtr option_def_list) {
    // Clear existing items in the storage.
    // We are going to replace all of them.
    storage_->clearItems();

    if (!option_def_list) {
        isc_throw(DhcpConfigError, "parser error: a pointer to a list of"
                  << " option definitions is NULL ("
                  << option_def_list->getPosition() << ")");
    }

    BOOST_FOREACH(ConstElementPtr option_def, option_def_list->listValue()) {
        boost::shared_ptr<OptionDefParser>
            parser(new OptionDefParser("single-option-def", storage_,
                                       global_context_));
        parser->build(option_def);
        parser->commit();
    }

    CfgMgr& cfg_mgr = CfgMgr::instance();
    cfg_mgr.deleteOptionDefs();

    // We need to move option definitions from the temporary
    // storage to the storage.
    std::list<std::string> space_names = storage_->getOptionSpaceNames();

    BOOST_FOREACH(std::string space_name, space_names) {
        BOOST_FOREACH(OptionDefinitionPtr def,
                    *(storage_->getItems(space_name))) {
            // All option definitions should be initialized to non-NULL
            // values. The validation is expected to be made by the
            // OptionDefParser when creating an option definition.
            assert(def);
            // The Config Manager may thrown an exception if the duplicated
            // definition is being added. Catch the exceptions here to and
            // append the position in the config.
            try {
                cfg_mgr.addOptionDef(def, space_name);
            } catch (const std::exception& ex) {
                isc_throw(DhcpConfigError, ex.what() << " ("
                          << option_def_list->getPosition() << ")");
            }
        }
    }
}

void
OptionDefListParser::commit() {
    // Do nothing.
}

//****************************** RelayInfoParser ********************************
RelayInfoParser::RelayInfoParser(const std::string&,
                                 const isc::dhcp::Subnet::RelayInfoPtr& relay_info,
                                 const Option::Universe& family)
    :storage_(relay_info), local_(isc::asiolink::IOAddress(
                                  family == Option::V4 ? "0.0.0.0" : "::")),
     string_values_(new StringStorage()), family_(family) {
    if (!relay_info) {
        isc_throw(isc::dhcp::DhcpConfigError, "parser logic error: "
                  << "relay-info storage may not be NULL");
    }

};

void
RelayInfoParser::build(ConstElementPtr relay_info) {

    BOOST_FOREACH(ConfigPair param, relay_info->mapValue()) {
        ParserPtr parser(createConfigParser(param.first));
        parser->build(param.second);
        parser->commit();
    }

    // Get the IP address
    boost::scoped_ptr<asiolink::IOAddress> ip;
    try {
        ip.reset(new asiolink::IOAddress(string_values_->getParam("ip-address")));
    } catch (...)  {
        isc_throw(DhcpConfigError, "Failed to parse ip-address "
                  "value: " << string_values_->getParam("ip-address")
                  << " (" << string_values_->getPosition("ip-address") << ")");
    }

    if ( (ip->isV4() && family_ != Option::V4) ||
         (ip->isV6() && family_ != Option::V6) ) {
        isc_throw(DhcpConfigError, "ip-address field " << ip->toText()
                  << "does not have IP address of expected family type: "
                  << (family_ == Option::V4 ? "IPv4" : "IPv6")
                  << " (" << string_values_->getPosition("ip-address") << ")");
    }

    local_.addr_ = *ip;
}

isc::dhcp::ParserPtr
RelayInfoParser::createConfigParser(const std::string& parameter) {
    DhcpConfigParser* parser = NULL;
    if (parameter.compare("ip-address") == 0) {
        parser = new StringParser(parameter, string_values_);
    } else {
        isc_throw(NotImplemented,
                  "parser error: RelayInfoParser parameter not supported: "
                  << parameter);
    }

    return (isc::dhcp::ParserPtr(parser));
}

void
RelayInfoParser::commit() {
    *storage_ = local_;
}

//****************************** PoolsListParser ********************************
PoolsListParser::PoolsListParser(const std::string&, PoolStoragePtr pools)
    :pools_(pools), local_pools_(new PoolStorage()) {
    if (!pools_) {
        isc_throw(isc::dhcp::DhcpConfigError, "parser logic error: "
                  << "storage may not be NULL");
    }
}

void
PoolsListParser::build(ConstElementPtr pools) {
    BOOST_FOREACH(ConstElementPtr pool, pools->listValue()) {

        // Iterate over every structure on the pools list and invoke
        // a separate parser for it.
        ParserPtr parser = poolParserMaker(local_pools_);

        parser->build(pool);

        // Before we can create a pool, we need to ask the pool parser
        // to create it.
        parser->commit();
    }
}

void PoolsListParser::commit() {
    if (pools_) {
        // local_pools_ holds the values produced by the build function.
        // At this point parsing should have completed successfuly so
        // we can append new data to the supplied storage.
        pools_->insert(pools_->end(), local_pools_->begin(), local_pools_->end());
    }
}

//****************************** PoolParser ********************************
PoolParser::PoolParser(const std::string&,  PoolStoragePtr pools)
        :pools_(pools) {

    if (!pools_) {
        isc_throw(isc::dhcp::DhcpConfigError, "parser logic error: "
                  << "storage may not be NULL");
    }
}

void
PoolParser::build(ConstElementPtr pool_structure) {

    ConstElementPtr text_pool = pool_structure->get("pool");

    if (!text_pool) {
        isc_throw(DhcpConfigError, "Mandatory 'pool' entry missing in "
                  "definition: (" << text_pool->getPosition() << ")");
    }

    // That should be a single pool representation. It should contain
    // text is form prefix/len or first - last. Note that spaces
    // are allowed
    string txt = text_pool->stringValue();

    // first let's remove any whitespaces
    boost::erase_all(txt, " "); // space
    boost::erase_all(txt, "\t"); // tabulation

    // Is this prefix/len notation?
    size_t pos = txt.find("/");
    if (pos != string::npos) {
        isc::asiolink::IOAddress addr("::");
        uint8_t len = 0;
        try {
            addr = isc::asiolink::IOAddress(txt.substr(0, pos));

            // start with the first character after /
            string prefix_len = txt.substr(pos + 1);

            // It is lexical cast to int and then downcast to uint8_t.
            // Direct cast to uint8_t (which is really an unsigned char)
            // will result in interpreting the first digit as output
            // value and throwing exception if length is written on two
            // digits (because there are extra characters left over).

            // No checks for values over 128. Range correctness will
            // be checked in Pool4 constructor.
            len = boost::lexical_cast<int>(prefix_len);
        } catch (...)  {
            isc_throw(DhcpConfigError, "Failed to parse pool "
                      "definition: " << text_pool->stringValue()
                      << " (" << text_pool->getPosition() << ")");
        }

        PoolPtr pool(poolMaker(addr, len));
        local_pools_.push_back(pool);
        return;
    }

    // Is this min-max notation?
    pos = txt.find("-");
    if (pos != string::npos) {
        // using min-max notation
        isc::asiolink::IOAddress min(txt.substr(0,pos));
        isc::asiolink::IOAddress max(txt.substr(pos + 1));

        PoolPtr pool(poolMaker(min, max));
        local_pools_.push_back(pool);
        return;
    }

    isc_throw(DhcpConfigError, "invalid pool definition: "
              << text_pool->stringValue() <<
              ". There are two acceptable formats <min address-max address>"
              " or <prefix/len> ("
              << text_pool->getPosition() << ")");
}

void
PoolParser::commit() {
    if (pools_) {
        // local_pools_ holds the values produced by the build function.
        // At this point parsing should have completed successfuly so
        // we can append new data to the supplied storage.
        pools_->insert(pools_->end(), local_pools_.begin(), local_pools_.end());
    }
}

//****************************** SubnetConfigParser *************************

SubnetConfigParser::SubnetConfigParser(const std::string&,
                                       ParserContextPtr global_context,
                                       const isc::asiolink::IOAddress& default_addr)
    : uint32_values_(new Uint32Storage()), string_values_(new StringStorage()),
    pools_(new PoolStorage()), options_(new OptionStorage()),
    global_context_(global_context),
    relay_info_(new isc::dhcp::Subnet::RelayInfo(default_addr)) {
    // The first parameter should always be "subnet", but we don't check
    // against that here in case some wants to reuse this parser somewhere.
    if (!global_context_) {
        isc_throw(isc::dhcp::DhcpConfigError, "parser logic error: "
                 << "context storage may not be NULL");
    }
}

void
SubnetConfigParser::build(ConstElementPtr subnet) {
    BOOST_FOREACH(ConfigPair param, subnet->mapValue()) {
        ParserPtr parser;
        // When unsupported parameter is specified, the function called
        // below will thrown an exception. We have to catch this exception
        // to append the line number where the parameter is.
        try {
            parser.reset(createSubnetConfigParser(param.first));
        } catch (const std::exception& ex) {
            isc_throw(DhcpConfigError, ex.what() << " ("
                      << param.second->getPosition() << ")");
        }
        parser->build(param.second);
        parsers_.push_back(parser);
    }

    // In order to create new subnet we need to get the data out
    // of the child parsers first. The only way to do it is to
    // invoke commit on them because it will make them write
    // parsed data into storages we have supplied.
    // Note that triggering commits on child parsers does not
    // affect global data because we supplied pointers to storages
    // local to this object. Thus, even if this method fails
    // later on, the configuration remains consistent.
    BOOST_FOREACH(ParserPtr parser, parsers_) {
        parser->commit();
    }

    // Create a subnet.
    try {
        createSubnet();
    } catch (const std::exception& ex) {
        isc_throw(DhcpConfigError,
                  "subnet configuration failed (" << subnet->getPosition()
                  << "): " << ex.what());
    }
}

void
SubnetConfigParser::appendSubOptions(const std::string& option_space,
                                     OptionPtr& option) {
    // Only non-NULL options are stored in option container.
    // If this option pointer is NULL this is a serious error.
    assert(option);

    OptionDefinitionPtr def;
    if (isServerStdOption(option_space, option->getType())) {
        def = getServerStdOptionDefinition(option->getType());
        // Definitions for some of the standard options hasn't been
        // implemented so it is ok to leave here.
        if (!def) {
            return;
        }
    } else {
        const OptionDefContainerPtr defs =
                global_context_->option_defs_->getItems(option_space);

        const OptionDefContainerTypeIndex& idx = defs->get<1>();
        const OptionDefContainerTypeRange& range =
        idx.equal_range(option->getType());
        // There is no definition so we have to leave.
        if (std::distance(range.first, range.second) == 0) {
            return;
        }

        def = *range.first;

        // If the definition exists, it must be non-NULL.
        // Otherwise it is a programming error.
        assert(def);
    }

    // We need to get option definition for the particular option space
    // and code. This definition holds the information whether our
    // option encapsulates any option space.
    // Get the encapsulated option space name.
    std::string encapsulated_space = def->getEncapsulatedSpace();
    // If option space name is empty it means that our option does not
    // encapsulate any option space (does not include sub-options).
    if (!encapsulated_space.empty()) {
        // Get the sub-options that belong to the encapsulated
        // option space.
        const Subnet::OptionContainerPtr sub_opts =
                global_context_->options_->getItems(encapsulated_space);
        // Append sub-options to the option.
        BOOST_FOREACH(Subnet::OptionDescriptor desc, *sub_opts) {
            if (desc.option) {
                option->addOption(desc.option);
            }
        }
    }
}

void
SubnetConfigParser::createSubnet() {
    std::string subnet_txt;
    try {
        subnet_txt = string_values_->getParam("subnet");
    } catch (const DhcpConfigError &) {
        // rethrow with precise error
        isc_throw(DhcpConfigError,
                 "mandatory 'subnet' parameter is missing for a subnet being"
                  " configured");
    }

    // Remove any spaces or tabs.
    boost::erase_all(subnet_txt, " ");
    boost::erase_all(subnet_txt, "\t");

    // The subnet format is prefix/len. We are going to extract
    // the prefix portion of a subnet string to create IOAddress
    // object from it. IOAddress will be passed to the Subnet's
    // constructor later on. In order to extract the prefix we
    // need to get all characters preceding "/".
    size_t pos = subnet_txt.find("/");
    if (pos == string::npos) {
        isc_throw(DhcpConfigError,
                  "Invalid subnet syntax (prefix/len expected):" << subnet_txt
                  << " (" << string_values_->getPosition("subnet") << ")");
    }

    // Try to create the address object. It also validates that
    // the address syntax is ok.
    isc::asiolink::IOAddress addr(subnet_txt.substr(0, pos));
    uint8_t len = boost::lexical_cast<unsigned int>(subnet_txt.substr(pos + 1));

    // Call the subclass's method to instantiate the subnet
    initSubnet(addr, len);

    // Add pools to it.
    for (PoolStorage::iterator it = pools_->begin(); it != pools_->end();
         ++it) {
        subnet_->addPool(*it);
    }

    // Configure interface, if defined

    // Get interface name. If it is defined, then the subnet is available
    // directly over specified network interface.
    std::string iface;
    try {
        iface = string_values_->getParam("interface");
    } catch (const DhcpConfigError &) {
        // iface not mandatory so swallow the exception
    }

    if (!iface.empty()) {
        if (!IfaceMgr::instance().getIface(iface)) {
            isc_throw(DhcpConfigError, "Specified interface name " << iface
                      << " for subnet " << subnet_->toText()
                      << " is not present" << " in the system ("
                      << string_values_->getPosition("interface") << ")");
        }

        subnet_->setIface(iface);
    }

    // We are going to move configured options to the Subnet object.
    // Configured options reside in the container where options
    // are grouped by space names. Thus we need to get all space names
    // and iterate over all options that belong to them.
    std::list<std::string> space_names = options_->getOptionSpaceNames();
    BOOST_FOREACH(std::string option_space, space_names) {
        // Get all options within a particular option space.
        BOOST_FOREACH(Subnet::OptionDescriptor desc,
                      *options_->getItems(option_space)) {
            // The pointer should be non-NULL. The validation is expected
            // to be performed by the OptionDataParser before adding an
            // option descriptor to the container.
            assert(desc.option);
            // We want to check whether an option with the particular
            // option code has been already added. If so, we want
            // to issue a warning.
            Subnet::OptionDescriptor existing_desc =
                            subnet_->getOptionDescriptor("option_space",
                                                 desc.option->getType());
            if (existing_desc.option) {
                duplicate_option_warning(desc.option->getType(), addr);
            }
            // Add sub-options (if any).
            appendSubOptions(option_space, desc.option);

            // Check if the option space defines a vendor-option
            uint32_t vendor_id = optionSpaceToVendorId(option_space);
            if (vendor_id) {
                // This is a vendor option
                subnet_->addVendorOption(desc.option, false, vendor_id);
            } else {
                // This is a normal option
                subnet_->addOption(desc.option, false, option_space);
            }
        }
    }

    // Check all global options and add them to the subnet object if
    // they have been configured in the global scope. If they have been
    // configured in the subnet scope we don't add global option because
    // the one configured in the subnet scope always takes precedence.
    space_names = global_context_->options_->getOptionSpaceNames();
    BOOST_FOREACH(std::string option_space, space_names) {
        // Get all global options for the particular option space.
        BOOST_FOREACH(Subnet::OptionDescriptor desc,
                *(global_context_->options_->getItems(option_space))) {
            // The pointer should be non-NULL. The validation is expected
            // to be performed by the OptionDataParser before adding an
            // option descriptor to the container.
            assert(desc.option);
            // Check if the particular option has been already added.
            // This would mean that it has been configured in the
            // subnet scope. Since option values configured in the
            // subnet scope take precedence over globally configured
            // values we don't add option from the global storage
            // if there is one already.
            Subnet::OptionDescriptor existing_desc =
                    subnet_->getOptionDescriptor(option_space,
                                                desc.option->getType());
            if (!existing_desc.option) {
                // Add sub-options (if any).
                appendSubOptions(option_space, desc.option);

                uint32_t vendor_id = optionSpaceToVendorId(option_space);
                if (vendor_id) {
                    // This is a vendor option
                    subnet_->addVendorOption(desc.option, false, vendor_id);
                } else {
                    // This is a normal option
                    subnet_->addOption(desc.option, false, option_space);
                }
            }
        }
    }
}

uint32_t
SubnetConfigParser::optionSpaceToVendorId(const std::string& option_space) {
    if (option_space.size() < 8) {
        // 8 is a minimal length of "vendor-X" format
        return (0);
    }
    if (option_space.substr(0,7) != "vendor-") {
        return (0);
    }

    // text after "vendor-", supposedly numbers only
    string x = option_space.substr(7);

    int64_t check;
    try {
        check = boost::lexical_cast<int64_t>(x);
    } catch (const boost::bad_lexical_cast &) {
        /// @todo: Should we throw here?
        // isc_throw(BadValue, "Failed to parse vendor-X value (" << x
        //           << ") as unsigned 32-bit integer.");
        return (0);
    }
    if (check > std::numeric_limits<uint32_t>::max()) {
        /// @todo: Should we throw here?
        //isc_throw(BadValue, "Value " << x << "is too large"
        //          << " for unsigned 32-bit integer.");
        return (0);
    }
    if (check < 0) {
        /// @todo: Should we throw here?
        // isc_throw(BadValue, "Value " << x << "is negative."
        //       << " Only 0 or larger are allowed for unsigned 32-bit integer.");
        return (0);
    }

    // value is small enough to fit
    return (static_cast<uint32_t>(check));
}

isc::dhcp::Triplet<uint32_t>
SubnetConfigParser::getParam(const std::string& name) {
    uint32_t value = 0;
    try {
        // look for local value
        value = uint32_values_->getParam(name);
    } catch (const DhcpConfigError &) {
        try {
            // no local, use global value
            value = global_context_->uint32_values_->getParam(name);
        } catch (const DhcpConfigError &) {
            isc_throw(DhcpConfigError, "Mandatory parameter " << name
                      << " missing (no global default and no subnet-"
                      << "specific value)");
        }
    }

    return (Triplet<uint32_t>(value));
}

isc::dhcp::Triplet<uint32_t>
SubnetConfigParser::getOptionalParam(const std::string& name) {
    try {
        return (getParam(name));
    } catch (const DhcpConfigError &) {
        // No error. We will return an unspecified value.
    }
    return (Triplet<uint32_t>());
}

//**************************** D2ClientConfigParser **********************
D2ClientConfigParser::D2ClientConfigParser(const std::string& entry_name)
    : entry_name_(entry_name), boolean_values_(new BooleanStorage()),
      uint32_values_(new Uint32Storage()), string_values_(new StringStorage()),
      local_client_config_() {
}

D2ClientConfigParser::~D2ClientConfigParser() {
}

void
D2ClientConfigParser::build(isc::data::ConstElementPtr client_config) {
    BOOST_FOREACH(ConfigPair param, client_config->mapValue()) {
        ParserPtr parser;
        try {
            parser = createConfigParser(param.first);
        } catch (std::exception& ex) {
            // Catch exception in case the configuration contains the
            // unsupported parameter. In this case, we will need to
            // append the position of this element.
            isc_throw(DhcpConfigError, ex.what() << " ("
                      << param.second->getPosition() << ")");
        }

        parser->build(param.second);
        parser->commit();
    }

    /// @todo Create configuration from the configuration parameters. Because
    /// the validation of the D2 configuration is atomic, there is no way to
    /// tell which parameter is invalid. Therefore, we catch all exceptions
    /// and append the line number of the parent element. In the future we
    /// may should extend D2ClientConfig code so as it returns the name of
    /// the invalid parameter.
    try {
        bool enable_updates = boolean_values_->getParam("enable-updates");
        if (!enable_updates && (client_config->mapValue().size() == 1)) {
            // If enable-updates is the only parameter and it is false then
            // we're done.  This allows for an abbreviated configuration entry
            // that only contains that flag.  Use the default D2ClientConfig
            // constructor to a create a disabled instance.
            local_client_config_.reset(new D2ClientConfig());

            return;
        }

        // Get all parameters that are needed to create the D2ClientConfig.
        IOAddress server_ip =
            IOAddress(string_values_->getOptionalParam("server-ip",
                                                       D2ClientConfig::
                                                       DFT_SERVER_IP));

        uint32_t server_port =
            uint32_values_->getOptionalParam("server-port",
                                             D2ClientConfig::DFT_SERVER_PORT);

        // The default sender IP depends on the server IP family
        asiolink::IOAddress
            sender_ip(string_values_->
                      getOptionalParam("sender-ip",
                                       (server_ip.isV4() ?
                                        D2ClientConfig::DFT_V4_SENDER_IP :
                                        D2ClientConfig::DFT_V6_SENDER_IP)));

        uint32_t sender_port =
            uint32_values_->getOptionalParam("sender-port",
                                             D2ClientConfig::
                                             DFT_SENDER_PORT);
        uint32_t max_queue_size
            = uint32_values_->getOptionalParam("max-queue-size",
                                               D2ClientConfig::
                                               DFT_MAX_QUEUE_SIZE);

        dhcp_ddns::NameChangeProtocol ncr_protocol =
            dhcp_ddns::stringToNcrProtocol(string_values_->
                                           getOptionalParam("ncr-protocol",
                                                            D2ClientConfig::
                                                            DFT_NCR_PROTOCOL));
        dhcp_ddns::NameChangeFormat ncr_format
            = dhcp_ddns::stringToNcrFormat(string_values_->
                                           getOptionalParam("ncr-format",
                                                            D2ClientConfig::
                                                            DFT_NCR_FORMAT));
        std::string generated_prefix =
            string_values_->getOptionalParam("generated-prefix",
                                             D2ClientConfig::
                                             DFT_GENERATED_PREFIX);
        std::string qualifying_suffix =
            string_values_->getOptionalParam("qualifying-suffix",
                                             D2ClientConfig::
                                             DFT_QUALIFYING_SUFFIX);

        bool always_include_fqdn =
            boolean_values_->getOptionalParam("always-include-fqdn",
                                                D2ClientConfig::
                                                DFT_ALWAYS_INCLUDE_FQDN);

        bool override_no_update =
            boolean_values_->getOptionalParam("override-no-update",
                                              D2ClientConfig::
                                              DFT_OVERRIDE_NO_UPDATE);

        bool override_client_update =
            boolean_values_->getOptionalParam("override-client-update",
                                              D2ClientConfig::
                                              DFT_OVERRIDE_CLIENT_UPDATE);

        bool replace_client_name =
            boolean_values_->getOptionalParam("replace-client-name",
                                              D2ClientConfig::
                                              DFT_REPLACE_CLIENT_NAME);

        // Attempt to create the new client config.
        local_client_config_.reset(new D2ClientConfig(enable_updates,
                                                      server_ip,
                                                      server_port,
                                                      sender_ip,
                                                      sender_port,
                                                      max_queue_size,
                                                      ncr_protocol,
                                                      ncr_format,
                                                      always_include_fqdn,
                                                      override_no_update,
                                                      override_client_update,
                                                      replace_client_name,
                                                      generated_prefix,
                                                      qualifying_suffix));

    }  catch (const std::exception& ex) {
        isc_throw(DhcpConfigError, ex.what() << " ("
                  << client_config->getPosition() << ")");
    }
}

isc::dhcp::ParserPtr
D2ClientConfigParser::createConfigParser(const std::string& config_id) {
    DhcpConfigParser* parser = NULL;
    if ((config_id.compare("server-port") == 0) ||
        (config_id.compare("sender-port") == 0) ||
        (config_id.compare("max-queue-size") == 0)) {
        parser = new Uint32Parser(config_id, uint32_values_);
    } else if ((config_id.compare("server-ip") == 0) ||
        (config_id.compare("ncr-protocol") == 0) ||
        (config_id.compare("ncr-format") == 0) ||
        (config_id.compare("generated-prefix") == 0) ||
        (config_id.compare("sender-ip") == 0) ||
        (config_id.compare("qualifying-suffix") == 0)) {
        parser = new StringParser(config_id, string_values_);
    } else if ((config_id.compare("enable-updates") == 0) ||
        (config_id.compare("always-include-fqdn") == 0) ||
        (config_id.compare("allow-client-update") == 0) ||
        (config_id.compare("override-no-update") == 0) ||
        (config_id.compare("override-client-update") == 0) ||
        (config_id.compare("replace-client-name") == 0)) {
        parser = new BooleanParser(config_id, boolean_values_);
    } else {
        isc_throw(NotImplemented,
            "parser error: D2ClientConfig parameter not supported: "
            << config_id);
    }

    return (isc::dhcp::ParserPtr(parser));
}

void
D2ClientConfigParser::commit() {
    // @todo if local_client_config_ is empty then shutdown the listener...
    // @todo Should this also attempt to start a listener?
    // In keeping with Interface, Subnet, and Hooks parsers, then this
    // should initialize the listener.  Failure to init it, should cause
    // rollback.  This gets sticky, because who owns the listener instance?
    // Does CfgMgr maintain it or does the server class?  If the latter
    // how do we get that value here?
    // I'm thinkikng D2ClientConfig could contain the listener instance
    CfgMgr::instance().setD2ClientConfig(local_client_config_);
}

};  // namespace dhcp
};  // namespace isc
