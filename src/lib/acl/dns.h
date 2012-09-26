// Copyright (C) 2011  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef ACL_DNS_H
#define ACL_DNS_H 1

#include <string>
#include <vector>

#include <boost/shared_ptr.hpp>

#include <cc/data.h>

#include <acl/ip_check.h>
#include <acl/dnsname_check.h>
#include <acl/loader.h>

namespace isc {
namespace dns {
class TSIGRecord;
}
namespace acl {
namespace dns {

/**
 * \brief DNS request to be checked.
 *
 * This plays the role of Context of the generic template ACLs (in namespace
 * isc::acl).
 *
 * It is a simple structure holding just the bunch of information. Therefore
 * the names don't end up with an underscore; there are no methods so they
 * can't be confused with local variables.
 *
 * This structure is generally expected to be ephemeral and read-only: It
 * would be constructed immediately before a particular ACL is checked
 * and used only for the ACL match purposes.  Due to this nature, and since
 * ACL processing is often performance sensitive (typically it's performed
 * against all incoming packets), the construction is designed to be
 * lightweight: it tries to avoid expensive data copies or dynamic memory
 * allocation as much as possible.  Specifically, the constructor can
 * take a pointer or reference to an object and keeps it as a reference
 * (not making a local copy).  This also means the caller is responsible for
 * keeping the passed parameters valid while this structure is used.
 * This should generally be reasonable as this structure is expected to be
 * used only for a very short period as stated above.
 *
 * Based on the minimalist philosophy, the initial implementation only
 * maintains the remote (source) IP address of the request and (optionally)
 * the TSIG record included in the request.  We may add more parameters of
 * the request as we see the need for them.  Possible additional parameters
 * are the local (destination) IP address, the remote and local port numbers,
 * various fields of the DNS request (e.g. a particular header flag value).
 */
struct RequestContext {
    /// The constructor
    ///
    /// This is a trivial constructor that perform straightforward
    /// initialization of the member variables from the given parameters.
    ///
    /// \exception None
    ///
    /// \param remote_address_param The remote IP address
    /// \param tsig_param A valid pointer to the TSIG record included in
    /// the request or NULL if the request doesn't contain a TSIG.
    RequestContext(const IPAddress& remote_address_param,
                   const isc::dns::TSIGRecord* tsig_param) :
        remote_address(remote_address_param),
        tsig(tsig_param)
    {}

    ///
    /// \name Parameter variables
    ///
    /// These member variables must be immutable so that the integrity of
    /// the structure is kept throughout its lifetime.  The easiest way is
    /// to declare the variable as const.  If it's not possible for a
    /// particular variable, it must be defined as private and accessible
    /// only via an accessor method.
    //@{
    /// \brief The remote IP address (eg. the client's IP address).
    const IPAddress& remote_address;

    /// \brief The TSIG record included in the request message, if any.
    ///
    /// If the request doesn't include a TSIG, this member will be NULL.
    const isc::dns::TSIGRecord* const tsig;
    //@}
};

/// \brief DNS based check.
typedef acl::Check<RequestContext> RequestCheck;
/// \brief DNS based compound check.
typedef acl::CompoundCheck<RequestContext> CompoundCheck;
/// \brief DNS based ACL.
typedef acl::ACL<RequestContext> RequestACL;
/// \brief DNS based ACL loader.
typedef acl::Loader<RequestContext> RequestLoader;

/**
 * \brief Loader singleton access function.
 *
 * This function returns a loader of ACLs. It is expected applications
 * will use this function instead of creating their own loaders, because
 * one is enough, this one will have registered default checks and it
 * is known one, so any plugins can registrer additional checks as well.
 */
RequestLoader& getRequestLoader();

// The following is essentially private to the implementation and could
// be hidden in the implementation file.  But it's visible via this header
// file for testing purposes.  They are not supposed to be used by normal
// applications directly, and to signal the intent, they are given inside
// a separate namespace.
namespace internal {

// Shortcut typedef
typedef isc::acl::IPCheck<RequestContext> RequestIPCheck;
typedef isc::acl::dns::NameCheck<RequestContext> RequestKeyCheck;

class RequestCheckCreator : public acl::Loader<RequestContext>::CheckCreator {
public:
    virtual std::vector<std::string> names() const;

    virtual boost::shared_ptr<RequestCheck>
    create(const std::string& name, isc::data::ConstElementPtr definition,
           const acl::Loader<RequestContext>& loader);
};
} // end of namespace "internal"

} // end of namespace "dns"
} // end of namespace "acl"
} // end of namespace "isc"

#endif

// Local Variables:
// mode: c++
// End:
