// Copyright (C) 2012-2015 Internet Systems Consortium, Inc. ("ISC")
//
// This Source Code Form is subject to the terms of the Mozilla Public
// License, v. 2.0. If a copy of the MPL was not distributed with this
// file, You can obtain one at http://mozilla.org/MPL/2.0/.

#include <dns/master_loader.h>
#include <dns/master_lexer.h>
#include <dns/name.h>
#include <dns/rdataclass.h>
#include <dns/rrttl.h>
#include <dns/rrclass.h>
#include <dns/rrtype.h>
#include <dns/rdata.h>

#include <boost/format.hpp>
#include <boost/algorithm/string/predicate.hpp> // for iequals
#include <boost/scoped_ptr.hpp>
#include <boost/shared_ptr.hpp>

#include <string>
#include <memory>
#include <vector>

#include <cstdio> // for sscanf()

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

/// \brief Private implementation class for the \c MasterLoader
///
/// This class is used internally by the \c MasterLoader and is not
/// publicly visible. It is present to avoid polluting the public API
/// with internal implementation details of the \c MasterLoader.
// cppcheck-suppress noConstructor
class MasterLoader::MasterLoaderImpl {
public:
    /// \brief Constructor.
    ///
    /// \param master_file Path to the file to load.
    /// \param zone_origin The origin of zone to be expected inside
    ///     the master file. Currently unused, but it is expected to
    ///     be used for some validation.
    /// \param zone_class The class of zone to be expected inside the
    ///     master file.
    /// \param callbacks The callbacks by which it should report problems.
    ///     Usually, the callback carries a filename and line number of the
    ///     input where the problem happens. There's a special case of empty
    ///     filename and zero line in case the opening of the top-level master
    ///     file fails.
    /// \param add_callback The callback which would be called with each
    ///     loaded RR.
    /// \param options Options for the parsing, which is bitwise-or of
    ///     the Options values or DEFAULT. If the MANY_ERRORS option is
    ///     included, the parser tries to continue past errors. If it
    ///     is not included, it stops at first encountered error.
    /// \throw std::bad_alloc when there's not enough memory.
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
        seen_error_(false),
        warn_rfc1035_ttl_(true),
        rr_count_(0)
    {}

    /// \brief Wrapper around \c MasterLexer::pushSource() (file version)
    ///
    /// This method is used as a wrapper around the lexer's
    /// \c pushSource() to also save the current origin and the last
    /// seen name (to be restored upon \c popSource()). It also calls
    /// \c pushSource(). See \c doInclude() implementation for more
    /// details.
    ///
    /// \param filename Path to the file to push as a new source.
    /// \param current_origin The current origin name to save.
    void pushSource(const std::string& filename, const Name& current_origin) {
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
        include_info_.push_back(IncludeInfo(current_origin, last_name_));
        initialized_ = true;
        previous_name_ = false;
    }

    /// \brief Wrapper around \c MasterLexer::pushSource() (stream version)
    ///
    /// Similar to \c pushSource(). This method need not save the
    /// current origin as it is not used with $INCLUDE processing.
    ///
    /// \param stream The input stream to use as a new source.
    void pushStreamSource(std::istream& stream) {
        lexer_.pushSource(stream);
        initialized_ = true;
    }

    /// \brief Implementation of \c MasterLoader::loadIncremental()
    ///
    /// See \c MasterLoader::loadIncremental() for details.
    bool loadIncremental(size_t count_limit);

    /// \brief Return the total size of the input sources pushed so
    /// far. See \c MasterLexer::getTotalSourceSize().
    size_t getSize() const { return (lexer_.getTotalSourceSize()); }

    /// \brief Return the line number being parsed in the pushed input
    /// sources. See \c MasterLexer::getPosition().
    size_t getPosition() const { return (lexer_.getPosition()); }

private:
    /// \brief Report an error using the callbacks that were supplied
    /// during \c MasterLoader construction. Note that this method also
    /// throws \c MasterLoaderError exception if necessary, so the
    /// caller need not throw it.
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

    /// \brief Wrapper around \c MasterLexer::popSource()
    ///
    /// This method is used as a wrapper around the lexer's
    /// \c popSource() to also restore the current origin and the last
    /// seen name (at time of push). It also calls \c popSource(). See
    /// \c doInclude() implementation for more details.
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

    /// \brief Get a string token. Handle it as error if it is not string.
    const string getString() {
        lexer_.getNextToken(MasterToken::STRING).getString(string_token_);
        return (string_token_);
    }

    /// \brief Parse the initial token at the beginning of a line in a
    /// master file (or stream).
    ///
    /// A helper method of \c loadIncremental(), parsing the first token
    /// of a new line.  If it looks like an RR, detect its owner name
    /// and return a string token for the next field of the RR.
    ///
    /// Otherwise, return either \c END_OF_LINE or \c END_OF_FILE token
    /// depending on whether the loader continues to the next line or
    /// completes the load, respectively.  Other corner cases including
    /// $-directive handling is done here.
    ///
    /// For unexpected errors, it throws an exception, which will be
    /// handled in \c loadIncremental().
    MasterToken handleInitialToken();

    /// \brief Helper method for \c doGenerate().
    ///
    /// This is a helper method for \c doGenerate() that processes the
    /// LHS or RHS for a single iteration in the range that is requested
    /// by the $GENERATE directive and returns a generated string (that
    /// is used to build a name (LHS) or RDATA (RHS) for an RR). See the
    /// commented implementation for details.
    std::string generateForIter(const std::string& str, const int it);

    /// \brief Process the $GENERATE directive.
    ///
    /// See the commented implementation for details.
    void doGenerate();

    /// \brief Process the $ORIGIN directive.
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
            if (name_string.len > 0 &&
                name_string.beg[name_string.len - 1] != '.') {
                callbacks_.warning(lexer_.getSourceName(),
                                   lexer_.getSourceLine(),
                                   "The new origin is relative, did you really"
                                   " mean " + active_origin_.toText() + "?");
            }
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

    /// \brief Process the $INCLUDE directive.
    void doInclude() {
        // First, get the filename to include
        const string
            filename(lexer_.getNextToken(MasterToken::QSTRING).getString());

        // There optionally can be an origin, that applies before the include.
        // We need to save the currently active origin before calling
        // doOrigin(), because it would update active_origin_ while we need
        // to pass the active origin before recognizing the new origin to
        // pushSource.  Note: RFC 1035 is not really clear on this: it reads
        // "regardless of changes... within the included file", but the new
        // origin is not really specified "within the included file".
        // Nevertheless, this behavior is probably more likely to be the
        // intent of the RFC, and it's compatible with BIND 9.
        const Name current_origin = active_origin_;
        doOrigin(true);

        pushSource(filename, current_origin);
    }

    /// \brief Parse RR fields (TTL, CLASS and TYPE).
    ///
    /// A helper method for \c loadIncremental(). It parses part of an
    /// RR until it finds the RR type field.  If TTL or RR class is
    /// specified before the RR type, it also recognizes and validates
    /// them.
    ///
    /// \param explicit_ttl will be set to true if this method finds a
    /// valid TTL field.
    /// \param rrparam_token Pass the current (parsed) token here.
    RRType parseRRParams(bool& explicit_ttl, MasterToken rrparam_token) {
        // Find TTL, class and type.  Both TTL and class are
        // optional and may occur in any order if they exist. TTL
        // and class come before type which must exist.
        //
        // [<TTL>] [<class>] <type> <RDATA>
        // [<class>] [<TTL>] <type> <RDATA>

        // named-signzone outputs TTL first, so try parsing it in order
        // first.
        if (setCurrentTTL(rrparam_token.getString())) {
            explicit_ttl = true;
            rrparam_token = lexer_.getNextToken(MasterToken::STRING);
        } else {
            // If it's not a TTL here, continue and try again
            // after the RR class below.
        }

        boost::scoped_ptr<RRClass> rrclass
            (RRClass::createFromText(rrparam_token.getString()));
        if (rrclass) {
            if (*rrclass != zone_class_) {
                isc_throw(InternalException, "Class mismatch: " << *rrclass <<
                          " vs. " << zone_class_);
            }
            rrparam_token = lexer_.getNextToken(MasterToken::STRING);
        }

        // If we couldn't parse TTL earlier in the stream (above), try
        // again at current location.
        if (!explicit_ttl && setCurrentTTL(rrparam_token.getString())) {
            explicit_ttl = true;
            rrparam_token = lexer_.getNextToken(MasterToken::STRING);
        }

        // Return the current string token's value as the RRType.
        return (RRType(rrparam_token.getString()));
    }

    /// \brief Check and limit TTL to maximum value.
    ///
    /// Upper limit check when recognizing a specific TTL value from the
    /// zone file ($TTL, the RR's TTL field, or the SOA minimum).  RFC2181
    /// Section 8 limits the range of TTL values to 2^31-1 (0x7fffffff),
    /// and prohibits transmitting a TTL field exceeding this range.  We
    /// guarantee that by limiting the value at the time of zone
    /// parsing/loading, following what BIND 9 does.  Resetting it to 0
    /// at this point may not be exactly what the RFC states (depending on
    /// the meaning of 'received'), but the end result would be the same (i.e.,
    /// the guarantee on transmission).  Again, we follow the BIND 9's behavior
    /// here.
    ///
    /// \param ttl the TTL to check. If it is larger than the maximum
    /// allowed, it is set to 0.
    /// \param post_parsing should be true iff this method is called
    /// after parsing the entire RR and the lexer is positioned at the
    /// next line. It's just for calculating the accurate source line
    /// when callback is necessary.
    void limitTTL(RRTTL& ttl, bool post_parsing) {
        if (ttl > RRTTL::MAX_TTL()) {
            const size_t src_line = lexer_.getSourceLine() -
                (post_parsing ? 1 : 0);
            callbacks_.warning(lexer_.getSourceName(), src_line,
                               "TTL " + ttl.toText() + " > MAXTTL, "
                               "setting to 0 per RFC2181");
            ttl = RRTTL(0);
        }
    }

    /// \brief Set/reset the default TTL.
    ///
    /// This should be from either $TTL or SOA minimum TTL (it's the
    /// caller's responsibility; this method doesn't care about where it
    /// comes from). See \c limitTTL() for parameter post_parsing.
    void setDefaultTTL(const RRTTL& ttl, bool post_parsing) {
        assignTTL(default_ttl_, ttl);
        limitTTL(*default_ttl_, post_parsing);
    }

    /// \brief Try to set/reset the current TTL from candidate TTL text.
    ///
    /// It's possible it that the text does not actually represent a TTL
    /// (which is not immediately considered an error). Returns \c true
    /// iff it's recognized as a valid TTL (and only in which case the
    /// current TTL is set).
    ///
    /// \param ttl_txt The text to parse as a TTL.
    /// \return true if a TTL was parsed (and set as the current TTL).
    bool setCurrentTTL(const string& ttl_txt) {
        // We use the factory version instead of RRTTL constructor as we
        // need to expect cases where ttl_txt does not actually represent a TTL
        // but an RR class or type.
        RRTTL* rrttl = RRTTL::createFromText(ttl_txt);
        if (rrttl) {
            current_ttl_.reset(rrttl);
            limitTTL(*current_ttl_, false);
            return (true);
        }
        return (false);
    }

    /// \brief Determine the TTL of the current RR based on the given
    /// parsing context.
    ///
    /// \c explicit_ttl is true iff the TTL is explicitly specified for that RR
    /// (in which case current_ttl_ is set to that TTL).
    /// \c rrtype is the type of the current RR, and \c rdata is its RDATA.  They
    /// only matter if the type is SOA and no available TTL is known.  In this
    /// case the minimum TTL of the SOA will be used as the TTL of that SOA
    /// and the default TTL for subsequent RRs.
    const RRTTL& getCurrentTTL(bool explicit_ttl, const RRType& rrtype,
                               const rdata::ConstRdataPtr& rdata) {
        // We've completed parsing the full of RR, and the lexer is already
        // positioned at the next line.  If we need to call callback,
        // we need to adjust the line number.
        const size_t current_line = lexer_.getSourceLine() - 1;

        if (!current_ttl_ && !default_ttl_) {
            if (rrtype == RRType::SOA()) {
                callbacks_.warning(lexer_.getSourceName(), current_line,
                                   "no TTL specified; "
                                   "using SOA MINTTL instead");
                const uint32_t ttl_val =
                    dynamic_cast<const rdata::generic::SOA&>(*rdata).
                    getMinimum();
                setDefaultTTL(RRTTL(ttl_val), true);
                assignTTL(current_ttl_, *default_ttl_);
            } else {
                // On catching the exception we'll try to reach EOL again,
                // so we need to unget it now.
                lexer_.ungetToken();
                throw InternalException(__FILE__, __LINE__,
                                        "no TTL specified; load rejected");
            }
        } else if (!explicit_ttl && default_ttl_) {
            assignTTL(current_ttl_, *default_ttl_);
        } else if (!explicit_ttl && warn_rfc1035_ttl_) {
            // Omitted (class and) TTL values are default to the last
            // explicitly stated values (RFC 1035, Sec. 5.1).
            callbacks_.warning(lexer_.getSourceName(), current_line,
                               "using RFC1035 TTL semantics; default to the "
                               "last explicitly stated TTL");
            warn_rfc1035_ttl_ = false; // we only warn about this once
        }
        assert(current_ttl_);
        return (*current_ttl_);
    }

    /// \brief Handle a $DIRECTIVE
    ///
    /// This method is called when a $DIRECTIVE is encountered in the
    /// input stream.
    void handleDirective(const char* directive, size_t length) {
        if (iequals(directive, "INCLUDE")) {
            doInclude();
        } else if (iequals(directive, "ORIGIN")) {
            doOrigin(false);
            eatUntilEOL(true);
        } else if (iequals(directive, "GENERATE")) {
            doGenerate();
            eatUntilEOL(true);
        } else if (iequals(directive, "TTL")) {
            setDefaultTTL(RRTTL(getString()), false);
            eatUntilEOL(true);
        } else {
            isc_throw(InternalException, "Unknown directive '" <<
                      string(directive, directive + length) << "'");
        }
    }

    /// \brief Skip tokens until end-of-line.
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

    /// \brief Assign the right RRTTL's value to the left RRTTL. If one
    /// doesn't exist in the scoped_ptr, make a new RRTTL copy of the
    /// right argument.
    static void assignTTL(boost::scoped_ptr<RRTTL>& left, const RRTTL& right) {
        if (!left) {
            left.reset(new RRTTL(right));
        } else {
            *left = right;
        }
    }

private:
    MasterLexer lexer_;
    const Name zone_origin_;
    Name active_origin_; // The origin used during parsing
                         // (modifiable by $ORIGIN)
    shared_ptr<Name> last_name_; // Last seen name (for INITIAL_WS handling)
    const RRClass zone_class_;
    MasterLoaderCallbacks callbacks_;
    const AddRRCallback add_callback_;
    boost::scoped_ptr<RRTTL> default_ttl_; // Default TTL of RRs used when
                                           // unspecified.  If NULL no default
                                           // is known.
    boost::scoped_ptr<RRTTL> current_ttl_; // The TTL used most recently.
                                           // Initially unset. Once set
                                           // always stores a valid
                                           // RRTTL.
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
    bool warn_rfc1035_ttl_;     // should warn if implicit TTL determination
                                // from the previous RR is used.
    size_t rr_count_;    // number of RRs successfully loaded
};

namespace { // begin unnamed namespace

/// \brief Generate a dotted nibble sequence.
///
/// This method generates a dotted nibble sequence and returns it as a
/// string. The nibbles are appended from the least significant digit
/// (in hex representation of \c num) to the most significant digit with
/// dots ('.') to separate the digits. If \c width is non-zero and the
/// dotted nibble sequence has not filled the requested width, the rest
/// of the width is filled with a dotted nibble sequence of 0 nibbles.
///
/// Some sample representations:
///
/// num = 0x1234, width = 0
/// "4.3.2.1"
///
/// num = 0x1234, width = 1
/// "4.3.2.1"
///
/// num = 0x1234, width = 8
/// "4.3.2.1"
///
/// num = 0x1234, width = 9
/// "4.3.2.1."
///
/// num = 0x1234, width = 10
/// "4.3.2.1.0"
///
/// num = 0x1234, width = 11
/// "4.3.2.1.0."
///
/// num = 0xabcd, width = 0, uppercase = true
/// "D.C.B.A"
///
/// num = 0, width = 0
/// "0"
///
/// num = 0, width = 1
/// "0"
///
/// num = 0, width = 2
/// "0."
///
/// num = 0, width = 3
/// "0.0"
///
/// \param num The number for which the dotted nibble sequence should be
/// generated.
/// \param width The width of the generated string. This is only
/// meaningful when it is larger than the dotted nibble sequence
/// representation of \c num.
/// \param uppercase Whether to use uppercase characters in nibble
/// sequence.
/// \return A string containing the dotted nibble sequence.
std::string
genNibbles(int num, unsigned int width, bool uppercase) {
    static const char *hex = "0123456789abcdef0123456789ABCDEF";
    std::string rstr;

    do {
        char ch = hex[(num & 0x0f) + (uppercase ? 16 : 0)];
        num >>= 4;
        rstr.push_back(ch);

        if (width > 0) {
            --width;
        }

        // If width is non zero then we need to add a label separator.
        // If value is non zero then we need to add another label and
        // that requires a label separator.
        if (width > 0 || num != 0) {
            rstr.push_back('.');

            if (width > 0) {
                --width;
            }
        }
    } while ((num != 0) || (width > 0));

    return (rstr);
}

} // end unnamed namespace

std::string
MasterLoader::MasterLoaderImpl::generateForIter(const std::string& str,
                                                const int num)
{
  std::string rstr;

  for (std::string::const_iterator it = str.begin(); it != str.end();) {
      switch (*it) {
      case '$':
          // This is the case when the '$' character is encountered in
          // the LHS or RHS. A computed value is added in its place in
          // the generated string.
          ++it;
          if ((it != str.end()) && (*it == '$')) {
              rstr.push_back('$');
              ++it;
              continue;
          }

          // The str.end() check is required.
          if ((it == str.end()) || (*it != '{')) {
              // There is no modifier (between {}), so just copy the
              // passed number into the generated string.
              rstr += boost::str(boost::format("%d") % num);
          } else {
              // There is a modifier (between {}). Parse it and handle
              // the various cases below.
              const char* scan_str =
                  str.c_str() + std::distance(str.begin(), it);
              int offset = 0;
              unsigned int width;
              char base[2] = {'d', 0}; // char plus null byte
              // cppcheck-suppress invalidscanf_libc
              const int n = sscanf(scan_str, "{%d,%u,%1[doxXnN]}",
                                   &offset, &width, base);
              switch (n) {
              case 1:
                  // Only 1 item was matched (the offset). Copy (num +
                  // offset) into the generated string.
                  rstr += boost::str(boost::format("%d") % (num + offset));
                  break;

              case 2: {
                  // 2 items were matched (the offset and width). Copy
                  // (num + offset) and format it according to the width
                  // into the generated string.
                  const std::string fmt =
                      boost::str(boost::format("%%0%ud") % width);
                  rstr += boost::str(boost::format(fmt) % (num + offset));
                  break;
              }

              case 3:
                  // 3 items were matched (offset, width and base).
                  if ((base[0] == 'n') || (base[0] == 'N')) {
                      // The base is requesting nibbles. Format it
                      // specially (see genNibbles() documentation).
                      rstr += genNibbles(num + offset, width, (base[0] == 'N'));
                  } else {
                      // The base is not requesting nibbles. Copy (num +
                      // offset) and format it according to the width
                      // and base into the generated string.
                      const std::string fmt =
                          boost::str(boost::format("%%0%u%c") % width % base[0]);
                      rstr += boost::str(boost::format(fmt) % (num + offset));
                  }
                  break;

              default:
                  // Any other case in the modifiers is an error.
                  reportError(lexer_.getSourceName(), lexer_.getSourceLine(),
                              "Invalid $GENERATE format modifiers");
                  return ("");
              }

              // Find the closing brace. Careful that 'it' can be equal
              // to str.end() here.
              while ((it != str.end()) && (*it != '}')) {
                  ++it;
              }
              // Skip past the closing brace (if there is one).
              if (it != str.end()) {
                  ++it;
              }
          }
          break;

      case '\\':
          // This is the case when the '\' character is encountered in
          // the LHS or RHS. The '\' and the following character are
          // copied as-is into the generated string. This is usually
          // used for escaping the $ character.
          rstr.push_back(*it);
          ++it;
          if (it == str.end()) {
              continue;
          }
          rstr.push_back(*it);
          ++it;
          break;

      default:
          // This is the default case that handles all other
          // characters. They are copied as-is into the generated
          // string.
          rstr.push_back(*it);
          ++it;
          break;
      }
  }

  return (rstr);
}

void
MasterLoader::MasterLoaderImpl::doGenerate() {
    // Parse the range token
    const MasterToken& range_token = lexer_.getNextToken(MasterToken::STRING);
    if (range_token.getType() != MasterToken::STRING) {
        reportError(lexer_.getSourceName(), lexer_.getSourceLine(),
                    "Invalid $GENERATE syntax");
        return;
    }
    const std::string range = range_token.getString();

    // Parse the LHS token
    const MasterToken& lhs_token = lexer_.getNextToken(MasterToken::STRING);
    if (lhs_token.getType() != MasterToken::STRING) {
        reportError(lexer_.getSourceName(), lexer_.getSourceLine(),
                    "Invalid $GENERATE syntax");
        return;
    }
    const std::string lhs = lhs_token.getString();

    // Parse the TTL, RR class and RR type tokens. Note that TTL and RR
    // class may come in any order, or may be missing (either or
    // both). If TTL is missing, we expect that it was either specified
    // explicitly using $TTL, or is implicitly known from a previous RR,
    // or that this is the SOA RR from which the MINIMUM field is
    // used. It's unlikely that $GENERATE will be used with an SOA RR,
    // but it's possible. The parsing happens within the parseRRParams()
    // helper method which is called below.
    const MasterToken& param_token = lexer_.getNextToken(MasterToken::STRING);
    if (param_token.getType() != MasterToken::STRING) {
        reportError(lexer_.getSourceName(), lexer_.getSourceLine(),
                    "Invalid $GENERATE syntax");
        return;
    }

    bool explicit_ttl = false;
    const RRType rrtype = parseRRParams(explicit_ttl, param_token);

    // Parse the RHS token. It can be a quoted string.
    const MasterToken& rhs_token = lexer_.getNextToken(MasterToken::QSTRING);
    if ((rhs_token.getType() != MasterToken::QSTRING) &&
        (rhs_token.getType() != MasterToken::STRING))
    {
        reportError(lexer_.getSourceName(), lexer_.getSourceLine(),
                    "Invalid $GENERATE syntax");
        return;
    }
    const std::string rhs = rhs_token.getString();

    // Range can be one of two forms: start-stop or start-stop/step. If
    // the first form is used, then step is set to 1. All of start, stop
    // and step must be positive.
    unsigned int start;
    unsigned int stop;
    unsigned int step;
    // cppcheck-suppress invalidscanf_libc
    const int n = sscanf(range.c_str(), "%u-%u/%u", &start, &stop, &step);
    if ((n < 2) || (stop < start)) {
        reportError(lexer_.getSourceName(), lexer_.getSourceLine(),
                    "$GENERATE: invalid range: " + range);
        return;
    }

    if (n == 2) {
        step = 1;
    }

    // Generate and add the records.
    for (unsigned int i = start; i <= stop; i += step) {
        // Get generated strings for LHS and RHS. LHS goes to form the
        // name, RHS goes to form the RDATA of the RR.
        const std::string generated_name = generateForIter(lhs, i);
        const std::string generated_rdata = generateForIter(rhs, i);
        if (generated_name.empty() || generated_rdata.empty()) {
            // The error should have been sent to the callbacks already
            // by generateForIter().
            reportError(lexer_.getSourceName(), lexer_.getSourceLine(),
                        "$GENERATE error");
            return;
        }

        // generateForIter() can return a string with a trailing '.' in
        // case of a nibble representation. So we cannot use the
        // relative Name constructor. We use concatenate() which is
        // expensive, but keeps the generated LHS-based Name within the
        // active origin.
        last_name_.reset
            (new Name(Name(generated_name).concatenate(active_origin_)));
        previous_name_ = true;

        const rdata::RdataPtr rdata =
            rdata::createRdata(rrtype, zone_class_, generated_rdata);
        // In case we get NULL, it means there was error creating the
        // Rdata. The errors should have been reported by callbacks_
        // already. We need to decide if we want to continue or not.
        if (rdata) {
            add_callback_(*last_name_, zone_class_, rrtype,
                          getCurrentTTL(explicit_ttl, rrtype, rdata),
                          rdata);
            // Good, we added another one
            ++rr_count_;
        } else {
            seen_error_ = true;
            if (!many_errors_) {
                ok_ = false;
                complete_ = true;
                // We don't have the exact error here, but it was
                // reported by the error callback.
                isc_throw(MasterLoaderError, "Invalid RR data");
            }
        }
    }
}

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
            callbacks_.warning(lexer_.getSourceName(), lexer_.getSourceLine(),
                               "Owner name omitted around $INCLUDE, the result "
                               "might not be as expected");
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
            // So continue to the next line of that source, but first, make
            // sure the source is at EOL
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
        pushSource(master_file_, active_origin_);
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

            bool explicit_ttl = false;
            const RRType rrtype = parseRRParams(explicit_ttl, next_token);
            // TODO: Check if it is SOA, it should be at the origin.

            const rdata::RdataPtr rdata =
                rdata::createRdata(rrtype, zone_class_, lexer_,
                                   &active_origin_, options_, callbacks_);

            // In case we get NULL, it means there was error creating
            // the Rdata. The errors should have been reported by
            // callbacks_ already. We need to decide if we want to continue
            // or not.
            if (rdata) {
                add_callback_(*last_name_, zone_class_, rrtype,
                              getCurrentTTL(explicit_ttl, rrtype, rdata),
                              rdata);
                // Good, we loaded another one
                ++count;
                ++rr_count_;
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
        } catch (const isc::dns::DNSTextError& e) {
            reportError(lexer_.getSourceName(), lexer_.getSourceLine(),
                        e.what());
            eatUntilEOL(false);
        } catch (const MasterLexer::ReadError& e) {
            reportError(lexer_.getSourceName(), lexer_.getSourceLine(),
                        e.what());
            eatUntilEOL(false);
        } catch (const MasterLexer::LexerError& e) {
            reportError(lexer_.getSourceName(), lexer_.getSourceLine(),
                        e.what());
            eatUntilEOL(false);
        } catch (const InternalException& e) {
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

size_t
MasterLoader::getSize() const {
    return (impl_->getSize());
}

size_t
MasterLoader::getPosition() const {
    return (impl_->getPosition());
}

} // end namespace dns
} // end namespace isc
