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

#ifndef ZONE_CHECKER_H
#define ZONE_CHECKER_H 1

#include <dns/dns_fwd.h>

#include <boost/function.hpp>

#include <string>

namespace isc {
namespace dns {

/// \brief Set of callbacks used in zone checks.
///
/// Objects of this class are expected to be passed to \c checkZone().
class ZoneCheckerCallbacks {
public:
    /// \brief Functor type of the callback on some issue (error or warning).
    ///
    /// Its parameter indicates the reason for the corresponding issue.
    typedef boost::function<void(const std::string& reason)> IssueCallback;

    /// \brief Default constructor.
    ///
    /// This is a convenient shortcut to specify callbacks that do nothing.
    /// If, for example, the caller of \c checkZone() is only interested in
    /// the final result, it can use this constructor.
    ///
    /// \throw none
    ZoneCheckerCallbacks() :
        error_callback_(nullCallback), warn_callback_(nullCallback)
    {}

    /// \brief Constructor with callbacks.
    ///
    /// \throw none
    ///
    /// \param error_callback Callback functor to be called on critical errors.
    /// \param warn_callback Callback functor to be called on non critical
    ///                               issues.
    ZoneCheckerCallbacks(const IssueCallback& error_callback,
                         const IssueCallback& warn_callback) :
        error_callback_(error_callback), warn_callback_(warn_callback)
    {}

    /// \brief Call the callback for a critical error.
    ///
    /// This method itself is exception free, but propagates any exception
    /// thrown from the callback.
    ///
    /// \param reason Textual representation of the reason for the error.
    void error(const std::string& reason) { error_callback_(reason); }

    /// \brief Call the callback for a non critical issue.
    ///
    /// This method itself is exception free, but propagates any exception
    /// thrown from the callback.
    ///
    /// \param reason Textual representation of the reason for the issue.
    void warn(const std::string& reason) { warn_callback_(reason); }

private:
    static void nullCallback(const std::string&) {}

    IssueCallback error_callback_;
    IssueCallback warn_callback_;
};

/// \brief Perform basic integrity checks on zone RRsets.
///
/// This function performs some lightweight checks on zone's SOA and (apex)
/// NS records.  Here, lightweight means it doesn't require traversing
/// the entire zone, and should be expected to complete reasonably quickly
/// regardless of the size of the zone.
///
/// It distinguishes "critical" errors and other undesirable issues:
/// the former should be interpreted as the resulting zone shouldn't be used
/// further, e.g, by an authoritative server implementation; the latter means
/// the issues are better to be addressed but are not necessarily considered
/// to make the zone invalid.  Critical errors are reported via the
/// \c error() method of \c callbacks, and non critical issues are reported
/// via its \c warn() method.
///
/// Specific checks performed by this function is as follows:
/// - There is exactly one SOA RR at the zone apex.
/// - There is at least one NS RR at the zone apex.
/// - For each apex NS record, if the NS name (the RDATA of the record) is
///   in the zone (i.e., it's a subdomain of the zone origin and above any
///   zone cut due to delegation), check the following:
///   - the NS name should have an address record (AAAA or A).  Failure of
///     this check is considered a non critical issue.
///   - the NS name does not have a CNAME.  This is prohibited by Section
///     10.3 of RFC 2181.
///   - the NS name is not subject to DNAME substitution.  This is prohibited
///     by Section 4 of RFC 6672.
///   .
///
/// In addition, when the check is completed without any critical error, this
/// function guarantees that RRsets for the SOA and (apex) NS stored in the
/// passed RRset collection have the expected type of Rdata objects,
/// i.e., generic::SOA and generic::NS, respectively.  (This is normally
/// expected to be the case, but not guaranteed by the API).
///
/// As for the check on the existence of AAAA or A records for NS names,
/// it should be noted that BIND 9 treats this as a critical error.
/// It's not clear whether it's an implementation dependent behavior or
/// based on the protocol standard (it looks like the former), but to make
/// it sure we need to confirm there is even no wildcard match for the names.
/// This should be a very rare configuration, and more expensive to detect,
/// so we do not check this condition, and treat this case as a non critical
/// issue.
///
/// This function indicates the result of the checks (whether there is a
/// critical error) via the return value: It returns \c true if there is no
/// critical error and returns \c false otherwise.  It doesn't throw an
/// exception on encountering an error so that it can report as many errors
/// as possible in a single call.  If an exception is a better way to signal
/// the error, the caller can pass a callback object that throws from its
/// \c error() method.
///
/// This function can still throw an exception if it finds a really bogus
/// condition that is most likely to be an implementation bug of the caller.
/// Such cases include when an RRset contained in the RRset collection is
/// empty.
///
/// \throw Unexpected Conditions that suggest a caller's bug (see the
/// description)
///
/// \param zone_name The name of the zone to be checked
/// \param zone_class The RR class of the zone to be checked
/// \param zone_rrsets The collection of RRsets of the zone
/// \param callbacks Callback object used to report errors and issues
///
/// \return \c true if no critical errors are found; \c false otherwise.
bool
checkZone(const Name& zone_name, const RRClass& zone_class,
          const RRsetCollectionBase& zone_rrsets,
          const ZoneCheckerCallbacks& callbacks = ZoneCheckerCallbacks());

} // namespace dns
} // namespace isc
#endif  // ZONE_CHECKER_H

// Local Variables:
// mode: c++
// End:
