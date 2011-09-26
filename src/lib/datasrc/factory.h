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

#ifndef __DATA_SOURCE_FACTORY_H
#define __DATA_SOURCE_FACTORY_H 1

//#include <boost/noncopyable.hpp>
//#include <boost/shared_ptr.hpp>

//#include <exceptions/exceptions.h>

#include <datasrc/data_source.h>
#include <datasrc/client.h>
#include <exceptions/exceptions.h>

#include <cc/data.h>

namespace isc {
namespace datasrc {


/// \brief Raised if there is an error loading the datasource implementation
///        library, or if that library misses a needed symbol
class DataSourceLibraryError : public DataSourceError {
public:
    DataSourceLibraryError(const char* file, size_t line, const char* what) :
        DataSourceError(file, line, what) {}
};

/// \brief Raised if the given config contains bad data
///
/// Depending on the datasource type, the configuration may differ (for
/// instance, the sqlite3 datasource needs a database file).
class DataSourceConfigError : public DataSourceError {
public:
    DataSourceConfigError(const char* file, size_t line, const char* what) :
        DataSourceError(file, line, what) {}
};

typedef DataSourceClient* ds_creator(isc::data::ConstElementPtr config);
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
class DLHolder {
public:
    /// \brief Constructor
    ///
    /// \param name The name of the library (.so) file. This file must be in
    ///             the library path.
    ///
    /// \exception DataSourceLibraryError If the library cannot be found or
    ///            cannot be loaded.
    DLHolder(const std::string& name);

    /// \brief Destructor
    ///
    /// Cleans up the library by calling dlclose()
    ~DLHolder();

    /// \brief Retrieve a symbol
    ///
    /// This retrieves a symbol from the loaded library.
    ///
    /// \exception DataSourceLibraryError if the symbol cannot be found, or if
    ///            another error (as reported by dlerror() occurs.
    ///
    /// \param name The name of the symbol to retrieve
    /// \return A pointer to the symbol
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
/// and can be accessed through getInstance().
///
/// The 'type' is actually the name of the library, minus the '_ds.so' postfix
/// Datasource implementation libraries therefore have a fixed name, both for
/// easy recognition and to reduce potential mistakes.
/// For example, the sqlite3 implementation has the type 'sqlite3', and the
/// derived filename 'sqlite3_ds.so'
///
/// There are of course some demands to an implementation, not all of which
/// can be verified compile-time. It must provide a creator and destructor
/// functions. The creator function must return an instance of a subclass of
/// DataSourceClient.
///
class DataSourceClientContainer {
public:
    /// \brief Constructor
    ///
    /// \exception DataSourceLibraryError if there is an error loading the
    ///            backend library
    /// \exception DataSourceConfigError if the given config is not correct
    ///            for the given type
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
    ~DataSourceClientContainer();

    /// \brief Accessor to the instance
    ///
    /// \return Reference to the DataSourceClient instance contained in this
    ///         container.
    DataSourceClient& getInstance() { return *instance_; }

private:
    DataSourceClient* instance_;
    ds_destructor* destructor_;
    DLHolder ds_lib_;
};

/// \brief Create a datasource instance
///
/// This function is a fixed generator for datasource instances of all types.
///
/// Currently, the different types are hardcoded in the implementation of this
/// function. However, we plan on making it more flexible, possibly through
/// th
///
/// \note This function returns a raw pointer. The caller is expected to
///       delete this pointer again. We don't return any specific smart
///       pointer for flexibility. However, we highly advice that the
///       return value of this function is directly put into a shared or
///       scoped pointer.
///
/// \exception DataSourceConfigError if the given configuration values are
///            bad for the given datasource type
DataSourceClient*
createDataSourceClient(const std::string& type,
                       isc::data::ConstElementPtr config);

}
}
#endif  // DATA_SOURCE_FACTORY_H
// Local Variables:
// mode: c++
// End:
