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

#ifndef DHCP_CONFIG_PARSER_H
#define DHCP_CONFIG_PARSER_H

#include <exceptions/exceptions.h>
#include <cc/data.h>
#include <stdint.h>
#include <string>
#include <map>

namespace isc {
namespace dhcp {

/// An exception that is thrown if an error occurs while configuring
/// DHCP server.
class DhcpConfigError : public isc::Exception {
public:

    /// @brief constructor
    ///
    /// @param file name of the file, where exception occurred
    /// @param line line of the file, where exception occurred
    /// @param what text description of the issue that caused exception
    DhcpConfigError(const char* file, size_t line, const char* what)
        : isc::Exception(file, line, what) {}
};

/// @brief Forward declaration to DhcpConfigParser class.
///
/// It is only needed here to define types that are
/// based on this class before the class definition.
class DhcpConfigParser;

/// @brief a pointer to configuration parser
typedef boost::shared_ptr<DhcpConfigParser> ParserPtr;

/// @brief Collection of parsers.
///
/// This container is used to store pointer to parsers for a given scope.
typedef std::vector<ParserPtr> ParserCollection;

/// @brief Combination of parameter name and configuration contents
typedef std::pair<std::string, isc::data::ConstElementPtr> ConfigPair;

/// @brief Base abstract class for all DHCP parsers
///
/// Each instance of a class derived from this class parses one specific config
/// element. Sometimes elements are simple (e.g. a string) and sometimes quite
/// complex (e.g. a subnet). In such case, it is likely that a parser will
/// spawn child parsers to parse child elements in the configuration.
class DhcpConfigParser {
    ///
    /// @name Constructors and Destructor
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private to make it explicit that this is a
    /// pure base class.
    //@{
private:

    // Private constructor and assignment operator assures that nobody
    // will be able to copy or assign a parser. There are no defined
    // bodies for them.
    DhcpConfigParser(const DhcpConfigParser& source);
    DhcpConfigParser& operator=(const DhcpConfigParser& source);
protected:
    /// @brief The default constructor.
    ///
    /// This is intentionally defined as @c protected as this base class should
    /// never be instantiated (except as part of a derived class).
    DhcpConfigParser() {}
public:
    /// The destructor.
    virtual ~DhcpConfigParser() {}
    //@}

    /// @brief Prepare configuration value.
    ///
    /// This method parses the "value part" of the configuration identifier
    /// that corresponds to this derived class and prepares a new value to
    /// apply to the server.
    ///
    /// This method must validate the given value both in terms of syntax
    /// and semantics of the configuration, so that the server will be
    /// validly configured at the time of @c commit().  Note: the given
    /// configuration value is normally syntactically validated, but the
    /// @c build() implementation must also expect invalid input.  If it
    /// detects an error it may throw an exception of a derived class
    /// of @c isc::Exception.
    ///
    /// Preparing a configuration value will often require resource
    /// allocation.  If it fails, it may throw a corresponding standard
    /// exception.
    ///
    /// This method is not expected to be called more than once in the
    /// life of the object. Although multiple calls are not prohibited
    /// by the interface, the behavior is undefined.
    ///
    /// @param config_value The configuration value for the identifier
    /// corresponding to the derived class.
    virtual void build(isc::data::ConstElementPtr config_value) = 0;

    /// @brief Apply the prepared configuration value to the server.
    ///
    /// This method is expected to be exception free, and, as a consequence,
    /// it should normally not involve resource allocation.
    /// Typically it would simply perform exception free assignment or swap
    /// operation on the value prepared in @c build().
    /// In some cases, however, it may be very difficult to meet this
    /// condition in a realistic way, while the failure case should really
    /// be very rare.  In such a case it may throw, and, if the parser is
    /// called via @c configureDhcp4Server(), the caller will convert the
    /// exception as a fatal error.
    ///
    /// This method is expected to be called after @c build(), and only once.
    /// The result is undefined otherwise.
    virtual void commit() = 0;
};

/// @brief A template class that stores named elements of a given data type.
///
/// This template class is provides data value storage for configuration parameters
/// of a given data type.  The values are stored by parameter name and as instances 
/// of type "ValueType". 
///
/// @param ValueType is the data type of the elements to store.
template<typename ValueType>
class ValueStorage {
    public:
        /// @brief  Stores the the parameter and its value in the store.
        ///
        /// If the parameter does not exist in the store, then it will be added,
        /// otherwise its data value will be updated with the given value. 
        ///
        /// @param name is the name of the paramater to store.
        /// @param value is the data value to store.
        void setParam(const std::string name, const ValueType& value) {
            values_[name] = value;
        }

        /// @brief Returns the data value for the given parameter.
        ///
        /// Finds and returns the data value for the given parameter.
        /// @param name is the name of the parameter for which the data
        /// value is desired.
        ///
        /// @return The paramater's data value of type <ValueType>.
        /// @throw DhcpConfigError if the parameter is not found.
        ValueType getParam(const std::string& name) const {
            typename std::map<std::string, ValueType>::const_iterator param 
                = values_.find(name);

            if (param == values_.end()) {
                isc_throw(DhcpConfigError, "Missing parameter '"
                       << name << "'");
            }

            return (param->second);
        }

        /// @brief  Remove the parameter from the store.
        ///
        /// Deletes the entry for the given parameter from the store if it 
        /// exists. 
        ///
        /// @param name is the name of the paramater to delete.
        void delParam(const std::string& name) {
            values_.erase(name);
        }

        /// @brief Deletes all of the entries from the store.
        ///
        void clear() {
            values_.clear();
        }


    private:
        /// @brief An std::map of the data values, keyed by parameter names.
        std::map<std::string, ValueType> values_;
};


/// @brief a collection of elements that store uint32 values (e.g. renew-timer = 900)
typedef ValueStorage<uint32_t> Uint32Storage;

/// @brief a collection of elements that store string values
typedef ValueStorage<std::string> StringStorage;

/// @brief Storage for parsed boolean values.
typedef ValueStorage<bool> BooleanStorage;

}; // end of isc::dhcp namespace
}; // end of isc namespace

#endif // DHCP_CONFIG_PARSER_H

