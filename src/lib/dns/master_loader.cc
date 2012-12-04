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
                     const AddRRCallback& add_callback,
                     MasterLoader::Options options) :
        lexer_(),
        zone_origin_(zone_origin),
        zone_class_(zone_class),
        callbacks_(callbacks),
        add_callback_(add_callback),
        options_(options),
        master_file_(master_file),
        initialized_(false),
        ok_(true),
        complete_(false)
    {}

    void pushSource(const std::string& filename) {
        std::string error;
        if (!lexer_.pushSource(filename.c_str(), &error)) {
            ok_ = false;
            callbacks_.error("", 0, error);
        }
    }

    // Get a string token. Handle it as error if it is not string.
    const string getString() {
        return (lexer_.getNextToken(MasterToken::QSTRING).getString());
    }

    bool loadIncremental(size_t count_limit) {
        if (complete_) {
            isc_throw(isc::InvalidOperation,
                      "Trying to load when already loaded");
        }
        if (!initialized_) {
            pushSource(master_file_);
            initialized_ = true;
        }
        size_t count = 0;
        while (ok_ && count < count_limit) {
            try {
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

                const MasterToken::StringRegion
                    name_string(lexer_.getNextToken(MasterToken::QSTRING).
                                getStringRegion());
                // TODO $ handling
                const Name name(name_string.beg, name_string.len,
                                &zone_origin_);
                // TODO: Some more flexibility. We don't allow omitting
                // anything yet

                // The parameters
                const RRTTL ttl(getString());
                const RRClass rrclass(getString());
                const RRType rrtype(getString());

                // TODO: Some more validation?
                if (rrclass != zone_class_) {
                    // It doesn't really matter much what type of exception
                    // we throw, we catch it just below.
                    isc_throw(isc::BadValue, "Class mismatch: " << rrclass <<
                              "vs. " << zone_class_);
                }

                const rdata::RdataPtr data(rdata::createRdata(rrtype, rrclass,
                                                              lexer_,
                                                              &zone_origin_,
                                                              options_,
                                                              callbacks_));
                // In case we get NULL, it means there was error creating
                // the Rdata. The errors should have been reported by
                // callbacks_ already. We need to decide if we want to continue
                // or not.
                if (data != rdata::RdataPtr()) {
                    add_callback_(name, rrclass, rrtype, ttl, data);

                    // Good, we loaded another one
                    ++count;
                } else if (!(options_ & MANY_ERRORS)) {
                    return (true);
                }
            } catch (const isc::Exception& e) {
                // TODO: Do we want to list expected exceptions here instead?
                callbacks_.error(lexer_.getSourceName(),
                                 lexer_.getSourceLine(),
                                 e.what());
                if (options_ & MANY_ERRORS) {
                    // We want to continue. Try to read until the end of line
                    bool end = false;
                    do {
                        const MasterToken& token(lexer_.getNextToken());
                        switch (token.getType()) {
                            case MasterToken::END_OF_FILE:
                                // TODO: Try pop in case this is not the only
                                // source
                                return (true);
                            case MasterToken::END_OF_LINE:
                                end = true;
                                break;
                            default:
                                // Do nothing. This is just to make compiler
                                // happy
                                break;
                        }
                    } while (!end);
                } else {
                    // We abort on first error. We are therefore done.
                    return (true);
                }
            }
        }
        // When there was a fatal error and ok is false, we say we are done.
        return (!ok_);
    }

private:
    MasterLexer lexer_;
    const Name zone_origin_;
    const RRClass zone_class_;
    MasterLoaderCallbacks callbacks_;
    AddRRCallback add_callback_;
    MasterLoader::Options options_;
    const std::string master_file_;
    bool initialized_;
    bool ok_;
public:
    bool complete_;
};

MasterLoader::MasterLoader(const char* master_file,
                           const Name& zone_origin,
                           const RRClass& zone_class,
                           const MasterLoaderCallbacks& callbacks,
                           const AddRRCallback& add_callback,
                           Options options)
{
    if (add_callback.empty()) {
        isc_throw(isc::InvalidParameter, "Empty add RR callback");
    }
    impl_ = new MasterLoaderImpl(master_file, zone_origin,
                                 zone_class, callbacks, add_callback, options);
}

MasterLoader::~MasterLoader() {
    delete impl_;
}

bool
MasterLoader::loadIncremental(size_t count_limit) {
    bool result = impl_->loadIncremental(count_limit);
    impl_->complete_ = result;
    return (result);
}

} // end namespace dns
} // end namespace isc
