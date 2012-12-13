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
#include <dns/rdataclass.h>
#include <dns/rrttl.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rdata.h>

#include <boost/scoped_ptr.hpp>

#include <string>
#include <memory>
#include <boost/algorithm/string/predicate.hpp> // for iequals

using std::string;
using std::auto_ptr;
using boost::algorithm::iequals;

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
        seen_error_(false),
        warn_rfc1035_ttl_(true)
    {}

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
        initialized_ = true;
        ++source_count_;
    }

    void pushStreamSource(std::istream& stream) {
        lexer_.pushSource(stream);
        initialized_ = true;
        ++source_count_;
    }

    bool loadIncremental(size_t count_limit);

private:
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

    bool popSource() {
        if (--source_count_ == 0) {
            return (false);
        }
        lexer_.popSource();
        return (true);
    }

    // Get a string token. Handle it as error if it is not string.
    const string getString() {
        lexer_.getNextToken(MasterToken::STRING).getString(string_token_);
        return (string_token_);
    }

    void doInclude() {
        // First, get the filename to include
        const string
            filename(lexer_.getNextToken(MasterToken::QSTRING).getString());

        // There could be an origin (or maybe not). So try looking
        const MasterToken name_tok(lexer_.getNextToken(MasterToken::QSTRING,
                                                       true));

        if (name_tok.getType() == MasterToken::QSTRING ||
            name_tok.getType() == MasterToken::STRING) {
            // TODO: Handle the origin. Once we complete #2427.
        } else {
            // We return the newline there. This is because after we pop
            // the source, we want to call eatUntilEOL and this would
            // eat to the next one.
            lexer_.ungetToken();
        }

        pushSource(filename);
    }

    void setDefaultTTL(const RRTTL& ttl) {
        if (!default_ttl_) {
            default_ttl_.reset(new RRTTL(ttl));
        } else {
            *default_ttl_ = ttl;
        }
    }

    void setDefaultTTL(const string& ttl_txt) {
        setDefaultTTL(RRTTL(ttl_txt));
        eatUntilEOL(true);
    }

    void setCurrentTTL(const RRTTL& ttl) {
        if (!current_ttl_) {
            current_ttl_.reset(new RRTTL(ttl));
        } else {
            *current_ttl_ = ttl;
        }
    }

    bool setCurrentTTL(const string& ttl_txt) {
        try {
            setCurrentTTL(RRTTL(ttl_txt));
            return (true);
        } catch (const InvalidRRTTL&) {
            return (false);
        }
    }

    // Determine the TTL of the current RR based on the given parsing context.
    //
    // explicit_ttl is true iff the TTL is explicitly specified for that RR
    // (in which case current_ttl_ is set to that TTL).
    // rrtype is the type of the current RR, and rdata is its RDATA.  They
    // only matter if the type is SOA and no available TTL is known.  In this
    // case the minimum TTL of the SOA will be used as the TTL of that SOA
    // and the default TTL for subsequent RRs.
    const RRTTL& getCurrentTTL(bool explicit_ttl, const RRType& rrtype,
                               const rdata::ConstRdataPtr& rdata) {
        if (!current_ttl_ && !default_ttl_) {
            if (rrtype == RRType::SOA()) {
                callbacks_.warning(lexer_.getSourceName(),
                                   lexer_.getSourceLine(),
                                   "no TTL specified; "
                                   "using SOA MINTTL instead");
                const uint32_t ttl_val =
                    dynamic_cast<const rdata::generic::SOA&>(*rdata).
                    getMinimum();
                setDefaultTTL(RRTTL(ttl_val));
                setCurrentTTL(*default_ttl_);
            }
        } else if (!explicit_ttl && default_ttl_) {
            setCurrentTTL(*default_ttl_);
        } else if (!explicit_ttl && warn_rfc1035_ttl_) {
            // Omitted (class and) TTL values are default to the last
            // explicitly stated values (RFC 1035, Sec. 5.1).
            callbacks_.warning(lexer_.getSourceName(),
                               lexer_.getSourceLine(),
                               "using RFC1035 TTL semantics");
            warn_rfc1035_ttl_ = false; // we only warn about this once
        }
        assert(current_ttl_);
        return (*current_ttl_);
    }

    void handleDirective(const char* directive, size_t length) {
        if (iequals(directive, "INCLUDE")) {
            doInclude();
        } else if (iequals(directive, "ORIGIN")) {
            // TODO: Implement
            isc_throw(isc::NotImplemented,
                      "Origin directive not implemented yet");
        } else if (iequals(directive, "TTL")) {
            setDefaultTTL(getString());
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
                                       "Unexpected end ond of file");
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
    const RRClass zone_class_;
    MasterLoaderCallbacks callbacks_;
    AddRRCallback add_callback_;
    boost::scoped_ptr<RRTTL> default_ttl_;
    boost::scoped_ptr<RRTTL> current_ttl_;
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
    bool warn_rfc1035_ttl_;     // should warn if implicit TTL determination
                                // from the previous RR is used.
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
                        // So retry the loop, but first, make sure the source
                        // is at EOL
                        eatUntilEOL(true);
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
            MasterToken rrparam_token = lexer_.getNextToken();

            bool explicit_ttl = false;
            if (rrparam_token.getType() == MasterToken::STRING) {
                // Try TTL
                if (setCurrentTTL(rrparam_token.getString())) {
                    explicit_ttl = true;
                    rrparam_token = lexer_.getNextToken();
                }
            }

            const RRClass rrclass(rrparam_token.getString());
            const RRType rrtype(getString());

            // TODO: Some more validation?
            if (rrclass != zone_class_) {
                // It doesn't really matter much what type of exception
                // we throw, we catch it just below.
                isc_throw(isc::BadValue, "Class mismatch: " << rrclass <<
                          "vs. " << zone_class_);
            }
            // TODO: Check if it is SOA, it should be at the origin.

            const rdata::RdataPtr rdata(rdata::createRdata(rrtype, rrclass,
                                                           lexer_,
                                                           &zone_origin_,
                                                           options_,
                                                           callbacks_));
            // In case we get NULL, it means there was error creating
            // the Rdata. The errors should have been reported by
            // callbacks_ already. We need to decide if we want to continue
            // or not.
            if (rdata) {
                add_callback_(name, rrclass, rrtype,
                              getCurrentTTL(explicit_ttl, rrtype, rdata),
                              rdata);

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
