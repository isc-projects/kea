#include <dns/cpp/buffer.h>
#include <dns/cpp/name.h>
#include <dns/cpp/rrset.h>
#include <dns/cpp/message.h>

#include <cc/cpp/data.h>

#include "data_source.h"

namespace isc {
namespace dns {

DSResult
DataSrc::runQuery(Query q) {
    DSResult result;
    RRsetList data, sigs;
    Name container(".");
    Message& m = q.message();

    while (!q.tasks().empty()) {
        bool found = false;
        QueryTaskPtr task = q.tasks().front();
        q.tasks().pop();

        const DataSrc* ds = findClosestEnclosure(task->qname, container, found);

        if (ds == NULL) {
            result = ZONE_NOT_FOUND;
        } else if (q.wantDnssec()) {
            result = ds->findRRset(task->qname, task->qclass, task->qtype,
                                   data, sigs);
            // XXX validity check:
            // for now, there must only be exactly one RRset in data
            // and no more than one RRset in sigs.  the rrtype of data
            // must match the sigtype of sigs, if any
        } else {
            result = ds->findRRset(task->qname, task->qclass, task->qtype,
                                   data);
        }

        switch (result) {
            case SUCCESS:
                m.addRRset(task->section, data[0]);
                if (q.wantDnssec() && sigs.size() == 1) {
                    m.addRRset(Section(task->section), sigs[0]);
                }

                if (q.status() == QUERY_FINISHING) {
                    q.setStatus(QUERY_DONE);
                    return (SUCCESS);
                }

                // if there are no more work items, add the authority section
                if (q.tasks().empty() && q.status() == QUERY_INCOMPLETE) {
                    QueryTask *qt = new QueryTask(container, task->qclass,
                                                  RRType::NS(),
                                                  Section::AUTHORITY());
                    q.tasks().push(QueryTaskPtr(qt));
                    q.setStatus(QUERY_FINISHING);
                }
                continue;

            case CNAME:
                m.addRRset(task->section, data[0]);
                if (q.wantDnssec() && sigs.size() == 1) {
                    m.addRRset(Section(task->section), sigs[0]);
                }

                // if (data[0].getType() == RRType::CNAME()) {
                //     // take apart the CNAME rdata and re-query HERE
                // }
                continue;

            case NAME_NOT_FOUND:
                q.setStatus(QUERY_NODATA);
                if (q.wantDnssec()) {
                    result = ds->findRRset(container, task->qclass,
                                           RRType::SOA(), data, sigs);
                } else {
                    result = ds->findRRset(container, task->qclass, 
                                           RRType::SOA(), data);
                }

                if (result != SUCCESS) {
                    m.setRcode(Rcode::SERVFAIL());
                    return (ERROR);
                }

                m.setRcode(Rcode::NXDOMAIN());
                m.addRRset(Section::AUTHORITY(), data[0]);
                if (q.wantDnssec() && sigs.size() == 1) {
                    m.addRRset(Section::AUTHORITY(), sigs[0]);
                }
                break;

            case TYPE_NOT_FOUND:
                m.setRcode(Rcode::NOERROR());
                q.setStatus(QUERY_NODATA);
                return (result);

            case ZONE_NOT_FOUND:
                m.setRcode(Rcode::REFUSED());
                q.setStatus(QUERY_NODATA);
                return (result);

            default:
                m.setRcode(Rcode::SERVFAIL());
                q.setStatus(QUERY_NODATA);
                return (result);
        }
    }

    return (result);
};


}
}
