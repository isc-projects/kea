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

#include <config.h>

#include <cassert>

#include <dns/name.h>
#include <dns/rdataclass.h>
#include <dns/rrclass.h>
#include <dns/rrset.h>
#include <dns/rrsetlist.h>
#include <dns/rrtype.h>
#include <dns/rrttl.h>

#include <datasrc/data_source.h>
#include <datasrc/static_datasrc.h>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace isc {
namespace datasrc {

// This class stores the "static" data for the built-in static data source.
// Since it's static, it could be literally static, i.e, defined as static
// objects.  But to avoid the static initialization order fiasco, which would
// be unlikely to happen for this class in practice but is still possible,
// we took a safer approach.  A downside of this approach is that redundant
// copies of exactly the same content of these objects can be created.
// In practice, however, there's normally at most one StaticDataSrc object,
// so this should be acceptable (if this turns out to be a real concern we
// might consider making this class a singleton).
// We use the "pimpl" idiom for this class.  Operations for this class is
// not expected to be performance sensitive, so the overhead due to the pimpl
// should be okay, and it's more beneficial to hide details and minimize
// inter module dependencies in header files.
struct StaticDataSrcImpl {
public:
    StaticDataSrcImpl();
    const Name authors_name;
    const Name version_name;
    // XXX: unfortunately these can't be ConstRRsetPtr because they'll be
    // passed to RRsetList::addRRset(), which expect non const RRsetPtr.
    // We should revisit this design later.
    RRsetPtr authors;
    RRsetPtr authors_ns;
    RRsetPtr authors_soa;
    RRsetPtr version;
    RRsetPtr version_ns;
    RRsetPtr version_soa;
};

StaticDataSrcImpl::StaticDataSrcImpl() :
    authors_name("authors.bind"), version_name("version.bind")
{
    authors = RRsetPtr(new RRset(authors_name, RRClass::CH(),
                                 RRType::TXT(), RRTTL(0)));
    authors->addRdata(generic::TXT("Chen Zhengzhang")); // Jerry
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
    authors->addRdata(generic::TXT("Shen Tingting"));
    authors->addRdata(generic::TXT("Stephen Morris"));
    authors->addRdata(generic::TXT("Zhang Likun"));

    authors_ns = RRsetPtr(new RRset(authors_name, RRClass::CH(),
                                    RRType::NS(), RRTTL(0)));
    authors_ns->addRdata(generic::NS(authors_name));

    authors_soa = RRsetPtr(new RRset(authors_name, RRClass::CH(),
                                     RRType::SOA(), RRTTL(0)));
    authors_soa->addRdata(generic::SOA(
                              "authors.bind. hostmaster.authors.bind. "
                              "0 28800 7200 604800 86400"));

    version = RRsetPtr(new RRset(version_name, RRClass::CH(),
                                 RRType::TXT(), RRTTL(0)));
    version->addRdata(generic::TXT(PACKAGE_STRING));

    version_ns = RRsetPtr(new RRset(version_name, RRClass::CH(),
                                    RRType::NS(), RRTTL(0)));
    version_ns->addRdata(generic::NS(version_name));

    version_soa = RRsetPtr(new RRset(version_name, RRClass::CH(),
                                     RRType::SOA(), RRTTL(0)));
    version_soa->addRdata(generic::SOA(
                              "version.bind. hostmaster.version.bind. "
                               "0 28800 7200 604800 86400"));
}

StaticDataSrc::StaticDataSrc()
{
    setClass(RRClass::CH());
    impl_ = new StaticDataSrcImpl;
}

StaticDataSrc::~StaticDataSrc()
{
    delete impl_;
}

namespace {
bool
isSubdomain(const Name& qname, const Name& zone) {
    const NameComparisonResult::NameRelation cmp =
        qname.compare(zone).getRelation();
    return (cmp == NameComparisonResult::EQUAL ||
            cmp == NameComparisonResult::SUBDOMAIN);
}
}

void
StaticDataSrc::findClosestEnclosure(DataSrcMatch& match) const {
    const Name& qname = match.getName();

    if (match.getClass() != getClass() && match.getClass() != RRClass::ANY()) {
        return;
    }

    if (isSubdomain(qname, impl_->version_name)) {
        match.update(*this, impl_->version_name);
        return;
    }

    if (isSubdomain(qname, impl_->authors_name)) {
        match.update(*this, impl_->authors_name);
        return;
    }
}

DataSrc::Result
StaticDataSrc::findRRset(const Name& qname,
                         const RRClass& qclass, const RRType& qtype,
                         RRsetList& target, uint32_t& flags,
                         const Name* const zonename) const
{
    flags = 0;
    if (qclass != getClass() && qclass != RRClass::ANY()) {
        return (ERROR);
    }

    // Identify the appropriate zone.
    bool is_versionname = false, is_authorsname = false;
    if (zonename != NULL) {
        if (*zonename == impl_->version_name &&
            isSubdomain(qname, impl_->version_name)) {
            is_versionname = true;
        } else if (*zonename == impl_->authors_name &&
                   isSubdomain(qname, impl_->authors_name)) {
            is_authorsname = true;
        } else {
            flags = NO_SUCH_ZONE;
            return (SUCCESS);
        }
    } else {
        if (isSubdomain(qname, impl_->version_name)) {
            is_versionname = true;
        } else if (isSubdomain(qname, impl_->authors_name)) {
            is_authorsname = true;
        } else {
            flags = NO_SUCH_ZONE;
            return (SUCCESS);
        }
    }

    const bool any = (qtype == RRType::ANY());

    if (is_versionname) {
        if (qname == impl_->version_name) {
            if (qtype == RRType::TXT() || any) {
                target.addRRset(impl_->version);
            }
            if (qtype == RRType::NS() || any) {
                target.addRRset(impl_->version_ns);
            }
            if (qtype == RRType::SOA() || any) {
                target.addRRset(impl_->version_soa);
            }
            if (target.size() == 0) {
                flags = TYPE_NOT_FOUND;
            }
        } else {
            flags = NAME_NOT_FOUND;
        }
    } else {
        assert(is_authorsname);
        if (qname == impl_->authors_name) {
            if (qtype == RRType::TXT() || any) {
                target.addRRset(impl_->authors);
            }
            if (qtype == RRType::NS() || any) {
                target.addRRset(impl_->authors_ns);
            }
            if (qtype == RRType::SOA() || any) {
                target.addRRset(impl_->authors_soa);
            }
            if (target.size() == 0 ) {
                flags = TYPE_NOT_FOUND;
            }
        } else {
            flags = NAME_NOT_FOUND;
        }
    }

    return (SUCCESS);
}

DataSrc::Result
StaticDataSrc::findExactRRset(const Name& qname,
                              const RRClass& qclass, const RRType& qtype,
                              RRsetList& target, uint32_t& flags,
                              const Name* zonename) const
{
    return (findRRset(qname, qclass, qtype, target, flags, zonename));
}

DataSrc::Result
StaticDataSrc::findPreviousName(const Name& qname UNUSED_PARAM,
                                Name& target UNUSED_PARAM,
                                const Name* zonename UNUSED_PARAM) const
{
    return (NOT_IMPLEMENTED);
}

DataSrc::Result
StaticDataSrc::findCoveringNSEC3(const Name& zonename UNUSED_PARAM,
                                 string& hash UNUSED_PARAM,
                                 RRsetList& target UNUSED_PARAM) const
{
   return (NOT_IMPLEMENTED);
}

DataSrc::Result
StaticDataSrc::init() {
    return (SUCCESS);
}

// Static data source is "configuration less", so the \c config parameter
// is intentionally ignored.
DataSrc::Result
StaticDataSrc::init(isc::data::ConstElementPtr config UNUSED_PARAM) {
    return (init());
}

DataSrc::Result
StaticDataSrc::close() {
    return (SUCCESS);
}

}
}
