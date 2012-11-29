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

#include <dns/master_loader.h>

namespace isc {
namespace dns {

class MasterLoader::MasterLoaderImpl {
public:
    MasterLoaderImpl(const char* master_file,
                     const Name& zone_origin,
                     const RRClass& zone_class,
                     const MasterLoaderCallbacks& callbacks,
                     const AddRRsetCallback& add_callback,
                     MasterLoader::Options options) :
        lexer_(),
        zone_origin_(zone_origin),
        zone_class_(zone_class),
        callbacks_(callbacks),
        add_callback_(add_callback),
        options_(options)
    {
        lexer_.pushSource(master_file);
    }

    bool loadIncremental(size_t count_limit) {
        size_t count = 0;
        bool done = false;
        do {
            // Code goes here
        } while (!done && (count_limit != 0 && ++count < count_limit));
        // add remaining rrset that was being built (TODO)
        return (false);
    }

private:
    MasterLexer lexer_;
    const Name& zone_origin_;
    const RRClass zone_class_;
    MasterLoaderCallbacks callbacks_;
    AddRRsetCallback add_callback_;
    MasterLoader::Options options_;
    RRsetPtr current_rrset_;
};

MasterLoader::MasterLoader(const char* master_file,
                           const Name& zone_origin,
                           const RRClass& zone_class,
                           const MasterLoaderCallbacks& callbacks,
                           const AddRRsetCallback& add_callback,
                           Options options)
{
    impl_ = new MasterLoaderImpl(master_file, zone_origin,
                                 zone_class, callbacks, add_callback, options);
}

MasterLoader::~MasterLoader() {
    delete impl_;
}

bool
MasterLoader::loadIncremental(size_t count_limit) {
    return (impl_->loadIncremental(count_limit));
}

} // end namespace dns
} // end namespace isc
