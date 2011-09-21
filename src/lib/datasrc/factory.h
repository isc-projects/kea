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

#include <cc/data.h>

namespace isc {
namespace datasrc {

boost::shared_ptr<DataSourceClient>
createDataSourceClient(const std::string& type,
                       const isc::dns::RRClass& rrclass,
                       isc::data::ConstElementPtr config);

}
}
#endif  // DATA_SOURCE_FACTORY_H
// Local Variables:
// mode: c++
// End:
