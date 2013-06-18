// Copyright (C) 2012  Internet Systems Consortium, Inc. ("ISC")
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

#include <datasrc/memory/zone_writer.h>
#include <datasrc/memory/zone_data.h>
#include <datasrc/memory/zone_table_segment.h>
#include <datasrc/memory/segment_object_holder.h>

#include <boost/scoped_ptr.hpp>

#include <dns/rrclass.h>

#include <datasrc/exceptions.h>

#include <memory>

using std::auto_ptr;

namespace isc {
namespace datasrc {
namespace memory {

ZoneTableSegment&
checkZoneTableSegment(ZoneTableSegment& segment) {
    if (!segment.isWritable()) {
        isc_throw(isc::InvalidOperation,
                  "Attempt to construct ZoneWriter for a read-only segment");
    }
    return (segment);
}

struct ZoneWriter::Impl {
    Impl(ZoneTableSegment& segment, const LoadAction& load_action,
         const dns::Name& origin, const dns::RRClass& rrclass,
         bool throw_on_load_error) :
        // We validate segment first so we can use it to initialize
        // data_holder_ safely.
        segment_(checkZoneTableSegment(segment)),
        load_action_(load_action),
        origin_(origin),
        rrclass_(rrclass),
        state_(ZW_UNUSED),
        catch_load_error_(throw_on_load_error)
    {
        while (true) {
            try {
                data_holder_.reset(
                    new ZoneDataHolder(segment.getMemorySegment(), rrclass_));
                break;
            } catch (const isc::util::MemorySegmentGrown&) {}
        }
    }

    ZoneTableSegment& segment_;
    const LoadAction load_action_;
    const dns::Name origin_;
    const dns::RRClass rrclass_;
    enum State {
        ZW_UNUSED,
        ZW_LOADED,
        ZW_INSTALLED,
        ZW_CLEANED
    };
    State state_;
    const bool catch_load_error_;
    typedef detail::SegmentObjectHolder<ZoneData, dns::RRClass> ZoneDataHolder;
    boost::scoped_ptr<ZoneDataHolder> data_holder_;
};

ZoneWriter::ZoneWriter(ZoneTableSegment& segment,
                       const LoadAction& load_action,
                       const dns::Name& origin,
                       const dns::RRClass& rrclass,
                       bool throw_on_load_error) :
    impl_(new Impl(segment, load_action, origin, rrclass, throw_on_load_error))
{
}

ZoneWriter::~ZoneWriter() {
    // Clean up everything there might be left if someone forgot, just
    // in case.
    cleanup();
    delete impl_;
}

void
ZoneWriter::load(std::string* error_msg) {
    if (impl_->state_ != Impl::ZW_UNUSED) {
        isc_throw(isc::InvalidOperation, "Trying to load twice");
    }

    try {
        ZoneData* zone_data =
            impl_->load_action_(impl_->segment_.getMemorySegment());

        if (!zone_data) {
            // Bug inside impl_->load_action_.
            isc_throw(isc::InvalidOperation,
                      "No data returned from load action");
        }

        impl_->data_holder_->set(zone_data);

    } catch (const ZoneLoaderException& ex) {
        if (!impl_->catch_load_error_) {
            throw;
        }
        if (error_msg) {
            *error_msg = ex.what();
        }
    }

    impl_->state_ = Impl::ZW_LOADED;
}

void
ZoneWriter::install() {
    if (impl_->state_ != Impl::ZW_LOADED) {
        isc_throw(isc::InvalidOperation, "No data to install");
    }

    // Check the internal integrity assumption: we should have non NULL
    // zone data or we've allowed load error to create an empty zone.
    assert(impl_->data_holder_.get() || impl_->catch_load_error_);

    while (impl_->state_ != Impl::ZW_INSTALLED) {
        try {
            ZoneTableHeader& header = impl_->segment_.getHeader();
            ZoneTable* table(header.getTable());
            if (!table) {
                isc_throw(isc::Unexpected, "No zone table present");
            }
            // We still need to hold the zone data until we return from
            // addZone in case it throws, but we then need to immediately
            // release it as the ownership is transferred to the zone table.
            // we release this by (re)set it to the old data; that way we can
            // use the holder for the final cleanup.
            const ZoneTable::AddResult result(
                impl_->data_holder_->get() ?
                table->addZone(impl_->segment_.getMemorySegment(),
                               impl_->origin_, impl_->data_holder_->get()) :
                table->addEmptyZone(impl_->segment_.getMemorySegment(),
                                    impl_->origin_));
            impl_->data_holder_->set(result.zone_data);
            impl_->state_ = Impl::ZW_INSTALLED;
        } catch (const isc::util::MemorySegmentGrown&) {}
    }
}

void
ZoneWriter::cleanup() {
    // We eat the data (if any) now.

    ZoneData* zone_data = impl_->data_holder_->release();
    if (zone_data) {
        ZoneData::destroy(impl_->segment_.getMemorySegment(), zone_data,
                          impl_->rrclass_);
        impl_->state_ = Impl::ZW_CLEANED;
    }
}

}
}
}
