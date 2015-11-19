// Copyright (C) 2015 Internet Systems Consortium, Inc. ("ISC")
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

#ifndef CLIENT_CLASS_DEF_H
#define CLIENT_CLASS_DEF_H

#include <dhcpsrv/cfg_option.h>
#include <eval/token.h>
#include <exceptions/exceptions.h>

#include <string>

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
class ClientClassDef {
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

    /// @brief Fetches the class's option collection
    const CfgOptionPtr& getCfgOption() const;

    /// @brief Sets the class's option collection
    ///
    /// @param options the option collection to assign the class
    void setCfgOption(const CfgOptionPtr& cfg_option);

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

private:
    /// @brief Unique text identifier by which this class is known.
    std::string name_;

    /// @brief The logical expression which determines membership in
    /// this class.
    ExpressionPtr match_expr_;

    /// @brief The option data configuration for this class
    CfgOptionPtr cfg_option_;
};

/// @brief a pointer to an ClientClassDef
typedef boost::shared_ptr<ClientClassDef> ClientClassDefPtr;

/// @brief Defines a map of ClientClassDef's, keyed by the class name.
typedef std::map<std::string, ClientClassDefPtr> ClientClassDefMap;

/// @brief Defines a pointer to a ClientClassDefMap
typedef boost::shared_ptr<ClientClassDefMap> ClientClassDefMapPtr;

/// @brief Defines a pair for working with ClientClassMap
typedef std::pair<std::string, ClientClassDefPtr> ClientClassMapPair;

/// @brief Maintains a list of ClientClassDef's
class ClientClassDictionary {

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
    /// @param options Collection of options members should be given
    ///
    /// @throw DuplicateClientClassDef if class already exists within the
    /// dictionary.  See @ref dhcp::ClientClassDef::ClientClassDef() for
    /// others.
    void addClass(const std::string& name, const ExpressionPtr& match_expr,
                  const CfgOptionPtr& options);

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

    /// @brief Fetches the dictionary's map of classes
    ///
    /// @return ClientClassDefMapPtr to the map of classes
    const ClientClassDefMapPtr& getClasses() const;

    /// @brief Compares two @c ClientClassDictionary objects for equality.
    ///
    /// @param other Other client class definition to compare to.
    ///
    /// @return true if descriptors equal, false otherwise.
    bool equals(const ClientClassDictionary& other) const;

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

private:

    /// @brief Map of the class definitions
    ClientClassDefMapPtr classes_;

};

/// @brief Defines a pointer to a ClientClassDictionary
typedef boost::shared_ptr<ClientClassDictionary> ClientClassDictionaryPtr;

} // namespace isc::dhcp
} // namespace isc

#endif // CLIENT_CLASS_DEF_H
