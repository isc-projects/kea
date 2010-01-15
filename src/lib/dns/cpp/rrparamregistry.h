// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

// $Id$

#ifndef __RRPARAMREGISTRY_H
#define __RRPARAMREGISTRY_H 1

#include <string>

#include <stdint.h>

#include "exceptions.h"

namespace isc {
namespace dns {

// forward declarations
struct RRParamRegistryImpl;

///
/// \brief A standard DNS module exception that is thrown if a new RR class is
/// being registered with a different type string.
///
class RRClassExist : public Exception {
public:
    RRClassExist(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if a new RR type is
/// being registered with a different type string.
///
class RRTypeExist : public Exception {
public:
    RRTypeExist(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

///
/// The \c RRParamRegistry class represents a registry of parameters to
/// manipulate DNS resource records (RRs).
///
/// A \c RRParamRegistry class object stores a mapping between RR types or
/// classes and their textual representations.  It will also have knowledge of
/// how to create an RDATA object for a specific pair of RR type and class
/// (not implemented in this version).
///
/// Normal applications that only handle standard DNS protocols won't have to
/// care about this class.  This is mostly an internal class to the DNS library
/// to manage standard parameters.  Some advanced applications may still need
/// to use this class explicitly.  For example, if an application wants to
/// define and use an experimental non-standard RR type, it may want to register
/// related protocol parameters for its convenience.  This class is designed to
/// allow such usage without modifying the library source code or rebuilding
/// the library.
///
/// It is assumed that at most one instance of this class can exist so that
/// the application uses the consistent set of registered parameters.  To ensure
/// this, this class is designed and implemented as a "singleton class": the
/// constructor is intentionally private, and applications must get access to
/// the single instance via the \c getRegistry() static member function.
///
/// Note: the implementation of this class is incomplete: we should at least
/// add RDATA related parameters.  This will be done in a near future version,
/// at which point some of method signatures will be changed.
class RRParamRegistry {
    ///
    /// \name Constructors and Destructor
    ///
    /// These are intentionally hidden (see the class description).
    //@{
private:
    RRParamRegistry();
    RRParamRegistry(const RRParamRegistry& orig);
    ~RRParamRegistry();
    //@}
public:
    static RRParamRegistry& getRegistry();

    ///
    /// \name Registry Update Methods
    ///
    //@{
    ///
    /// \brief Add a set of parameters for a pair of RR type and class.
    ///
    /// This method adds to the registry a specified set of RR parameters,
    /// including mappings between type/class codes and their textual
    /// representations.
    ///
    /// Regarding the mappings between textual representations and integer
    /// codes, this methods behaves in the same way as \c addType() and
    /// \c addClass().  That is, it ignores any overriding attempt as
    /// long as the mapping is the same; otherwise the corresponding exception
    /// will be thrown.
    ///
    /// This method provides the strong exception guarantee: unless an
    /// exception is thrown the entire specified set of parameters must be
    /// stored in the registry; if this method throws an exception the
    /// registry will remain in the state before this method is called.
    ///
    /// Note: this method will be extended to support more parameters in a
    /// near future version.
    ///
    /// \param type_string The textual representation of the RR type.
    /// \param type_code The integer code of the RR type.
    /// \param class_string The textual representation of the RR class.
    /// \param class_code The integer code of the RR class.
    void add(const std::string& type_string, uint16_t type_code,
             const std::string& class_string, uint16_t class_code);

    /// \brief Add mappings between RR type code and textual representation.
    ///
    /// This method adds a mapping from the type code of an RR to its textual
    /// representation and the reverse mapping in the registry.
    ///
    /// If the given RR type is already registered with the same textual
    /// representation, this method simply ignores the duplicate mapping;
    /// if the given type is registered and a new pair with a different
    /// textual representation is being added,an exception of class
    /// \c RRTypeExist will be thrown.
    /// To replace an existing mapping with a different textual representation,
    /// the existing one must be removed by the \c removeType() method
    /// beforehand.
    ///
    /// In addition, if resource allocation for the new mapping entries fails,
    /// a corresponding standard exception will be thrown.
    ///
    /// This method provides the strong exception guarantee: unless an exception
    /// is thrown the specified mappings must be stored in the registry
    /// (although it may be an already existing one) on completion of the
    /// method; if this method throws an exception the registry will remain
    /// in the state before this method is called.
    ///
    /// \param type_string The textual representation of the RR type.
    /// \param type_code The integer code of the RR type.
    /// \return \c true if a new mapping is added to the repository; \c false
    /// if the same mapping is already registered.
    bool addType(const std::string& type_string, uint16_t type_code);

    /// \brief Remove mappings between RR type code and textual representation
    /// for a given type.
    ///
    /// This method can safely be called whether or not the specified mappings
    /// exist in the registry.  If not, this method simply ignores the attempt
    /// and returns \c false.
    ///
    /// This method never throw an exception.
    ///
    /// \param type_code The integer code of the RR type.
    /// \return \c true if mappings for the specified RR type exists and is
    /// removed; \c false if no such mapping is in the registry.
    bool removeType(uint16_t type_code);

    /// \brief Add mappings between RR class code and textual representation.
    ///
    /// This method adds a mapping from the class code of an RR to its textual
    /// representation and the reverse mapping in the registry.
    ///
    /// If the given RR class is already registered with the same textual
    /// representation, this method simply ignores the duplicate mapping;
    /// if the given class is registered and a new pair with a different
    /// textual representation is being added,an exception of class
    /// \c RRClassExist will be thrown.
    /// To replace an existing mapping with a different textual representation,
    /// the existing one must be removed by the \c removeClass() method
    /// beforehand.
    ///
    /// In addition, if resource allocation for the new mapping entries fails,
    /// a corresponding standard exception will be thrown.
    ///
    /// This method provides the strong exception guarantee: unless an exception
    /// is thrown the specified mappings must be stored in the registry
    /// (although it may be an already existing one) on completion of the
    /// method; if this method throws an exception the registry will remain
    /// in the state before this method is called.
    ///
    /// \param class_string The textual representation of the RR class.
    /// \param class_code The integer code of the RR class.
    /// \return
    bool addClass(const std::string& class_string, uint16_t class_code);

    /// \brief Remove mappings between RR class code and textual representation
    /// for a given class.
    ///
    /// This method can safely be called whether or not the specified mappings
    /// exist in the registry.  If not, this method simply ignores the attempt
    /// and returns \c false.
    ///
    /// This method never throw an exception.
    ///
    /// \param class_code The integer code of the RR class.
    /// \return
    bool removeClass(uint16_t class_code);
    //@}

    ///
    /// \name Parameter Conversion Methods
    ///
    //@{
    /// \brief Convert a textual representation of an RR type to the
    /// corresponding 16-bit integer code.
    ///
    /// This method searches the \c RRParamRegistry for the mapping from the
    /// given textual representation of RR type to the corresponding integer
    /// code.  If a mapping is found, it returns the associated type code;
    /// otherwise, if the given string is in the form of "TYPEnnnn", it returns
    /// the corresponding number as the type code; otherwise, it throws an
    /// exception of class \c InvalidRRType.
    ///
    /// \param type_string The textual representation of the RR type.
    /// \return The RR type code for \c type_string.
    uint16_t textToTypeCode(const std::string& type_string) const;

    /// \brief Convert type code into its textual representation.
    ///
    /// This method searches the \c RRParamRegistry for the mapping from the
    /// given RR type code to its textual representation.
    /// If a mapping is found, it returns (a copy of) the associated string;
    /// otherwise, this method creates a new string in the form of "TYPEnnnn"
    /// where "nnnn" is the decimal representation of the type code, and
    /// returns the new string.
    ///
    /// If resource allocation for the returned string fails,
    /// a corresponding standard exception will be thrown.
    /// This method never fails otherwise.
    ///
    /// \param type_code The integer code of the RR type.
    /// \return A textual representation of the RR type for code \c type_code.
    std::string codeToTypeText(uint16_t type_code) const;

    /// \brief Convert a textual representation of an RR class to the
    /// corresponding 16-bit integer code.
    ///
    /// This method searches the \c RRParamRegistry for the mapping from the
    /// given textual representation of RR class to the corresponding integer
    /// code.  If a mapping is found, it returns the associated class code;
    /// otherwise, if the given string is in the form of "CLASSnnnn", it returns
    /// the corresponding number as the class code; otherwise, it throws an
    /// exception of class \c InvalidRRClass.
    ///
    /// \param class_string The textual representation of the RR class.
    /// \return The RR class code for \c class_string.
    uint16_t textToClassCode(const std::string& class_string) const;

    /// \brief Convert class code into its textual representation.
    ///
    /// This method searches the \c RRParamRegistry for the mapping from the
    /// given RR class code to its textual representation.
    /// If a mapping is found, it returns (a copy of) the associated string;
    /// otherwise, this method creates a new string in the form of "CLASSnnnn"
    /// where "nnnn" is the decimal representation of the class code, and
    /// returns the new string.
    ///
    /// If resource allocation for the returned string fails,
    /// a corresponding standard exception will be thrown.
    /// This method never fails otherwise.
    ///
    /// \param class_code The integer code of the RR class.
    /// \return A textual representation of the RR class for code \c class_code.
    std::string codeToClassText(uint16_t class_code) const;
    //@}

private:
    RRParamRegistryImpl* impl_;
};

}
}
#endif  // __RRPARAMREGISTRY_H

// Local Variables: 
// mode: c++
// End: 
