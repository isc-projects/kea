// Copyright (C) 2013 Internet Systems Consortium, Inc. ("ISC")
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

#include <dhcpsrv/dhcp_parsers.h>
#include <dhcp/libdhcp++.h>
#include <dhcpsrv/cfgmgr.h>
#include <util/encode/hex.h>
#include <util/strutil.h>

#include <boost/foreach.hpp>
#include <boost/lexical_cast.hpp>
#include <boost/algorithm/string.hpp>
#include <boost/lexical_cast.hpp>

#include <string>
#include <map>

using namespace std;
using namespace isc::data;

namespace isc {
namespace dhcp {

// Pointers to various parser objects.
typedef boost::shared_ptr<BooleanParser> BooleanParserPtr;
typedef boost::shared_ptr<StringParser> StringParserPtr;
typedef boost::shared_ptr<Uint32Parser> Uint32ParserPtr;

// **************************** DebugParser *************************

DebugParser::DebugParser(const std::string& param_name)
    :param_name_(param_name) {
}

void DebugParser::build(ConstElementPtr new_config) {
    std::cout << "Build for token: [" << param_name_ << "] = ["
        << value_->str() << "]" << std::endl; 
    value_ = new_config;
}

void DebugParser::commit() {
    // Debug message. The whole DebugParser class is used only for parser
    // debugging, and is not used in production code. It is very convenient
    // to keep it around. Please do not turn this cout into logger calls.
    std::cout << "Commit for token: [" << param_name_ << "] = ["
                  << value_->str() << "]" << std::endl;
}

// **************************** BooleanParser  *************************
BooleanParser::BooleanParser(const std::string& param_name, BooleanStorage *storage)
    : storage_(storage), param_name_(param_name), value_(false) {
    // Empty parameter name is invalid.
    if (param_name_.empty()) {
        isc_throw(isc::dhcp::DhcpConfigError, "parser logic error:"
        << "empty parameter name provided");
    }

    // NUll storage is invalid.
    if (!storage_) {
        isc_throw(isc::dhcp::DhcpConfigError, "parser logic error:"
            << "storage may not be NULL");
    }
}

void BooleanParser::build(ConstElementPtr value) {
    // The Config Manager checks if user specified a
    // valid value for a boolean parameter: True or False.
    // It is then ok to assume that if str() does not return
    // 'true' the value is 'false'.
    value_ = (value->str() == "true") ? true : false;
}

void BooleanParser::commit() {
    // If a given parameter already exists in the storage we override
    // its value. If it doesn't we insert a new element.
    storage_->setParam(param_name_, value_);
}

// **************************** Uin32Parser  *************************

Uint32Parser::Uint32Parser(const std::string& param_name, Uint32Storage *storage)
    : storage_(storage), param_name_(param_name) {
    // Empty parameter name is invalid.
    if (param_name_.empty()) {
        isc_throw(DhcpConfigError, "parser logic error:"
            << "empty parameter name provided");
    }

    // NULL storage is invalid.
    if (!storage_) {
        isc_throw(isc::dhcp::DhcpConfigError, "parser logic error:"
            << "storage may not be NULL");
    }
}

void Uint32Parser::build(ConstElementPtr value) {
    int64_t check;
    string x = value->str();
    try {
        check = boost::lexical_cast<int64_t>(x);
    } catch (const boost::bad_lexical_cast &) {
        isc_throw(BadValue, "Failed to parse value " << value->str()
                  << " as unsigned 32-bit integer.");
    }
    if (check > std::numeric_limits<uint32_t>::max()) {
        isc_throw(BadValue, "Value " << value->str() << "is too large"
                  << " for unsigned 32-bit integer.");
    }
    if (check < 0) {
        isc_throw(BadValue, "Value " << value->str() << "is negative."
                  << " Only 0 or larger are allowed for unsigned 32-bit integer.");
    }

    // value is small enough to fit
    value_ = static_cast<uint32_t>(check);
}

void Uint32Parser::commit() {
    // If a given parameter already exists in the storage we override
    // its value. If it doesn't we insert a new element.
    storage_->setParam(param_name_, value_);
}

// **************************** StringParser  *************************

StringParser::StringParser(const std::string& param_name, StringStorage *storage)
    :storage_(storage), param_name_(param_name) {
    // Empty parameter name is invalid.
    if (param_name_.empty()) {
        isc_throw(DhcpConfigError, "parser logic error:"
                  << "empty parameter name provided");
    }

    // NULL storage is invalid.
    if (!storage_) {
        isc_throw(isc::dhcp::DhcpConfigError, "parser logic error:"
            << "storage may not be NULL");
    }
}

void StringParser::build(ConstElementPtr value) {
    value_ = value->str();
    boost::erase_all(value_, "\"");
}

void StringParser::commit() {
    // If a given parameter already exists in the storage we override
    // its value. If it doesn't we insert a new element.
    storage_->setParam(param_name_, value_);
}

// **************************** InterfaceListConfigParser *************************

InterfaceListConfigParser::InterfaceListConfigParser(const std::string& param_name) {
    if (param_name != "interface") {
        isc_throw(BadValue, "Internal error. Interface configuration "
            "parser called for the wrong parameter: " << param_name);
    }
}

void InterfaceListConfigParser::build(ConstElementPtr value) {
    BOOST_FOREACH(ConstElementPtr iface, value->listValue()) {
        interfaces_.push_back(iface->str());
    }
}

void InterfaceListConfigParser::commit() {
    /// @todo: Implement per interface listening. Currently always listening
    /// on all interfaces.
}

// **************************** OptionDataParser *************************

OptionDataParser::OptionDataParser(const std::string&, OptionStorage *options,
    OptionDefStorage *option_defs, Option::Universe universe)
        : options_(options),
          // initialize option to NULL ptr
          option_descriptor_(false), global_option_defs_(option_defs),
          universe_(universe) {
    if (!options_) {
        isc_throw(isc::dhcp::DhcpConfigError, "parser logic error:"
             << "options storage may not be NULL");
    }
}

void OptionDataParser::build(ConstElementPtr option_data_entries) {
    BOOST_FOREACH(ConfigPair param, option_data_entries->mapValue()) {
        ParserPtr parser;
        if (param.first == "name" || param.first == "data" ||
            param.first == "space") {
            StringParserPtr name_parser(new StringParser(param.first, &string_values_)); 
            parser = name_parser;
        } else if (param.first == "code") {
            Uint32ParserPtr code_parser(new Uint32Parser(param.first, &uint32_values_)); 
            parser = code_parser;
        } else if (param.first == "csv-format") {
            BooleanParserPtr value_parser(new BooleanParser(param.first, &boolean_values_)); 
            parser = value_parser;
        } else {
            isc_throw(DhcpConfigError,
                      "Parser error: option-data parameter not supported: "
                      << param.first);
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
    createOption();
}

void OptionDataParser::commit() {
    if (!option_descriptor_.option) {
        // Before we can commit the new option should be configured. If it is not
        // than somebody must have called commit() before build().
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

void OptionDataParser::createOption() {
    // Option code is held in the uint32_t storage but is supposed to
    // be uint16_t value. We need to check that value in the configuration
    // does not exceed range of uint8_t and is not zero.
    uint32_t option_code = uint32_values_.getParam("code");
    if (option_code == 0) {
        isc_throw(DhcpConfigError, "option code must not be zero."
                << " Option code '0' is reserved in DHCPv4.");
    } else if (option_code > std::numeric_limits<uint8_t>::max()) {
        isc_throw(DhcpConfigError, "invalid option code '" << option_code
                << "', it must not exceed '"
                << std::numeric_limits<uint8_t>::max() << "'");
    }

    // Check that the option name has been specified, is non-empty and does not
    // contain spaces
    std::string option_name = string_values_.getParam("name"); 
    if (option_name.empty()) {
        isc_throw(DhcpConfigError, "name of the option with code '"
                << option_code << "' is empty");
    } else if (option_name.find(" ") != std::string::npos) {
        isc_throw(DhcpConfigError, "invalid option name '" << option_name
                << "', space character is not allowed");
    }

    std::string option_space = string_values_.getParam("space"); 
    if (!OptionSpace::validateName(option_space)) {
        isc_throw(DhcpConfigError, "invalid option space name '"
                << option_space << "' specified for option '"
                << option_name << "' (code '" << option_code
                << "')");
    }

    // Find the Option Definition for the option by its option code.
    // findOptionDefinition will throw if not found, no need to test.
    OptionDefinitionPtr def;
    if (!(def = findServerSpaceOptionDefinition(option_space, option_code))) {
        // If we are not dealing with a standard option then we
        // need to search for its definition among user-configured
        // options. They are expected to be in the global storage
        // already.
        OptionDefContainerPtr defs = global_option_defs_->getItems(option_space);

        // The getItems() should never return the NULL pointer. If there are
        // no option definitions for the particular option space a pointer
        // to an empty container should be returned.
        assert(defs);
        const OptionDefContainerTypeIndex& idx = defs->get<1>();
        OptionDefContainerTypeRange range = idx.equal_range(option_code);
        if (std::distance(range.first, range.second) > 0) {
            def = *range.first;
        }
        if (!def) {
            isc_throw(DhcpConfigError, "definition for the option '"
                      << option_space << "." << option_name
                      << "' having code '" <<  option_code
                      << "' does not exist");
        }
    }

    // Get option data from the configuration database ('data' field).
    const std::string option_data = string_values_.getParam("data");
    const bool csv_format = boolean_values_.getParam("csv-format");

    // Transform string of hexadecimal digits into binary format.
    std::vector<uint8_t> binary;
    std::vector<std::string> data_tokens;

    if (csv_format) {
        // If the option data is specified as a string of comma
        // separated values then we need to split this string into
        // individual values - each value will be used to initialize
        // one data field of an option.
        data_tokens = isc::util::str::tokens(option_data, ",");
    } else {
        // Otherwise, the option data is specified as a string of
        // hexadecimal digits that we have to turn into binary format.
        try {
            util::encode::decodeHex(option_data, binary);
        } catch (...) {
            isc_throw(DhcpConfigError, "option data is not a valid"
                      << " string of hexadecimal digits: " << option_data);
        }
    }

    OptionPtr option;
    if (!def) {
        if (csv_format) {
            isc_throw(DhcpConfigError, "the CSV option data format can be"
                      " used to specify values for an option that has a"
                      " definition. The option with code " << option_code
                      << " does not have a definition.");
        }

        // @todo We have a limited set of option definitions intiialized at the moment.
        // In the future we want to initialize option definitions for all options.
        // Consequently an error will be issued if an option definition does not exist
        // for a particular option code. For now it is ok to create generic option
        // if definition does not exist.
        OptionPtr option(new Option(universe_, static_cast<uint16_t>(option_code),
                                        binary));
        // The created option is stored in option_descriptor_ class member until the
        // commit stage when it is inserted into the main storage. If an option with the
        // same code exists in main storage already the old option is replaced.
        option_descriptor_.option = option;
        option_descriptor_.persistent = false;
    } else {

        // Option name should match the definition. The option name
        // may seem to be redundant but in the future we may want
        // to reference options and definitions using their names
        // and/or option codes so keeping the option name in the
        // definition of option value makes sense.
        if (def->getName() != option_name) {
            isc_throw(DhcpConfigError, "specified option name '"
                      << option_name << "' does not match the "
                      << "option definition: '" << option_space
                      << "." << def->getName() << "'");
        }

        // Option definition has been found so let's use it to create
        // an instance of our option.
        try {
            OptionPtr option = csv_format ?
                def->optionFactory(universe_, option_code, data_tokens) :
                def->optionFactory(universe_, option_code, binary);
            Subnet::OptionDescriptor desc(option, false);
            option_descriptor_.option = option;
            option_descriptor_.persistent = false;
        } catch (const isc::Exception& ex) {
            isc_throw(DhcpConfigError, "option data does not match"
                      << " option definition (space: " << option_space
                      << ", code: " << option_code << "): "
                      << ex.what());
        }
    }

    // All went good, so we can set the option space name.
    option_space_ = option_space;
}

// **************************** OptionDataListParser *************************

OptionDataListParser::OptionDataListParser(const std::string&, 
    OptionStorage *storage, OptionDefStorage *global_option_defs,
    OptionDataParserFactory *optionDataParserFactory)
    : options_(storage), local_options_(), 
    global_option_defs_(global_option_defs),
    optionDataParserFactory_(optionDataParserFactory) {
    if (!options_) {
        isc_throw(isc::dhcp::DhcpConfigError, "parser logic error:"
             << "options storage may not be NULL");
    }

    if (!optionDataParserFactory_) {
        isc_throw(isc::dhcp::DhcpConfigError, "parser logic error:"
             << "option data parser factory may not be NULL");
    }
}


void OptionDataListParser::build(ConstElementPtr option_data_list) {
    BOOST_FOREACH(ConstElementPtr option_value, option_data_list->listValue()) {
        boost::shared_ptr<OptionDataParser> 
            parser((*optionDataParserFactory_)("option-data", &local_options_, global_option_defs_));

        // options_ member will hold instances of all options thus
        // each OptionDataParser takes it as a storage.
        // Build the instance of a single option.
        parser->build(option_value);
        // Store a parser as it will be used to commit.
        parsers_.push_back(parser);
    }
}

void OptionDataListParser::commit() {
    BOOST_FOREACH(ParserPtr parser, parsers_) {
        parser->commit();
    }

    // Parsing was successful and we have all configured
    // options in local storage. We can now replace old values
    // with new values.
    std::swap(local_options_, *options_);
}

// ******************************** OptionDefParser ****************************

OptionDefParser::OptionDefParser(const std::string&, OptionDefStorage *storage)
    : storage_(storage) {
    if (!storage_) {
        isc_throw(isc::dhcp::DhcpConfigError, "parser logic error:"
             << "options storage may not be NULL");
    }
}

void OptionDefParser::build(ConstElementPtr option_def) {
    // Parse the elements that make up the option definition.
     BOOST_FOREACH(ConfigPair param, option_def->mapValue()) {
        std::string entry(param.first);
        ParserPtr parser;
        if (entry == "name" || entry == "type" || entry == "record-types" 
            || entry == "space" || entry == "encapsulate") {
            StringParserPtr str_parser(new StringParser(entry, &string_values_));
            parser = str_parser;
        } else if (entry == "code") {
            Uint32ParserPtr code_parser(new Uint32Parser(entry, &uint32_values_));
            parser = code_parser;
        } else if (entry == "array") {
            BooleanParserPtr array_parser(new BooleanParser(entry, &boolean_values_));
            parser = array_parser;
        } else {
            isc_throw(DhcpConfigError, "invalid parameter: " << entry);
        }

        parser->build(param.second);
        parser->commit();
    }

    // Create an instance of option definition.
    createOptionDef();

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
                << " code '" << option_definition_->getCode() << "'");
    }
}

void OptionDefParser::commit() {
    if (storage_ && option_definition_ &&
        OptionSpace::validateName(option_space_name_)) {
            storage_->addItem(option_definition_, option_space_name_);
    }
}

void OptionDefParser::createOptionDef() {
    // Get the option space name and validate it.
    std::string space = string_values_.getParam("space");
    if (!OptionSpace::validateName(space)) {
        isc_throw(DhcpConfigError, "invalid option space name '"
                  << space << "'");
    }

    // Get other parameters that are needed to create the
    // option definition.
    std::string name = string_values_.getParam("name");
    uint32_t code = uint32_values_.getParam("code");
    std::string type = string_values_.getParam("type");
    bool array_type = boolean_values_.getParam("array");
    std::string encapsulates = string_values_.getParam("encapsulate");

    // Create option definition.
    OptionDefinitionPtr def;
    // We need to check if user has set encapsulated option space
    // name. If so, different constructor will be used.
    if (!encapsulates.empty()) {
        // Arrays can't be used together with sub-options.
        if (array_type) {
            isc_throw(DhcpConfigError, "option '" << space << "."
                      << "name" << "', comprising an array of data"
                      << " fields may not encapsulate any option space");

        } else if (encapsulates == space) {
            isc_throw(DhcpConfigError, "option must not encapsulate"
                      << " an option space it belongs to: '"
                      << space << "." << name << "' is set to"
                      << " encapsulate '" << space << "'");

        } else {
            def.reset(new OptionDefinition(name, code, type,
                        encapsulates.c_str()));
        }

    } else {
        def.reset(new OptionDefinition(name, code, type, array_type));

    }

    // The record-types field may carry a list of comma separated names
    // of data types that form a record.
    std::string record_types = string_values_.getParam("record-types");

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
                      << ex.what());
        }
    }

    // Check the option definition parameters are valid.
    try {
        def->validate();
    } catch (const isc::Exception& ex) {
        isc_throw(DhcpConfigError, "invalid option definition"
                  << " parameters: " << ex.what());
    }

    // Option definition has been created successfully.
    option_space_name_ = space;
    option_definition_ = def;
}

// ******************************** OptionDefListParser ************************

OptionDefListParser::OptionDefListParser(const std::string&, 
    OptionDefStorage *storage) :storage_(storage) {
    if (!storage_) {
        isc_throw(isc::dhcp::DhcpConfigError, "parser logic error:"
             << "storage may not be NULL");
    }
}

void OptionDefListParser::build(ConstElementPtr option_def_list) {
    // Clear existing items in the global storage.
    // We are going to replace all of them.
    storage_->clearItems();

    if (!option_def_list) {
        isc_throw(DhcpConfigError, "parser error: a pointer to a list of"
                  << " option definitions is NULL");
    }

    BOOST_FOREACH(ConstElementPtr option_def, option_def_list->listValue()) {
        boost::shared_ptr<OptionDefParser>
                parser(new OptionDefParser("single-option-def", storage_));
        parser->build(option_def);
        parser->commit();
    }
}

void OptionDefListParser::commit() {
    CfgMgr& cfg_mgr = CfgMgr::instance();
    cfg_mgr.deleteOptionDefs();

    // We need to move option definitions from the temporary
    // storage to the global storage.
    std::list<std::string> space_names =
    storage_->getOptionSpaceNames();

    BOOST_FOREACH(std::string space_name, space_names) {
        BOOST_FOREACH(OptionDefinitionPtr def,
                    *(storage_->getItems(space_name))) {
            // All option definitions should be initialized to non-NULL
            // values. The validation is expected to be made by the
            // OptionDefParser when creating an option definition.
            assert(def);
            cfg_mgr.addOptionDef(def, space_name);
        }
    }
}

};  // namespace dhcp
};  // namespace isc
