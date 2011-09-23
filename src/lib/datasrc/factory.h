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

#include <datasrc/client.h>
#include <exceptions/exceptions.h>

#include <cc/data.h>

namespace isc {
namespace datasrc {

typedef DataSourceClient* ds_creator(isc::data::ConstElementPtr config);
typedef void ds_destructor(DataSourceClient* instance);

class DLHolder {
public:
    DLHolder(const std::string& name);
    ~DLHolder();
    void* getSym(const char* name);
private:
    const std::string ds_name_;
    void *ds_lib_;
};

class DataSourceClientContainer {
public:
    DataSourceClientContainer(const std::string& type,
                              isc::data::ConstElementPtr config);
    ~DataSourceClientContainer();
private:
    DataSourceClient* instance_;
    ds_destructor* destructor_;
    DLHolder ds_lib_;
};


/// \brief Raised if the given config contains bad data
///
/// Depending on the datasource type, the configuration may differ (for
/// instance, the sqlite3 datasource needs a database file).
class DataSourceConfigError : public isc::Exception {
public:
    DataSourceConfigError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
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
