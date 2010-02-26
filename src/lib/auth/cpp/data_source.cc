#include <iostream>
#include <vector>

#include <dns/buffer.h>
#include <dns/message.h>
#include <dns/name.h>
#include <dns/rdataclass.h>
#include <dns/rrset.h>
#include <dns/rrsetlist.h>

#include <cc/data.h>

#include "data_source.h"

using namespace std;
using namespace isc::dns;
using namespace isc::dns::rdata;

namespace isc {
namespace auth {

// Add a task to the query task queue to look up additional data
// (i.e., address records for the names included in NS or MX records)
static void
getAdditional(Query& q, RRsetPtr rrset) {
    if (!q.wantAdditional()) {
        return;
    }

    RdataIteratorPtr it = rrset->getRdataIterator();
    for (it->first(); !it->isLast(); it->next()) {
        const Rdata& rd(it->getCurrent());
        QueryTask* t = NULL;
        if (rrset->getType() == RRType::NS()) {
            const generic::NS& ns = dynamic_cast<const generic::NS&>(rd);

            t = new QueryTask(ns.getNSName(), q.qclass(),
                              Section::ADDITIONAL(),
                              QueryTask::GLUE_QUERY,
                              QueryTask::GETADDITIONAL); 
        } else if (rrset->getType() == RRType::MX()) {
            const generic::MX& mx = dynamic_cast<const generic::MX&>(rd);
            t = new QueryTask(mx.getMXName(), q.qclass(),
                              Section::ADDITIONAL(),
                              QueryTask::NOGLUE_QUERY,
                              QueryTask::GETADDITIONAL); 
        }
        if (t != NULL) {
            q.tasks().push(*t);
        }
    }
}

// Synthesize a CNAME answer, for the benefit of clients that don't
// understand DNAME
static void
synthesizeCname(Query& q, QueryTask& task, RRsetPtr rrset, RRsetList& target) {
    RdataIteratorPtr it;
    it = rrset->getRdataIterator();

    // More than one DNAME RR in the RRset is illegal, so we only have
    // to process the first one.
    it->first();
    if (it->isLast()) {
        return;
    }

    const Rdata& rd(it->getCurrent());
    const generic::DNAME& dname = dynamic_cast<const generic::DNAME&>(rd);
    const Name& dname_target(dname.getDname());

    try {
        int qnlen = task.qname.getLabelCount();
        int dnlen = rrset->getName().getLabelCount();
        const Name& prefix(task.qname.split(0, qnlen - dnlen));
        const Name& newname(prefix.concatenate(dname_target));
        RRsetPtr cname(new RRset(task.qname, task.qclass, RRType::CNAME(),
                                 rrset->getTTL()));
        cname->addRdata(generic::CNAME(newname));
        cname->setTTL(rrset->getTTL());
        target.addRRset(cname);
    } catch (...) {}
}

// Add a task to the query task queue to look up the data pointed
// to by a CNAME record
static void
chaseCname(Query& q, QueryTask& task, RRsetPtr rrset) {
    RdataIteratorPtr it;
    it = rrset->getRdataIterator();

    // More than one CNAME RR in the RRset is illegal, so we only have
    // to process the first one.
    it->first();
    if (it->isLast()) {
        return;
    }

    const Rdata& rd(it->getCurrent());
    const generic::CNAME& cname = dynamic_cast<const generic::CNAME&>(rd);
    const Name& target(cname.getCname());

    QueryTask* t = new QueryTask(target, task.qclass, task.qtype,
                                 Section::ANSWER(), QueryTask::FOLLOWCNAME);
    q.tasks().push(*t);
}

// Perform the query specified in a QueryTask object
DataSrc::Result
doQueryTask(const DataSrc* ds, Query& q, QueryTask& task, RRsetList& target) {
    switch (task.op) {
    case QueryTask::AUTH_QUERY:
        return (ds->findRRset(q, task.qname, task.qclass, task.qtype,
                              target, task.flags, task.zone));

    case QueryTask::SIMPLE_QUERY:
        return (ds->findExactRRset(q, task.qname, task.qclass, task.qtype,
                                   target, task.flags, task.zone));

    case QueryTask::GLUE_QUERY:
    case QueryTask::NOGLUE_QUERY:
        return (ds->findAddrs(q, task.qname, task.qclass, target,
                              task.flags, task.zone));

    case QueryTask::REF_QUERY:
        return (ds->findReferral(q, task.qname, task.qclass, target,
                                 task.flags, task.zone));
    }

    // Not reached
    return (DataSrc::ERROR);
}

// Copy referral information into the authority section of a message
static inline void
copyAuth(Query& q, const RRsetList& auth) {
    Message& m = q.message();
    BOOST_FOREACH(RRsetPtr rrset, auth) {
        if (rrset->getType() == RRType::DNAME()) {
            continue;
        }
        m.addRRset(Section::AUTHORITY(), rrset, q.wantDnssec());
        getAdditional(q, rrset);
    }
}

// Query for referrals (i.e., NS/DS or DNAME) at a given name
static inline bool
refQuery(const Name& name, Query& q, QueryTask& task,
         const DataSrc* ds, RRsetList& target) {
    QueryTask t(name, q.qclass(), QueryTask::REF_QUERY);
    t.zone = task.zone;

    DataSrc::Result result = doQueryTask(ds, q, t, target);

    // Lookup failed
    if (result != DataSrc::SUCCESS) {
        return (false);
    }
    
    // Referral bit is expected, so clear it when checking flags
    if ((t.flags & ~DataSrc::REFERRAL) != 0) {
        return (false);
    }

    return (true);
}

// Match downward, from the zone apex to the query name, looking for
// referrals.
static inline bool
hasDelegation(const DataSrc* ds, Query& q, QueryTask& task) {
    Message& m = q.message();
    int nlen = task.qname.getLabelCount();
    int diff = nlen - task.zone->getLabelCount();
    if (diff > 1) {
        bool found = false;
        RRsetList ref;
        for(int i = diff; i > 1; i--) {
            Name sub(task.qname.split(i - 1, nlen - i));
            if (refQuery(sub, q, task, ds, ref)) {
                found = true;
                break;
            }
        }

        // Found a referral while getting additional data
        // for something other than NS; we skip it.
        if (found && task.op == QueryTask::NOGLUE_QUERY) {
            return (true);
        }

        // Found a referral while getting answer data;
        // send a delegation.
        if (found) {
            if (RRsetPtr r = ref[RRType::DNAME()]) {
                RRsetList syn;
                m.addRRset(Section::ANSWER(), r, q.wantDnssec());
                m.setHeaderFlag(MessageFlag::AA());
                synthesizeCname(q, task, r, syn);
                if (syn.size() == 1) {
                    m.addRRset(Section::ANSWER(),
                               syn[RRType::CNAME()],
                               q.wantDnssec());
                    chaseCname(q, task, syn[RRType::CNAME()]);
                    return (true);
                }
            }

            copyAuth(q, ref);
            return (true);
        }
    }

    // We appear to have authoritative data; set the header
    // flag.  (We may clear it later if we find a referral
    // at the actual qname node.)
    if (task.op == QueryTask::AUTH_QUERY &&
        task.state == QueryTask::GETANSWER) {
        m.setHeaderFlag(MessageFlag::AA());
    }

    return (false);
}

// Attempt a wildcard lookup
static inline DataSrc::Result
tryWildcard(Query& q, QueryTask& task, const DataSrc* ds, bool& found) {
    Message& m = q.message();
    DataSrc::Result result;
    found = false;

    if ((task.flags & DataSrc::NAME_NOT_FOUND) == 0 || 
        (task.state != QueryTask::GETANSWER &&
         task.state != QueryTask::FOLLOWCNAME)) {
        return (DataSrc::SUCCESS);
    }

    int nlen = task.qname.getLabelCount();
    int diff = nlen - task.zone->getLabelCount();
    if (diff < 1) {
        return (DataSrc::SUCCESS);
    }

    RRsetList wild;
    Name star("*");
    uint32_t rflags = 0;

    for(int i = 1; i <= diff; i++) {
        const Name& wname(star.concatenate(task.qname.split(i, nlen - i)));
        QueryTask t(wname, task.qclass, task.qtype,
                    QueryTask::SIMPLE_QUERY); 
        t.zone = task.zone;
        result = doQueryTask(ds, q, t, wild);
        if (result == DataSrc::SUCCESS &&
            (t.flags == 0 || (t.flags & DataSrc::CNAME_FOUND))) {
            rflags = t.flags;
            found = true;
            break;
        }
    }

    // A wildcard was found.  Add the data to the answer
    // section (but with the name changed to match the
    // qname), and then continue as if this were a normal
    // answer: if a CNAME, chase the target, otherwise
    // add authority.
    if (found) {
        if (rflags & DataSrc::CNAME_FOUND) {
            if (RRsetPtr rrset = wild[RRType::CNAME()]) {
                rrset->setName(task.qname);
                m.addRRset(Section::ANSWER(), rrset, q.wantDnssec());
                chaseCname(q, task, rrset);
            }
        } else {
            BOOST_FOREACH (RRsetPtr rrset, wild) {
                rrset->setName(task.qname);
                m.addRRset(Section::ANSWER(), rrset, q.wantDnssec());
            }

            RRsetList auth;
            if (! refQuery(Name(*task.zone), q, task, ds, auth)) {
                return (DataSrc::ERROR);
            }

            copyAuth(q, auth);
        }
    } else if (q.wantDnssec()) {
        // No wildcard found; add an NSEC to prove it
        RRsetList nsec;
        QueryTask t = QueryTask(*task.zone, task.qclass, RRType::NSEC(),
                                QueryTask::SIMPLE_QUERY); 
        t.zone = task.zone;
        result = doQueryTask(ds, q, t, nsec);
        if (result != DataSrc::SUCCESS) {
            return (DataSrc::ERROR);
        }

        if (t.flags == 0) {
            m.addRRset(Section::AUTHORITY(), nsec[RRType::NSEC()], true);
        }
    }

    return (DataSrc::SUCCESS);
}

//
// doQuery: Processes a query.
// 
void
DataSrc::doQuery(Query q) {
    Result result;
    Message& m = q.message();
    vector<RRsetPtr> additional;

    // XXX: this is for testing purposes; it should be done when 
    // parsing the message for EDNS0 options
    q.setWantDnssec(true);

    m.clearHeaderFlag(MessageFlag::AA());
    while (!q.tasks().empty()) {
        RRsetList data;

        QueryTask task = q.tasks().front();
        q.tasks().pop();

        // These task types should never be on the task queue.
        if (task.op == QueryTask::SIMPLE_QUERY ||
            task.op == QueryTask::REF_QUERY) {
            m.setRcode(Rcode::SERVFAIL());
            return;
        }

        // Find the closest enclosing zone for which we are authoritative,
        // and the concrete data source which is authoritative for it.
        // (Note that RRtype DS queries need to go to the parent.)
        Name search(".");
        if (task.qtype == RRType::DS()) {
            search = task.qname.split(1, task.qname.getLabelCount() - 1);
        } else {
            search = task.qname;
        }

        NameMatch match(search);
        findClosestEnclosure(match);
        const DataSrc* ds = match.bestDataSrc();
        const Name* zone = match.closestName();

        if (ds) {
            task.zone = new Name(*zone);

            // For these query task types, if there is more than
            // one level between the zone name and qname, we need to
            // check the intermediate nodes for referrals.
            if ((task.op == QueryTask::AUTH_QUERY ||
                 task.op == QueryTask::NOGLUE_QUERY) &&
                  hasDelegation(ds, q, task)) {
                continue;
            }

            result = doQueryTask(ds, q, task, data);
            if (result != SUCCESS) {
                m.setRcode(Rcode::SERVFAIL());
                return;
            }

            // Query found a referral; let's find out if that was expected--
            // i.e., if an NS was at the zone apex, or if we were querying
            // specifically for the NS, DS or DNAME record.
            if ((task.flags & REFERRAL) &&
                (zone->getLabelCount() == task.qname.getLabelCount() ||
                 task.qtype == RRType::NS() ||
                 task.qtype == RRType::DS() ||
                 task.qtype == RRType::DNAME())) {
                task.flags &= ~REFERRAL;
            }
        } else {
            task.flags = NO_SUCH_ZONE;
        }

        if (result == SUCCESS && task.flags == 0) {
            bool have_ns = false, need_auth = false;
            switch (task.state) {
            case QueryTask::GETANSWER:
            case QueryTask::FOLLOWCNAME:
                BOOST_FOREACH(RRsetPtr rrset, data) {
                    m.addRRset(task.section, rrset, q.wantDnssec());
                    if (q.tasks().empty()) {
                        need_auth = true;
                    }
                    getAdditional(q, rrset);
                    if (rrset->getType() == RRType::NS()) {
                        have_ns = true;
                    }
                }
                q.setStatus(Query::ANSWERED);
                if (need_auth && !have_ns) {
                    // Data found, no additional processing needed.
                    // Add the NS records for the enclosing zone to
                    // the authority section.
                    RRsetList auth;
                    if (! refQuery(Name(*zone), q, task, ds, auth)) {
                        m.setRcode(Rcode::SERVFAIL());
                        return;
                    }

                    copyAuth(q, auth);
                }
                continue;

            case QueryTask::GETADDITIONAL:
                // Got additional data.  Do not add it to the message
                // yet; instead store it and copy it in at the end
                // (this allow RRSIGs to be omitted if necessary).
                BOOST_FOREACH(RRsetPtr rrset, data) {
                    if (q.status() == Query::ANSWERED &&
                        rrset->getName() == q.qname() &&
                        rrset->getType() == q.qtype()) {
                        continue;
                    }
                    additional.push_back(rrset);
                }
                continue;

            default:
                dns_throw (Unexpected, "unexpected query state");
            }
        } else if (result == ERROR || result == NOT_IMPLEMENTED) {
            m.setRcode(Rcode::SERVFAIL());
            return;
        } else if (task.flags & CNAME_FOUND) {
            // The qname node contains a CNAME.  Add a new task to the
            // queue to look up its target.
            if (RRsetPtr rrset = data[RRType::CNAME()]) {
                m.addRRset(task.section, rrset, q.wantDnssec());
                chaseCname(q, task, rrset);
            }
            continue;
        } else if (task.flags & REFERRAL) {
            // The qname node contains an out-of-zone referral.
            if (task.state == QueryTask::GETANSWER) {
                RRsetList auth;
                m.clearHeaderFlag(MessageFlag::AA());
                if (! refQuery(task.qname, q, task, ds, auth)) {
                    m.setRcode(Rcode::SERVFAIL());
                    return;
                }
                BOOST_FOREACH (RRsetPtr rrset, auth) {
                    if (rrset->getType() == RRType::DNAME()) {
                        continue;
                    }
                    if (rrset->getType() == RRType::DS() &&
                        task.qtype == RRType::DS()) {
                        m.addRRset(Section::ANSWER(), rrset, q.wantDnssec());
                    } else {
                        m.addRRset(Section::AUTHORITY(), rrset, q.wantDnssec());
                    }
                    getAdditional(q, rrset);
                }
            } 
            continue;
        } else if (task.flags & NO_SUCH_ZONE) {
            // No such zone.  If we're chasing cnames or adding additional
            // data, that's okay, but if doing an original query, return
            // REFUSED.
            if (task.state == QueryTask::GETANSWER) {
                m.setRcode(Rcode::REFUSED());
                return;
            }
            continue;
        } else if (task.flags & (NAME_NOT_FOUND|TYPE_NOT_FOUND)) {
            // No data found at this qname/qtype.
            // If we were looking for answer data, not additional,
            // and the name was not found, we need to find out whether
            // there are any relevant wildcards.
            bool wildcard_found = false;
            result = tryWildcard(q, task, ds, wildcard_found);
            if (result != SUCCESS) {
                m.setRcode(Rcode::SERVFAIL());
                return;
            }

            if (wildcard_found) {
                continue;
            }

            // If we've reached this point, there is definitely no answer.
            // If we were chasing cnames or adding additional data, that's
            // okay, but if we were doing an original query, reply with the
            // SOA in the authority section.  For NAME_NOT_FOUND, set
            // NXDOMAIN, and also add the previous NSEC to the authority
            // section.  For TYPE_NOT_FOUND, do not set an error rcode,
            // and send the current NSEC in the authority section.
            Name nsecname(task.qname);
            if (task.flags & NAME_NOT_FOUND) {
                ds->findPreviousName(q, task.qname, nsecname, task.zone);
            }

            if (task.state == QueryTask::GETANSWER) {
                if (task.flags & NAME_NOT_FOUND) {
                    m.setRcode(Rcode::NXDOMAIN());
                }

                RRsetList soa;
                QueryTask t(Name(*zone), task.qclass, RRType::SOA(), 
                            QueryTask::SIMPLE_QUERY); 
                t.zone = task.zone;
                result = doQueryTask(ds, q, t, soa);
                if (result != SUCCESS || t.flags != 0) {
                    m.setRcode(Rcode::SERVFAIL());
                    return;
                }

                m.addRRset(Section::AUTHORITY(), soa[RRType::SOA()],
                           q.wantDnssec());
            }

            if (q.wantDnssec()) {
                RRsetList nsec;
                QueryTask t = QueryTask(nsecname, task.qclass, RRType::NSEC(), 
                                        QueryTask::SIMPLE_QUERY); 
                t.zone = task.zone;
                result = doQueryTask(ds, q, t, nsec);
                if (result != SUCCESS) {
                    m.setRcode(Rcode::SERVFAIL());
                    return;
                }

                if (t.flags == 0) {
                    m.addRRset(Section::AUTHORITY(), nsec[RRType::NSEC()],
                               true);
                }
            }

            return;
        } else {
            // Should never be reached!
            m.setRcode(Rcode::SERVFAIL());
            return;
        }
    }

    // We're done, so now copy in the additional data:
    // data first, then signatures.  (If we run out of
    // space, signatures in additional section are
    // optional.)
    BOOST_FOREACH(RRsetPtr rrset, additional) {
        m.addRRset(Section::ADDITIONAL(), rrset, false);
    }

    if (q.wantDnssec()) {
        BOOST_FOREACH(RRsetPtr rrset, additional) {
            if (rrset->getRRsig()) {
                m.addRRset(Section::ADDITIONAL(), rrset->getRRsig(), false);
            }
        }
    }
}

}
}
