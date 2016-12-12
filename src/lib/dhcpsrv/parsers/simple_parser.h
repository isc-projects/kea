#ifndef SIMPLE_PARSER_H
#define SIMPLE_PARSER_H

#include <cc/data.h>
#include <string>
#include <stdint.h>

namespace isc {
namespace dhcp {

/// This array defines a single entry of default values
struct SimpleDefault {
    SimpleDefault(const char* name, isc::data::Element::types type, const char* value)
        :name_(name), type_(type), value_(value) {}
    std::string name_;
    const isc::data::Element::types type_;
    const char* value_;
};

/// This specifies all default values in a given scope (e.g. a subnet)
typedef std::vector<SimpleDefault> SimpleDefaults;

/// This defines a list of all parameters that are derived (or inherited) between
/// contexts
typedef std::vector<std::string> ParamsList;


/// @brief A simple parser
///
/// This class is intended to be a simpler replacement for @ref DhcpConfigParser.
/// The simplification comes from several factors:
/// - no build/commit nonsense. There's a single step:
///   CfgStorage parse(ConstElementPtr json)
///   that converts JSON configuration into an object and returns it.
/// - almost no state kept. The only state kept in most cases is whether the
///   parsing is done in v4 or v6 context. This greatly simplifies the
///   parsers (no contexts, no child parsers list, no separate storage for
///   uint32, strings etc. In fact, there's so little state kept, that this
///   parser is mostly a collection of static methods.
/// - no optional parameters (all are mandatory). This simplifies the parser,
///   but introduces a new step before parsing where we insert the default
///   values into client configuration before parsing. This is actually a good
///   thing, because we now have a clear picture of the default parameters as
///   they're defined in a single place (the DhcpConfigParser had the defaults
///   spread out in multiple files in multiple directories).
class SimpleParser {
 public:

    /// @brief Derives (inherits) parameters from parent scope to a child
    ///
    /// This method derives parameters from the parent scope to the child,
    /// if there are no values specified in the child scope. For example,
    /// this method can be used to derive timers from global scope (e.g. for
    /// the whole DHCPv6 server) to a subnet scope. This method checks
    /// if the child scope doesn't have more specific values defined. If
    /// it doesn't, then the value from parent scope is copied over.
    ///
    /// @param parent scope to copy from (e.g. global)
    /// @param child scope to copy from (e.g. subnet)
    /// @param params names of the parameters to copy
    /// @return number of parameters copied
    static size_t deriveParams(isc::data::ConstElementPtr parent,
                               isc::data::ElementPtr child,
                               const ParamsList& params);
    /// @brief Derives (inherits) parameters from global to subnet scope
    ///
    /// This method derives global parameters into subnet scope if they're
    /// not defined there yet.
    ///
    /// @param global parameters will be inherited from here
    /// @param subnet parameters will be inserted here
    /// @return number of parameters copied
    static size_t
    inheritGlobalToSubnet(isc::data::ConstElementPtr global,
                          isc::data::ElementPtr subnet);

    /// @brief Sets the default values
    ///
    /// This method sets the default values for parameters that are not
    /// defined. The list of default values is specified by default_values.
    /// If not present, those will be inserted into the scope. If
    /// a parameter is already present, the default value will not
    /// be inserted.
    ///
    /// @param scope default values will be inserted here
    /// @param default_values list of default values
    /// @return number of parameters inserted
    static size_t setDefaults(isc::data::ElementPtr scope,
                              const SimpleDefaults& default_values);

    /// @brief Sets global defaults
    ///
    /// This method sets global defaults. Note it does not set the
    /// defaults for any scopes lower than global. See @ref setAllDefaults
    /// for that.
    ///
    /// @param global scope to be filled in with defaults.
    /// @param v6 is it v6 (true) or v4 (false) option?
    /// @return number of default values added
    static size_t setGlobalDefaults(isc::data::ElementPtr global, bool v6);

    /// @brief Sets option defaults for a single option
    ///
    /// This method sets default values for a single option.
    ///
    /// @param option an option data to be filled in with defaults.
    /// @param v6 is it v6 (true) or v4 (false) option?
    /// @return number of default values added
    static size_t setOptionDefaults(isc::data::ElementPtr option, bool v6);

    /// @brief Sets option defaults for the whole options list
    ///
    /// This method sets default values for a list of options.
    ///
    /// @param option_list an option data to be filled in with defaults.
    /// @param v6 is it v6 (true) or v4 (false) option?
    /// @return number of default values added
    static size_t setOptionListDefaults(isc::data::ElementPtr option_list, bool v6);

    /// @brief Sets option defaults for a single option definition
    ///
    /// This method sets default values for a single option definition.
    ///
    /// @param option_def an option defintion to be filled in with defaults.
    /// @param v6 is it v6 (true) or v4 (false) option defintion?
    /// @return number of default values added
    static size_t setOptionDefDefaults(isc::data::ElementPtr option_def, bool v6);

    /// @brief Sets option defaults for the whole option definitions list
    ///
    /// This method sets default values for a list of option definitions.
    ///
    /// @param option_def_list a list of option defintions to be filled in with defaults.
    /// @param v6 is it v6 (true) or v4 (false) option?
    /// @return number of default values added
    static size_t setOptionDefListDefaults(isc::data::ElementPtr option_def_list,
                                           bool v6);

    /// @brief Sets defaults for the whole configuration
    ///
    /// This method sets global, options and option definition defaults. Note
    /// it does set the defaults for scopes lower than global. If you want to
    /// set the global defaults only, see @ref setGlobalDefaults for that.
    ///
    /// @param global scope to be filled in with defaults.
    /// @param v6 true = v6, false = v4
    /// @return number of default values added
    static size_t setAllDefaults(isc::data::ElementPtr global, bool v6);

    /// @brief Utility method that returns position of an element
    ///
    /// It's mostly useful for logging.
    ///
    /// @param name position of that element will be returned
    /// @param parent parent element (optional)
    /// @return position of the element specified.
    const data::Element::Position&
    getPosition(const std::string& name, const data::ConstElementPtr parent =
                data::ConstElementPtr()) const;

    /// Destructor
    ///
    /// It's really simple, isn't it?
    virtual ~SimpleParser() {}

 protected:

    /// @brief Returns a string parameter from a scope
    ///
    /// Unconditionally returns a parameter. If the parameter is not there or
    /// is not of appropriate type, BadValue exception is thrown.
    ///
    /// @param scope specified parameter will be extracted from this scope
    /// @param name name of the parameter
    /// @return a string value of the parameter
    static std::string getString(isc::data::ConstElementPtr scope, const std::string& name);

    /// @brief Returns an integer parameter from a scope
    ///
    /// Unconditionally returns a parameter. If the parameter is not there or
    /// is not of appropriate type, BadValue exception is thrown.
    ///
    /// @param scope specified parameter will be extracted from this scope
    /// @param name name of the parameter
    /// @return an integer value of the parameter
    static int64_t getInteger(isc::data::ConstElementPtr scope, const std::string& name);

    /// @brief Returns a boolean parameter from a scope
    ///
    /// Unconditionally returns a parameter. If the parameter is not there or
    /// is not of appropriate type, BadValue exception is thrown.
    ///
    /// @param scope specified parameter will be extracted from this scope
    /// @param name name of the parameter
    /// @return a boolean value of the parameter
    static bool getBoolean(isc::data::ConstElementPtr scope, const std::string& name);
};

};
};

#endif
