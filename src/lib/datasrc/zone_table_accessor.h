// Copyright (C) 2013  Internet Systems Consortium, Inc. ("ISC")
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

#ifndef DATASRC_ZONE_TABLE_ACCESSOR_H
#define DATASRC_ZONE_TABLE_ACCESSOR_H

#include <dns/name.h>

#include <boost/noncopyable.hpp>
#include <boost/shared_ptr.hpp>

#include <stdint.h>

namespace isc {
namespace datasrc {

/// \brief Information of a zone stored in a data source zone table.
///
/// This is a straightforward composite type that represents an entry of
/// the conceptual zone table referenced by \c ZoneTableAccessor.
/// An object of this structure is specifically intended to be returned by
/// \c ZoneTableIterator.
///
/// This is essentially a read-only tuple; only created by
/// \c ZoneTableAccessor, and once created it will be immutable.
///
/// \note Once Trac #2144 is completed, this struct must be defined as
/// non-assignable because it has a const member variable.
struct ZoneSpec {
    /// \brief Constructor.
    ZoneSpec(uint32_t index_param, const dns::Name& origin_param) :
        index(index_param), origin(origin_param)
    {}

    /// \brief Numeric zone index.
    ///
    /// In the current initial version, this field is just a placeholder.
    /// In the future, we'll probably define it as a unique index in the table
    /// for that particular zone so that applications can distinguish
    /// and specify different zones efficiently. Until it's fixed, this field
    /// shouldn't be used by applications.
    const uint32_t index;

    /// \brief The origin name of the zone.
    const dns::Name origin;
};

/// \brief A simple iterator of zone table.
///
/// This is an abstract base class providing simple iteration operation
/// over zones stored in a data source.  A concrete object of this class
/// is expected to be returned by \c ZoneTableAccessor::getIterator().
///
/// The interface is intentionally simplified and limited: it works
/// "forward-only", i.e, only goes from begin to end one time; it's not
/// copyable, assignable, nor comparable.  For the latter reasons it's not
/// compatible with standard iterator traits.  It's simplified because it's
/// not clear what kind of primitive can be used in specific data sources.
/// In particular, iteration in a database-based data source would be very
/// restrictive.  So it's better to begin with minimal guaranteed features
/// at the base class.  If we find it possible to loosen the restriction
/// as we implement more derived versions, we may extend the features later.
///
/// Likewise, this iterator does not guarantee the ordering of the zones
/// returned by \c getCurrent().  It's probably possible to ensure some
/// sorted order, but until we can be sure it's the case for many cases
/// in practice, we'll not rely on it.
///
/// A concrete object of this class is created by specific derived
/// implementation for the corresponding data source.  The implementation
/// must ensure the iterator is located at the "beginning" of the zone table,
/// and that subsequent calls to \c next() go through all the zones
/// one by one, until \c isLast() returns \c true.  The implementation must
/// support the concept of "empty table"; in that case \c isLast() will
/// return \c true from the beginning.
class ZoneTableIterator : boost::noncopyable {
protected:
    /// \brief The constructor.
    ///
    /// This class is not expected to be instantiated directly, so the
    /// constructor is hidden from normal applications as protected.
    ZoneTableIterator() {}

public:
    /// \brief The destructor.
    virtual ~ZoneTableIterator() {}

    /// \brief Return if the iterator reaches the end of the zone table.
    virtual bool isLast() const = 0;

    /// \brief Move the iterator to the next zone of the table.
    ///
    /// This method must not be called once the iterator reaches the end
    /// of the table.
    ///
    /// \throw InvalidOperation called after reaching the end of table.
    void next() {
        // Perform common check, and delegate the actual work to the protected
        // method.
        if (isLast()) {
            isc_throw(InvalidOperation,
                      "next() called on iterator beyond end of zone table");
        }
        nextImpl();
    }

    /// \brief Return the information of the zone at which the iterator is
    /// currently located in the form of \c ZoneSpec.
    ///
    /// This method must not be called once the iterator reaches the end
    /// of the zone table.
    ///
    /// \throw InvalidOperation called after reaching the end of table.
    ///
    /// \return Information of the "current" zone.
    ZoneSpec getCurrent() const {
        // Perform common check, and delegate the actual work to the protected
        // method.
        if (isLast()) {
            isc_throw(InvalidOperation,
                      "getCurrent() called on iterator beyond "
                      "end of zone table");
        }
        return (getCurrentImpl());
    }

protected:
    /// \brief Actual implementation of \c next().
    ///
    /// Each derived class must provide the implementation of \c next()
    /// in its data source specific form, except for the common
    /// validation check.
    virtual void nextImpl() = 0;

    /// \brief Actual implementation of \c getCurrent().
    ///
    /// Each derived class must provide the implementation of
    /// \c getCurrent() in its data source specific form, except for the
    /// common validation check.
    virtual ZoneSpec getCurrentImpl() const = 0;
};

/// \brief An abstract accessor to conceptual zone table for a data source.
///
/// This is an abstract base class providing common interfaces to get access
/// to a conceptual "zone table" corresponding to a specific data source.
/// A zone table would contain a set of information about DNS zones stored in
/// the data source.  It's "conceptual" in that the actual form of the
/// information is specific to the data source implementation.
///
/// The initial version of this class only provides one simple feature:
/// iterating over the table so that an application can get a list of
/// all zones of a specific data source (of a specific RR class).  In
/// future, this class will be extended so that, e.g., applications can
/// add or remove zones.
///
/// \note It may make sense to move \c DataSourceClient::createZone()
/// and \c DataSourceClient::deleteZone() to this class.
class ZoneTableAccessor : boost::noncopyable {
protected:
    /// \brief The constructor.
    ///
    /// This class is not expected to be instantiated directly, so the
    /// constructor is hidden from normal applications as protected.
    ZoneTableAccessor() {}

public:
    /// \brief Shortcut type for a smart pointer of \c ZoneTableIterator
    typedef boost::shared_ptr<ZoneTableIterator> IteratorPtr;

    /// \brief The destructor.
    virtual ~ZoneTableAccessor() {}

    /// \brief Return a zone table iterator.
    ///
    /// In general, the specific implementation of the iterator object would
    /// contain some form of reference to the underlying data source
    /// (e.g., a database connection or a pointer to memory region), which
    /// would be valid only until the object that created the instance of
    /// the accessor is destroyed.  The iterator must not be used beyond
    /// the lifetime of such a creator object, and normally it's expected to
    /// be even more ephemeral: it would be created by this method in a
    /// single method or function and only used in that limited scope.
    ///
    /// \throw std::bad_alloc Memory allocation for the iterator object failed.
    /// \throw Others There will be other cases as more implementations
    /// are added (in this initial version, it's not really decided yet).
    ///
    /// \return A smart pointer to a newly created iterator object.  Once
    /// returned, the \c ZoneTableAccessor effectively releases its ownership.
    virtual IteratorPtr getIterator() const = 0;
};

}
}

#endif  // DATASRC_ZONE_TABLE_ACCESSOR_H

// Local Variables:
// mode: c++
// End:
