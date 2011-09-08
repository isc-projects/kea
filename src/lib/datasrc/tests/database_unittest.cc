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

#include <boost/foreach.hpp>

#include <gtest/gtest.h>

#include <dns/name.h>
#include <dns/rrttl.h>
#include <dns/rrset.h>
#include <exceptions/exceptions.h>

#include <datasrc/database.h>
#include <datasrc/zone.h>
#include <datasrc/data_source.h>
#include <datasrc/iterator.h>
#include <datasrc/sqlite3_accessor.h>

#include <testutils/dnsmessage_test.h>

#include <map>

using namespace isc::datasrc;
using namespace std;
using namespace boost;
using namespace isc::dns;

namespace {

// Imaginary zone IDs used in the mock accessor below.
const int READONLY_ZONE_ID = 42;
const int WRITABLE_ZONE_ID = 4200;

// Commonly used test data
const char* const TEST_RECORDS[][5] = {
    // some plain data
    {"www.example.org.", "A", "3600", "", "192.0.2.1"},
    {"www.example.org.", "AAAA", "3600", "", "2001:db8::1"},
    {"www.example.org.", "AAAA", "3600", "", "2001:db8::2"},
    {"www.example.org.", "NSEC", "3600", "", "www2.example.org. A AAAA NSEC RRSIG"},
    {"www.example.org.", "RRSIG", "3600", "", "NSEC 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},

    {"www2.example.org.", "A", "3600", "", "192.0.2.1"},
    {"www2.example.org.", "AAAA", "3600", "", "2001:db8::1"},
    {"www2.example.org.", "A", "3600", "", "192.0.2.2"},

    {"cname.example.org.", "CNAME", "3600", "", "www.example.org."},

    // some DNSSEC-'signed' data
    {"signed1.example.org.", "A", "3600", "", "192.0.2.1"},
    {"signed1.example.org.", "RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},

    {"signed1.example.org.", "RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12346 example.org. FAKEFAKEFAKE"},
    {"signed1.example.org.", "AAAA", "3600", "", "2001:db8::1"},
    {"signed1.example.org.", "AAAA", "3600", "", "2001:db8::2"},
    {"signed1.example.org.", "RRSIG", "3600", "", "AAAA 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},

    {"signedcname1.example.org.", "CNAME", "3600", "", "www.example.org."},
    {"signedcname1.example.org.", "RRSIG", "3600", "", "CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},

    // special case might fail; sig is for cname, which isn't there (should be ignored)
    // (ignoring of 'normal' other type is done above by www.)
    {"acnamesig1.example.org.", "A", "3600", "", "192.0.2.1"},
    {"acnamesig1.example.org.", "RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"acnamesig1.example.org.", "RRSIG", "3600", "", "CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},

    // let's pretend we have a database that is not careful
    // about the order in which it returns data
    {"signed2.example.org.", "RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"signed2.example.org.", "AAAA", "3600", "", "2001:db8::2"},
    {"signed2.example.org.", "RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12346 example.org. FAKEFAKEFAKE"},
    {"signed2.example.org.", "A", "3600", "", "192.0.2.1"},
    {"signed2.example.org.", "RRSIG", "3600", "", "AAAA 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"signed2.example.org.", "AAAA", "3600", "", "2001:db8::1"},

    {"signedcname2.example.org.", "RRSIG", "3600", "", "CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"signedcname2.example.org.", "CNAME", "3600", "", "www.example.org."},

    {"acnamesig2.example.org.", "RRSIG", "3600", "", "CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"acnamesig2.example.org.", "A", "3600", "", "192.0.2.1"},
    {"acnamesig2.example.org.", "RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},

    {"acnamesig3.example.org.", "RRSIG", "3600", "", "CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"acnamesig3.example.org.", "RRSIG", "3600", "", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"acnamesig3.example.org.", "A", "3600", "", "192.0.2.1"},

    {"ttldiff1.example.org.", "A", "3600", "", "192.0.2.1"},
    {"ttldiff1.example.org.", "A", "360", "", "192.0.2.2"},

    {"ttldiff2.example.org.", "A", "360", "", "192.0.2.1"},
    {"ttldiff2.example.org.", "A", "3600", "", "192.0.2.2"},

    // also add some intentionally bad data
    {"badcname1.example.org.", "A", "3600", "", "192.0.2.1"},
    {"badcname1.example.org.", "CNAME", "3600", "", "www.example.org."},

    {"badcname2.example.org.", "CNAME", "3600", "", "www.example.org."},
    {"badcname2.example.org.", "A", "3600", "", "192.0.2.1"},

    {"badcname3.example.org.", "CNAME", "3600", "", "www.example.org."},
    {"badcname3.example.org.", "CNAME", "3600", "", "www.example2.org."},

    {"badrdata.example.org.", "A", "3600", "", "bad"},

    {"badtype.example.org.", "BAD_TYPE", "3600", "", "192.0.2.1"},

    {"badttl.example.org.", "A", "badttl", "", "192.0.2.1"},

    {"badsig.example.org.", "A", "badttl", "", "192.0.2.1"},
    {"badsig.example.org.", "RRSIG", "3600", "", "A 5 3 3600 somebaddata 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},

    {"badsigtype.example.org.", "A", "3600", "", "192.0.2.1"},
    {"badsigtype.example.org.", "RRSIG", "3600", "TXT", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},

    // Data for testing delegation (with NS and DNAME)
    {"delegation.example.org.", "NS", "3600", "", "ns.example.com."},
    {"delegation.example.org.", "NS", "3600", "",
     "ns.delegation.example.org."},
    {"delegation.example.org.", "RRSIG", "3600", "", "NS 5 3 3600 "
     "20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"ns.delegation.example.org.", "A", "3600", "", "192.0.2.1"},
    {"deep.below.delegation.example.org.", "A", "3600", "", "192.0.2.1"},

    {"dname.example.org.", "A", "3600", "", "192.0.2.1"},
    {"dname.example.org.", "DNAME", "3600", "", "dname.example.com."},
    {"dname.example.org.", "RRSIG", "3600", "",
     "DNAME 5 3 3600 20000101000000 20000201000000 12345 "
     "example.org. FAKEFAKEFAKE"},

    {"below.dname.example.org.", "A", "3600", "", "192.0.2.1"},

    // Broken NS
    {"brokenns1.example.org.", "A", "3600", "", "192.0.2.1"},
    {"brokenns1.example.org.", "NS", "3600", "", "ns.example.com."},

    {"brokenns2.example.org.", "NS", "3600", "", "ns.example.com."},
    {"brokenns2.example.org.", "A", "3600", "", "192.0.2.1"},

    // Now double DNAME, to test failure mode
    {"baddname.example.org.", "DNAME", "3600", "", "dname1.example.com."},
    {"baddname.example.org.", "DNAME", "3600", "", "dname2.example.com."},

    // Put some data into apex (including NS) so we can check our NS
    // doesn't break anything
    {"example.org.", "NS", "3600", "", "ns.example.com."},
    {"example.org.", "A", "3600", "", "192.0.2.1"},
    {"example.org.", "RRSIG", "3600", "", "NS 5 3 3600 20000101000000 "
              "20000201000000 12345 example.org. FAKEFAKEFAKE"},

    // This is because of empty domain test
    {"a.b.example.org.", "A", "3600", "", "192.0.2.1"},

    // Something for wildcards
    {"*.wild.example.org.", "A", "3600", "", "192.0.2.5"},
    {"*.wild.example.org.", "RRSIG", "3600", "A", "A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"*.wild.example.org.", "NSEC", "3600", "", "cancel.here.wild.example.org. A NSEC RRSIG"},
    {"*.wild.example.org.", "RRSIG", "3600", "", "NSEC 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE"},
    {"cancel.here.wild.example.org.", "AAAA", "3600", "", "2001:db8::5"},
    {"delegatedwild.example.org.", "NS", "3600", "", "ns.example.com."},
    {"*.delegatedwild.example.org.", "A", "3600", "", "192.0.2.5"},
    {"wild.*.foo.example.org.", "A", "3600", "", "192.0.2.5"},
    {"wild.*.foo.*.bar.example.org.", "A", "3600", "", "192.0.2.5"},

    {NULL, NULL, NULL, NULL, NULL},
};

/*
 * An accessor with minimum implementation, keeping the original
 * "NotImplemented" methods.
 */
class NopAccessor : public DatabaseAccessor {
public:
    NopAccessor() : database_name_("mock_database")
    { }

    virtual std::pair<bool, int> getZone(const std::string& name) const {
        if (name == "example.org.") {
            return (std::pair<bool, int>(true, READONLY_ZONE_ID));
        } else if (name == "null.example.org.") {
            return (std::pair<bool, int>(true, 13));
        } else if (name == "empty.example.org.") {
            return (std::pair<bool, int>(true, 0));
        } else if (name == "bad.example.org.") {
            return (std::pair<bool, int>(true, -1));
        } else {
            return (std::pair<bool, int>(false, 0));
        }
    }

    virtual shared_ptr<DatabaseAccessor> clone() {
        return (shared_ptr<DatabaseAccessor>()); // bogus data, but unused
    }

    virtual std::pair<bool, int> startUpdateZone(const std::string&, bool) {
        // return dummy value.  unused anyway.
        return (pair<bool, int>(true, 0));
    }
    virtual void commitUpdateZone() {}
    virtual void rollbackUpdateZone() {}
    virtual void addRecordToZone(const string (&)[ADD_COLUMN_COUNT]) {}
    virtual void deleteRecordInZone(const string (&)[DEL_PARAM_COUNT]) {}

    virtual const std::string& getDBName() const {
        return (database_name_);
    }

    virtual IteratorContextPtr getRecords(const std::string&, int, bool)
        const
        {
        isc_throw(isc::NotImplemented,
                  "This database datasource can't be iterated");
    }

    virtual IteratorContextPtr getAllRecords(int) const {
        isc_throw(isc::NotImplemented,
                  "This database datasource can't be iterated");
    }

private:
    const std::string database_name_;

};

/*
 * A virtual database accessor that pretends it contains single zone --
 * example.org.
 *
 * It has the same getZone method as NopConnection, but it provides
 * implementation of the optional functionality.
 */
class MockAccessor : public NopAccessor {
    // Type of mock database "row"s
    typedef std::map<std::string, std::vector< std::vector<std::string> > >
        Domains;

public:
    MockAccessor() : rollbacked_(false) {
        readonly_records_ = &readonly_records_master_;
        update_records_ = &update_records_master_;
        empty_records_ = &empty_records_master_;
        fillData();
    }

    virtual shared_ptr<DatabaseAccessor> clone() {
        shared_ptr<MockAccessor> cloned_accessor(new MockAccessor());
        cloned_accessor->readonly_records_ = &readonly_records_master_;
        cloned_accessor->update_records_ = &update_records_master_;
        cloned_accessor->empty_records_ = &empty_records_master_;
        latest_clone_ = cloned_accessor;
        return (cloned_accessor);
    }

private:
    class MockNameIteratorContext : public IteratorContext {
    public:
        MockNameIteratorContext(const MockAccessor& mock_accessor, int zone_id,
                                const std::string& name, bool subdomains) :
            searched_name_(name), cur_record_(0)
        {
            // 'hardcoded' names to trigger exceptions
            // On these names some exceptions are thrown, to test the robustness
            // of the find() method.
            if (searched_name_ == "dsexception.in.search.") {
                isc_throw(DataSourceError, "datasource exception on search");
            } else if (searched_name_ == "iscexception.in.search.") {
                isc_throw(isc::Exception, "isc exception on search");
            } else if (searched_name_ == "basicexception.in.search.") {
                throw std::exception();
            }

            cur_record_ = 0;
            const Domains& cur_records = mock_accessor.getMockRecords(zone_id);
            if (cur_records.count(name) > 0) {
                    // we're not aiming for efficiency in this test, simply
                    // copy the relevant vector from records
                    cur_name = cur_records.find(name)->second;
            } else if (subdomains) {
                cur_name.clear();
                // Just walk everything and check if it is a subdomain.
                // If it is, just copy all data from there.
                for (Domains::const_iterator i(cur_records.begin());
                     i != cur_records.end(); ++i) {
                    const Name local(i->first);
                    if (local.compare(Name(name)).getRelation() ==
                        isc::dns::NameComparisonResult::SUBDOMAIN) {
                        cur_name.insert(cur_name.end(), i->second.begin(),
                                        i->second.end());
                    }
                }
            } else {
                cur_name.clear();
            }
        }

        virtual bool getNext(std::string (&columns)[COLUMN_COUNT]) {
            if (searched_name_ == "dsexception.in.getnext.") {
                isc_throw(DataSourceError, "datasource exception on getnextrecord");
            } else if (searched_name_ == "iscexception.in.getnext.") {
                isc_throw(isc::Exception, "isc exception on getnextrecord");
            } else if (searched_name_ == "basicexception.in.getnext.") {
                throw std::exception();
            }

            if (cur_record_ < cur_name.size()) {
                for (size_t i = 0; i < COLUMN_COUNT; ++i) {
                    columns[i] = cur_name[cur_record_][i];
                }
                cur_record_++;
                return (true);
            } else {
                return (false);
            }
        }

    private:
        const std::string searched_name_;
        int cur_record_;
        std::vector< std::vector<std::string> > cur_name;
    };

    class MockIteratorContext : public IteratorContext {
    private:
        int step;
    public:
        MockIteratorContext() :
            step(0)
        { }
        virtual bool getNext(string (&data)[COLUMN_COUNT]) {
            switch (step ++) {
                case 0:
                    data[DatabaseAccessor::NAME_COLUMN] = "example.org";
                    data[DatabaseAccessor::TYPE_COLUMN] = "SOA";
                    data[DatabaseAccessor::TTL_COLUMN] = "300";
                    data[DatabaseAccessor::RDATA_COLUMN] = "ns1.example.org. admin.example.org. "
                        "1234 3600 1800 2419200 7200";
                    return (true);
                case 1:
                    data[DatabaseAccessor::NAME_COLUMN] = "x.example.org";
                    data[DatabaseAccessor::TYPE_COLUMN] = "A";
                    data[DatabaseAccessor::TTL_COLUMN] = "300";
                    data[DatabaseAccessor::RDATA_COLUMN] = "192.0.2.1";
                    return (true);
                case 2:
                    data[DatabaseAccessor::NAME_COLUMN] = "x.example.org";
                    data[DatabaseAccessor::TYPE_COLUMN] = "A";
                    data[DatabaseAccessor::TTL_COLUMN] = "300";
                    data[DatabaseAccessor::RDATA_COLUMN] = "192.0.2.2";
                    return (true);
                case 3:
                    data[DatabaseAccessor::NAME_COLUMN] = "x.example.org";
                    data[DatabaseAccessor::TYPE_COLUMN] = "AAAA";
                    data[DatabaseAccessor::TTL_COLUMN] = "300";
                    data[DatabaseAccessor::RDATA_COLUMN] = "2001:db8::1";
                    return (true);
                case 4:
                    data[DatabaseAccessor::NAME_COLUMN] = "x.example.org";
                    data[DatabaseAccessor::TYPE_COLUMN] = "AAAA";
                    data[DatabaseAccessor::TTL_COLUMN] = "300";
                    data[DatabaseAccessor::RDATA_COLUMN] = "2001:db8::2";
                    return (true);
                default:
                    ADD_FAILURE() <<
                        "Request past the end of iterator context";
                case 5:
                    return (false);
            }
        }
    };
    class EmptyIteratorContext : public IteratorContext {
    public:
        virtual bool getNext(string(&)[COLUMN_COUNT]) {
            return (false);
        }
    };
    class BadIteratorContext : public IteratorContext {
    private:
        int step;
    public:
        BadIteratorContext() :
            step(0)
        { }
        virtual bool getNext(string (&data)[COLUMN_COUNT]) {
            switch (step ++) {
                case 0:
                    data[DatabaseAccessor::NAME_COLUMN] = "x.example.org";
                    data[DatabaseAccessor::TYPE_COLUMN] = "A";
                    data[DatabaseAccessor::TTL_COLUMN] = "300";
                    data[DatabaseAccessor::RDATA_COLUMN] = "192.0.2.1";
                    return (true);
                case 1:
                    data[DatabaseAccessor::NAME_COLUMN] = "x.example.org";
                    data[DatabaseAccessor::TYPE_COLUMN] = "A";
                    data[DatabaseAccessor::TTL_COLUMN] = "301";
                    data[DatabaseAccessor::RDATA_COLUMN] = "192.0.2.2";
                    return (true);
                default:
                    ADD_FAILURE() <<
                        "Request past the end of iterator context";
                case 2:
                    return (false);
            }
        }
    };
public:
    virtual IteratorContextPtr getAllRecords(int id) const {
        if (id == READONLY_ZONE_ID) {
            return (IteratorContextPtr(new MockIteratorContext()));
        } else if (id == 13) {
            return (IteratorContextPtr());
        } else if (id == 0) {
            return (IteratorContextPtr(new EmptyIteratorContext()));
        } else if (id == -1) {
            return (IteratorContextPtr(new BadIteratorContext()));
        } else {
            isc_throw(isc::Unexpected, "Unknown zone ID");
        }
    }

    virtual IteratorContextPtr getRecords(const std::string& name, int id,
                                          bool subdomains) const
    {
        if (id == READONLY_ZONE_ID || id == WRITABLE_ZONE_ID) {
            return (IteratorContextPtr(
                        new MockNameIteratorContext(*this, id, name,
                                                    subdomains)));
        } else {
            isc_throw(isc::Unexpected, "Unknown zone ID");
        }
    }

    virtual pair<bool, int> startUpdateZone(const std::string& zone_name,
                                            bool replace)
    {
        const pair<bool, int> zone_info = getZone(zone_name);
        if (!zone_info.first) {
            return (pair<bool, int>(false, 0));
        }

        // Prepare the record set for update.  If replacing the existing one,
        // we use an empty set; otherwise we use a writable copy of the
        // original.
        if (replace) {
            update_records_->clear();
        } else {
            *update_records_ = *readonly_records_;
        }

        return (pair<bool, int>(true, WRITABLE_ZONE_ID));
    }
    virtual void commitUpdateZone() {
        *readonly_records_ = *update_records_;
    }
    virtual void rollbackUpdateZone() {
        // Special hook: if something with a name of "throw.example.org"
        // has been added, trigger an imaginary unexpected event with an
        // exception.
        if (update_records_->count("throw.example.org.") > 0) {
            isc_throw(DataSourceError, "unexpected failure in rollback");
        }

        rollbacked_ = true;
    }
    virtual void addRecordToZone(const string (&columns)[ADD_COLUMN_COUNT]) {
        // Copy the current value to cur_name.  If it doesn't exist,
        // operator[] will create a new one.
        cur_name_ = (*update_records_)[columns[DatabaseAccessor::ADD_NAME]];

        vector<string> record_columns;
        record_columns.push_back(columns[DatabaseAccessor::ADD_TYPE]);
        record_columns.push_back(columns[DatabaseAccessor::ADD_TTL]);
        record_columns.push_back(columns[DatabaseAccessor::ADD_SIGTYPE]);
        record_columns.push_back(columns[DatabaseAccessor::ADD_RDATA]);
        record_columns.push_back(columns[DatabaseAccessor::ADD_NAME]);

        // copy back the added entry
        cur_name_.push_back(record_columns);
        (*update_records_)[columns[DatabaseAccessor::ADD_NAME]] = cur_name_;

        // remember this one so that test cases can check it.
        copy(columns, columns + DatabaseAccessor::ADD_COLUMN_COUNT,
             columns_lastadded_);
    }

    // Helper predicate class used in deleteRecordInZone().
    struct deleteMatch {
        deleteMatch(const string& type, const string& rdata) :
            type_(type), rdata_(rdata)
        {}
        bool operator()(const vector<string>& row) const {
            return (row[0] == type_ && row[3] == rdata_);
        }
        const string& type_;
        const string& rdata_;
    };

    virtual void deleteRecordInZone(const string (&params)[DEL_PARAM_COUNT]) {
        vector<vector<string> >& records =
            (*update_records_)[params[DatabaseAccessor::DEL_NAME]];
        records.erase(remove_if(records.begin(), records.end(),
                                deleteMatch(
                                    params[DatabaseAccessor::DEL_TYPE],
                                    params[DatabaseAccessor::DEL_RDATA])),
                      records.end());
        if (records.empty()) {
            (*update_records_).erase(params[DatabaseAccessor::DEL_NAME]);
        }
    }

    //
    // Helper methods to keep track of some update related activities
    //
    bool isRollbacked() const {
        return (rollbacked_);
    }

    const string* getLastAdded() const {
        return (columns_lastadded_);
    }

    // This allows the test code to get the accessor used in an update context
    shared_ptr<const MockAccessor> getLatestClone() const {
        return (latest_clone_);
    }

private:
    // The following member variables are storage and/or update work space
    // of the test zone.  The "master"s are the real objects that contain
    // the data, and they are shared among all accessors cloned from
    // an initially created one.  The pointer members allow the sharing.
    // "readonly" is for normal lookups.  "update" is the workspace for
    // updates.  When update starts it will be initialized either as an
    // empty set (when replacing the entire zone) or as a copy of the
    // "readonly" one.  "empty" is a sentinel to produce negative results.
    Domains readonly_records_master_;
    Domains* readonly_records_;
    Domains update_records_master_;
    Domains* update_records_;
    const Domains empty_records_master_;
    const Domains* empty_records_;

    // used as temporary storage during the building of the fake data

    // used as temporary storage after searchForRecord() and during
    // getNextRecord() calls, as well as during the building of the
    // fake data
    std::vector< std::vector<std::string> > cur_name_;

    // The columns that were most recently added via addRecordToZone()
    string columns_lastadded_[ADD_COLUMN_COUNT];

    // Whether rollback operation has been performed for the database.
    // Not useful except for purely testing purpose.
    bool rollbacked_;

    // Remember the mock accessor that was last cloned
    boost::shared_ptr<MockAccessor> latest_clone_;

    const Domains& getMockRecords(int zone_id) const {
        if (zone_id == READONLY_ZONE_ID) {
            return (*readonly_records_);
        } else if (zone_id == WRITABLE_ZONE_ID) {
            return (*update_records_);
        }
        return (*empty_records_);
    }

    // Adds one record to the current name in the database
    // The actual data will not be added to 'records' until
    // addCurName() is called
    void addRecord(const std::string& type,
                   const std::string& ttl,
                   const std::string& sigtype,
                   const std::string& rdata) {
        std::vector<std::string> columns;
        columns.push_back(type);
        columns.push_back(ttl);
        columns.push_back(sigtype);
        columns.push_back(rdata);
        cur_name_.push_back(columns);
    }

    // Adds all records we just built with calls to addRecords
    // to the actual fake database. This will clear cur_name_,
    // so we can immediately start adding new records.
    void addCurName(const std::string& name) {
        ASSERT_EQ(0, readonly_records_->count(name));
        // Append the name to all of them
        for (std::vector<std::vector<std::string> >::iterator
             i(cur_name_.begin()); i != cur_name_.end(); ++ i) {
            i->push_back(name);
        }
        (*readonly_records_)[name] = cur_name_;
        cur_name_.clear();
    }

    // Fills the database with zone data.
    // This method constructs a number of resource records (with addRecord),
    // which will all be added for one domain name to the fake database
    // (with addCurName). So for instance the first set of calls create
    // data for the name 'www.example.org', which will consist of one A RRset
    // of one record, and one AAAA RRset of two records.
    // The order in which they are added is the order in which getNextRecord()
    // will return them (so we can test whether find() etc. support data that
    // might not come in 'normal' order)
    // It shall immediately fail if you try to add the same name twice.
    void fillData() {
        const char* prev_name = NULL;
        for (int i = 0; TEST_RECORDS[i][0] != NULL; ++i) {
            if (prev_name != NULL &&
                strcmp(prev_name, TEST_RECORDS[i][0]) != 0) {
                addCurName(prev_name);
            }
            prev_name = TEST_RECORDS[i][0];
            addRecord(TEST_RECORDS[i][1], TEST_RECORDS[i][2],
                      TEST_RECORDS[i][3], TEST_RECORDS[i][4]);
        }
        addCurName(prev_name);
    }
};

// This tests the default getRecords behaviour, throwing NotImplemented
TEST(DatabaseConnectionTest, getRecords) {
    EXPECT_THROW(NopAccessor().getRecords(".", 1, false),
                 isc::NotImplemented);
}

// This tests the default getAllRecords behaviour, throwing NotImplemented
TEST(DatabaseConnectionTest, getAllRecords) {
    // The parameters don't matter
    EXPECT_THROW(NopAccessor().getAllRecords(1),
                 isc::NotImplemented);
}

// This test fixture is templated so that we can share (most of) the test
// cases with different types of data sources.  Note that in test cases
// we need to use 'this' to refer to member variables of the test class.
template <typename ACCESSOR_TYPE>
class DatabaseClientTest : public ::testing::Test {
public:
    DatabaseClientTest() : zname_("example.org"), qname_("www.example.org"),
                           qclass_(RRClass::IN()), qtype_(RRType::A()),
                           rrttl_(3600)
    {
        createClient();

        // set up the commonly used finder.
        DataSourceClient::FindResult zone(client_->findZone(zname_));
        assert(zone.code == result::SUCCESS);
        finder_ = dynamic_pointer_cast<DatabaseClient::Finder>(
            zone.zone_finder);

        // Test IN/A RDATA to be added in update tests.  Intentionally using
        // different data than the initial data configured in the MockAccessor.
        rrset_.reset(new RRset(qname_, qclass_, qtype_, rrttl_));
        rrset_->addRdata(rdata::createRdata(rrset_->getType(),
                                            rrset_->getClass(), "192.0.2.2"));

        // And its RRSIG.  Also different from the configured one.
        rrsigset_.reset(new RRset(qname_, qclass_, RRType::RRSIG(),
                                  rrttl_));
        rrsigset_->addRdata(rdata::createRdata(rrsigset_->getType(),
                                               rrsigset_->getClass(),
                                               "A 5 3 0 20000101000000 "
                                               "20000201000000 0 example.org. "
                                               "FAKEFAKEFAKE"));
    }

    /*
     * We initialize the client from a function, so we can call it multiple
     * times per test.
     */
    void createClient() {
        current_accessor_ = new ACCESSOR_TYPE();
        is_mock_ = (dynamic_cast<MockAccessor*>(current_accessor_) != NULL);
        client_.reset(new DatabaseClient(qclass_,
                                         shared_ptr<ACCESSOR_TYPE>(
                                             current_accessor_)));
    }

    /**
     * Check the zone finder is a valid one and references the zone ID and
     * database available here.
     */
    void checkZoneFinder(const DataSourceClient::FindResult& zone) {
        ASSERT_NE(ZoneFinderPtr(), zone.zone_finder) << "No zone finder";
        shared_ptr<DatabaseClient::Finder> finder(
            dynamic_pointer_cast<DatabaseClient::Finder>(zone.zone_finder));
        ASSERT_NE(shared_ptr<DatabaseClient::Finder>(), finder) <<
            "Wrong type of finder";
        if (is_mock_) {
            EXPECT_EQ(READONLY_ZONE_ID, finder->zone_id());
        }
        EXPECT_EQ(current_accessor_, &finder->getAccessor());
    }

    shared_ptr<DatabaseClient::Finder> getFinder() {
        DataSourceClient::FindResult zone(client_->findZone(zname_));
        EXPECT_EQ(result::SUCCESS, zone.code);
        shared_ptr<DatabaseClient::Finder> finder(
            dynamic_pointer_cast<DatabaseClient::Finder>(zone.zone_finder));
        if (is_mock_) {
            EXPECT_EQ(READONLY_ZONE_ID, finder->zone_id());
        }

        return (finder);
    }

    // Helper methods for update tests
    bool isRollbacked(bool expected = false) const {
        if (is_mock_) {
            const MockAccessor& mock_accessor =
                dynamic_cast<const MockAccessor&>(*update_accessor_);
            return (mock_accessor.isRollbacked());
        } else {
            return (expected);
        }
    }

    void checkLastAdded(const char* const expected[]) const {
        if (is_mock_) {
            const MockAccessor* mock_accessor =
                dynamic_cast<const MockAccessor*>(current_accessor_);
            for (int i = 0; i < DatabaseAccessor::ADD_COLUMN_COUNT; ++i) {
                EXPECT_EQ(expected[i],
                          mock_accessor->getLatestClone()->getLastAdded()[i]);
            }
        }
    }

    void setUpdateAccessor() {
        if (is_mock_) {
            const MockAccessor* mock_accessor =
                dynamic_cast<const MockAccessor*>(current_accessor_);
            update_accessor_ = mock_accessor->getLatestClone();
        }
    }

    // Some tests only work for MockAccessor.  We remember whether our accessor
    // is of that type.
    bool is_mock_;

    // Will be deleted by client_, just keep the current value for comparison.
    ACCESSOR_TYPE* current_accessor_;
    shared_ptr<DatabaseClient> client_;
    const std::string database_name_;

    // The zone finder of the test zone commonly used in various tests.
    shared_ptr<DatabaseClient::Finder> finder_;

    // Some shortcut variables for commonly used test parameters
    const Name zname_; // the zone name stored in the test data source
    const Name qname_; // commonly used name to be found
    const RRClass qclass_;      // commonly used RR class used with qname
    const RRType qtype_;        // commonly used RR type used with qname
    const RRTTL rrttl_;         // commonly used RR TTL
    RRsetPtr rrset_;            // for adding/deleting an RRset
    RRsetPtr rrsigset_;         // for adding/deleting an RRset

    // update related objects to be tested
    ZoneUpdaterPtr updater_;
    shared_ptr<const DatabaseAccessor> update_accessor_;

    // placeholders
    const std::vector<std::string> empty_rdatas_; // for NXRRSET/NXDOMAIN
    std::vector<std::string> expected_rdatas_;
    std::vector<std::string> expected_sig_rdatas_;
};

class TestSQLite3Accessor : public SQLite3Accessor {
public:
    TestSQLite3Accessor() : SQLite3Accessor(
        TEST_DATA_BUILDDIR "/rwtest.sqlite3.copied",
        RRClass::IN())
    {
        startUpdateZone("example.org.", true);
        string columns[ADD_COLUMN_COUNT];
        for (int i = 0; TEST_RECORDS[i][0] != NULL; ++i) {
            columns[ADD_NAME] = TEST_RECORDS[i][0];
            columns[ADD_REV_NAME] = Name(columns[ADD_NAME]).reverse().toText();
            columns[ADD_TYPE] = TEST_RECORDS[i][1];
            columns[ADD_TTL] = TEST_RECORDS[i][2];
            columns[ADD_SIGTYPE] = TEST_RECORDS[i][3];
            columns[ADD_RDATA] = TEST_RECORDS[i][4];

            addRecordToZone(columns);
        }
        commitUpdateZone();
    }
};

// The following two lines instantiate test cases with concrete accessor
// classes to be tested.
typedef ::testing::Types<MockAccessor, TestSQLite3Accessor> TestAccessorTypes;
TYPED_TEST_CASE(DatabaseClientTest, TestAccessorTypes);

// In some cases the entire test fixture is for the mock accessor only.
// We use the usual TEST_F for them with the corresponding specialized class
// to make the code simpler.
typedef DatabaseClientTest<MockAccessor> MockDatabaseClientTest;

TYPED_TEST(DatabaseClientTest, zoneNotFound) {
    DataSourceClient::FindResult zone(
        this->client_->findZone(Name("example.com")));
    EXPECT_EQ(result::NOTFOUND, zone.code);
}

TYPED_TEST(DatabaseClientTest, exactZone) {
    DataSourceClient::FindResult zone(
        this->client_->findZone(Name("example.org")));
    EXPECT_EQ(result::SUCCESS, zone.code);
    this->checkZoneFinder(zone);
}

TYPED_TEST(DatabaseClientTest, superZone) {
    DataSourceClient::FindResult zone(this->client_->findZone(Name(
        "sub.example.org")));
    EXPECT_EQ(result::PARTIALMATCH, zone.code);
    this->checkZoneFinder(zone);
}

// This test doesn't depend on derived accessor class, so we use TEST().
TEST(GenericDatabaseClientTest, noAccessorException) {
    // We need a dummy variable here; some compiler would regard it a mere
    // declaration instead of an instantiation and make the test fail.
    EXPECT_THROW(DatabaseClient dummy(RRClass::IN(),
                                      shared_ptr<DatabaseAccessor>()),
                 isc::InvalidParameter);
}

// If the zone doesn't exist, exception is thrown
TYPED_TEST(DatabaseClientTest, noZoneIterator) {
    EXPECT_THROW(this->client_->getIterator(Name("example.com")),
                 DataSourceError);
}

// If the zone doesn't exist and iteration is not implemented, it still throws
// the exception it doesn't exist
TEST(GenericDatabaseClientTest, noZoneNotImplementedIterator) {
    EXPECT_THROW(DatabaseClient(RRClass::IN(),
                                boost::shared_ptr<DatabaseAccessor>(
                                    new NopAccessor())).getIterator(
                                        Name("example.com")),
                 DataSourceError);
}

TEST(GenericDatabaseClientTest, notImplementedIterator) {
    EXPECT_THROW(DatabaseClient(RRClass::IN(), shared_ptr<DatabaseAccessor>(
        new NopAccessor())).getIterator(Name("example.org")),
                 isc::NotImplemented);
}

// Pretend a bug in the connection and pass NULL as the context
// Should not crash, but gracefully throw.  Works for the mock accessor only.
TEST_F(MockDatabaseClientTest, nullIteratorContext) {
    EXPECT_THROW(this->client_->getIterator(Name("null.example.org")),
                 isc::Unexpected);
}

// It doesn't crash or anything if the zone is completely empty.
// Works for the mock accessor only.
TEST_F(MockDatabaseClientTest, emptyIterator) {
    ZoneIteratorPtr it(this->client_->getIterator(Name("empty.example.org")));
    EXPECT_EQ(ConstRRsetPtr(), it->getNextRRset());
    // This is past the end, it should throw
    EXPECT_THROW(it->getNextRRset(), isc::Unexpected);
}

// Iterate through a zone
TYPED_TEST(DatabaseClientTest, iterator) {
    ZoneIteratorPtr it(this->client_->getIterator(Name("example.org")));
    ConstRRsetPtr rrset(it->getNextRRset());
    ASSERT_NE(ConstRRsetPtr(), rrset);

    // The rest of the checks work only for the mock accessor.
    if (!this->is_mock_) {
        return;
    }

    EXPECT_EQ(Name("example.org"), rrset->getName());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
    EXPECT_EQ(RRType::SOA(), rrset->getType());
    EXPECT_EQ(RRTTL(300), rrset->getTTL());
    RdataIteratorPtr rit(rrset->getRdataIterator());
    ASSERT_FALSE(rit->isLast());
    rit->next();
    EXPECT_TRUE(rit->isLast());

    rrset = it->getNextRRset();
    ASSERT_NE(ConstRRsetPtr(), rrset);
    EXPECT_EQ(Name("x.example.org"), rrset->getName());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
    EXPECT_EQ(RRType::A(), rrset->getType());
    EXPECT_EQ(RRTTL(300), rrset->getTTL());
    rit = rrset->getRdataIterator();
    ASSERT_FALSE(rit->isLast());
    EXPECT_EQ("192.0.2.1", rit->getCurrent().toText());
    rit->next();
    ASSERT_FALSE(rit->isLast());
    EXPECT_EQ("192.0.2.2", rit->getCurrent().toText());
    rit->next();
    EXPECT_TRUE(rit->isLast());

    rrset = it->getNextRRset();
    ASSERT_NE(ConstRRsetPtr(), rrset);
    EXPECT_EQ(Name("x.example.org"), rrset->getName());
    EXPECT_EQ(RRClass::IN(), rrset->getClass());
    EXPECT_EQ(RRType::AAAA(), rrset->getType());
    EXPECT_EQ(RRTTL(300), rrset->getTTL());
    EXPECT_EQ(ConstRRsetPtr(), it->getNextRRset());
    rit = rrset->getRdataIterator();
    ASSERT_FALSE(rit->isLast());
    EXPECT_EQ("2001:db8::1", rit->getCurrent().toText());
    rit->next();
    ASSERT_FALSE(rit->isLast());
    EXPECT_EQ("2001:db8::2", rit->getCurrent().toText());
    rit->next();
    EXPECT_TRUE(rit->isLast());
}

// This has inconsistent TTL in the set (the rest, like nonsense in
// the data is handled in rdata itself).  Works for the mock accessor only.
TEST_F(MockDatabaseClientTest, badIterator) {
    // It should not throw, but get the lowest one of them
    ZoneIteratorPtr it(this->client_->getIterator(Name("bad.example.org")));
    EXPECT_EQ(it->getNextRRset()->getTTL(), isc::dns::RRTTL(300));
}

// checks if the given rrset matches the
// given name, class, type and rdatas
void
checkRRset(isc::dns::ConstRRsetPtr rrset,
           const isc::dns::Name& name,
           const isc::dns::RRClass& rrclass,
           const isc::dns::RRType& rrtype,
           const isc::dns::RRTTL& rrttl,
           const std::vector<std::string>& rdatas) {
    isc::dns::RRsetPtr expected_rrset(
        new isc::dns::RRset(name, rrclass, rrtype, rrttl));
    for (unsigned int i = 0; i < rdatas.size(); ++i) {
        expected_rrset->addRdata(
            isc::dns::rdata::createRdata(rrtype, rrclass,
                                         rdatas[i]));
    }
    isc::testutils::rrsetCheck(expected_rrset, rrset);
}

void
doFindTest(ZoneFinder& finder,
           const isc::dns::Name& name,
           const isc::dns::RRType& type,
           const isc::dns::RRType& expected_type,
           const isc::dns::RRTTL expected_ttl,
           ZoneFinder::Result expected_result,
           const std::vector<std::string>& expected_rdatas,
           const std::vector<std::string>& expected_sig_rdatas,
           const isc::dns::Name& expected_name = isc::dns::Name::ROOT_NAME(),
           const ZoneFinder::FindOptions options = ZoneFinder::FIND_DEFAULT)
{
    SCOPED_TRACE("doFindTest " + name.toText() + " " + type.toText());
    ZoneFinder::FindResult result =
        finder.find(name, type, NULL, options);
    ASSERT_EQ(expected_result, result.code) << name << " " << type;
    if (!expected_rdatas.empty() && result.rrset) {
        checkRRset(result.rrset, expected_name != Name(".") ? expected_name :
                   name, finder.getClass(), expected_type, expected_ttl,
                   expected_rdatas);

        if (!expected_sig_rdatas.empty() && result.rrset->getRRsig()) {
            checkRRset(result.rrset->getRRsig(), expected_name != Name(".") ?
                       expected_name : name, finder.getClass(),
                       isc::dns::RRType::RRSIG(), expected_ttl,
                       expected_sig_rdatas);
        } else if (expected_sig_rdatas.empty()) {
            EXPECT_EQ(isc::dns::RRsetPtr(), result.rrset->getRRsig());
        } else {
            ADD_FAILURE() << "Missing RRSIG";
        }
    } else if (expected_rdatas.empty()) {
        EXPECT_EQ(isc::dns::RRsetPtr(), result.rrset);
    } else {
        ADD_FAILURE() << "Missing result";
    }
}

TYPED_TEST(DatabaseClientTest, find) {
    shared_ptr<DatabaseClient::Finder> finder(this->getFinder());

    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.1");
    doFindTest(*finder, isc::dns::Name("www.example.org."),
               this->qtype_, this->qtype_, this->rrttl_, ZoneFinder::SUCCESS,
               this->expected_rdatas_, this->expected_sig_rdatas_);

    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.1");
    this->expected_rdatas_.push_back("192.0.2.2");
    doFindTest(*finder, isc::dns::Name("www2.example.org."),
               this->qtype_, this->qtype_, this->rrttl_, ZoneFinder::SUCCESS,
               this->expected_rdatas_, this->expected_sig_rdatas_);

    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    this->expected_rdatas_.push_back("2001:db8::1");
    this->expected_rdatas_.push_back("2001:db8::2");
    doFindTest(*finder, isc::dns::Name("www.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               this->rrttl_,
               ZoneFinder::SUCCESS,
               this->expected_rdatas_, this->expected_sig_rdatas_);

    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    doFindTest(*finder, isc::dns::Name("www.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::TXT(),
               this->rrttl_,
               ZoneFinder::NXRRSET,
               this->expected_rdatas_, this->expected_sig_rdatas_);

    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    this->expected_rdatas_.push_back("www.example.org.");
    doFindTest(*finder, isc::dns::Name("cname.example.org."),
               this->qtype_, isc::dns::RRType::CNAME(), this->rrttl_,
               ZoneFinder::CNAME, this->expected_rdatas_,
               this->expected_sig_rdatas_);

    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    this->expected_rdatas_.push_back("www.example.org.");
    doFindTest(*finder, isc::dns::Name("cname.example.org."),
               isc::dns::RRType::CNAME(), isc::dns::RRType::CNAME(),
               this->rrttl_, ZoneFinder::SUCCESS, this->expected_rdatas_,
               this->expected_sig_rdatas_);

    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    doFindTest(*finder, isc::dns::Name("doesnotexist.example.org."),
               this->qtype_, this->qtype_, this->rrttl_, ZoneFinder::NXDOMAIN,
               this->expected_rdatas_, this->expected_sig_rdatas_);

    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.1");
    this->expected_sig_rdatas_.push_back("A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    this->expected_sig_rdatas_.push_back("A 5 3 3600 20000101000000 20000201000000 12346 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("signed1.example.org."),
               this->qtype_, this->qtype_, this->rrttl_, ZoneFinder::SUCCESS,
               this->expected_rdatas_, this->expected_sig_rdatas_);

    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    this->expected_rdatas_.push_back("2001:db8::1");
    this->expected_rdatas_.push_back("2001:db8::2");
    this->expected_sig_rdatas_.push_back("AAAA 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("signed1.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               this->rrttl_, ZoneFinder::SUCCESS, this->expected_rdatas_,
               this->expected_sig_rdatas_);

    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    doFindTest(*finder, isc::dns::Name("signed1.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::TXT(), this->rrttl_,
               ZoneFinder::NXRRSET, this->expected_rdatas_,
               this->expected_sig_rdatas_);

    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    this->expected_rdatas_.push_back("www.example.org.");
    this->expected_sig_rdatas_.push_back("CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("signedcname1.example.org."),
               this->qtype_, isc::dns::RRType::CNAME(), this->rrttl_,
               ZoneFinder::CNAME, this->expected_rdatas_,
               this->expected_sig_rdatas_);

    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.1");
    this->expected_sig_rdatas_.push_back("A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    this->expected_sig_rdatas_.push_back("A 5 3 3600 20000101000000 20000201000000 12346 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("signed2.example.org."),
               this->qtype_, this->qtype_, this->rrttl_, ZoneFinder::SUCCESS,
               this->expected_rdatas_, this->expected_sig_rdatas_);

    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    this->expected_rdatas_.push_back("2001:db8::2");
    this->expected_rdatas_.push_back("2001:db8::1");
    this->expected_sig_rdatas_.push_back("AAAA 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("signed2.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               this->rrttl_, ZoneFinder::SUCCESS, this->expected_rdatas_,
               this->expected_sig_rdatas_);

    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    doFindTest(*finder, isc::dns::Name("signed2.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::TXT(), this->rrttl_,
               ZoneFinder::NXRRSET, this->expected_rdatas_,
               this->expected_sig_rdatas_);

    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    this->expected_rdatas_.push_back("www.example.org.");
    this->expected_sig_rdatas_.push_back("CNAME 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("signedcname2.example.org."),
               this->qtype_, isc::dns::RRType::CNAME(), this->rrttl_,
               ZoneFinder::CNAME, this->expected_rdatas_,
               this->expected_sig_rdatas_);

    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.1");
    this->expected_sig_rdatas_.push_back("A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("acnamesig1.example.org."),
               this->qtype_, this->qtype_, this->rrttl_, ZoneFinder::SUCCESS,
               this->expected_rdatas_, this->expected_sig_rdatas_);

    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.1");
    this->expected_sig_rdatas_.push_back("A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("acnamesig2.example.org."),
               this->qtype_, this->qtype_, this->rrttl_, ZoneFinder::SUCCESS,
               this->expected_rdatas_, this->expected_sig_rdatas_);

    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.1");
    this->expected_sig_rdatas_.push_back("A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("acnamesig3.example.org."),
               this->qtype_, this->qtype_, this->rrttl_, ZoneFinder::SUCCESS,
               this->expected_rdatas_, this->expected_sig_rdatas_);

    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.1");
    this->expected_rdatas_.push_back("192.0.2.2");
    doFindTest(*finder, isc::dns::Name("ttldiff1.example.org."),
               this->qtype_, this->qtype_, isc::dns::RRTTL(360),
               ZoneFinder::SUCCESS, this->expected_rdatas_,
               this->expected_sig_rdatas_);

    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.1");
    this->expected_rdatas_.push_back("192.0.2.2");
    doFindTest(*finder, isc::dns::Name("ttldiff2.example.org."),
               this->qtype_, this->qtype_, isc::dns::RRTTL(360),
               ZoneFinder::SUCCESS, this->expected_rdatas_,
               this->expected_sig_rdatas_);

    EXPECT_THROW(finder->find(isc::dns::Name("badcname1.example.org."),
                                              this->qtype_,
                                              NULL, ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_THROW(finder->find(isc::dns::Name("badcname2.example.org."),
                                              this->qtype_,
                                              NULL, ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_THROW(finder->find(isc::dns::Name("badcname3.example.org."),
                                              this->qtype_,
                                              NULL, ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_THROW(finder->find(isc::dns::Name("badrdata.example.org."),
                                              this->qtype_,
                                              NULL, ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_THROW(finder->find(isc::dns::Name("badtype.example.org."),
                                              this->qtype_,
                                              NULL, ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_THROW(finder->find(isc::dns::Name("badttl.example.org."),
                                              this->qtype_,
                                              NULL, ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_THROW(finder->find(isc::dns::Name("badsig.example.org."),
                                              this->qtype_,
                                              NULL, ZoneFinder::FIND_DEFAULT),
                 DataSourceError);

    // Trigger the hardcoded exceptions and see if find() has cleaned up
    if (this->is_mock_) {
        EXPECT_THROW(finder->find(isc::dns::Name("dsexception.in.search."),
                                  this->qtype_,
                                  NULL, ZoneFinder::FIND_DEFAULT),
                     DataSourceError);
        EXPECT_THROW(finder->find(isc::dns::Name("iscexception.in.search."),
                                  this->qtype_,
                                  NULL, ZoneFinder::FIND_DEFAULT),
                     isc::Exception);
        EXPECT_THROW(finder->find(isc::dns::Name("basicexception.in.search."),
                                  this->qtype_,
                                  NULL, ZoneFinder::FIND_DEFAULT),
                     std::exception);
        EXPECT_THROW(finder->find(isc::dns::Name("dsexception.in.getnext."),
                                  this->qtype_,
                                  NULL, ZoneFinder::FIND_DEFAULT),
                     DataSourceError);
        EXPECT_THROW(finder->find(isc::dns::Name("iscexception.in.getnext."),
                                  this->qtype_,
                                  NULL, ZoneFinder::FIND_DEFAULT),
                     isc::Exception);
        EXPECT_THROW(finder->find(isc::dns::Name("basicexception.in.getnext."),
                                  this->qtype_,
                                  NULL, ZoneFinder::FIND_DEFAULT),
                     std::exception);
    }

    // This RRSIG has the wrong sigtype field, which should be
    // an error if we decide to keep using that field
    // Right now the field is ignored, so it does not error
    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.1");
    this->expected_sig_rdatas_.push_back("A 5 3 3600 20000101000000 20000201000000 12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("badsigtype.example.org."),
               this->qtype_, this->qtype_, this->rrttl_, ZoneFinder::SUCCESS,
               this->expected_rdatas_, this->expected_sig_rdatas_);
}

TYPED_TEST(DatabaseClientTest, findDelegation) {
    shared_ptr<DatabaseClient::Finder> finder(this->getFinder());

    // The apex should not be considered delegation point and we can access
    // data
    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.1");
    doFindTest(*finder, isc::dns::Name("example.org."),
               this->qtype_, this->qtype_,
               this->rrttl_, ZoneFinder::SUCCESS, this->expected_rdatas_,
               this->expected_sig_rdatas_);

    this->expected_rdatas_.clear();
    this->expected_rdatas_.push_back("ns.example.com.");
    this->expected_sig_rdatas_.push_back("NS 5 3 3600 20000101000000 20000201000000 "
                                  "12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("example.org."),
               isc::dns::RRType::NS(), isc::dns::RRType::NS(),
               this->rrttl_, ZoneFinder::SUCCESS, this->expected_rdatas_,
               this->expected_sig_rdatas_);

    // Check when we ask for something below delegation point, we get the NS
    // (Both when the RRset there exists and doesn't)
    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    this->expected_rdatas_.push_back("ns.example.com.");
    this->expected_rdatas_.push_back("ns.delegation.example.org.");
    this->expected_sig_rdatas_.push_back("NS 5 3 3600 20000101000000 20000201000000 "
                                  "12345 example.org. FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("ns.delegation.example.org."),
               this->qtype_, isc::dns::RRType::NS(),
               this->rrttl_, ZoneFinder::DELEGATION, this->expected_rdatas_,
               this->expected_sig_rdatas_,
               isc::dns::Name("delegation.example.org."));
    doFindTest(*finder, isc::dns::Name("ns.delegation.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::NS(),
               this->rrttl_, ZoneFinder::DELEGATION, this->expected_rdatas_,
               this->expected_sig_rdatas_,
               isc::dns::Name("delegation.example.org."));
    doFindTest(*finder, isc::dns::Name("deep.below.delegation.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::NS(),
               this->rrttl_, ZoneFinder::DELEGATION, this->expected_rdatas_,
               this->expected_sig_rdatas_,
               isc::dns::Name("delegation.example.org."));

    // Even when we check directly at the delegation point, we should get
    // the NS
    doFindTest(*finder, isc::dns::Name("delegation.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::NS(),
               this->rrttl_, ZoneFinder::DELEGATION, this->expected_rdatas_,
               this->expected_sig_rdatas_);

    // And when we ask direcly for the NS, we should still get delegation
    doFindTest(*finder, isc::dns::Name("delegation.example.org."),
               isc::dns::RRType::NS(), isc::dns::RRType::NS(),
               this->rrttl_, ZoneFinder::DELEGATION, this->expected_rdatas_,
               this->expected_sig_rdatas_);

    // Now test delegation. If it is below the delegation point, we should get
    // the DNAME (the one with data under DNAME is invalid zone, but we test
    // the behaviour anyway just to make sure)
    this->expected_rdatas_.clear();
    this->expected_rdatas_.push_back("dname.example.com.");
    this->expected_sig_rdatas_.clear();
    this->expected_sig_rdatas_.push_back("DNAME 5 3 3600 20000101000000 "
                                  "20000201000000 12345 example.org. "
                                  "FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("below.dname.example.org."),
               this->qtype_, isc::dns::RRType::DNAME(),
               this->rrttl_, ZoneFinder::DNAME, this->expected_rdatas_,
               this->expected_sig_rdatas_, isc::dns::Name("dname.example.org."));
    doFindTest(*finder, isc::dns::Name("below.dname.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::DNAME(),
               this->rrttl_, ZoneFinder::DNAME, this->expected_rdatas_,
               this->expected_sig_rdatas_, isc::dns::Name("dname.example.org."));
    doFindTest(*finder, isc::dns::Name("really.deep.below.dname.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::DNAME(),
               this->rrttl_, ZoneFinder::DNAME, this->expected_rdatas_,
               this->expected_sig_rdatas_, isc::dns::Name("dname.example.org."));

    // Asking direcly for DNAME should give SUCCESS
    doFindTest(*finder, isc::dns::Name("dname.example.org."),
               isc::dns::RRType::DNAME(), isc::dns::RRType::DNAME(),
               this->rrttl_, ZoneFinder::SUCCESS, this->expected_rdatas_,
               this->expected_sig_rdatas_);

    // But we don't delegate at DNAME point
    this->expected_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.1");
    this->expected_sig_rdatas_.clear();
    doFindTest(*finder, isc::dns::Name("dname.example.org."),
               this->qtype_, this->qtype_,
               this->rrttl_, ZoneFinder::SUCCESS, this->expected_rdatas_,
               this->expected_sig_rdatas_);
    this->expected_rdatas_.clear();
    doFindTest(*finder, isc::dns::Name("dname.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               this->rrttl_, ZoneFinder::NXRRSET, this->expected_rdatas_,
               this->expected_sig_rdatas_);

    // This is broken dname, it contains two targets
    EXPECT_THROW(finder->find(isc::dns::Name("below.baddname.example.org."),
                              this->qtype_, NULL,
                              ZoneFinder::FIND_DEFAULT),
                 DataSourceError);

    // Broken NS - it lives together with something else
    EXPECT_THROW(finder->find(isc::dns::Name("brokenns1.example.org."),
                              this->qtype_, NULL,
                              ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
    EXPECT_THROW(finder->find(isc::dns::Name("brokenns2.example.org."),
                              this->qtype_, NULL,
                              ZoneFinder::FIND_DEFAULT),
                 DataSourceError);
}

TYPED_TEST(DatabaseClientTest, emptyDomain) {
    shared_ptr<DatabaseClient::Finder> finder(this->getFinder());

    // This domain doesn't exist, but a subdomain of it does.
    // Therefore we should pretend the domain is there, but contains no RRsets
    doFindTest(*finder, isc::dns::Name("b.example.org."), this->qtype_,
               this->qtype_, this->rrttl_, ZoneFinder::NXRRSET,
               this->expected_rdatas_, this->expected_sig_rdatas_);
}

// Glue-OK mode. Just go through NS delegations down (but not through
// DNAME) and pretend it is not there.
TYPED_TEST(DatabaseClientTest, glueOK) {
    shared_ptr<DatabaseClient::Finder> finder(this->getFinder());

    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    doFindTest(*finder, isc::dns::Name("ns.delegation.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               this->rrttl_, ZoneFinder::NXRRSET,
               this->expected_rdatas_, this->expected_sig_rdatas_,
               isc::dns::Name("ns.delegation.example.org."),
               ZoneFinder::FIND_GLUE_OK);
    doFindTest(*finder, isc::dns::Name("nothere.delegation.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               this->rrttl_, ZoneFinder::NXDOMAIN,
               this->expected_rdatas_, this->expected_sig_rdatas_,
               isc::dns::Name("nothere.delegation.example.org."),
               ZoneFinder::FIND_GLUE_OK);
    this->expected_rdatas_.push_back("192.0.2.1");
    doFindTest(*finder, isc::dns::Name("ns.delegation.example.org."),
               this->qtype_, this->qtype_,
               this->rrttl_, ZoneFinder::SUCCESS,
               this->expected_rdatas_, this->expected_sig_rdatas_,
               isc::dns::Name("ns.delegation.example.org."),
               ZoneFinder::FIND_GLUE_OK);
    this->expected_rdatas_.clear();
    this->expected_rdatas_.push_back("ns.example.com.");
    this->expected_rdatas_.push_back("ns.delegation.example.org.");
    this->expected_sig_rdatas_.clear();
    this->expected_sig_rdatas_.push_back("NS 5 3 3600 20000101000000 "
                                   "20000201000000 12345 example.org. "
                                   "FAKEFAKEFAKE");
    // When we request the NS, it should be SUCCESS, not DELEGATION
    // (different in GLUE_OK)
    doFindTest(*finder, isc::dns::Name("delegation.example.org."),
               isc::dns::RRType::NS(), isc::dns::RRType::NS(),
               this->rrttl_, ZoneFinder::SUCCESS,
               this->expected_rdatas_, this->expected_sig_rdatas_,
               isc::dns::Name("delegation.example.org."),
               ZoneFinder::FIND_GLUE_OK);
    this->expected_rdatas_.clear();
    this->expected_rdatas_.push_back("dname.example.com.");
    this->expected_sig_rdatas_.clear();
    this->expected_sig_rdatas_.push_back("DNAME 5 3 3600 20000101000000 "
                                   "20000201000000 12345 example.org. "
                                   "FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("below.dname.example.org."),
               this->qtype_, isc::dns::RRType::DNAME(),
               this->rrttl_, ZoneFinder::DNAME, this->expected_rdatas_,
               this->expected_sig_rdatas_,
               isc::dns::Name("dname.example.org."), ZoneFinder::FIND_GLUE_OK);
    doFindTest(*finder, isc::dns::Name("below.dname.example.org."),
               isc::dns::RRType::AAAA(), isc::dns::RRType::DNAME(),
               this->rrttl_, ZoneFinder::DNAME, this->expected_rdatas_,
               this->expected_sig_rdatas_,
               isc::dns::Name("dname.example.org."), ZoneFinder::FIND_GLUE_OK);
}

TYPED_TEST(DatabaseClientTest, wildcard) {
    shared_ptr<DatabaseClient::Finder> finder(this->getFinder());

    // First, simple wildcard match
    // Check also that the RRSIG is added from the wildcard (not modified)
    this->expected_rdatas_.push_back("192.0.2.5");
    this->expected_sig_rdatas_.push_back("A 5 3 3600 20000101000000 "
                                         "20000201000000 12345 example.org. "
                                         "FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("a.wild.example.org"),
               this->qtype_, this->qtype_, this->rrttl_,
               ZoneFinder::WILDCARD, this->expected_rdatas_,
               this->expected_sig_rdatas_);
    doFindTest(*finder, isc::dns::Name("b.a.wild.example.org"),
               this->qtype_, this->qtype_, this->rrttl_, ZoneFinder::WILDCARD,
               this->expected_rdatas_, this->expected_sig_rdatas_);
    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    doFindTest(*finder, isc::dns::Name("a.wild.example.org"),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               this->rrttl_, ZoneFinder::WILDCARD_NXRRSET,
               this->expected_rdatas_, this->expected_sig_rdatas_);
    doFindTest(*finder, isc::dns::Name("b.a.wild.example.org"),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               this->rrttl_, ZoneFinder::WILDCARD_NXRRSET,
               this->expected_rdatas_, this->expected_sig_rdatas_);

    // Direct request for this wildcard
    this->expected_rdatas_.push_back("192.0.2.5");
    this->expected_sig_rdatas_.push_back("A 5 3 3600 20000101000000 "
                                         "20000201000000 12345 example.org. "
                                         "FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("*.wild.example.org"),
               this->qtype_, this->qtype_, this->rrttl_, ZoneFinder::SUCCESS,
               this->expected_rdatas_, this->expected_sig_rdatas_);
    this->expected_rdatas_.clear();
    this->expected_sig_rdatas_.clear();
    doFindTest(*finder, isc::dns::Name("*.wild.example.org"),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               this->rrttl_, ZoneFinder::NXRRSET, this->expected_rdatas_,
               this->expected_sig_rdatas_);
    // This is nonsense, but check it doesn't match by some stupid accident
    doFindTest(*finder, isc::dns::Name("a.*.wild.example.org"),
               this->qtype_, this->qtype_, this->rrttl_, ZoneFinder::NXDOMAIN,
               this->expected_rdatas_, this->expected_sig_rdatas_);
    // These should be canceled, since it is below a domain which exitsts
    doFindTest(*finder, isc::dns::Name("nothing.here.wild.example.org"),
               this->qtype_, this->qtype_, this->rrttl_, ZoneFinder::NXDOMAIN,
               this->expected_rdatas_, this->expected_sig_rdatas_);
    doFindTest(*finder, isc::dns::Name("cancel.here.wild.example.org"),
               this->qtype_, this->qtype_, this->rrttl_, ZoneFinder::NXRRSET,
               this->expected_rdatas_, this->expected_sig_rdatas_);
    doFindTest(*finder,
               isc::dns::Name("below.cancel.here.wild.example.org"),
               this->qtype_, this->qtype_, this->rrttl_, ZoneFinder::NXDOMAIN,
               this->expected_rdatas_, this->expected_sig_rdatas_);
    // And this should be just plain empty non-terminal domain, check
    // the wildcard doesn't hurt it
    doFindTest(*finder, isc::dns::Name("here.wild.example.org"),
               this->qtype_, this->qtype_, this->rrttl_, ZoneFinder::NXRRSET,
               this->expected_rdatas_, this->expected_sig_rdatas_);
    // Also make sure that the wildcard doesn't hurt the original data
    // below the wildcard
    this->expected_rdatas_.push_back("2001:db8::5");
    doFindTest(*finder, isc::dns::Name("cancel.here.wild.example.org"),
               isc::dns::RRType::AAAA(), isc::dns::RRType::AAAA(),
               this->rrttl_, ZoneFinder::SUCCESS,
               this->expected_rdatas_, this->expected_sig_rdatas_);
    this->expected_rdatas_.clear();

    // How wildcard go together with delegation
    this->expected_rdatas_.push_back("ns.example.com.");
    doFindTest(*finder, isc::dns::Name("below.delegatedwild.example.org"),
               this->qtype_, isc::dns::RRType::NS(), this->rrttl_,
               ZoneFinder::DELEGATION, this->expected_rdatas_,
               this->expected_sig_rdatas_,
               isc::dns::Name("delegatedwild.example.org"));
    // FIXME: This doesn't look logically OK, GLUE_OK should make it transparent,
    // so the match should either work or be canceled, but return NXDOMAIN
    doFindTest(*finder, isc::dns::Name("below.delegatedwild.example.org"),
               this->qtype_, isc::dns::RRType::NS(), this->rrttl_,
               ZoneFinder::DELEGATION, this->expected_rdatas_,
               this->expected_sig_rdatas_,
               isc::dns::Name("delegatedwild.example.org"),
               ZoneFinder::FIND_GLUE_OK);

    this->expected_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.5");
    // These are direct matches
    const char* positive_names[] = {
        "wild.*.foo.example.org.",
        "wild.*.foo.*.bar.example.org.",
        NULL
    };
    for (const char** name(positive_names); *name != NULL; ++ name) {
        doFindTest(*finder, isc::dns::Name(*name), this->qtype_,
                   this->qtype_, this->rrttl_, ZoneFinder::SUCCESS,
                   this->expected_rdatas_,
                   this->expected_sig_rdatas_);
    }

    // These are wildcard matches against empty nonterminal asterisk
    this->expected_rdatas_.clear();
    const char* negative_names[] = {
        "a.foo.example.org.",
        "*.foo.example.org.",
        "foo.example.org.",
        "wild.bar.foo.example.org.",
        "baz.foo.*.bar.example.org",
        "baz.foo.baz.bar.example.org",
        "*.foo.baz.bar.example.org",
        "*.foo.*.bar.example.org",
        "foo.*.bar.example.org",
        "*.bar.example.org",
        "bar.example.org",
        NULL
    };
    for (const char** name(negative_names); *name != NULL; ++ name) {
        doFindTest(*finder, isc::dns::Name(*name), this->qtype_,
                   this->qtype_, this->rrttl_, ZoneFinder::NXRRSET,
                   this->expected_rdatas_, this->expected_sig_rdatas_);
        // FIXME: What should be returned in this case? How does the
        // DNSSEC logic handle it?
    }
}

TYPED_TEST(DatabaseClientTest, NXRRSET_NSEC) {
    // The domain exists, but doesn't have this RRType
    // So we should get it's NSEC
    shared_ptr<DatabaseClient::Finder> finder(this->getFinder());

    this->expected_rdatas_.push_back("www2.example.org. A AAAA NSEC RRSIG");
    this->expected_sig_rdatas_.push_back("NSEC 5 3 3600 20000101000000 "
                                         "20000201000000 12345 example.org. "
                                         "FAKEFAKEFAKE");
    doFindTest(*finder, isc::dns::Name("www.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::NSEC(),
               isc::dns::RRTTL(3600),
               ZoneFinder::NXRRSET,
               this->expected_rdatas_, this->expected_sig_rdatas_,
               Name::ROOT_NAME(), ZoneFinder::FIND_DNSSEC);
}

TYPED_TEST(DatabaseClientTest, wildcardNXRRSET_NSEC) {
    // The domain exists, but doesn't have this RRType
    // So we should get it's NSEC
    //
    // The user will have to query us again to get the correct
    // answer (eg. prove there's not an exact match)
    shared_ptr<DatabaseClient::Finder> finder(this->getFinder());

    this->expected_rdatas_.push_back("cancel.here.wild.example.org. A NSEC "
                                     "RRSIG");
    this->expected_sig_rdatas_.push_back("NSEC 5 3 3600 20000101000000 "
                                         "20000201000000 12345 example.org. "
                                         "FAKEFAKEFAKE");
    // Note that the NSEC name should NOT be synthesized.
    doFindTest(*finder, isc::dns::Name("a.wild.example.org."),
               isc::dns::RRType::TXT(), isc::dns::RRType::NSEC(),
               isc::dns::RRTTL(3600),
               ZoneFinder::WILDCARD_NXRRSET,
               this->expected_rdatas_, this->expected_sig_rdatas_,
               Name("*.wild.example.org"), ZoneFinder::FIND_DNSSEC);
}


TYPED_TEST(DatabaseClientTest, getOrigin) {
    DataSourceClient::FindResult
        zone(this->client_->findZone(Name("example.org")));
    ASSERT_EQ(result::SUCCESS, zone.code);
    shared_ptr<DatabaseClient::Finder> finder(
        dynamic_pointer_cast<DatabaseClient::Finder>(zone.zone_finder));
    if (this->is_mock_) {
        EXPECT_EQ(READONLY_ZONE_ID, finder->zone_id());
    }
    EXPECT_EQ(this->zname_, finder->getOrigin());
}

TYPED_TEST(DatabaseClientTest, updaterFinder) {
    this->updater_ = this->client_->getUpdater(this->zname_, false);
    ASSERT_TRUE(this->updater_);

    // If this update isn't replacing the zone, the finder should work
    // just like the normal find() case.
    if (this->is_mock_) {
        DatabaseClient::Finder& finder = dynamic_cast<DatabaseClient::Finder&>(
            this->updater_->getFinder());
        EXPECT_EQ(WRITABLE_ZONE_ID, finder.zone_id());
    }
    this->expected_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.1");
    doFindTest(this->updater_->getFinder(), this->qname_,
               this->qtype_, this->qtype_, this->rrttl_, ZoneFinder::SUCCESS,
               this->expected_rdatas_, this->empty_rdatas_);

    // When replacing the zone, the updater's finder shouldn't see anything
    // in the zone until something is added.
    this->updater_.reset();
    this->updater_ = this->client_->getUpdater(this->zname_, true);
    ASSERT_TRUE(this->updater_);
    if (this->is_mock_) {
        DatabaseClient::Finder& finder = dynamic_cast<DatabaseClient::Finder&>(
            this->updater_->getFinder());
        EXPECT_EQ(WRITABLE_ZONE_ID, finder.zone_id());
    }
    doFindTest(this->updater_->getFinder(), this->qname_, this->qtype_,
               this->qtype_, this->rrttl_, ZoneFinder::NXDOMAIN,
               this->empty_rdatas_, this->empty_rdatas_);
}

TYPED_TEST(DatabaseClientTest, flushZone) {
    // A simple update case: flush the entire zone
    shared_ptr<DatabaseClient::Finder> finder(this->getFinder());

    // Before update, the name exists.
    EXPECT_EQ(ZoneFinder::SUCCESS, finder->find(this->qname_,
                                                this->qtype_).code);

    // start update in the replace mode.  the normal finder should still
    // be able to see the record, but the updater's finder shouldn't.
    this->updater_ = this->client_->getUpdater(this->zname_, true);
    this->setUpdateAccessor();
    EXPECT_EQ(ZoneFinder::SUCCESS,
              finder->find(this->qname_, this->qtype_).code);
    EXPECT_EQ(ZoneFinder::NXDOMAIN,
              this->updater_->getFinder().find(this->qname_,
                                               this->qtype_).code);

    // commit the update.  now the normal finder shouldn't see it.
    this->updater_->commit();
    EXPECT_EQ(ZoneFinder::NXDOMAIN, finder->find(this->qname_,
                                                 this->qtype_).code);

    // Check rollback wasn't accidentally performed.
    EXPECT_FALSE(this->isRollbacked());
}

TYPED_TEST(DatabaseClientTest, updateCancel) {
    // similar to the previous test, but destruct the updater before commit.

    ZoneFinderPtr finder = this->client_->findZone(this->zname_).zone_finder;
    EXPECT_EQ(ZoneFinder::SUCCESS, finder->find(this->qname_,
                                                this->qtype_).code);

    this->updater_ = this->client_->getUpdater(this->zname_, true);
    this->setUpdateAccessor();
    EXPECT_EQ(ZoneFinder::NXDOMAIN,
              this->updater_->getFinder().find(this->qname_,
                                               this->qtype_).code);
    // DB should not have been rolled back yet.
    EXPECT_FALSE(this->isRollbacked());
    this->updater_.reset();            // destruct without commit

    // reset() should have triggered rollback (although it doesn't affect
    // anything to the mock accessor implementation except for the result of
    // isRollbacked())
    EXPECT_TRUE(this->isRollbacked(true));
    EXPECT_EQ(ZoneFinder::SUCCESS, finder->find(this->qname_,
                                                this->qtype_).code);
}

TYPED_TEST(DatabaseClientTest, exceptionFromRollback) {
    this->updater_ = this->client_->getUpdater(this->zname_, true);

    this->rrset_.reset(new RRset(Name("throw.example.org"), this->qclass_,
                                 this->qtype_, this->rrttl_));
    this->rrset_->addRdata(rdata::createRdata(this->rrset_->getType(),
                                              this->rrset_->getClass(),
                                              "192.0.2.1"));
    this->updater_->addRRset(*this->rrset_);
    // destruct without commit.  The added name will result in an exception
    // in the MockAccessor's rollback method.  It shouldn't be propagated.
    EXPECT_NO_THROW(this->updater_.reset());
}

TYPED_TEST(DatabaseClientTest, duplicateCommit) {
    // duplicate commit.  should result in exception.
    this->updater_ = this->client_->getUpdater(this->zname_, true);
    this->updater_->commit();
    EXPECT_THROW(this->updater_->commit(), DataSourceError);
}

TYPED_TEST(DatabaseClientTest, addRRsetToNewZone) {
    // Add a single RRset to a fresh empty zone
    this->updater_ = this->client_->getUpdater(this->zname_, true);
    this->updater_->addRRset(*this->rrset_);

    this->expected_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.2");
    {
        SCOPED_TRACE("add RRset");
        doFindTest(this->updater_->getFinder(), this->qname_, this->qtype_,
                   this->qtype_, this->rrttl_, ZoneFinder::SUCCESS,
                   this->expected_rdatas_, this->empty_rdatas_);
    }

    // Similar to the previous case, but with RRSIG
    this->updater_.reset();
    this->updater_ = this->client_->getUpdater(this->zname_, true);
    this->updater_->addRRset(*this->rrset_);
    this->updater_->addRRset(*this->rrsigset_);

    // confirm the expected columns were passed to the accessor (if checkable).
    const char* const rrsig_added[] = {
        "www.example.org.", "org.example.www.", "3600", "RRSIG", "A",
        "A 5 3 0 20000101000000 20000201000000 0 example.org. FAKEFAKEFAKE"
    };
    this->checkLastAdded(rrsig_added);

    this->expected_sig_rdatas_.clear();
    this->expected_sig_rdatas_.push_back(
        rrsig_added[DatabaseAccessor::ADD_RDATA]);
    {
        SCOPED_TRACE("add RRset with RRSIG");
        doFindTest(this->updater_->getFinder(), this->qname_, this->qtype_,
                   this->qtype_, this->rrttl_, ZoneFinder::SUCCESS,
                   this->expected_rdatas_, this->expected_sig_rdatas_);
    }

    // Add the non RRSIG RRset again, to see the attempt of adding RRSIG
    // causes any unexpected effect, in particular, whether the SIGTYPE
    // field might remain.
    this->updater_->addRRset(*this->rrset_);
    const char* const rrset_added[] = {
        "www.example.org.", "org.example.www.", "3600", "A", "", "192.0.2.2"
    };
    this->checkLastAdded(rrset_added);
}

TYPED_TEST(DatabaseClientTest, addRRsetToCurrentZone) {
    // Similar to the previous test, but not replacing the existing data.
    shared_ptr<DatabaseClient::Finder> finder(this->getFinder());

    this->updater_ = this->client_->getUpdater(this->zname_, false);
    this->updater_->addRRset(*this->rrset_);

    // We should see both old and new data.
    this->expected_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.1");
    this->expected_rdatas_.push_back("192.0.2.2");
    {
        SCOPED_TRACE("add RRset");
        doFindTest(this->updater_->getFinder(), this->qname_, this->qtype_,
                   this->qtype_, this->rrttl_, ZoneFinder::SUCCESS,
                   this->expected_rdatas_, this->empty_rdatas_);
    }
    this->updater_->commit();
    {
        SCOPED_TRACE("add RRset after commit");
        doFindTest(*finder, this->qname_, this->qtype_, this->qtype_,
                   this->rrttl_, ZoneFinder::SUCCESS, this->expected_rdatas_,
                   this->empty_rdatas_);
    }
}

TYPED_TEST(DatabaseClientTest, addMultipleRRs) {
    // Similar to the previous case, but the added RRset contains multiple
    // RRs.
    this->updater_ = this->client_->getUpdater(this->zname_, false);
    this->rrset_->addRdata(rdata::createRdata(this->rrset_->getType(),
                                              this->rrset_->getClass(),
                                              "192.0.2.3"));
    this->updater_->addRRset(*this->rrset_);
    this->expected_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.1");
    this->expected_rdatas_.push_back("192.0.2.2");
    this->expected_rdatas_.push_back("192.0.2.3");
    {
        SCOPED_TRACE("add multiple RRs");
        doFindTest(this->updater_->getFinder(), this->qname_, this->qtype_,
                   this->qtype_, this->rrttl_, ZoneFinder::SUCCESS,
                   this->expected_rdatas_, this->empty_rdatas_);
    }
}

TYPED_TEST(DatabaseClientTest, addRRsetOfLargerTTL) {
    // Similar to the previous one, but the TTL of the added RRset is larger
    // than that of the existing record.  The finder should use the smaller
    // one.
    this->updater_ = this->client_->getUpdater(this->zname_, false);
    this->rrset_->setTTL(RRTTL(7200));
    this->updater_->addRRset(*this->rrset_);

    this->expected_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.1");
    this->expected_rdatas_.push_back("192.0.2.2");
    {
        SCOPED_TRACE("add RRset of larger TTL");
        doFindTest(this->updater_->getFinder(), this->qname_, this->qtype_,
                   this->qtype_, this->rrttl_, ZoneFinder::SUCCESS,
                   this->expected_rdatas_, this->empty_rdatas_);
    }
}

TYPED_TEST(DatabaseClientTest, addRRsetOfSmallerTTL) {
    // Similar to the previous one, but the added RRset has a smaller TTL.
    // The added TTL should be used by the finder.
    this->updater_ = this->client_->getUpdater(this->zname_, false);
    this->rrset_->setTTL(RRTTL(1800));
    this->updater_->addRRset(*this->rrset_);

    this->expected_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.1");
    this->expected_rdatas_.push_back("192.0.2.2");
    {
        SCOPED_TRACE("add RRset of smaller TTL");
        doFindTest(this->updater_->getFinder(), this->qname_, this->qtype_,
                   this->qtype_, RRTTL(1800), ZoneFinder::SUCCESS,
                   this->expected_rdatas_, this->empty_rdatas_);
    }
}

TYPED_TEST(DatabaseClientTest, addSameRR) {
    // Add the same RR as that is already in the data source.
    // Currently the add interface doesn't try to suppress the duplicate,
    // neither does the finder.  We may want to revisit it in future versions.

    this->updater_ = this->client_->getUpdater(this->zname_, false);
    this->rrset_.reset(new RRset(this->qname_, this->qclass_, this->qtype_,
                                 this->rrttl_));
    this->rrset_->addRdata(rdata::createRdata(this->rrset_->getType(),
                                              this->rrset_->getClass(),
                                              "192.0.2.1"));
    this->updater_->addRRset(*this->rrset_);
    this->expected_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.1");
    this->expected_rdatas_.push_back("192.0.2.1");
    {
        SCOPED_TRACE("add same RR");
        doFindTest(this->updater_->getFinder(), this->qname_, this->qtype_,
                   this->qtype_, this->rrttl_, ZoneFinder::SUCCESS,
                   this->expected_rdatas_, this->empty_rdatas_);
    }
}

TYPED_TEST(DatabaseClientTest, addDeviantRR) {
    this->updater_ = this->client_->getUpdater(this->zname_, false);

    // RR class mismatch.  This should be detected and rejected.
    this->rrset_.reset(new RRset(this->qname_, RRClass::CH(), RRType::TXT(),
                                 this->rrttl_));
    this->rrset_->addRdata(rdata::createRdata(this->rrset_->getType(),
                                              this->rrset_->getClass(),
                                              "test text"));
    EXPECT_THROW(this->updater_->addRRset(*this->rrset_), DataSourceError);

    // Out-of-zone owner name.  At a higher level this should be rejected,
    // but it doesn't happen in this interface.
    this->rrset_.reset(new RRset(Name("example.com"), this->qclass_,
                                 this->qtype_, this->rrttl_));
    this->rrset_->addRdata(rdata::createRdata(this->rrset_->getType(),
                                              this->rrset_->getClass(),
                                              "192.0.2.100"));
    this->updater_->addRRset(*this->rrset_);

    this->expected_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.100");
    {
        // Note: with the find() implementation being more strict about
        // zone cuts, this test may fail.  Then the test should be updated.
        SCOPED_TRACE("add out-of-zone RR");
        doFindTest(this->updater_->getFinder(), Name("example.com"),
                   this->qtype_, this->qtype_, this->rrttl_,
                   ZoneFinder::SUCCESS, this->expected_rdatas_,
                   this->empty_rdatas_);
    }
}

TYPED_TEST(DatabaseClientTest, addEmptyRRset) {
    this->updater_ = this->client_->getUpdater(this->zname_, false);
    this->rrset_.reset(new RRset(this->qname_, this->qclass_, this->qtype_,
                                 this->rrttl_));
    EXPECT_THROW(this->updater_->addRRset(*this->rrset_), DataSourceError);
}

TYPED_TEST(DatabaseClientTest, addAfterCommit) {
   this->updater_ = this->client_->getUpdater(this->zname_, false);
   this->updater_->commit();
   EXPECT_THROW(this->updater_->addRRset(*this->rrset_), DataSourceError);
}

TYPED_TEST(DatabaseClientTest, addRRsetWithRRSIG) {
    this->updater_ = this->client_->getUpdater(this->zname_, false);
    this->rrset_->addRRsig(*this->rrsigset_);
    EXPECT_THROW(this->updater_->addRRset(*this->rrset_), DataSourceError);
}

TYPED_TEST(DatabaseClientTest, deleteRRset) {
    shared_ptr<DatabaseClient::Finder> finder(this->getFinder());

    this->rrset_.reset(new RRset(this->qname_, this->qclass_, this->qtype_,
                                 this->rrttl_));
    this->rrset_->addRdata(rdata::createRdata(this->rrset_->getType(),
                                              this->rrset_->getClass(),
                                              "192.0.2.1"));

    // Delete one RR from an RRset
    this->updater_ = this->client_->getUpdater(this->zname_, false);
    this->updater_->deleteRRset(*this->rrset_);

    // Delete the only RR of a name
    this->rrset_.reset(new RRset(Name("cname.example.org"), this->qclass_,
                          RRType::CNAME(), this->rrttl_));
    this->rrset_->addRdata(rdata::createRdata(this->rrset_->getType(),
                                              this->rrset_->getClass(),
                                              "www.example.org"));
    this->updater_->deleteRRset(*this->rrset_);

    // The this->updater_ finder should immediately see the deleted results.
    {
        SCOPED_TRACE("delete RRset");
        doFindTest(this->updater_->getFinder(), this->qname_, this->qtype_,
                   this->qtype_, this->rrttl_, ZoneFinder::NXRRSET,
                   this->empty_rdatas_, this->empty_rdatas_);
        doFindTest(this->updater_->getFinder(), Name("cname.example.org"),
                   this->qtype_, this->qtype_, this->rrttl_,
                   ZoneFinder::NXDOMAIN, this->empty_rdatas_,
                   this->empty_rdatas_);
    }

    // before committing the change, the original finder should see the
    // original record.
    {
        SCOPED_TRACE("delete RRset before commit");
        this->expected_rdatas_.push_back("192.0.2.1");
        doFindTest(*finder, this->qname_, this->qtype_, this->qtype_,
                   this->rrttl_, ZoneFinder::SUCCESS, this->expected_rdatas_,
                   this->empty_rdatas_);

        this->expected_rdatas_.clear();
        this->expected_rdatas_.push_back("www.example.org.");
        doFindTest(*finder, Name("cname.example.org"), this->qtype_,
                   RRType::CNAME(), this->rrttl_, ZoneFinder::CNAME,
                   this->expected_rdatas_, this->empty_rdatas_);
    }

    // once committed, the record should be removed from the original finder's
    // view, too.
    this->updater_->commit();
    {
        SCOPED_TRACE("delete RRset after commit");
        doFindTest(*finder, this->qname_, this->qtype_, this->qtype_,
                   this->rrttl_, ZoneFinder::NXRRSET, this->empty_rdatas_,
                   this->empty_rdatas_);
        doFindTest(*finder, Name("cname.example.org"), this->qtype_,
                   this->qtype_, this->rrttl_, ZoneFinder::NXDOMAIN,
                   this->empty_rdatas_, this->empty_rdatas_);
    }
}

TYPED_TEST(DatabaseClientTest, deleteRRsetToNXDOMAIN) {
    // similar to the previous case, but it removes the only record of the
    // given name.  a subsequent find() should result in NXDOMAIN.
    this->rrset_.reset(new RRset(Name("cname.example.org"), this->qclass_,
                           RRType::CNAME(), this->rrttl_));
    this->rrset_->addRdata(rdata::createRdata(this->rrset_->getType(),
                                              this->rrset_->getClass(),
                                              "www.example.org"));

    this->updater_ = this->client_->getUpdater(this->zname_, false);
    this->updater_->deleteRRset(*this->rrset_);
    {
        SCOPED_TRACE("delete RRset to NXDOMAIN");
        doFindTest(this->updater_->getFinder(), Name("cname.example.org"),
                   this->qtype_, this->qtype_, this->rrttl_,
                   ZoneFinder::NXDOMAIN, this->empty_rdatas_,
                   this->empty_rdatas_);
    }
}

TYPED_TEST(DatabaseClientTest, deleteMultipleRRs) {
    this->rrset_.reset(new RRset(this->qname_, this->qclass_, RRType::AAAA(),
                                 this->rrttl_));
    this->rrset_->addRdata(rdata::createRdata(this->rrset_->getType(),
                                              this->rrset_->getClass(),
                                              "2001:db8::1"));
    this->rrset_->addRdata(rdata::createRdata(this->rrset_->getType(),
                                              this->rrset_->getClass(),
                                              "2001:db8::2"));

    this->updater_ = this->client_->getUpdater(this->zname_, false);
    this->updater_->deleteRRset(*this->rrset_);

    {
        SCOPED_TRACE("delete multiple RRs");
        doFindTest(this->updater_->getFinder(), this->qname_, RRType::AAAA(),
                   this->qtype_, this->rrttl_, ZoneFinder::NXRRSET,
                   this->empty_rdatas_, this->empty_rdatas_);
    }
}

TYPED_TEST(DatabaseClientTest, partialDelete) {
    this->rrset_.reset(new RRset(this->qname_, this->qclass_, RRType::AAAA(),
                                 this->rrttl_));
    this->rrset_->addRdata(rdata::createRdata(this->rrset_->getType(),
                                              this->rrset_->getClass(),
                                              "2001:db8::1"));
    // This does not exist in the test data source:
    this->rrset_->addRdata(rdata::createRdata(this->rrset_->getType(),
                                              this->rrset_->getClass(),
                                              "2001:db8::3"));

    // deleteRRset should succeed "silently", and subsequent find() should
    // find the remaining RR.
    this->updater_ = this->client_->getUpdater(this->zname_, false);
    this->updater_->deleteRRset(*this->rrset_);
    {
        SCOPED_TRACE("partial delete");
        this->expected_rdatas_.push_back("2001:db8::2");
        doFindTest(this->updater_->getFinder(), this->qname_, RRType::AAAA(),
                   RRType::AAAA(), this->rrttl_, ZoneFinder::SUCCESS,
                   this->expected_rdatas_, this->empty_rdatas_);
    }
}

TYPED_TEST(DatabaseClientTest, deleteNoMatch) {
    // similar to the previous test, but there's not even a match in the
    // specified RRset.  Essentially there's no difference in the result.
    this->updater_ = this->client_->getUpdater(this->zname_, false);
    this->updater_->deleteRRset(*this->rrset_);
    {
        SCOPED_TRACE("delete no match");
        this->expected_rdatas_.push_back("192.0.2.1");
        doFindTest(this->updater_->getFinder(), this->qname_, this->qtype_,
                   this->qtype_, this->rrttl_, ZoneFinder::SUCCESS,
                   this->expected_rdatas_, this->empty_rdatas_);
    }
}

TYPED_TEST(DatabaseClientTest, deleteWithDifferentTTL) {
    // Our delete interface simply ignores TTL (may change in a future version)
    this->rrset_.reset(new RRset(this->qname_, this->qclass_, this->qtype_,
                                 RRTTL(1800)));
    this->rrset_->addRdata(rdata::createRdata(this->rrset_->getType(),
                                              this->rrset_->getClass(),
                                              "192.0.2.1"));
    this->updater_ = this->client_->getUpdater(this->zname_, false);
    this->updater_->deleteRRset(*this->rrset_);
    {
        SCOPED_TRACE("delete RRset with a different TTL");
        doFindTest(this->updater_->getFinder(), this->qname_, this->qtype_,
                   this->qtype_, this->rrttl_, ZoneFinder::NXRRSET,
                   this->empty_rdatas_, this->empty_rdatas_);
    }
}

TYPED_TEST(DatabaseClientTest, deleteDeviantRR) {
    this->updater_ = this->client_->getUpdater(this->zname_, false);

    // RR class mismatch.  This should be detected and rejected.
    this->rrset_.reset(new RRset(this->qname_, RRClass::CH(), RRType::TXT(),
                                 this->rrttl_));
    this->rrset_->addRdata(rdata::createRdata(this->rrset_->getType(),
                                              this->rrset_->getClass(),
                                              "test text"));
    EXPECT_THROW(this->updater_->deleteRRset(*this->rrset_), DataSourceError);

    // Out-of-zone owner name.  At a higher level this should be rejected,
    // but it doesn't happen in this interface.
    this->rrset_.reset(new RRset(Name("example.com"), this->qclass_,
                                 this->qtype_, this->rrttl_));
    this->rrset_->addRdata(rdata::createRdata(this->rrset_->getType(),
                                              this->rrset_->getClass(),
                                              "192.0.2.100"));
    EXPECT_NO_THROW(this->updater_->deleteRRset(*this->rrset_));
}

TYPED_TEST(DatabaseClientTest, deleteAfterCommit) {
   this->updater_ = this->client_->getUpdater(this->zname_, false);
   this->updater_->commit();
   EXPECT_THROW(this->updater_->deleteRRset(*this->rrset_), DataSourceError);
}

TYPED_TEST(DatabaseClientTest, deleteEmptyRRset) {
    this->updater_ = this->client_->getUpdater(this->zname_, false);
    this->rrset_.reset(new RRset(this->qname_, this->qclass_, this->qtype_,
                                 this->rrttl_));
    EXPECT_THROW(this->updater_->deleteRRset(*this->rrset_), DataSourceError);
}

TYPED_TEST(DatabaseClientTest, deleteRRsetWithRRSIG) {
    this->updater_ = this->client_->getUpdater(this->zname_, false);
    this->rrset_->addRRsig(*this->rrsigset_);
    EXPECT_THROW(this->updater_->deleteRRset(*this->rrset_), DataSourceError);
}

TYPED_TEST(DatabaseClientTest, compoundUpdate) {
    // This test case performs an arbitrary chosen add/delete operations
    // in a single update transaction.  Essentially there is nothing new to
    // test here, but there may be some bugs that was overlooked and can
    // only happen in the compound update scenario, so we test it.

    this->updater_ = this->client_->getUpdater(this->zname_, false);

    // add a new RR to an existing RRset
    this->updater_->addRRset(*this->rrset_);
    this->expected_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.1");
    this->expected_rdatas_.push_back("192.0.2.2");
    doFindTest(this->updater_->getFinder(), this->qname_, this->qtype_,
               this->qtype_, this->rrttl_, ZoneFinder::SUCCESS,
               this->expected_rdatas_, this->empty_rdatas_);

    // delete an existing RR
    this->rrset_.reset(new RRset(Name("www.example.org"), this->qclass_,
                                 this->qtype_, this->rrttl_));
    this->rrset_->addRdata(rdata::createRdata(this->rrset_->getType(),
                                              this->rrset_->getClass(),
                                              "192.0.2.1"));
    this->updater_->deleteRRset(*this->rrset_);
    this->expected_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.2");
    doFindTest(this->updater_->getFinder(), this->qname_, this->qtype_,
               this->qtype_, this->rrttl_, ZoneFinder::SUCCESS,
               this->expected_rdatas_, this->empty_rdatas_);

    // re-add it
    this->updater_->addRRset(*this->rrset_);
    this->expected_rdatas_.push_back("192.0.2.1");
    doFindTest(this->updater_->getFinder(), this->qname_, this->qtype_,
               this->qtype_, this->rrttl_, ZoneFinder::SUCCESS,
               this->expected_rdatas_, this->empty_rdatas_);

    // add a new RR with a new name
    const Name newname("newname.example.org");
    const RRType newtype(RRType::AAAA());
    doFindTest(this->updater_->getFinder(), newname, newtype, newtype,
               this->rrttl_, ZoneFinder::NXDOMAIN, this->empty_rdatas_,
               this->empty_rdatas_);
    this->rrset_.reset(new RRset(newname, this->qclass_, newtype,
                                 this->rrttl_));
    this->rrset_->addRdata(rdata::createRdata(this->rrset_->getType(),
                                              this->rrset_->getClass(),
                                              "2001:db8::10"));
    this->rrset_->addRdata(rdata::createRdata(this->rrset_->getType(),
                                              this->rrset_->getClass(),
                                              "2001:db8::11"));
    this->updater_->addRRset(*this->rrset_);
    this->expected_rdatas_.clear();
    this->expected_rdatas_.push_back("2001:db8::10");
    this->expected_rdatas_.push_back("2001:db8::11");
    doFindTest(this->updater_->getFinder(), newname, newtype, newtype,
               this->rrttl_, ZoneFinder::SUCCESS, this->expected_rdatas_,
               this->empty_rdatas_);

    // delete one RR from the previous set
    this->rrset_.reset(new RRset(newname, this->qclass_, newtype,
                                 this->rrttl_));
    this->rrset_->addRdata(rdata::createRdata(this->rrset_->getType(),
                                              this->rrset_->getClass(),
                                              "2001:db8::11"));
    this->updater_->deleteRRset(*this->rrset_);
    this->expected_rdatas_.clear();
    this->expected_rdatas_.push_back("2001:db8::10");
    doFindTest(this->updater_->getFinder(), newname, newtype, newtype,
               this->rrttl_, ZoneFinder::SUCCESS, this->expected_rdatas_,
               this->empty_rdatas_);

    // Commit the changes, confirm the entire changes applied.
    this->updater_->commit();
    shared_ptr<DatabaseClient::Finder> finder(this->getFinder());
    this->expected_rdatas_.clear();
    this->expected_rdatas_.push_back("192.0.2.2");
    this->expected_rdatas_.push_back("192.0.2.1");
    doFindTest(*finder, this->qname_, this->qtype_, this->qtype_, this->rrttl_,
               ZoneFinder::SUCCESS, this->expected_rdatas_,
               this->empty_rdatas_);

    this->expected_rdatas_.clear();
    this->expected_rdatas_.push_back("2001:db8::10");
    doFindTest(*finder, newname, newtype, newtype, this->rrttl_,
               ZoneFinder::SUCCESS, this->expected_rdatas_,
               this->empty_rdatas_);
}
}
