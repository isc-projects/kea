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

// $Id$

#include <dns/name.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>
#include <dns/rrsetlist.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>

#include "data_source.h"
#include "data_source_static.h"

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace isc {
namespace auth {

// There's no mutable internal state in StaticDataSrcImpl, so define it
// as a struct.

namespace {

// All data in this class is literally static and can be generated at
// initialization time (and won't be changed).  Names can be statically
// initialized.  For RRsets, a helper class (StaticDataInitializer) and its
// only instance will be used for initialization.
const Name authors_name("authors.bind");
const Name version_name("version.bind");
// XXX: unfortunately these can't be RRsetPtr because they'll be passed to
// RRsetList::addRRset(), which expect non const RRsetPtr.  We should revisit
// this design later.
RRsetPtr authors;
RRsetPtr authors_ns;
RRsetPtr version;
RRsetPtr version_ns;

class StaticDataInitializer {
public:
    StaticDataInitializer()
    {
        authors = RRsetPtr(new RRset(authors_name, RRClass::CH(),
                                     RRType::TXT(), RRTTL(0)));
        authors->addRdata(generic::TXT("Evan Hunt"));
        authors->addRdata(generic::TXT("Han Feng"));
        authors->addRdata(generic::TXT("Jelte Jansen"));
        authors->addRdata(generic::TXT("Jeremy C. Reed")); 
        authors->addRdata(generic::TXT("Jin Jian"));
        authors->addRdata(generic::TXT("JINMEI Tatuya"));
        authors->addRdata(generic::TXT("Kazunori Fujiwara"));
        authors->addRdata(generic::TXT("Michael Graff"));
        authors->addRdata(generic::TXT("Naoki Kambe"));
        authors->addRdata(generic::TXT("Shane Kerr"));
        authors->addRdata(generic::TXT("Zhang Likun"));

        authors_ns = RRsetPtr(new RRset(authors_name, RRClass::CH(),
                                        RRType::NS(), RRTTL(0)));
        authors_ns->addRdata(generic::NS(authors_name));

        version = RRsetPtr(new RRset(version_name, RRClass::CH(),
                                     RRType::TXT(), RRTTL(0)));
        version->addRdata(generic::TXT("BIND10 0.0.0 (pre-alpha)"));

        version_ns = RRsetPtr(new RRset(version_name, RRClass::CH(),
                                        RRType::NS(), RRTTL(0)));
        version_ns->addRdata(generic::NS(version_name));
    }
};
const StaticDataInitializer initialier_object;
}

StaticDataSrc::StaticDataSrc()
{
    setClass(RRClass::CH());
}

void
StaticDataSrc::findClosestEnclosure(NameMatch& match) const {
    const Name& qname = match.qname();
    NameComparisonResult::NameRelation cmp;

    cmp = qname.compare(version_name).getRelation();
    if (cmp == NameComparisonResult::EQUAL ||
        cmp == NameComparisonResult::SUBDOMAIN) {
        match.update(*this, version_name);
        return;
    }

    cmp = qname.compare(authors_name).getRelation();
    if (cmp == NameComparisonResult::EQUAL ||
        cmp == NameComparisonResult::SUBDOMAIN) {
        match.update(*this, authors_name);
        return;
    }
}

DataSrc::Result
StaticDataSrc::findRRset(const Query& q, const Name& qname,
                         const RRClass& qclass, const RRType& qtype,
                         RRsetList& target, uint32_t& flags,
                         const Name* zonename) const
{
    flags = 0;
    if (qclass != getClass()) {
        return (ERROR);
    }

    bool any = (qtype == RRType::ANY());

    if (qname == version_name) {
        if (qtype == RRType::TXT() || any) {
            target.addRRset(version);
        } else if (qtype == RRType::NS()) {
            target.addRRset(version_ns);
        } else {
            flags = TYPE_NOT_FOUND;
        }
    } else if (qname == authors_name) {
        if (qtype == RRType::TXT() || any) {
            target.addRRset(authors);
            return (SUCCESS);
        } else if (qtype == RRType::NS()) {
            target.addRRset(authors_ns);
            return (SUCCESS);
        } else {
            flags = TYPE_NOT_FOUND;
        }
    } else {
        flags = NAME_NOT_FOUND;
    }

    return (SUCCESS);
}

DataSrc::Result
StaticDataSrc::findExactRRset(const Query& q, const Name& qname,
                              const RRClass& qclass, const RRType& qtype,
                              RRsetList& target, uint32_t& flags,
                              const Name* zonename) const
{
    return (findRRset(q, qname, qclass, qtype, target, flags, zonename));
}

DataSrc::Result
StaticDataSrc::findPreviousName(const Query& q, const Name& qname,
                                Name& target, const Name* zonename) const
{
    return (NOT_IMPLEMENTED);
}

DataSrc::Result
StaticDataSrc::findCoveringNSEC3(const Query& q, const Nsec3Param& param,
                                 const Name& qname, const Name& zonename,
                                 RRsetList& target) const
{
   return (NOT_IMPLEMENTED);
}

DataSrc::Result
StaticDataSrc::init()
{
    return (SUCCESS);
}

DataSrc::Result
StaticDataSrc::close()
{
    return (SUCCESS);
}

}
}
