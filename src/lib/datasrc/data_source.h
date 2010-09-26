// Copyright (C) 2009  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef __DATA_SOURCE_H
#define __DATA_SOURCE_H

#include <stdint.h>

#include <vector>

#include <boost/shared_ptr.hpp>

#include <exceptions/exceptions.h>

#include <dns/name.h>
#include <dns/rrclass.h>
#include <cc/data.h>

namespace isc {

namespace dns {
class Name;
class RRType;
class RRset;
class RRsetList;
}

namespace datasrc {

class DataSrcMatch;
class Query;

class DataSrc;
typedef boost::shared_ptr<DataSrc> DataSrcPtr;
typedef boost::shared_ptr<const DataSrc> ConstDataSrcPtr;

/// This exception represents Backend-independent errors relating to
/// data source operations.
class DataSourceError : public Exception {
public:
    DataSourceError(const char* file, size_t line, const char* what) :
        isc::Exception(file, line, what) {}
};


class AbstractDataSrc {
    ///
    /// \name Constructors, Assignment Operator and Destructor.
    ///
    /// Note: The copy constructor and the assignment operator are intentionally
    /// defined as private to make it explicit that this is a pure base class.
private:
    AbstractDataSrc(const AbstractDataSrc& source);
    AbstractDataSrc& operator=(const AbstractDataSrc& source);
protected:
    /// \brief The default constructor.
    ///
    /// This is intentionally defined as \c protected as this base class should
    /// never be instantiated (except as part of a derived class).
    AbstractDataSrc() {}
public:
    /// \brief The destructor.
    virtual ~AbstractDataSrc() {};
    //@}

    enum Result {
        SUCCESS,
        ERROR,
        NOT_IMPLEMENTED
    };

    // These flags indicate conditions encountered while processing a query.
    //
    // REFERRAL:       The node contains an NS record
    // CNAME_FOUND:    The node contains a CNAME record
    // NAME_NOT_FOUND: The node does not exist in the data source.
    // TYPE_NOT_FOUND: The node does not contain the requested RRType
    // NO_SUCH_ZONE:   The zone does not exist in this data source.
    //
    // DATA_NOT_FOUND: A combination of the last three, for coding convenience
    enum QueryResponseFlags {
        REFERRAL = 0x01,
        CNAME_FOUND = 0x02,
        NAME_NOT_FOUND = 0x04,
        TYPE_NOT_FOUND = 0x08,
        NO_SUCH_ZONE = 0x10,
        DATA_NOT_FOUND = (NAME_NOT_FOUND|TYPE_NOT_FOUND|NO_SUCH_ZONE)
    };

    // 'High-level' methods.  These will be implemented by the
    // general DataSrc class, and SHOULD NOT be overwritten by subclasses.
    virtual void doQuery(Query& query) = 0;

    // XXX: High-level methods to be implemented later:
    // virtual void doUpdate(Update update) = 0;
    // virtual void doXfr(Query query) = 0;

    // 'Medium-level' methods.  This will be implemented by the general
    // DataSrc class but MAY be overwritten by subclasses.
    virtual void findClosestEnclosure(DataSrcMatch& match) const = 0;

    // Optional 'low-level' methods.  These will have stub implementations
    // in the general DataSrc class but MAY be overwritten by subclasses
    virtual Result init() = 0;
    virtual Result init(isc::data::ConstElementPtr config) = 0;
    virtual Result close() = 0;

    // Mandatory 'low-level' methods: These will NOT be implemented by
    // the general DataSrc class; subclasses MUST implement them.
    virtual Result findRRset(const isc::dns::Name& qname,
                             const isc::dns::RRClass& qclass,
                             const isc::dns::RRType& qtype,
                             isc::dns::RRsetList& target,
                             uint32_t& flags,
                             const isc::dns::Name* zonename) const = 0;

    virtual Result findExactRRset(const isc::dns::Name& qname,
                                  const isc::dns::RRClass& qclass,
                                  const isc::dns::RRType& qtype,
                                  isc::dns::RRsetList& target,
                                  uint32_t& flags,
                                  const isc::dns::Name* zonename) const = 0;

    // These will have dumb implementations in the general DataSrc
    // class, and SHOULD be overwritten by subclasses.
    virtual Result findAddrs(const isc::dns::Name& qname,
                             const isc::dns::RRClass& qclass,
                             isc::dns::RRsetList& target,
                             uint32_t& flags,
                             const isc::dns::Name* zonename) const = 0;

     virtual Result findReferral(const isc::dns::Name& qname,
                                 const isc::dns::RRClass& qclass,
                                 isc::dns::RRsetList& target,
                                 uint32_t& flags,
                                 const isc::dns::Name* zonename) const = 0;

    // This MUST be implemented by concrete data sources which support
    // DNSSEC, but is optional for others (e.g., the static data source).
    virtual Result findPreviousName(const isc::dns::Name& qname,
                                    isc::dns::Name& target,
                                    const isc::dns::Name* zonename) const = 0;

   // This MUST be implemented by concrete data sources which support
   // NSEC3, but is optional for others
   virtual Result findCoveringNSEC3(const isc::dns::Name& zonename,
                                    std::string& hash,
                                    isc::dns::RRsetList& target) const = 0;
};

// Base class for a DNS Data Source
class DataSrc : public AbstractDataSrc {
    ///
    /// \name Constructors, Assignment Operator and Destructor.
    ///
    /// Note: The copy constructor and the assignment operator are intentionally
    /// defined as private.
private:
    DataSrc(const DataSrc& source);
    DataSrc& operator=(const DataSrc& source);
public:
    DataSrc() : rrclass(isc::dns::RRClass::IN()) {}
    DataSrc(const isc::dns::RRClass& c) : rrclass(c) {}
    /// \brief The destructor.
    virtual ~DataSrc() {};
    //@}

    virtual void doQuery(Query& q);

    virtual void findClosestEnclosure(DataSrcMatch& match) const = 0;

    const isc::dns::RRClass& getClass() const { return (rrclass); }
    void setClass(isc::dns::RRClass& c) { rrclass = c; }
    void setClass(const isc::dns::RRClass& c) { rrclass = c; }

    Result init() { return (NOT_IMPLEMENTED); }
    Result init(isc::data::ConstElementPtr config);
    Result close() { return (NOT_IMPLEMENTED); }

    virtual Result findRRset(const isc::dns::Name& qname,
                             const isc::dns::RRClass& qclass,
                             const isc::dns::RRType& qtype,
                             isc::dns::RRsetList& target,
                             uint32_t& flags,
                             const isc::dns::Name* zonename) const = 0;

    virtual Result findExactRRset(const isc::dns::Name& qname,
                                  const isc::dns::RRClass& qclass,
                                  const isc::dns::RRType& qtype,
                                  isc::dns::RRsetList& target,
                                  uint32_t& flags,
                                  const isc::dns::Name* zonename) const = 0;

    virtual Result findAddrs(const isc::dns::Name& qname,
                             const isc::dns::RRClass& qclass,
                             isc::dns::RRsetList& target,
                             uint32_t& flags,
                             const isc::dns::Name* zonename) const;

    virtual Result findReferral(const isc::dns::Name& qname,
                                const isc::dns::RRClass& qclass,
                                isc::dns::RRsetList& target,
                                uint32_t& flags,
                                const isc::dns::Name* zonename) const;

    virtual Result findPreviousName(const isc::dns::Name& qname,
                                    isc::dns::Name& target,
                                    const isc::dns::Name* zonename) const = 0;

   virtual Result findCoveringNSEC3(const isc::dns::Name& zonename,
                                    std::string& hash,
                                    isc::dns::RRsetList& target) const = 0;

private:
    isc::dns::RRClass rrclass;
};

class MetaDataSrc : public DataSrc {
    ///
    /// \name Constructors, Assignment Operator and Destructor.
    ///
    /// Note: The copy constructor and the assignment operator are intentionally
    /// defined as private.
    //@{
private:
    MetaDataSrc(const MetaDataSrc& source);
    MetaDataSrc& operator=(const MetaDataSrc& source);
public:
    MetaDataSrc() : DataSrc(isc::dns::RRClass::ANY()) {}
    MetaDataSrc(const isc::dns::RRClass& c) : DataSrc(c) {}
    /// \brief The destructor.
    virtual ~MetaDataSrc() {}
    //@}

    void addDataSrc(ConstDataSrcPtr data_src);
    void removeDataSrc(ConstDataSrcPtr data_src);
    size_t dataSrcCount() { return (data_sources.size()); }
    
    void findClosestEnclosure(DataSrcMatch& match) const;

    // Actual queries for data should not be sent to a MetaDataSrc object,
    // so we return NOT_IMPLEMENTED if we receive any.
    //
    // The proper way to use the MetaDataSrc is to run findClosestEnclosure()
    // to get a pointer to the best concrete data source for the specified
    // zone, then send all queries directly to that data source.

    Result findRRset(const isc::dns::Name& qname,
                     const isc::dns::RRClass& qclass,
                     const isc::dns::RRType& qtype,
                     isc::dns::RRsetList& target,
                     uint32_t& flags,
                     const isc::dns::Name* zonename) const;

    Result findExactRRset(const isc::dns::Name& qname,
                          const isc::dns::RRClass& qclass,
                          const isc::dns::RRType& qtype,
                          isc::dns::RRsetList& target,
                          uint32_t& flags,
                          const isc::dns::Name* zonename) const;

    Result findAddrs(const isc::dns::Name& qname,
                     const isc::dns::RRClass& qclass,
                     isc::dns::RRsetList& target,
                     uint32_t& flags,
                     const isc::dns::Name* zonename) const;

    Result findReferral(const isc::dns::Name& qname,
                        const isc::dns::RRClass& qclass,
                        isc::dns::RRsetList& target,
                        uint32_t& flags,
                        const isc::dns::Name* zonename) const;

    virtual Result findPreviousName(const isc::dns::Name& qname,
                                    isc::dns::Name& target,
                                    const isc::dns::Name* zonename) const;

   virtual Result findCoveringNSEC3(const isc::dns::Name& zonename,
                                    std::string& hash,
                                    isc::dns::RRsetList& target) const;

private:
    std::vector<ConstDataSrcPtr> data_sources;
};

/// \brief Information about the zone along with the %data source that best
/// matches a give name and RR class.
///
/// A \c DataSrcMatch object is created with a domain name and RR class to
/// hold the search state of looking for the zone and the %data source that
/// stores the zone that best match the given name and RR class.
/// The application of this class passes an object of \c DataSrcMatch to
/// one or more ^data sources via their \c findClosestEnclosure() method.
/// The %data source searches its content for the given key, and update
/// the state if it finds a better zone than the currently recorded one.
///
/// The state of a \c DataSrcMatch object should be updated if and only if:
///  - The specified RR class and the RR class of the %data source are the
//     same, or the specified RR class is ANY; and
///  - There is no matching %data source and name found (which is probably
///    wrong, see below), or the given enclosing name gives a longer match
///    than the currently stored enclosing name against the specified name.
class DataSrcMatch {
    ///
    /// \name Constructors, Assignment Operator and Destructor.
    ///
    /// Note: The copy constructor and the assignment operator are
    /// intentionally defined as private.
    //@{
private:
    DataSrcMatch(const DataSrcMatch& source);
    DataSrcMatch& operator=(const DataSrcMatch& source);
public:
    /// \brief The constructor.
    ///
    /// This constructor normally doesn't throw an exception.  However,
    /// it creates a copy of the given name object, which may require memory
    /// allocation, and if it fails the corresponding standard exception will
    /// be thrown.
    ///
    /// \param name The domain name to be matched.
    /// \param rrclass The RR class to be matched
    DataSrcMatch(const isc::dns::Name& name,
                 const isc::dns::RRClass& rrclass) :
        closest_name_(NULL), best_source_(NULL),
        name_(name), rrclass_(rrclass)
    {}
    ~DataSrcMatch();
    //@}

    /// \name Getter and Setter Methods
    //@{
    /// \brief Returns the name to be matched.
    const isc::dns::Name& getName() const { return (name_); }

    /// \brief Returns the RR class to be matched.
    ///
    /// This method never throws an exception.
    const isc::dns::RRClass& getClass() const { return (rrclass_); }

    /// \brief Returns the best enclosing zone name found for the given
    // name and RR class so far.
    /// 
    /// \return A pointer to the zone apex \c Name, NULL if none found yet.
    ///
    /// This method never throws an exception.
    const isc::dns::Name* getEnclosingZone() const { return (closest_name_); }

    /// \brief Returns the best %data source found for the given name and
    /// RR class so far.
    ///
    /// This method never throws an exception.
    ///
    /// \return A pointer to a concrete %data source, NULL if none found yet.
    const DataSrc* getDataSource() const { return (best_source_); }
    //@}

    /// \brief Update the object state with better information if possible.
    ///
    /// This method is intended to be called by a concrete %data source's
    /// \c findClosestEnclosure() method to store the best match for
    /// the given name and class that has been found so far.
    ///
    /// It compares the best name (if found) and \c container, and if the
    /// latter gives a longer match, it will install the given %data source
    /// and the enclosing name as the best match;
    /// if there is no known pair of %data source and enclosing name,
    /// this method will install the given pair unconditionally.
    /// (which is probably BAD);
    /// otherwise this method does nothing.
    ///
    /// In any case, if a new pair of %data source and enclosing name are
    /// installed, a new name object will be internally allocated.
    /// And, if memory allocation fails the corresponding standard exception
    /// will be thrown.
    ///
    /// \param new_source A candidate %data source that gives a better match.
    /// \param container The enclosing name of the matching zone in
    /// \c new_source.
    void update(const DataSrc& new_source, const isc::dns::Name& container);

private:
    isc::dns::Name* closest_name_;
    const DataSrc* best_source_;
    const isc::dns::Name name_;
    const isc::dns::RRClass& rrclass_;
};

class Nsec3Param {
public:
    Nsec3Param(uint8_t a, uint8_t f, uint16_t i, const std::vector<uint8_t>& s);
    std::string getHash(const isc::dns::Name& name) const;
private:
    const uint8_t algorithm_;
    const uint8_t flags_;
    const uint16_t iterations_;
    const std::vector<uint8_t> salt_;
};

}
}

#endif

// Local Variables: 
// mode: c++
// End: 
