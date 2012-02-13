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

#include <sstream>
#include <vector>
#include <map>

#include <boost/bind.hpp>
#include <boost/scoped_ptr.hpp>

#include <exceptions/exceptions.h>

#include <dns/masterload.h>
#include <dns/message.h>
#include <dns/name.h>
#include <dns/opcode.h>
#include <dns/rcode.h>
#include <dns/rrttl.h>
#include <dns/rrtype.h>
#include <dns/rdataclass.h>

#include <datasrc/memory_datasrc.h>

#include <auth/query.h>

#include <testutils/dnsmessage_test.h>

#include <gtest/gtest.h>

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;
using namespace isc::datasrc;
using namespace isc::auth;
using namespace isc::testutils;

namespace {

// This is the content of the mock zone (see below).
// It's a sequence of textual RRs that is supposed to be parsed by
// dns::masterLoad().  Some of the RRs are also used as the expected
// data in specific tests, in which case they are referenced via specific
// local variables (such as soa_txt).
const char* const soa_txt = "example.com. 3600 IN SOA . . 0 0 0 0 0\n";
const char* const zone_ns_txt =
    "example.com. 3600 IN NS glue.delegation.example.com.\n"
    "example.com. 3600 IN NS noglue.example.com.\n"
    "example.com. 3600 IN NS example.net.\n";
const char* const ns_addrs_txt =
    "glue.delegation.example.com. 3600 IN A 192.0.2.153\n"
    "glue.delegation.example.com. 3600 IN AAAA 2001:db8::53\n"
    "noglue.example.com. 3600 IN A 192.0.2.53\n";
const char* const delegation_txt =
    "delegation.example.com. 3600 IN NS glue.delegation.example.com.\n"
    "delegation.example.com. 3600 IN NS noglue.example.com.\n"
    "delegation.example.com. 3600 IN NS cname.example.com.\n"
    "delegation.example.com. 3600 IN NS example.org.\n";
const char* const mx_txt =
    "mx.example.com. 3600 IN MX 10 www.example.com.\n"
    "mx.example.com. 3600 IN MX 20 mailer.example.org.\n"
    "mx.example.com. 3600 IN MX 30 mx.delegation.example.com.\n";
const char* const www_a_txt = "www.example.com. 3600 IN A 192.0.2.80\n";
const char* const cname_txt =
    "cname.example.com. 3600 IN CNAME www.example.com.\n";
const char* const cname_nxdom_txt =
    "cnamenxdom.example.com. 3600 IN CNAME nxdomain.example.com.\n";
// CNAME Leading out of zone
const char* const cname_out_txt =
    "cnameout.example.com. 3600 IN CNAME www.example.org.\n";
// The DNAME to do tests against
const char* const dname_txt =
    "dname.example.com. 3600 IN DNAME "
    "somethinglong.dnametarget.example.com.\n";
// Some data at the dname node (allowed by RFC 2672)
const char* const dname_a_txt =
    "dname.example.com. 3600 IN A 192.0.2.5\n";
// This is not inside the zone, this is created at runtime
const char* const synthetized_cname_txt =
    "www.dname.example.com. 3600 IN CNAME "
    "www.somethinglong.dnametarget.example.com.\n";
// The rest of data won't be referenced from the test cases.
const char* const other_zone_rrs =
    "cnamemailer.example.com. 3600 IN CNAME www.example.com.\n"
    "cnamemx.example.com. 3600 IN MX 10 cnamemailer.example.com.\n"
    "mx.delegation.example.com. 3600 IN A 192.0.2.100\n";
// Wildcards
const char* const wild_txt = "*.wild.example.com. 3600 IN A 192.0.2.7\n";
const char* const nsec_wild_txt =
    "*.wild.example.com. 3600 IN NSEC www.example.com. A NSEC RRSIG\n";
const char* const cnamewild_txt =
    "*.cnamewild.example.com. 3600 IN CNAME www.example.org.\n";
const char* const nsec_cnamewild_txt = "*.cnamewild.example.com. "
    "3600 IN NSEC delegation.example.com. CNAME NSEC RRSIG\n";
// Wildcard_nxrrset
const char* const wild_txt_nxrrset =
    "*.uwild.example.com. 3600 IN A 192.0.2.9\n";
const char* const nsec_wild_txt_nxrrset =
    "*.uwild.example.com. 3600 IN NSEC www.uwild.example.com. A NSEC RRSIG\n";
const char* const wild_txt_next =
    "www.uwild.example.com. 3600 IN A 192.0.2.11\n";
const char* const nsec_wild_txt_next =
    "www.uwild.example.com. 3600 IN NSEC *.wild.example.com. A NSEC RRSIG\n";
// Wildcard empty
const char* const empty_txt = "b.*.t.example.com. 3600 IN A 192.0.2.13\n";
const char* const nsec_empty_txt =
    "b.*.t.example.com. 3600 IN NSEC *.uwild.example.com. A NSEC RRSIG\n";
const char* const empty_prev_txt = "t.example.com. 3600 IN A 192.0.2.15\n";
const char* const nsec_empty_prev_txt =
    "t.example.com. 3600 IN NSEC b.*.t.example.com. A NSEC RRSIG\n";
// Used in NXDOMAIN proof test.  We are going to test some unusual case where
// the best possible wildcard is below the "next domain" of the NSEC RR that
// proves the NXDOMAIN, i.e.,
// mx.example.com. (exist)
// (.no.example.com. (qname, NXDOMAIN)
// ).no.example.com. (exist)
// *.no.example.com. (best possible wildcard, not exist)
const char* const no_txt =
    ").no.example.com. 3600 IN AAAA 2001:db8::53\n";
// NSEC records.
const char* const nsec_apex_txt =
    "example.com. 3600 IN NSEC cname.example.com. NS SOA NSEC RRSIG\n";
const char* const nsec_mx_txt =
    "mx.example.com. 3600 IN NSEC ).no.example.com. MX NSEC RRSIG\n";
const char* const nsec_no_txt =
    ").no.example.com. 3600 IN NSEC nz.no.example.com. AAAA NSEC RRSIG\n";
// We'll also test the case where a single NSEC proves both NXDOMAIN and the
// non existence of wildcard.  The following records will be used for that
// test.
// ).no.example.com. (exist, whose NSEC proves everything)
// *.no.example.com. (best possible wildcard, not exist)
// nx.no.example.com. (NXDOMAIN)
// nz.no.example.com. (exist)
const char* const nz_txt =
    "nz.no.example.com. 3600 IN AAAA 2001:db8::5300\n";
const char* const nsec_nz_txt =
    "nz.no.example.com. 3600 IN NSEC noglue.example.com. AAAA NSEC RRSIG\n";
const char* const nsec_nxdomain_txt =
    "noglue.example.com. 3600 IN NSEC nonsec.example.com. A\n";

// NSEC for the normal NXRRSET case
const char* const nsec_www_txt =
    "www.example.com. 3600 IN NSEC example.com. A NSEC RRSIG\n";

// Authoritative data without NSEC
const char* const nonsec_a_txt = "nonsec.example.com. 3600 IN A 192.0.2.0\n";

// NSEC3 RRs.  You may also need to add mapping to MockZoneFinder::hash_map_.
const char* const nsec3_apex_txt =
    "0p9mhaveqvm6t7vbl5lop2u3t2rp3tom.example.com. 3600 IN NSEC3 1 1 12 "
    "aabbccdd 2t7b4g4vsa5smi47k61mv5bv1a22bojr NS SOA NSEC3PARAM RRSIG\n";
const char* const nsec3_www_txt =
    "q04jkcevqvmu85r014c7dkba38o0ji5r.example.com. 3600 IN NSEC3 1 1 12 "
    "aabbccdd r53bq7cc2uvmubfu5ocmm6pers9tk9en A RRSIG\n";

// (Secure) delegation data; Delegation with DS record
const char* const signed_delegation_txt =
    "signed-delegation.example.com. 3600 IN NS ns.example.net.\n";
const char* const signed_delegation_ds_txt =
    "signed-delegation.example.com. 3600 IN DS 12345 8 2 "
    "764501411DE58E8618945054A3F620B36202E115D015A7773F4B78E0F952CECA\n";

// (Secure) delegation data; Delegation without DS record (and NSEC denying
// its existence.
const char* const unsigned_delegation_txt =
    "unsigned-delegation.example.com. 3600 IN NS ns.example.net.\n";
const char* const unsigned_delegation_nsec_txt =
    "unsigned-delegation.example.com. 3600 IN NSEC "
    "*.uwild.example.com. NS RRSIG NSEC\n";

// (Secure) delegation data; Delegation where the DS lookup will raise an
// exception.
const char* const bad_delegation_txt =
    "bad-delegation.example.com. 3600 IN NS ns.example.net.\n";


// A helper function that generates a textual representation of RRSIG RDATA
// for the given covered type.  The resulting RRSIG may not necessarily make
// sense in terms of the DNSSEC protocol, but for our testing purposes it's
// okay.
string
getCommonRRSIGText(const string& type) {
    return (type +
            string(" 5 3 3600 20000101000000 20000201000000 12345 "
                   "example.com. FAKEFAKEFAKE"));
}

// This is a mock Zone Finder class for testing.
// It is a derived class of ZoneFinder for the convenient of tests.
// Its find() method emulates the common behavior of protocol compliant
// ZoneFinder classes, but simplifies some minor cases and also supports broken
// behavior.
// For simplicity, most names are assumed to be "in zone"; there's only
// one zone cut at the point of name "delegation.example.com".
// Another special name is "dname.example.com".  Query names under this name
// will result in DNAME.
// This mock zone doesn't handle empty non terminal nodes (if we need to test
// such cases find() should have specialized code for it).
class MockZoneFinder : public ZoneFinder {
public:
    MockZoneFinder() :
        origin_(Name("example.com")),
        delegation_name_("delegation.example.com"),
        signed_delegation_name_("signed-delegation.example.com"),
        bad_signed_delegation_name_("bad-delegation.example.com"),
        unsigned_delegation_name_("unsigned-delegation.example.com"),
        dname_name_("dname.example.com"),
        has_SOA_(true),
        has_apex_NS_(true),
        rrclass_(RRClass::IN()),
        include_rrsig_anyway_(false),
        use_nsec3_(false),
        nsec_name_(origin_),
        nsec3_fake_(NULL)
    {
        stringstream zone_stream;
        zone_stream << soa_txt << zone_ns_txt << ns_addrs_txt <<
            delegation_txt << mx_txt << www_a_txt << cname_txt <<
            cname_nxdom_txt << cname_out_txt << dname_txt <<
            dname_a_txt << other_zone_rrs << no_txt << nz_txt <<
            nsec_apex_txt << nsec_mx_txt << nsec_no_txt << nsec_nz_txt <<
            nsec_nxdomain_txt << nsec_www_txt << nonsec_a_txt <<
            wild_txt << nsec_wild_txt << cnamewild_txt << nsec_cnamewild_txt <<
            wild_txt_nxrrset << nsec_wild_txt_nxrrset << wild_txt_next <<
            nsec_wild_txt_next << empty_txt << nsec_empty_txt <<
            empty_prev_txt << nsec_empty_prev_txt <<
            nsec3_apex_txt << nsec3_www_txt <<
            signed_delegation_txt << signed_delegation_ds_txt <<
            unsigned_delegation_txt << unsigned_delegation_nsec_txt <<
            bad_delegation_txt;

        masterLoad(zone_stream, origin_, rrclass_,
                   boost::bind(&MockZoneFinder::loadRRset, this, _1));

        empty_nsec_rrset_ = ConstRRsetPtr(new RRset(Name::ROOT_NAME(),
                                                    RRClass::IN(),
                                                    RRType::NSEC(),
                                                    RRTTL(3600)));

        // (Faked) NSEC3 hash map.  For convenience we use hardcoded built-in
        // map instead of calculating and using actual hash.
        // The used hash values are borrowed from RFC5155 examples (they are
        // based on the query name, not that they would correspond directly
        // to the name).
        hash_map_[Name("example.com")] = "0p9mhaveqvm6t7vbl5lop2u3t2rp3tom";
        hash_map_[Name("www.example.com")] =
            "q04jkcevqvmu85r014c7dkba38o0ji5r";
        hash_map_[Name("nxdomain.example.com")] =
            "v644ebqk9bibcna874givr6joj62mlhv";
        hash_map_[Name("nx.domain.example.com")] =
            "v644ebqk9bibcna874givr6joj62mlhv";
        hash_map_[Name("domain.example.com")] =
            "v644ebqk9bibcna874givr6joj62mlhv";
        hash_map_[Name("nxdomain2.example.com")] =
            "q00jkcevqvmu85r014c7dkba38o0ji5r";
        hash_map_[Name("nxdomain3.example.com")] =
            "009mhaveqvm6t7vbl5lop2u3t2rp3tom";
    }
    virtual isc::dns::Name getOrigin() const { return (origin_); }
    virtual isc::dns::RRClass getClass() const { return (rrclass_); }
    virtual FindResult find(const isc::dns::Name& name,
                            const isc::dns::RRType& type,
                            const FindOptions options = FIND_DEFAULT);
    virtual FindResult findAll(const isc::dns::Name& name,
                               std::vector<ConstRRsetPtr>& target,
                               const FindOptions options = FIND_DEFAULT);

    virtual ZoneFinder::FindNSEC3Result
    findNSEC3(const Name& name, bool recursive);

    // If false is passed, it makes the zone broken as if it didn't have the
    // SOA.
    void setSOAFlag(bool on) { has_SOA_ = on; }

    // If false is passed, it makes the zone broken as if it didn't have
    // the apex NS.
    void setApexNSFlag(bool on) { has_apex_NS_ = on; }

    // Turn this on if you want it to return RRSIGs regardless of FIND_GLUE_OK
    void setIncludeRRSIGAnyway(bool on) { include_rrsig_anyway_ = on; }

    // Once called, this "faked" result will be returned when NSEC is expected
    // for the specified query name.
    void setNSECResult(const Name& nsec_name, Result code,
                       ConstRRsetPtr rrset)
    {
        nsec_name_ = nsec_name;
        nsec_result_.reset(new ZoneFinder::FindResult(code, rrset));
    }

    // Once called, the findNSEC3 will return the provided result for the next
    // query. After that, it'll return to operate normally.
    // NULL disables. Does not take ownership of the pointer (it is generally
    // expected to be a local variable in the test function).
    void setNSEC3Result(const FindNSEC3Result* result) {
        nsec3_fake_ = result;
    }

    // If true is passed return an empty NSEC3 RRset for some negative
    // answers when DNSSEC is required.
    void setNSEC3Flag(bool on) { use_nsec3_ = on; }

    Name findPreviousName(const Name&) const {
        isc_throw(isc::NotImplemented, "Mock doesn't support previous name");
    }

public:
    // We allow the tests to use these for convenience
    ConstRRsetPtr delegation_rrset_;
    ConstRRsetPtr signed_delegation_rrset_;
    ConstRRsetPtr signed_delegation_ds_rrset_;
    ConstRRsetPtr bad_signed_delegation_rrset_;
    ConstRRsetPtr unsigned_delegation_rrset_;
    ConstRRsetPtr empty_nsec_rrset_;

private:
    typedef map<RRType, ConstRRsetPtr> RRsetStore;
    typedef map<Name, RRsetStore> Domains;
    Domains domains_;
    Domains nsec3_domains_;
    void loadRRset(RRsetPtr rrset) {
        if (rrset->getType() == RRType::NSEC3()) {
            // NSEC3 should go to the dedicated table
            nsec3_domains_[rrset->getName()][rrset->getType()] = rrset;

            // By nature it should have RRSIG.  (We may want to selectively
            // omit this to test pathological cases).
            rrset->addRRsig(RdataPtr(new generic::RRSIG(
                                         getCommonRRSIGText(rrset->getType().
                                                            toText()))));
            return;
        }
        domains_[rrset->getName()][rrset->getType()] = rrset;
        if (rrset->getName() == delegation_name_ &&
            rrset->getType() == RRType::NS()) {
            delegation_rrset_ = rrset;
        } else if (rrset->getName() == signed_delegation_name_ &&
                   rrset->getType() == RRType::NS()) {
            signed_delegation_rrset_ = rrset;
        } else if (rrset->getName() == bad_signed_delegation_name_ &&
                   rrset->getType() == RRType::NS()) {
            bad_signed_delegation_rrset_ = rrset;
        } else if (rrset->getName() == unsigned_delegation_name_ &&
                   rrset->getType() == RRType::NS()) {
            unsigned_delegation_rrset_ = rrset;
        } else if (rrset->getName() == signed_delegation_name_ &&
                   rrset->getType() == RRType::DS()) {
            signed_delegation_ds_rrset_ = rrset;
            // Like NSEC(3), by nature it should have an RRSIG.
            rrset->addRRsig(RdataPtr(new generic::RRSIG(
                                         getCommonRRSIGText(rrset->getType().
                                                            toText()))));
        } else if (rrset->getName() == dname_name_ &&
            rrset->getType() == RRType::DNAME()) {
            dname_rrset_ = rrset;
        // Add some signatures
        } else if (rrset->getName() == Name("example.com.") &&
                   rrset->getType() == RRType::NS()) {
            // For NS, we only have RRSIG for the origin name.
            rrset->addRRsig(RdataPtr(new generic::RRSIG(
                                         getCommonRRSIGText("NS"))));
        } else {
            // For others generate RRSIG unconditionally.  Technically this
            // is wrong because we shouldn't have it for names under a zone
            // cut.  But in our tests that doesn't matter, so we add them
            // just for simplicity.
            rrset->addRRsig(RdataPtr(new generic::RRSIG(
                                         getCommonRRSIGText(rrset->getType().
                                                            toText()))));
        }
    }

    const Name origin_;
    // Names where we delegate somewhere else
    const Name delegation_name_;
    const Name signed_delegation_name_;
    const Name bad_signed_delegation_name_;
    const Name unsigned_delegation_name_;
    const Name dname_name_;
    bool has_SOA_;
    bool has_apex_NS_;
    ConstRRsetPtr dname_rrset_;
    const RRClass rrclass_;
    bool include_rrsig_anyway_;
    bool use_nsec3_;
    // The following two will be used for faked NSEC cases
    Name nsec_name_;
    boost::scoped_ptr<ZoneFinder::FindResult> nsec_result_;
    // The following two are for faking bad NSEC3 responses
    // Enabled when not NULL
    const FindNSEC3Result* nsec3_fake_;
public:
    // Public, to allow tests looking up the right names for something
    map<Name, string> hash_map_;
};

// A helper function that generates a new RRset based on "wild_rrset",
// replacing its owner name with 'real_name'.
ConstRRsetPtr
substituteWild(const AbstractRRset& wild_rrset, const Name& real_name) {
    RRsetPtr rrset(new RRset(real_name, wild_rrset.getClass(),
                             wild_rrset.getType(), wild_rrset.getTTL()));
    // For simplicity we only consider the case with one RDATA (for now)
    rrset->addRdata(wild_rrset.getRdataIterator()->getCurrent());
    ConstRRsetPtr wild_sig = wild_rrset.getRRsig();
    if (wild_sig) {
        RRsetPtr sig(new RRset(real_name, wild_sig->getClass(),
                               wild_sig->getType(), wild_sig->getTTL()));
        sig->addRdata(wild_sig->getRdataIterator()->getCurrent());
        rrset->addRRsig(sig);
    }
    return (rrset);
}

ZoneFinder::FindResult
MockZoneFinder::findAll(const Name& name, std::vector<ConstRRsetPtr>& target,
                        const FindOptions options)
{
    ZoneFinder::FindResult result(find(name, RRType::ANY(), options));
    if (result.code == NXRRSET) {
        const Domains::const_iterator found_domain = domains_.find(name);
        if (!found_domain->second.empty()) {
            for (RRsetStore::const_iterator found_rrset =
                 found_domain->second.begin();
                 found_rrset != found_domain->second.end(); ++found_rrset) {
                // Insert RRs under the domain name into target
                target.push_back(found_rrset->second);
            }
            return (FindResult(SUCCESS, RRsetPtr()));
        }
    }

    return (result);
}

ZoneFinder::FindNSEC3Result
MockZoneFinder::findNSEC3(const Name& name, bool recursive) {
    // Do we have a fake result set? If so, use it.
    if (nsec3_fake_ != NULL) {
        const FindNSEC3Result* result(nsec3_fake_);
        // Disable the fake for the next call
        nsec3_fake_ = NULL;
        return (*result);
    }

    ConstRRsetPtr covering_proof;
    const int labels = name.getLabelCount();

    // For brevity, we assume several things below: maps should have an
    // expected entry when operator[] is used; maps are not empty.
    for (int i = 0; i < labels; ++i) {
        const string hlabel = hash_map_[name.split(i, labels - i)];
        const Name hname = Name(hlabel + ".example.com");
        // We don't use const_iterator so that we can use operator[] below
        Domains::iterator found_domain = nsec3_domains_.lower_bound(hname);

        // If the given hash is larger than the largest stored hash or
        // the first label doesn't match the target, identify the "previous"
        // hash value and remember it as the candidate next closer proof.
        if (found_domain == nsec3_domains_.end() ||
            found_domain->first.split(0, 1).toText(true) != hlabel) {
            // If the given hash is larger or smaller than everything,
            // the covering proof is the NSEC3 that has the largest hash.
            if (found_domain == nsec3_domains_.end() ||
                found_domain == nsec3_domains_.begin()) {
                covering_proof =
                    nsec3_domains_.rbegin()->second[RRType::NSEC3()];
            } else {
                // Otherwise, H(found_domain-1) < given_hash < H(found_domain)
                // The covering proof is the first one.
                covering_proof = (--found_domain)->second[RRType::NSEC3()];
            }
            if (!recursive) {   // in non recursive mode, we are done.
                return (ZoneFinder::FindNSEC3Result(false,
                                                    name.getLabelCount(),
                                                    covering_proof,
                                                    ConstRRsetPtr()));
            }
        } else {                // exact match
            return (ZoneFinder::FindNSEC3Result(
                        true, name.getLabelCount() - i,
                        found_domain->second[RRType::NSEC3()],
                        covering_proof));
        }
    }
    isc_throw(isc::Unexpected, "findNSEC3() isn't expected to fail");
}

ZoneFinder::FindResult
MockZoneFinder::find(const Name& name, const RRType& type,
                     const FindOptions options)
{
    // Emulating a broken zone: mandatory apex RRs are missing if specifically
    // configured so (which are rare cases).
    if (name == origin_ && type == RRType::SOA() && !has_SOA_) {
        return (FindResult(NXDOMAIN, RRsetPtr()));
    } else if (name == origin_ && type == RRType::NS() && !has_apex_NS_) {
        return (FindResult(NXDOMAIN, RRsetPtr()));
    }

    // Special case for names on or under a zone cut
    if ((options & FIND_GLUE_OK) == 0 &&
        (name == delegation_name_ ||
         name.compare(delegation_name_).getRelation() ==
         NameComparisonResult::SUBDOMAIN)) {
        return (FindResult(DELEGATION, delegation_rrset_));
    // And under DNAME
    } else if (name.compare(dname_name_).getRelation() ==
        NameComparisonResult::SUBDOMAIN) {
        if (type != RRType::DS()) {
            return (FindResult(DNAME, dname_rrset_));
        }
    } else if (name == signed_delegation_name_ ||
               name.compare(signed_delegation_name_).getRelation() ==
               NameComparisonResult::SUBDOMAIN) {
        if (type != RRType::DS()) {
            return (FindResult(DELEGATION, signed_delegation_rrset_));
        } else {
            return (FindResult(SUCCESS, signed_delegation_ds_rrset_));
        }
    } else if (name == unsigned_delegation_name_ ||
               name.compare(unsigned_delegation_name_).getRelation() ==
               NameComparisonResult::SUBDOMAIN) {
        if (type != RRType::DS()) {
            return (FindResult(DELEGATION, unsigned_delegation_rrset_));
        }
    } else if (name == bad_signed_delegation_name_ ||
               name.compare(bad_signed_delegation_name_).getRelation() ==
               NameComparisonResult::SUBDOMAIN) {
        if (type != RRType::DS()) {
            return (FindResult(DELEGATION, bad_signed_delegation_rrset_));
        } else {
            return (FindResult(NXDOMAIN, RRsetPtr()));
        }
    }

    // normal cases.  names are searched for only per exact-match basis
    // for simplicity.
    const Domains::const_iterator found_domain = domains_.find(name);
    if (found_domain != domains_.end()) {
        // First, try exact match.
        RRsetStore::const_iterator found_rrset =
            found_domain->second.find(type);
        if (found_rrset != found_domain->second.end()) {
            ConstRRsetPtr rrset;
            // Strip whatever signature there is in case DNSSEC is not required
            // Just to make sure the Query asks for it when it is needed
            if ((options & ZoneFinder::FIND_DNSSEC) != 0 ||
                include_rrsig_anyway_ ||
                !found_rrset->second->getRRsig()) {
                rrset = found_rrset->second;
            } else {
                RRsetPtr noconst(new RRset(found_rrset->second->getName(),
                                           found_rrset->second->getClass(),
                                           found_rrset->second->getType(),
                                           found_rrset->second->getTTL()));
                for (RdataIteratorPtr
                     i(found_rrset->second->getRdataIterator());
                     !i->isLast(); i->next()) {
                    noconst->addRdata(i->getCurrent());
                }
                rrset = noconst;
            }
            return (FindResult(SUCCESS, rrset));
        }

        // Otherwise, if this domain name has CNAME, return it.
        found_rrset = found_domain->second.find(RRType::CNAME());
        if (found_rrset != found_domain->second.end()) {
            return (FindResult(CNAME, found_rrset->second));
        }

        // Otherwise it's NXRRSET case.
        if ((options & FIND_DNSSEC) != 0) {
            if (use_nsec3_) {
                return (FindResult(NXRRSET, RRsetPtr(), RESULT_NSEC3_SIGNED));
            }
            found_rrset = found_domain->second.find(RRType::NSEC());
            if (found_rrset != found_domain->second.end()) {
                return (FindResult(NXRRSET, found_rrset->second,
                                   RESULT_NSEC_SIGNED));
            }
        }
        return (FindResult(NXRRSET, RRsetPtr(), RESULT_NSEC_SIGNED));
    }

    // query name isn't found in our domains.
    // We first check if the query name is an empty non terminal name
    // of the zone by naive linear search.
    Domains::const_iterator domain;
    for (domain = domains_.begin(); domain != domains_.end(); ++domain) {
        if (name.compare((*domain).first).getRelation() ==
            NameComparisonResult::SUPERDOMAIN) {
            break;
        }
    }
    if (domain != domains_.end()) {
        // The query name is in an empty non terminal node followed by 'domain'
        // (for simplicity we ignore the pathological case of 'domain' is
        // the origin of the zone)
        --domain;               // reset domain to the "previous name"
        if ((options & FIND_DNSSEC) != 0) {
            if (use_nsec3_) {
                return (FindResult(NXRRSET, RRsetPtr(), RESULT_NSEC3_SIGNED));
            }
            RRsetStore::const_iterator found_rrset =
                (*domain).second.find(RRType::NSEC());
            if (found_rrset != (*domain).second.end()) {
                return (FindResult(NXRRSET, found_rrset->second,
                                   RESULT_NSEC_SIGNED));
            }
        }
        return (FindResult(NXRRSET, RRsetPtr()));
    }

    // Another possibility is wildcard.  For simplicity we only check
    // hardcoded specific cases, ignoring other details such as canceling
    // due to the existence of closer name.
    if ((options & NO_WILDCARD) == 0) {
        const Name wild_suffix(name.split(1));
        // Unit Tests use those domains for Wildcard test.
        if (name.equals(Name("www.wild.example.com"))||
           name.equals(Name("www1.uwild.example.com"))||
           name.equals(Name("a.t.example.com"))) {
            if (name.compare(wild_suffix).getRelation() ==
                NameComparisonResult::SUBDOMAIN) {
                domain = domains_.find(Name("*").concatenate(wild_suffix));
                // Matched the QNAME
                if (domain != domains_.end()) {
                    RRsetStore::const_iterator found_rrset =
                        domain->second.find(type);
                    // Matched the QTYPE
                    if(found_rrset != domain->second.end()) {
                        return (FindResult(SUCCESS,
                                           substituteWild(
                                               *found_rrset->second, name),
                                           RESULT_WILDCARD |
                                           (use_nsec3_ ?
                                            RESULT_NSEC3_SIGNED :
                                            RESULT_NSEC_SIGNED)));
                    } else {
                        // No matched QTYPE, this case is for WILDCARD_NXRRSET
                        if (use_nsec3_) {
                            return (FindResult(NXRRSET, RRsetPtr(),
                                               RESULT_WILDCARD |
                                               RESULT_NSEC3_SIGNED));
                        }
                        const Name new_name =
                            Name("*").concatenate(wild_suffix);
                        found_rrset = domain->second.find(RRType::NSEC());
                        assert(found_rrset != domain->second.end());
                        return (FindResult(NXRRSET,
                                           substituteWild(
                                               *found_rrset->second,
                                               new_name),
                                           RESULT_WILDCARD |
                                           RESULT_NSEC_SIGNED));
                    }
                } else {
                    // This is empty non terminal name case on wildcard.
                    const Name empty_name = Name("*").concatenate(wild_suffix);
                    if (use_nsec3_) {
                        return (FindResult(NXRRSET, RRsetPtr(),
                                           RESULT_WILDCARD |
                                           RESULT_NSEC3_SIGNED));
                    }
                    for (Domains::reverse_iterator it = domains_.rbegin();
                         it != domains_.rend();
                         ++it) {
                        RRsetStore::const_iterator nsec_it;
                        if ((*it).first < empty_name &&
                            (nsec_it = (*it).second.find(RRType::NSEC()))
                            != (*it).second.end()) {
                            return (FindResult(NXRRSET, (*nsec_it).second,
                                               RESULT_WILDCARD |
                                               RESULT_NSEC_SIGNED));
                        }
                    }
                }
                return (FindResult(NXRRSET, RRsetPtr(), RESULT_WILDCARD));
             }
        }
        const Name cnamewild_suffix("cnamewild.example.com");
        if (name.compare(cnamewild_suffix).getRelation() ==
            NameComparisonResult::SUBDOMAIN) {
            domain = domains_.find(Name("*").concatenate(cnamewild_suffix));
            assert(domain != domains_.end());
            RRsetStore::const_iterator found_rrset =
                domain->second.find(RRType::CNAME());
            assert(found_rrset != domain->second.end());
            return (FindResult(CNAME,
                               substituteWild(*found_rrset->second, name),
                               RESULT_WILDCARD |
                               (use_nsec3_ ? RESULT_NSEC3_SIGNED :
                                RESULT_NSEC_SIGNED)));
        }
    }

    // This is an NXDOMAIN case.
    // If we need DNSSEC proof, find the "previous name" that has an NSEC RR
    // and return NXDOMAIN with the found NSEC.  Otherwise, just return the
    // NXDOMAIN code and NULL.  If DNSSEC proof is requested but no NSEC is
    // found, we return NULL, too.  (For simplicity under the test conditions
    // we don't care about pathological cases such as the name is "smaller"
    // than the origin)
    if ((options & FIND_DNSSEC) != 0) {
        if (use_nsec3_) {
            return (FindResult(NXDOMAIN, RRsetPtr(), RESULT_NSEC3_SIGNED));
        }

        // Emulate a broken DataSourceClient for some special names.
        if (nsec_result_ && nsec_name_ == name) {
            return (*nsec_result_);
        }

        // Normal case
        // XXX: some older g++ complains about operator!= if we use
        // const_reverse_iterator
        for (Domains::reverse_iterator it = domains_.rbegin();
             it != domains_.rend();
             ++it) {
            RRsetStore::const_iterator nsec_it;
            if ((*it).first < name &&
                (nsec_it = (*it).second.find(RRType::NSEC()))
                != (*it).second.end()) {
                return (FindResult(NXDOMAIN, (*nsec_it).second,
                                   RESULT_NSEC_SIGNED));
            }
        }
    }
    return (FindResult(NXDOMAIN, RRsetPtr()));
}

class QueryTest : public ::testing::Test {
protected:
    QueryTest() :
        qname(Name("www.example.com")), qclass(RRClass::IN()),
        qtype(RRType::A()), response(Message::RENDER),
        qid(response.getQid()), query_code(Opcode::QUERY().getCode())
    {
        response.setRcode(Rcode::NOERROR());
        response.setOpcode(Opcode::QUERY());
        // create and add a matching zone.
        mock_finder = new MockZoneFinder();
        memory_client.addZone(ZoneFinderPtr(mock_finder));
    }
    MockZoneFinder* mock_finder;
    // We use InMemoryClient here. We could have some kind of mock client
    // here, but historically, the Query supported only InMemoryClient
    // (originally named MemoryDataSrc) and was tested with it, so we keep
    // it like this for now.
    InMemoryClient memory_client;
    const Name qname;
    const RRClass qclass;
    const RRType qtype;
    Message response;
    const qid_t qid;
    const uint16_t query_code;
};

// A wrapper to check resulting response message commonly used in
// tests below.
// check_origin needs to be specified only when the authority section has
// an SOA RR.  The interface is not generic enough but should be okay
// for our test cases in practice.
void
responseCheck(Message& response, const isc::dns::Rcode& rcode,
              unsigned int flags, const unsigned int ancount,
              const unsigned int nscount, const unsigned int arcount,
              const char* const expected_answer,
              const char* const expected_authority,
              const char* const expected_additional,
              const Name& check_origin = Name::ROOT_NAME())
{
    // In our test cases QID, Opcode, and QDCOUNT should be constant, so
    // we don't bother the test cases specifying these values.
    headerCheck(response, response.getQid(), rcode, Opcode::QUERY().getCode(),
                flags, 0, ancount, nscount, arcount);
    if (expected_answer != NULL) {
        rrsetsCheck(expected_answer,
                    response.beginSection(Message::SECTION_ANSWER),
                    response.endSection(Message::SECTION_ANSWER),
                    check_origin);
    }
    if (expected_authority != NULL) {
        rrsetsCheck(expected_authority,
                    response.beginSection(Message::SECTION_AUTHORITY),
                    response.endSection(Message::SECTION_AUTHORITY),
                    check_origin);
    }
    if (expected_additional != NULL) {
        rrsetsCheck(expected_additional,
                    response.beginSection(Message::SECTION_ADDITIONAL),
                    response.endSection(Message::SECTION_ADDITIONAL));
    }
}

TEST_F(QueryTest, noZone) {
    // There's no zone in the memory datasource.  So the response should have
    // REFUSED.
    InMemoryClient empty_memory_client;
    Query nozone_query(empty_memory_client, qname, qtype, response);
    EXPECT_NO_THROW(nozone_query.process());
    EXPECT_EQ(Rcode::REFUSED(), response.getRcode());
}

TEST_F(QueryTest, exactMatch) {
    Query query(memory_client, qname, qtype, response);
    EXPECT_NO_THROW(query.process());
    // find match rrset
    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 3,
                  www_a_txt, zone_ns_txt, ns_addrs_txt);
}

TEST_F(QueryTest, exactMatchIgnoreSIG) {
    // Check that we do not include the RRSIG when not requested even when
    // we receive it from the data source.
    mock_finder->setIncludeRRSIGAnyway(true);
    Query query(memory_client, qname, qtype, response);
    EXPECT_NO_THROW(query.process());
    // find match rrset
    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 3,
                  www_a_txt, zone_ns_txt, ns_addrs_txt);
}

TEST_F(QueryTest, dnssecPositive) {
    // Just like exactMatch, but the signatures should be included as well
    Query query(memory_client, qname, qtype, response, true);
    EXPECT_NO_THROW(query.process());
    // find match rrset
    // We can't let responseCheck to check the additional section as well,
    // it gets confused by the two RRs for glue.delegation.../RRSIG due
    // to it's design and fixing it would be hard. Therefore we simply
    // check manually this one time.
    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 2, 4, 6,
                  (www_a_txt + std::string("www.example.com. 3600 IN RRSIG "
                                           "A 5 3 3600 20000101000000 "
                                           "20000201000000 12345 example.com. "
                                           "FAKEFAKEFAKE\n")).c_str(),
                  (zone_ns_txt + std::string("example.com. 3600 IN RRSIG NS 5 "
                                             "3 3600 20000101000000 "
                                             "20000201000000 12345 "
                                             "example.com. FAKEFAKEFAKE\n")).
                  c_str(), NULL);
    RRsetIterator iterator(response.beginSection(Message::SECTION_ADDITIONAL));
    const char* additional[] = {
        "glue.delegation.example.com. 3600 IN A 192.0.2.153\n",
        "glue.delegation.example.com. 3600 IN RRSIG A 5 3 3600 20000101000000 "
            "20000201000000 12345 example.com. FAKEFAKEFAKE\n",
        "glue.delegation.example.com. 3600 IN AAAA 2001:db8::53\n",
        "glue.delegation.example.com. 3600 IN RRSIG AAAA 5 3 3600 "
            "20000101000000 20000201000000 12345 example.com. FAKEFAKEFAKE\n",
        "noglue.example.com. 3600 IN A 192.0.2.53\n",
        "noglue.example.com. 3600 IN RRSIG A 5 3 3600 20000101000000 "
            "20000201000000 12345 example.com. FAKEFAKEFAKE\n",
        NULL
    };
    for (const char** rr(additional); *rr != NULL; ++ rr) {
        ASSERT_FALSE(iterator ==
                     response.endSection(Message::SECTION_ADDITIONAL));
        EXPECT_EQ(*rr, (*iterator)->toText());
        iterator ++;
    }
    EXPECT_TRUE(iterator == response.endSection(Message::SECTION_ADDITIONAL));
}

TEST_F(QueryTest, exactAddrMatch) {
    // find match rrset, omit additional data which has already been provided
    // in the answer section from the additional.
    EXPECT_NO_THROW(Query(memory_client, Name("noglue.example.com"), qtype,
                          response).process());

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 2,
                  "noglue.example.com. 3600 IN A 192.0.2.53\n", zone_ns_txt,
                  "glue.delegation.example.com. 3600 IN A 192.0.2.153\n"
                  "glue.delegation.example.com. 3600 IN AAAA 2001:db8::53\n");
}

TEST_F(QueryTest, apexNSMatch) {
    // find match rrset, omit authority data which has already been provided
    // in the answer section from the authority section.
    EXPECT_NO_THROW(Query(memory_client, Name("example.com"), RRType::NS(),
                          response).process());

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 3, 0, 3,
                  zone_ns_txt, NULL, ns_addrs_txt);
}

// test type any query logic
TEST_F(QueryTest, exactAnyMatch) {
    // find match rrset, omit additional data which has already been provided
    // in the answer section from the additional.
    EXPECT_NO_THROW(Query(memory_client, Name("noglue.example.com"),
                          RRType::ANY(), response).process());

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 2, 3, 2,
                  (string("noglue.example.com. 3600 IN A 192.0.2.53\n") +
                   string(nsec_nxdomain_txt)).c_str(),
                  zone_ns_txt,
                  "glue.delegation.example.com. 3600 IN A 192.0.2.153\n"
                  "glue.delegation.example.com. 3600 IN AAAA 2001:db8::53\n");
}

TEST_F(QueryTest, apexAnyMatch) {
    // find match rrset, omit additional data which has already been provided
    // in the answer section from the additional.
    EXPECT_NO_THROW(Query(memory_client, Name("example.com"),
                          RRType::ANY(), response).process());
    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 5, 0, 3,
                  (string(soa_txt) + string(zone_ns_txt) +
                   string(nsec_apex_txt)).c_str(),
                  NULL, ns_addrs_txt, mock_finder->getOrigin());
}

TEST_F(QueryTest, mxANYMatch) {
    EXPECT_NO_THROW(Query(memory_client, Name("mx.example.com"),
                          RRType::ANY(), response).process());
    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 4, 3, 4,
                  (string(mx_txt) + string(nsec_mx_txt)).c_str(), zone_ns_txt,
                  (string(ns_addrs_txt) + string(www_a_txt)).c_str());
}

TEST_F(QueryTest, glueANYMatch) {
    EXPECT_NO_THROW(Query(memory_client, Name("delegation.example.com"),
                          RRType::ANY(), response).process());
    responseCheck(response, Rcode::NOERROR(), 0, 0, 4, 3,
                  NULL, delegation_txt, ns_addrs_txt);
}

TEST_F(QueryTest, nodomainANY) {
    EXPECT_NO_THROW(Query(memory_client, Name("nxdomain.example.com"),
                          RRType::ANY(), response).process());
    responseCheck(response, Rcode::NXDOMAIN(), AA_FLAG, 0, 1, 0,
                  NULL, soa_txt, NULL, mock_finder->getOrigin());
}

// This tests that when we need to look up Zone's apex NS records for
// authoritative answer, and there is no apex NS records. It should
// throw in that case.
TEST_F(QueryTest, noApexNS) {
    // Disable apex NS record
    mock_finder->setApexNSFlag(false);

    EXPECT_THROW(Query(memory_client, Name("noglue.example.com"), qtype,
                       response).process(), Query::NoApexNS);
    // We don't look into the response, as it threw
}

TEST_F(QueryTest, delegation) {
    EXPECT_NO_THROW(Query(memory_client, Name("delegation.example.com"),
                          qtype, response).process());

    responseCheck(response, Rcode::NOERROR(), 0, 0, 4, 3,
                  NULL, delegation_txt, ns_addrs_txt);
}

TEST_F(QueryTest, secureDelegation) {
    EXPECT_NO_THROW(Query(memory_client,
                          Name("foo.signed-delegation.example.com"),
                          qtype, response, true).process());

    // Should now contain RRSIG and DS record as well.
    responseCheck(response, Rcode::NOERROR(), 0, 0, 3, 0,
                  NULL,
                  (string(signed_delegation_txt) +
                   string(signed_delegation_ds_txt) +
                   string("signed-delegation.example.com. 3600 IN RRSIG ") +
                   getCommonRRSIGText("DS")).c_str(),
                  NULL);
}

TEST_F(QueryTest, secureUnsignedDelegation) {
    EXPECT_NO_THROW(Query(memory_client,
                          Name("foo.unsigned-delegation.example.com"),
                          qtype, response, true).process());

    // Should now contain RRSIG and NSEC record as well.
    responseCheck(response, Rcode::NOERROR(), 0, 0, 3, 0,
                  NULL,
                  (string(unsigned_delegation_txt) +
                   string(unsigned_delegation_nsec_txt) +
                   string("unsigned-delegation.example.com. 3600 IN RRSIG ") +
                   getCommonRRSIGText("NSEC")).c_str(),
                  NULL);
}

TEST_F(QueryTest, badSecureDelegation) {
    // Test whether exception is raised if DS query at delegation results in
    // something different than SUCCESS or NXRRSET
    EXPECT_THROW(Query(memory_client, Name("bad-delegation.example.com"),
                       qtype, response, true).process(), Query::BadDS);

    // But only if DNSSEC is requested (it shouldn't even try to look for
    // the DS otherwise)
    EXPECT_NO_THROW(Query(memory_client, Name("bad-delegation.example.com"),
                          qtype, response).process());
}


TEST_F(QueryTest, nxdomain) {
    EXPECT_NO_THROW(Query(memory_client, Name("nxdomain.example.com"), qtype,
                          response).process());
    responseCheck(response, Rcode::NXDOMAIN(), AA_FLAG, 0, 1, 0,
                  NULL, soa_txt, NULL, mock_finder->getOrigin());
}

TEST_F(QueryTest, nxdomainWithNSEC) {
    // NXDOMAIN with DNSSEC proof.  We should have SOA, NSEC that proves
    // NXDOMAIN and NSEC that proves nonexistence of matching wildcard,
    // as well as their RRSIGs.
    EXPECT_NO_THROW(Query(memory_client, Name("nxdomain.example.com"), qtype,
                          response, true).process());
    responseCheck(response, Rcode::NXDOMAIN(), AA_FLAG, 0, 6, 0,
                  NULL, (string(soa_txt) +
                         string("example.com. 3600 IN RRSIG ") +
                         getCommonRRSIGText("SOA") + "\n" +
                         string(nsec_nxdomain_txt) + "\n" +
                         string("noglue.example.com. 3600 IN RRSIG ") +
                         getCommonRRSIGText("NSEC") + "\n" +
                         string(nsec_apex_txt) + "\n" +
                         string("example.com. 3600 IN RRSIG ") +
                         getCommonRRSIGText("NSEC")).c_str(),
                  NULL, mock_finder->getOrigin());
}

TEST_F(QueryTest, nxdomainWithNSEC2) {
    // See comments about no_txt.  In this case the best possible wildcard
    // is derived from the next domain of the NSEC that proves NXDOMAIN, and
    // the NSEC to provide the non existence of wildcard is different from
    // the first NSEC.
    Query(memory_client, Name("(.no.example.com"), qtype,
          response, true).process();
    responseCheck(response, Rcode::NXDOMAIN(), AA_FLAG, 0, 6, 0,
                  NULL, (string(soa_txt) +
                         string("example.com. 3600 IN RRSIG ") +
                         getCommonRRSIGText("SOA") + "\n" +
                         string(nsec_mx_txt) + "\n" +
                         string("mx.example.com. 3600 IN RRSIG ") +
                         getCommonRRSIGText("NSEC") + "\n" +
                         string(nsec_no_txt) + "\n" +
                         string(").no.example.com. 3600 IN RRSIG ") +
                         getCommonRRSIGText("NSEC")).c_str(),
                  NULL, mock_finder->getOrigin());
}

TEST_F(QueryTest, nxdomainWithNSECDuplicate) {
    // See comments about nz_txt.  In this case we only need one NSEC,
    // which proves both NXDOMAIN and the non existence of wildcard.
    Query(memory_client, Name("nx.no.example.com"), qtype,
          response, true).process();
    responseCheck(response, Rcode::NXDOMAIN(), AA_FLAG, 0, 4, 0,
                  NULL, (string(soa_txt) +
                         string("example.com. 3600 IN RRSIG ") +
                         getCommonRRSIGText("SOA") + "\n" +
                         string(nsec_no_txt) + "\n" +
                         string(").no.example.com. 3600 IN RRSIG ") +
                         getCommonRRSIGText("NSEC")).c_str(),
                  NULL, mock_finder->getOrigin());
}

TEST_F(QueryTest, nxdomainBadNSEC1) {
    // ZoneFinder::find() returns NXDOMAIN with non NSEC RR.
    mock_finder->setNSECResult(Name("badnsec.example.com"),
                               ZoneFinder::NXDOMAIN,
                               mock_finder->delegation_rrset_);
    EXPECT_THROW(Query(memory_client, Name("badnsec.example.com"), qtype,
                       response, true).process(),
                 std::bad_cast);
}

TEST_F(QueryTest, nxdomainBadNSEC2) {
    // ZoneFinder::find() returns NXDOMAIN with an empty NSEC RR.
    mock_finder->setNSECResult(Name("emptynsec.example.com"),
                               ZoneFinder::NXDOMAIN,
                               mock_finder->empty_nsec_rrset_);
    EXPECT_THROW(Query(memory_client, Name("emptynsec.example.com"), qtype,
                       response, true).process(),
                 Query::BadNSEC);
}

TEST_F(QueryTest, nxdomainBadNSEC3) {
    // "no-wildcard proof" returns SUCCESS.  it should be NXDOMAIN.
    mock_finder->setNSECResult(Name("*.example.com"),
                               ZoneFinder::SUCCESS,
                               mock_finder->delegation_rrset_);
    EXPECT_THROW(Query(memory_client, Name("nxdomain.example.com"), qtype,
                       response, true).process(),
                 Query::BadNSEC);
}

TEST_F(QueryTest, nxdomainBadNSEC4) {
    // "no-wildcard proof" doesn't return RRset.
    mock_finder->setNSECResult(Name("*.example.com"),
                               ZoneFinder::NXDOMAIN, ConstRRsetPtr());
    EXPECT_THROW(Query(memory_client, Name("nxdomain.example.com"), qtype,
                       response, true).process(),
                 Query::BadNSEC);
}

TEST_F(QueryTest, nxdomainBadNSEC5) {
    // "no-wildcard proof" returns non NSEC.
    mock_finder->setNSECResult(Name("*.example.com"),
                               ZoneFinder::NXDOMAIN,
                               mock_finder->delegation_rrset_);
    // This is a bit odd, but we'll simply include the returned RRset.
    Query(memory_client, Name("nxdomain.example.com"), qtype,
          response, true).process();
    responseCheck(response, Rcode::NXDOMAIN(), AA_FLAG, 0, 8, 0,
                  NULL, (string(soa_txt) +
                         string("example.com. 3600 IN RRSIG ") +
                         getCommonRRSIGText("SOA") + "\n" +
                         string(nsec_nxdomain_txt) + "\n" +
                         string("noglue.example.com. 3600 IN RRSIG ") +
                         getCommonRRSIGText("NSEC") + "\n" +
                         delegation_txt).c_str(),
                  NULL, mock_finder->getOrigin());
}

TEST_F(QueryTest, nxdomainBadNSEC6) {
    // "no-wildcard proof" returns empty NSEC.
    mock_finder->setNSECResult(Name("*.example.com"),
                               ZoneFinder::NXDOMAIN,
                               mock_finder->empty_nsec_rrset_);
    EXPECT_THROW(Query(memory_client, Name("nxdomain.example.com"), qtype,
                       response, true).process(),
                 Query::BadNSEC);
}

TEST_F(QueryTest, nxrrset) {
    EXPECT_NO_THROW(Query(memory_client, Name("www.example.com"),
                          RRType::TXT(), response).process());

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 0, 1, 0,
                  NULL, soa_txt, NULL, mock_finder->getOrigin());
}

TEST_F(QueryTest, nxrrsetWithNSEC) {
    // NXRRSET with DNSSEC proof.  We should have SOA, NSEC that proves the
    // NXRRSET and their RRSIGs.
    Query(memory_client, Name("www.example.com"), RRType::TXT(), response,
          true).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 0, 4, 0, NULL,
                  (string(soa_txt) + string("example.com. 3600 IN RRSIG ") +
                   getCommonRRSIGText("SOA") + "\n" +
                   string(nsec_www_txt) + "\n" +
                   string("www.example.com. 3600 IN RRSIG ") +
                   getCommonRRSIGText("NSEC")).c_str(),
                  NULL, mock_finder->getOrigin());
}

TEST_F(QueryTest, emptyNameWithNSEC) {
    // Empty non terminal with DNSSEC proof.  This is one of the cases of
    // Section 3.1.3.2 of RFC4035.
    // mx.example.com. NSEC ).no.example.com. proves no.example.com. is a
    // non empty terminal node.  Note that it also implicitly proves there
    // should be no closer wildcard match (because the empty name is an
    // exact match), so we only need one NSEC.
    // From the point of the Query::process(), this is actually no different
    // from the other NXRRSET case, but we check that explicitly just in case.
    Query(memory_client, Name("no.example.com"), RRType::A(), response,
          true).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 0, 4, 0, NULL,
                  (string(soa_txt) + string("example.com. 3600 IN RRSIG ") +
                   getCommonRRSIGText("SOA") + "\n" +
                   string(nsec_mx_txt) + "\n" +
                   string("mx.example.com. 3600 IN RRSIG ") +
                   getCommonRRSIGText("NSEC")).c_str(),
                  NULL, mock_finder->getOrigin());
}

TEST_F(QueryTest, nxrrsetWithoutNSEC) {
    // NXRRSET with DNSSEC proof requested, but there's no NSEC at that node.
    // This is an unexpected event (if the zone is supposed to be properly
    // signed with NSECs), but we accept and ignore the oddity.
    Query(memory_client, Name("nonsec.example.com"), RRType::TXT(), response,
          true).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 0, 2, 0, NULL,
                  (string(soa_txt) + string("example.com. 3600 IN RRSIG ") +
                   getCommonRRSIGText("SOA") + "\n").c_str(),
                  NULL, mock_finder->getOrigin());
}

TEST_F(QueryTest, wildcardNSEC) {
    // The qname matches *.wild.example.com.  The response should contain
    // an NSEC that proves the non existence of a closer name.
    Query(memory_client, Name("www.wild.example.com"), RRType::A(), response,
          true).process();
    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 2, 6, 6,
                  (string(wild_txt).replace(0, 1, "www") +
                   string("www.wild.example.com. 3600 IN RRSIG ") +
                   getCommonRRSIGText("A") + "\n").c_str(),
                  (zone_ns_txt + string("example.com. 3600 IN RRSIG NS 5 "
                                        "3 3600 20000101000000 "
                                        "20000201000000 12345 "
                                        "example.com. FAKEFAKEFAKE\n") +
                   string(nsec_wild_txt) +
                   string("*.wild.example.com. 3600 IN RRSIG ") +
                   getCommonRRSIGText("NSEC") + "\n").c_str(),
                  NULL, // we are not interested in additionals in this test
                  mock_finder->getOrigin());
}

TEST_F(QueryTest, CNAMEwildNSEC) {
    // Similar to the previous case, but the matching wildcard record is
    // CNAME.
    Query(memory_client, Name("www.cnamewild.example.com"), RRType::A(),
          response, true).process();
    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 2, 2, 0,
                  (string(cnamewild_txt).replace(0, 1, "www") +
                   string("www.cnamewild.example.com. 3600 IN RRSIG ") +
                   getCommonRRSIGText("CNAME") + "\n").c_str(),
                  (string(nsec_cnamewild_txt) +
                   string("*.cnamewild.example.com. 3600 IN RRSIG ") +
                   getCommonRRSIGText("NSEC") + "\n").c_str(),
                  NULL, // we are not interested in additionals in this test
                  mock_finder->getOrigin());
}

TEST_F(QueryTest, badWildcardProof1) {
    // Unexpected case in wildcard proof: ZoneFinder::find() returns SUCCESS
    // when NXDOMAIN is expected.
    mock_finder->setNSECResult(Name("www.wild.example.com"),
                               ZoneFinder::SUCCESS,
                               mock_finder->delegation_rrset_);
    EXPECT_THROW(Query(memory_client, Name("www.wild.example.com"),
                       RRType::A(), response, true).process(),
                 Query::BadNSEC);
}

TEST_F(QueryTest, badWildcardProof2) {
    // "wildcard proof" doesn't return RRset.
    mock_finder->setNSECResult(Name("www.wild.example.com"),
                               ZoneFinder::NXDOMAIN, ConstRRsetPtr());
    EXPECT_THROW(Query(memory_client, Name("www.wild.example.com"),
                       RRType::A(), response, true).process(),
                 Query::BadNSEC);
}

TEST_F(QueryTest, badWildcardProof3) {
    // "wildcard proof" returns empty NSEC.
    mock_finder->setNSECResult(Name("www.wild.example.com"),
                               ZoneFinder::NXDOMAIN,
                               mock_finder->empty_nsec_rrset_);
    EXPECT_THROW(Query(memory_client, Name("www.wild.example.com"),
                       RRType::A(), response, true).process(),
                 Query::BadNSEC);
}

TEST_F(QueryTest, wildcardNxrrsetWithDuplicateNSEC) {
    // WILDCARD_NXRRSET with DNSSEC proof.  We should have SOA, NSEC that proves the
    // NXRRSET and their RRSIGs. In this case we only need one NSEC,
    // which proves both NXDOMAIN and the non existence RRSETs of wildcard.
    Query(memory_client, Name("www.wild.example.com"), RRType::TXT(), response,
          true).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 0, 4, 0, NULL,
                  (string(soa_txt) + string("example.com. 3600 IN RRSIG ") +
                   getCommonRRSIGText("SOA") + "\n" +
                   string(nsec_wild_txt) +
                   string("*.wild.example.com. 3600 IN RRSIG ") +
                   getCommonRRSIGText("NSEC")+"\n").c_str(),
                  NULL, mock_finder->getOrigin());
}

TEST_F(QueryTest, wildcardNxrrsetWithNSEC) {
    // WILDCARD_NXRRSET with DNSSEC proof.  We should have SOA, NSEC that proves the
    // NXRRSET and their RRSIGs. In this case we need two NSEC RRs,
    // one proves NXDOMAIN and the other proves non existence RRSETs of wildcard.
    Query(memory_client, Name("www1.uwild.example.com"), RRType::TXT(), response,
          true).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 0, 6, 0, NULL,
                  (string(soa_txt) + string("example.com. 3600 IN RRSIG ") +
                   getCommonRRSIGText("SOA") + "\n" +
                   string(nsec_wild_txt_nxrrset) +
                   string("*.uwild.example.com. 3600 IN RRSIG ") +
                   getCommonRRSIGText("NSEC")+"\n" +
                   string(nsec_wild_txt_next) +
                   string("www.uwild.example.com. 3600 IN RRSIG ") +
                   getCommonRRSIGText("NSEC") + "\n").c_str(),
                  NULL, mock_finder->getOrigin());
}

TEST_F(QueryTest, wildcardEmptyWithNSEC) {
    // WILDCARD_EMPTY with DNSSEC proof.  We should have SOA, NSEC that proves the
    // NXDOMAIN and their RRSIGs. In this case we need two NSEC RRs,
    // one proves NXDOMAIN and the other proves non existence wildcard.
    Query(memory_client, Name("a.t.example.com"), RRType::A(), response,
          true).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 0, 6, 0, NULL,
                  (string(soa_txt) + string("example.com. 3600 IN RRSIG ") +
                   getCommonRRSIGText("SOA") + "\n" +
                   string(nsec_empty_prev_txt) +
                   string("t.example.com. 3600 IN RRSIG ") +
                   getCommonRRSIGText("NSEC")+"\n" +
                   string(nsec_empty_txt) +
                   string("b.*.t.example.com. 3600 IN RRSIG ") +
                   getCommonRRSIGText("NSEC")+"\n").c_str(),
                  NULL, mock_finder->getOrigin());
}

/*
 * This tests that when there's no SOA and we need a negative answer. It should
 * throw in that case.
 */
TEST_F(QueryTest, noSOA) {
    // disable zone's SOA RR.
    mock_finder->setSOAFlag(false);

    // The NX Domain
    EXPECT_THROW(Query(memory_client, Name("nxdomain.example.com"),
                       qtype, response).process(), Query::NoSOA);
    // Of course, we don't look into the response, as it throwed

    // NXRRSET
    EXPECT_THROW(Query(memory_client, Name("nxrrset.example.com"),
                       qtype, response).process(), Query::NoSOA);
}

TEST_F(QueryTest, noMatchZone) {
    // there's a zone in the memory datasource but it doesn't match the qname.
    // should result in REFUSED.
    Query(memory_client, Name("example.org"), qtype, response).process();
    EXPECT_EQ(Rcode::REFUSED(), response.getRcode());
}

/*
 * Test MX additional processing.
 *
 * The MX RRset has two RRs, one pointing to a known domain with
 * A record, other to unknown out of zone one.
 */
TEST_F(QueryTest, MX) {
    Query(memory_client, Name("mx.example.com"), RRType::MX(),
          response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 3, 3, 4,
                  mx_txt, NULL,
                  (string(ns_addrs_txt) + string(www_a_txt)).c_str());
}

/*
 * Test when we ask for MX whose exchange is an alias (CNAME in this case).
 *
 * This should not trigger the additional processing for the exchange.
 */
TEST_F(QueryTest, MXAlias) {
    Query(memory_client, Name("cnamemx.example.com"), RRType::MX(),
          response).process();

    // there shouldn't be no additional RRs for the exchanges (we have 3
    // RRs for the NS).  The normal MX case is tested separately so we don't
    // bother to examine the answer (and authority) sections.
    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 3,
                  NULL, NULL, ns_addrs_txt);
}

/*
 * Tests encountering a cname.
 *
 * There are tests leading to successful answers, NXRRSET, NXDOMAIN and
 * out of the zone.
 *
 * TODO: We currently don't do chaining, so only the CNAME itself should be
 * returned.
 */
TEST_F(QueryTest, CNAME) {
    Query(memory_client, Name("cname.example.com"), RRType::A(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 0, 0,
        cname_txt, NULL, NULL);
}

TEST_F(QueryTest, explicitCNAME) {
    // same owner name as the CNAME test but explicitly query for CNAME RR.
    // expect the same response as we don't provide a full chain yet.
    Query(memory_client, Name("cname.example.com"), RRType::CNAME(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 3,
        cname_txt, zone_ns_txt, ns_addrs_txt);
}

TEST_F(QueryTest, CNAME_NX_RRSET) {
    // Leads to www.example.com, it doesn't have TXT
    // note: with chaining, what should be expected is not trivial:
    // BIND 9 returns the CNAME in answer and SOA in authority, no additional.
    // NSD returns the CNAME, NS in authority, A/AAAA for NS in additional.
    Query(memory_client, Name("cname.example.com"), RRType::TXT(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 0, 0,
        cname_txt, NULL, NULL);
}

TEST_F(QueryTest, explicitCNAME_NX_RRSET) {
    // same owner name as the NXRRSET test but explicitly query for CNAME RR.
    Query(memory_client, Name("cname.example.com"), RRType::CNAME(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 3,
        cname_txt, zone_ns_txt, ns_addrs_txt);
}

TEST_F(QueryTest, CNAME_NX_DOMAIN) {
    // Leads to nxdomain.example.com
    // note: with chaining, what should be expected is not trivial:
    // BIND 9 returns the CNAME in answer and SOA in authority, no additional,
    // RCODE being NXDOMAIN.
    // NSD returns the CNAME, NS in authority, A/AAAA for NS in additional,
    // RCODE being NOERROR.
    Query(memory_client, Name("cnamenxdom.example.com"), RRType::A(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 0, 0,
        cname_nxdom_txt, NULL, NULL);
}

TEST_F(QueryTest, explicitCNAME_NX_DOMAIN) {
    // same owner name as the NXDOMAIN test but explicitly query for CNAME RR.
    Query(memory_client, Name("cnamenxdom.example.com"), RRType::CNAME(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 3,
        cname_nxdom_txt, zone_ns_txt, ns_addrs_txt);
}

TEST_F(QueryTest, CNAME_OUT) {
    /*
     * This leads out of zone. This should have only the CNAME even
     * when we do chaining.
     *
     * TODO: We should be able to have two zones in the mock data source.
     * Then the same test should be done with .org included there and
     * see what it does (depends on what we want to do)
     */
    Query(memory_client, Name("cnameout.example.com"), RRType::A(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 0, 0,
        cname_out_txt, NULL, NULL);
}

TEST_F(QueryTest, explicitCNAME_OUT) {
    // same owner name as the OUT test but explicitly query for CNAME RR.
    Query(memory_client, Name("cnameout.example.com"), RRType::CNAME(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 3,
        cname_out_txt, zone_ns_txt, ns_addrs_txt);
}

/*
 * Test a query under a domain with DNAME. We should get a synthetized CNAME
 * as well as the DNAME.
 *
 * TODO: Once we have CNAME chaining, check it works with synthetized CNAMEs
 * as well. This includes tests pointing inside the zone, outside the zone,
 * pointing to NXRRSET and NXDOMAIN cases (similarly as with CNAME).
 */
TEST_F(QueryTest, DNAME) {
    Query(memory_client, Name("www.dname.example.com"), RRType::A(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 2, 0, 0,
        (string(dname_txt) + synthetized_cname_txt).c_str(),
        NULL, NULL);
}

/*
 * Ask an ANY query below a DNAME. Should return the DNAME and synthetized
 * CNAME.
 *
 * ANY is handled specially sometimes. We check it is not the case with
 * DNAME.
 */
TEST_F(QueryTest, DNAME_ANY) {
    Query(memory_client, Name("www.dname.example.com"), RRType::ANY(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 2, 0, 0,
        (string(dname_txt) + synthetized_cname_txt).c_str(), NULL, NULL);
}

// Test when we ask for DNAME explicitly, it does no synthetizing.
TEST_F(QueryTest, explicitDNAME) {
    Query(memory_client, Name("dname.example.com"), RRType::DNAME(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 3,
        dname_txt, zone_ns_txt, ns_addrs_txt);
}

/*
 * Request a RRset at the domain with DNAME. It should not synthetize
 * the CNAME, it should return the RRset.
 */
TEST_F(QueryTest, DNAME_A) {
    Query(memory_client, Name("dname.example.com"), RRType::A(),
        response).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 1, 3, 3,
        dname_a_txt, zone_ns_txt, ns_addrs_txt);
}

/*
 * Request a RRset at the domain with DNAME that is not there (NXRRSET).
 * It should not synthetize the CNAME.
 */
TEST_F(QueryTest, DNAME_NX_RRSET) {
    EXPECT_NO_THROW(Query(memory_client, Name("dname.example.com"),
        RRType::TXT(), response).process());

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 0, 1, 0,
        NULL, soa_txt, NULL, mock_finder->getOrigin());
}

/*
 * Constructing the CNAME will result in a name that is too long. This,
 * however, should not throw (and crash the server), but respond with
 * YXDOMAIN.
 */
TEST_F(QueryTest, LongDNAME) {
    // A name that is as long as it can be
    Name longname(
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa."
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa."
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa."
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa."
        "dname.example.com.");
    EXPECT_NO_THROW(Query(memory_client, longname, RRType::A(),
        response).process());

    responseCheck(response, Rcode::YXDOMAIN(), AA_FLAG, 1, 0, 0,
        dname_txt, NULL, NULL);
}

/*
 * Constructing the CNAME will result in a name of maximal length.
 * This tests that we don't reject valid one by some kind of off by
 * one mistake.
 */
TEST_F(QueryTest, MaxLenDNAME) {
    Name longname(
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa."
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa."
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa."
        "aaaaaaaaaaaaaaaaaaaaaaaaaaaaaaaa."
        "dname.example.com.");
    EXPECT_NO_THROW(Query(memory_client, longname, RRType::A(),
        response).process());

    // Check the answer is OK
    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 2, 0, 0,
        NULL, NULL, NULL);

    // Check that the CNAME has the maximal length.
    bool ok(false);
    for (RRsetIterator i(response.beginSection(Message::SECTION_ANSWER));
        i != response.endSection(Message::SECTION_ANSWER); ++ i) {
        if ((*i)->getType() == RRType::CNAME()) {
            ok = true;
            RdataIteratorPtr ci((*i)->getRdataIterator());
            ASSERT_FALSE(ci->isLast()) << "The CNAME is empty";
            /*
             * Does anybody have a clue why, if the Name::MAX_WIRE is put
             * directly inside ASSERT_EQ, it fails to link and complains
             * it is unresolved external?
             */
            const size_t max_len(Name::MAX_WIRE);
            ASSERT_EQ(max_len, dynamic_cast<const rdata::generic::CNAME&>(
                ci->getCurrent()).getCname().getLength());
        }
    }
    EXPECT_TRUE(ok) << "The synthetized CNAME not found";
}

// Test for this test module itself
void
nsec3Check(bool expected_matched, uint8_t expected_labels,
           const string& expected_rrsets_txt,
           const ZoneFinder::FindNSEC3Result& result)
{
    vector<ConstRRsetPtr> actual_rrsets;
    EXPECT_EQ(expected_matched, result.matched);
    // Convert to int so the error messages would be more readable:
    EXPECT_EQ(static_cast<int>(expected_labels),
              static_cast<int>(result.closest_labels));
    if (result.closest_proof) {
        actual_rrsets.push_back(result.closest_proof);
    }
    if (result.next_proof) {
        actual_rrsets.push_back(result.next_proof);
    }
    rrsetsCheck(expected_rrsets_txt, actual_rrsets.begin(),
                actual_rrsets.end());
}

TEST_F(QueryTest, findNSEC3) {
    // In all test cases in the recursive mode, the closest encloser is the
    // apex, and result's closest_labels should be the number of apex labels.
    // (In non recursive mode closest_labels should be the # labels of the
    // query name)
    const uint8_t expected_closest_labels =
        Name("example.com").getLabelCount();

    // Apex name.  It should have a matching NSEC3
    nsec3Check(true, expected_closest_labels, nsec3_apex_txt,
               mock_finder->findNSEC3(Name("example.com"), false));

    // Recursive mode doesn't change the result in this case.
    nsec3Check(true, expected_closest_labels, nsec3_apex_txt,
               mock_finder->findNSEC3(Name("example.com"), true)); 

    // Non existent name.  Disabling recursion, a covering NSEC3 should be
    // returned.
    nsec3Check(false, 4, nsec3_www_txt,
               mock_finder->findNSEC3(Name("nxdomain.example.com"), false));

    // Non existent name.  The closest provable encloser is the apex,
    // and next closer is the query name.
    nsec3Check(true, expected_closest_labels,
               string(nsec3_apex_txt) + string(nsec3_www_txt),
               mock_finder->findNSEC3(Name("nxdomain.example.com"), true));

    // Similar to the previous case, but next closer name is different
    // (is the parent) of the non existent name.
    nsec3Check(true, expected_closest_labels,
               string(nsec3_apex_txt) + string(nsec3_www_txt),
               mock_finder->findNSEC3(Name("nx.domain.example.com"), true));

    // In the rest of test we check hash comparison for wrap around cases.
    nsec3Check(false, 4, nsec3_apex_txt,
               mock_finder->findNSEC3(Name("nxdomain2.example.com"), false));
    nsec3Check(false, 4, nsec3_www_txt,
               mock_finder->findNSEC3(Name("nxdomain3.example.com"), false));
}

// Check the signature is present when an NXRRSET is returned
TEST_F(QueryTest, nxrrsetWithNSEC3) {
    mock_finder->setNSEC3Flag(true);

    // NXRRSET with DNSSEC proof.  We should have SOA, NSEC3 that proves the
    // NXRRSET and their RRSIGs.
    Query(memory_client, Name("www.example.com"), RRType::TXT(), response,
          true).process();

    responseCheck(response, Rcode::NOERROR(), AA_FLAG, 0, 4, 0, NULL,
                  (string(soa_txt) + string("example.com. 3600 IN RRSIG ") +
                   getCommonRRSIGText("SOA") + "\n" +
                   string(nsec3_www_txt) + "\n" +
                   mock_finder->hash_map_[Name("www.example.com.")] +
                   ".example.com. 3600 IN RRSIG " +
                   getCommonRRSIGText("NSEC3") + "\n").c_str(),
                  NULL, mock_finder->getOrigin());
}

// Check the exception is correctly raised when the NSEC3 thing isn't in the
// zone
TEST_F(QueryTest, nxrrsetMissingNSEC3) {
    mock_finder->setNSEC3Flag(true);
    // We just need it to return false for "matched". This indicates
    // there's no exact match for NSEC3 on www.example.com.
    ZoneFinder::FindNSEC3Result nsec3(false, 0, ConstRRsetPtr(),
                                      ConstRRsetPtr());
    mock_finder->setNSEC3Result(&nsec3);

    EXPECT_THROW(Query(memory_client, Name("www.example.com"), RRType::TXT(),
                       response, true).process(), Query::BadNSEC3);
}

// The following are tentative tests until we really add tests for the
// query logic for these cases.  At that point it's probably better to
// clean them up.
TEST_F(QueryTest, nxdomainWithNSEC3) {
    mock_finder->setNSEC3Flag(true);
    ZoneFinder::FindResult result = mock_finder->find(
        Name("nxdomain.example.com"), RRType::A(), ZoneFinder::FIND_DNSSEC);
    EXPECT_EQ(ZoneFinder::NXDOMAIN, result.code);
    EXPECT_FALSE(result.rrset);
    EXPECT_TRUE(result.isNSEC3Signed());
    EXPECT_FALSE(result.isWildcard());
}

TEST_F(QueryTest, emptyNameWithNSEC3) {
    mock_finder->setNSEC3Flag(true);
    ZoneFinder::FindResult result = mock_finder->find(
        Name("no.example.com"), RRType::A(), ZoneFinder::FIND_DNSSEC);
    EXPECT_EQ(ZoneFinder::NXRRSET, result.code);
    EXPECT_FALSE(result.rrset);
    EXPECT_TRUE(result.isNSEC3Signed());
    EXPECT_FALSE(result.isWildcard());
}

TEST_F(QueryTest, wildcardNxrrsetWithNSEC3) {
    mock_finder->setNSEC3Flag(true);
    ZoneFinder::FindResult result = mock_finder->find(
        Name("www1.uwild.example.com"), RRType::TXT(),
        ZoneFinder::FIND_DNSSEC);
    EXPECT_EQ(ZoneFinder::NXRRSET, result.code);
    EXPECT_FALSE(result.rrset);
    EXPECT_TRUE(result.isNSEC3Signed());
    EXPECT_TRUE(result.isWildcard());
}

TEST_F(QueryTest, wildcardEmptyWithNSEC3) {
    mock_finder->setNSEC3Flag(true);
    ZoneFinder::FindResult result = mock_finder->find(
        Name("a.t.example.com"), RRType::A(), ZoneFinder::FIND_DNSSEC);
    EXPECT_EQ(ZoneFinder::NXRRSET, result.code);
    EXPECT_TRUE(result.isNSEC3Signed());
    EXPECT_TRUE(result.isWildcard());
}
}
