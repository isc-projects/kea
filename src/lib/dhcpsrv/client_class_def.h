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

#include <dhcp/option.h>
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
/// In addition it defines a continer class, ClientClassDictionary, which
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
                const OptionCollectionPtr& options = OptionCollectionPtr());

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
    const OptionCollectionPtr& getOptions() const;

    /// @brief Sets the class's option collection
    ///
    /// @param options the option collection to assign the class
    void setOptions(const OptionCollectionPtr& options);

    /// @brief Fetches an option from the class's collection by code
    ///
    /// @param option_code Option code value of the desired option
    /// @return A pointer to the option if found, otherwise an
    /// empty pointer
    OptionPtr findOption(uint16_t option_code) const;

    /// @brief Provides a convenient text representation of the class
    friend  std::ostream& operator<<(std::ostream& os, const ClientClassDef& x);

  private:
    /// @brief Unique text identifier by which this class is known.
    std::string name_;

    /// @brief The logical expression which deteremines membership in
    /// this class.
    ExpressionPtr match_expr_;

    /// @brief The collection of options members should be given
    /// Currently this is a multimap, not sure we need/want that complexity
    OptionCollectionPtr options_;
};

/// @brief a pointer to an ClientClassDef
typedef boost::shared_ptr<ClientClassDef> ClientClassDefPtr;

/// @brief Defines a map of ClientClassDefes, keyed by the class name.
typedef std::map<std::string,ClientClassDefPtr> ClientClassDefMap;

/// @brief Defines a pointer to a ClientClassDictionary
typedef boost::shared_ptr<ClientClassDefMap> ClientClassDefMapPtr;

/// @brief Maintains a list of ClientClassDefes
class ClientClassDictionary {

  public:
    /// @brief Constructor
    ClientClassDictionary();

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
                  const OptionCollectionPtr& options);

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
    /// Removes the class defintion from the map if it exists, otherwise
    /// no harm, no foul.
    ///
    /// @param name the name of the class to remove
    void removeClass(const std::string& name);

    /// @brief Fetches the dictionary's map of classes
    ///
    /// @return ClientClassDefMapPtr to the map of classes
    const ClientClassDefMapPtr& getClasses() const;

  private:

    /// @brief Map of the class definitions
    ClientClassDefMapPtr classes_;

};

/// @brief Defines a pointer to a ClientClassDictionary
typedef boost::shared_ptr<ClientClassDictionary> ClientClassDictionaryPtr;

} // namespace isc::dhcp
} // namespace isc

#endif // CLIENT_CLASS_DEF_H
