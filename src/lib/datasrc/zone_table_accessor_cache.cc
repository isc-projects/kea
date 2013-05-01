// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#include <datasrc/zone_table_accessor_cache.h>
#include <datasrc/cache_config.h>

#include <exceptions/exceptions.h>

namespace isc {
namespace datasrc {
namespace internal {

namespace {
// This is a straightforward wrapper of CacheConfig::ConstZoneIterator to
// implement ZoneTableIterator interfaces.
class ZoneTableIteratorCache : public ZoneTableIterator {
public:
    ZoneTableIteratorCache(const CacheConfig& config) :
        it_(config.begin()),
        it_end_(config.end())
    {}

    virtual void nextImpl() {
        ++it_;
    }

    virtual ZoneSpec getCurrentImpl() const {
        return (ZoneSpec(0, it_->first)); // index is always 0 in this version.
    }

    virtual bool isLast() const {
        return (it_ == it_end_);
    }

private:
    CacheConfig::ConstZoneIterator it_;
    CacheConfig::ConstZoneIterator const it_end_;
};
}

ZoneTableAccessor::IteratorPtr
ZoneTableAccessorCache::getIterator() const {
    return (ZoneTableAccessor::IteratorPtr(
                new ZoneTableIteratorCache(config_)));
}

}
}
}
