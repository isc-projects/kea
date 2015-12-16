// Copyright (C) 2010-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#ifndef RRPARAMREGISTRY_H
#define RRPARAMREGISTRY_H 1

#include <string>

#include <stdint.h>

#include <boost/shared_ptr.hpp>

#include <dns/exceptions.h>

#include <dns/rdata.h>

namespace isc {
namespace dns {

// forward declarations
struct RRParamRegistryImpl;

///
/// \brief A standard DNS module exception that is thrown if a new RR type is
/// being registered with a different type string.
///
class RRTypeExists : public isc::dns::Exception {
public:
    RRTypeExists(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

///
/// \brief A standard DNS module exception that is thrown if a new RR class is
/// being registered with a different type string.
///
class RRClassExists : public isc::dns::Exception {
public:
    RRClassExists(const char* file, size_t line, const char* what) :
        isc::dns::Exception(file, line, what) {}
};

namespace rdata {
/// \brief The \c AbstractRdataFactory class is an abstract base class to
/// encapsulate a set of Rdata factory methods in a polymorphic way.
///
/// An external developer who wants to introduce a new or experimental RR type
/// is expected to define a corresponding derived class of \c
/// AbstractRdataFactory and register it via \c RRParamRegistry.
///
/// Other users of this API normally do not have to care about this class
/// or its derived classes; this class is generally intended to be used
/// as an internal utility of the API implementation.
class AbstractRdataFactory {
    ///
    /// \name Constructors and Destructor
    ///
    //@{
protected:
    /// The default constructor
    ///
    /// This is intentionally defined as \c protected as this base class should
    /// never be instantiated (except as part of a derived class).
    AbstractRdataFactory() {}
public:
    /// The destructor.
    virtual ~AbstractRdataFactory() {};
    //@}

    ///
    /// \name Factory methods for polymorphic creation.
    ///
    //@{

    /// \brief Create RDATA from a string.
    ///
    /// This method creates from a string an \c Rdata object of specific class
    /// corresponding to the specific derived class of \c AbstractRdataFactory.
    ///
    /// \param rdata_str A string of textual representation of the \c Rdata.
    /// \return An \c RdataPtr object pointing to the created \c Rdata object.
    virtual RdataPtr create(const std::string& rdata_str) const = 0;

    /// \brief Create RDATA from wire-format data.
    ///
    /// This method creates from wire-format binary data an \c Rdata object
    /// of specific class corresponding to the specific derived class of
    /// \c AbstractRdataFactory.
    ///
    /// \param buffer A reference to an \c InputBuffer object storing the
    /// \c Rdata to parse.
    /// \param rdata_len The length in buffer of the \c Rdata.  In bytes.
    /// \return An \c RdataPtr object pointing to the created \c Rdata object.
    virtual RdataPtr create(isc::util::InputBuffer& buffer, size_t rdata_len) const = 0;

    /// \brief Create RDATA from another \c Rdata object of the same type.
    ///
    /// This method creates an \c Rdata object of specific class corresponding
    /// to the specific derived class of \c AbstractRdataFactory, copying the
    /// content of the given \c Rdata, \c source.
    ///
    /// \c source must be an object of the concrete derived class corresponding
    /// to the specific derived class of \c AbstractRdataFactory;
    /// otherwise, an exception of class \c std::bad_cast will be thrown.
    ///
    /// \param source A reference to an \c Rdata object whose content is to
    /// be copied to the created \c Rdata object.
    /// \return An \c RdataPtr object pointing to the created \c Rdata object.
    virtual RdataPtr create(const rdata::Rdata& source) const = 0;

    /// \brief Create RDATA using MasterLexer.
    ///
    /// This version of the method defines the entry point of factory
    /// of a specific RR type and class for \c RRParamRegistry::createRdata()
    /// that uses \c MasterLexer.  See its description for the expected
    /// behavior and meaning of the parameters.
    virtual RdataPtr create(MasterLexer& lexer, const Name* origin,
                            MasterLoader::Options options,
                            MasterLoaderCallbacks& callbacks) const = 0;
    //@}
};

///
/// The \c RdataFactoryPtr type is a pointer-like type, pointing to an
/// object of some concrete derived class of \c AbstractRdataFactory.
///
typedef boost::shared_ptr<AbstractRdataFactory> RdataFactoryPtr;
} // end of namespace rdata

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
/// In the current implementation, access to the singleton \c RRParamRegistry
/// object is not thread safe.
/// The application should ensure that multiple threads don't race in the
/// first invocation of \c getRegistry(), and, if the registry needs to
/// be changed dynamically, read and write operations are performed
/// exclusively.
/// Since this class should be static in common usage this restriction would
/// be acceptable in practice.
/// In the future, we may extend the implementation so that multiple threads can
/// get access to the registry fully concurrently without any restriction.
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
    ///
    /// \brief Return the singleton instance of \c RRParamRegistry.
    ///
    /// This method is a unified access point to the singleton instance of
    /// the RR parameter registry (\c RRParamRegistry).
    /// On first invocation it internally constructs an instance of the
    /// \c RRParamRegistry class and returns a reference to it.
    /// This is a static object inside this method and will remain valid
    /// throughout the rest of the application lifetime.
    /// On subsequent calls this method simply returns a reference to the
    /// singleton object.
    ///
    /// If resource allocation fails in the first invocation,
    /// a corresponding standard exception will be thrown.
    /// This method never fails otherwise.  In particular, this method
    /// doesn't throw an exception once the singleton instance is constructed.
    ///
    /// \return A reference to the singleton instance of \c RRParamRegistry.
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
    /// codes, this method behaves in the same way as \c addType() and
    /// \c addClass().  That is, it ignores any overriding attempt as
    /// long as the mapping is the same; otherwise the corresponding exception
    /// will be thrown.
    ///
    /// This method provides the strong exception guarantee: unless an
    /// exception is thrown the entire specified set of parameters must be
    /// stored in the registry; if this method throws an exception the
    /// registry will remain in the state before this method is called.
    ///
    /// \param type_string The textual representation of the RR type.
    /// \param type_code The integer code of the RR type.
    /// \param class_string The textual representation of the RR class.
    /// \param class_code The integer code of the RR class.
    /// \param rdata_factory An \c RdataFactoryPtr object pointing to a
    /// concrete RDATA factory.
    void add(const std::string& type_string, uint16_t type_code,
             const std::string& class_string, uint16_t class_code,
             rdata::RdataFactoryPtr rdata_factory);

    /// \brief Add a set of parameters for a class-independent RR type.
    ///
    /// This method behaves as exactly same as the other \c add method except
    /// that it handles class-independent types (such as NS, CNAME, or SOA).
    ///
    /// \param type_string The textual representation of the RR type.
    /// \param type_code The integer code of the RR type.
    /// \param rdata_factory An \c RdataFactoryPtr object pointing to a
    /// concrete RDATA factory.
    void add(const std::string& type_string, uint16_t type_code,
             rdata::RdataFactoryPtr rdata_factory);

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
    /// This method never throws an exception.
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
    /// \return \c true if a new mapping is added to the repository; \c false
    /// if the same mapping is already registered.
    bool addClass(const std::string& class_string, uint16_t class_code);

    /// \brief Remove mappings between RR class code and textual representation
    /// for a given class.
    ///
    /// This method can safely be called whether or not the specified mappings
    /// exist in the registry.  If not, this method simply ignores the attempt
    /// and returns \c false.
    ///
    /// This method never throws an exception.
    ///
    /// \param class_code The integer code of the RR class.
    /// \return \c true if mappings for the specified RR type exists and is
    /// removed; \c false if no such mapping is in the registry.
    bool removeClass(uint16_t class_code);

    /// \brief Remove registered RDATA factory for the given pair of \c RRType
    /// and \c RRClass.
    ///
    /// This method can safely be called whether or not the specified factory
    /// object exist in the registry.  If not, this method simply ignores the
    /// attempt and returns \c false.
    ///
    /// This method never throws an exception.
    ///
    /// \param rrtype An \c RRType object specifying the type/class pair.
    /// \param rrclass An \c RRClass object specifying the type/class pair.
    /// \return \c true if a factory object for the specified RR type/class
    /// pair exists and is removed; \c false if no such object is in the
    /// registry.
    bool removeRdataFactory(const RRType& rrtype, const RRClass& rrclass);

    /// \brief Remove registered RDATA factory for the given pair of \c RRType
    /// and \c RRClass.
    ///
    /// This method can safely be called whether or not the specified factory
    /// object exist in the registry.  If not, this method simply ignores the
    /// attempt and returns \c false.
    ///
    /// This method never throws an exception.
    ///
    /// \param rrtype An \c RRType object specifying the type/class pair.
    /// \return \c true if a factory object for the specified RR type/class
    /// pair exists and is removed; \c false if no such object is in the
    /// registry.
    bool removeRdataFactory(const RRType& rrtype);
    //@}

    ///
    /// \name Parameter Conversion Methods
    ///
    //@{
    /// \brief Convert a textual representation of an RR type to the
    /// corresponding 16-bit integer code.
    ///
    /// This method searches the \c RRParamRegistry for the mapping from
    /// the given textual representation of RR type to the corresponding
    /// integer code. If a mapping is found, it returns true with the
    /// associated type code in \c type_code; otherwise, if the given
    /// string is in the form of "TYPEnnnn", it returns true with the
    /// corresponding number as the type code in \c type_code;
    /// otherwise, it returns false and \c type_code is untouched.
    ///
    /// It returns \c false and avoids throwing an exception in the case
    /// of an error to avoid the exception overhead in some situations.
    ///
    /// \param type_string The textual representation of the RR type.
    /// \param type_code Returns the RR type code in this argument.
    /// \return true if conversion is successful, false otherwise.
    bool textToTypeCode(const std::string& type_string,
                        uint16_t& type_code) const;

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
    /// This method searches the \c RRParamRegistry for the mapping from
    /// the given textual representation of RR class to the
    /// corresponding integer code.  If a mapping is found, it returns
    /// true with the associated class code in \c class_code; otherwise,
    /// if the given string is in the form of "CLASSnnnn", it returns
    /// true with the corresponding number as the class code in
    /// \c class_code; otherwise, it returns false and \c class_code is
    /// untouched.
    ///
    /// It returns \c false and avoids throwing an exception in the case
    /// of an error to avoid the exception overhead in some situations.
    ///
    /// \param class_string The textual representation of the RR class.
    /// \param class_code Returns the RR class code in this argument.
    /// \return true if conversion is successful, false otherwise.
    bool textToClassCode(const std::string& class_string,
                         uint16_t& class_code) const;

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

    ///
    /// \name RDATA Factories
    ///
    /// This set of methods provide a unified interface to create an
    /// \c rdata::Rdata object in a parameterized polymorphic way,
    /// that is, these methods take a pair of \c RRType and \c RRClass
    /// objects and data specific to that pair, and create an object of
    /// the corresponding concrete derived class of \c rdata::Rdata.
    ///
    /// These methods first search the \c RRParamRegistry for a factory
    /// method (a member of a concrete derived class of
    /// \c AbstractRdataFactory) for the given RR type and class pair.
    /// If the search fails, they then search for a factory method for
    /// the given type ignoring the class, in case a RRClass independent
    /// factory method is registered.
    /// If it still fails, these methods assume the RDATA is of an "unknown"
    /// type, and creates a new object by calling a constructor of the
    /// \c rdata::generic::Generic class.
    ///
    //@{
    /// \brief Create RDATA of a given pair of RR type and class from a string.
    ///
    /// This method creates from a string an \c Rdata object of the given pair
    /// of RR type and class.
    ///
    /// \param rrtype An \c RRType object specifying the type/class pair.
    /// \param rrclass An \c RRClass object specifying the type/class pair.
    /// \param rdata_string A string of textual representation of the \c Rdata.
    /// \return An \c rdata::RdataPtr object pointing to the created \c Rdata
    /// object.
    rdata::RdataPtr createRdata(const RRType& rrtype, const RRClass& rrclass,
                                const std::string& rdata_string);
    /// \brief Create RDATA of a given pair of RR type and class from
    /// wire-format data.
    ///
    /// This method creates from wire-format binary data an \c Rdata object
    /// of the given pair of RR type and class.
    ///
    /// \param rrtype An \c RRType object specifying the type/class pair.
    /// \param rrclass An \c RRClass object specifying the type/class pair.
    /// \param buffer A reference to an \c InputBuffer object storing the
    /// \c Rdata to parse.
    /// \param len The length in buffer of the \c Rdata.  In bytes.
    /// \return An \c rdata::RdataPtr object pointing to the created \c Rdata
    /// object.
    rdata::RdataPtr createRdata(const RRType& rrtype, const RRClass& rrclass,
                                isc::util::InputBuffer& buffer, size_t len);
    /// \brief Create RDATA of a given pair of RR type and class, copying
    /// of another RDATA of same kind.
    ///
    /// This method creates an \c Rdata object of the given pair of
    /// RR type and class, copying the  content of the given \c Rdata,
    /// \c source.
    ///
    /// \c source must be an object of the concrete derived class of
    /// \c rdata::Rdata for the given pair of RR type and class;
    /// otherwise, an exception of class \c std::bad_cast will be thrown.
    /// In case the \c RRParamRegistry doesn't have a factory method for
    /// the given pair and it is assumed to be of an "unknown" type,
    /// \c source must reference an object of class
    /// \c rdata::generic::Generic; otherwise, an exception of class
    /// \c std::bad_cast will be thrown.
    ///
    /// \param rrtype An \c RRType object specifying the type/class pair.
    /// \param rrclass An \c RRClass object specifying the type/class pair.
    /// \param source A reference to an \c rdata::Rdata object whose content
    /// is to be copied to the created \c rdata::Rdata object.
    /// \return An \c rdata::RdataPtr object pointing to the created
    /// \c rdata::Rdata object.
    rdata::RdataPtr createRdata(const RRType& rrtype, const RRClass& rrclass,
                                const rdata::Rdata& source);

    /// \brief Create RDATA using MasterLexer
    ///
    /// This method is expected to be used as the underlying implementation
    /// of the same signature of \c rdata::createRdata().  One main
    /// difference is that this method is only responsible for constructing
    /// the Rdata; it doesn't update the lexer to reach the end of line or
    /// file or doesn't care about whether there's an extra (garbage) token
    /// after the textual RDATA representation.  Another difference is that
    /// this method can throw on error and never returns a NULL pointer.
    ///
    /// For other details and parameters, see the description of
    /// \c rdata::createRdata().
    rdata::RdataPtr createRdata(const RRType& rrtype, const RRClass& rrclass,
                                MasterLexer& lexer, const Name* origin,
                                MasterLoader::Options options,
                                MasterLoaderCallbacks& callbacks);
    //@}

private:
    RRParamRegistryImpl* impl_;
};

}
}
#endif  // RRPARAMREGISTRY_H

// Local Variables:
// mode: c++
// End:
