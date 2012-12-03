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
#include <dns/master_lexer.h>
#include <dns/name.h>
#include <dns/rrttl.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rrset.h>
#include <dns/rdata.h>

using std::string;

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
        string errors;
        if (!lexer_.pushSource(master_file, &errors)) {
            // TODO: Handle somehow.
            assert(0);
        }
    }

    // Get a string token. Handle it as error if it is not string.
    const string getString() {
        return (lexer_.getNextToken(MasterToken::QSTRING).getString());
    }

    bool loadIncremental(size_t count_limit) {
        size_t count = 0;
        while (count < count_limit) {
            // Skip all EOLNs (empty lines) and finish on EOF
            bool empty = true;
            do {
                const MasterToken& empty_token(lexer_.getNextToken());
                if (empty_token.getType() == MasterToken::END_OF_FILE) {
                    // TODO: Check if this is the last source, possibly pop
                    return (true);
                }
                empty = empty_token.getType() == MasterToken::END_OF_LINE;
            } while (empty);
            // Return the last token, as it was not empty
            lexer_.ungetToken();

            const string name_string(getString());
            // TODO $ handling
            const Name name(name_string); // TODO: Origin
            // TODO: Some more flexibility. We don't allow omitting anything yet

            // The parameters
            const RRTTL ttl(getString());
            const RRClass rrclass(getString());
            const RRType rrtype(getString());

            // TODO: Origin handling
            const rdata::RdataPtr data(rdata::createRdata(rrtype, rrclass,
                                                          lexer_, NULL,
                                                          options_,
                                                          callbacks_));
            // In case we get NULL, it means there was error creating
            // the Rdata. The errors should have been reported by
            // callbacks_ already, so we just need to not report the RR
            if (data != rdata::RdataPtr()) {
                // Create the RRset. We don't need the RRSIG, so we are good
                // with the basic one
                const RRsetPtr rrset(new BasicRRset(name, rrclass, rrtype,
                                                    ttl));
                rrset->addRdata(data);
                // OK now, so give the RRset with single RR to the caller
                add_callback_(rrset);

                // Good, we loaded another one
                ++count;
            };
        }
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
