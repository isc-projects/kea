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

#include <string>
#include <memory>
#include <strings.h>

using std::string;
using std::auto_ptr;

namespace isc {
namespace dns {

// An internal exception, used to control the code flow in case of errors.
// It is thrown during the loading and caught later, not to be propagated
// outside of the file.
class InternalException : public isc::Exception {
public:
    InternalException(const char* filename, size_t line, const char* what) :
        Exception(filename, line, what)
    {}
};

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
        many_errors_((options & MANY_ERRORS) != 0),
        source_count_(0),
        complete_(false),
        seen_error_(false)
    {}

    void reportError(const std::string& filename, size_t line,
                     const std::string& reason)
    {
        seen_error_ = true;
        callbacks_.error(filename, line, reason);
        if (!many_errors_) {
            // In case we don't have the lenient mode, every error is fatal
            // and we throw
            ok_ = false;
            complete_ = true;
            isc_throw(MasterLoaderError, reason.c_str());
        }
    }

    void pushSource(const std::string& filename) {
        std::string error;
        if (!lexer_.pushSource(filename.c_str(), &error)) {
            if (initialized_) {
                // $INCLUDE file
                reportError(lexer_.getSourceName(), lexer_.getSourceLine(),
                            error);
            } else {
                // Top-level file
                reportError("", 0, error);
                ok_ = false;
            }
        }
        initialized_ = true;
        ++source_count_;
    }

    bool popSource() {
        lexer_.popSource();
        return (--source_count_ != 0);
    }

    void pushStreamSource(std::istream& stream) {
        lexer_.pushSource(stream);
        initialized_ = true;
        ++source_count_;
    }

    // Get a string token. Handle it as error if it is not string.
    const string getString() {
        lexer_.getNextToken(MasterToken::STRING).getString(string_token_);
        return (string_token_);
    }

    bool loadIncremental(size_t count_limit);

    void doInclude() {
        // First, get the filename to include
        const MasterToken::StringRegion
            filename(lexer_.getNextToken(MasterLexer::QSTRING).
                     getStringRegion());

        // TODO: Handle the case where there's Name after the
        // filename, meaning origin. Once $ORIGIN handling is
        // done, it should be interconnected somehow.

        // Push the filename. We abuse the fact that filename
        // may not contain '\0' anywhere in it, so we can
        // freely use the filename.beg directly.
        pushSource(filename.beg);

        // TODO: Eat any extra tokens at the end of line (they
        // should not be here, of course).
    }

    void handleDirective(const char* directive, size_t length) {
        // We use strncasecmp, because there seems to be no reasonable
        // way to compare strings case-insensitive in C++

        // Warning: The order of compared strings does matter. The length
        // parameter applies to the first one only.
        if (strncasecmp(directive, "INCLUDE", length) == 0) {
            doInclude();
        } else if (strncasecmp(directive, "ORIGIN", length) == 0) {
            // TODO: Implement
            isc_throw(isc::NotImplemented,
                      "Origin directive not implemented yet");
        } else if (strncasecmp(directive, "TTL", length) == 0) {
            // TODO: Implement
            isc_throw(isc::NotImplemented,
                      "TTL directive not implemented yet");
        } else {
            isc_throw(InternalException, "Unknown directive '" <<
                      string(directive, directive + length) << "'");
        }
    }

private:
    MasterLexer lexer_;
    const Name zone_origin_;
    const RRClass zone_class_;
    MasterLoaderCallbacks callbacks_;
    AddRRCallback add_callback_;
    const MasterLoader::Options options_;
    const std::string master_file_;
    std::string string_token_;
    bool initialized_;
    bool ok_;                   // Is it OK to continue loading?
    const bool many_errors_;    // Are many errors allowed (or should we abort
                                // on the first)
    size_t source_count_;       // How many sources are currently pushed.
public:
    bool complete_;             // All work done.
    bool seen_error_;           // Was there at least one error during the
                                // load?
};

bool
MasterLoader::MasterLoaderImpl::loadIncremental(size_t count_limit) {
    if (count_limit == 0) {
        isc_throw(isc::InvalidParameter, "Count limit set to 0");
    }
    if (complete_) {
        isc_throw(isc::InvalidOperation,
                  "Trying to load when already loaded");
    }
    if (!initialized_) {
        pushSource(master_file_);
    }
    size_t count = 0;
    while (ok_ && count < count_limit) {
        try {
            // Skip all EOLNs (empty lines) and finish on EOF
            bool empty = true;
            do {
                const MasterToken& empty_token(lexer_.getNextToken());
                if (empty_token.getType() == MasterToken::END_OF_FILE) {
                    if (!popSource()) {
                        return (true);
                    } else {
                        // We try to read a token from the popped source
                        // So retry the loop
                        continue;
                    }
                }
                empty = empty_token.getType() == MasterToken::END_OF_LINE;
            } while (empty);
            // Return the last token, as it was not empty
            lexer_.ungetToken();

            const MasterToken::StringRegion&
                name_string(lexer_.getNextToken(MasterToken::QSTRING).
                            getStringRegion());

            if (name_string.len > 0 && name_string.beg[0] == '$') {
                // This should have either thrown (and the error handler
                // will read up until the end of line) or read until the
                // end of line.

                // Exclude the $ from the string on this point.
                handleDirective(name_string.beg + 1, name_string.len - 1);
                // So, get to the next line, there's nothing more interesting
                // in this one.
                continue;
            }

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
            if (data) {
                add_callback_(name, rrclass, rrtype, ttl, data);

                // Good, we loaded another one
                ++count;
            } else {
                seen_error_ = true;
                if (!many_errors_) {
                    ok_ = false;
                    complete_ = true;
                    // We don't have the exact error here, but it was reported
                    // by the error callback.
                    isc_throw(MasterLoaderError, "Invalid RR data");
                }
            }
        } catch (const MasterLoaderError&) {
            // This is a hack. We exclude the MasterLoaderError from the
            // below case. Once we restrict the below to some smaller
            // exception, we should remove this.
            throw;
        } catch (const isc::Exception& e) {
            // TODO: Once we do #2518, catch only the DNSTextError here,
            // not isc::Exception. The rest should be just simply
            // propagated.
            reportError(lexer_.getSourceName(), lexer_.getSourceLine(),
                        e.what());
            // We want to continue. Try to read until the end of line
            bool end = false;
            do {
                const MasterToken& token(lexer_.getNextToken());
                switch (token.getType()) {
                    case MasterToken::END_OF_FILE:
                        callbacks_.warning(lexer_.getSourceName(),
                                           lexer_.getSourceLine(),
                                           "Unexpected end ond of file");
                        if (!popSource()) {
                            return (true);
                        }
                        // Else: fall through, the popped source is
                        // at the end of line currently
                    case MasterToken::END_OF_LINE:
                        end = true;
                        break;
                    default:
                        // Do nothing. This is just to make compiler
                        // happy
                        break;
                }
            } while (!end);
        }
    }
    // When there was a fatal error and ok is false, we say we are done.
    return (!ok_);
}

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

MasterLoader::MasterLoader(std::istream& stream,
                           const Name& zone_origin,
                           const RRClass& zone_class,
                           const MasterLoaderCallbacks& callbacks,
                           const AddRRCallback& add_callback,
                           Options options)
{
    if (add_callback.empty()) {
        isc_throw(isc::InvalidParameter, "Empty add RR callback");
    }
    auto_ptr<MasterLoaderImpl> impl(new MasterLoaderImpl("", zone_origin,
                                                         zone_class, callbacks,
                                                         add_callback,
                                                         options));
    impl->pushStreamSource(stream);
    impl_ = impl.release();
}

MasterLoader::~MasterLoader() {
    delete impl_;
}

bool
MasterLoader::loadIncremental(size_t count_limit) {
    const bool result = impl_->loadIncremental(count_limit);
    impl_->complete_ = result;
    return (result);
}

bool
MasterLoader::loadedSucessfully() const {
    return (impl_->complete_ && !impl_->seen_error_);
}

} // end namespace dns
} // end namespace isc
