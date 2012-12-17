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
#include <vector>
#include <boost/algorithm/string/predicate.hpp> // for iequals
#include <boost/shared_ptr.hpp>

using std::string;
using std::auto_ptr;
using std::vector;
using std::pair;
using boost::algorithm::iequals;
using boost::shared_ptr;

namespace isc {
namespace dns {

namespace {

// An internal exception, used to control the code flow in case of errors.
// It is thrown during the loading and caught later, not to be propagated
// outside of the file.
class InternalException : public isc::Exception {
public:
    InternalException(const char* filename, size_t line, const char* what) :
        Exception(filename, line, what)
    {}
};

} // end unnamed namespace

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
        active_origin_(zone_origin),
        zone_class_(zone_class),
        callbacks_(callbacks),
        add_callback_(add_callback),
        options_(options),
        master_file_(master_file),
        initialized_(false),
        ok_(true),
        many_errors_((options & MANY_ERRORS) != 0),
        previous_name_(false),
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
                isc_throw(InternalException, error.c_str());
            } else {
                // Top-level file
                reportError("", 0, error);
                ok_ = false;
            }
        }
        // Store the current status, so we can recover it upon popSource
        include_info_.push_back(IncludeInfo(active_origin_, last_name_));
        initialized_ = true;
        previous_name_ = false;
    }

    bool popSource() {
        if (lexer_.getSourceCount() == 1) {
            return (false);
        }
        lexer_.popSource();
        // Restore original origin and last seen name

        // We move in tandem, there's an extra item included during the
        // initialization, so we can never run out of them
        assert(!include_info_.empty());
        const IncludeInfo& info(include_info_.back());
        active_origin_ = info.first;
        last_name_ = info.second;
        include_info_.pop_back();
        previous_name_ = false;
        return (true);
    }

    void pushStreamSource(std::istream& stream) {
        lexer_.pushSource(stream);
        initialized_ = true;
    }

    // Get a string token. Handle it as error if it is not string.
    const string getString() {
        lexer_.getNextToken(MasterToken::STRING).getString(string_token_);
        return (string_token_);
    }

    bool loadIncremental(size_t count_limit);

    MasterToken handleInitialToken();

    void doOrigin(bool is_optional) {
        // Parse and create the new origin. It is relative to the previous
        // one.
        const MasterToken&
            name_tok(lexer_.getNextToken(MasterToken::QSTRING, is_optional));

        if (name_tok.getType() == MasterToken::QSTRING ||
            name_tok.getType() == MasterToken::STRING) {

            const MasterToken::StringRegion&
                name_string(name_tok.getStringRegion());
            active_origin_ = Name(name_string.beg, name_string.len,
                                  &active_origin_);
        } else {
            // If it is not optional, we must not get anything but
            // a string token.
            assert(is_optional);

            // We return the newline there. This is because we want to
            // behave the same if there is or isn't the name, leaving the
            // newline there.
            lexer_.ungetToken();
        }
    }

    void doInclude() {
        // First, get the filename to include
        const string
            filename(lexer_.getNextToken(MasterToken::QSTRING).getString());

        // There optionally can be an origin, that applies before the include.
        doOrigin(true);

        pushSource(filename);
    }

    void handleDirective(const char* directive, size_t length) {
        if (iequals(directive, "INCLUDE")) {
            doInclude();
        } else if (iequals(directive, "ORIGIN")) {
            doOrigin(false);
            // The doOrigin doesn't do the cleanup of the line. This is
            // because it's shared with the doInclude and that one can't do
            // it.
            eatUntilEOL(true);
        } else if (iequals(directive, "TTL")) {
            // TODO: Implement
            isc_throw(isc::NotImplemented,
                      "TTL directive not implemented yet");
        } else {
            isc_throw(InternalException, "Unknown directive '" <<
                      string(directive, directive + length) << "'");
        }
    }

    void eatUntilEOL(bool reportExtra) {
        // We want to continue. Try to read until the end of line
        for (;;) {
            const MasterToken& token(lexer_.getNextToken());
            switch (token.getType()) {
                case MasterToken::END_OF_FILE:
                    callbacks_.warning(lexer_.getSourceName(),
                                       lexer_.getSourceLine(),
                                       "File does not end with newline");
                    // We don't pop here. The End of file will stay there,
                    // and we'll handle it in the next iteration of
                    // loadIncremental properly.
                    return;
                case MasterToken::END_OF_LINE:
                    // Found the end of the line. Good.
                    return;
                default:
                    // Some other type of token.
                    if (reportExtra) {
                        reportExtra = false;
                        reportError(lexer_.getSourceName(),
                                    lexer_.getSourceLine(),
                                    "Extra tokens at the end of line");
                    }
                    break;
            }
        }
    }

private:
    MasterLexer lexer_;
    const Name zone_origin_;
    Name active_origin_; // The origin used during parsing
                         // (modifiable by $ORIGIN)
    shared_ptr<Name> last_name_; // Last seen name (for INITAL_WS handling)
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
    // Some info about the outer files from which we include.
    // The first one is current origin, the second is the last seen name
    // in that file.
    typedef pair<Name, shared_ptr<Name> > IncludeInfo;
    vector<IncludeInfo> include_info_;
    bool previous_name_; // True if there was a previous name in this file
                         // (false at the beginning or after an $INCLUDE line)
public:
    bool complete_;             // All work done.
    bool seen_error_;           // Was there at least one error during the
                                // load?
};

// A helper method of loadIncremental, parsing the first token of a new line.
// If it looks like an RR, detect its owner name and return a string token for
// the next field of the RR.
// Otherwise, return either END_OF_LINE or END_OF_FILE token depending on
// whether the loader continues to the next line or completes the load,
// respectively.  Other corner cases including $-directive handling is done
// here.
// For unexpected errors, it throws an exception, which will be handled in
// loadIncremental.
MasterToken
MasterLoader::MasterLoaderImpl::handleInitialToken() {
    const MasterToken& initial_token =
        lexer_.getNextToken(MasterLexer::QSTRING | MasterLexer::INITIAL_WS);

    // The most likely case is INITIAL_WS, and then string/qstring.  We
    // handle them first.
    if (initial_token.getType() == MasterToken::INITIAL_WS) {
        const MasterToken& next_token = lexer_.getNextToken();
        if (next_token.getType() == MasterToken::END_OF_LINE) {
            return (next_token); // blank line
        } else if (next_token.getType() == MasterToken::END_OF_FILE) {
            lexer_.ungetToken(); // handle it in the next iteration.
            eatUntilEOL(true);  // effectively warn about the unexpected EOF.
            return (MasterToken(MasterToken::END_OF_LINE));
        }

        // This means the same name as previous.
        if (last_name_.get() == NULL) {
            isc_throw(InternalException, "No previous name to use in "
                      "place of initial whitespace");
        } else if (!previous_name_) {
            callbacks_.warning(lexer_.getSourceName(),
                               lexer_.getSourceLine(),
                               "Ambiguous previous name previous name for "
                               "use in place of initial whitespace");
        }
        return (next_token);
    } else if (initial_token.getType() == MasterToken::STRING ||
               initial_token.getType() == MasterToken::QSTRING) {
        // If it is name (or directive), handle it.
        const MasterToken::StringRegion&
            name_string(initial_token.getStringRegion());

        if (name_string.len > 0 && name_string.beg[0] == '$') {
            // This should have either thrown (and the error handler
            // will read up until the end of line) or read until the
            // end of line.

            // Exclude the $ from the string on this point.
            handleDirective(name_string.beg + 1, name_string.len - 1);
            // So, get to the next line, there's nothing more interesting
            // in this one.
            return (MasterToken(MasterToken::END_OF_LINE));
        }

        // This should be an RR, starting with an owner name.  Construct the
        // name, and some string token should follow.
        last_name_.reset(new Name(name_string.beg, name_string.len,
                                  &active_origin_));
        previous_name_ = true;
        return (lexer_.getNextToken(MasterToken::STRING));
    }

    switch (initial_token.getType()) { // handle less common cases
    case MasterToken::END_OF_FILE:
        if (!popSource()) {
            return (initial_token);
        } else {
            // We try to read a token from the popped source
            // So retry the loop, but first, make sure the source
            // is at EOL
            eatUntilEOL(true);
            return (MasterToken(MasterToken::END_OF_LINE));
        }
    case MasterToken::END_OF_LINE:
        return (initial_token); // empty line
    case MasterToken::ERROR:
        // Error token here.
        isc_throw(InternalException, initial_token.getErrorText());
    default:
        // Some other token (what could that be?)
        isc_throw(InternalException, "Parser got confused (unexpected "
                  "token " << initial_token.getType() << ")");
    }
}

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
            const MasterToken next_token = handleInitialToken();
            if (next_token.getType() == MasterToken::END_OF_FILE) {
                return (true);  // we are done
            } else if (next_token.getType() == MasterToken::END_OF_LINE) {
                continue;       // nothing more to do in this line
            }
            // We are going to parse an RR, have known the owner name,
            // and are now seeing the next string token in the rest of the RR.
            assert(next_token.getType() == MasterToken::STRING);

            // TODO: Some more flexibility. We don't allow omitting
            // anything yet

            // The parameters
            const RRTTL ttl(next_token.getString());
            const RRClass rrclass(getString());
            const RRType rrtype(getString());

            // TODO: Some more validation?
            if (rrclass != zone_class_) {
                // It doesn't really matter much what type of exception
                // we throw, we catch it just below.
                isc_throw(isc::BadValue, "Class mismatch: " << rrclass <<
                          "vs. " << zone_class_);
            }
            // TODO: Check if it is SOA, it should be at the origin.

            const rdata::RdataPtr data(rdata::createRdata(rrtype, rrclass,
                                                          lexer_,
                                                          &active_origin_,
                                                          options_,
                                                          callbacks_));
            // In case we get NULL, it means there was error creating
            // the Rdata. The errors should have been reported by
            // callbacks_ already. We need to decide if we want to continue
            // or not.
            if (data) {
                add_callback_(*last_name_, rrclass, rrtype, ttl, data);

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
            eatUntilEOL(false);
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
