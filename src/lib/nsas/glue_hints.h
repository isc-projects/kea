// Copyright (C) 2010  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef GLUE_HINTS_H
#define GLUE_HINTS_H

#include <vector>

#include <dns/message.h>

#include "nsas_types.h"
#include "nameserver_address.h"

namespace isc {
namespace nsas {

class GlueHints {
public:
    /// \brief Empty constructor
    GlueHints() {};

    /// \brief Constructor
    ///
    /// Creates a glue hint object, with the glue data found in the
    /// given packet.
    ///
    /// \param zone_name The name of the zone to find glue for
    /// \param delegation_message The Message that may contain glue
    GlueHints(const std::string& zone_name,
              const isc::dns::Message& delegation_message);

    /// \brief Check if there is glue for the given AddressFamily
    ///
    /// \param family the AddressFamily to check for glue for
    /// \return true if there is glue for that family. false if not
    bool hasGlue(AddressFamily family) const;

    /// \brief Get a random glue address for the given family
    ///
    /// ONLY call this if hasGlue() returned true.
    ///
    /// \param family the AddressFamily to get glue for
    /// \return a NameserverAddress specified by the glue
    NameserverAddress getGlue(AddressFamily family) const;

private:
    void addGlueForName(const isc::dns::Name& name,
                        const isc::dns::Message& message);
    void addGlueForRRset(const isc::dns::RRsetPtr rrset,
                         const isc::dns::Message& message);

    std::vector<NameserverAddress> addresses_v4;
    std::vector<NameserverAddress> addresses_v6;
};

}
}


#endif // GLUE_HINTS_H
