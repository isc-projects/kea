// Copyright (C) 2015-2023 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef CLIENT_CLASS_DEF_H
#define CLIENT_CLASS_DEF_H

#include <cc/cfg_to_element.h>
#include <cc/stamped_element.h>
#include <cc/user_context.h>
#include <dhcpsrv/cfg_option.h>
#include <dhcpsrv/cfg_option_def.h>
#include <eval/token.h>
#include <exceptions/exceptions.h>
#include <util/triplet.h>
#include <util/optional.h>

#include <string>
#include <unordered_map>
#include <list>
#include <vector>

/// @file client_class_def.h
///
/// @brief Defines classes for storing client class definitions
///
/// The file defines the class, ClientClassDef, which houses the
/// information for single client class such as the class name, the
/// logical expression used to identify members of the class, and options
/// that may be attributed to class members.
///
/// In addition it defines a container class, ClientClassDictionary, which
/// is houses class definitions keyed by class name.
///
namespace isc {
namespace dhcp {

/// @brief Error that occurs when an attempt is made to add a duplicate class
/// to a class dictionary.
class DuplicateClientClassDef : public isc::Exception {
public:
    DuplicateClientClassDef(const char* file, size_t line, const char* what)
        : isc::Exception(file, line, what) {}
};

/// @brief Embodies a single client class definition
class ClientClassDef : public data::UserContext,
                       public data::CfgToElement,
                       public data::StampedElement {
public:
    /// @brief Constructor
    ///
    /// @param name Name to assign to this class
    /// @param match_expr Expression the class will use to determine membership
    /// @param options Collection of options members should be given
    ClientClassDef(const std::string& name, const ExpressionPtr& match_expr,
                   const CfgOptionPtr& options = CfgOptionPtr());

    /// Copy constructor
    ClientClassDef(const ClientClassDef& rhs);

    /// @brief Destructor
    virtual ~ClientClassDef();

    /// @brief Fetches the class's name
    std::string getName() const;

    /// @brief Sets the class's name
    ///
    /// @param name the name to assign the class
    void setName(const std::string& name);

    /// @brief Fetches the class's match expression
    const ExpressionPtr& getMatchExpr() const;

    /// @brief Sets the class's match expression
    ///
    /// @param match_expr the expression to assign the class
    void setMatchExpr(const ExpressionPtr& match_expr);

    /// @brief Fetches the class's original match expression
    std::string getTest() const;

    /// @brief Sets the class's original match expression
    ///
    /// @param test the original expression to assign the class
    void setTest(const std::string& test);

    /// @brief Fetches the only if required flag
    bool getRequired() const;

    /// @brief Sets the only if required flag
    ///
    /// @param required the value of the only if required flag
    void setRequired(bool required);

    /// @brief Fetches the depend on known flag aka use host flag
    bool getDependOnKnown() const;

    /// @brief Sets the depend on known flag aka use host flag
    ///
    /// @param depend_on_known the value of the depend on known flag
    void setDependOnKnown(bool depend_on_known);

    /// @brief Fetches the class's option definitions
    const CfgOptionDefPtr& getCfgOptionDef() const;

    /// @brief Sets the class's option definition collection
    ///
    /// @param cfg_option_def the option definitions to assign the class
    void setCfgOptionDef(const CfgOptionDefPtr& cfg_option_def);

    /// @brief Fetches the class's option collection
    const CfgOptionPtr& getCfgOption() const;

    /// @brief Sets the class's option collection
    ///
    /// @param cfg_option the option collection to assign the class
    void setCfgOption(const CfgOptionPtr& cfg_option);

    /// @brief Checks direct dependency.
    ///
    /// @param name The client class name.
    ///
    /// @return true if the definition depends on the class name, false if not.
    bool dependOnClass(const std::string& name) const;

    /// @brief Compares two @c ClientClassDef objects for equality.
    ///
    /// @param other Other client class definition to compare to.
    ///
    /// @return true if objects are equal, false otherwise.
    bool equals(const ClientClassDef& other) const;

    /// @brief Equality operator.
    ///
    /// @param other Other client class definition to compare to.
    ///
    /// @return true if the definitions equal, false otherwise.
    bool operator==(const ClientClassDef& other) const {
        return (equals(other));
    }

    /// @brief Inequality operator.
    ///
    /// @param other Other client class definition to compare to.
    ///
    /// @return true if the definitions are not equal, false otherwise.
    bool operator!=(const ClientClassDef& other) const {
        return (!(equals(other)));
    }

    /// @brief Provides a convenient text representation of the class
    friend std::ostream& operator<<(std::ostream& os, const ClientClassDef& x);

    /// @brief returns next-server value
    /// @return next-server value
    const asiolink::IOAddress& getNextServer() const {
        return (next_server_);
    }

    /// @brief sets the next-server value
    ///
    /// @param addr the value to be set
    void setNextServer(const asiolink::IOAddress& addr) {
        next_server_ = addr;
    }

    /// @brief sets the server-name value
    ///
    /// @param sname the value to be set
    void setSname(const std::string& sname) {
        sname_ = sname;
    }

    /// @brief returns server-hostname value
    /// @return the vector that contains server-hostname (may be empty if not defined)
    const std::string& getSname() const {
        return (sname_);
    }

    /// @brief sets the boot-file-name value
    ///
    /// @param filename the value to be set
    void setFilename(const std::string& filename) {
        filename_ = filename;
    }

    /// @brief returns boot-file-name value
    /// @return the vector that contains boot-file-name (may be empty if not defined)
    const std::string& getFilename() const {
        return (filename_);
    }

    /// @brief Return valid-lifetime value
    ///
    /// @return a triplet containing the valid lifetime.
    util::Triplet<uint32_t> getValid() const {
        return (valid_);
    }

    /// @brief Sets new valid lifetime
    ///
    /// @param valid New valid lifetime in seconds.
    void setValid(const util::Triplet<uint32_t>& valid) {
        valid_ = valid;
    }

    /// @brief Return preferred-lifetime value
    ///
    /// @return a triplet containing the preferred lifetime.
    util::Triplet<uint32_t> getPreferred() const {
        return (preferred_);
    }

    /// @brief Sets new preferred lifetime
    ///
    /// @param preferred New valid lifetime in seconds.
    void setPreferred(const util::Triplet<uint32_t>& preferred) {
        preferred_ = preferred;
    }

    /// @brief Sets offer lifetime for the class.
    ///
    /// @param offer_lft the offer lifetime assigned to the class (may be empty if not defined)
    void setOfferLft(const util::Optional<uint32_t>& offer_lft) {
        offer_lft_ = offer_lft;
    }

    /// @brief Returns offer lifetime for the class.
    ///
    /// @return offer lifetime value
    util::Optional<uint32_t> getOfferLft() const {
        return (offer_lft_);
    }

    /// @brief Test method which checks if the packet belongs to the class
    ///
    /// If the packet belongs to the class, the class is added to the packet.
    ///
    /// @param pkt The packet checked if it belongs to the class.
    virtual void test(PktPtr pkt, const ExpressionPtr& expr_ptr);

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to unparsed configuration
    virtual isc::data::ElementPtr toElement() const;

private:
    /// @brief Unique text identifier by which this class is known.
    std::string name_;

    /// @brief The logical expression which determines membership in
    /// this class.
    ExpressionPtr match_expr_;

    /// @brief The original expression which determines membership in
    /// this class.
    std::string test_;

    /// @brief The only-if-required flag: when false (the default) membership
    /// is determined during classification so is available for instance for
    /// subnet selection. When true, membership is evaluated only when required
    /// and is usable only for option configuration.
    bool required_;

    /// @brief The depend on known aka use host flag: when false (the default),
    /// the required flag is false and the class has a match expression
    /// the expression is evaluated in the first pass. When true and the
    /// two other conditions stand the expression is evaluated later when
    /// the host reservation membership was determined.
    /// This flag is set to true during the match expression parsing if
    /// direct or indirect dependency on the builtin [UN]KNOWN classes is
    /// detected.
    bool depend_on_known_;

    /// @brief The option definition configuration for this class
    CfgOptionDefPtr cfg_option_def_;

    /// @brief The option data configuration for this class
    CfgOptionPtr cfg_option_;

    /// @brief Next server field
    /// If set by the next-server parameter, this value will be set
    /// in the siaddr field of the DHCPv4 packet.
    asiolink::IOAddress next_server_;

    /// @brief server-hostname
    /// If set by the server-hostname parameter, this value will be
    /// set in the sname field of the DHCPv4 packet.
    /// This can be up to 64 octets long.
    std::string sname_;

    /// @brief boot-file-name
    /// If set by the boot-file-name parameter, this value will be
    /// set in the file field of the DHCPv4 packet.
    /// This can be up to 128 octets long.
    std::string filename_;

    /// @brief a Triplet (min/default/max) holding allowed valid lifetime values
    util::Triplet<uint32_t> valid_;

    /// @brief a Triplet (min/default/max) holding allowed preferred lifetime values
    util::Triplet<uint32_t> preferred_;

    /// @brief offer lifetime for this class (V4 only).
    util::Optional<uint32_t> offer_lft_;
};

class TemplateClientClassDef : public ClientClassDef {
public:
    /// @brief Constructor
    ///
    /// @param name Name to assign to this class
    /// @param match_expr Expression the class will use to determine membership
    /// @param options Collection of options members should be given
    TemplateClientClassDef(const std::string& name, const ExpressionPtr& match_expr,
                           const CfgOptionPtr& options = CfgOptionPtr());

    /// @brief Test method which checks if the packet belongs to the class
    ///
    /// If the packet belongs to the class, the class is added to the packet.
    ///
    /// @param pkt The packet checked if it belongs to the class.
    virtual void test(PktPtr pkt, const ExpressionPtr& expr_ptr) override;

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to unparsed configuration
    virtual isc::data::ElementPtr toElement() const override;

    /// @brief This is a prefix added to the spawned class name
    ///
    /// If incoming packet is associated with the template class, the name of
    /// generated spawned class is prepended with this prefix.
    /// For example, a packet that associates with the template class "FOO" by
    /// evaluating the template class expression to BAR will cause the packet to
    /// be assigned to class SPAWN_FOO_BAR.
    static const std::string SPAWN_CLASS_PREFIX;
};

/// @brief a pointer to an ClientClassDef
typedef boost::shared_ptr<ClientClassDef> ClientClassDefPtr;

/// @brief Defines a map of ClientClassDef's, keyed by the class name.
typedef std::unordered_map<std::string, ClientClassDefPtr> ClientClassDefMap;

/// @brief Defines a pointer to a ClientClassDefMap
typedef boost::shared_ptr<ClientClassDefMap> ClientClassDefMapPtr;

/// @brief Defines a list of ClientClassDefPtr's, using insert order.
typedef std::vector<ClientClassDefPtr> ClientClassDefList;

/// @brief Defines a pointer to a ClientClassDefList
typedef boost::shared_ptr<ClientClassDefList> ClientClassDefListPtr;

/// @brief Maintains a list of ClientClassDef's
class ClientClassDictionary : public isc::data::CfgToElement {

public:
    /// @brief Constructor
    ClientClassDictionary();

    ClientClassDictionary(const ClientClassDictionary& rhs);

    /// @brief Destructor
    ~ClientClassDictionary();

    /// @brief Adds a new class to the list
    ///
    /// @param name Name to assign to this class
    /// @param match_expr Expression the class will use to determine membership
    /// @param test Original version of match_expr
    /// @param required Original value of the only if required flag
    /// @param depend_on_known Using host so will be evaluated later
    /// @param options Collection of options members should be given
    /// @param defs Option definitions (optional)
    /// @param user_context User context (optional)
    /// @param next_server next-server value for this class (optional)
    /// @param sname server-name value for this class (optional)
    /// @param filename boot-file-name value for this class (optional)
    /// @param valid valid-lifetime triplet (optional)
    /// @param preferred preferred-lifetime triplet (optional)
    ///
    /// @throw DuplicateClientClassDef if class already exists within the
    /// dictionary.  See @ref dhcp::ClientClassDef::ClientClassDef() for
    /// others.
    void addClass(const std::string& name, const ExpressionPtr& match_expr,
                  const std::string& test, bool required, bool depend_on_known,
                  const CfgOptionPtr& options,
                  CfgOptionDefPtr defs = CfgOptionDefPtr(),
                  isc::data::ConstElementPtr user_context = isc::data::ConstElementPtr(),
                  asiolink::IOAddress next_server = asiolink::IOAddress("0.0.0.0"),
                  const std::string& sname = std::string(),
                  const std::string& filename = std::string(),
                  const util::Triplet<uint32_t>& valid = util::Triplet<uint32_t>(),
                  const util::Triplet<uint32_t>& preferred = util::Triplet<uint32_t>(),
                  bool is_template = false,
                  const util::Optional<uint32_t>& offer_lft = util::Optional<uint32_t>());

    /// @brief Adds a new class to the list
    ///
    /// @param class_def pointer to class definition to add
    ///
    /// @throw DuplicateClientClassDef if class already exists within the
    /// dictionary, BadValue if the pointer is empty.
    void addClass(ClientClassDefPtr& class_def);

    /// @brief Fetches the class definition for a given class name
    ///
    /// @param name the name of the desired class
    ///
    /// @return ClientClassDefPtr to the desired class if found, or
    /// an empty pointer if not.
    ClientClassDefPtr findClass(const std::string& name) const;

    /// @brief Removes a given class definition from the dictionary
    ///
    /// Removes the class definition from the map if it exists, otherwise
    /// no harm, no foul.
    ///
    /// @param name the name of the class to remove
    void removeClass(const std::string& name);

    /// @brief Removes a client class by id.
    ///
    /// @param id class id.
    void removeClass(const uint64_t id);

    /// @brief Fetches the dictionary's list of classes
    ///
    /// @return ClientClassDefListPtr to the list of classes
    const ClientClassDefListPtr& getClasses() const;

    /// @brief Checks if the class dictionary is empty.
    ///
    /// @return true if there are no classes, false otherwise.
    bool empty() const;

    /// @brief Checks direct dependency.
    ///
    /// @param name The client class name.
    /// @param [out] dependent_class Reference to a variable where the
    /// name of the first class depending on the checked class is set.
    ///
    /// @return true if a definition depends on the class name, false if none.
    bool dependOnClass(const std::string& name, std::string& dependent_class) const;

    /// @brief Compares two @c ClientClassDictionary objects for equality.
    ///
    /// @param other Other client class definition to compare to.
    ///
    /// @return true if descriptors equal, false otherwise.
    bool equals(const ClientClassDictionary& other) const;

    /// @brief Iterates over the classes in the dictionary and ensures that
    /// that match expressions are initialized.
    ///
    /// @param family Class universe, e.g. AF_INET or AF_INET6.
    void initMatchExpr(uint16_t family);

    /// @brief Iterates over the classes in the dictionary and recreates
    /// the options.
    ///
    /// @param cfg_option_def set of option definitions to use.
    void createOptions(const CfgOptionDefPtr& cfg_option_def);

    /// @brief Equality operator.
    ///
    /// @param other Other client class dictionary to compare to.
    ///
    /// @return true if the dictionaries are equal, false otherwise.
    bool operator==(const ClientClassDictionary& other) const {
        return (equals(other));
    }

    /// @brief Inequality operator.
    ///
    /// @param other Other client class dictionary to compare to.
    ///
    /// @return true if the dictionaries are not equal, false otherwise.
    bool operator!=(const ClientClassDictionary& other) const {
        return (!equals(other));
    }

    /// @brief Copy assignment operator.
    ///
    /// @param rhs Client class dictionary to be copied from.
    /// @return Instance copy.
    ClientClassDictionary& operator=(const ClientClassDictionary& rhs);

    /// @brief Unparse a configuration object
    ///
    /// @return a pointer to unparsed configuration
    virtual isc::data::ElementPtr toElement() const;

private:

    /// @brief Map of the class definitions
    ClientClassDefMapPtr map_;

    /// @brief List of the class definitions
    ClientClassDefListPtr list_;
};

/// @brief Defines a pointer to a ClientClassDictionary
typedef boost::shared_ptr<ClientClassDictionary> ClientClassDictionaryPtr;

/// @brief List of built-in client class names.
/// i.e. ALL, KNOWN, UNKNOWN and BOOTP but not DROP.
extern std::list<std::string> builtinNames;

/// @brief List of built-in client class prefixes
/// i.e. VENDOR_CLASS_, HA_, AFTER_ and EXTERNAL_.
extern std::list<std::string> builtinPrefixes;

/// @brief Check if a client class name is builtin.
///
/// @param client_class A client class name to look for.
/// @return true if built-in, false if not.
bool isClientClassBuiltIn(const ClientClass& client_class);

/// @brief Check if a client class name is already defined,
/// i.e. is built-in or in the dictionary,
///
/// The reference to depend on known flag is set to true if the class
/// is KNOWN or UNKNOWN (direct dependency) or has this flag set
/// (indirect dependency).
///
/// @param class_dictionary A class dictionary where to look for.
/// @param depend_on_known A reference to depend on known flag.
/// @param client_class A client class name to look for.
/// @return true if defined or built-in, false if not.
bool isClientClassDefined(ClientClassDictionaryPtr& class_dictionary,
                          bool& depend_on_known,
                          const ClientClass& client_class);

} // namespace isc::dhcp
} // namespace isc

#endif // CLIENT_CLASS_DEF_H
