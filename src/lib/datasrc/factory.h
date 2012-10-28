// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DATA_SOURCE_FACTORY_H
#define DATA_SOURCE_FACTORY_H 1

#include <datasrc/data_source.h>
#include <datasrc/client.h>

#include <cc/data.h>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

namespace isc {
namespace datasrc {


/// \brief Raised if there is an error loading the datasource implementation
///        library
class DataSourceLibraryError : public DataSourceError {
public:
    DataSourceLibraryError(const char* file, size_t line, const char* what) :
        DataSourceError(file, line, what) {}
};

/// \brief Raised if there is an error reading a symbol from the datasource
///        implementation library
class DataSourceLibrarySymbolError : public DataSourceError {
public:
    DataSourceLibrarySymbolError(const char* file, size_t line,
                                 const char* what) :
        DataSourceError(file, line, what) {}
};

typedef DataSourceClient* ds_creator(isc::data::ConstElementPtr config,
                                     std::string& error);
typedef void ds_destructor(DataSourceClient* instance);

/// \brief Container class for dynamically loaded libraries
///
/// This class is used to dlopen() a library, provides access to dlsym(),
/// and cleans up the dlopened library when the instance of this class is
/// destroyed.
///
/// Its main function is to provide RAII-style access to dlopen'ed libraries.
///
/// \note Currently it is Datasource-backend specific. If we have need for this
///       in other places than for dynamically loading datasources, then, apart
///       from moving it to another location, we also need to make the
///       exceptions raised more general.
class LibraryContainer : boost::noncopyable {
public:
    /// \brief Constructor
    ///
    /// \param name The name of the library (.so) file. This file must be in
    ///             the library path.
    ///
    /// \exception DataSourceLibraryError If the library cannot be found or
    ///            cannot be loaded, or if name is an empty string.
    LibraryContainer(const std::string& name);

    /// \brief Destructor
    ///
    /// Cleans up the library by calling dlclose()
    ~LibraryContainer();

    /// \brief Retrieve a symbol
    ///
    /// This retrieves a symbol from the loaded library.
    ///
    /// \exception DataSourceLibrarySymbolError if the symbol cannot be found,
    ///            or if another error (as reported by dlerror() occurs.
    ///
    /// \param name The name of the symbol to retrieve
    /// \return A pointer to the symbol. This may be NULL, and if so, indicates
    ///         the symbol does indeed exist, but has the value NULL itself.
    ///         If the symbol does not exist, a DataSourceLibrarySymbolError is
    ///         raised.
    ///
    /// \note The argument is a const char* (and not a std::string like the
    ///       argument in the constructor). This argument is always a fixed
    ///       string in the code, while the other can be read from
    ///       configuration, and needs modification
    void* getSym(const char* name);
private:
    /// Pointer to the dynamically loaded library structure
    void *ds_lib_;
};


/// \brief Container for a specific instance of a dynamically loaded
///        DataSourceClient implementation
///
/// Given a datasource type and a type-specific set of configuration data,
/// the corresponding dynamic library is loaded (if it hadn't been already),
/// and an instance is created. This instance is stored within this structure,
/// and can be accessed through getInstance(). Upon destruction of this
/// container, the stored instance of the DataSourceClient is deleted with
/// the destructor function provided by the loaded library.
///
/// The 'type' is actually the name of the library, minus the '_ds.so' postfix
/// Datasource implementation libraries therefore have a fixed name, both for
/// easy recognition and to reduce potential mistakes.
/// For example, the sqlite3 implementation has the type 'sqlite3', and the
/// derived filename 'sqlite3_ds.so'
/// The value of type can be a specific loadable library; if it already ends
/// with '.so', the loader will not add '_ds.so'.
/// It may also be an absolute path; if it starts with '/', nothing is
/// prepended. If it does not, the loadable library will be taken from the
/// installation directory, see the value of
/// isc::datasrc::BACKEND_LIBRARY_PATH in datasrc_config.h for the exact path.
///
/// \note When 'B10_FROM_BUILD' is set in the environment, the build
///       directory is used instead of the install directory.
///
/// There are of course some demands to an implementation, not all of which
/// can be verified compile-time. It must provide a creator and destructor
/// functions. The creator function must return an instance of a subclass of
/// DataSourceClient. The prototypes of these functions are as follows:
/// \code
/// extern "C" DataSourceClient* createInstance(isc::data::ConstElementPtr cfg);
///
/// extern "C" void destroyInstance(isc::data::DataSourceClient* instance);
/// \endcode
///
/// \note This class is relatively recent, and its design is not yet fully
/// formed. We may want to split this into an abstract base container
/// class, and a derived 'dyload' class, and perhaps then add non-dynamic
/// derived classes as well. Currently, the class is actually derived in some
/// of the tests, which is rather unclean (as this class as written is really
/// intended to be used directly).
class DataSourceClientContainer : boost::noncopyable {
public:
    /// \brief Constructor
    ///
    /// \exception DataSourceLibraryError if there is an error loading the
    ///            backend library
    /// \exception DataSourceLibrarySymbolError if the library does not have
    ///            the needed symbols, or if there is an error reading them
    /// \exception DataError if the given config is not correct
    ///            for the given type, or if there was a problem during
    ///            initialization
    ///
    /// \param type The type of the datasource client. Based on the value of
    ///             type, a specific backend library is used, by appending the
    ///             string '_ds.so' to the given type, and loading that as the
    ///             implementation library
    /// \param config Type-specific configuration data, see the documentation
    ///               of the datasource backend type for information on what
    ///               configuration data to pass.
    DataSourceClientContainer(const std::string& type,
                              isc::data::ConstElementPtr config);

    /// \brief Destructor
    virtual ~DataSourceClientContainer();

    /// \brief Accessor to the instance
    ///
    /// \return Reference to the DataSourceClient instance contained in this
    ///         container.
    virtual DataSourceClient& getInstance() { return (*instance_); }

private:
    DataSourceClient* instance_;
    ds_destructor* destructor_;
    LibraryContainer ds_lib_;
};

///
/// Shared pointer type for datasource client containers
///
typedef boost::shared_ptr<DataSourceClientContainer>
    DataSourceClientContainerPtr;

} // end namespace datasrc
} // end namespace isc
#endif  // DATA_SOURCE_FACTORY_H
// Local Variables:
// mode: c++
// End:
